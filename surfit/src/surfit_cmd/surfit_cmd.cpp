
#include <tcl.h>

int AppInit(Tcl_Interp *interp) {
	if(Tcl_Init(interp) == TCL_ERROR) 
		return TCL_ERROR;
	Tcl_Eval(interp, "info sharedlibextension");
	const char * res = Tcl_GetStringResult(interp);
	char buf[256];
	sprintf(buf, "load libsurfit%s", res);
	Tcl_Eval(interp, buf);
	
	Tcl_Eval(interp, "info sharedlibextension");
	res = Tcl_GetStringResult(interp);
	sprintf(buf, "load libsurfit_io%s", res);
	Tcl_Eval(interp, buf);
	
	Tcl_Eval(interp, "info sharedlibextension");
	res = Tcl_GetStringResult(interp);
	sprintf(buf, "load libglobe%s", res);
	Tcl_Eval(interp, buf);

	Tcl_Eval(interp, "info sharedlibextension");
	res = Tcl_GetStringResult(interp);
	sprintf(buf, "load libfreeflow%s", res);
	Tcl_Eval(interp, buf);
	return TCL_OK;
}

int main(int argc, char *argv[]) {
	Tcl_Main(argc, argv, AppInit);
	return 0;
}

