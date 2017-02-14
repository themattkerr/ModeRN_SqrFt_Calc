#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "propertysqrftstats.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:




    void on_horizontalSlider_valueChanged(int value);

    //void on_lineEdit_3_editingFinished();

    void on_lineAddr_textChanged(const QString &arg1);

    void on_lineMLSNum_textChanged(const QString &arg1);

    void on_linePrice_textChanged(const QString &arg1);

//    void on_lineAbove_textChanged(const QString &arg1);

//    void on_lineBelow_textChanged(const QString &arg1);

    void on_spinBoxFinAbove_valueChanged(int arg1);

    void on_spinBoxFinBelow_valueChanged(int arg1);

private:
    Ui::MainWindow *ui;
    PropertySqrftStats Home;
    void refreshFields();

};

#endif // MAINWINDOW_H
