#pragma once

#include <QApplication>
#include <QMainWindow>
#include <QPushButton>
#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QFont>
#include <QObject>
#include <QMessageBox>
#include <QColor>

class MainWindow : public QMainWindow
{
public:
    MainWindow(QWidget* parent);

private slots:
    void            StartSlot();
    void            TableDataShowSlot();
    void            ParamsDataShowSlot();
    void            SolutionsDataShowSlot();

private:
    void            SetSizeForLabel(int Size, QLabel* Label);
    void            SetSizeForButton(int Size, QPushButton* Button);
    void            SetColorForButton(QColor color, QPushButton* Button);

private:
    QWidget*        CentralWidget;
    QLabel*         Title;
    QLabel*         LabelParam1;
    QLabel*         LabelParam2;
    QLabel*         LabelParam3;
    QLabel*         LabelParam4;
    QLabel*         LabelParam5;
    QLabel*         LabelParam6;
    QLineEdit*      LineEditParam1;
    QLineEdit*      LineEditParam2;
    QLineEdit*      LineEditParam3;
    QLineEdit*      LineEditParam4;
    QLineEdit*      LineEditParam5;
    QLineEdit*      LineEditParam6;
    QPushButton*    Start;
    QPushButton*    Params;
    QPushButton*    Solutions;
    QPushButton*    Table;

    QString         TableData       = "";
    QString         ParamsData      = "";
    QString         SolutionsData   = "";
};