Hi!
This library is a loadable module for surfit.
This library implements the "Conjugate Gradients" method
using MKL (http://www.intel.com/software/products/mkl) functions. 
To use this library you should load it with a Tcl command:

# load libmklbooster[info sharedlibextension]

Then library is loaded, you can set solver variable to "cg_mkl"
with a command:

# set_solver "cg_mkl"

