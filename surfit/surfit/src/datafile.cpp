
/*------------------------------------------------------------------------------
 *	$Id$
 *
 *	Copyright (c) 2002-2004 by M. V. Dmitrievsky and V. N. Kutrunov
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

#include "ie.h"
#include "datafile.h"
#include "variables_tcl.h"
#include "variables_internal.h"
#include "fileio.h"
#include <stdarg.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>

#ifdef HAVE_UNISTD_H
#include <unistd.h>
#endif

#include <float.h>

#include <tcl.h>

#ifdef HAVE_STRING_H
#include <string.h>
#endif

#if defined(_WIN32) || defined(__WIN32__) || defined(WIN32)
#include <io.h>
#endif


namespace surfit {

datafile::datafile(const char * filename, int imode, int iomode) {

	zero = '\0';

	file = -1;
	File = NULL;

	mode = iomode;

	datafile_filename = strdup(filename);

	extern int datafile_mode;

	// write mode
	if (imode == DF_MODE_WRITE) {

		// binary mode
		if (mode == DF_IOMODE_BINARY) {
			
			if (datafile_mode == 0) {
#if defined(_WIN32) || defined(__WIN32__) || defined(WIN32)
				file = open(filename, O_BINARY|O_RDWR);
#else
				file = open(filename, O_RDWR);
#endif
			}

			if (datafile_mode == 1) {
#if defined(_WIN32) || defined(__WIN32__) || defined(WIN32)
				file = open(filename, O_BINARY|O_RDWR|O_TRUNC|O_APPEND);
#else
				file = open(filename, O_RDWR|O_TRUNC|O_APPEND);
#endif
			}
			
			if (file == -1) {
#if defined(_WIN32) || defined(__WIN32__) || defined(WIN32)
				file = open(filename, O_BINARY|O_CREAT|O_APPEND|O_RDWR, S_IREAD|S_IWRITE);
#else
				file = open(filename, O_CREAT|O_APPEND|O_RDWR, S_IREAD|S_IWRITE);
#endif
			}
			
			if (file == -1) 
				writelog(SURFIT_ERROR, "The file %s was not opened: %s",filename,strerror( errno ));
		} 

		// text mode
		if (mode == DF_IOMODE_TEXT) {

			if (datafile_mode == 0)
				File = fopen(filename, "r+");
			if (datafile_mode == 1)
				File = fopen(filename, "w");

			if (!File)
				if (datafile_mode == 0)
					File = fopen(filename, "a+");

			if (!File) 
				writelog(SURFIT_ERROR, "The file %s was not opened: %s",filename,strerror( errno ));
			
		} 

		if (!checkHeader(filename)) {
			writelog(SURFIT_ERROR, "Can't write data to file %s",filename,strerror( errno ));
			if (file != -1) {
				close(file);
				file = -1;
			}
			if (File) {
				fclose(File);
				File = NULL;
			}
		};
		
	};

	// read mode
	if (imode == DF_MODE_READ) {
		if (mode == DF_IOMODE_BINARY) {
#if defined(_WIN32) || defined(__WIN32__) || defined(WIN32)
			file = open(filename, O_BINARY);
#else
            file = open(filename, O_RDONLY);
#endif
			if (file == -1) {
				writelog(SURFIT_ERROR, "The file %s was not opened: %s",filename,strerror( errno ));
				return;
			}
		}
		
		if (mode == DF_IOMODE_TEXT) {
			File = fopen(filename, "r");
			if (File == NULL) {
				writelog(SURFIT_ERROR, "The file %s was not opened: %s",filename,strerror( errno ));
				return;
			}
		}

		
		skipHeader(filename);
	};

};

datafile::~datafile() {
	if (file != -1)
		close(file);
	if (File)
		fclose(File);
	free(datafile_filename);
};

bool datafile::condition() const {
	if (mode == 0)
		return (file != -1);
	return (File != NULL);
};

const char * datafile::getWord() const {
	return word;
};

bool datafile::isWord(const char * testword) const {
	return ( strcmp( word, testword ) == 0 );
};

bool datafile::byteswaptest() {

	// byteswaptest
	if ( findTag("filedata") ) {
		
		int one;
		skipTagName();

		if ( !readWord() ) return false;
		
		while ( !isWord("endtag") ) {
			
			if ( isWord("int") ) {
				// read name
				if ( !readWord() ) 
					return false;
				if ( isWord("byteswaptest") ) {
					readInt(one);
					if (one != 1) return false;
					return true;
				}
				skipInt();
				if ( !readWord() ) return false;
				continue;
			}
			skip(false);
			if ( !readWord() ) return false;
			continue;
		}
		return false;
	}
	return false;
};

//////////////
//
// NAVIGATION
//
//////////////

void datafile::skipHeader(const char * filename) {
	bool res = true;
	bool op;
	op = readWord(); res = ( op && res );
	if ( (mode == 0) && !(isWord("roff-bin")) ) {
		writelog(SURFIT_ERROR,"%s is not valid binary data file", filename);
		close(file);
		file = -1;
		return;
	}

	if ( (mode == 1) && !(isWord("roff-asc")) ) {
		writelog(SURFIT_ERROR,"%s is not valid text data file", filename);
		fclose(File);
		File = NULL;
		return;
	}
	
	switch (mode) {
	case 0: 
		{
			op = readWord(); res = ( op && res );
			op = readWord(); res = ( op && res );
			if (!res) {
				writelog(SURFIT_ERROR,"%s is not valid binary file", filename);
				close(file);
				file = -1;
				return;
			}
			
			long file_pos = lseek(file, 0, SEEK_CUR);
			
			if (!byteswaptest()) {
				writelog(SURFIT_ERROR,"%s : byteswap test failed", filename);
				close(file);
				file = -1;
				return;
			}
			
			if (condition())
				lseek(file,file_pos, SEEK_SET);

			break;
		}
	case 1:
		{
			op = ( fscanf(File, "%[ \n]", word) == 1); res = ( op && res );
			op = ( fscanf(File, "%[ !-~]", word) == 1); res = ( op && res );
			op = ( fscanf(File, "%[ \n]", word) == 1); res = ( op && res );
			op = ( fscanf(File, "%[ !-~]", word) == 1); res = ( op && res );
						
			if (!res) {
				writelog(SURFIT_ERROR,"%s is not valid text file", filename);
				fclose(File);
				File = NULL;
				return;
			}

			break;
			
		}
	}

};

bool datafile::findTagEof() {
	char tagname[TAG_WORD_SIZE];
	char error[] = "find_tag : wrong binary datafile format";
	
	if (!readTagName(tagname)) {
		writelog(SURFIT_ERROR, error);
		return false;
	};
	
	while ( strcmp(tagname,"eof") != 0 ) {
		if (!skipTag(false)) {
			writelog(SURFIT_ERROR, error);
			return false;
		};
		
		if (!readTagName(tagname)) {
			writelog(SURFIT_ERROR, error);
			return false;
		};
		
	}
	
	if (mode == 1) {
		fpos_t pos;
		fgetpos(File, &pos);
		fflush(File);
		fsetpos(File, &pos);
	}

	return true;
};

bool datafile::findTag(const char * tag) {
	char tagname[TAG_WORD_SIZE];
	char error[] = "find_tag : wrong datafile format";
	
	if (!readTagName(tagname)) {
		writelog(SURFIT_ERROR, error);
		return false;
	};
	
	while ( strcmp(tagname,tag) != 0 ) {
		if (!skipTag(false)) {
			writelog(SURFIT_ERROR, error);
			return false;
		};
		if (strcmp(tagname,"eof") == 0) {
			return false;
		}
		
		if (!readTagName(tagname)) {
			writelog(SURFIT_ERROR, error);
			return false;
		};
		
	}
	
	return true;
};

bool datafile::skip(bool print_name, char * name) {
	if ( isWord("int") )		
					return skipInt();
	if ( isWord(REAL_NAME) )		
					return skipReal();
	if ( isWord("char") )		
					return skipChar(print_name, true, name);
	if ( isWord("array") )		
					return skipArray();
	if ( isWord("tag") ) {
		switch (mode) {
		case 0:
			{
				if ( lseek(file, lseek(file, 0, SEEK_CUR)-4,SEEK_SET) != -1L ) 
					return skipTag(print_name, name);
				return false;
			}
		case 1:
			{
				if ( ungetString("tag ") )
					return skipTag(print_name, name);
				return false;
			}
			return false;
		}
	}
	return false;
};

bool datafile::skipByte() {
	switch (mode) {
	case 0:
		{
			// skip Name
			if (!readWord()) return false;
			return skipBytes(sizeof(char));
		}
	case 1:
		{
			if (!readWord()) return false;
			if (!readWord()) return false;
			return true;
		}
	};
	return false;
};

bool datafile::skipBool() {
	switch (mode) {
	case 0:
		{
			// skip Name
			if (!readWord()) return false;
			return skipBytes(sizeof(char));
		}
	case 1:
		{
			if (!readWord()) return false;
			if (!readWord()) return false;
			return true;
		}
	};
	return false;
};

bool datafile::skipInt(bool skip_name) {
	switch (mode) {
	case 0:
		{
			if (skip_name)
				if (!readWord()) return false;
			return skipBytes(sizeof(int));
		}
	case 1:
		{
			if (skip_name)
				if (!readWord()) return false;
			if (!readWord()) return false;
			return true;
		}
	};
	return false;
};

bool datafile::skipReal(bool skip_name) {
	switch (mode) {
	case 0:
		{
			if (skip_name)
				if (!readWord()) return false;
			return skipBytes(sizeof(REAL));
		}
	case 1:
		{
			if (skip_name)
				if (!readWord()) return false;
			if (!readWord()) return false;
			return true;
		}
	};
	return false;
};

bool datafile::skipChar(bool print_name, bool skip_name, char * name) {
	switch (mode) {
	case 0:
		{
			if (skip_name)
				if (!readWord()) return false;
			if ( isWord("name") ) {
				bool res = readWord();
				if (print_name) {
					Tcl_printf("%s",word);
				}
				if (name != NULL) 
						strncpy(name, word, strlen(word)+1);
				return res;
			}
			return readWord();
		}
	case 1:
		{
			if (skip_name)
				if (!readWord()) return false;
			bool is_name = isWord("name");
			bool res = true;
			bool op = false;
			op = ( fscanf(File,"%[ \"]",word)   == 1 ); res = ( op && res );
			op = ( fscanf(File,"%[ !#-~]",word) == 1 ); res = ( op && res );
			if (is_name && print_name)
				Tcl_printf("%s",word);
			//op = ( fscanf(File,"%[ \"]",word)   == 1 ); res = ( op && res );
			return res;
		}
	};
	return false;
};

bool datafile::skipArray(bool skip_type) {
	if (skip_type)
		if (!readWord()) return false;
	
	if ( isWord("byte") )   
							return skipByteArray();
	if ( isWord("bool") )   
							return skipBoolArray();
	if ( isWord("int") )    
							return skipIntArray();
	if ( isWord(REAL_NAME) )  
							return skipRealArray();
	return false;
};

bool datafile::skipByteArray(bool skip_name) {

	if (skip_name)
		if ( !readWord() ) return false;

	switch (mode) {
	case 0:
		{
			int size = 0;
			int f = file;
			if ( read(f, &size, sizeof(int)) > 0 )
				return skipBytes(size*sizeof(char));
			return false;
		}
	case 1:
		{
			int size = 0;
			if ( !readInt(size) ) return false;
			int cnt; unsigned char fake;
			for (cnt = 0; cnt < size; cnt++)
				if ( !readByte(fake) ) return false;
			return true;
		}
	};
	return false;
};

bool datafile::skipBoolArray(bool skip_name) {
	
	if (skip_name)
		if ( !readWord() ) return false;

	switch (mode) {
	case 0:
		{
			int size = 0;
			if ( read( file, &size, sizeof(int)) > 0 )
				return skipBytes(size*sizeof(char));
			return false;
		}
	case 1:
		{
			int size = 0;
			if ( !readInt(size) ) return false;
			int cnt; bool fake;
			for (cnt = 0; cnt < size; cnt++)
				if ( !readBool(fake) ) return false;
			return true;
		}
	};
	return false;
};

bool datafile::skipIntArray(bool skip_name) {

	if (skip_name)
		if ( !readWord() ) return false;

	switch (mode) {
	case 0:
		{
			int size = 0;
			if ( read( file, &size, sizeof(int)) > 0 )
				return skipBytes(size*sizeof(int));
			return false;
		}
	case 1:
		{
			int size = 0;
			if ( !readInt(size) ) return false;
			int cnt; int fake;
			for (cnt = 0; cnt < size; cnt++)
				if ( !readInt(fake) ) return false;
			return true;
		}
	};
	return false;
};

bool datafile::skipRealArray(bool skip_name) {

	if (skip_name) 
		if ( !readWord() ) return false;
	
	switch (mode) {
	case 0:
		{
			int size = 0;
			if ( read( file, &size, sizeof(int)) > 0 ) {
				return skipBytes(size*sizeof(REAL));
			}
			return false;
		}
	case 1:
		{
			int size = 0;
			if ( !readInt(size) ) return false;
			int cnt; 
			REAL fake;
			for (cnt = 0; cnt < size; cnt++) {
				if ( !readReal(fake) ) return false;
			}
			return true;
		}
	};
	return false;
};

bool datafile::skipTagName() {
	switch (mode) {
	case 0:
		{
			int file_pos = lseek(file, 0, SEEK_CUR);
			
			char t[4];
						
			unsigned int r = read( file, t, 4);
			r += read(file, word, TAG_WORD_SIZE);
			
			lseek(file, file_pos+4+strlen(word)+1, SEEK_SET);
			
			return (r > 0);
		}
	case 1:
		{
			if ( !readWord() ) return false;
			if ( !readWord() ) return false;
			return true;
		}
	}
	return false;
};

bool datafile::skipToEndTag() {
	
	if (!readWord())
		return false;

	while ( !isWord("endtag") ) {
		
		if ( !skip(false) ) return false;
		if ( !readWord() ) return false;
		
	}
	return true;
};

bool datafile::skipTag(bool print_name, char * name) {
	if (!skipTagName())
		return false;
	
	if (!readWord())
		return false;
	
	while ( !isWord("endtag") ) {
		
		if ( !skip(print_name, name) ) return false;
		if ( !readWord() ) return false;
		
	}
	return true;
};


//////////////
//
//   WRITING
//
//////////////

bool datafile::checkHeader(const char * filename) {
	bool res = true;
	bool op;
	op = readWord(); res = ( op && res );
	switch (mode) {
	case 0:
		{
			if ( ! isWord("roff-bin")  ) 
				return writeHeader();
			op = readWord(); res = ( op && res );
			op = readWord(); res = ( op && res );
		}
		break;
	case 1:	
		{
			if ( ! isWord("roff-asc")  ) 
				return writeHeader();
			op = ( fscanf(File, "%[ \n]", word) == 1); res = ( op && res );
			op = ( fscanf(File, "%[ !-~]", word) == 1); res = ( op && res );
			op = ( fscanf(File, "%[ \n]", word) == 1); res = ( op && res );
			op = ( fscanf(File, "%[ !-~]", word) == 1); res = ( op && res );
		}
	}
	
	if (!res) {
		writelog(SURFIT_ERROR,"%s is not valid binary file");
		close(file);
		file = -1;
		return false;
	}
	return findTagEof();
};

bool datafile::writeHeader() {
	bool res = true; 
	bool op = false;
	char buf[200];
	switch (mode) {
	case 0:
		{
			op = writeString("roff-bin");
			res = ( op && res );
			op = writeString("#ROFF file#"); res = ( op && res );
			sprintf(buf,"#Creator: surfit-%s#", VERSION);
			op = writeString(buf); res = ( op && res );
			break;
		}
	case 1:
		{
			op = writeString("roff-asc");
			res = ( op && res );
			op = writeTextString("#ROFF file#\n"); res = ( op && res );
			sprintf(buf,"#Creator: surfit-%s#\n", VERSION);
			op = writeTextString(buf); res = ( op && res );
			break;
		}
	}
	op = writeTag("filedata");
	op = writeInt("byteswaptest", 1);
	op = writeEndTag();
	return res;
};


bool datafile::writeTag(const char * string) {
	bool res = true;
	bool op;
	switch (mode) {
	case 0:
		{
			op = writeString("tag");		res = (op && res);
			op = writeString(string);		res = (op && res);
			return res;
		}
	case 1:
		{
			op = writeTextString("tag ");	res = (op && res);
			op = writeString(string);		res = (op && res);
			return res;
		}
	}
	return false;
};


bool datafile::writeEndTag() {
	return writeString("endtag");
};

bool datafile::writeEof() {
	bool res = true;
	bool op;
	op = writeTag("eof");			res = (op && res);
	op = writeEndTag();				res = (op && res);
	return res;
};

unsigned int datafile::writeBinaryString(const char * name) {
	unsigned int r = 0;
	r += write(file, name, strlen(name));
	r += write(file, &zero, 1);
	return r;
};

bool datafile::writeTextString(const char * string) {
	int r = fprintf(File, "%s", string);
	return (r > 0);
};

bool datafile::writeString(const char * string) {
	
	switch (mode) {
	case 0: 
		{
			unsigned int r = write(file, string, strlen(string));
			r += write(file, &zero, 1);
			return (r > 0);
		}
	case 1:
		{
			int r = fprintf(File, "%s \n",string);
			return (r > 0);
		}
	}
	return false;
};

bool datafile::writeString(const char * name, const char * string) {
	switch (mode) {
	case 0:
		{
			unsigned int r = writeBinaryString("char");
			r += writeBinaryString(name);
			r += write(file, string, strlen(string)+1);
			return ( r > 0 );
		}
	case 1:
		{
			int r = fprintf(File, "char %s %s \n",name, string);
			return ( r > 0 );
		}
	}
	return false;
};


bool datafile::writeInt(const char * name, const int & i) {
	switch (mode) {
	case 0:
		{
			unsigned int r = writeBinaryString("int");
			r += writeBinaryString(name);
			r += write(file, (void *)&i, sizeof(int));
			return ( r > 0 );
		}
	case 1:
		{
			int r = fprintf(File, "int %s %d \n", name, i);
			return ( r > 0 );
		}
	}
	return false;
};

bool datafile::writeReal(const char * name, const REAL & d) {
	switch (mode) {
	case 0:
		{
			unsigned int r = writeBinaryString(REAL_NAME);
			r += writeBinaryString(name);
			r += write(file, (void *)&d, sizeof(REAL));
			return (r > 0);
		}
	case 1:
		{
			if (d == FLT_MAX) {
				int r = fprintf(File, "double %s FLT_MAX \n", name);
				return ( r > 0 );
			} else {
				int r = fprintf(File, "double %s %.16G \n", name, d);
				return ( r > 0 );
			}
		}
	}
	return false;
};


bool datafile::writeChar(const char * name, const char * c) {
	switch (mode) {
	case 0:
		{
			unsigned int r = writeBinaryString("char");
			r += writeBinaryString(name);
			//r += write(file, (void *)c, strlen(csizeof(char));
			r += writeBinaryString(c);
			return (r > 0);
		}
	case 1:
		{
			int r = fprintf(File,"char %s \"%s\" \n", name, c);
			return ( r > 0 );
		}
	}
	return false;
};

bool datafile::writeRealArray(const char * name, const REAL * ptr, unsigned int size) {
	switch (mode) {
	case 0:
		{
			unsigned int r = writeBinaryString("array");
			r += writeBinaryString(REAL_NAME);
			r += writeBinaryString(name);
			r += write(file, (void *)&size, sizeof(int));
			r += write(file, ptr, size*sizeof(REAL));
			return (r > 0);
		}
	case 1:
		{
			bool res = true;
			bool op = false;

			int r = 0;
			r = fprintf(File,"array double %s %d \n", name, size);
			if (r == 0) return false;
			r = 0;

			unsigned int cnt = 1;
			while (cnt <= size) {
				
				if (*ptr == FLT_MAX)
					r += fprintf(File," FLT_MAX");
				else
					r += fprintf(File," %18.16G",*ptr);
				if (r == 0) return false; r = 0;

				if ( cnt % 4 == 0 )
					fprintf(File, " \n");

				ptr++; cnt++;
			};
			if ( size % 4 != 0 ) {
				fprintf(File, " \n");
			}

			return res;			
		}
	}
	return false;
};

bool datafile::writeBoolArray(const char * name, const bool * ptr, unsigned int size) {
	switch (mode) {
	case 0:
		{
			unsigned int r = writeBinaryString("array");
			r += writeBinaryString("bool");
			r += writeBinaryString(name);
			r += write(file, (void *)&size, sizeof(int));
			r += write(file, ptr, size*sizeof(bool));
			return (r > 0);
		}
	case 1:
		{
			bool res = true;
			bool op = false;

			int r = 0;
			r = fprintf(File,"array bool %s %d \n", name, size);
			if (r == 0) return false;
			r = 0;

			unsigned int cnt = 1;
			while (cnt <= size) {
				
				r += fprintf(File," %d",*ptr);
				if (r == 0) return false; r = 0;

				if ( cnt % 4 == 0 )
					fprintf(File, " \n");

				ptr++; cnt++;
			};
			if ( size % 4 != 0 ) {
				fprintf(File, " \n");
			}

			return res;			
		}
	}
	return false;
};

//////////////
//
//   READING
//
//////////////

bool datafile::ungetString(const char * string) {
	int i;
	char c;
	for (i = strlen(string)-1; i >=0 ; i--) {
		c = *(string+i);
		if (c != ungetc(c,File)) 
			return false;
	}
	return true;
};

bool datafile::readTagName(char * tagname) {
	switch (mode) {
	case 0:
		{
			int file_pos = lseek(file, 0, SEEK_CUR);
			char t[4];
			unsigned int r = read( file, t, 4);
			r += read( file, tagname, TAG_WORD_SIZE);
			lseek(file, file_pos, SEEK_SET);
			return (r > 0);
		}
	case 1:
		{
			long file_pos = ftell(File);
			if ( !readWord() ) return false;
			if ( !isWord("tag") ) return false;

			bool res = ( 1 == fscanf(File, "%s",tagname) );
			if (res) {
				ungetString(tagname);
				ungetString("tag ");
				//res = ( (fseek(File, file_pos, SEEK_SET) == 0) && res );
			}

			return res;

		}
	}
	return false;
};


bool datafile::readWord() {
	switch (mode) {
	case 0:
		{
			int file_pos = lseek(file, 0, SEEK_CUR);
			unsigned int r = read(file, word, TAG_WORD_SIZE);
			if (lseek(file, file_pos + strlen(word)+1, SEEK_SET) == -1L)
				return false;
			return (r > 0);
		}
	case 1:
		{
			return ( fscanf(File, "%s", word) == 1);
		}
	}
	return false;
};

bool datafile::skipBytes(long how_much) {
	switch (mode) {
	case 0:
		{
			int res = lseek(file, how_much, SEEK_CUR);
			return ( res != -1L );
		};
	case 1:
		{
			return ( fscanf(File, "%s", word) == 1);
		}
	};
	return false;
};

bool datafile::readBool(bool &b) {
	switch (mode) {
	case 0: 
		{
			unsigned int r = read( file, &b, sizeof(bool));
			return (r > 0);
		}
	case 1:
		{
			if (!readWord()) return false;
			b = ( 1 == atoi(word) );
			return true;
		}
	}
	return false;
};

bool datafile::readByte(unsigned char &c) {
	switch (mode) {
	case 0: 
		{
			unsigned int r = read( file, &c, sizeof(char));
			return (r > 0);
		}
	case 1:
		{
			if (!readWord()) return false;
			c = atoi(word);
			return true;
		}
	}
	return false;
};

bool datafile::readInt(int & i) {
	switch (mode) {
	case 0: 
		{
			unsigned int r = read( file, &i, sizeof(int));
			return (r > 0);
		}
	case 1:
		{
			if (!readWord()) return false;
			i = atoi(word);
			return true;
		}
	}
	return false;
};

bool datafile::readReal(REAL & d) {
	switch (mode) {
	case 0: 
		{
			unsigned int r = read( file, &d, sizeof(REAL));
			return (r > 0);
		}
	case 1:
		{
			if (!readWord()) return false;
			if ( strcmp(word,"FLT_MAX") == 0 ) 
				d = FLT_MAX;
			else
				d = REAL(atof(word));
			
			return true;
		}
	}
	return false;
};

bool datafile::readRealArray(REAL *& begin, REAL *& end) {
	switch (mode) {
	case 0: 
		{
			unsigned int r = 0;
			unsigned int size = 0;
			if (read( file,  &size, sizeof(int)) > 0) {
				
				begin = (REAL*)malloc(size * sizeof(REAL));
				if (begin == NULL) {
					writelog(SURFIT_ERROR,"Out of memory");
					return false;
				}
				
				r = read( file, begin, sizeof(REAL)*size );
				end = begin+size;
				
				if ( r == size*sizeof(REAL) )
					return true;
				else {
					free (begin);
					return false;
				}
			};
			
			return false;
		}
	case 1:
		{
			int size = 0;
			if (! readInt(size) ) return false;
			int cnt;
			
			begin = (REAL*)malloc(size * sizeof(REAL));
			if (begin == NULL) {
				writelog(SURFIT_ERROR,"Out of memory");
				return false;
			}

			REAL * ptr = begin;

			for (cnt = 0; cnt < size; cnt++) {
				if ( !readReal(*ptr) ) {
					free (begin);
					return false;
				}
				ptr++;
			}

			end = begin+size;
			return true;

		}
	}
	return false;
};

bool datafile::readBoolArray(bool *& begin, bool *& end) {
	switch (mode) {
	case 0: 
		{
			unsigned int r = 0;
			unsigned int size = 0;
			if (read( file,  &size, sizeof(int)) > 0) {
				
				begin = (bool*)malloc(size * sizeof(bool));
				if (begin == NULL) {
					writelog(SURFIT_ERROR,"Out of memory");
					return false;
				}
				
				r = read( file, begin, sizeof(bool)*size );
				end = begin+size;
				
				if ( r == size*sizeof(bool) )
					return true;
				else {
					free (begin);
					return false;
				}
			};
			
			return false;
		}
	case 1:
		{
			int size = 0;
			if (! readInt(size) ) return false;
			int cnt;
			
			begin = (bool*)malloc(size * sizeof(bool));
			if (begin == NULL) {
				writelog(SURFIT_ERROR,"Out of memory");
				return false;
			}

			bool * ptr = begin;

			for (cnt = 0; cnt < size; cnt++) {
				if ( !readBool(*ptr) ) {
					free (begin);
					return false;
				}
				ptr++;
			}

			end = begin+size;
			return true;

		}
	}
	return false;
};

void datafile::file_info() {
	char tagname[TAG_WORD_SIZE];
	if ( !readTagName(tagname) ) return;
	while ( strcmp(tagname,"eof") != 0 ) {
		Tcl_printf("%s ",tagname);
		if ( ! skipTag(true) ) return;
		Tcl_printf("\n",tagname);
		if ( !readTagName(tagname) ) return;
	}
	return;
};

void datafile::file_info_fill(char **& contents) {
	
	int count = 0;

	char * name = NULL;

	contents = NULL;
	
	char tagname[TAG_WORD_SIZE];
	if ( !readTagName(tagname) ) return;
	while ( strcmp(tagname,"eof") != 0 ) {
		
		count++;

		int alloc_size = (count*2 + 1)*sizeof(char**);
		contents = (char**)realloc(contents, alloc_size);

		if (contents) {
			*(contents+(count-1)*2)   = strdup(tagname);
			*(contents+(count-1)*2+1) = (char*)malloc(TAG_WORD_SIZE);
			**(contents+(count-1)*2+1) = '\0';
		} else {
			bool qq = false;
			contents = (char**)malloc(alloc_size);
		}
				
		Tcl_printf("%s ",tagname);
		if ( ! skipTag(true, *(contents+(count-1)*2+1)) ) return;
		Tcl_printf("\n");
	

		if ( !readTagName(tagname) ) return;
	}
	count++;
	*(contents+(count-1)*2) = NULL;

	return;
};

void file_info(const char * filename) {

	datafile *df = new datafile(filename, 1, get_rw_mode() );
	
	if (!df->condition()) {
		delete df;
		return;
	}

	df->file_info();
	delete df;
	
};

void _file_info(const char * filename, char **& contents) {
	
	datafile *df = new datafile(filename, 1, get_rw_mode() );
	
	if (!df->condition()) {
		delete df;
		return;
	}

	df->file_info_fill(contents);
	delete df;
}

// 
// Comfortable reading
//

bool datafile::isVariableType(const char * type_name, bool & read_ok) {
	read_ok = true;
	if ( isWord(type_name) ) {
		read_ok = readWord();
		return true;
	}
	return false;
};

bool datafile::ReadChar(const char * variable_name, char *& result, bool & read_ok) {
	read_ok = true;
	if ( isWord(variable_name) ) {
		if ( !readWord() ) goto exit;
		result = strdup(getWord());
		if ( !readWord() ) goto exit;
		return true;
	}
	return false;
exit:
	free(result);
	read_ok = false;
	return false;
};

bool datafile::ReadInt(const char * variable_name, int & result, bool & read_ok) {
	read_ok = true;
	if ( isWord(variable_name) ) {
		if ( !readInt(result) ) goto exit;
		if ( !readWord() ) goto exit;
		return true;
	}
	return false;
exit:
	read_ok = false;
	return false;
};

bool datafile::ReadReal(const char * variable_name, REAL & result, bool & read_ok) {
	read_ok = true;
	if ( isWord(variable_name) ) {
		if ( !readReal(result) ) goto exit;
		if ( !readWord() ) goto exit;
		return true;
	}
	return false;
exit:
	read_ok = false;
	return false;
};

bool datafile::ReadRealArray(const char * variable_name, REAL *& begin, REAL *& end, bool & read_ok) {
	read_ok = true;
	if ( isWord(variable_name) ) {
		if ( !readRealArray(begin,end) ) goto exit;
		if ( !readWord() ) goto exit;
		return true;
	}
	return false;
exit:
	read_ok = false;
	return false;
};

const char * datafile::get_filename() const {
	return datafile_filename;
};

}; // namespace surfit;

