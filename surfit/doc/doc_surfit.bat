
cd surfit
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

doxygen surfit.cfg

cd surfit
cd html
perl installdox -lsurfit_src.tag@../../surfit/surfit_src/html
del *.bak
cd ..
cd ..

cd ..
cd surfit
cd doc
copy index.html ..\..\doc\surfit\html\index.html

