######################################################################
# Automatically generated by qmake (2.01a) ?? ?? 22 15:16:15 2012
######################################################################

# ȫ�ֱ���
include (../../dev.pri)

TEMPLATE    = app
TARGET      = SerialportAssisten
DEFINES     += QT_NO_STL_WCHAR UNICODE _UNICODE
INCLUDEPATH	= . \
		$$INCLUDE_PATH \
		../esframework

DESTDIR     = $$BIN_PATH
OBJECTS_DIR = $$BUILD_PATH/$$TARGET
MOC_DIR     = $$OBJECTS_DIR
RCC_DIR     = $$OBJECTS_DIR
UI_DIR      = $$OBJECTS_DIR

LIBS        += -L$$LIB_PATH
LIBS        += -l$$qtLibraryTarget(esframework)

CONFIG		+= console
QT          += core xml serialport widgets


win32 {
   target.path=../../../install/bin
   INSTALLS += target
   QMAKE_CXXFLAGS_DEBUG += /Od
}

# Input
HEADERS += SerialportAssisten.pro \
	*.h 
SOURCES += *.cpp

RESOURCES = SerialportAssisten.qrc
RC_FILE = SerialportAssisten.rc
TARGET = $$qtLibraryTarget($$TARGET)