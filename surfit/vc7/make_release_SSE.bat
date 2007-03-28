mkdir ..\bin
devenv surfit.sln /build "Release_SSE"
mkdir ..\bin_SSE
copy ..\bin ..\bin_SSE