
#include <tcl.h>
#include <string.h>

#ifdef _MSC_VER
#pragma warning(disable : 4786)
#pragma warning(disable : 4996)
#endif

int AppInit(Tcl_Interp *interp) 
{
	if(Tcl_Init(interp) == TCL_ERROR) 
		return TCL_ERROR;

	const char * new_string = "\n";
	const char * message_on_error = "\n\nSome errors detected while starting surfit!!!\nPlease refer \"Getting started\" documentation page.\n\n";
	Tcl_Channel out = NULL;
	if (interp) {
		out = Tcl_GetStdChannel(TCL_STDOUT);
	}

	bool errors_on_loading = false;

	Tcl_Eval(interp, "info sharedlibextension");
	const char * res = Tcl_GetStringResult(interp);
	char buf[256];
	sprintf(buf, "load libsurfit%s", res);
	int result = Tcl_Eval(interp, buf);
	if (result != TCL_OK) {
		errors_on_loading = true;
		res = Tcl_GetStringResult(interp);
		if (out) {
			Tcl_WriteChars(out, res, (int)strlen(res));
			Tcl_WriteChars(out, new_string, 1);
		}
	}
	
	Tcl_Eval(interp, "info sharedlibextension");
	res = Tcl_GetStringResult(interp);
	sprintf(buf, "load libsurfit_io%s", res);
	result = Tcl_Eval(interp, buf);
	if (result != TCL_OK) {
		errors_on_loading = true;
		res = Tcl_GetStringResult(interp);
		if (out) {
			Tcl_WriteChars(out, res, (int)strlen(res));
			Tcl_WriteChars(out, new_string, 1);
		}
	}
	
	Tcl_Eval(interp, "info sharedlibextension");
	res = Tcl_GetStringResult(interp);
	sprintf(buf, "load libglobe%s", res);
	result = Tcl_Eval(interp, buf);
	if (result != TCL_OK) {
		errors_on_loading = true;
		res = Tcl_GetStringResult(interp);
		if (out) {
			Tcl_WriteChars(out, res, (int)strlen(res));
			Tcl_WriteChars(out, new_string, 1);
		}
	}

	Tcl_Eval(interp, "info sharedlibextension");
	res = Tcl_GetStringResult(interp);
	sprintf(buf, "load libfreeflow%s", res);
	result = Tcl_Eval(interp, buf);
	if (result != TCL_OK) {
		errors_on_loading = true;
		res = Tcl_GetStringResult(interp);
		if (out) {
			Tcl_WriteChars(out, res, (int)strlen(res));
			Tcl_WriteChars(out, new_string, 1);
		}
	}

	if (errors_on_loading)
	{
		Tcl_WriteChars(out, message_on_error, (int)strlen(message_on_error));
	}

	return TCL_OK;
}

int main(int argc, char *argv[]) {
	Tcl_Main(argc, argv, AppInit);
	return 0;
}

