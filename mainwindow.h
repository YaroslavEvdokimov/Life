#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QVBoxLayout>
#include <QScrollArea>
#include <QHash>
#include <QList>
#include <QDebug>
#include <tuple>

#include "Widget/IMicroorganisms.h"
#include "CastomThread/Microorganism.h"
#include "utils/utils.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void updateMicroorganism(QString& name, int& l_time, int& b_time);
    void deathMicroorganism(QString name);
    void giveOffspring(QString name);
    void applyAntibiotics();

private:
    void createMicroorganisms(uint32_t number);

    Microorganism* addMicroorganism(const uint32_t& live_time, const uint32_t& breeding_time);
    void play();

private:
    QTimer *mTimer;
    QMutex mMutexDeath;
    QVBoxLayout *mItemLayout;
    QScrollArea *mScrollArea;

    Ui::MainWindow *ui;

    QHash<QString, std::pair<IMicroorganisms*, Microorganism*>> mMicroorganisms;
};
#endif // MAINWINDOW_H
