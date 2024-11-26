#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QLineEdit>
#include "result.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    wid1 = new QWidget(this);
    equation = new QHBoxLayout(wid1);
    wid1->setLayout(equation);

    ui->scrollArea->setWidget(wid1);
    ui->scrollArea->setWidgetResizable(true);

    connect(ui->spinBox, QOverload<int>::of(&QSpinBox::valueChanged), this, &MainWindow::on_spinBox_valueChanged);

    wid2 = new QWidget(this);
    limits = new QVBoxLayout(wid2);
    wid2->setLayout(limits);

    ui->scrollArea_2->setWidget(wid2);
    ui->scrollArea_2->setWidgetResizable(true);

    connect(ui->spinBox_2, QOverload<int>::of(&QSpinBox::valueChanged), this, &MainWindow::on_spinBox_2_valueChanged);

    on_spinBox_valueChanged(ui->spinBox->value());
    on_spinBox_2_valueChanged(ui->spinBox_2->value());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_spinBox_valueChanged(int value)
{
    changeMainFunc(value);
}

void MainWindow::on_spinBox_2_valueChanged(int value)
{
    changeLimits(value);
}


void MainWindow::on_pushButton_clicked()
{
    clearAllLineEdits();
}


void MainWindow::on_pushButton_2_clicked()
{
    int numOfX = ui->spinBox->value();
    int numOfLim = ui->spinBox_2->value();
    QVector<QVector<float>> table = formationTable(numOfX, numOfLim);

    openResultWindow(numOfX, numOfLim, table);
}


void MainWindow::on_comboBox_currentIndexChanged(int index)
{
    QStringList num;
    switch(index){
    case 1:{
        num = {"5", "6", "4",
               "3", "1", "2", "1",
               "2", "3", "2", "12"};
        fillLineEditsTest(3, 2, num);
        break;
    }
    case 2:{
        num = {"3", "2",
               "1", "1", "4",
               "2", "1", "5"};
        fillLineEditsTest(2, 2, num);
        break;
    }
    case 3:{
        num = {"5", "8", "4", "3",
               "2", "3", "1", "1","20",
               "3", "2", "4", "0", "30",
               "0", "1", "1", "2", "15"};
        fillLineEditsTest(4, 3, num);
        break;
    }
    case 4:{
        num = {"6", "7", "2",
                "1", "1", "1", "10",
                "2", "3", "0", "12",
                "1", "0", "2", "6"};
        fillLineEditsTest(3, 3, num);
        break;
    }
    case 5:{
        num = {"3", "5", "2", "4",
            "4", "3", "2", "1","17",
            "4", "3", "7", "1", "9",
            "1", "2", "1", "2", "13",
            "3", "2", "4", "8", "23"};
        fillLineEditsTest(4, 4, num);
        break;
    }
    case 0:{
        clearAllLineEdits();
    }
    default:
        break;
    }
}


void MainWindow::clearHLayout(QHBoxLayout *layout) {
    while (QLayoutItem *item = layout->takeAt(0)) {
        if (QWidget *widget = item->widget()) {
            delete widget;
        }
        delete item;
    }
}


void MainWindow::clearVLayout(QVBoxLayout *layout) {
    while (QLayoutItem *item = layout->takeAt(0)) {

        if (QLayout *childLayout = item->layout()) {
            clearHLayout(static_cast<QHBoxLayout*>(childLayout));
        }

        if (QWidget *widget = item->widget()) {
            delete widget;
        }

        delete item;
    }
}


void MainWindow::changeMainFunc(int value){
    clearHLayout(equation);

    for (int i = 0; i < value; i++) {
        QLineEdit *lineEdit = new QLineEdit(this);
        QLabel *label = new QLabel(tr("x%1").arg(i + 1), this);

        equation->addWidget(lineEdit);
        equation->addWidget(label);

        if (i < value - 1) {
            QLabel *plusLabel = new QLabel("+", this);
            equation->addWidget(plusLabel);
        }
    }

    QLabel *equalLabel = new QLabel("-> max", this);
    equation->addWidget(equalLabel);
    changeLimits(ui->spinBox_2->value());
}


void MainWindow::changeLimits(int value){
    clearVLayout(limits);

    for (int i = 0; i < value; i++) {
        QHBoxLayout *equat = new QHBoxLayout();

        for (int j = 0; j < ui->spinBox->value(); j++){

            QLineEdit *lineEdit = new QLineEdit(this);
            QLabel *label = new QLabel(QString("x%1").arg(j + 1), this);

            equat->addWidget(lineEdit);
            equat->addWidget(label);

            if (j < ui->spinBox->value() - 1) {
                QLabel *plusLabel = new QLabel("+", this);
                equat->addWidget(plusLabel);
            }

        }

        QLabel *equalLabel = new QLabel("<=", this);
        QLineEdit *lineEdit = new QLineEdit(this);
        equat->addWidget(equalLabel);
        equat->addWidget(lineEdit);
        limits->addLayout(equat);
    }
}


void MainWindow::clearAllLineEdits(){
    QList<QLineEdit*> lineEdits = wid1->findChildren<QLineEdit*>();
    for(QLineEdit *lineEdit : lineEdits){
        lineEdit->clear();
    }

    QList<QLineEdit*> lineEdits2 = wid2->findChildren<QLineEdit*>();
    for(QLineEdit *lineEdit : lineEdits2){
        lineEdit->clear();
    }
}


QVector<QVector<float>> MainWindow::formationTable(int numOfX, int numOfLim){
    int n = numOfLim + 1;
    int m = numOfX + numOfLim + 1;
    QList<QLineEdit*> limit = wid2->findChildren<QLineEdit*>();
    QVector<QVector<float>> table(n, QVector<float>(m, 0));
    int index = 0;
    for(int i = 0; i < n-1; i++){
        int j = 0;
        while(j<numOfX){
            table[i][j] = limit.at(index)->text().toFloat();
            j++;
            index++;
        }
        table[i][numOfX+i] = 1;
        table[i][m-1] = limit.at(index)->text().toFloat();
        index++;
    }
    QList<QLineEdit*> equat = wid1->findChildren<QLineEdit*>();
    for(int j = 0; j < numOfX; j++){
        table[n-1][j] = equat.at(j)->text().toFloat() * -1;
    }
    return table;
}


void MainWindow::openResultWindow(int numOfX, int numOfLim, QVector<QVector<float>> table){
    result *reswindow = new result(this);
    reswindow->setValues(numOfX, numOfLim, table);
    reswindow->show();
}


void MainWindow::fillLineEditsTest(int x, int lim, QStringList num){
    ui->spinBox->setValue(x);
    ui->spinBox_2->setValue(lim);

    int ind = 0;

    QList<QLineEdit*> lineEdits1 = wid1->findChildren<QLineEdit*>();
    for (int i = 0; i < lineEdits1.size(); ++i) {
        lineEdits1[i]->setText(num[ind]);
        ind++;
    }

    QList<QLineEdit*> lineEdits2 = wid2->findChildren<QLineEdit*>();
    for (int i = 0; i < lineEdits2.size(); ++i) {
        lineEdits2[i]->setText(num[ind]);
        ind++;
    }
}
