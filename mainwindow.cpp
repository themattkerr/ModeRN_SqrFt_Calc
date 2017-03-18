#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_horizontalSlider_valueChanged(int value)
{

    //ui->spinboxBelow ->setValue(value);
    //ui->spinAbove->setValue(100-value);
    Home.enterPercentPriceBelow((value/10));
    refreshFields();
}

void MainWindow::on_lineAddr_textChanged(const QString &arg1)
{
    Home.enterAddress(arg1);
    refreshFields();
}

void MainWindow::on_lineMLSNum_textChanged(const QString &arg1)
{
    Home.enterMLSNumber(arg1);
    refreshFields();
}

void MainWindow::on_linePrice_textChanged(const QString &arg1)
{
    Home.enterPropertyPrice(arg1);
    refreshFields();
}


//void MainWindow::on_lineAbove_textChanged(const QString &arg1)
//{
//    bool *ok =0;
//    Home.enterFinAboveSqrFt(arg1.toInt(ok,10));
//    refreshFields();
//}

//void MainWindow::on_lineBelow_textChanged(const QString &arg1)
//{
//    bool *ok =0;
//    Home.enterFinBelowSqrFt(arg1.toInt(ok,10));
//    refreshFields();
//}
void MainWindow::refreshFields(){
    int nCorrectionFactor = 1;

    ui->lineAddr->setText(Home.getAddress());

    ui->lineMLSNum->setText( Home.getMLSNumber());
    ui->linePrice->setText(Home.getPropertyPrice());

    ui->spinBoxFinAbove->setValue(Home.getFinAboveSqrFt());
    ui->spinBoxFinBelow->setValue(Home.getFinBelowSqrFt());
    ui->label_TotSqrFt->setText(QString::number((Home.getFinAboveSqrFt()+Home.getFinBelowSqrFt()),10));
    ui->tot_Cost_Per_Sqr_Ft_Label->setText(Home.getPricePerSqrFtTotal());

    ui->horizontalSlider->setValue((Home.getPercentPriceBelow()*10));

    ui->label_RatioPriceAboveToBelow->setText(Home.getRatioAboveToBelowPricePerSqrFt());

    ui->label_BelowPercent->setText(QString::number(static_cast<int>(Home.getPercentPriceBelow()), 10));
    ui->label_AbovePercent->setText((QString::number((static_cast<int>(100-Home.getPercentPriceBelow())),10)));


    ui->cost_Per_Below_SqrFt_Label->setText(Home.getPricePerSqrFtBelow());
    ui->cost_per_above_sqr_ft->setText(Home.getPricePerSqrFtAbove());

    ui->cost_Below_Label->setText(Home.getPriceTotBelow());
    ui->cost_Above_Label->setText(Home.getPriceTotAbove());



}

void MainWindow::on_spinBoxFinAbove_valueChanged(int arg1)
{
    Home.enterFinAboveSqrFt(arg1);
    refreshFields();
}

void MainWindow::on_spinBoxFinBelow_valueChanged(int arg1)
{
    Home.enterFinBelowSqrFt(arg1);
    refreshFields();
}
