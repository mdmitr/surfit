
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
copy gallery\globe\*.* html\*.*

doxygen.exe surfit.cfg

copy src\index.html html\index.html
copy src\examples.html html\examples.html

cd html
"C:\Program Files\HTML Help Workshop\hhc.exe" index.hhp
cd ..
copy html\surfit.chm ..\bin\surfit.chm


