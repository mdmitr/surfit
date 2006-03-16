
mkdir html
cd html
del *.html
del *.png
del *.css
del *.gif
del *.jpg
del formula.*
del _form*.*
cd ..

rem copy ..\surfit\doc\surfit.css surfit.css
rem copy ..\surfit\doc\surfit_head.html surfit_head.html
rem copy ..\surfit\doc\surfit_foot.html surfit_foot.html
copy gallery\*.* html\*.*
copy gallery\maps\*.* html\*.*

doxygen.exe surfit.cfg

cd html
"C:\Program Files\HTML Help Workshop\hhc.exe" index.hhp
cd ..
copy html\surfit.chm ..\bin\surfit.chm

rem perl installdox -lsurfit_src.tag@../../surfit/surfit_src/html
rem del *.bak

rem copy ..\surfit\doc\index.html html\index.html

