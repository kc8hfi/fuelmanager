1.  Make sure you have the following packages installed:
		qt-devel
		gcc-c++
2.  execute 'qmake' or 'qmake-qt4', depending on your distro 
3.  execute 'make' to build
4.  execute 'fuelmanager' to run fuelmanager

The documentation is in the documentation folder.  It is written in latex, and
the html version has already been created.  The index.html file is the main
file.

If you wish to generate the pdf file, the main .tex file is called
fuelmanager.tex.  If you like to click buttons, the fuelmanager.kilepr is the
project file for kile.

Qt Assistant can also be used to view the documents.  There is a file called
fuelmanager.qch.  You can view it using qt assistant by executing 
	assistant-qt4 -collectionFile fuelmanager.qhc 
or by executing 
	assistant - collectionFile
fuelmanager.qhc depending on your distribution.

If you want to regenerate the qt assistant collection from the html docs, do so
by executing 
	qcollectiongenerator fuelmanager.qhcp -o fuelmanager.qhc

