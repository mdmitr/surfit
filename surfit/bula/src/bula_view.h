
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

#ifndef __bula__view__
#define __bula__view__

#include <stdio.h>

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Gl_Window.H>
#include <FL/gl.h>

#include <tcl.h>
#include <vector>

#include <assert.h>

using namespace std;

#define BULA_CMD_SIZE 2048

typedef struct glChannelInfo {
    char * data;
	int size;
} glChannelInfo;

static int
glCloseProc(ClientData instanceData, Tcl_Interp *interp) {
	return 0;
};

static int
glOutputProc(ClientData instanceData, CONST char * buf, int toWrite, int * errorCode)
{
    *errorCode = 0;
	if (toWrite <= 0) 
		return -1;

	if (strlen(buf) == toWrite) {
		toWrite++;
	}

	glChannelInfo * inf = (glChannelInfo*)instanceData;
	if (inf->size < toWrite) {
		free(inf->data);
		inf->data = (char *) malloc(toWrite);
		inf->size = toWrite;
	}

	if (inf->data)
		strncpy(((glChannelInfo*)instanceData)->data,buf,toWrite);
		
	return toWrite;
};

static Tcl_ChannelType glChannelType = {
    "file",											/* Type name. */
    TCL_CHANNEL_VERSION_2,							/* v2 channel */
    glCloseProc,									/* Close proc. */
    NULL,											/* Input proc. */
    (Tcl_DriverOutputProc *)glOutputProc,			/* Output proc. */
	NULL,											/* Seek proc. */
    NULL,											/* Set option proc. */
    NULL,											/* Get option proc. */
    NULL,											/* Set up the notifier to watch the channel. */
    NULL,											/* Get an OS handle from channel. */
    NULL,											/* close2proc. */
    NULL,   										/* Set blocking or non-blocking mode.*/
    NULL,											/* flush proc. */
    NULL,											/* handler proc. */
};

class bula_view : public Fl_Gl_Window {
public:
	bula_view(const char * exec, int x, int y, int w, int h, const char * text, const char * iscript_name);
	virtual ~bula_view();
	virtual void draw();

	bool shown_cmd();
	void show_cmd(bool icmd_show);
	void draw_cmd();

	bool process_cmd_key(const char * fl_text);
	bool process_key(const char * fl_text);
	void process_push_mouse();
	void process_drag_mouse();
	void process_wheel();
	void process_cmd();

private:

	char cmd[1024];
	int font_size;
	
	bool fabula;
	bool prefabula;
	char * fabula_filename;
    const char * script_name;

	int mouse_x, mouse_y;
	
	bool cmd_show;
	char command[BULA_CMD_SIZE];
	int cursor_pos;

	vector<char*> res_history;
	vector<char*> cmd_history;
	unsigned int cmd_history_pos;

	Tcl_Interp  *interp;
	Tcl_Channel gl_output;

	void add_to_cmd_history(const char * command);
	void add_to_res_history(const char * command);
	void processHistoryUp();
	void processHistoryDown();
	bool processFabula();
	//bool preprocessFabula(char * filename = NULL);

};

#endif

