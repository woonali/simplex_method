#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QHBoxLayout >

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

private slots:
    void on_spinBox_valueChanged(int arg1);

    void on_spinBox_2_valueChanged(int arg1);

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_comboBox_currentIndexChanged(int index);

private:
    Ui::MainWindow *ui;

    QHBoxLayout  *equation;
    QWidget *wid1;

    QVBoxLayout  *limits;
    QWidget *wid2;

    void clearHLayout(QHBoxLayout  *layout);
    void clearVLayout(QVBoxLayout  *layout);
    void changeMainFunc(int value);
    void changeLimits(int value);
    void clearAllLineEdits();
    QVector<QVector<float>> formationTable(int numOfX, int numOfLim);
    void openResultWindow(int numOfX, int numOfLim, QVector<QVector<float>> table);
    void fillLineEditsTest(int x, int lim, QStringList num);
};
#endif // MAINWINDOW_H
