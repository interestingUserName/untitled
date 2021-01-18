#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
#include <regex>
#include "dialog.h"
#include "logic.h"
#include "drawing.h"
#include <QPair>
#include <QPaintEvent>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    createDrawing();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setPointsCount(int count)
{
    pointsCount = count;
    ui->points_count_text->setText(QString::number(pointsCount));
}

QString MainWindow::getPointsText()
{
    return ui->coordinates_text->toPlainText();
}

int MainWindow::getPointsCount()
{
    return pointsCount;
}

QList<QPair<int, int>> MainWindow::getPoints()
{
   return points;
}

void MainWindow::setPoints(QList<QPair<int, int>> pts)
{
    points = pts;
}

void MainWindow::writePoints()
{
    ui->coordinates_text->clear();
    for (int i = 0; i < points.length(); i++)
    {
        ui->coordinates_text->setText(ui->coordinates_text->toPlainText() +
                                      QString::number(points.at(i).first) +
                                      ", " +
                                      QString::number(points.at(i).second) + '\n');
    }
}

void MainWindow::createDrawing()
{
    drawing = new Drawing(this, &points);
}

void MainWindow::openDrawing()
{
    if (drawing->isVisible())
    {
        drawing->close();
    }
    if (points.length() < 1)
    {
        QMessageBox::warning(this, "error", "need more points");
    }
    else
    {
        createDrawing();
        drawing->show();
    }
}

void MainWindow::InitializePoints()
{
    points.clear();
    QString text = ui->coordinates_text->toPlainText();
    QStringList lines = text.split("\n", QString::SkipEmptyParts);
    foreach(QString line, lines)
    {
        std::string str = line.toStdString();
        int temp = str.find(',');
        int number1 = std::stoi(str.substr(0,temp));
        int number2 = std::stoi(str.substr(temp + 2,str.length() - (temp + 2)));
        QPair<int, int> newPair(number1, number2);
        points.append(newPair);
    }
}

void MainWindow::on_add_button_clicked()
{
    Dialog* dialog = new Dialog(this, this);
    dialog->show();
}

void MainWindow::on_clear_button_clicked()
{
    ui->coordinates_text->clear();
    pointsCount = 0;
    ui->points_count_text->setText(QString::number(pointsCount));
    InitializePoints();
    if (drawing != nullptr)
    {
        drawing->close();
    }
}

void MainWindow::setCoordinatesText(QString text)
{
    ui->coordinates_text->setText(text);
}

void MainWindow::on_actionSave_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, "open a file", "C://");
    QFile file(fileName);

    if (!file.open(QFile::WriteOnly | QFile::Text))
    {
       QMessageBox::warning(this, "title", "file was not opened");
    }
    else
    {
        QTextStream out(&file);
        QString text = ui->coordinates_text->toPlainText();
        out << text;
        file.flush();
        file.close();
    }
}

void MainWindow::on_actionOpen_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, "open a file", "C://");
    QFile file(fileName);

    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
       QMessageBox::warning(this, "title", "file was not opened");
    }
    else
    {
        QTextStream in(&file);
        QString text = in.readAll();
        int validPoints = Logic::CheckText(text);
        if (validPoints != -1)
        {
            ui->coordinates_text->clear();
            QStringList lines = text.split("\n", QString::SkipEmptyParts);
            foreach(QString line, lines)
            {
                ui->coordinates_text->setText(ui->coordinates_text->toPlainText() + line + '\n');
            }
            InitializePoints();
            points = Logic::normalizePoints(points);
            writePoints();
            setPointsCount(points.length());
            if (drawing->isVisible())
            {
                drawing->close();
                openDrawing();
            }
        }
        else
        {
            QMessageBox::warning(this, "error", "invalid text");
        }
        file.close();
    }
}

void MainWindow::on_show_button_clicked()
{
    openDrawing();
}
