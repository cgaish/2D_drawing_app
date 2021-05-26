QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    3rd_party_deps/glad/src/glad.c \
    beziercurve.cpp \
    glshaderprogram.cpp \
    main.cpp \
    mainwindow.cpp \
    orthographiccamera.cpp \
    point.cpp \
    rendermanager.cpp

HEADERS += \
    3rd_party_deps/glad/include/KHR/khrplatform.h \
    3rd_party_deps/glad/include/glad/glad.h \
    beziercurve.h \
    camera.h \
    constants.h \
    glshaderexception.h \
    glshaderprogram.h \
    mainwindow.h \
    orthographiccamera.h \
    point.h \
    rendermanager.h \
    rendermanager.h

INCLUDEPATH += \
    3rd_party_deps/glad/include/glad/ \
    3rd_party_deps/glm/ \

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    basic.frag \
    basic.vert \
    bez.fs \
    bez.tcs \
    bez.tes \
    bez.vs \
    cps.fs \
    cps.vs

