/*#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextImageFormat>
#include <QMessageBox>
#include <QString>
#include <QFile>
#include <QStringListModel>
#include <QInputDialog>
#include <QStringList>
#include <utility>
#include <QKeyEvent>
#include <QContextMenuEvent>
#include <QMenu>
#include <QAction>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    bool ReadFileFunc(const QString&);
private slots:

    void on_arrSizeButt_clicked();

    void on_readFileButt_clicked();

    void on_readFileButtPath_clicked();

    void on_FIleArrSizeButt_clicked();

    void on_readSizeFileButt_clicked();

    void on_OpenTabButt_clicked();

    void on_OpenListButt_clicked();

    void on_defSortButt_clicked();

    void on_mySortButt_clicked();

    void on_AddListWidgButt_clicked();

    void on_DelListWidgButt_clicked();

    void on_addTableElemButt_clicked();

    void on_delTableElemButt_clicked();

    void keyPressEvent(QKeyEvent *event);

    void contextMenuEvent(QContextMenuEvent* event);
private:

    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H*/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "cars.h"
#include <QTextImageFormat>
#include <QMessageBox>
#include <QString>
#include <QFile>
#include <QStringListModel>
#include <QInputDialog>
#include <QStringList>
#include <utility>
#include <QKeyEvent>
#include <QContextMenuEvent>
#include <QMenu>
#include <QAction>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class TestReadFileFunc;

class MainWindow : public QMainWindow
{
    Q_OBJECT

    friend class TestReadFileFunc;

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();



private slots:

    void on_arrSizeButt_clicked();

    void on_readFileButt_clicked();

    void on_readFileButtPath_clicked();

    void on_FIleArrSizeButt_clicked();

    void on_readSizeFileButt_clicked();

    void on_OpenTabButt_clicked();

    void on_OpenListButt_clicked();

    void on_defSortButt_clicked();

    void on_mySortButt_clicked();

    void on_AddListWidgButt_clicked();

    void on_DelListWidgButt_clicked();

    void on_addTableElemButt_clicked();

    void on_delTableElemButt_clicked();

    void keyPressEvent(QKeyEvent *event) override;

    void contextMenuEvent(QContextMenuEvent* event) override;
private:
    Ui::MainWindow *ui;
    bool ReadFileFunc(const QString &filename);
    Cars cars;
    static int sizeEnd;
};

#endif // MAINWINDOW_H

