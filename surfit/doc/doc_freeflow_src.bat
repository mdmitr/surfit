
cd freeflow
cd freeflow_src
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
cd ..

doxygen freeflow_src.cfg

cd freeflow
cd freeflow_src
cd html
perl installdox -lsurfit_src.tag@../../../surfit/surfit_src/html
del *.bak
cd ..
cd ..
cd ..


