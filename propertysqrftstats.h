#ifndef PROPERTYSQRFTSTATS_H
#define PROPERTYSQRFTSTATS_H

#include <QString>
#include "mattcalculations.h"


class PropertySqrftStats
{
public:
    PropertySqrftStats();

    void enterAddress(QString addr);
    void enterMLSNumber(QString MLSNum);

    void enterPropertyPrice(QString strPrice);
    void enterFinAboveSqrFt(int nFinAboveSqrFt);
    void enterFinBelowSqrFt(int nFinBelowSqrFt);
    void enterPercentPriceBelow(double dFromSlider );
    void enterRatioAboveToBelowPricePerSqrFt(double dRatio);

    void enterLotSize(int nLotSizeAcers);
    void enterLandAssess(int nLandAssess);



    QString getAddress();
    QString getMLSNumber();

    QString getPropertyPrice();
    QString getPriceTotAbove();
    QString getPriceTotBelow();

    int getFinAboveSqrFt();
    int getFinBelowSqrFt();

    QString getPricePerSqrFtTotal();
    QString getPricePerSqrFtAbove();
    QString getPricePerSqrFtBelow();

    QString getRatioAboveToBelowPricePerSqrFt();

    double getPercentPriceBelow();

    PropertySqrftStats& operator= (const PropertySqrftStats &source);


private:

    QString m_strAddress;
    QString m_strMLSNumber;

    int m_nPropertyPrice;
    int m_nPriceTotAbove;
    int m_nPriceTotBelow;

    int m_nFinAboveSqrFt;
    int m_nFinBelowSqrFt;
    double m_dPricePerSqrFtTotal;
    double m_dPricePerSqrFtAbove;
    double m_dPricePerSqrFtBelow;

    double m_dPercentPriceBelow;
    double m_dRatioAboveToBelowPricePerSqrFt;

    int m_nLotSizeAcers;
    int m_nLandAssess;
    int m_nTotalPrice;


    void calcPricePerSqrFtTotal();
    void calcPricePerSqrFtBelow();
    void calcPricePerSqrFtAbove();
    void calcRatioAboveToBelowPricePerSqrFt();
    void calcPriceAbove();
    void calcPriceBelow();

    void refreshData();

};

#endif // PROPERTYSQRFTSTATS_H
