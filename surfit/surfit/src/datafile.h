
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

#ifndef __surfit__datafile__
#define __surfit__datafile__

#include <stdio.h>
#include "real.h"

namespace surfit {

#define BUFFER 2048
#define TAG_WORD_SIZE 512

#define DF_MODE_WRITE      0
#define DF_MODE_READ       1
#define DF_IOMODE_BINARY   0
#define DF_IOMODE_TEXT     1

/*! \class datafile
    \brief supports surfit binary and text file formats

    This format is based on RMS open file format (ROFF), but little extended.
    surfit support text and binary roff files.
*/
class SURFIT_EXPORT datafile {
public:
	/*! constructor
	\param filename filename for input/output
	\param mode (write = 0, read = 1)
	\param iomode (binary = 0, text = 1)
	*/
	datafile(const char * filename, int mode, int iomode);

	//! destructor
	~datafile();

	/*!	writes tag with name "string"
		\param string tag name
	*/
	bool writeTag(const char * string);

	//!	writes "endtag" 
	bool writeEndTag();
	//!	writes "tag eof endtag" 
	bool writeEof();
		
	//! writes named string
	bool writeString(const char * name, const char * string);
	
	/*! writes int value 
	    \param name variable name
	    \param i variable value
	*/
	bool writeInt(const char * name, const int & i);
	
	/*! writes real (float, double, long double) value 
	    \param name variable name
	    \param d variable value
	*/
	bool writeReal(const char * name, const REAL & d);
	
	/*! writes char value
	    \param name variable name
	    \param c variable value
	*/
	bool writeChar(const char * name, const char * c);
	
	/*! writes array of REAL
	    \param name array name
	    \param ptr pointer to begining of the array
	    \param size amount of array's elements
	*/
	bool writeRealArray(const char * name, const REAL * ptr, unsigned int size);
	
	/*! writes array of bool
	    \param name array name
	    \param ptr pointer to begining of the array
	    \param size amount of array's elements
	*/
	bool writeBoolArray(const char * name, const bool * ptr, unsigned int size);
	
	//! reads word
	bool readWord();
	
	//! reads bool value
	bool readBool(bool & b);

	//! reads byte value
	bool readByte(unsigned char & c);
	
	//! reads int value
	bool readInt(int & i);
	
	//! reads REAL value
	bool readReal(REAL & d);

	/*! reads array of REAL
	    \param begin pointer to begining of the array
	    \param end pointer to end of the array
	*/
	bool readRealArray(REAL *& begin, REAL *& end);

	/*! reads array of bool
	    \param begin pointer to begining of the array
	    \param end pointer to end of the array
	*/
	bool readBoolArray(bool *& begin, bool *& end);
	
	/*! checks usability of datafile */
	bool condition() const;

	//! finds begin of tag named "tagname"
	bool findTag(const char * tagname);

	//! finds begin of tag named "eof"
	bool findTagEof();

	//! skips tag name
	bool skipTagName();

	//! compares testword with word in buffer
	bool isWord(const char * testword) const;
	
	//! skips one element
	bool skip(bool print_name, char * name = NULL);

	//! skips until "endtag"
	bool skipToEndTag();
	
	//! skips byte value
	bool skipByte();

	//! skips bool value
	bool skipBool();

	//! skips int value
	bool skipInt(bool skip_name = true);

	//! skips REAL value
	bool skipReal(bool skip_name = true);

	//! skips string value
	bool skipChar(bool print_name = false, bool skip_name = true, char * name = NULL);

	//! skips array
	bool skipArray(bool skip_type = true);

	//! skips array of bytes
	bool skipByteArray(bool skip_name = true);
	
	//! skips array of bool
	bool skipBoolArray(bool skip_name = true);
	
	//! skips array of int
	bool skipIntArray(bool skip_name = true);
	
	//! skips array of real
	bool skipRealArray(bool skip_name = true);
			
	//! reads next tag
	const char * readNextTag();

	//! returns word in buffer
	const char * getWord() const;

	//! prints tags info
	void file_info();
	//! prints tags info and writes them into contents
	void file_info_fill(char **& contents);

	//
	// comfortable reading section
	//

	//! checks for type of name type
	bool isVariableType(const char * type_name, bool & read_ok);
	
	//! reads char variable with name variable_name
	bool ReadChar(const char * variable_name, char *& result, bool & read_ok);

	//! reads int variable with name variable_name
	bool ReadInt(const char * variable_name, int & result, bool & read_ok);
	
	//! reads real variable with name variable_name
	bool ReadReal(const char * variable_name, REAL & result, bool & read_ok);
	
	//! reads real array with name variable_name
	bool ReadRealArray(const char * variable_name, REAL *& begin, REAL *& end, bool & read_ok);

public:

	//
	// internal writing
	//

	//! (internal) writes string as binary
	unsigned int writeBinaryString(const char * string);
	//! (internal) writes string
	bool writeString(const char * string);
	//! (internal) writes string as text
	bool writeTextString(const char * string);
	//! (internal) writes roff-header
	bool writeHeader();
	//! (internal) checks for roff-header
	bool checkHeader(const char * filename);
	
	//
	// internal reading
	//
	
	//! reads tag name
	bool readTagName(char * string);
	//! performs byteswap test
	bool byteswaptest();
	//! unreading operation
	bool ungetString(const char * string);

	//! skips some bytes
	bool skipBytes(long how_much);
	//! skips header
	void skipHeader(const char * filename);
	//! skips tag
	bool skipTag(bool print_name, char * name = NULL);
	
	//! file handler	
	int file;
	//! another file handler (other format)
	FILE * File;
	//! returns filename
	const char * get_filename() const;
	//! buffer for reading words
	char word[TAG_WORD_SIZE]; 
	//! datafile_mode
	int mode;

	//! word "\0"
	char zero;

	//! name of ROFF file
	char * datafile_filename;

};

}; // namespace surfit;

#endif

