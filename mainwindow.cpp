#include <QWidget>

#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , mTimer(new QTimer(this))
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    mItemLayout = new QVBoxLayout(ui->ItemPlace);
    mItemLayout->setSpacing(0);
    mItemLayout->setContentsMargins(0, 0, 0, 0);

    addMicroorganisms(QRandomGenerator::global()->bounded(1, 20));
    ui->CounterValue->setText(QString::number(mMicroorganisms.size()));

    connect(ui->AntibioticBtn, &QPushButton::clicked, this, &MainWindow::applyAntibiotics);

    play();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addMicroorganisms(uint32_t number)
{
    for (int i = 0; i < number; i++)
    {
        QString name = getOrganismName();
        while (mMicroorganisms.count(name))
        {
            name = getOrganismName();
        }

        uint32_t live_time = QRandomGenerator::global()->bounded(20, 30);
        uint32_t breeding_time = live_time / 2;

        IMicroorganisms* m_org_gui = new IMicroorganisms(ui->ItemPlace, name, live_time, breeding_time);
        Microorganism* m_org_thread = new Microorganism(ui->ItemPlace, name, live_time, breeding_time);
        mItemLayout->addWidget(m_org_gui);

        mMicroorganisms.insert(name, std::make_pair(m_org_gui, m_org_thread));

        connect(m_org_thread, &Microorganism::updateMicroorganism, this, &MainWindow::updateMicroorganism);
        connect(m_org_thread, &Microorganism::deathMicroorganism, this, &MainWindow::deathMicroorganism);
        connect(m_org_thread, &Microorganism::giveOffspring, this, &MainWindow::giveOffspring);
    }
}

void MainWindow::play()
{
    for(auto& org: mMicroorganisms)
    {
        org.second->start();
    }
}

void MainWindow::applyAntibiotics()
{
    int rand = QRandomGenerator::global()->bounded(0, mMicroorganisms.size());
    QList<QString> org = mMicroorganisms.keys();
    for (int i = 0; i < rand; i++)
    {
        mMicroorganisms[org[i]].second->deleteLater();
        delete mMicroorganisms[org[i]].first;
        mMicroorganisms.remove(org[i]);
    }
    ui->CounterValue->setText(QString::number(mMicroorganisms.size()));
}

void MainWindow::updateMicroorganism(QString name, int l_time, int b_time)
{
    if (mMicroorganisms.count(name))
    {
        mMicroorganisms[name].first->setStatistic(l_time, b_time);
    }
}

void MainWindow::deathMicroorganism(QString name)
{
    if (mMicroorganisms.count(name))
    {
        mMicroorganisms[name].second->deleteLater();
        delete mMicroorganisms[name].first;

        mMicroorganisms.remove(name);

        ui->CounterValue->setText(QString::number(mMicroorganisms.size()));
    }
}

void MainWindow::giveOffspring(QString name)
{
    if (!mMicroorganisms.count(name))
    {
        return;
    }

    QString heir = getOrganismName();
    while (mMicroorganisms.count(heir))
    {
        heir = getOrganismName();
    }

    uint32_t live_time = mMicroorganisms[name].first->getLifeTime() + 2;
    uint32_t breeding_time = mMicroorganisms[name].first->getBreedingTime();

    IMicroorganisms* m_org_gui = new IMicroorganisms(ui->ItemPlace, heir, live_time, breeding_time);
    Microorganism* m_org_thread = new Microorganism(ui->ItemPlace, heir, live_time, breeding_time);
    mItemLayout->addWidget(m_org_gui);

    mMicroorganisms.insert(heir, std::make_pair(m_org_gui, m_org_thread));

    connect(m_org_thread, &Microorganism::updateMicroorganism, this, &MainWindow::updateMicroorganism);
    connect(m_org_thread, &Microorganism::deathMicroorganism, this, &MainWindow::deathMicroorganism);
    connect(m_org_thread, &Microorganism::giveOffspring, this, &MainWindow::giveOffspring);
    ui->CounterValue->setText(QString::number(mMicroorganisms.size()));

    m_org_thread->start();
}
