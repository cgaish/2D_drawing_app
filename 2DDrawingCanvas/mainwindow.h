#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStatusBar>


class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    QStatusBar *statusBar = new QStatusBar;;
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void renderWindowIsInitialized();
    QSize sizeHint() const;
};
#endif // MAINWINDOW_H
