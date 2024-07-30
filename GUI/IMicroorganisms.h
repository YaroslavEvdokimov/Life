#ifndef IMICROORGANISMS_H
#define IMICROORGANISMS_H

#include <iostream>
#include <QWidget>
#include <QTimer>
#include <QMutex>

QT_BEGIN_NAMESPACE
namespace Ui { class ItemMicroorganism; }
QT_END_NAMESPACE

class IMicroorganisms : public QWidget
{
    Q_OBJECT
public:
    IMicroorganisms(QWidget *parent, const QString& name, const uint32_t& l_time, const uint32_t& b_time);
    ~IMicroorganisms();

    void setStatistic(const uint32_t& l_time, const uint32_t& b_time);

    uint32_t getLifeTime();
    uint32_t getBreedingTime();

private:
    QString mName;
    uint32_t mLifeTime = 0;
    uint32_t mBreedingTime = 0;

    Ui::ItemMicroorganism *ui;
};

#endif // IMICROORGANISMS_H
