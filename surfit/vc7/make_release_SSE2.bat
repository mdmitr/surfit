mkdir ..\bin
devenv surfit.sln /build "Release_SSE2"
mkdir ..\bin_SSE2
copy ..\bin ..\bin_SSE2