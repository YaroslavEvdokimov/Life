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
    , mIsAlive(true)
{

}

Microorganism::~Microorganism()
{
    death();
}

void Microorganism::death()
{
    mIsAlive = false;
}

void Microorganism::updateBreedingTime()
{
    mBreedingTime = mSaveBreedingTime;
}

void Microorganism::run()
{
    while(mIsAlive)
    {
        QThread::sleep(1);
        mLifeTime--;
        mBreedingTime--;

        if (mLifeTime == 0)
        {
            emit deathMicroorganism(mName);
            continue;
        }

        if (mBreedingTime == 0)
        {
            emit giveOffspring(mName);
            updateBreedingTime();
        }

        emit updateMicroorganism(mName, mLifeTime, mBreedingTime);
    }
}
