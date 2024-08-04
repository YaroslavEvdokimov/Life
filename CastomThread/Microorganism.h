#ifndef MICROORGANISM_H
#define MICROORGANISM_H

#include <QObject>
#include <QThread>
#include <QTimer>
#include <QDebug>

///
/// \brief The Microorganism class
/// Класс отвеает за логику "жизни" организма.
class Microorganism : public QThread
{
    Q_OBJECT
public:
    Microorganism(QObject *parent, const QString& name, const uint32_t& l_time, const uint32_t& b_time);
    ~Microorganism();

    void run() override;

    /// Метод остановки потока
    void death();

signals:
    void updateMicroorganism(QString& name, int& l_time, int& b_time);
    void deathMicroorganism(QString name);
    void giveOffspring(QString name);

private slots:
    /// Основной метод расчета времени до смерти и потомства
    void updateStat();

private:
    /// Метод обновления времени до потомства
    void updateBreedingTime();

    bool mIsAlive;

    QTimer* mTimer;

    QString mName;
    int mLifeTime = 0;
    int mBreedingTime = 0;
    int mSaveBreedingTime = 0;
};

#endif // MICROORGANISM_H
