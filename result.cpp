#include "result.h"
#include "ui_result.h"
#include <QVBoxLayout>
#include <QTableWidget>
#include <QHeaderView>

result::result(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::result)
{
    ui->setupUi(this);

    widget = new QWidget(this);
    tabs = new QVBoxLayout(widget);
    widget->setLayout(tabs);

    ui->scrollArea->setWidget(widget);
    ui->scrollArea->setWidgetResizable(true);
}

result::~result()
{
    delete ui;
}

void result::setValues(int numOfX, int numOfLim, QVector<QVector<float>> table){
    simplexAlgorithm(numOfX, numOfLim, table);
}


void result::simplexAlgorithm(int numOfX, int numOfLim, QVector<QVector<float>> table){
    int n = numOfLim + 1;
    int m = numOfX + numOfLim + 1;
    QVector<int> basis;
    for(int i = 1; i <= numOfLim; i++){
        basis.append(numOfX+i);
    }
    int count = 1;
    bool nonNegativeB = true;
    while(true){
        QVector<QVector<float>> newtable(n, QVector<float>(m, 0));

        int column = choiseColumn(n, m, table);
        if(column == -1){
            break;
        }

        int row = choiseRow(n, m, column, table, newtable);
        if(row == -1){
            nonNegativeB = false;
            break;
        }

        //деление b на соответствующее значение столбца
        for(int i = 0; i < n-1; i++){
            if(table[i][column] <= 0){
                continue;
            }
            newtable[i][m-1] = table[i][m-1]/table[i][column];
        }

        float del = table[row][column];
        //ведущий эелемент приводиться к единицe
        for(int j = 0; j < m-1; j++){
            newtable[row][j] = table[row][j] / del;
        }

        //перерасчет остальной части таблицы
        for(int k = 0; k < n;k++){
            if(k != row){
                for(int j = 0; j < m; j++){
                    newtable[k][j] = table[k][j] - table[k][column]*newtable[row][j];
                }
            }
        }
        addViewTable(count, n, m, row, column, table, basis);
        basis[row] = column+1;
        table = newtable;
        count++;
    }    
    addViewTable(count, n, m, -1, -1, table, basis);

    QVector<float> res;
    for(int i =0; i < numOfLim; i++){
        res.append(table[i][m-1]);
    }
    res.append(table[n-1][m-1]);

    answer(numOfX, basis, res, nonNegativeB);
}


int result::choiseColumn(int n, int m, QVector<QVector<float>> table){
    int column = -1;
    float min = 0;
    for(int j = 0; j < m; j++){
        if(table[n-1][j] < min){
            min = table[n-1][j];
            column = j;
        }
    }

    return column;
}


int result::choiseRow(int n, int m, int column, QVector<QVector<float>> table, QVector<QVector<float>> newtable){
    int row = -1;
    int min = 1000000;
    for(int i = 0; i < n-1; i++){
        if(table[i][column] <= 0){
            continue;
        }
        newtable[i][m-1] = table[i][m-1]/table[i][column];
        if(newtable[i][m-1] < min){
            min = newtable[i][m-1];
            row = i;
        }
    }

    return row;
}


void result::addViewTable(int count, int n, int m, int row, int column, QVector<QVector<float>> table, QVector<int> basis){
    QLabel *iteration = new QLabel("Итерация " + QString::number(count));
    tabs->addWidget(iteration);
    QTableWidget *tab = new QTableWidget(n, m);

    setVerticalHeader(n, basis, tab);
    setHorizontalHeader(m, tab);
    fillTable(n, m, table, tab);

    tab->setEditTriggers(QAbstractItemView::NoEditTriggers);//не изменяема
    tab->setSelectionMode(QAbstractItemView::NoSelection);//не выделяема

    tab->horizontalHeader()->setDefaultSectionSize(50);//ширина столбцов
    tab->resizeRowsToContents();

    QSize minSize = tab->sizeHint();//минимальный размер
    tab->setMinimumSize(minSize);

    if(row != -1 && column != -1){
        drawTable(n, m, row, column, tab);
    }

    tabs->addWidget(tab);
}


void result::setVerticalHeader(int n, QVector<int> basis, QTableWidget *tab){
    for (int i = 0; i < n-1; i++){
        tab->setVerticalHeaderItem(i,new QTableWidgetItem(QString("x%1").arg(basis[i])));
    }
    tab->setVerticalHeaderItem(n-1, new QTableWidgetItem(QString::fromUtf16(u"\u0394")));
}


void result::setHorizontalHeader(int m, QTableWidget *tab){
    for(int j = 0; j < m-1; j++){
        tab->setHorizontalHeaderItem(j, new QTableWidgetItem(QString("x%1").arg(j+1)));
    }
    tab->setHorizontalHeaderItem(m-1, new QTableWidgetItem("b"));
}


void result::fillTable(int n, int m, QVector<QVector<float>> table, QTableWidget *tab){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            QString item;
            if(table[i][j] == std::floor(table[i][j])){
                item = QString::number(table[i][j]);
            }
            else{
                item = QString::number(table[i][j], 'f', 2);
            }
            tab->setItem(i, j, new QTableWidgetItem(item));
        }
    }
}


void result::drawTable(int n, int m, int row, int column, QTableWidget *tab){
    for(int i = 0; i < n; i++){
        QTableWidgetItem *item = tab->item(i, column);
        item->setBackground(QColor(240,0,0));
    }

    for(int j = 0; j < m; j++){
        QTableWidgetItem *item = tab->item(row, j);
        item->setBackground(QColor(0,0,240));
    }

    QTableWidgetItem *item = tab->item(row, column);
    item->setBackground(QColor(240,0,240));
}


void result::answer(int numOfX, QVector<int> basis, QVector<float> res, bool nonNegativB){
    QString end = "Ответ:\n";
    if (nonNegativB == false){
        end += "Оптимальное решение отсутствует";
    }
    else{
        for(int i = 0; i < numOfX; i++){
            bool finding = std::find(basis.begin(), basis.end(), i+1) == basis.end();
            auto iterator = std::find(basis.begin(), basis.end(), i+1);
            int index = std::distance(basis.begin(), iterator);
            end += QString("x%1").arg(i+1) + " = " + (finding ? "0.00" :  QString::number(res[index],'f', 2));
            if(i != numOfX-1){
                end += ", ";
            }
        }
        end += "\nF = " + QString::number(res[res.size()-1], 'f', 2);
    }
    ui->label_2->setText(end);
}
