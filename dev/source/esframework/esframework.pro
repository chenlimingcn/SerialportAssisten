TEMPLATE = lib

DEPENDPATH += .

TARGET = esframework

DEFINES += ESFRAMEWORK_LIB UNICODE _UNICODE QT_NO_STL_WCHAR

DESTDIR = ../../lib
DLLDESTDIR = ../../../bin

INCLUDEPATH += ./ \
		../../include \
		../../source 

LIBS += -L../../lib 

QT -= gui

CONFIG(debug, release|debug):{
OBJECTS_DIR = ../../build/esframework/debug
MOC_DIR = ../../build/esframework/debug/moc


}
CONFIG(release, release|debug): {
OBJECTS_DIR = ../../build/esframework/release
MOC_DIR = ../../build/esframework/release/moc

}

win32 {
   target.path=../../../install/bin
   INSTALLS += target
   QMAKE_CXXFLAGS_DEBUG += /Od
}

# Input
HEADERS +=  esframework.pro \
	*.h 

SOURCES += *.cpp 

TARGET = $$qtLibraryTarget($$TARGET)
