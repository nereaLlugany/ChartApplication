#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QColorDialog>
#include <QComboBox>
#include <QFileDialog>
#include <QInputDialog>
#include "canvas.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected Q_SLOTS:
    virtual void on_actionSave_triggered();
    virtual void on_actionChange_Title_triggered();
    virtual void on_actionReset_triggered();

private Q_SLOTS:
    void updateBarAPosition(int value);
    void updateBarBPosition(int value);

    void changeColorA();
    void changeColorB();

    void updateResolution(int resolution);
    void saveChart();

    void changeTitle();

private:
    Ui::MainWindow *ui;
    Canvas* canv;
    Canvas* newCanv;
    QComboBox *resolutionComboBox;
    QSize selectedResolution;
};
#endif // MAINWINDOW_H
