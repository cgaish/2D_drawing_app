#include "mainwindow.h"

#include <QApplication>
#include <QSurfaceFormat>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Global format setup
    QSurfaceFormat canvasFormat(QSurfaceFormat::DebugContext);
    canvasFormat.setSamples(4);
    canvasFormat.setSamples(8);
    canvasFormat.setDepthBufferSize(24);
    canvasFormat.setStencilBufferSize(8);
    canvasFormat.setVersion(4, 6);
    canvasFormat.setProfile(QSurfaceFormat::CoreProfile);
    QSurfaceFormat::setDefaultFormat(canvasFormat);

    // Init objects
    MainWindow w;
    w.setFixedSize(1024, 1024);
    w.show();
    return a.exec();
}
