#include "drawing.h"
#include "ui_drawing.h"
#include <QMessageBox>

Drawing::Drawing(QWidget *parent, QList<QPair<int, int>> *pts) :
    QDialog(parent),
    ui(new Ui::Drawing)
{
    ui->setupUi(this);
    points = pts;
}

Drawing::~Drawing()
{
    delete ui;
}

void Drawing::Draw()
{
    QPainter painter(this);
    painter.translate(0, this->height());
    painter.scale(1, -1);
    int multiplier = 15;
    QPen pen(Qt::black);
    pen.setWidth(2);
    painter.setPen(pen);
    for (int i = 0; i < points->length() - 1; i++)
    {
       painter.drawLine(points->at(i).first * multiplier, points->at(i).second * multiplier,
                        points->at(i + 1).first * multiplier, points->at(i + 1).second * multiplier);
    }
    painter.drawLine(points->at(points->length() - 1).first * multiplier, points->at(points->length() - 1).second * multiplier,
                     points->at(0).first * multiplier, points->at(0).second * multiplier);
}

void Drawing::paintEvent(QPaintEvent *event)
{
    Draw();
}
