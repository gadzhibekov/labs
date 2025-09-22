#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>


struct MainWindow : QMainWindow
{
    MainWindow(QWidget* parent);
    ~MainWindow() = default;
};

#endif // MAINWINDOW_H
