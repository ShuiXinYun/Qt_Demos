#ifndef COUNTRYPOPULATION_H
#define COUNTRYPOPULATION_H
#include <QtCore>

const int HEADERSIZE=5;

class CountryPopulation
{
public:
    int rank;
    QString country_name;
    long long population;
    QString date;
    double percent;
    CountryPopulation();
    CountryPopulation(int rank, const QString &countryname, long long population, const QString& date, double percent);
};

QDataStream& operator<<(QDataStream&, const CountryPopulation&);
QDataStream& operator>>(QDataStream&, CountryPopulation&);


#endif // COUNTRYPOPULATION_H
