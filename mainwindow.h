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

///
/// \brief The MainWindow class
///
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    /// Слот обновления данных микроорганизмов
    void updateMicroorganism(QString& name, int& l_time, int& b_time);
    /// Слот удаления микроорганизма
    void deathMicroorganism(QString name);
    /// Слот создает потомка организма.
    /// Наследуется время жизни(увел. на 2 сек) и время производства потомства
    void giveOffspring(QString name);
    /// Слот принятия антибиотика(удаляет рандомный процент организмов)
    void applyAntibiotics();

private:
    /// Метод создания микроорганизмов
    void createMicroorganisms(uint32_t number);

    /// Метод добавлет один микорорганизм
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
