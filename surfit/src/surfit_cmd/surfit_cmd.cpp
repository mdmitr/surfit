
#include <tcl.h>

int AppInit(Tcl_Interp *interp) {
	if(Tcl_Init(interp) == TCL_ERROR) 
		return TCL_ERROR;
	Tcl_Eval(interp, "load libsurfit[info sharedlibextension]");
	Tcl_Eval(interp, "load libsurfit_io[info sharedlibextension]");
	Tcl_Eval(interp, "load libglobe[info sharedlibextension]");
	Tcl_Eval(interp, "load libfreeflow[info sharedlibextension]");
	return TCL_OK;
}

int main(int argc, char *argv[]) {
	Tcl_Main(argc, argv, AppInit);
	return 0;
}

