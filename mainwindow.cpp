#include <QWidget>

#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , mTimer(new QTimer(this))
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    createMicroorganisms(QRandomGenerator::global()->bounded(1, 20));

    connect(ui->AntibioticBtn, &QPushButton::clicked, this, &MainWindow::applyAntibiotics);

    play();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::play()
{
    for(auto& org: mMicroorganisms)
    {
        org.second->start();
    }
}

void MainWindow::createMicroorganisms(uint32_t number)
{
    for (int i = 0; i < number; i++)
    {
        uint32_t live_time = QRandomGenerator::global()->bounded(20, 30);
        uint32_t breeding_time = live_time / 2;

        addMicroorganism(live_time, breeding_time);
    }
    ui->CounterValue->setText(QString::number(mMicroorganisms.size()));
}

Microorganism* MainWindow::addMicroorganism(const uint32_t& live_time, const uint32_t& breeding_time)
{
    QString name = getOrganismName();
    while (mMicroorganisms.count(name))
    {
        name = getOrganismName();
    }

    IMicroorganisms* m_org_gui = new IMicroorganisms(ui->ItemPlace, name, live_time, breeding_time);
    Microorganism* m_org_thread = new Microorganism(this, name, live_time, breeding_time);
    ui->ItemLayout->addWidget(m_org_gui);

    mMicroorganisms.insert(name, std::make_pair(m_org_gui, m_org_thread));

    connect(m_org_thread, &Microorganism::updateMicroorganism, this, &MainWindow::updateMicroorganism);
    connect(m_org_thread, &Microorganism::deathMicroorganism, this, &MainWindow::deathMicroorganism);
    connect(m_org_thread, &Microorganism::giveOffspring, this, &MainWindow::giveOffspring);

    return m_org_thread;
}

void MainWindow::applyAntibiotics()
{
    int rand = QRandomGenerator::global()->bounded(1, 100);
    int count = mMicroorganisms.size() * rand / 100;
    QList<QString> org = mMicroorganisms.keys();
    for (int i = 0; i < count; i++)
    {
        deathMicroorganism(org[i]);
    }
    ui->CounterValue->setText(QString::number(mMicroorganisms.size()));
}

void MainWindow::updateMicroorganism(QString& name, int& l_time, int& b_time)
{
    if (mMicroorganisms.count(name))
    {
        mMicroorganisms[name].first->setStatistic(l_time, b_time);
    }
}

void MainWindow::deathMicroorganism(QString name)
{
    mMutexDeath.lock();
    if (mMicroorganisms.count(name))
    {
        delete mMicroorganisms[name].first;
        mMicroorganisms[name].second->deleteLater();

        mMicroorganisms.remove(name);
    }
    mMutexDeath.unlock();
}

void MainWindow::giveOffspring(QString name)
{
    if (!mMicroorganisms.count(name) || mMicroorganisms.size() >= 50)
    {
        return;
    }

    uint32_t live_time = mMicroorganisms[name].first->getLifeTime() + 2;
    uint32_t breeding_time = mMicroorganisms[name].first->getBreedingTime();

    addMicroorganism(live_time, breeding_time)->start();
    ui->CounterValue->setText(QString::number(mMicroorganisms.size()));
}
