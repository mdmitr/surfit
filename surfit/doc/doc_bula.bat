
cd bula
cd html
del *.html
del *.png
del *.css
del *.gif
del *.jpg
del formula.*
del _form*.*
cd ..
cd ..

doxygen bula.cfg
cd bula
cd html
perl installdox -lsurfit_src.tag@../../surfit_src/html
del *.bak
cd ..
cd ..

cd ..
cd bula
cd doc
copy index.html ..\..\doc\bula\html\index.html

