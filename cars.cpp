#include "cars.h"
Cars::Cars() : size(0), arr(nullptr){};
Cars::Cars(int n) : size(n) {
    arr = new CarInfo[size];
}
Cars::Cars(const Cars && copy) : size(copy.size) {
    arr = new CarInfo[size];
    for (int i = 0; i < 0; i++) {
        arr[i] = copy.arr[i];
    }
}
Cars::Cars(Cars && move) : size(move.size), arr(move.arr) {
    move.arr = nullptr;
    move.size = 0;
}
Cars::~Cars() {
    delete[] arr;
}

Cars& Cars::operator=(const Cars& obj) {
    if (this != &obj) {
        delete[] arr;
        size = obj.size;
        arr = new CarInfo[size];
        for (int i = 0; i < size; i++) {
            arr[i] = obj.arr[i];
        }
    }
    return *this;
}
Cars& Cars::operator=(Cars&& obj) {
    if (this != &obj) {
        delete[] arr;
        size = obj.size;
        arr = obj.arr;
        obj.arr = nullptr;
        obj.size = 0;
    }
    return *this;
}
CarInfo& Cars::operator [] (int index){
    return arr[index];
}
const CarInfo& Cars::operator [] (int index) const {
    return arr[index];
}

QTextStream& operator>>(QTextStream& in, CarInfo& obj) {
    QString str;
    str = in.readLine();
    QStringList parts = str.split(' ');
    if (parts.size() == 3) {
        obj.model = parts[0];
        obj.speed = parts[1].toInt();
        obj.price = parts[2].toDouble();
    }
    if (parts.size() == 4) {
        obj.model = parts[0] + parts[1];
        obj.speed = parts[2].toInt();
        obj.price = parts[3].toDouble();
    }
    if (parts.size() == 5) {
        obj.model = parts[0] + parts[1] + parts[2];
        obj.speed = parts[3].toInt();
        obj.price = parts[4].toDouble();
    }
    return in;
};
QTextStream& operator<< (QTextStream& out, CarInfo& obj) {
    out << obj.model << obj.speed << obj.price;
    return out;
}
bool CarInfo::operator==(const CarInfo& obj) {
    return (model == obj.model);
}
