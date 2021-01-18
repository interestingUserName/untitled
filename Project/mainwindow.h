#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "drawing.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void setCoordinatesText(QString text);
    void setPointsCount(int count);
    QString getPointsText();
    int getPointsCount();
    void InitializePoints();
    QList<QPair<int, int>> getPoints();
    void setPoints(QList<QPair<int, int>> pts);
    void writePoints();
    Drawing *drawing;
    void createDrawing();
    void openDrawing();

private slots:


    void on_add_button_clicked();

    void on_clear_button_clicked();

    void on_actionSave_triggered();

    void on_actionOpen_triggered();

    void on_show_button_clicked();

private:
    Ui::MainWindow *ui;
    int pointsCount = 0;
    QList<QPair<int, int>> points;
};
#endif // MAINWINDOW_H
