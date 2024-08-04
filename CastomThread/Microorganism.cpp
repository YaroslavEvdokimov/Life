#include "Microorganism.h"

Microorganism::Microorganism(QObject *parent
                             , const QString& name
                             , const uint32_t& l_time
                             , const uint32_t& b_time)
    : QThread(parent)
    , mName(name)
    , mLifeTime(l_time)
    , mBreedingTime(b_time)
    , mSaveBreedingTime(b_time)
    , mTimer(new QTimer(this))
    , mIsAlive(true)
{
    connect(mTimer, &QTimer::timeout, this, &Microorganism::updateStat);
    mTimer->start(1000);
}

Microorganism::~Microorganism()
{
    wait();
    qDebug() << "Death:"  << mName;
}

void Microorganism::death()
{
    mIsAlive = false;
    emit deathMicroorganism(mName);
}

void Microorganism::updateBreedingTime()
{
    mBreedingTime = mSaveBreedingTime;
}

void Microorganism::updateStat()
{
    mLifeTime--;
    mBreedingTime--;

    if (mLifeTime == 0)
    {
        death();
        return;
    }

    if (mBreedingTime == 0)
    {
        emit giveOffspring(mName);
        updateBreedingTime();
    }

    emit updateMicroorganism(mName, mLifeTime, mBreedingTime);
}

void Microorganism::run(){}
