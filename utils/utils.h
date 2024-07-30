#ifndef UTILS_H
#define UTILS_H

#endif // UTILS_H


#include <QRandomGenerator>
#include <QString>
#include <vector>

const static std::vector<QString> firstName =
    {"Oliver", "Jack", "Harry", "Charlie", "Ava", "George", "Amelia", "Henry", "James", "Emma"};

const static std::vector<QString> secondName =
    {"Hilfiger", "Klein", "Converse", "Vans", "Jordan", "Dell", "Jacobs", "Ford", "Timberland", "Kors"};

inline QString getOrganismName()
{
    QString first = firstName.at(QRandomGenerator::global()->bounded(0, 10));
    QString second = secondName.at(QRandomGenerator::global()->bounded(0, 10));

    return QString("Org.%1 %2").arg(first).arg(second);
}
