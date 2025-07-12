#include <QtTest>
#include <QTemporaryFile>
#include <QTextStream>
#include "mainwindow.h"

class TestReadFileFunc : public QObject {
    Q_OBJECT

private slots:
    void initTestCase() {
        MainWindow::sizeEnd = 0;
    }

    void testEmptyFile() {
        QTemporaryFile tmp;
        QVERIFY(tmp.open());
        tmp.close();

        MainWindow mw;
        QVERIFY(mw.ReadFileFunc(tmp.fileName()));
        QCOMPARE(MainWindow::sizeEnd, 0);
        QCOMPARE(mw.cars.size, 0);
    }

    void testValidFile() {
        QTemporaryFile tmp;
        QVERIFY(tmp.open());
        QTextStream out(&tmp);
        out << "Ford 120 15000.00\n"
               "Tesla 200 50000.50\n";
        tmp.close();

        MainWindow mw;
        QVERIFY(mw.ReadFileFunc(tmp.fileName()));

        QCOMPARE(MainWindow::sizeEnd, 2);
        QCOMPARE(mw.cars.size,      2);

        QCOMPARE(mw.cars[0].model, QString("Ford"));
        QCOMPARE(mw.cars[0].speed, qint8(120));
        QCOMPARE(mw.cars[0].price, qreal(15000.00));

        QCOMPARE(mw.cars[1].model, QString("Tesla"));
        QCOMPARE(mw.cars[1].speed, qint8(200));
        QCOMPARE(mw.cars[1].price, qreal(50000.50));
    }
};

QTEST_MAIN(TestReadFileFunc)
#include "test_readfile.moc"
