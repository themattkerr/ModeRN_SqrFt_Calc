#include "maincompare.h"
#include "ui_maincompare.h"

#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>


MainCompare::MainCompare(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainCompare)
{
    ui->setupUi(this);
    setupTableHeaders();
    setupTable();
}

MainCompare::~MainCompare()
{
    //on_pushButton_2_clicked();
    delete ui;
}

void MainCompare::on_pushButton_AddProperty_clicked()
{
    m_nCurrentNumOfProperties++;
    if(m_nCurrentNumOfProperties > 0)
        m_Property[m_nCurrentNumOfProperties-1].show();
    setupTable();
}

void MainCompare::setupTable()
{
    int nTotalNumOfFields = 14;
    int nColumn = 0;
    ui->tableWidget->setColumnCount(nTotalNumOfFields);
    ui->tableWidget->setRowCount(m_nCurrentNumOfProperties);
    for(int nRow = 0; nRow <= m_nCurrentNumOfProperties; nRow++)
    {
        nColumn = 0;
        ui->tableWidget->setHorizontalHeaderLabels(m_strlTitles);
        ui->tableWidget->setItem(nRow, nColumn, new QTableWidgetItem   (  m_Property[nRow].getInfo().getAddress()));
        ui->tableWidget->setItem(nRow, ++nColumn, new QTableWidgetItem (  m_Property[nRow].getInfo().getMLSNumber() ));
        ui->tableWidget->setItem(nRow, ++nColumn, new QTableWidgetItem (  m_Property[nRow].getInfo().getPropertyPrice() ));

        ui->tableWidget->setItem(nRow, ++nColumn, new QTableWidgetItem (  QString::number(m_Property[nRow].getInfo().getFinAboveSqrFt() + m_Property[nRow].getInfo().getFinBelowSqrFt()) ));
        ui->tableWidget->setItem(nRow, ++nColumn, new QTableWidgetItem (  QString::number(m_Property[nRow].getInfo().getFinAboveSqrFt()) ));
        ui->tableWidget->setItem(nRow, ++nColumn, new QTableWidgetItem (  QString::number(m_Property[nRow].getInfo().getFinBelowSqrFt()) ));
        // need total sqrftg
        ui->tableWidget->setItem(nRow, ++nColumn, new QTableWidgetItem (  m_Property[nRow].getInfo().getPricePerSqrFtTotal() ));
        ui->tableWidget->setItem(nRow, ++nColumn, new QTableWidgetItem (  m_Property[nRow].getInfo().getPricePerSqrFtAbove() ));
        ui->tableWidget->setItem(nRow, ++nColumn, new QTableWidgetItem (  m_Property[nRow].getInfo().getPricePerSqrFtBelow() ));

        ui->tableWidget->setItem(nRow, ++nColumn, new QTableWidgetItem (  (m_Property[nRow].getInfo().getRatioAboveToBelowPricePerSqrFt()) ));
        ui->tableWidget->setItem(nRow, ++nColumn, new QTableWidgetItem (  QString::number(m_Property[nRow].getInfo().getPercentPriceBelow()) ));
        ui->tableWidget->setItem(nRow, ++nColumn, new QTableWidgetItem (  QString::number(100 - m_Property[nRow].getInfo().getPercentPriceBelow()) ));

        ui->tableWidget->setItem(nRow, ++nColumn, new QTableWidgetItem (  m_Property[nRow].getInfo().getPriceTotAbove() ));
        ui->tableWidget->setItem(nRow, ++nColumn,new QTableWidgetItem ( m_Property[nRow].getInfo().getPriceTotBelow()));
    }
}

void MainCompare::initializeVariables()

{
    for(int iii = 0; iii < MAX_NUM_OF_PROPERTIES; iii++)
    {
        m_Property[iii].getInfo().getAddress();
    }
}

void MainCompare::on_tableWidget_cellDoubleClicked(int row, int column)
{
    m_Property[row].refreshFields();
    m_Property[row].show();
}

void MainCompare::on_pushButton_clicked()
{
    setupTable();
}
void MainCompare::refreshTable()
{
    setupTable();
}
void MainCompare::setupTableHeaders()
{
m_strlTitles
           << "Address"
           << "MLS Number"
           << "Property Price"

           << "Total Finished SqrFt"
           << "Finished Above"
           << "Finished Below"

           << "Total Price/SqrFt"
           << "Above Price/SqrFt"
           << "Below Price/SqrFt"

           << "Ratio Price/SqrFt Above to Below"
           << "% Price Below"
           << "% Price Above"
           << "Price of Above"
           << "Price of Below";
}

void MainCompare::on_pushButton_2_clicked()
{
    for (int iii = 0; iii < MAX_NUM_OF_PROPERTIES; iii++)
        m_Property[iii].close();
}

void MainCompare::on_actionExport_CSV_triggered()
{
        m_strFileName = QFileDialog::getSaveFileName (this, tr("Save As CSV File"), "",tr( "*.csv"));

                bool ok;
                QMessageBox SaveStatus;
                SaveStatus.setWindowTitle("");
                ok = saveCSVFile();
                if(ok)
                {
                    SaveStatus.setText("Save Successful!");
                }
                else
                {
                    SaveStatus.setText("File NOT saved.");
                }
                SaveStatus.exec();
                SaveStatus.raise();
}

bool MainCompare::saveCSVFile()
{
    QFile CSV(m_strFileName);
    if (CSV.open(QIODevice::ReadWrite | QIODevice::Truncate))
    {
        QTextStream stream(&CSV);
        int iii = 0;
        while (iii < 14)
        {
            stream << m_strlTitles[iii];
            stream << ",";
            iii++;
        }
        stream << "\n";

        for (int jjj=0;jjj<m_nCurrentNumOfProperties ;jjj++)
        {
                stream
                 <<  m_Property[jjj].getInfo().getAddress() << ","
                 <<  m_Property[jjj].getInfo().getMLSNumber() << ","
                 <<  m_Property[jjj].getInfo().getPropertyPrice().remove(',') << ","

                 <<  QString::number(m_Property[jjj].getInfo().getFinAboveSqrFt() + m_Property[jjj].getInfo().getFinBelowSqrFt() )   << ","
                 <<  QString::number(m_Property[jjj].getInfo().getFinAboveSqrFt())<< ","
                 <<  QString::number(m_Property[jjj].getInfo().getFinBelowSqrFt()) << ","

                 <<  m_Property[jjj].getInfo().getPricePerSqrFtTotal().remove(',') << ","
                 <<  m_Property[jjj].getInfo().getPricePerSqrFtAbove().remove(',') << ","
                 <<  m_Property[jjj].getInfo().getPricePerSqrFtBelow().remove(',') << ","

                 <<  (m_Property[jjj].getInfo().getRatioAboveToBelowPricePerSqrFt())<< ","
                 <<  QString::number(m_Property[jjj].getInfo().getPercentPriceBelow()) << ","
                 <<  QString::number(100 - m_Property[jjj].getInfo().getPercentPriceBelow()) << ","

                 <<  m_Property[jjj].getInfo().getPriceTotAbove().remove(',') << ","
                 <<  m_Property[jjj].getInfo().getPriceTotBelow().remove(',')  << "\n";
        }
        return true;
    }
return false;
}

void MainCompare::on_actionSave_As_triggered()
{
    m_strFileName = QFileDialog::getSaveFileName (this, tr("Save As SqrFt File"), "",tr( "*.SFC"));

            bool ok;
            QMessageBox SaveStatus;
            SaveStatus.setWindowTitle("");
            ok = saveSqrFtFile();
            if(ok)
            {
                SaveStatus.setText("Save Successful!");
            }
            else
            {
                SaveStatus.setText("File NOT saved.");
            }
            SaveStatus.exec();
            SaveStatus.raise();
}

bool MainCompare::saveSqrFtFile()
{

    QFile SaveFile(m_strFileName);
    if (SaveFile.open(QIODevice::ReadWrite | QIODevice::Truncate))
    {
        QDataStream outputData(&SaveFile);
        MainWindow *x = 0;
        QString strVerNum = "1.0.0";
        outputData <<  strVerNum;
        outputData << m_nCurrentNumOfProperties;
        for(int iii = 0; iii < MAX_NUM_OF_PROPERTIES; iii++)
        {
            x = &m_Property[iii];
            outputData << x->getInfo().getAddress();
            outputData << x->getInfo().getFinAboveSqrFt();
            outputData << x->getInfo().getFinBelowSqrFt();
            outputData << x->getInfo().getMLSNumber();
            outputData << x->getInfo().getPercentPriceBelow();
            outputData << x->getInfo().getPropertyPrice();
        }
        return true;
    }
    return false;
}

void MainCompare::on_actionSave_triggered()
{
    if(m_strFileName == "" || m_strFileName.contains(".csv") )
        on_actionOpen_triggered();
    saveSqrFtFile();
}

void MainCompare::on_actionOpen_triggered()
{


        m_strFileName = QFileDialog::getOpenFileName (this, tr("Open SqrFt File"), "",tr("*.SFC"));

        bool ok;
        QMessageBox openStatus;
        openStatus.setWindowTitle("");
        ok = openSqrFtFile();
        setupTable();
        if(ok)
        {
            openStatus.setText("Open Successful!");
        }
        else
        {
            openStatus.setText("Open Failed!!!");
        }
        openStatus.exec();

}

bool MainCompare::openSqrFtFile()
{
    QString strVerNum;
    int nCurrentNumOfProperties;

    QString strAddress;
    QString strMLSNumber;
    QString strPropertyPrice;

    int nFinAboveSqrFt;
    int nFinBelowSqrFt;
    double dPercentPriceBelow;


    QFile ReadFile(m_strFileName);
    if (ReadFile.open(QIODevice::ReadOnly | QIODevice::Truncate))
    {
        QDataStream inputData(&ReadFile);
        inputData >> strVerNum;
        if(strVerNum == "1.0.0")
        {
            inputData >> nCurrentNumOfProperties;
            m_nCurrentNumOfProperties = nCurrentNumOfProperties;
            for(int zzz=0 ; zzz < MAX_NUM_OF_PROPERTIES ; zzz++)
            {
                inputData >> strAddress;
                inputData >> nFinAboveSqrFt;
                inputData >> nFinBelowSqrFt;
                inputData >> strMLSNumber;
                inputData >> dPercentPriceBelow;
                inputData >> strPropertyPrice;

                m_Property[zzz].Home.enterAddress(strAddress);
                m_Property[zzz].Home.enterFinAboveSqrFt(nFinAboveSqrFt);
                m_Property[zzz].Home.enterFinBelowSqrFt(nFinBelowSqrFt);
                m_Property[zzz].Home.enterMLSNumber(strMLSNumber);
                m_Property[zzz].Home.enterPercentPriceBelow(dPercentPriceBelow);
                m_Property[zzz].Home.enterPropertyPrice(strPropertyPrice);
            }
            return true;
        }
        return false;
    }
}

