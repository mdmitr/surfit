
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

	char * new_string = "\n";
	Tcl_Channel out = NULL;
	if (interp) {
		out = Tcl_GetStdChannel(TCL_STDOUT);
	}

	Tcl_Eval(interp, "info sharedlibextension");
	const char * res = Tcl_GetStringResult(interp);
	char buf[256];
	sprintf(buf, "load libsurfit%s", res);
	int result = Tcl_Eval(interp, buf);
	if (result != TCL_OK) {
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
		res = Tcl_GetStringResult(interp);
		if (out) {
			Tcl_WriteChars(out, res, (int)strlen(res));
			Tcl_WriteChars(out, new_string, 1);
		}
	}

	return TCL_OK;
}

int main(int argc, char *argv[]) {
	Tcl_Main(argc, argv, AppInit);
	return 0;
}

