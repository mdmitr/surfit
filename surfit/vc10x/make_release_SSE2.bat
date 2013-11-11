mkdir ..\bin
vcbuild /u surfit.sln "Release_SSE2|Win32"
mkdir ..\bin_SSE2
copy ..\bin ..\bin_SSE2