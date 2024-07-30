#ifndef MICROORGANISM_H
#define MICROORGANISM_H

#include <QObject>
#include <QThread>

class Microorganism : public QThread
{
    Q_OBJECT
public:
    Microorganism(QObject *parent, const QString& name, const uint32_t& l_time, const uint32_t& b_time);
    ~Microorganism();

    void run() override;
    void death();

signals:
    void updateMicroorganism(QString name, int l_time, int b_time);
    void deathMicroorganism(QString name);
    void giveOffspring(QString name);

private:
    void updateBreedingTime();

    bool mIsAlive;

    QString mName;
    uint32_t mLifeTime = 0;
    uint32_t mBreedingTime = 0;
    uint32_t mSaveBreedingTime = 0;
};

#endif // MICROORGANISM_H
