#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "propertysqrftstats.h"
//#include "maincompare.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
     PropertySqrftStats getInfo();
     PropertySqrftStats Home;
     void refreshFields();
private slots:

    void on_horizontalSlider_valueChanged(int value);
    void on_lineAddr_textChanged(const QString &arg1);
    void on_lineMLSNum_textChanged(const QString &arg1);
    void on_linePrice_textChanged(const QString &arg1);
    void on_spinBoxFinAbove_valueChanged(int arg1);
    void on_spinBoxFinBelow_valueChanged(int arg1);

private:
    Ui::MainWindow *ui;


    //MainCompare *temp = 0;
};

#endif // MAINWINDOW_H
