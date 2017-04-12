#include "propertysqrftstats.h"

PropertySqrftStats::PropertySqrftStats()
{
     m_strAddress = "";
     m_strMLSNumber = "";

     m_nPropertyPrice = 0;
     m_nPriceTotAbove = 0;
     m_nPriceTotBelow = 0;

     m_nFinAboveSqrFt = 0;
     m_nFinBelowSqrFt = 0;
     m_dPricePerSqrFtTotal = 0;
     m_dPricePerSqrFtAbove = 0;
     m_dPricePerSqrFtBelow = 0;

     m_dPercentPriceBelow = .2;

     m_dRatioAboveToBelowPricePerSqrFt = 0;


     m_nLandAssess = 0;

}

void PropertySqrftStats::enterAddress(QString addr)
{
    m_strAddress = addr;
}
void PropertySqrftStats::enterMLSNumber(QString MLSNum)
{
    m_strMLSNumber = MLSNum;
}

void PropertySqrftStats::enterPropertyPrice(QString strPrice)
{
    m_nPropertyPrice = (usDollarsStringToDouble(strPrice));
    if (m_nPropertyPrice < 0)
        m_nPropertyPrice = 0;
    refreshData();
}
void PropertySqrftStats::enterFinAboveSqrFt(int nFinAboveSqrFt)
{
    m_nFinAboveSqrFt = nFinAboveSqrFt;
    refreshData();
}

void PropertySqrftStats::enterFinBelowSqrFt(int nFinBelowSqrFt)
{
    m_nFinBelowSqrFt = nFinBelowSqrFt;
    refreshData();
}
void PropertySqrftStats::enterPercentPriceBelow(double dFromSlider )
{
    double Temp = dFromSlider;
    m_dPercentPriceBelow = Temp/100;
    refreshData();
}
void PropertySqrftStats::enterRatioAboveToBelowPricePerSqrFt(double dRatio)  //      <=====================================<<<<
{
    m_dRatioAboveToBelowPricePerSqrFt = dRatio;
    if(! m_nPropertyPrice  <= 0)
    {
        double dPercentPriceBelow = (1/((((m_nFinAboveSqrFt*m_dRatioAboveToBelowPricePerSqrFt)/m_nFinBelowSqrFt))+1) ) ;
        enterPercentPriceBelow(dPercentPriceBelow * 100);
    }
    else
        m_dPercentPriceBelow = 0;
    refreshData();
}

void PropertySqrftStats::enterLotSize(int nLotSizeAcers)
{

}

void PropertySqrftStats::enterLandAssess(int nLandAssess)
{
    m_nLandAssess = nLandAssess;
    refreshData();
}

void PropertySqrftStats::enterTotalAssess(int nTotalAssess)
{
     m_nTotalAssess = nTotalAssess;
     refreshData();
}

void PropertySqrftStats::enterAdjustedPrice(int nAdjustedPrice)
{

}

void PropertySqrftStats::enterRatioLandToTotal(double dRatioLandToTotal)
{

}

void PropertySqrftStats::enterLotSizeAcres (double dLotSizeAcres)
{

}

QString PropertySqrftStats::getAddress()
{
    return m_strAddress;
}
QString PropertySqrftStats::getMLSNumber()
{
    return m_strMLSNumber;
}

QString PropertySqrftStats::getPropertyPrice()
{
    return doubleToCurrency (m_nPropertyPrice, US_DOLLARS);
}
QString PropertySqrftStats::getPriceTotAbove()
{

        return  doubleToCurrency(m_nPriceTotAbove, US_DOLLARS );

}
QString PropertySqrftStats::getPriceTotBelow()
{  
        return doubleToCurrency(m_nPriceTotBelow, US_DOLLARS);
}

int PropertySqrftStats::getFinAboveSqrFt()
{
    return m_nFinAboveSqrFt;
}
int PropertySqrftStats::getFinBelowSqrFt()
{
    return m_nFinBelowSqrFt;
}

QString PropertySqrftStats::getPricePerSqrFtTotal()
{

        return doubleToCurrency(m_dPricePerSqrFtTotal, US_DOLLARS );
}
QString PropertySqrftStats::getPricePerSqrFtAbove()
{   
    double dTemp = m_dPricePerSqrFtAbove;
    dTemp = roundDoubleToPoints(dTemp, 2);
    return doubleToCurrency(dTemp, US_DOLLARS);
}
QString PropertySqrftStats::getPricePerSqrFtBelow()
{        
    double dTemp =  m_dPricePerSqrFtBelow;
    dTemp = roundDoubleToPoints(dTemp, 2);
    return doubleToCurrency(dTemp, US_DOLLARS);
}
QString PropertySqrftStats::getRatioAboveToBelowPricePerSqrFt()
{
    double dTemp = roundDoubleToPoints ((m_dPricePerSqrFtAbove/m_dPricePerSqrFtBelow),2);
    if(dTemp > 10000 || dTemp < 0)
        return "---";

    return QString::number(dTemp,'g',10);
}

double PropertySqrftStats::getPercentPriceBelow()
{
    return (m_dPercentPriceBelow * 100 );
}

int PropertySqrftStats::getLandAssesses()
{
    return m_nLandAssess;
}

QString PropertySqrftStats::getAdjustedPropertyPrice()
{
    double dTemp = m_nAdjustedPrice;
    dTemp = roundDoubleToPoints(dTemp, 2);
    return doubleToCurrency(dTemp, US_DOLLARS);
}
QString PropertySqrftStats::getAdjustedPricePerSqrFtTotal()
{
    double dTemp =  m_dAdjustedPricePerSqrFtTotal;
    dTemp = roundDoubleToPoints(dTemp, 2);
    return doubleToCurrency(dTemp, US_DOLLARS);
}
QString PropertySqrftStats::getAdjustedPricePerSqrFtAbove()
{
    double dTemp =  m_dAdjustedPricePerSqrFtAbove;
    dTemp = roundDoubleToPoints(dTemp, 2);
    return doubleToCurrency(dTemp, US_DOLLARS);
}
QString PropertySqrftStats::getAdjustedPricePerSqrFtBelow()
{
    double dTemp =  m_dAdjustedPricePerSqrFtBelow;
    dTemp = roundDoubleToPoints(dTemp, 2);
    return doubleToCurrency(dTemp, US_DOLLARS);
}

//-------------------------------------------------------------

void PropertySqrftStats::calcAdjustedPrice()
{
    if(1)
    {
        //m_dRatioLandToTotal = (m_nLandAssess/m_nTotalAssess);
        m_nAdjustedPrice = m_nPropertyPrice - m_nLandAssess;
    }
    else
    {
        m_dRatioLandToTotal = 0;
        m_nAdjustedPrice = m_nPropertyPrice;
    }

}

void PropertySqrftStats::calcPricePerSqrFtTotal()
{
    if((m_nFinAboveSqrFt + m_nFinBelowSqrFt) > 0)
    {
        double dTempPricePerSqrFtTotal = static_cast<double>((((10*m_nPropertyPrice)/(m_nFinAboveSqrFt + m_nFinBelowSqrFt))+5)/10);
        m_dPricePerSqrFtTotal = static_cast<int>(dTempPricePerSqrFtTotal);
    }
    else
       m_dPricePerSqrFtTotal = 0;
}
void PropertySqrftStats::calcPricePerSqrFtBelow()
{
    if(m_nFinBelowSqrFt > 0)
        m_dPricePerSqrFtBelow = (m_nPropertyPrice*m_dPercentPriceBelow )/m_nFinBelowSqrFt;
    else {
        m_dPricePerSqrFtBelow = 0;
    }
}
void PropertySqrftStats::calcPricePerSqrFtAbove()
{
    if(m_nFinAboveSqrFt > 0)
        m_dPricePerSqrFtAbove = ((1 - m_dPercentPriceBelow)*m_nPropertyPrice)/m_nFinAboveSqrFt;
    else
        m_dPricePerSqrFtAbove = 0;
}
void PropertySqrftStats::calcRatioAboveToBelowPricePerSqrFt()
{
      if(m_dPricePerSqrFtBelow > 0)
          m_dRatioAboveToBelowPricePerSqrFt = m_dPricePerSqrFtAbove / m_dPricePerSqrFtBelow;
      else
            m_dRatioAboveToBelowPricePerSqrFt = 0;
}
void PropertySqrftStats::calcPriceAbove()
{
    m_nPriceTotAbove = (((m_nFinAboveSqrFt * m_dPricePerSqrFtAbove*10)+5)/10);
}
void PropertySqrftStats::calcPriceBelow()
{
    m_nPriceTotBelow = (m_dPricePerSqrFtBelow * m_nFinBelowSqrFt);
}
void PropertySqrftStats::calcAdjustedPricePerSqrFtTotal()
{
    if((m_nFinAboveSqrFt + m_nFinBelowSqrFt) > 0)
    {
        double dTempAdjPricePerSqrFtTotal = static_cast<double>((((10*m_nAdjustedPrice )/(m_nFinAboveSqrFt + m_nFinBelowSqrFt))+5)/10);
        m_dAdjustedPricePerSqrFtTotal = static_cast<int>(dTempAdjPricePerSqrFtTotal);
    }
    else
       m_dAdjustedPricePerSqrFtTotal = 0;
}
void PropertySqrftStats::calcAdjustedPricePerSqrFtBelow()
{
    if(m_nFinBelowSqrFt > 0)
        m_dAdjustedPricePerSqrFtBelow = (m_nAdjustedPrice*m_dPercentPriceBelow )/m_nFinBelowSqrFt;
    else {
        m_dAdjustedPricePerSqrFtBelow = 0;
    }
}
void PropertySqrftStats::calcAdjustedPricePerSqrFtAbove()
{
    if(m_nFinAboveSqrFt > 0)
        m_dAdjustedPricePerSqrFtAbove = ((1 - m_dPercentPriceBelow)*m_nAdjustedPrice )/m_nFinAboveSqrFt;
    else
        m_dAdjustedPricePerSqrFtAbove = 0;
}

//=============================================================

void PropertySqrftStats::refreshData()
{


     calcPricePerSqrFtTotal();
     calcPricePerSqrFtBelow();
     calcPricePerSqrFtAbove();

     calcPriceAbove();
     calcPriceBelow();

     calcAdjustedPrice();
     calcAdjustedPricePerSqrFtTotal();
     calcAdjustedPricePerSqrFtBelow();
     calcAdjustedPricePerSqrFtAbove();
}
PropertySqrftStats& PropertySqrftStats::operator= (const PropertySqrftStats &source)
{
    if(this==&source)
        return *this;
     m_strAddress = source.m_strAddress;
     m_strMLSNumber = source.m_strMLSNumber;

     m_nPropertyPrice = source.m_nPropertyPrice;
     m_nPriceTotAbove = source.m_nPriceTotAbove;
     m_nPriceTotBelow = source.m_nPriceTotBelow;

     m_nFinAboveSqrFt = source.m_nFinAboveSqrFt;
     m_nFinBelowSqrFt = source.m_nFinBelowSqrFt;
     m_dPricePerSqrFtTotal = source.m_dPricePerSqrFtTotal;
     m_dPricePerSqrFtAbove = source.m_dPricePerSqrFtAbove;
     m_dPricePerSqrFtBelow = source.m_dPricePerSqrFtBelow;

     m_dPercentPriceBelow = source.m_dPercentPriceBelow;
     m_dRatioAboveToBelowPricePerSqrFt = source.m_dRatioAboveToBelowPricePerSqrFt;

}
