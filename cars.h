#ifndef CARS_H
#define CARS_H
#include <QString>
#include <QTextStream>
#include <QList>
#include <QStringList>

struct CarInfo;

class TestReadFileFunc;

class Cars
{
    friend class TestReadFileFunc;
    int size;
    CarInfo *arr;
public:
    Cars();
    Cars(int);
    Cars(const Cars&&);
    Cars(Cars&&);
    ~Cars();

    Cars& operator= (const Cars&);
    Cars& operator= (Cars&&);
    CarInfo& operator[] (int);
    const CarInfo& operator [](int) const;

    CarInfo* data() { return arr; }
    const CarInfo* data() const { return arr; }
};

struct CarInfo{
    QString model;
    qint8 speed;
    qreal price;
    friend QTextStream& operator>>(QTextStream&, CarInfo&);
    friend QTextStream& operator <<(QTextStream&, CarInfo&);
    bool operator==(const CarInfo&);
};

#endif // CARS_H
