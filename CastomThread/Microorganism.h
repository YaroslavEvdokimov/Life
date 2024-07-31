#ifndef MICROORGANISM_H
#define MICROORGANISM_H

#include <QObject>
#include <QThread>
#include <QTimer>
#include <QDebug>

class Microorganism : public QThread
{
    Q_OBJECT
public:
    Microorganism(QObject *parent, const QString& name, const uint32_t& l_time, const uint32_t& b_time);
    ~Microorganism();

    void run() override;
    void death();

signals:
    void updateMicroorganism(QString& name, int& l_time, int& b_time);
    void deathMicroorganism(QString name);
    void giveOffspring(QString name);

private slots:
    void updateStat();

private:
    void updateBreedingTime();

    bool mIsAlive;

    QTimer* mTimer;

    QString mName;
    int mLifeTime = 0;
    int mBreedingTime = 0;
    int mSaveBreedingTime = 0;
};

#endif // MICROORGANISM_H
