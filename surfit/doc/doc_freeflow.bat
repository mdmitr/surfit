
cd freeflow
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

doxygen freeflow.cfg
cd freeflow
cd html
perl installdox -lsurfit_src.tag@../../surfit/surfit_src/html
perl installdox -lsurfit_src.tag@../freeflow_src/html
del *.bak
cd ..
cd ..

cd ..
cd freeflow
cd doc
copy index.html ..\..\doc\freeflow\html\index.html

