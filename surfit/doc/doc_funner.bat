
cd funner
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

doxygen funner.cfg
cd funner
cd html
perl installdox -lsurfit_src.tag@../../surfit_src/html
del *.bak
cd ..
cd ..

cd ..
cd funner2d
cd doc
copy index.html ..\..\doc\funner\html\index.html

