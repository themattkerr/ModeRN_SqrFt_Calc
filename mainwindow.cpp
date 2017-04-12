#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "maincompare.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowFlags(Qt::WindowStaysOnTopHint);
    ui->horizontalSlider->setValue(static_cast<int>(Home.getPercentPriceBelow()*10));
    //temp = parent;
    refreshFields();

}

MainWindow::~MainWindow()
{

    delete ui;
}


PropertySqrftStats MainWindow::getInfo()
{
    return Home;
}

void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    double dTemp = value;
    Home.enterPercentPriceBelow(dTemp/10);
//        ((MainWindow*)parentWidget())->setupTable();
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



void MainWindow::refreshFields()
{

    //((MainCompare*)parentWidget())->setupTable();
    ui->horizontalSlider->setValue(static_cast<int>((Home.getPercentPriceBelow()*10)+.5));

    ui->lineAddr->setText(Home.getAddress());

    ui->lineMLSNum->setText( Home.getMLSNumber());
    ui->linePrice->setText(Home.getPropertyPrice());

    ui->spinBoxFinAbove->setValue(Home.getFinAboveSqrFt());
    ui->spinBoxFinBelow->setValue(Home.getFinBelowSqrFt());
    ui->label_TotSqrFt->setText(QString::number((Home.getFinAboveSqrFt()+Home.getFinBelowSqrFt()),10));


    ui->tot_Cost_Per_Sqr_Ft_Label->setText(Home.getPricePerSqrFtTotal());

    ui->label_RatioPriceAboveToBelow->setText(Home.getRatioAboveToBelowPricePerSqrFt());

    ui->label_BelowPercent->setText(QString::number(/*static_cast<int>*/(Home.getPercentPriceBelow()),'g', 6));
    ui->label_AbovePercent->setText((QString::number(/*(static_cast<int>*/(100-Home.getPercentPriceBelow()),'g',6)));

    ui->cost_Per_Below_SqrFt_Label->setText(Home.getPricePerSqrFtBelow());
    ui->cost_per_above_sqr_ft->setText(Home.getPricePerSqrFtAbove());

    ui->cost_Below_Label->setText(Home.getPriceTotBelow());
    ui->cost_Above_Label->setText(Home.getPriceTotAbove());

    ui->label_AdjPricePerSqrFtAbove->setText(Home.getAdjustedPricePerSqrFtAbove());
    ui->label_AdjPricePerSqrFtBelow->setText(Home.getAdjustedPricePerSqrFtBelow());

    ui->label_AdjPricePerSqrFtTot->setText(Home.getAdjustedPricePerSqrFtTotal());
    ui->lineEdit_LandAssesses->setText(doubleToCurrency(Home.getLandAssesses(),US_DOLLARS));

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

void MainWindow::on_lineEdit_LandAssesses_editingFinished()
{
        int nTempLandAssesses = usDollarsStringToDouble(ui->lineEdit_LandAssesses->text());
        Home.enterLandAssess(nTempLandAssesses);
        refreshFields();
}
