#ifndef RESULT_H
#define RESULT_H

#include <QDialog>
#include <QVBoxLayout>
#include <QTableWidget>

namespace Ui {
class result;
}

class result : public QDialog
{
    Q_OBJECT

public:
    explicit result(QWidget *parent = nullptr);
    ~result();

    void setValues(int numOfX, int numOfLim, QVector<QVector<float>> table);
    void simplexAlgorithm(int numOfX, int numOfLim, QVector<QVector<float>> table);
    int choiseColumn(int n, int m, QVector<QVector<float>> table);
    int choiseRow(int n, int m, int column, QVector<QVector<float>> table, QVector<QVector<float>> newtable);
    void addViewTable(int count, int n, int m, int row, int column, QVector<QVector<float>> table, QVector<int> basis);
    void setVerticalHeader(int n, QVector<int> basis, QTableWidget *tab);
    void setHorizontalHeader(int m, QTableWidget *tab);
    void fillTable(int n, int m, QVector<QVector<float>> table, QTableWidget *tab);
    void drawTable(int n, int m, int row, int column, QTableWidget *tab);
    void answer(int numOfX, QVector<int> basis, QVector<float> res, bool nonNegativB);

private:
    Ui::result *ui;

    QWidget *widget;
    QVBoxLayout *tabs;
};

#endif // RESULT_H
