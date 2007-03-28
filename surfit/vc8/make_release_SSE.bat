mkdir ..\bin
vcbuild /u surfit.sln "Release_SSE|Win32"
mkdir ..\bin_SSE
copy ..\bin ..\bin_SSE