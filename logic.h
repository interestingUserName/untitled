#ifndef LOGIC_H
#define LOGIC_H
#include <QString>
#include <QPair>

class Logic
{
public:
    Logic();
    static int CheckText(QString text);
    static QList<QPair<int, int>> normalizePoints(QList<QPair<int, int>> points);
};

#endif // LOGIC_H
