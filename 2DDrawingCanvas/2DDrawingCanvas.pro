QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    3rd_party_deps/glad/src/glad.c \
    geo.cpp \
    glshaderprogram.cpp \
    grid.cpp \
    main.cpp \
    mainwindow.cpp \
    orthographiccamera.cpp \
    rendermanager.cpp \
    stb_image.cpp \
    texture.cpp

HEADERS += \
    camera.h \
    constants.h \
    drawable.h \
    geo.h \
    glshaderexception.h \
    glshaderprogram.h \
    grid.h \
    mainwindow.h \
    orthographiccamera.h \
    particleutils.h \
    random.h \
    rendermanager.h \
    rendermanager.h \
    stb-master/stb.h \
    stb-master/stb_c_lexer.h \
    stb-master/stb_connected_components.h \
    stb-master/stb_divide.h \
    stb-master/stb_ds.h \
    stb-master/stb_dxt.h \
    stb-master/stb_easy_font.h \
    stb-master/stb_herringbone_wang_tile.h \
    stb-master/stb_hexwave.h \
    stb-master/stb_image.h \
    stb-master/stb_image_resize.h \
    stb-master/stb_image_write.h \
    stb-master/stb_include.h \
    stb-master/stb_leakcheck.h \
    stb-master/stb_perlin.h \
    stb-master/stb_rect_pack.h \
    stb-master/stb_sprintf.h \
    stb-master/stb_textedit.h \
    stb-master/stb_tilemap_editor.h \
    stb-master/stb_truetype.h \
    stb-master/stb_voxel_render.h \
    stb-master/tests/caveview/cave_parse.h \
    stb-master/tests/caveview/caveview.h \
    stb-master/tests/caveview/glext.h \
    stb-master/tests/caveview/glext_list.h \
    stb-master/tests/caveview/stb_gl.h \
    stb-master/tests/caveview/stb_glprog.h \
    stb-master/tests/oversample/stb_wingraph.h \
    stb-master/tests/prerelease/stb_lib.h \
    texture.h

INCLUDEPATH += \
    3rd_party_deps/glad/includes/glad/ \
    3rd_party_deps/glm/ \
    stb-master/ \

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    Curve.fs \
    Curve.gs \
    Curve.vs \
    basic.frag \
    basic.vert \
    bez.fs \
    bez.gs \
    bez.tcs \
    bez.tes \
    bez.vs \
    bezier.frag \
    bezier.geom \
    bezier.vert \
    circle.fs \
    circle.gs \
    circle.vs \
    cps.fs \
    cps.vs \
    flat.fs \
    flat.fs \
    flat.vs \
    flat.vs \
    particles.cs \
    particles.fs \
    particles.vs \
    point.frag \
    point.vert \
    qbez.tes \
    quad.fs \
    quad.gs \
    quad.tcs \
    quad.tes \
    quad.vs \
    triangle.frag \
    triangle.vert


#else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

