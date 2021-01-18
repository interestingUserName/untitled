#include "logic.h"
#include <regex>

#include <QFile>
#include <QFileDialog>
#include <QTextStream>

Logic::Logic()
{

}

int Logic::CheckText(QString text)
{
    int counter = 0;
    std::cmatch result;
    std::regex regular("([\\d]+)(,)([\\s])([\\d]+)");
    QStringList lines = text.split("\n", QString::SkipEmptyParts);
    foreach(QString line, lines)
    {
        std::string str = line.toStdString();
        if (!std::regex_match(str.c_str(), result, regular))
        {
            counter = -1;
            break;
        }
        else
        {
            counter++;
        }
    }
    return counter;
}

QList<QPair<int, int>> Logic::normalizePoints(QList<QPair<int, int>> points)
{
    if (points.length() < 3)
    {
        return points;
    }
    bool isNormalized = false;

    while (!isNormalized)
    {
        int counter = 0;
        for (int i = 0; i < points.length() - 2; i++)
        {
            if (((float)points.at(i).first / (float)points.at(i).second ==
                 (float)points.at(i + 1).first / (float)points.at(i + 1).second)
                 && ((float)points.at(i + 1).first / (float)points.at(i + 1).second ==
                 (float)points.at(i + 2).first / (float)points.at(i + 2).second))
            {
                counter++;
                points.removeAt(i + 1);
                if (points.length() < 3)
                {
                    return points;
                }
                continue;
            }
        }
        if ((float)points.at(points.length() - 2).first / (float)points.at(points.length() - 2).second ==
                (float)points.at(points.length() - 1).first / (float)points.at(points.length() - 1).second
                && (float)points.at(points.length() - 1).first / (float)points.at(points.length() - 1).second ==
                (float)points.at(0).first / (float)points.at(0).second)
        {
            counter++;
            points.removeAt(points.length() - 1);
            if (points.length() < 3)
            {
                return points;
            }
            continue;
        }
        if ((float)points.at(points.length() - 1).first / (float)points.at(points.length() - 1).second ==
                (float)points.at(0).first / (float)points.at(0).second
                && (float)points.at(0).first / (float)points.at(0).second ==
                (float)points.at(1).first / (float)points.at(1).second)
        {
            counter++;
            points.removeAt(0);
            if (points.length() < 3)
            {
                return points;
            }
            continue;
        }
        if (counter == 0)
        {
            isNormalized = true;
        }
    }

    return points;
}
