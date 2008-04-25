
/*------------------------------------------------------------------------------
 *	$Id: color_scale.cpp 473 2007-03-28 11:08:13Z mvd $
 *	Copyright (c) 2002-2006 by M. V. Dmitrievsky 
 *----------------------------------------------------------------------------*/

#include "surfit_ie.h"
#include "colorscale.h"
#include "fileio.h"
#include "read_txt.h"

#include <float.h>
#include <errno.h>
#include <algorithm>
#include <string.h>
#include <limits.h>

namespace surfit {

int check_color(int color) {
	color = MIN(255, color);
	color = MAX(0, color);
	return color;
}

color_scale::color_scale()
{
	r_values = NULL;
	g_values = NULL;
	b_values = NULL;
	values = NULL;
	set(0, 1, 0.1, 
	    0, 0, 0,
	    255, 255, 255);
	default_cs = false;	
};

color_scale::color_scale(double from, double to, double step,
                         int r_from, int g_from, int b_from,
                         int r_to, int g_to, int b_to) 
{
	r_values = NULL;
	g_values = NULL;
	b_values = NULL;
	values = NULL;
	set(from, to, step, 
	    r_from, g_from, b_from,
	    r_to, g_to, b_to);
	default_cs = false;	
};

color_scale::color_scale(const color_scale & cs) {
	r_values = new std::vector<int>( *(cs.get_r_values()) );
	g_values = new std::vector<int>( *(cs.get_g_values()) );
	b_values = new std::vector<int>( *(cs.get_b_values()) );
	values = new std::vector<double>( *(cs.get_values()) );
	default_cs = cs.is_default();
};

void color_scale::operator =(const color_scale & cs) {
	delete r_values;
	delete g_values;
	delete b_values;
	delete values;
	r_values = new std::vector<int>( *(cs.get_r_values()) );
	g_values = new std::vector<int>( *(cs.get_g_values()) );
	b_values = new std::vector<int>( *(cs.get_b_values()) );
	values = new std::vector<double>( *(cs.get_values()) );
	default_cs = cs.is_default();
};

const std::vector<int> * color_scale::get_r_values() const
{
	return r_values;
};

const std::vector<int> * color_scale::get_g_values() const
{
	return g_values;
};

const std::vector<int> * color_scale::get_b_values() const
{
	return b_values;
};

const std::vector<double> * color_scale::get_values() const
{
	return values;
};

color_scale::~color_scale() 
{
	delete r_values;
	delete g_values;
	delete b_values;
	delete values;
};

void color_scale::release() { 
	delete this;
};

void color_scale::set(double from, double to, double step,
                      int r_from, int g_from, int b_from,
                      int r_to, int g_to, int b_to)
{
	delete r_values;
	delete g_values;
	delete b_values;
	delete values;
	r_values = NULL;
	g_values = NULL;
	b_values = NULL;
	values = NULL;

	int size = int((to-from)/step) + 1;
	if (size <= 0)
		return;

	r_values = new std::vector<int>(size+1);
	g_values = new std::vector<int>(size+1);
	b_values = new std::vector<int>(size+1);
	values   = new std::vector<double>(size);
	
	int i;
	double r_step = (r_to-r_from)/double(size);
	double g_step = (g_to-g_from)/double(size);
	double b_step = (b_to-b_from)/double(size);
	double r_val, g_val, b_val;

	for (i = 0; i < size; i++) {
		r_val = check_color(int(r_from + i*r_step));
		g_val = check_color(int(g_from + i*g_step));
		b_val = check_color(int(b_from + i*b_step));
		(*values)[i] = from + i*step;
		(*r_values)[i] = (int)r_val;
		(*g_values)[i] = (int)g_val;
		(*b_values)[i] = (int)b_val;
	};
	(*r_values)[i] = (int)r_to;
	(*g_values)[i] = (int)g_to;
	(*b_values)[i] = (int)b_to;
	default_cs = false;
}

void color_scale::get_value(double value, int & r, int & g, int & b) const
{
	if (!values)
		return;
	int size = values->size();
	if (size == 0)
		return;
	
	std::vector<double>::const_iterator it = std::lower_bound(values->begin(), values->end(), value);
	
	if (it == values->end()) {
		r = (*r_values)[size];
		g = (*g_values)[size];
		b = (*b_values)[size];
		return;
	} else {
		size_t pos = it-values->begin();
		size_t pos2 = pos - 1;
		pos2 = pos;
		if (pos == 0)
			pos2 = 0;
		if (pos == pos2) {
			r = (*r_values)[pos];
			g = (*g_values)[pos];
			b = (*b_values)[pos];
			return;
		}
	}

	return;
	
};

void color_scale::set_value(int pos, double value, int r, int g, int b) {
	(*values)[pos] = value;
	(*r_values)[pos] = r;
	(*g_values)[pos] = g;
	(*b_values)[pos] = b;
};

void color_scale::add_value(double value, int r, int g, int b) {
	values->push_back(value);
	r_values->push_back(r);
	g_values->push_back(g);
	b_values->push_back(b);
};

int color_scale::size() const {
	if (!r_values)
		return 0;

	return r_values->size();
};

void color_scale::resize(int new_size) {
	values->resize(new_size);
	r_values->resize(new_size);
	g_values->resize(new_size);
	b_values->resize(new_size);
};

bool color_scale::get_color(int pos, int & r, int & g, int &b) const {
	if (!r_values)
		return false;

	if ((pos < 0) || (pos > (int)r_values->size()))
		return false;

	r = (*r_values)[pos];
	g = (*g_values)[pos];
	b = (*b_values)[pos];
	return true;
};

double color_scale::get_value(int pos) const {
	return (*values)[pos];
};

bool color_scale::operator==(const color_scale& cs) const
{
	if (default_cs != cs.is_default())
		return false;

	int max_cnt = size();
	if (max_cnt != cs.size())
		return false;

	int i;
	int r, g, b, r2, g2, b2;
	for (i = 0; i < max_cnt; i++) {
		double val = get_value(i);
		if (val != cs.get_value(i))
			return false;

		get_color(i, r, g, b);
		cs.get_color(i, r2, g2, b2);
		if (r != r2)
			return false;
		if (g != g2)
			return false;
		if (b != b2)
			return false;
	};

	return true;
};

bool color_scale::LoadCLR(const char * filename) 
{
	FILE * file = fopen(filename, "r");
	if (file == NULL) {
		writelog(LOG_ERROR,"The file %s was not opened: %s",filename,strerror( errno ));
		return false;
	}

	std::vector<double> new_values;
	std::vector<int> new_r_values;
	std::vector<int> new_g_values;
	std::vector<int> new_b_values;

	char buf[1024];
	if (fscanf(file, "%s", buf) == 0) 
		goto exit;

	if (strcmp("ColorMap", buf) != 0)
		goto exit;

	if (fscanf(file, "%s", buf) == 0) 
		goto exit;

	if (atoi(buf) != 1)
		goto exit;

	if (fscanf(file, "%s", buf) == 0) 
		goto exit;

	if (atoi(buf) != 1)
		goto exit;

	double value;
	int r, g, b;
	while (!feof(file)) {
		if (fscanf(file, "%s", buf) == 0) 
			break;
		value = atof(buf);
		if ((value < 0) || (value > 100))
			goto exit;

		if (fscanf(file, "%s", buf) == 0) 
			goto exit;
		r = atoi(buf);
		if ((r < 0) || (r > 255))
			goto exit;

		if (fscanf(file, "%s", buf) == 0) 
			goto exit;
		g = atoi(buf);
		if ((g < 0) || (g > 255))
			goto exit;

		if (fscanf(file, "%s", buf) == 0) 
			goto exit;
		b = atoi(buf);
		if ((b < 0) || (b > 255))
			goto exit;

		new_values.push_back(value);
		new_r_values.push_back(r);
		new_g_values.push_back(g);
		new_b_values.push_back(b);

		if (value == 100)
			break;

	};

	if (new_values.size() == 0)
		goto exit;
	if (new_values[0] != 0)
		goto exit;
	if (new_values[new_values.size()-1] != 100)
		goto exit;

	*values = new_values;
	*r_values = new_r_values;
	*g_values = new_g_values;
	*b_values = new_b_values;

	fclose(file);
	return true;

exit:

	fclose(file);
	writelog(LOG_ERROR,"Wrong file format");
	return false;
};

bool color_scale::SaveCLR(const char * filename) const 
{
	FILE * file = fopen(filename, "w");
	if (file == NULL) {
		writelog(LOG_ERROR,"The file %s was not opened: %s",filename,strerror( errno ));
		return false;
	}

	int total = size();
	double min_val = (*values)[0];
	double max_val = (*values)[total-1];
	double len = max_val-min_val;

	int q;
	double val;
	
	int written;
	written = fprintf(file, "ColorMap 1 1" );
	if (written != strlen("ColorMap 1 1"))
		goto exit;
	
	for (q = 0; q < total; q++) {
		val = (*values)[q] - min_val;
		val = val/len*100.;
		written = fprintf(file, "\n");
		written = fprintf(file, "%g %d %d %d", 
			val, (*r_values)[q], (*g_values)[q], (*b_values)[q]);
		if (written <= 0)
			goto exit;
	}

	fclose(file);
	return true;

exit:

	fclose(file);
	return false;
};

bool color_scale::LoadLVL(const char * filename)
{
	FILE * file = fopen(filename, "r");
	if (file == NULL) {
		writelog(LOG_ERROR,"The file %s was not opened: %s",filename,strerror( errno ));
		return false;
	}

	resize(0);

	char buf[1024*4];
	char seps[] = ", \t";
	char seps2[] = "\"";
	int cnt = 0;
	char * token = NULL;
	const char * pos1 = NULL;
	const char * pos2 = NULL;

	double Level;
	int Flag;
	char LineColor[512];
	char LineStyle[512];
	int LineWidth;
	char FillForeColor[512];
	char FillBackColor[512];
	char FillPattern[512];
	int FillMode;

	int fr, fg, fb;
	
	if ( fread(buf, sizeof(char), 4, file) != 4 )
		goto exit;
	buf[4] = '\0';

	if ( strcmp(buf, "LVL2") != 0 )
		goto exit;

	if ( fgets(buf, 1024*4, file) == NULL )
		goto exit;


	while (!feof(file)) {
		
		if ( fgets(buf, 1024*4, file) == NULL ) {
			if ( feof(file) )
				break;
			goto exit;
		}

		if (buf[0] == '\'')
			continue; // this is a comment

		Level = FLT_MAX;
		Flag = INT_MAX;
		LineColor[0] = '\0';
		LineStyle[0] = '\0';
		LineWidth = INT_MAX;
		FillForeColor[0] = '\0';
		FillBackColor[0] = '\0';
		FillPattern[0] = '\0';
		FillMode = INT_MAX;

		cnt = -1;
		token = strtok( buf, seps );
		while (token != NULL) {
			if (strlen(token) > 0)
				cnt++;
			if (cnt == 0)
				Level = ator(token);
			if (cnt == 1)
				Flag = atoi(token);
			if (cnt == 2) {
				pos1 = strchr(token,'"');
				if (pos1 == NULL)
					goto exit;
				pos1++;
				pos2 = strchr(pos1,'"');
				if (pos2 == NULL) {
					token = strtok(NULL, seps2);
					if (token == NULL)
						goto exit;
					if (strlen(token) == 0)
						goto exit;
					int len_pos1 = strlen(pos1);
					strncpy(LineColor, pos1, len_pos1*sizeof(char));
					LineColor[len_pos1]=' ';
					strncpy(LineColor+len_pos1+1, token, strlen(token)*sizeof(char));
					LineColor[len_pos1+1+strlen(token)]='\0';
				} else {
					strncpy(LineColor, pos1, (pos2-pos1)*sizeof(char));
					LineColor[pos2-pos1] = '\0';
				}
			}
			if (cnt == 3) {
				pos1 = strchr(token,'"');
				if (pos1 == NULL)
					goto exit;
				pos1++;
				pos2 = strchr(pos1,'"');
				if (pos2 == NULL) {
					token = strtok(NULL, seps2);
					if (token == NULL)
						goto exit;
					if (strlen(token) == 0)
						goto exit;
					int len_pos1 = strlen(pos1);
					strncpy(LineStyle, pos1, len_pos1*sizeof(char));
					LineStyle[len_pos1]=' ';
					strncpy(LineStyle+len_pos1+1, token, strlen(token)*sizeof(char));
					LineStyle[len_pos1+1+strlen(token)]='\0';
				} else {
					strncpy(LineStyle, pos1, (pos2-pos1)*sizeof(char));
					LineStyle[pos2-pos1] = '\0';
				}
			}
			if (cnt == 4)
				LineWidth = atoi(token);

			if (cnt == 5) {
				pos1 = strchr(token,'"');
				if (pos1 == NULL)
					goto exit;
				pos1++;
				pos2 = strchr(pos1,'"');
				if (pos2 == NULL) {
					token = strtok(NULL, seps2);
					if (token == NULL)
						goto exit;
					if (strlen(token) == 0)
						goto exit;
					int len_pos1 = strlen(pos1);
					strncpy(FillForeColor, pos1, len_pos1*sizeof(char));
					FillForeColor[len_pos1]=' ';
					strncpy(FillForeColor+len_pos1+1, token, strlen(token)*sizeof(char));
					FillForeColor[len_pos1+1+strlen(token)]='\0';
				} else {
					strncpy(FillForeColor, pos1, (pos2-pos1)*sizeof(char));
					FillForeColor[pos2-pos1] = '\0';
				}
			}

			if (cnt == 6) {
				pos1 = strchr(token,'"');
				if (pos1 == NULL)
					goto exit;
				pos1++;
				pos2 = strchr(pos1,'"');
				if (pos2 == NULL) {
					token = strtok(NULL, seps2);
					if (token == NULL)
						goto exit;
					if (strlen(token) == 0)
						goto exit;
					int len_pos1 = strlen(pos1);
					strncpy(FillBackColor, pos1, len_pos1*sizeof(char));
					FillBackColor[len_pos1]=' ';
					strncpy(FillBackColor+len_pos1+1, token, strlen(token)*sizeof(char));
					FillBackColor[len_pos1+1+strlen(token)]='\0';
				} else {
					strncpy(FillBackColor, pos1, (pos2-pos1)*sizeof(char));
					FillBackColor[pos2-pos1] = '\0';
				}
			}

			if (cnt == 7) {
				pos1 = strchr(token,'"');
				if (pos1 == NULL)
					goto exit;
				pos1++;
				pos2 = strchr(pos1,'"');
				if (pos2 == NULL) {
					token = strtok(NULL, seps2);
					if (token == NULL)
						goto exit;
					if (strlen(token) == 0)
						goto exit;
					int len_pos1 = strlen(pos1);
					strncpy(FillPattern, pos1, len_pos1*sizeof(char));
					FillPattern[len_pos1]=' ';
					strncpy(FillPattern+len_pos1+1, token, strlen(token)*sizeof(char));
					FillPattern[len_pos1+1+strlen(token)]='\0';
				} else {
					strncpy(FillPattern, pos1, (pos2-pos1)*sizeof(char));
					FillPattern[pos2-pos1] = '\0';
				}
			}

			if (cnt == 8)
				FillMode = atoi(token);
			
			token = strtok( NULL, seps );
		}

		if ((Level != FLT_MAX) && ( strlen(FillForeColor) != 0 ))
		{
			fr = INT_MAX;
			fg = INT_MAX;
			fb = INT_MAX;
			cnt = -1;
			token = strtok( FillForeColor, seps );
			while (token != NULL) {
				if (token[0] == 'R')
					fr = atoi(token+1);
				
				if (token[0] == 'G')
					fg = atoi(token+1);

				if (token[0] == 'B')
					fb = atoi(token+1);
				
				token = strtok( NULL, seps );
			}

			if ((fr != INT_MAX) && (fg != INT_MAX) && (fb != INT_MAX) && (Level != FLT_MAX))
				add_value(Level, fr, fg, fb);
			else
				goto exit;
		}
		
				
	}

	
	fclose(file);
	return true;

exit:

	writelog(LOG_ERROR, "Wrong file format");
	fclose(file);
	return false;

};

bool color_scale::SaveLVL(const char * filename) const
{
	FILE * file = fopen(filename, "w");
	if (file == NULL) {
		writelog(LOG_ERROR, "The file %s was not opened: %s",filename,strerror( errno ));
		return false;
	}

	int written;
	int q;

	written = fprintf(file, "LVL2\n");
	if (written != strlen("LVL2\n"))
		goto exit;

	written = fprintf(file, "'Level Flags LColor LStyle LWidth FFGColor FBGColor FPattern FMode");
	if (written <= 0)
		goto exit;

	for (q = 0; q < size(); q++) {
		written = fprintf(file, "\n");
		if (written <= 0)
			goto exit;
		written = fprintf(file, "%g 0 \"Black\" \"Solid\" 0 \"R%d G%d B%d\" \"R%d G%d B%d\" \"Solid\" 1 1 1", 
			(*values)[q], (*r_values)[q], (*g_values)[q], (*b_values)[q], (*r_values)[q], (*g_values)[q], (*b_values)[q]);
		if (written <= 0)
			goto exit;
	}

	fclose(file);
	return true;

exit:

	fclose(file);
	return false;

};

color_scale * create_color_scale(double from, double to, double step,
			         int r_from, int g_from, int b_from,
			         int r_to, int g_to, int b_to)
{
	return new color_scale(from, to, step, 
		r_from, g_from, b_from,
		r_to,	g_to,	b_to);
};

}; // namespace surfit

