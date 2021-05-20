#include <QMenu>
#include <QMenuBar>
#include <QStatusBar>
#include <QAction>
#include <QDebug>
#include <QApplication>

#include "mainwindow.h"
#include "renderwindow.h"

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


    RenderWindow *rw = new RenderWindow;

    this->setCentralWidget(rw);

    // Set status bar
    //statusBar->showMessage(tr(rw->openGLInfo));
    MainWindow::setStatusBar(statusBar);

;}

MainWindow::~MainWindow()
{
}


QSize MainWindow::sizeHint() const
{
    return QSize(900, 500);
}
