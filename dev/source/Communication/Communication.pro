######################################################################
# Automatically generated by qmake (2.01a) ?? ?? 30 15:20:05 2013
######################################################################

include (../../dev.pri)

TEMPLATE    = lib
TARGET      = Communication
DEFINES     += COMMUNICATION_LIB QT_NO_STL_WCHAR UNICODE _UNICODE
INCLUDEPATH	= . \
			$$INCLUDE_PATH

DESTDIR = $$LIB_PATH
DLLDESTDIR = $$BIN_PATH

OBJECTS_DIR = $$BUILD_PATH/$$TARGET
MOC_DIR     = $$OBJECTS_DIR
RCC_DIR     = $$OBJECTS_DIR
UI_DIR      = $$OBJECTS_DIR

LIBS        += -L$$LIB_PATH
#LIBS        += -l

QT          += xml widgets

win32 {
   target.path=../../../install/bin
   INSTALLS += target
   QMAKE_CXXFLAGS_DEBUG += /Od
}

# Input
HEADERS += Communication.pro \
	*.h 
SOURCES += *.cpp

# RESOURCES = Communication.qrc
TARGET      = $$qtLibraryTarget($$TARGET)

