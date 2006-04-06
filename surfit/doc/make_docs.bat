
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

copy gallery\*.* html\*.*
copy gallery\data\*.* html\*.*
copy gallery\maps\*.* html\*.*

doxygen.exe surfit.cfg

rem cd html
rem "C:\Program Files\HTML Help Workshop\hhc.exe" index.hhp
rem cd ..
rem copy html\surfit.chm ..\bin\surfit.chm

copy src\index.html html\index.html

