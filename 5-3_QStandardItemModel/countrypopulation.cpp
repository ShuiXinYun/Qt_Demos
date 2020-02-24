#include "countrypopulation.h"

CountryPopulation::CountryPopulation()
{
    rank = 0;
    country_name = "";
    population = 0;
    date = "";
    percent = 0.0;
}

CountryPopulation::CountryPopulation(int rank, const QString &countryname, long long population, const QString &date, double percent)
{
    this->rank = rank;
    this->country_name = countryname;
    this->population = population;
    this->date = date;
    this->percent = percent;
}

QDataStream& operator<<(QDataStream& data_stream, const CountryPopulation& cp)
{
    data_stream<<cp.rank;
    data_stream<<cp.country_name;
    data_stream<<cp.population;
    data_stream<<cp.date;
    data_stream<<cp.percent;
    return data_stream;
}

QDataStream& operator>>(QDataStream& data_stream, CountryPopulation& cp)
{
    data_stream>>cp.rank;
    data_stream>>cp.country_name;
    data_stream>>cp.population;
    data_stream>>cp.date;
    data_stream>>cp.percent;
    return data_stream;
}
