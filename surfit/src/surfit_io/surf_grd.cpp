
/*------------------------------------------------------------------------------
 *	$Id$
 *
 *	Copyright (c) 2002-2006 by M. V. Dmitrievsky
 *	See COPYING file for copying and redistribution conditions.
 *
 *	This program is free software; you can redistribute it and/or modify
 *	it under the terms of the GNU General Public License as published by
 *	the Free Software Foundation; version 2 of the License.
 *
 *	This program is distributed in the hope that it will be useful,
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *	GNU General Public License for more details.
 *
 *	Contact info: surfit.sourceforge.net
 *----------------------------------------------------------------------------*/

#include "surfit_io_ie.h"
#include "surf_io.h"

// sstuff includes
#include "sstuff.h"

// surfit includes
#include "surf.h"
#include "fileio.h"
#include "vec.h"
#include "variables_tcl.h"
#include "grid.h"
#include "curv.h"
#include "free_elements.h"

#ifdef HAVE_UNISTD_H
#include <unistd.h>
#endif

#if defined(_WIN32) || defined(__WIN32__) || defined(WIN32)
#include <io.h>
#endif

#include <fcntl.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>

namespace surfit {

d_surf * _surf_load_grd(const char * filename, const char * surfname) 
{

	FILE * file = fopen(filename,"r");
	if (!file) {
		writelog(LOG_ERROR, "surf_load_grd : the file %s was not opened: %s",filename,strerror( errno ));
		return NULL;
	};

	int nx, ny;
	REAL miny, maxy;
	REAL minx, maxx;
	REAL minz, maxz;
	REAL stepX, stepY;
	d_grid * grd = NULL;
	d_surf * res = NULL;
	extvec * data = NULL;

	char buf[200];
	
	//if ( fscanf(file, "%s", buf) == 0)
	//	goto exit;
	if ( fread(buf, sizeof(char), 4, file) != 4)
		goto exit;
	buf[4]='\0';

	if (strcmp(buf,"DSAA") == 0)
		writelog(LOG_MESSAGE, "loading surface from Surfer GRD-ASCII format file %s",filename);

	if (strcmp(buf,"DSBB") == 0) {
		fclose(file);
		return _surf_load_grd_bin(filename, surfname);
	}

	if (strcmp(buf,"DSRB") == 0) {
		fclose(file);
		return _surf_load_grd_bin7(filename, surfname);
	}
		
	if (strcmp(buf,"DSAA") != 0) 
		goto exit;
	
	int ix, iy;

	if (fscanf(file, "%s", buf) != 1)
		goto exit;
	nx = atoi(buf);

	if (fscanf(file, "%s", buf) != 1)
		goto exit;
	ny = atoi(buf);

	if (fscanf(file, "%s", buf) != 1)
		goto exit;
	minx = atof(buf);

	if (fscanf(file, "%s", buf) != 1)
		goto exit;
	maxx = atof(buf);

	if (fscanf(file, "%s", buf) != 1)
		goto exit;
	miny = atof(buf);

	if (fscanf(file, "%s", buf) != 1)
		goto exit;
	maxy = atof(buf);

	if (fscanf(file, "%s", buf) != 1)
		goto exit;
	minz = atof(buf);

	if (fscanf(file, "%s", buf) != 1)
		goto exit;
	maxz = atof(buf);

	data = create_extvec(nx*ny);
	REAL value;

	for(iy=0; iy<ny; iy++) {
		for(ix=0; ix<nx; ix++) {
			
			if (fscanf(file, "%s", buf) != 1)
				goto exit;
	
			value = atof(buf);
			if ((value >= minz) && (value <= maxz))
				(*data)(ix + iy*nx) = value;
			else 
				(*data)(ix + iy*nx) = undef_value;
		}
	}

	if (fscanf(file, "%s", buf) == 1)
		goto exit;

	stepX = (maxx-minx)/(nx-1);
	stepY = (maxy-miny)/(ny-1);
	grd = create_grid(minx, maxx, stepX,
			  miny, maxy, stepY);

	res = create_surf(data, grd);

	fclose(file);

	if (surfname)
		res->setName(surfname);
	else {
		char * name = get_name(filename);
		res->setName(name);
		sstuff_free_char(name);
	}

	return res;

exit:
	writelog(LOG_ERROR, "surf_load_grd : Wrong file format %s", filename);
	
	if (res)
		res->release();
	if (data)
		data->release();
	if (grd)
		grd->release();
	fclose(file);
	return NULL;
};

d_surf * _surf_load_grd_bin(const char * filename, const char * surfname) 
{

	FILE * file = fopen(filename,"rb");
	if (!file) {
		writelog(LOG_ERROR, "surf_load_grd : the file %s was not opened: %s",filename,strerror( errno ));
		return NULL;
	};

	short nx, ny;
	size_t i;
	REAL miny, maxy;
	REAL minx, maxx;
	REAL minz, maxz;
	REAL stepX, stepY;
	d_grid * grd = NULL;
	d_surf * res = NULL;
	extvec * data = NULL;
	float * fdata = NULL;
	REAL value;

	char buf[200];
	
	if ( fread(buf, sizeof(char), 4, file) != 4)
		goto exit;
	buf[4]='\0';

	if (strcmp(buf,"DSAA") == 0) {
		fclose(file);
		return _surf_load_grd(filename, surfname);
	}

	if (strcmp(buf,"DSRB") == 0) {
		fclose(file);
		return _surf_load_grd_bin7(filename, surfname);
	}

	if (strcmp(buf,"DSBB") == 0) {
		writelog(LOG_MESSAGE, "loading surface from Surfer GRD format file %s",filename);
	}
		
	if (strcmp(buf,"DSBB") != 0) 
		goto exit;
	
	if ( fread(&nx, sizeof(short), 1, file) != 1)
		goto exit;

	if ( fread(&ny, sizeof(short), 1, file) != 1)
		goto exit;

	if ( fread(&minx, sizeof(double), 1, file) != 1)
		goto exit;

	if ( fread(&maxx, sizeof(double), 1, file) != 1)
		goto exit;

	if ( fread(&miny, sizeof(double), 1, file) != 1)
		goto exit;

	if ( fread(&maxy, sizeof(double), 1, file) != 1)
		goto exit;

	if ( fread(&minz, sizeof(double), 1, file) != 1)
		goto exit;

	if ( fread(&maxz, sizeof(double), 1, file) != 1)
		goto exit;

	fdata = (float*)malloc( nx*ny*sizeof(float) );
	if (fdata == NULL)
		goto exit;

	if ( fread(fdata, sizeof(float), nx*ny, file) != nx*ny )
		goto exit;

	fclose(file);

	data = create_extvec(nx*ny);
	for (i = 0; i < (size_t)(nx*ny); i++) {
		value = REAL(*(fdata + i));
		if ((value < minz) || (value > maxz))
			value = undef_value;
		(*data)(i) = value;
	}

	free(fdata);
	fdata = NULL;
	
	stepX = (maxx-minx)/(nx-1);
	stepY = (maxy-miny)/(ny-1);
	grd = create_grid(minx, maxx, stepX,
			  miny, maxy, stepY);

	res = create_surf(data, grd);

	if (surfname)
		res->setName(surfname);
	else {
		char * name = get_name(filename);
		res->setName(name);
		sstuff_free_char(name);
	}

	return res;

exit:
	writelog(LOG_ERROR, "surf_load_grd : Wrong file format %s", filename);
	
	if (res)
		res->release();
	if (data)
		data->release();
	if (grd)
		grd->release();
	fclose(file);
	return NULL;
};

d_surf * _surf_load_grd_bin7(const char * filename, const char * surfname) 
{

	int file = -1;
#if defined(_WIN32) || defined(__WIN32__) || defined(WIN32)
	file = open(filename, O_BINARY|O_RDONLY);
#else
	file = open(filename, O_RDONLY);
#endif
	
	if (file == -1) {
		writelog(LOG_ERROR, "surf_load_grd : the file %s was not opened: %s",filename,strerror( errno ));
		return NULL;
	};

	long id, size, version;

	long nx, ny;
	long nTraces, nVertices;
	size_t i;
	double miny, maxy;
	double minx, maxx;
	double minz, maxz;
	double rotation, blank;
	REAL stepX, stepY;
	d_grid * grd = NULL;
	d_surf * res = NULL;
	extvec * data = NULL;
	double * dbuf = NULL;
	REAL value;

	vec * XX = NULL;
	vec * YY = NULL;
	std::vector<d_curv *> faults;
	std::vector<long> iFirsts;
	std::vector<long> nPoints;

	char * name = get_name(filename);

	char buf[200];
	
	if ( read(file, buf, sizeof(char)*4) != sizeof(char)*4)
		goto exit;
	buf[4]='\0';

	if (strcmp(buf,"DSAA") == 0) {
		close(file);
		return _surf_load_grd(filename, surfname);
	}

	if (strcmp(buf,"DSBB") == 0) {
		close(file);
		return _surf_load_grd_bin(filename, surfname);
	}

	if (strcmp(buf,"DSRB") == 0) {
		writelog(LOG_MESSAGE, "loading surface from Surfer7 GRD format file %s",filename);
	}
		
	if (strcmp(buf,"DSRB") != 0) 
		goto exit;
	
	if ( read( file, &size, sizeof(long) ) != sizeof(long) )
		goto exit;

	if (size != 4)
		goto exit;

	if ( read( file, &version, sizeof(long) ) != sizeof(long) )
		goto exit;

	while (true) {
		
		// read tag id
		size_t readed = read( file, &id, sizeof(long) );
		if (readed == 0)
			break;
		if ( readed != sizeof(long) )
			goto exit;
		// read tag size
		if ( read( file, &size, sizeof(long) ) != sizeof(long) )
			goto exit;
		
		switch (id) {
		case 0x44495247: // grid section
			{
				if (size != 72)
					goto exit;
				
				if ( read( file, &ny, sizeof(long) ) != sizeof(long) )
					goto exit;
				
				if ( read( file, &nx, sizeof(long) ) != sizeof(long) )
					goto exit;
				
				if ( read( file, &minx, sizeof(double) ) != sizeof(double) )
					goto exit;
				
				if ( read( file, &miny, sizeof(double) ) != sizeof(double) )
					goto exit;
				
				if ( read( file, &stepX, sizeof(double) ) != sizeof(double) )
					goto exit;
				
				if ( read( file, &stepY, sizeof(double) ) != sizeof(double) )
					goto exit;
				
				if ( read( file, &minz, sizeof(double) ) != sizeof(double) )
					goto exit;
				
				if ( read( file, &maxz, sizeof(double) ) != sizeof(double) )
					goto exit;
				
				if ( read( file, &rotation, sizeof(double) ) != sizeof(double) )
					goto exit;
				
				if ( read( file, &blank, sizeof(double) ) != sizeof(double) )
					goto exit;
				
				data = create_vec( nx*ny, 0, 0 ); // don't fill
				
				maxx = stepX*(nx-1)+minx;
				maxy = stepY*(ny-1)+miny;
				grd = create_grid(minx, maxx, stepX, miny, maxy, stepY);
				
			};
			break;
		case 0x41544144: // data section
			{
				if (data == NULL)
					goto exit;
				if (grd == NULL)
					goto exit;

				dbuf = (double*)malloc(nx*ny*sizeof(double));
				if ( read( file, dbuf, nx*ny*sizeof(double) ) != nx*ny*sizeof(double) )
					goto exit;

				for (i = 0; i < (size_t)(nx*ny); i++) {
					value = *(dbuf+i);
					if ((value < minz) || (value > maxz) || (value >= blank))
						(*data)(i) = undef_value;
					else 
						(*data)(i) = value;
				}
				
				free(dbuf);
				dbuf = NULL;
			};
			break;
		case 0x49544c46: // fault info section
			{
				// read nTraces
				if ( read( file, &nTraces, sizeof(long) ) != sizeof(long) )
					goto exit;
				// read nVertices
				if ( read( file, &nVertices, sizeof(long) ) != sizeof(long) )
					goto exit;
				
				if ( read( file, &id, sizeof(long) ) != sizeof(long) )
					goto exit;

				if (id != 1096040772) // DATA
					goto exit; 

				if ( read( file, &size, sizeof(long) ) != sizeof(long) )
					goto exit;

				size_t curves = surfit_curvs->size();

				char buf[512];

				for (i = 0; i < (size_t)nTraces; i++) {
					long iFirst;
					long nPnts;

					if ( read( file, &iFirst, sizeof(long) ) != sizeof(long) )
						goto exit;

					if ( read( file, &nPnts, sizeof(long) ) != sizeof(long) )
						goto exit;
					
					vec * X = create_vec(nPnts,0,0); // don't fill
					vec * Y = create_vec(nPnts,0,0); // don't fill
					sprintf(buf,"%s_%d",name, i+1);
					d_curv * curve = create_curv(X, Y, buf);

					faults.push_back(curve);
					iFirsts.push_back(iFirst);
					nPoints.push_back(nPnts);

				}

				XX = create_vec(nVertices, 0, 0); // don't fill
				YY = create_vec(nVertices, 0, 0); // don't fill

				for (i = 0; i < (size_t)nVertices; i++) {
					double x, y;
					if ( read( file, &x, sizeof(double) ) != sizeof(double) )
						goto exit;
					if ( read( file, &y, sizeof(double) ) != sizeof(double) )
						goto exit;

					(*XX)(i) = x;
					(*YY)(i) = y;
				}

				for (i = 0; i < (size_t)nTraces; i++) {
					d_curv * curve = faults[i];
					long iFirst = iFirsts[i];
					long nPos = nPoints[i];

					std::copy( XX->begin()+iFirst, XX->begin()+iFirst+nPos, curve->X->begin() );
					std::copy( YY->begin()+iFirst, YY->begin()+iFirst+nPos, curve->Y->begin() );
				}

				XX->release();
				XX = NULL;
				YY->release();
				YY = NULL;

								
			};
			break;
		default: // some other section
			{
				// skip this section
				if (lseek(file, size, SEEK_CUR) != -1L)
					goto exit;
			}
		}
	}

	if ((data ==NULL) || (grd == NULL))
		goto exit;

	res = create_surf(data, grd);

	if (surfname)
		res->setName(surfname);
	else {
		res->setName(name);
	}

	for (i = 0; i < faults.size(); i++) {
		d_curv * crv = faults[i];
		surfit_curvs_push_back(crv);
	}

	sstuff_free_char(name);

	return res;

exit:
	writelog(LOG_ERROR, "surf_load_grd : Wrong file format %s", filename);
	
	if (res)
		res->release();
	if (data)
		data->release();
	if (grd)
		grd->release();
	if (XX)
		XX->release();
	if (YY)
		YY->release();

	free(dbuf);
	sstuff_free_char(name);

	release_elements(faults.begin(), faults.end());
	close(file);
	return NULL;
};

bool _surf_save_grd(const d_surf * srf, const char * filename) {

	if (!filename)
		return false;

	if (!srf) {
		writelog(LOG_ERROR,"surf_save_grd : no surf loaded");
		return false;
	}

	FILE * f = fopen(filename,"w");

	if (!f) {
		writelog(LOG_ERROR, "Can't write data to file %s",filename,strerror( errno ));
		return false;
	}

	writelog(LOG_MESSAGE,"Saving surf %s to file %s (Surfer GRD-ASCII)", srf->getName(), filename);

	fprintf(f,"DSAA\n");
	int nx = srf->getCountX();
	int ny = srf->getCountY();

	fprintf(f,"%d %d\n", nx, ny);
	fprintf(f,"%lf %lf\n", srf->grd->startX, srf->grd->endX);
	fprintf(f,"%lf %lf\n", srf->grd->startY, srf->grd->endY);

	REAL minZ, maxZ;
	srf->getMinMaxZ(minZ, maxZ);
	fprintf(f,"%lf %lf\n", minZ, maxZ);

	// matrix 
	int iy, ix;
	int ncnt;
	int cnt = 0;
	REAL val;
	
    
	for(iy=0; iy<ny; iy++)	{
		ncnt = 0;
		
		for(ix=0; ix<nx; ix++)	{
			val = (*(srf->coeff))( ix + nx*iy );
			fprintf(f,"%lf ", val);
			if (ncnt>9) { 
				fprintf(f,"\n");
				ncnt = 0;
			}
			ncnt++;
		}
		fprintf(f,"\n");
	}

	fclose(f);

	return true;
};

bool _surf_save_grd_bin(const d_surf * srf, const char * filename) 
{
	size_t NN, MM, i;
	short nx, ny;
	double minx, maxx, miny, maxy, minz, maxz;
	REAL minZ, maxZ;
	float * fdata = NULL;

	if (!filename)
		return false;

	if (!srf) {
		writelog(LOG_ERROR,"surf_save_grd : no surf loaded");
		return false;
	}

	FILE * f = fopen(filename,"wb");

	if (!f) {
		writelog(LOG_ERROR, "Can't write data to file %s",filename,strerror( errno ));
		return false;
	}

	writelog(LOG_MESSAGE,"Saving surf %s to file %s (Surfer GRD)", srf->getName(), filename);

	NN = srf->getCountX();
	MM = srf->getCountY();

	if ((NN > SHRT_MAX) || (MM > SHRT_MAX))
	{
		writelog(LOG_ERROR,"Surface %s is too large for saving in Surfer GRD binary format!");
		goto exit;
	}

	if (fwrite("DSBB", sizeof(char), strlen("DSBB"), f) != strlen("DSBB"))
		goto exit;

	nx = (short)NN;
	ny = (short)MM;
	minx = (double)srf->grd->startX;
	miny = (double)srf->grd->startY;
	maxx = (double)srf->grd->endX;
	maxy = (double)srf->grd->endY;
	srf->getMinMaxZ(minZ, maxZ);
	minz = minZ;
	maxz = maxZ;

	if ( fwrite( &nx, sizeof(short), 1, f ) != 1 )
		goto exit;

	if ( fwrite( &ny, sizeof(short), 1, f ) != 1 )
		goto exit;

	if ( fwrite( &minx, sizeof(double), 1, f ) != 1 )
		goto exit;

	if ( fwrite( &maxx, sizeof(double), 1, f ) != 1 )
		goto exit;

	if ( fwrite( &miny, sizeof(double), 1, f ) != 1 )
		goto exit;

	if ( fwrite( &maxy, sizeof(double), 1, f ) != 1 )
		goto exit;

	if ( fwrite( &minz, sizeof(double), 1, f ) != 1 )
		goto exit;

	if ( fwrite( &maxz, sizeof(double), 1, f ) != 1 )
		goto exit;

	fdata = (float*)malloc( nx * ny * sizeof(float) );
	if (fdata == NULL)
		goto exit;
	
	for (i = 0; i < NN*MM; i++)
	{
		*(fdata+i) = (float)srf->getValue(i);
	}

	if ( fwrite( fdata, sizeof(float), nx*ny, f ) != nx*ny )
		goto exit;

	free(fdata);
	fclose(f);

	return true;

exit:

	fclose(f);
	return false;
};

bool _surf_save_grd_bin7(const d_surf * srf, const char * filename) 
{
	size_t NN, MM;
	long nx, ny;
	double minx, stepX, miny, stepY, minz, maxz;
	REAL minZ, maxZ;
	double blank = srf->undef_value;
	double rotation = 0;
	long version = 1;

	long id, size;

	if (!filename)
		return false;

	if (!srf) {
		writelog(LOG_ERROR,"surf_save_grd : no surf loaded");
		return false;
	}

	int f = -1;
#if defined(_WIN32) || defined(__WIN32__) || defined(WIN32)
	f = open(filename, O_BINARY|O_RDWR|O_TRUNC|O_APPEND);
#else
	f = open(filename, O_RDWR|O_TRUNC|O_APPEND);
#endif

	if (f == -1) {
#if defined(_WIN32) || defined(__WIN32__) || defined(WIN32)
		f = open(filename, O_BINARY|O_CREAT|O_APPEND|O_RDWR, S_IREAD|S_IWRITE);
#else
		f = open(filename, O_CREAT|O_APPEND|O_RDWR, S_IREAD|S_IWRITE);
#endif
	}

	if (f == -1) {
		writelog(LOG_ERROR, "Can't write data to file %s : %s",filename,strerror( errno ));
		return false;
	}

	writelog(LOG_MESSAGE,"Saving surf %s to file %s (Surfer7 GRD)", srf->getName(), filename);

	NN = srf->getCountX();
	MM = srf->getCountY();

	if ((NN > LONG_MAX) || (MM > LONG_MAX) || (NN*MM > LONG_MAX))
	{
		writelog(LOG_ERROR,"Surface %s is too large for saving in Surfer GRD binary format!");
		goto exit;
	}

	if ( write(f, "DSRB", sizeof(char)*strlen("DSRB")) != strlen("DSRB")*sizeof(char))
		goto exit;
	size = 4;
	if ( write(f, &size, sizeof(long)) != sizeof(long) )
		goto exit;
	if ( write(f, &version, sizeof(long)) != sizeof(long) )
		goto exit;

	// writing grid section
	id = 0x44495247;
	size = 72;
	if ( write(f, &id, sizeof(long)) != sizeof(long) )
		goto exit;
	if ( write(f, &size, sizeof(long)) != sizeof(long) )
		goto exit;

	nx = (long)NN;
	ny = (long)MM;
	minx = (double)srf->grd->startX;
	miny = (double)srf->grd->startY;
	stepX = (double)srf->grd->stepX;
	stepY = (double)srf->grd->stepY;
	srf->getMinMaxZ(minZ, maxZ);
	minz = minZ;
	maxz = maxZ;

	if ( write(f, &ny, sizeof(long)) != sizeof(long) )
		goto exit;

	if ( write(f, &nx, sizeof(long)) != sizeof(long) )
		goto exit;

	if ( write(f, &minx, sizeof(double)) != sizeof(double) )
		goto exit;

	if ( write(f, &miny, sizeof(double)) != sizeof(double) )
		goto exit;

	if ( write(f, &stepX, sizeof(double)) != sizeof(double) )
		goto exit;

	if ( write(f, &stepY, sizeof(double)) != sizeof(double) )
		goto exit;

	if ( write(f, &minz, sizeof(double)) != sizeof(double) )
		goto exit;

	if ( write(f, &maxz, sizeof(double)) != sizeof(double) )
		goto exit;

	if ( write(f, &rotation, sizeof(double)) != sizeof(double) )
		goto exit;

	if ( write(f, &blank, sizeof(double)) != sizeof(double) )
		goto exit;

	// writing data section
	id = 0x41544144;
	size = NN*MM*sizeof(double);
	if ( write(f, &id, sizeof(long)) != sizeof(long) )
		goto exit;
	if ( write(f, &size, sizeof(long)) != sizeof(long) )
		goto exit;

	if (srf->coeff->write_file(f, NN*MM) != NN*MM*sizeof(double))
		goto exit;

	close(f);

	return true;

exit:

	close(f);
	return false;
};

};

