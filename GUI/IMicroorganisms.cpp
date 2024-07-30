#include "IMicroorganisms.h"
#include "./ui_ItemMicroorganism.h"

IMicroorganisms::IMicroorganisms(QWidget *parent
                                 , const QString& name
                                 , const uint32_t& l_time
                                 , const uint32_t& b_time)
    : QWidget(parent)
    , ui(new Ui::ItemMicroorganism)
    , mName(name)
    , mLifeTime(l_time)
    , mBreedingTime(b_time)
{
    ui->setupUi(this);

    ui->ItemName->setText(name);
    ui->LivetimeValue->setText(QString::number(l_time));
    ui->OffspringValue->setText(QString::number(b_time));
}

IMicroorganisms::~IMicroorganisms()
{
    delete ui;
}

void IMicroorganisms::setStatistic(const uint32_t& l_time, const uint32_t& b_time)
{
    ui->LivetimeValue->setText(QString::number(l_time));
    ui->OffspringValue->setText(QString::number(b_time));
}

uint32_t IMicroorganisms::getLifeTime()
{
    return mLifeTime;
}

uint32_t IMicroorganisms::getBreedingTime()
{
    return mBreedingTime;
}


