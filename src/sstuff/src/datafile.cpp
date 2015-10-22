
/*------------------------------------------------------------------------------
 *	$Id$
 *
 *	Copyright (c) 2002-2006 by M. V. Dmitrievsky and V. N. Kutrunov
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

#include "sstuff_ie.h"
#include "datafile.h"
#include "fileio.h"
#include "vec.h"
#include "boolvec.h"
#include "shortvec.h"
#include "bitvec.h"
#include "intvec.h"
#include "strvec.h"

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

#ifdef HAVE_STRING_H
#include <string.h>
#endif

#if defined(_WIN32) || defined(__WIN32__) || defined(WIN32)
#include <io.h>
#endif

namespace surfit {

int datafile_modE = 1; // 1 - create new file, 0 - create or append if file already exists

void add_word(char * contents, const char * word) {
	int old_len = strlen(contents);
	strncpy(contents + old_len, word, strlen(word) );
	*( contents + old_len + strlen(word) ) = '\0';
};

void add_new_line(char * contents) {
	int old_len = strlen(contents);
	*(contents+old_len) = '\n';
	*(contents+old_len+1) = '\0';
};

datafile::datafile(const char * filename, int imode) {

	zero = '\0';

	file = -1;
	File = NULL;

	datafile_filename = strdup(filename);

	extern int datafile_modE;

	// write mode
	if (imode == DF_MODE_WRITE) {

		if (datafile_modE == 0) {
#if defined(_WIN32) || defined(__WIN32__) || defined(WIN32)
			file = open(filename, O_BINARY|O_RDWR);
#else
			file = open(filename, O_RDWR);
#endif
		}

		if (datafile_modE == 1) {
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
			writelog(LOG_ERROR, "The file %s was not opened: %s",filename,strerror( errno ));


		if (!checkHeader(filename)) {
			writelog(LOG_ERROR, "Can't write data to file %s",filename,strerror( errno ));
			if (file != -1) {
				close(file);
				file = -1;
			}
			if (File) {
				fclose(File);
				File = NULL;
			}
		};

	} 

	// read mode
	if (imode == DF_MODE_READ) {

#if defined(_WIN32) || defined(__WIN32__) || defined(WIN32)
		file = open(filename, O_BINARY);
#else
		file = open(filename, O_RDONLY);
#endif
		if (file == -1) {
			writelog(LOG_ERROR, "The file %s was not opened: %s",filename,strerror( errno ));
			return;
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
	return (file != -1);
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
	if ( !(isWord("roff-bin")) ) {
		writelog(LOG_ERROR,"%s is not valid binary data file", filename);
		close(file);
		file = -1;
		return;
	}
	
	{
		op = readWord(); res = ( op && res );
		op = readWord(); res = ( op && res );
		if (!res) {
			writelog(LOG_ERROR,"%s is not valid binary file", filename);
			close(file);
			file = -1;
			return;
		}
		
#ifdef XXL
		__int64 file_pos = _lseeki64(file, 0, SEEK_CUR);
#else
		long file_pos = lseek(file, 0, SEEK_CUR);
#endif
		
		if (!byteswaptest()) {
			writelog(LOG_ERROR,"%s : byteswap test failed", filename);
			close(file);
			file = -1;
			return;
		}
		
		if (condition())
#ifdef XXL
			_lseeki64(file,file_pos, SEEK_SET);
#else
			lseek(file,file_pos, SEEK_SET);
#endif
		
	}
};

bool datafile::findTagEof() {
	char tagname[TAG_WORD_SIZE];
	char error[] = "find_tag : wrong binary datafile format";
	
	if (!readTagName(tagname)) {
		writelog(LOG_ERROR, error);
		return false;
	};
	
	while ( strcmp(tagname,"eof") != 0 ) {
		if (!skipTag(false,NULL,false)) {
			writelog(LOG_ERROR, error);
			return false;
		};
		
		if (!readTagName(tagname)) {
			writelog(LOG_ERROR, error);
			return false;
		};
		
	}

	return true;
};

bool datafile::findTag(const char * tag, const char * tag2) {
	char tagname[TAG_WORD_SIZE];
	char error[] = "find_tag : wrong datafile format";
	
	if (!readTagName(tagname)) {
		writelog(LOG_ERROR, error);
		return false;
	};
	
	while ( strcmp(tagname,tag) != 0 ) {

		if (tag2 != NULL) {
			if (strcmp(tagname, tag2) == 0)
				break;
		}

		if (!skipTag(false)) {
			writelog(LOG_ERROR, error);
			return false;
		};
		if (strcmp(tagname,"eof") == 0) {
			return false;
		}
		
		if (!readTagName(tagname)) {
			writelog(LOG_ERROR, error);
			return false;
		};
		
	}
	
	return true;
};

bool datafile::skip(bool print_name, char * name, bool print_name_inside_tag) {
	if ( isWord("int") )		
					return skipInt();
	if ( isWord("short") )		
					return skipShort();
	if ( isWord(REAL_NAME) )		
					return skipReal();
	if ( isWord("char") )		
					return skipChar(print_name, true, name);
	if ( isWord("array") )		
					return skipArray();
	if ( isWord("tag") ) {
		
#ifdef XXL
		if ( _lseeki64(file, _lseeki64(file, 0, SEEK_CUR)-4,SEEK_SET) != -1L ) 
#else
		if ( lseek(file, lseek(file, 0, SEEK_CUR)-4,SEEK_SET) != -1L ) 
#endif
			return skipTag(print_name_inside_tag, name, print_name_inside_tag);
		return false;
		
	}
	return false;
};

bool datafile::skipByte() {
	// skip Name
	if (!readWord()) return false;
	return skipBytes(sizeof(char));
};

bool datafile::skipBool() {
	// skip Name
	if (!readWord()) return false;
	return skipBytes(sizeof(char));
};

bool datafile::skipInt(bool skip_name) {
	if (skip_name)
		if (!readWord()) 
			return false;
		
	return skipBytes(sizeof(int));
};

bool datafile::skipShort(bool skip_name) {
	if (skip_name)
		if (!readWord()) 
			return false;

	return skipBytes(sizeof(short));
};

bool datafile::skipReal(bool skip_name) {
	if (skip_name)
		if (!readWord()) 
			return false;
		
	return skipBytes(sizeof(REAL));
};

bool datafile::skipChar(bool print_name, bool skip_name, char * name) {
	if (skip_name)
		if (!readWord()) 
			return false;
		
	if ( isWord("name") ) {
		bool res = readWord();
		if (print_name) {
			log_printf("%s",word);
		}
		if ((name != NULL) && (print_name)) {
			add_word(name, " ");
			add_word(name, word);
		}
		return res;
	}
	return readWord();
};

bool datafile::skipArray(bool skip_type) {
	if (skip_type)
		if (!readWord()) return false;
	
	if ( isWord("byte") )   
							return skipByteArray();
	if ( isWord("bool") )   
							return skipBoolArray();
	if ( isWord("bit") )   
							return skipBitArray();
	if ( isWord("int") )    
							return skipIntArray();
	if ( isWord("short") )    
							return skipShortArray();
	if ( isWord(REAL_NAME) )  
							return skipRealArray();
	if ( isWord("string") )
							return skipStringArray();
	return false;
};

bool datafile::skipByteArray(bool skip_name) {
	if (skip_name)
		if ( !readWord() ) return false;
		
	surfit_int32 size = 0;
	int f = file;
	if ( read(f, &size, sizeof(surfit_int32)) > 0 )
		return skipBytes(size*sizeof(char));
	return false;
};

bool datafile::skipBoolArray(bool skip_name) {
	
	if (skip_name)
		if ( !readWord() ) 
			return false;

	surfit_int32 size = 0;
	if ( read( file, &size, sizeof(surfit_int32)) > 0 )
		return skipBytes(size*sizeof(char));
	return false;
};

bool datafile::skipBitArray(bool skip_name) {
	
	if (skip_name)
		if ( !readWord() ) return false;

	surfit_int32 size = 0;
	if ( read( file, &size, sizeof(surfit_int32)) > 0 )
		return skipBytes(size*sizeof(char));
	return false;
};

bool datafile::skipIntArray(bool skip_name) {

	if (skip_name)
		if ( !readWord() ) 
			return false;

	surfit_int32 size = 0;
	if ( read( file, &size, sizeof(surfit_int32)) > 0 )
		return skipBytes(size*sizeof(int));
		
	return false;
};

bool datafile::skipShortArray(bool skip_name) {

	if (skip_name)
		if ( !readWord() ) 
			return false;

	surfit_int32 size = 0;
	if ( read( file, &size, sizeof(surfit_int32)) > 0 )
		return skipBytes(size*sizeof(short));
	return false;
};

bool datafile::skipStringArray(bool skip_name) {

	if (skip_name) 
		if ( !readWord() ) return false;
	
	surfit_int32 size = 0;
	if ( read( file, &size, sizeof(surfit_int32)) > 0 ) {
		size_t i;
		for (i = 0; i < size; i++)
			if (!readWord())
				return false;
	}
	return false;
};

bool datafile::skipRealArray(bool skip_name) {

	if (skip_name) 
		if ( !readWord() ) return false;
	
	surfit_int32 size = 0;
	if ( read( file, &size, sizeof(surfit_int32)) > 0 ) {
		return skipBytes(size*sizeof(REAL));
	}
	return false;
};

bool datafile::skipTagName() {
#ifdef XXL
	__int64 file_pos = _lseeki64(file, 0, SEEK_CUR);
#else
	long file_pos = lseek(file, 0, SEEK_CUR);
#endif
	
	char t[4];
	
	size_t r = read( file, t, 4);
	r += read(file, word, TAG_WORD_SIZE);
	
#ifdef XXL
	_lseeki64(file, file_pos+4+strlen(word)+1, SEEK_SET);
#else
	lseek(file, file_pos+4+strlen(word)+1, SEEK_SET);
#endif
	
	return (r > 0);
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

bool datafile::skipTag(bool print_name, char * name, bool print_name_inside_tag) {
	if (!skipTagName())
		return false;
	
	if (!readWord())
		return false;
	
	while ( !isWord("endtag") ) {
		
		if ( !skip(print_name, name, print_name_inside_tag) ) return false;
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
	if ( ! isWord("roff-bin")  ) 
		return writeHeader();
	op = readWord(); res = ( op && res );
	op = readWord(); res = ( op && res );
	
	if (!res) {
		writelog(LOG_ERROR,"%s is not valid binary file");
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
	op = writeString("roff-bin");
	res = ( op && res );
	op = writeString("#ROFF file#"); res = ( op && res );
	sprintf(buf,"#Creator: surfit-%s#", VERSION);
	op = writeString(buf); res = ( op && res );
	op = writeTag("filedata");
	op = writeInt("byteswaptest", 1);
	op = writeEndTag();
	return res;
};

bool datafile::writeTag(const char * string) {
	bool res = true;
	bool op;
	op = writeString("tag");		res = (op && res);
	op = writeString(string);		res = (op && res);
	return res;
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

size_t datafile::writeBinaryString(const char * name) {
	size_t r = 0;
	r += write(file, name, strlen(name));
	r += write(file, &zero, 1);
	return r;
};

bool datafile::writeTextString(const char * string) {
	int r = fprintf(File, "%s", string);
	return (r > 0);
};

bool datafile::writeString(const char * string) {
	size_t r = write(file, string, strlen(string));
	r += write(file, &zero, 1);
	return (r > 0);
};

bool datafile::writeString(const char * name, const char * string) {
	size_t r = writeBinaryString("char");
	r += writeBinaryString(name);
	r += write(file, string, strlen(string)+1);
	return ( r > 0 );
};

bool datafile::writeInt(const char * name, const int & i) {
	size_t r = writeBinaryString("int");
	r += writeBinaryString(name);
	r += write(file, (void *)&i, sizeof(int));
	return ( r > 0 );
};

bool datafile::writeShort(const char * name, const short & i) {
	size_t r = writeBinaryString("short");
	r += writeBinaryString(name);
	r += write(file, (void *)&i, sizeof(short));
	return ( r > 0 );
};

bool datafile::writeReal(const char * name, const REAL & d) {
	size_t r = writeBinaryString(REAL_NAME);
	r += writeBinaryString(name);
	r += write(file, (void *)&d, sizeof(REAL));
	return (r > 0);
};

bool datafile::writeChar(const char * name, const char * c) {
	size_t r = writeBinaryString("char");
	r += writeBinaryString(name);
	//r += write(file, (void *)c, strlen(csizeof(char));
	r += writeBinaryString(c);
	return (r > 0);
};

bool datafile::writeStringArray(const char * name, const strvec * data) {
	surfit_int32 size =(surfit_int32) data->size();
	size_t r = writeBinaryString("array");
	r += writeBinaryString("string");
	r += writeBinaryString(name);
	r += write(file, (void *)&size, sizeof(surfit_int32));
	size_t i;
	for (i = 0; i < data->size(); i++)
		r += writeBinaryString( (*data)(i) );
	return (r > 0);
};

bool datafile::writeRealArray(const char * name, const vec * data) {
	surfit_int32 size = (surfit_int32)data->size();
	size_t r = writeBinaryString("array");
	r += writeBinaryString(REAL_NAME);
	r += writeBinaryString(name);
	r += write(file, (void *)&size, sizeof(surfit_int32));
	r += data->write_file(file, size);
	//r += write(file, data->begin(), size*sizeof(REAL));
	return (r > 0);
};

#ifdef XXL
bool datafile::writeRealArray(const char * name, const extvec * data) {
	surfit_int32 size = (surfit_int32)data->size();
	size_t r = writeBinaryString("array");
	r += writeBinaryString(REAL_NAME);
	r += writeBinaryString(name);
	r += write(file, (void *)&size, sizeof(surfit_int32));
	r += data->write_file(file, size);
	//r += write(file, data->begin(), size*sizeof(REAL));
	return (r > 0);
};
#endif

bool datafile::writeBoolArray(const char * name, const boolvec * data) {
	size_t r = writeBinaryString("array");
	surfit_int32 size = (surfit_int32)data->size();
	r += writeBinaryString("bool");
	r += writeBinaryString(name);
	r += write(file, (void *)&size, sizeof(surfit_int32));
	r += write(file, data->begin(), size*sizeof(bool));
	return (r > 0);
};

bool datafile::writeBitArray(const char * name, const bitvec * data) {
	size_t r = writeBinaryString("array");
	surfit_int32 int_size =(surfit_int32)( data->int_size() + 1 );
	surfit_int32 size = (surfit_int32)data->size();
	r += writeBinaryString("bit");
	r += writeBinaryString(name);
	r += write(file, &size, sizeof(surfit_int32));
	r += write(file, (void *)&int_size, sizeof(surfit_int32));
	r += data->write_file(file);
	//r += write(file, data->const_begin(), (int_size)*sizeof(surfit_int32));
	return (r > 0);
};

bool datafile::writeShortArray(const char * name, const shortvec * data) {
	size_t r = writeBinaryString("array");
	surfit_int32 size = (surfit_int32)data->size();
	r += writeBinaryString("short");
	r += writeBinaryString(name);
	r += write(file, (void *)&size, sizeof(surfit_int32));
	r += data->write_file(file, size);
	//r += write(file, data->begin(), size*sizeof(short));
	return (r > 0);
};

bool datafile::writeIntArray(const char * name, const intvec * data) {
	size_t r = writeBinaryString("array");
	surfit_int32 size = (surfit_int32)data->size();
	r += writeBinaryString("int");
	r += writeBinaryString(name);
	r += write(file, (void *)&size, sizeof(surfit_int32));
	r += write(file, data->begin(), size*sizeof(int));
	return (r > 0);
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
#ifdef XXL
	__int64 file_pos = _lseeki64(file, 0, SEEK_CUR);
#else
	long file_pos = lseek(file, 0, SEEK_CUR);
#endif
	char t[4];
	size_t r = read( file, t, 4);
	r += read( file, tagname, TAG_WORD_SIZE);
#ifdef XXL
	_lseeki64(file, file_pos, SEEK_SET);
#else
	lseek(file, file_pos, SEEK_SET);
#endif
	return (r > 0);
};

bool datafile::readWord() {
#ifdef XXL
	__int64 file_pos = _lseeki64(file, 0, SEEK_CUR);
	size_t r = read(file, word, TAG_WORD_SIZE);
	if (_lseeki64(file, file_pos + strlen(word)+1, SEEK_SET) == -1L)
		return false;
	return (r > 0);
#else
	long file_pos = lseek(file, 0, SEEK_CUR);
	size_t r = read(file, word, TAG_WORD_SIZE);
	if (lseek(file, file_pos + strlen(word)+1, SEEK_SET) == -1L)
		return false;
	return (r > 0);
#endif
};

bool datafile::skipBytes(long how_much) {
#ifdef XXL
	__int64 res = _lseeki64(file, how_much, SEEK_CUR);
#else
	long res = lseek(file, how_much, SEEK_CUR);
#endif
	return ( res != -1L );
};

bool datafile::readBool(bool &b) {
	size_t r = read( file, &b, sizeof(bool));
	return (r > 0);
};

bool datafile::readByte(unsigned char &c) {
	size_t r = read( file, &c, sizeof(char));
	return (r > 0);
};

bool datafile::readInt(int & i) {
	size_t r = read( file, &i, sizeof(int));
	return (r > 0);
};

bool datafile::readShort(short & i) {
	size_t r = read( file, &i, sizeof(short));
	return (r > 0);
};

bool datafile::readReal(REAL & d) {
	size_t r = read( file, &d, sizeof(REAL));
	return (r > 0);
};

bool datafile::readStringArray(strvec *& data) {
	size_t r = 0;
	surfit_int32 size = 0;
	if (read( file, &size, sizeof(surfit_int32)) > 0) {
		
		data = create_strvec(size);
		if (data == NULL) {
			writelog(LOG_ERROR,"Out of memory");
			return false;
		}
		
		size_t i;
		for (i = 0; i < (size_t)size; i++) {
			if (readWord() == false)
				return false;
			(*data)(i) = strdup(word);
		}
		return true;
	};
	
	return false;
};

bool datafile::readRealArray(vec *& data) {
	size_t r = 0;
	surfit_int32 size = 0;
	if (read( file, &size, sizeof(surfit_int32)) > 0) {
		
		data = create_vec(size,0,0); // don't fill
		if (data == NULL) {
			writelog(LOG_ERROR,"Out of memory");
			return false;
		}
		
		r = data->read_file(file, size);
				
		if ( r == size*sizeof(REAL) )
			return true;
		else {
			data->release();
			data = NULL;
			return false;
		}
	};
	
	return false;
};

#ifdef XXL
bool datafile::readRealArray(extvec *& data) {
	size_t r = 0;
	surfit_int32 size = 0;
	if (read( file,  &size, sizeof(surfit_int32)) > 0) {
		
		data = create_extvec(size,0,0); // don't fill
		if (data == NULL) {
			writelog(LOG_ERROR,"Out of memory");
			return false;
		}
		
		r = data->read_file(file, size);
				
		if ( r == size*sizeof(REAL) )
			return true;
		else {
			data->release();
			data = NULL;
			return false;
		}
	};
	
	return false;
};
#endif

bool datafile::readBoolArray(boolvec *& data) {
	size_t r = 0;
	surfit_int32 size = 0;
	if (read( file,  &size, sizeof(surfit_int32)) > 0) {
		
		data = create_boolvec(size,0,0); // don't fill
		
		r = read( file, data->begin(), sizeof(bool)*size );
		
		if ( r == size*sizeof(bool) )
			return true;
		else {
			data->release();
			data = NULL;
			return false;
		}
	};
	
	return false;
};

bool datafile::readBitArray(bitvec *& data) {
	size_t r = 0;
	surfit_int32 size = 0;
	if (read( file,  &size, sizeof(surfit_int32)) > 0) {
		
		size_t elements = 0;
		r = read( file, &elements, sizeof(surfit_int32) );
		
		data = create_bitvec(size);
		
		r = data->read_file(file, elements);
		
		if ( r == elements*sizeof(surfit_int32) )
			return true;
		else {
			data->release();
			data = NULL;
			return false;
		}
		
	};
	
	return false;
};

bool datafile::readShortArray(shortvec *& data) {
	size_t r = 0;
	surfit_int32 size = 0;
	if (read( file, &size, sizeof(surfit_int32)) > 0) {
		
		data = create_shortvec(size,0,0); // don't fill
		
		r = data->read_file(file, size);
		//r = read( file, data->begin(), sizeof(short)*size );
		
		if ( r == size*sizeof(short) )
			return true;
		else {
			data->release();
			data = NULL;
			return false;
		}
	};
	
	return false;
};

bool datafile::readIntArray(intvec *& data) {
	size_t r = 0;
	surfit_int32 size = 0;
	if (read( file,  &size, sizeof(surfit_int32)) > 0) {
		
		data = create_intvec(size,0,0); // don't fill
		
		r = read( file, data->begin(), sizeof(int)*size );
		
		if ( r == size*sizeof(int) )
			return true;
		else {
			data->release();
			data = NULL;
			return false;
		}
	};
	
	return false;
};

void datafile::file_info(char *& contents) {
	
	int count = 0;

	char * name = NULL;

	contents = (char*)malloc( 1024*20*sizeof(char) );
	*contents = '\0';
	
	char tagname[TAG_WORD_SIZE];
	if ( !readTagName(tagname) ) return;
	while ( strcmp(tagname,"eof") != 0 ) {
		
		add_word(contents, tagname);
		log_printf("%s ",tagname);
		if ( ! skipTag(true, contents, false) ) 
			return;
		log_printf("\n");
		add_new_line(contents);
	

		if ( !readTagName(tagname) ) return;
	}

	return;
};

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

bool datafile::ReadShort(const char * variable_name, short & result, bool & read_ok) {
	read_ok = true;
	if ( isWord(variable_name) ) {
		if ( !readShort(result) ) goto exit;
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

bool datafile::ReadRealArray(const char * variable_name, vec *& data, bool & read_ok) {
	read_ok = true;
	if ( isWord(variable_name) ) {
		if ( !readRealArray(data) ) goto exit;
		if ( !readWord() ) goto exit;
		return true;
	}
	return false;
exit:
	read_ok = false;
	return false;
};

bool datafile::ReadShortArray(const char * variable_name, shortvec *& data, bool & read_ok) {
	read_ok = true;
	if ( isWord(variable_name) ) {
		if ( !readShortArray(data) ) goto exit;
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

