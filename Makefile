#############################################################################
# Makefile for building: Battleship3D
# Generated by qmake (2.01a) (Qt 4.8.7) on: ?? ??? 26 16:29:25 2020
# Project:  Battleship3D.pro
# Template: app
# Command: /usr/bin/qmake-qt4 -o Makefile Battleship3D.pro
#############################################################################

####### Compiler, tools and options

CC            = gcc
CXX           = g++
DEFINES       = -DQT_NO_DEBUG -DQT_OPENGL_LIB -DQT_GUI_LIB -DQT_CORE_LIB -DQT_SHARED
CFLAGS        = -m64 -pipe -O2 -Wall -W -D_REENTRANT $(DEFINES)
CXXFLAGS      = -m64 -pipe -O2 -Wall -W -D_REENTRANT $(DEFINES)
INCPATH       = -I/usr/share/qt4/mkspecs/linux-g++-64 -I. -I/usr/include/qt4/QtCore -I/usr/include/qt4/QtGui -I/usr/include/qt4/QtOpenGL -I/usr/include/qt4 -I. -I/usr/X11R6/include -I.
LINK          = g++
LFLAGS        = -m64 -Wl,-O1
LIBS          = $(SUBLIBS)  -L/usr/lib/x86_64-linux-gnu -L/usr/X11R6/lib64 -lQtOpenGL -lQtGui -lQtCore -lGL -lGLU -lpthread 
AR            = ar cqs
RANLIB        = 
QMAKE         = /usr/bin/qmake-qt4
TAR           = tar -cf
COMPRESS      = gzip -9f
COPY          = cp -f
SED           = sed
COPY_FILE     = $(COPY)
COPY_DIR      = $(COPY) -r
STRIP         = strip
INSTALL_FILE  = install -m 644 -p
INSTALL_DIR   = $(COPY_DIR)
INSTALL_PROGRAM = install -m 755 -p
DEL_FILE      = rm -f
SYMLINK       = ln -f -s
DEL_DIR       = rmdir
MOVE          = mv -f
CHK_DIR_EXISTS= test -d
MKDIR         = mkdir -p

####### Output directory

OBJECTS_DIR   = ./

####### Files

SOURCES       = 3ds.cpp \
		bateau.C \
		camera.C \
		cartenavale.C \
		case.C \
		classetext.C \
		fonctions.C \
		graphique.C \
		mer.C \
		model.C \
		PD.cpp \
		principale.C \
		projet.C \
		skydome.C \
		terrain.C \
		texture.C \
		transf.C \
		tree.C moc_graphique.cpp \
		moc_PD.cpp \
		moc_principale.cpp
OBJECTS       = 3ds.o \
		bateau.o \
		camera.o \
		cartenavale.o \
		case.o \
		classetext.o \
		fonctions.o \
		graphique.o \
		mer.o \
		model.o \
		PD.o \
		principale.o \
		projet.o \
		skydome.o \
		terrain.o \
		texture.o \
		transf.o \
		tree.o \
		moc_graphique.o \
		moc_PD.o \
		moc_principale.o
DIST          = /usr/share/qt4/mkspecs/common/unix.conf \
		/usr/share/qt4/mkspecs/common/linux.conf \
		/usr/share/qt4/mkspecs/common/gcc-base.conf \
		/usr/share/qt4/mkspecs/common/gcc-base-unix.conf \
		/usr/share/qt4/mkspecs/common/g++-base.conf \
		/usr/share/qt4/mkspecs/common/g++-unix.conf \
		/usr/share/qt4/mkspecs/qconfig.pri \
		/usr/share/qt4/mkspecs/features/qt_functions.prf \
		/usr/share/qt4/mkspecs/features/qt_config.prf \
		/usr/share/qt4/mkspecs/features/exclusive_builds.prf \
		/usr/share/qt4/mkspecs/features/default_pre.prf \
		/usr/share/qt4/mkspecs/features/release.prf \
		/usr/share/qt4/mkspecs/features/default_post.prf \
		/usr/share/qt4/mkspecs/features/shared.prf \
		/usr/share/qt4/mkspecs/features/unix/gdb_dwarf_index.prf \
		/usr/share/qt4/mkspecs/features/warn_on.prf \
		/usr/share/qt4/mkspecs/features/qt.prf \
		/usr/share/qt4/mkspecs/features/unix/opengl.prf \
		/usr/share/qt4/mkspecs/features/unix/thread.prf \
		/usr/share/qt4/mkspecs/features/moc.prf \
		/usr/share/qt4/mkspecs/features/resources.prf \
		/usr/share/qt4/mkspecs/features/uic.prf \
		/usr/share/qt4/mkspecs/features/yacc.prf \
		/usr/share/qt4/mkspecs/features/lex.prf \
		/usr/share/qt4/mkspecs/features/include_source_dir.prf \
		Battleship3D.pro
QMAKE_TARGET  = Battleship3D
DESTDIR       = 
TARGET        = Battleship3D

first: all
####### Implicit rules

.SUFFIXES: .o .c .cpp .cc .cxx .C

.cpp.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cc.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cxx.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.C.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.c.o:
	$(CC) -c $(CFLAGS) $(INCPATH) -o "$@" "$<"

####### Build rules

all: Makefile $(TARGET)

$(TARGET):  $(OBJECTS)  
	$(LINK) $(LFLAGS) -o $(TARGET) $(OBJECTS) $(OBJCOMP) $(LIBS)

Makefile: Battleship3D.pro  /usr/share/qt4/mkspecs/linux-g++-64/qmake.conf /usr/share/qt4/mkspecs/common/unix.conf \
		/usr/share/qt4/mkspecs/common/linux.conf \
		/usr/share/qt4/mkspecs/common/gcc-base.conf \
		/usr/share/qt4/mkspecs/common/gcc-base-unix.conf \
		/usr/share/qt4/mkspecs/common/g++-base.conf \
		/usr/share/qt4/mkspecs/common/g++-unix.conf \
		/usr/share/qt4/mkspecs/qconfig.pri \
		/usr/share/qt4/mkspecs/features/qt_functions.prf \
		/usr/share/qt4/mkspecs/features/qt_config.prf \
		/usr/share/qt4/mkspecs/features/exclusive_builds.prf \
		/usr/share/qt4/mkspecs/features/default_pre.prf \
		/usr/share/qt4/mkspecs/features/release.prf \
		/usr/share/qt4/mkspecs/features/default_post.prf \
		/usr/share/qt4/mkspecs/features/shared.prf \
		/usr/share/qt4/mkspecs/features/unix/gdb_dwarf_index.prf \
		/usr/share/qt4/mkspecs/features/warn_on.prf \
		/usr/share/qt4/mkspecs/features/qt.prf \
		/usr/share/qt4/mkspecs/features/unix/opengl.prf \
		/usr/share/qt4/mkspecs/features/unix/thread.prf \
		/usr/share/qt4/mkspecs/features/moc.prf \
		/usr/share/qt4/mkspecs/features/resources.prf \
		/usr/share/qt4/mkspecs/features/uic.prf \
		/usr/share/qt4/mkspecs/features/yacc.prf \
		/usr/share/qt4/mkspecs/features/lex.prf \
		/usr/share/qt4/mkspecs/features/include_source_dir.prf \
		/usr/lib/x86_64-linux-gnu/libQtOpenGL.prl \
		/usr/lib/x86_64-linux-gnu/libQtGui.prl \
		/usr/lib/x86_64-linux-gnu/libQtCore.prl
	$(QMAKE) -o Makefile Battleship3D.pro
/usr/share/qt4/mkspecs/common/unix.conf:
/usr/share/qt4/mkspecs/common/linux.conf:
/usr/share/qt4/mkspecs/common/gcc-base.conf:
/usr/share/qt4/mkspecs/common/gcc-base-unix.conf:
/usr/share/qt4/mkspecs/common/g++-base.conf:
/usr/share/qt4/mkspecs/common/g++-unix.conf:
/usr/share/qt4/mkspecs/qconfig.pri:
/usr/share/qt4/mkspecs/features/qt_functions.prf:
/usr/share/qt4/mkspecs/features/qt_config.prf:
/usr/share/qt4/mkspecs/features/exclusive_builds.prf:
/usr/share/qt4/mkspecs/features/default_pre.prf:
/usr/share/qt4/mkspecs/features/release.prf:
/usr/share/qt4/mkspecs/features/default_post.prf:
/usr/share/qt4/mkspecs/features/shared.prf:
/usr/share/qt4/mkspecs/features/unix/gdb_dwarf_index.prf:
/usr/share/qt4/mkspecs/features/warn_on.prf:
/usr/share/qt4/mkspecs/features/qt.prf:
/usr/share/qt4/mkspecs/features/unix/opengl.prf:
/usr/share/qt4/mkspecs/features/unix/thread.prf:
/usr/share/qt4/mkspecs/features/moc.prf:
/usr/share/qt4/mkspecs/features/resources.prf:
/usr/share/qt4/mkspecs/features/uic.prf:
/usr/share/qt4/mkspecs/features/yacc.prf:
/usr/share/qt4/mkspecs/features/lex.prf:
/usr/share/qt4/mkspecs/features/include_source_dir.prf:
/usr/lib/x86_64-linux-gnu/libQtOpenGL.prl:
/usr/lib/x86_64-linux-gnu/libQtGui.prl:
/usr/lib/x86_64-linux-gnu/libQtCore.prl:
qmake:  FORCE
	@$(QMAKE) -o Makefile Battleship3D.pro

dist: 
	@$(CHK_DIR_EXISTS) .tmp/Battleship3D1.0.0 || $(MKDIR) .tmp/Battleship3D1.0.0 
	$(COPY_FILE) --parents $(SOURCES) $(DIST) .tmp/Battleship3D1.0.0/ && $(COPY_FILE) --parents 3ds.h 3dsModel.h bateau.h camera.h cartenavale.h case.h classetext.h graphique.h headers.h mer.h model.h objet.h PD.h principale.h skydome.h terrain.h texture.h transf.h tree.h .tmp/Battleship3D1.0.0/ && $(COPY_FILE) --parents 3ds.cpp bateau.C camera.C cartenavale.C case.C classetext.C fonctions.C graphique.C mer.C model.C PD.cpp principale.C projet.C skydome.C terrain.C texture.C transf.C tree.C .tmp/Battleship3D1.0.0/ && (cd `dirname .tmp/Battleship3D1.0.0` && $(TAR) Battleship3D1.0.0.tar Battleship3D1.0.0 && $(COMPRESS) Battleship3D1.0.0.tar) && $(MOVE) `dirname .tmp/Battleship3D1.0.0`/Battleship3D1.0.0.tar.gz . && $(DEL_FILE) -r .tmp/Battleship3D1.0.0


clean:compiler_clean 
	-$(DEL_FILE) $(OBJECTS)
	-$(DEL_FILE) *~ core *.core


####### Sub-libraries

distclean: clean
	-$(DEL_FILE) $(TARGET) 
	-$(DEL_FILE) Makefile


check: first

mocclean: compiler_moc_header_clean compiler_moc_source_clean

mocables: compiler_moc_header_make_all compiler_moc_source_make_all

compiler_moc_header_make_all: moc_graphique.cpp moc_PD.cpp moc_principale.cpp
compiler_moc_header_clean:
	-$(DEL_FILE) moc_graphique.cpp moc_PD.cpp moc_principale.cpp
moc_graphique.cpp: headers.h \
		config \
		Francais.lng \
		English.lng \
		principale.h \
		transf.h \
		3dsModel.h \
		camera.h \
		texture.h \
		classetext.h \
		mer.h \
		cartenavale.h \
		objet.h \
		bateau.h \
		case.h \
		skydome.h \
		terrain.h \
		3ds.h \
		model.h \
		graphique.h \
		tree.h \
		PD.h \
		graphique.h
	/usr/lib/x86_64-linux-gnu/qt4/bin/moc $(DEFINES) $(INCPATH) graphique.h -o moc_graphique.cpp

moc_PD.cpp: headers.h \
		config \
		Francais.lng \
		English.lng \
		principale.h \
		transf.h \
		3dsModel.h \
		camera.h \
		texture.h \
		classetext.h \
		mer.h \
		cartenavale.h \
		objet.h \
		bateau.h \
		case.h \
		skydome.h \
		terrain.h \
		3ds.h \
		model.h \
		graphique.h \
		tree.h \
		PD.h \
		PD.h
	/usr/lib/x86_64-linux-gnu/qt4/bin/moc $(DEFINES) $(INCPATH) PD.h -o moc_PD.cpp

moc_principale.cpp: headers.h \
		config \
		Francais.lng \
		English.lng \
		principale.h \
		transf.h \
		3dsModel.h \
		camera.h \
		texture.h \
		classetext.h \
		mer.h \
		cartenavale.h \
		objet.h \
		bateau.h \
		case.h \
		skydome.h \
		terrain.h \
		3ds.h \
		model.h \
		graphique.h \
		tree.h \
		PD.h \
		principale.h
	/usr/lib/x86_64-linux-gnu/qt4/bin/moc $(DEFINES) $(INCPATH) principale.h -o moc_principale.cpp

compiler_rcc_make_all:
compiler_rcc_clean:
compiler_image_collection_make_all: qmake_image_collection.cpp
compiler_image_collection_clean:
	-$(DEL_FILE) qmake_image_collection.cpp
compiler_moc_source_make_all:
compiler_moc_source_clean:
compiler_uic_make_all:
compiler_uic_clean:
compiler_yacc_decl_make_all:
compiler_yacc_decl_clean:
compiler_yacc_impl_make_all:
compiler_yacc_impl_clean:
compiler_lex_make_all:
compiler_lex_clean:
compiler_clean: compiler_moc_header_clean 

####### Compile

3ds.o: 3ds.cpp headers.h \
		config \
		Francais.lng \
		English.lng \
		principale.h \
		transf.h \
		3dsModel.h \
		camera.h \
		texture.h \
		classetext.h \
		mer.h \
		cartenavale.h \
		objet.h \
		bateau.h \
		case.h \
		skydome.h \
		terrain.h \
		3ds.h \
		model.h \
		graphique.h \
		tree.h \
		PD.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o 3ds.o 3ds.cpp

bateau.o: bateau.C headers.h \
		config \
		Francais.lng \
		English.lng \
		principale.h \
		transf.h \
		3dsModel.h \
		camera.h \
		texture.h \
		classetext.h \
		mer.h \
		cartenavale.h \
		objet.h \
		bateau.h \
		case.h \
		skydome.h \
		terrain.h \
		3ds.h \
		model.h \
		graphique.h \
		tree.h \
		PD.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o bateau.o bateau.C

camera.o: camera.C headers.h \
		config \
		Francais.lng \
		English.lng \
		principale.h \
		transf.h \
		3dsModel.h \
		camera.h \
		texture.h \
		classetext.h \
		mer.h \
		cartenavale.h \
		objet.h \
		bateau.h \
		case.h \
		skydome.h \
		terrain.h \
		3ds.h \
		model.h \
		graphique.h \
		tree.h \
		PD.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o camera.o camera.C

cartenavale.o: cartenavale.C headers.h \
		config \
		Francais.lng \
		English.lng \
		principale.h \
		transf.h \
		3dsModel.h \
		camera.h \
		texture.h \
		classetext.h \
		mer.h \
		cartenavale.h \
		objet.h \
		bateau.h \
		case.h \
		skydome.h \
		terrain.h \
		3ds.h \
		model.h \
		graphique.h \
		tree.h \
		PD.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o cartenavale.o cartenavale.C

case.o: case.C headers.h \
		config \
		Francais.lng \
		English.lng \
		principale.h \
		transf.h \
		3dsModel.h \
		camera.h \
		texture.h \
		classetext.h \
		mer.h \
		cartenavale.h \
		objet.h \
		bateau.h \
		case.h \
		skydome.h \
		terrain.h \
		3ds.h \
		model.h \
		graphique.h \
		tree.h \
		PD.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o case.o case.C

classetext.o: classetext.C headers.h \
		config \
		Francais.lng \
		English.lng \
		principale.h \
		transf.h \
		3dsModel.h \
		camera.h \
		texture.h \
		classetext.h \
		mer.h \
		cartenavale.h \
		objet.h \
		bateau.h \
		case.h \
		skydome.h \
		terrain.h \
		3ds.h \
		model.h \
		graphique.h \
		tree.h \
		PD.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o classetext.o classetext.C

fonctions.o: fonctions.C headers.h \
		config \
		Francais.lng \
		English.lng \
		principale.h \
		transf.h \
		3dsModel.h \
		camera.h \
		texture.h \
		classetext.h \
		mer.h \
		cartenavale.h \
		objet.h \
		bateau.h \
		case.h \
		skydome.h \
		terrain.h \
		3ds.h \
		model.h \
		graphique.h \
		tree.h \
		PD.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o fonctions.o fonctions.C

graphique.o: graphique.C headers.h \
		config \
		Francais.lng \
		English.lng \
		principale.h \
		transf.h \
		3dsModel.h \
		camera.h \
		texture.h \
		classetext.h \
		mer.h \
		cartenavale.h \
		objet.h \
		bateau.h \
		case.h \
		skydome.h \
		terrain.h \
		3ds.h \
		model.h \
		graphique.h \
		tree.h \
		PD.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o graphique.o graphique.C

mer.o: mer.C headers.h \
		config \
		Francais.lng \
		English.lng \
		principale.h \
		transf.h \
		3dsModel.h \
		camera.h \
		texture.h \
		classetext.h \
		mer.h \
		cartenavale.h \
		objet.h \
		bateau.h \
		case.h \
		skydome.h \
		terrain.h \
		3ds.h \
		model.h \
		graphique.h \
		tree.h \
		PD.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o mer.o mer.C

model.o: model.C headers.h \
		config \
		Francais.lng \
		English.lng \
		principale.h \
		transf.h \
		3dsModel.h \
		camera.h \
		texture.h \
		classetext.h \
		mer.h \
		cartenavale.h \
		objet.h \
		bateau.h \
		case.h \
		skydome.h \
		terrain.h \
		3ds.h \
		model.h \
		graphique.h \
		tree.h \
		PD.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o model.o model.C

PD.o: PD.cpp headers.h \
		config \
		Francais.lng \
		English.lng \
		principale.h \
		transf.h \
		3dsModel.h \
		camera.h \
		texture.h \
		classetext.h \
		mer.h \
		cartenavale.h \
		objet.h \
		bateau.h \
		case.h \
		skydome.h \
		terrain.h \
		3ds.h \
		model.h \
		graphique.h \
		tree.h \
		PD.h \
		images/icon1.xpm \
		images/icon2.xpm \
		images/icon3.xpm \
		images/icon4.xpm \
		images/icon5.xpm \
		images/cam1.xpm
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o PD.o PD.cpp

principale.o: principale.C headers.h \
		config \
		Francais.lng \
		English.lng \
		principale.h \
		transf.h \
		3dsModel.h \
		camera.h \
		texture.h \
		classetext.h \
		mer.h \
		cartenavale.h \
		objet.h \
		bateau.h \
		case.h \
		skydome.h \
		terrain.h \
		3ds.h \
		model.h \
		graphique.h \
		tree.h \
		PD.h \
		images/filesave.xpm \
		images/fileopen.xpm \
		images/file_new.xpm \
		images/icon1.xpm \
		images/icon2.xpm \
		images/icon3.xpm \
		images/icon4.xpm \
		images/icon5.xpm \
		images/x.xpm \
		images/prop.xpm \
		images/cam1.xpm \
		images/cam2.xpm \
		images/cam3.xpm
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o principale.o principale.C

projet.o: projet.C headers.h \
		config \
		Francais.lng \
		English.lng \
		principale.h \
		transf.h \
		3dsModel.h \
		camera.h \
		texture.h \
		classetext.h \
		mer.h \
		cartenavale.h \
		objet.h \
		bateau.h \
		case.h \
		skydome.h \
		terrain.h \
		3ds.h \
		model.h \
		graphique.h \
		tree.h \
		PD.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o projet.o projet.C

skydome.o: skydome.C headers.h \
		config \
		Francais.lng \
		English.lng \
		principale.h \
		transf.h \
		3dsModel.h \
		camera.h \
		texture.h \
		classetext.h \
		mer.h \
		cartenavale.h \
		objet.h \
		bateau.h \
		case.h \
		skydome.h \
		terrain.h \
		3ds.h \
		model.h \
		graphique.h \
		tree.h \
		PD.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o skydome.o skydome.C

terrain.o: terrain.C headers.h \
		config \
		Francais.lng \
		English.lng \
		principale.h \
		transf.h \
		3dsModel.h \
		camera.h \
		texture.h \
		classetext.h \
		mer.h \
		cartenavale.h \
		objet.h \
		bateau.h \
		case.h \
		skydome.h \
		terrain.h \
		3ds.h \
		model.h \
		graphique.h \
		tree.h \
		PD.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o terrain.o terrain.C

texture.o: texture.C headers.h \
		config \
		Francais.lng \
		English.lng \
		principale.h \
		transf.h \
		3dsModel.h \
		camera.h \
		texture.h \
		classetext.h \
		mer.h \
		cartenavale.h \
		objet.h \
		bateau.h \
		case.h \
		skydome.h \
		terrain.h \
		3ds.h \
		model.h \
		graphique.h \
		tree.h \
		PD.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o texture.o texture.C

transf.o: transf.C headers.h \
		config \
		Francais.lng \
		English.lng \
		principale.h \
		transf.h \
		3dsModel.h \
		camera.h \
		texture.h \
		classetext.h \
		mer.h \
		cartenavale.h \
		objet.h \
		bateau.h \
		case.h \
		skydome.h \
		terrain.h \
		3ds.h \
		model.h \
		graphique.h \
		tree.h \
		PD.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o transf.o transf.C

tree.o: tree.C headers.h \
		config \
		Francais.lng \
		English.lng \
		principale.h \
		transf.h \
		3dsModel.h \
		camera.h \
		texture.h \
		classetext.h \
		mer.h \
		cartenavale.h \
		objet.h \
		bateau.h \
		case.h \
		skydome.h \
		terrain.h \
		3ds.h \
		model.h \
		graphique.h \
		tree.h \
		PD.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o tree.o tree.C

moc_graphique.o: moc_graphique.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_graphique.o moc_graphique.cpp

moc_PD.o: moc_PD.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_PD.o moc_PD.cpp

moc_principale.o: moc_principale.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_principale.o moc_principale.cpp

####### Install

install:   FORCE

uninstall:   FORCE

FORCE:

