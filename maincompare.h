#ifndef MAINCOMPARE_H
#define MAINCOMPARE_H

#include <QMainWindow>
#include "mainwindow.h"
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
#include <qdebug.h>

#define MAX_NUM_OF_PROPERTIES 250

enum
{
    TITLE_LINE = 0,
};

namespace Ui {
class MainCompare;
}

class MainCompare : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainCompare(QWidget *parent = 0);
    ~MainCompare();

    void refreshTable();
  void setupTable();
private slots:



    void on_pushButton_AddProperty_clicked();



    void on_tableWidget_cellDoubleClicked(int row, int column);

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_actionExport_CSV_triggered();

    void on_actionSave_As_triggered();

    void on_actionSave_triggered();

    void on_actionOpen_triggered();

    void on_actionDelete_Selected_triggered();

    void on_actionImport_Paragon_CSV_triggered();

private:
    Ui::MainCompare *ui;
    MainWindow m_Property[MAX_NUM_OF_PROPERTIES];
    int m_nCurrentNumOfProperties = 0;
    QStringList m_strlTitles;

    void initializeVariables();
    void setupTableHeaders();
    QString m_strFileName;
    bool saveCSVFile();
    bool saveSqrFtFile();
    bool openSqrFtFile();
    bool importCSV(QString strFileName);
};

#endif // MAINCOMPARE_H
