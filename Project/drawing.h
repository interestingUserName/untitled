#ifndef DRAWING_H
#define DRAWING_H

#include <QDialog>
#include <QPair>
#include <QPainter>

namespace Ui {
class Drawing;
}

class Drawing : public QDialog
{
    Q_OBJECT

public:
    explicit Drawing(QWidget *parent = nullptr, QList<QPair<int, int>> *pts = nullptr);
    ~Drawing();
    void Draw();

    virtual void paintEvent(QPaintEvent *event);

private:
    Ui::Drawing *ui;
    QList<QPair<int, int>> *points;
};

#endif // DRAWING_H
