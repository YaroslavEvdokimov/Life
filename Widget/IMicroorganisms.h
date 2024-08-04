#ifndef IMICROORGANISMS_H
#define IMICROORGANISMS_H

#include <iostream>
#include <QWidget>
#include <QTimer>
#include <QMutex>

QT_BEGIN_NAMESPACE
namespace Ui { class ItemMicroorganism; }
QT_END_NAMESPACE

///
/// \brief The IMicroorganisms class
/// Класс отвечает за отрисовку и отображение параметров жизни организма
class IMicroorganisms : public QWidget
{
    Q_OBJECT
public:
    IMicroorganisms(QWidget *parent, const QString& name, const uint32_t& l_time, const uint32_t& b_time);
    ~IMicroorganisms();

    ///  Задать значения времени жизни микроорганизма и времени до потомства
    void setStatistic(const uint32_t& l_time, const uint32_t& b_time);
    /// Метод получения времени жизни микроорганизма
    uint32_t getLifeTime();
    /// Метод получения времени оставшегося до потомства
    uint32_t getBreedingTime();

private:
    QString  mName;
    uint32_t mLifeTime = 0;
    uint32_t mBreedingTime = 0;

    Ui::ItemMicroorganism *ui;
};

#endif // IMICROORGANISMS_H
