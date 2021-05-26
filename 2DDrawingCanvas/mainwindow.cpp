#include <QMenu>
#include <QMenuBar>
#include <QStatusBar>
#include <QAction>
#include <QDebug>
#include <QApplication>

#include "mainwindow.h"
#include "rendermanager.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // Declare Quit Action
    QAction *quitAction = new QAction("Quit");
    connect(quitAction, &QAction::triggered, [=](){
      QApplication::quit();
    });

    // Set menu bar
    QMenu *fileMenu = menuBar()->addMenu("File");
    fileMenu->addAction(quitAction);
    // Set central widget to the opengl rendering widget


    RenderManager *rw = new RenderManager;

    this->setCentralWidget(rw);

    // Set status bar
    //statusBar->showMessage(tr(rw->openGLInfo));
    MainWindow::setStatusBar(statusBar);

    qDebug() << "Main window size: " << this->width() << " | " << this->height();

;}

MainWindow::~MainWindow()
{
}


QSize MainWindow::sizeHint() const
{
    return QSize(1200, 1000);
}
