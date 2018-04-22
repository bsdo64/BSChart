QT += core network quick qml
CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

HEADERS += \
    bitmexauth.h \
    bitmexclient.h


SOURCES += \
        main.cpp \
    bitmexauth.cpp \
    bitmexclient.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

# 3rdparty/cryptopp700
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/3rdparty/cryptopp700/release/ -lcryptopp
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/3rdparty/cryptopp700/debug/ -lcryptopp
else:unix: LIBS += -L$$PWD/3rdparty/cryptopp700/ -lcryptopp

INCLUDEPATH += $$PWD/3rdparty/cryptopp700
DEPENDPATH += $$PWD/3rdparty/cryptopp700

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/3rdparty/cryptopp700/release/libcryptopp.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/3rdparty/cryptopp700/debug/libcryptopp.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/3rdparty/cryptopp700/release/cryptopp.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/3rdparty/cryptopp700/debug/cryptopp.lib
else:unix: PRE_TARGETDEPS += $$PWD/3rdparty/cryptopp700/libcryptopp.a

# /usr/local/Cellar/boost/1.66.0
macx {
    _BOOST_PATH = /usr/local/Cellar/boost/1.66.0
    INCLUDEPATH += "$${_BOOST_PATH}/include/"
    LIBS += -L$${_BOOST_PATH}/lib
    ## Use only one of these:
    ## LIBS += -lboost_chrono-mt # using dynamic lib (not sure if you need that "-mt" at the end or not)
    ## LIBS += $${_BOOST_PATH}/lib/libboost_chrono-mt.a # using static lib
}

# /usr/local/Cellar/armadillo/8.400.0
macx {
    _ARMA_PATH = /usr/local/Cellar/armadillo/8.400.1
    INCLUDEPATH += "$${_ARMA_PATH}/include/"
    LIBS += -L$${_ARMA_PATH}/lib -larmadillo
}
