#include "maincompare.h"
#include "ui_maincompare.h"




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
    int nTotalNumOfFields = NUM_OF_FIELDS;
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

        ui->tableWidget->setItem(nRow, ++nColumn, new QTableWidgetItem (  m_Property[nRow].getInfo().getPricePerSqrFtTotal() ));
        ui->tableWidget->setItem(nRow, ++nColumn, new QTableWidgetItem (  m_Property[nRow].getInfo().getPricePerSqrFtAbove() ));
        ui->tableWidget->setItem(nRow, ++nColumn, new QTableWidgetItem (  m_Property[nRow].getInfo().getPricePerSqrFtBelow() ));

        ui->tableWidget->setItem(nRow, ++nColumn, new QTableWidgetItem (  (m_Property[nRow].getInfo().getRatioAboveToBelowPricePerSqrFt()) ));
        ui->tableWidget->setItem(nRow, ++nColumn, new QTableWidgetItem (  QString::number(m_Property[nRow].getInfo().getPercentPriceBelow()) ));
        ui->tableWidget->setItem(nRow, ++nColumn, new QTableWidgetItem (  QString::number(100 - m_Property[nRow].getInfo().getPercentPriceBelow()) ));

        ui->tableWidget->setItem(nRow, ++nColumn, new QTableWidgetItem (  m_Property[nRow].getInfo().getPriceTotAbove() ));
        ui->tableWidget->setItem(nRow, ++nColumn, new QTableWidgetItem (  m_Property[nRow].getInfo().getPriceTotBelow()));

        ui->tableWidget->setItem(nRow, ++nColumn, new QTableWidgetItem (  m_Property[nRow].getInfo().getAdjustedPropertyPrice()));
        ui->tableWidget->setItem(nRow, ++nColumn, new QTableWidgetItem (  m_Property[nRow].getInfo().getAdjustedPricePerSqrFtTotal()));
        ui->tableWidget->setItem(nRow, ++nColumn, new QTableWidgetItem (  m_Property[nRow].getInfo().getAdjustedPricePerSqrFtAbove()));
        ui->tableWidget->setItem(nRow, ++nColumn, new QTableWidgetItem (  m_Property[nRow].getInfo().getAdjustedPricePerSqrFtBelow()));

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
           << "Price of Below"
           << "Price w/o Land"

           << "Adj Total Price/SqrFt"
           << "Adj Above Price/SqrFt"
           << "Adj Below Price/SqrFt"
              ;
}

void MainCompare::on_pushButton_2_clicked()
{
    setupTable();
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
        while (iii < NUM_OF_FIELDS)
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
                 <<  m_Property[jjj].getInfo().getPriceTotBelow().remove(',') << ","

                  << m_Property[jjj].getInfo().getAdjustedPropertyPrice().remove(',') << ","
                  << m_Property[jjj].getInfo().getAdjustedPricePerSqrFtTotal().remove(',') << ","
                  << m_Property[jjj].getInfo().getAdjustedPricePerSqrFtAbove().remove(',') << ","
                  << m_Property[jjj].getInfo().getAdjustedPricePerSqrFtBelow().remove(',')
                  << "\n";
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
        QString strVerNum = "1.2.1";
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
            outputData << x->getInfo().getLandAssesses();
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
    int nLandAssesses;


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
        if(strVerNum == "1.2.1")
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
                inputData >> nLandAssesses;

                m_Property[zzz].Home.enterAddress(strAddress);
                m_Property[zzz].Home.enterFinAboveSqrFt(nFinAboveSqrFt);
                m_Property[zzz].Home.enterFinBelowSqrFt(nFinBelowSqrFt);
                m_Property[zzz].Home.enterMLSNumber(strMLSNumber);
                m_Property[zzz].Home.enterPercentPriceBelow(dPercentPriceBelow);
                m_Property[zzz].Home.enterPropertyPrice(strPropertyPrice);
                m_Property[zzz].Home.enterLandAssess(nLandAssesses);
            }
            return true;
        }
        return false;
    }
}

bool MainCompare::importCSV(QString strFileName)
{
    QFile CSVFile(strFileName);
    if (!CSVFile.open(QIODevice::ReadOnly))
    {
        return false;
    }

    int nNumOfEntries = 0;
    QStringList strlFieldInfo[MAX_NUM_OF_PROPERTIES];
    while (!CSVFile.atEnd())
    {
        QString temp = CSVFile.readLine();
        temp = splitString(temp);
        temp.remove("\r\n");
        strlFieldInfo[nNumOfEntries].append(temp.split('|'));
        nNumOfEntries++;
    }

    int nNumberOfFields = 0;
    nNumberOfFields = strlFieldInfo[TITLE_LINE].count() ;

    int nLocationOfAddress = strlFieldInfo[TITLE_LINE].indexOf("Address");
    int nLocationOfAboveGradeSqFt = strlFieldInfo[TITLE_LINE].indexOf("Above Grade SqFt");
    int nLocationOfMLSNum = strlFieldInfo[TITLE_LINE].indexOf("MLS #");
    int nLocationOfSoldPrice = strlFieldInfo[TITLE_LINE].indexOf("Sold Price");
    int nLocationOfListPrice = strlFieldInfo[TITLE_LINE].indexOf("Price");
    int nLocationOfFinishedSqFt = strlFieldInfo[TITLE_LINE].indexOf("Finished SqFt");

    int nLocationOfLandAssess = strlFieldInfo[TITLE_LINE].indexOf("Land Assess");
    int nLocationOfLotSize = strlFieldInfo[TITLE_LINE].indexOf("Est. Total Acres");
    int nLocationOfTotalAssess = strlFieldInfo[TITLE_LINE].indexOf("Total Assess");

    if (nLocationOfAboveGradeSqFt > nNumberOfFields || nLocationOfAboveGradeSqFt <= 0)
    {
        nLocationOfAboveGradeSqFt = 0;
        return false;
    }
    if (nLocationOfFinishedSqFt > nNumberOfFields || nLocationOfFinishedSqFt <= 0)
    {
        nLocationOfFinishedSqFt = 0;
        return false;
    }

    m_nCurrentNumOfProperties = nNumOfEntries-1;
    nNumberOfFields = strlFieldInfo[TITLE_LINE].count() ;
    bool ok;
    for(int jjj = 1, III = 0; jjj < nNumOfEntries; jjj++, III++)
    {

            m_Property[III].Home.enterAddress(strlFieldInfo[jjj][nLocationOfAddress]);

            QString strAbove = strlFieldInfo[jjj][nLocationOfAboveGradeSqFt];
            int nAboveSqrFt;
            strAbove.remove(',');
            nAboveSqrFt = strAbove.toInt(&ok, 10);
            m_Property[III].Home.enterFinAboveSqrFt(nAboveSqrFt);

            QString strTotSqrFt = strlFieldInfo[jjj][nLocationOfFinishedSqFt];
            strTotSqrFt.remove(',');
            int nTotSqrFt = strTotSqrFt.toInt(&ok, 10);
            int nBelowSqrFt = nTotSqrFt - nAboveSqrFt;
            if (nBelowSqrFt < 0)
                return false;
            m_Property[III].Home.enterFinBelowSqrFt(nBelowSqrFt);

            m_Property[III].Home.enterMLSNumber(strlFieldInfo[jjj][nLocationOfMLSNum]);

            QString strLandAssess = strlFieldInfo[jjj][nLocationOfLandAssess];
            strLandAssess.remove(',');
            int nLandAssess = strLandAssess.toInt(&ok, 10);
            m_Property[III].Home.enterLandAssess(nLandAssess);

            if(usDollarsStringToDouble(strlFieldInfo[jjj][nLocationOfSoldPrice]) < .5)
                m_Property[III].Home.enterPropertyPrice(strlFieldInfo[jjj][nLocationOfListPrice]);
            else
                m_Property[III].Home.enterPropertyPrice(strlFieldInfo[jjj][nLocationOfSoldPrice]);

            //set the default ratio to 5x
            double dRatio = 5.0;
            m_Property[III].Home.enterRatioAboveToBelowPricePerSqrFt(dRatio);


//            if(!ok)
//            {
//                QMessageBox openStatus;
//                openStatus.setWindowTitle("");
//                    openStatus.setText("Conversion failed!");
//                openStatus.exec();
//            }
            m_Property[III].refreshFields();
    }
    return true;
}

void MainCompare::on_actionDelete_Selected_triggered()
{
    if(m_nCurrentNumOfProperties > 0)
    {
        int nPropertyToDelete;
        if(nPropertyToDelete == (MAX_NUM_OF_PROPERTIES - 1))
                return;
        nPropertyToDelete = ui->tableWidget->currentRow();
        for(int iii = nPropertyToDelete; iii < m_nCurrentNumOfProperties; iii++)
        {
            m_Property[iii].Home = m_Property[(iii+1)].Home;
            m_Property[iii].refreshFields();
            m_Property[(iii+1)].refreshFields();
        }
        m_nCurrentNumOfProperties--;
        setupTable();
    }
}

void MainCompare::on_actionImport_Paragon_CSV_triggered()
{
    {
        {
            QString FileName = QFileDialog::getOpenFileName (this, tr("Import .csv File"), "",tr("*.csv"));

            bool ok = false;
            QMessageBox openStatus;
            openStatus.setWindowTitle("");
            ok = importCSV(FileName);
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
    }
}
void MainCompare::swapProp(int nPropA, int nPropB)
{
    if(        nPropA != nPropB
            && nPropA > 0
            && nPropB > 0
            && nPropA < MAX_NUM_OF_PROPERTIES
            && nPropB < MAX_NUM_OF_PROPERTIES)
    {
        PropertySqrftStats cTemp;
        cTemp = m_Property[nPropA].Home;
        m_Property[nPropA].Home = m_Property[nPropB].Home;
        m_Property[nPropB].Home = cTemp;
    }
}
