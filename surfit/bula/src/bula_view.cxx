
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

#include "bula_view.h"

#include <FL/Fl_Text_Display.H>
#include <FL/Fl_File_Chooser.H>

#include <math.h>

#include <stdlib.h>

#include "init_surfit.h"
#include "ie_bula.h"

#define BULA_CMD_LINES 50

/////
/////

static inline int insertChar(char c, char *buf,
                             int cursor_pos)
{
    char post_cursor_buf[BULA_CMD_SIZE];
    int l = strlen(buf)+1;
    if (l < BULA_CMD_SIZE) {
		strcpy(post_cursor_buf,&(buf[cursor_pos]));
		buf[cursor_pos++] = c;
		strcpy(&(buf[cursor_pos]),post_cursor_buf);
	}
	return cursor_pos;
};

static inline int cursorLeft(int cursor_pos)
{
    cursor_pos--;
    if (cursor_pos < 0) cursor_pos = 0;
    return cursor_pos;
};

static inline int cursorRight(int cursor_pos, int max_length)
{
    cursor_pos++;
    if (cursor_pos > max_length) cursor_pos = max_length;
    return cursor_pos;
};

static inline int delLeft(char *buf, int cursor_pos)
{
    if (cursor_pos == 0) return cursor_pos;
    cursor_pos--;
    int l = strlen(buf);
    int i;
    for (i=cursor_pos; i<=l; i++) buf[i] = buf[i+1];
    return cursor_pos;
};

static inline int delRight(char *buf, int cursor_pos)
{
    int l = strlen(buf);
	if (l == cursor_pos) return cursor_pos;
	int i;
    for (i=cursor_pos; i<=l; i++) 
		buf[i] = buf[i+1];
    return cursor_pos;
};

static inline void drawCommandText(char * command, float x_begin, float y_begin, int cursor_pos) 
{
	int len = strlen(command)-2;	
	
	if (len == 0) {
		glRasterPos3i( GLint(x_begin), GLint(y_begin), GLint(1) );
		gl_draw("> _");
		return;
	}
	if (len == cursor_pos) {
		char text[BULA_CMD_SIZE+1];
		strncpy(text,command,len+2);
		strcpy(text+len+2,"_");
		glRasterPos3i( GLint(x_begin), GLint(y_begin), GLint(1) );
		gl_draw(text);
	} else {
		char text[BULA_CMD_SIZE+1];
		strncpy(text,command,cursor_pos+2);
		strncpy(text+cursor_pos+2,"_",1);
		strncpy(text+cursor_pos+3,command+2+cursor_pos,len+2-cursor_pos+1);
		glRasterPos3i( GLint(x_begin), GLint(y_begin), GLint(1) );
		gl_draw(text);
	}
};

//
// bula_view
//

bula_view::bula_view(const char * exec, int x, int y, int w, int h, const char * text, const char * iscript_name) 
				: Fl_Gl_Window(x,y,w,h,text) 
{

    script_name = iscript_name;

	cmd_show = false;
	cursor_pos = 0;
	strcpy(command,"> ");
	interp  = Tcl_CreateInterp();
	Tcl_FindExecutable(exec);
	Tcl_Init(interp);

	glChannelInfo *infoPtr;
	infoPtr = (glChannelInfo *) ckalloc((unsigned) sizeof(glChannelInfo));
	
	gl_output = Tcl_CreateChannel(&glChannelType, "stdoudt",
	    (ClientData) infoPtr, TCL_WRITABLE);

	Tcl_RegisterChannel(interp,gl_output);
	Tcl_SetStdChannel(gl_output,TCL_STDOUT);

	char * puts = (char*)malloc(BULA_CMD_SIZE);
	*puts = '\0';

	glChannelInfo* Dat = (glChannelInfo*)Tcl_GetChannelInstanceData(gl_output);
	Dat->data = puts;
	Dat->size = BULA_CMD_SIZE;

	fabula = false;

	// history settings
	cmd_history_pos = 0;

	fabula_filename = NULL;

	prefabula = init_surfit_libs(NULL,interp,&gl_output);

	while (!prefabula) {
#ifdef WIN32
			char * filepos = fl_dir_chooser("Pick a dir to libsurfit.dll", NULL);
#else
			char * filepos = fl_dir_chooser("Pick a dir to libsurfit.so", NULL);
#endif
			prefabula = init_surfit_libs(filepos, interp, &gl_output);
			if (!prefabula) {
				Tcl_Obj *res = Tcl_GetObjResult(interp);
				char * str_err = Tcl_GetStringFromObj(res,NULL);
				fl_alert(str_err);
				Tcl_Exit(0);
			}
	}

	int max_lines = BULA_CMD_LINES;
	int y_step = Fl_Window::h()/max_lines;
	
	gl_font(fl_font(),y_step);
    font_size = gl_height();

};

bula_view::~bula_view() 
{

	free(fabula_filename);

	vector<char*>::iterator it;
	for (it = cmd_history.begin(); it != cmd_history.end(); it++)
		delete *it;

	for (it = res_history.begin(); it != res_history.end(); it++)
		delete *it;

	Tcl_SetStdChannel(NULL,TCL_STDOUT);
	Tcl_UnregisterChannel(interp,gl_output);

    Tcl_DeleteInterp(interp);

};

bool bula_view::shown_cmd() {
	return cmd_show;
};

void bula_view::show_cmd(bool icmd_show) {
	cmd_show = icmd_show;
};

void bula_view::draw() {

	if (!valid()) {
		valid(1);
		
		char draw_cmd[100];
		sprintf(draw_cmd,"init %d %d", w(), h());
		Tcl_EvalEx(interp, draw_cmd, -1, TCL_EVAL_DIRECT);

	}

	if (!fabula) 
		fabula = processFabula();
	
	if (fabula) {
		char draw_cmd[100];
		sprintf(draw_cmd,"draw %d %d", w(), h());
		Tcl_EvalEx(interp, draw_cmd, -1, TCL_EVAL_DIRECT);
	} else {
		glClearColor(0,0,0,0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	int max_lines = BULA_CMD_LINES;
	int y_step = Fl_Window::h()/max_lines;
	
	gl_font(fl_font(),y_step);
    font_size = gl_height();
		  
	if (cmd_show)
		draw_cmd();
};

int line_count(const char * line) {
    int res = 1;
	int len = strlen(line);
    char * c = strchr(line, '\n');
    while( c != NULL ) {
		if (c-line != len-1)
			res++;
        c = strchr( c+1, '\n' );
    }
    return res;
}

int lines_count( vector<char *> & lines ) {
    int res = 0;

    vector< char* >::iterator it;
    for (it = lines.begin(); it != lines.end(); ++it)
        res += line_count(*it);

    return res;
};

void bula_view::draw_cmd() {

	int w = Fl_Window::w();
	int h = Fl_Window::h();

	int max_val = MAX(w,h);
	//w = max_val;
	//h = max_val;

	float p_x = 100.0f/w;
	float p_y = 100.0f/h;

	gl_font(fl_font(),font_size);
	int y_step = gl_height();
		y_step += int(gl_height()/5.);
	
	int max_lines = int( float(Fl_Window::h())/y_step - 2 );
	//max_lines = max_val/y_step - 2;

	float x_begin = p_x*12;
	float y_begin = 100;

	const char * temp = NULL;
	int light = 0;
	temp = Tcl_GetVar(interp,"light",0);
	if (temp)
		light = atoi(temp);

	if (light == 1)
		glDisable(GL_LIGHTING);
	
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0,100,0,100,-1,1);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	
	int red = 0;
	temp = Tcl_GetVar(interp,"bg_color_red",0);
	if (temp)
		red = atoi(temp);

	int green = 0;
	temp = Tcl_GetVar(interp,"bg_color_green",0);
	if (temp)
		green = atoi(temp);

	int blue = 0;
	temp = Tcl_GetVar(interp,"bg_color_blue",0);
	if (temp)
		blue = atoi(temp);

	glColor3f( (255-red)/255.f,
		   (255-green)/255.f,
		   (255-blue)/255.f);
	
	y_begin -= y_step*p_y;

	// history drawing
	vector<char*>::iterator text_it;
	
	vector<char*> text(cmd_history.size()+res_history.size());
	
	vector< char * >::iterator cmd_it = cmd_history.begin(), res_it = res_history.begin();
	int pos = 0;
	
	while (true) {
		
		text[pos] = *cmd_it;
		pos++;

		text[pos] = *res_it;
		pos++;
		

		res_it++;
		if (res_it == res_history.end())
			break;
		
		cmd_it++;
		if (cmd_it == cmd_history.end())
			break;
	}
    
    int lines_printed = 0;
    int ln;
    char * c;
    char * prev_c;
	
	int total_lines = lines_count(text);

	if (total_lines > max_lines) {

		text_it = text.end();
		
		y_begin -= y_step*p_y*max_lines;
		float save_y = y_begin;

		while ( true ) {

			text_it--;

			ln = line_count(*text_it);
			int shift = MIN(ln,max_lines);

			float prev_y_begin = y_begin;
			y_begin += y_step*p_y*shift;

			if (ln == 1) {
				glRasterPos3f(x_begin,y_begin,1);
				gl_draw(*text_it);
				y_begin -= y_step*p_y;
				lines_printed++;
				if (lines_printed == max_lines)
					break;
			} else {
				c = strchr(*text_it,'\n');
				prev_c = *text_it;
				int qq = lines_printed;
				while( c != NULL ) {
					if (ln > max_lines - qq) {
						ln--;
						prev_c = c + 1;
						c = strchr(c+1,'\n');
					} else {
						glRasterPos3f(x_begin,y_begin,1);
						gl_draw(prev_c, c - prev_c);
						y_begin -= y_step*p_y;
						prev_c = c + 1;
						c = strchr(c+1,'\n');
						lines_printed++;
						if (lines_printed == max_lines)
							break;
					}
				}
				if (lines_printed == max_lines)
					break;
				glRasterPos3f(x_begin,y_begin,1);
				gl_draw(prev_c);
				y_begin -= y_step*p_y;
				lines_printed++;
				if (lines_printed == max_lines)
					break;
			}

			y_begin = prev_y_begin;
			y_begin += y_step*p_y*(shift);

			if (text_it == text.begin())
				break;
			
		}

		y_begin = save_y;

	} else {

		text_it = text.begin();
		
		while ( text_it != text.end() ) {
			
			ln = line_count(*text_it);
			
			if (ln == 1) {
				glRasterPos3f(x_begin,y_begin,1);
				gl_draw(*text_it);
				y_begin -= y_step*p_y;
				++text_it;
				lines_printed++;
			} else {
				c = strchr(*text_it,'\n');
				prev_c = *text_it;
				while( c != NULL ) {
					glRasterPos3f(x_begin,y_begin,1);
					gl_draw(prev_c, c - prev_c);
					y_begin -= y_step*p_y;
					prev_c = c + 1;
					c = strchr(c+1,'\n');
				}
				glRasterPos3f(x_begin,y_begin,1);
				gl_draw(prev_c);
				y_begin -= y_step*p_y;
				++text_it;
			}
		}
		
	}
        
	drawCommandText(command,x_begin,y_begin,cursor_pos);

	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();	

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();	

	glMatrixMode(GL_MODELVIEW);

	if (light == 1)
		glEnable(GL_LIGHTING);
	

	Fl_Gl_Window::draw();

};

bool bula_view::process_cmd_key(const char * fl_text) {

	int fl_key = Fl::event_key();

	switch ( fl_key ) {
	case ' ':
		if (fabula) {
			Tcl_EvalEx(interp, "cleanup", -1, TCL_EVAL_DIRECT);

			vector<char*>::iterator cmd_it = cmd_history.begin();
			while ( cmd_it != cmd_history.end() ) {
				char * cmd = (char*)malloc( strlen(*cmd_it) - 1);
				strcpy(cmd,*cmd_it+2);
				
				Tcl_EvalEx(interp, cmd, -1, TCL_EVAL_DIRECT);

				free(cmd);
				cmd_it++;
			}


			Fl_Widget::redraw();			
		}
		return true;

	}
	return false;
};

bool bula_view::process_key(const char * fl_text) {

	int fl_key = Fl::event_key();

	switch( fl_key ) 
	{
	case FL_Up:
		processHistoryUp();
		Fl_Widget::redraw();
		return true;
	case FL_Down:
		processHistoryDown();
		Fl_Widget::redraw();
		return true;
	case FL_Left:
		cursor_pos = cursorLeft(cursor_pos);
		Fl_Widget::redraw();
		return true;
	case FL_Right:
		cursor_pos = cursorRight(cursor_pos, strlen(command)-2);
		Fl_Widget::redraw();
		return true;
	case FL_BackSpace:
		cursor_pos = delLeft(command+2, cursor_pos);
		Fl_Widget::redraw();
		return true;
	case FL_Delete:
		cursor_pos = delRight(command+2, cursor_pos);
		Fl_Widget::redraw();
		return true;
	case FL_Enter: 
		{
			process_cmd();
			Fl_Widget::redraw();
			return true;
		}
	};

	if (strlen(fl_text) > 0) {
		cursor_pos = insertChar(fl_text[0], command+2, cursor_pos);
		Fl_Widget::redraw();
		return true;
	}

	return false;

};

void bula_view::process_cmd()
{
	glChannelInfo* Dat = (glChannelInfo*)Tcl_GetChannelInstanceData(gl_output);
	
	Tcl_EvalEx(interp, command+2, -1, TCL_EVAL_DIRECT);
	Tcl_Flush(gl_output);
	Tcl_Obj *res = Tcl_GetObjResult(interp);

	add_to_cmd_history(command);
	strcpy(command,"> ");
	cursor_pos = 0;
	const char * cres = Tcl_GetStringResult(interp);

    int tt = strlen(cres);
	
	char * res_string = (char*) malloc ( strlen(cres)+strlen(Dat->data)+1 );
	
	if (tt > 0) {
		strncpy(res_string,Dat->data, strlen(Dat->data));
		strcpy(res_string+strlen(Dat->data),cres);
	} else {
		res_string = strdup(Dat->data);
	}
	add_to_res_history(res_string);
	*(Dat->data) = '\0';
	free(res_string);
	cmd_history_pos = 0;
}

void bula_view::add_to_cmd_history(const char * command) {
	char * add = (char * ) malloc(strlen(command)+1);
	strcpy(add,command);
	cmd_history.push_back(add);

};

void bula_view::add_to_res_history(const char * command) {
	char * add = strdup(command);
	res_history.push_back(add);
};

void bula_view::processHistoryUp() {
	cmd_history_pos++;
	if (cmd_history_pos > cmd_history.size())
		cmd_history_pos = cmd_history.size();

	strcpy(command,*(cmd_history.begin()+cmd_history.size()-cmd_history_pos));
	cursor_pos = strlen(command)-2;
};

void bula_view::processHistoryDown() {
	if (cmd_history_pos == 0)
		return;
	cmd_history_pos--;
	if (cmd_history_pos < 0)
		cmd_history_pos = 0;

	if (cmd_history_pos == 0) {
		strcpy(command,"> ");
		cursor_pos = 0;
		return;
	}

	strcpy(command,*(cmd_history.begin()+cmd_history.size()-cmd_history_pos));
	cursor_pos = strlen(command)-2;
};

bool bula_view::processFabula() {
	// startup script
	char * my_script_name = strdup(script_name);
	
	Tcl_EvalFile(interp, my_script_name);

	free(my_script_name);

#ifdef WIN32
	add_to_cmd_history("> source bula.tcl");
#else
	add_to_cmd_history("> source bula.tcl");
#endif

	Tcl_Flush(gl_output);
	Tcl_Obj *res = Tcl_GetObjResult(interp);
	
	cursor_pos = 0;
	const char * cres = Tcl_GetStringResult(interp);
	
	glChannelInfo* Dat = (glChannelInfo*)Tcl_GetChannelInstanceData(gl_output);
	
	char * res_string = (char*) malloc ( strlen(cres)+strlen(Dat->data)+1 );

	strncpy(res_string,Dat->data, strlen(Dat->data));
	strcpy(res_string+strlen(Dat->data),cres);
	add_to_res_history(res_string);
	free(res_string);
	free(Dat->data);
	Dat->data = (char*)malloc(1);
	*(Dat->data) = '\0';
	Dat->size = 0;
	Tcl_Flush(gl_output);
	return true;
};

void bula_view::process_push_mouse() {
	mouse_x = Fl::event_x();
	mouse_y = Fl::event_y();
};

void bula_view::process_wheel() {
	int dy = -Fl::event_dy();

	char buf[2048];
	const char * temp = NULL;

	double z_scale = 5.;
	temp = Tcl_GetVar(interp,"z_scale",0);
	if (temp)
		z_scale = atof(temp);

	z_scale += z_scale*dy/10. + dy/50.;
	if (z_scale < 0.0001) 
		z_scale = 0.0001;
	
	sprintf(buf,"%lf",z_scale);
	Tcl_SetVar(interp, "z_scale", buf, TCL_GLOBAL_ONLY);
	Fl_Widget::redraw();
};

void bula_view::process_drag_mouse() {

	char buf[2048];
	const char * temp = NULL;

	double dx = Fl::event_x() - mouse_x;
	double dy = Fl::event_y() - mouse_y;

	switch (Fl::event_button()) {
	case FL_LEFT_MOUSE :
		{
			if (Fl::event_state(FL_CAPS_LOCK)) 
			{
				double z_scale = 5.;
				temp = Tcl_GetVar(interp,"z_scale",0);
					if (temp)
						z_scale = atof(temp);
				
				z_scale += z_scale*dy/10. + dy/50.;
				if (z_scale < 0.0001) 
					z_scale = 0.0001;

				sprintf(buf,"%lf",z_scale);
				Tcl_SetVar(interp, "z_scale", buf, TCL_GLOBAL_ONLY);
				
			} else 
			{
				int pos_x = Fl::event_x();
				int pos_y = Fl::event_y();
				int ww = w();
				int hh = h();
				sprintf(cmd,"moving %d %d %d %d %d %d", mouse_x, mouse_y, pos_x, pos_y, ww, hh);
				Tcl_EvalEx(interp, cmd, -1, TCL_EVAL_DIRECT);
				Tcl_Obj *res = Tcl_GetObjResult(interp);
			}

			Fl_Widget::redraw();
		}
		break;
	case FL_MIDDLE_MOUSE :
		{
			double scale = 5.;
			temp = Tcl_GetVar(interp,"scale",0);
			if (temp) scale = atof(temp);

			scale -=  dy/100.*scale;
			sprintf(buf,"%lf",scale);
			Tcl_SetVar(interp, "scale", buf, TCL_GLOBAL_ONLY);
						
			Fl_Widget::redraw();
		}
		break;
	case FL_RIGHT_MOUSE :
		{
			if (Fl::event_state(FL_CAPS_LOCK)) {
				double scale = 5.;
				temp = Tcl_GetVar(interp,"scale",0);
				if (temp) scale = atof(temp);

				scale -=  dy/100.*scale;
				sprintf(buf,"%lf",scale);
				Tcl_SetVar(interp, "scale", buf, TCL_GLOBAL_ONLY);
			} else {
				double scale = 5.;
				temp = Tcl_GetVar(interp,"scale",0);
				if (temp) scale = atof(temp);

				dx *= 2.;
				dx /= scale;
				dy *= 2.;
				dy /= scale;
				
				double x_shift = 0;
				temp = Tcl_GetVar(interp,"x_shift",0);
				if (temp) x_shift = atof(temp);
				x_shift += dx*scale;
				sprintf(buf,"%lf",x_shift);
				Tcl_SetVar(interp, "x_shift", buf, TCL_GLOBAL_ONLY);

				double y_shift = 0;
				temp = Tcl_GetVar(interp,"y_shift",0);
				if (temp) y_shift = atof(temp);
				y_shift -= dy*scale;
				sprintf(buf,"%lf",y_shift);
				Tcl_SetVar(interp, "y_shift", buf, TCL_GLOBAL_ONLY);

			}
			
			Fl_Widget::redraw();
		}
		break;
	};
	mouse_x = Fl::event_x();
	mouse_y = Fl::event_y();
};
