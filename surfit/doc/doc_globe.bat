
cd globe
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

doxygen globe.cfg
cd freeflow
cd html
perl installdox -lsurfit_src.tag@../../surfit_src/html
del *.bak
cd ..
cd ..

cd ..
cd globe
cd doc
copy index.html ..\..\doc\globe\html\index.html

