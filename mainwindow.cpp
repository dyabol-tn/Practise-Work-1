//C:\Users\qt\Documents\PracticeWork1\cars.txt

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <cars.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);

    QPixmap pic(":/images/StartCar.png");
    ui->imageLabel->setPixmap(pic);
    ui->imageLabel->setScaledContents(true);

}

MainWindow::~MainWindow()
{
    delete ui;
}

int MainWindow::sizeEnd = 0;
bool MainWindow::ReadFileFunc(const QString &filename)
{
    QFile filein(filename);
    if (!filein.exists()) {
        QMessageBox::warning(this, "Ошибка", "Файл не найден");
        return false;
    }
    if (!filein.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Ошибка", "Не удалось открыть файл");
        return false;
    }

    QTextStream in(&filein);
    QList<CarInfo> tempList;
    while (!in.atEnd()) {
        CarInfo car;
        in >> car;
        if (!car.model.isEmpty())
            tempList.append(car);
    }
    filein.close();

    int count = 0;
    if (sizeEnd > 0 && tempList.size() >= sizeEnd) {
        count = sizeEnd;
    } else {
        count = tempList.size();
    }

    Cars newCars(count);
    for (int i = 0; i < count; ++i) {
        newCars[i] = tempList.at(i);
    }

    cars    = std::move(newCars);
    sizeEnd = count;

    return true;
}

void MainWindow::on_arrSizeButt_clicked()
{
    bool check;
    int size;
    QString sizeStr = ui->ArrSizeLineEdit->text();
    size = sizeStr.toInt(&check);
    if (size >= 0) {
        if (check) {
            sizeEnd = size;
            QMessageBox::information(this, "Размер массива", "Введенный размер массива успешно сохранен.");
        }
        else {
            QMessageBox::warning(this, "Ошибка", "Проверьте введенные данные.");
        }
    }
    else {
        QMessageBox::warning(this, "Ошибка", "Некорректный размер массива.");
    }
}


void MainWindow::on_readFileButt_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
}


void MainWindow::on_readFileButtPath_clicked()
{
    QString name = ui->readFileLineEdit->text();

    bool success = ReadFileFunc(name);

    if (success) {
        QMessageBox::information(this, "Результат выполнения", "Файл успешно загружен.");

        QStringList list;
        for (int i = 0; i < sizeEnd; ++i) {
            QString text = QString("%1 | Скорость: %2 км/ч | Цена: $%3")
                               .arg(cars[i].model)
                               .arg(cars[i].speed)
                               .arg(cars[i].price, 0, 'f', 2);

            list << text;
        }

        QStringListModel* model = new QStringListModel(this);
        model->setStringList(list);
        ui->FileListView->setModel(model);
    }
}


void MainWindow::on_FIleArrSizeButt_clicked()
{
    QString str = QString::number(sizeEnd);
    ui->arrSizeTextEdit->setText(str);
    ui->stackedWidget->setCurrentIndex(5);
}


void MainWindow::on_readSizeFileButt_clicked()
{
    QString name = ui->readSizeFileLineEdit->text();

    bool success = ReadFileFunc(name);

    if (success) {
        QMessageBox::information(this, "Результат выполнения", "Выполнено успешно.");
    }

    QString str = QString::number(sizeEnd);
    ui->arrSizeTextEdit->setText(str);
}



void MainWindow::on_OpenTabButt_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
    ui->tableWidget->setRowCount(sizeEnd);
    for (int i = 0; i < sizeEnd; i++) {
        ui->tableWidget->setItem(i, 0, new QTableWidgetItem(cars[i].model));
        ui->tableWidget->setItem(i, 1, new QTableWidgetItem(QString::number(cars[i].speed)));
        ui->tableWidget->setItem(i, 2, new QTableWidgetItem(QString::number(cars[i].price)));
    }
}


void MainWindow::on_OpenListButt_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
    ui->listWidget->clear();

    for (int i = 0; i < sizeEnd; ++i) {
        QString itemText = QString("%1 | Скорость: %2 км/ч | Цена: $%3")
                               .arg(cars[i].model)
                               .arg(cars[i].speed)
                               .arg(cars[i].price, 0, 'f', 2);

        ui->listWidget->addItem(itemText);
    }
}


void MainWindow::on_defSortButt_clicked()
{
    if (ui->FileListView->model() && ui->FileListView->model()->rowCount() != 0) {
        ui->listWidget->sortItems(Qt::AscendingOrder);
        QMessageBox::information(this, "Результат выполнения", "Выполнено успешно.");
    }
    else {
        QMessageBox::warning(this, "Внимание", "Ошибка сортировки.");
    }
}


void MainWindow::on_mySortButt_clicked()
{
    if (ui->FileListView->model() && ui->FileListView->model()->rowCount() != 0) {
        if (sizeEnd == 0) return;

        std::sort(cars.data(), cars.data() + sizeEnd,
                  [](const CarInfo& a, const CarInfo& b) {
                      return a.model < b.model;
                  });

        QString key = QInputDialog::getText(this, "Поиск модели", "Введите модель:");
        if (key.isEmpty()) return;

        int left = 0, right = sizeEnd - 1;
        int foundIndex = -1;

        while (left <= right) {
            int mid = (left + right) / 2;
            if (cars[mid].model == key) {
                foundIndex = mid;
                break;
            } else if (cars[mid].model < key) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }

        if (foundIndex != -1) {
            QMessageBox::information(this, "Результат",
                                     QString("Найдена модель: %1 (скорость: %2, цена: $%3)")
                                         .arg(cars[foundIndex].model)
                                         .arg(cars[foundIndex].speed)
                                         .arg(cars[foundIndex].price));

            for (int i = 0; i < ui->listWidget->count(); ++i) {
                if (ui->listWidget->item(i)->text().contains(cars[foundIndex].model)) {
                    ui->listWidget->setCurrentRow(i);
                    break;
                }
            }
        } else {
            QMessageBox::warning(this, "Поиск", "Модель не найдена.");
        }
    }
    else {
        QMessageBox::warning(this, "Внимание", "Ошибка бинарного поиска.");
    }
}


void MainWindow::on_AddListWidgButt_clicked()
{
    QString model = QInputDialog::getText(this, "Новая модель", "Введите модель автомобиля:");
    if (model.isEmpty()) return;

    int speed = QInputDialog::getInt(this, "Скорость", "Введите скорость (км/ч):", 100, 1, 300);
    double price = QInputDialog::getDouble(this, "Цена", "Введите цену ($):", 15000.0, 0, 1000000, 2);

    CarInfo newCar;
    newCar.model = model;
    newCar.speed = static_cast<qint8>(speed);
    newCar.price = price;

    Cars updated(sizeEnd + 1);
    for (int i = 0; i < sizeEnd; ++i)
        updated[i] = cars[i];
    updated[sizeEnd] = newCar;
    cars = updated;
    sizeEnd++;

    ui->listWidget->clear();
    for (int i = 0; i < sizeEnd; ++i) {
        QString itemText = QString("%1 | Скорость: %2 км/ч | Цена: $%3")
                               .arg(cars[i].model)
                               .arg(cars[i].speed)
                               .arg(cars[i].price, 0, 'f', 2);

        ui->listWidget->addItem(itemText);
    }

    QMessageBox::information(this, "Успешно", "Автомобиль добавлен!");
}


void MainWindow::on_DelListWidgButt_clicked()
{
    int row = ui->listWidget->currentRow();

    if (row < 0 || row >= sizeEnd) {
        QMessageBox::warning(this, "Ошибка", "Не выбрана строка для удаления.");
        return;
    }

    Cars updated(sizeEnd - 1);
    int j = 0;
    for (int i = 0; i < sizeEnd; ++i) {
        if (i != row)
            updated[j++] = cars[i];
    }

    cars = updated;
    sizeEnd--;

    ui->listWidget->clear();
    for (int i = 0; i < sizeEnd; ++i) {
        QString itemText = QString("%1 | Скорость: %2 км/ч | Цена: $%3")
                               .arg(cars[i].model)
                               .arg(cars[i].speed)
                               .arg(cars[i].price, 0, 'f', 2);

        ui->listWidget->addItem(itemText);
    }

    QMessageBox::information(this, "Успешно", "Автомобиль удалён.");
}


void MainWindow::on_addTableElemButt_clicked()
{
    QString model = QInputDialog::getText(this, "Новая модель", "Введите модель автомобиля:");
    if (model.isEmpty()) return;

    int speed = QInputDialog::getInt(this, "Скорость", "Введите скорость (км/ч):", 100, 1, 300);
    double price = QInputDialog::getDouble(this, "Цена", "Введите цену ($):", 15000.0, 0, 1000000, 2);

    CarInfo newCar;
    newCar.model = model;
    newCar.speed = static_cast<qint8>(speed);
    newCar.price = price;

    Cars updated(sizeEnd + 1);
    for (int i = 0; i < sizeEnd; ++i)
        updated[i] = cars[i];
    updated[sizeEnd] = newCar;
    cars = updated;
    sizeEnd++;

    ui->tableWidget->clear();
    ui->tableWidget->setRowCount(sizeEnd);
    for (int i = 0; i < sizeEnd; i++) {
        ui->tableWidget->setItem(i, 0, new QTableWidgetItem(cars[i].model));
        ui->tableWidget->setItem(i, 1, new QTableWidgetItem(QString::number(cars[i].speed)));
        ui->tableWidget->setItem(i, 2, new QTableWidgetItem(QString::number(cars[i].price)));
    }

    QMessageBox::information(this, "Успешно", "Автомобиль добавлен!");
}


void MainWindow::on_delTableElemButt_clicked()
{
    int row = ui->tableWidget->currentRow();

    if (row < 0 || row >= sizeEnd) {
        QMessageBox::warning(this, "Ошибка", "Не выбрана строка для удаления.");
        return;
    }

    Cars updated(sizeEnd - 1);
    int j = 0;
    for (int i = 0; i < sizeEnd; ++i) {
        if (i != row)
            updated[j++] = cars[i];
    }

    cars = updated;
    sizeEnd--;

    ui->tableWidget->clear();
    ui->tableWidget->setRowCount(sizeEnd);
    for (int i = 0; i < sizeEnd; ++i) {
        ui->tableWidget->setItem(i, 0, new QTableWidgetItem(cars[i].model));
        ui->tableWidget->setItem(i, 1, new QTableWidgetItem(QString::number(cars[i].speed)));
        ui->tableWidget->setItem(i, 2, new QTableWidgetItem(QString::number(cars[i].price, 'f', 2)));
    }

    QMessageBox::information(this, "Успешно", "Автомобиль удалён.");
}

void MainWindow::keyPressEvent(QKeyEvent *event) {
    if ((event->key() == Qt::Key_Delete || event->key() == Qt::Key_Backspace) && ui->stackedWidget->currentIndex() == 1) {
        on_delTableElemButt_clicked();
    }
    if ((event->key() == Qt::Key_Delete || event->key() == Qt::Key_Backspace) && ui->stackedWidget->currentIndex() == 2) {
        on_DelListWidgButt_clicked();
    }
    if ((event->key() == Qt::Key_Return) && ui->stackedWidget->currentIndex() == 0) {
        on_arrSizeButt_clicked();
    }
}


void MainWindow::contextMenuEvent(QContextMenuEvent* event)
{
    QMenu menu(this);

    QAction* enableSizeInput = menu.addAction("Включить ввод размера массива");
    QAction* disableSizeInput = menu.addAction("Отключить ввод размера массива");

    QAction* selectedAction = menu.exec(event->globalPos());

    if (selectedAction == enableSizeInput) {
        ui->ArrSizeLineEdit->setEnabled(true);
        ui->arrSizeButt->setEnabled(true);
    }
    else if (selectedAction == disableSizeInput) {
        ui->ArrSizeLineEdit->setEnabled(false);
        ui->arrSizeButt->setEnabled(false);
    }
}
