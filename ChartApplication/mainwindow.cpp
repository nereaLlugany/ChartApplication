#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QColor>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    canv = new Canvas();

    //Opcions del ComboBox
    resolutionComboBox = new QComboBox(this);
    resolutionComboBox->setStyleSheet("background-color: #ffffff;");
    resolutionComboBox->addItem("480x320");
    resolutionComboBox->addItem("800x600");
    resolutionComboBox->addItem("1280x720");
    resolutionComboBox->addItem("1920x1080");
    resolutionComboBox->addItem("2560x1440");

    //La opció per defecte
    resolutionComboBox->setCurrentIndex(1);

    canv->setParent(ui->chart);

    //Connects a la UI
    connect(ui->spinBox_A, SIGNAL(valueChanged(int)), this, SLOT(updateBarAPosition(int)));
    connect(ui->spinBox_B, SIGNAL(valueChanged(int)), this, SLOT(updateBarBPosition(int)));

    connect(ui->frameBarA, SIGNAL(clicked()), this, SLOT(changeColorA()));
    connect(ui->frameBarB, SIGNAL(clicked()), this, SLOT(changeColorB()));

    ui->horizontalLayout_8->addWidget(resolutionComboBox);
    connect(resolutionComboBox, SIGNAL(activated(int)), this, SLOT(updateResolution(int)));
    connect(ui->SavePushButton, SIGNAL(clicked()), this, SLOT(saveChart()));

    connect(ui->tittlePushButton, SIGNAL(clicked()), this, SLOT(changeTitle()));

}

//Destructora
MainWindow::~MainWindow()
{
    delete ui;
    delete canv;
}

//Mètodes
void MainWindow::updateBarAPosition(int value) {
    canv->setBarAHeight(value);
}

void MainWindow::updateBarBPosition(int value) {
    canv->setBarBHeight(value);
}

void MainWindow::changeColorA() {
    QColor color = QColorDialog::getColor(Qt::white, this, "Select Color for A");
    if (color.isValid()) {
        canv->setColorA(color);
        QString styleSheetButtonA = "background-color: " + color.name() + ";";
        ui->frameBarA->setStyleSheet(styleSheetButtonA);
    }
}

void MainWindow::changeColorB() {
    QColor color = QColorDialog::getColor(Qt::white, this, "Select Color for B");
    if (color.isValid()) {
        canv->setColorB(color);
        QString styleSheetButtonB = "background-color: " + color.name() + ";";
        ui->frameBarB->setStyleSheet(styleSheetButtonB);
    }
}


void MainWindow::updateResolution(int resolution)
{
    QString resolutionText = resolutionComboBox->itemText(resolution);

    QStringList dimensions = resolutionText.split("x");
    int width = dimensions[0].toInt();
    int height = dimensions[1].toInt();

    selectedResolution = QSize(width, height);

    resolutionComboBox->setCurrentText(resolutionText);

    statusBar()->showMessage("Selected resolution: " + resolutionText);

}

void MainWindow::saveChart()
{
    QString filePath = QFileDialog::getSaveFileName(this, tr("Save Chart"), "",  tr("PNG Image (*.png);;JPEG Image (*.jpg *.jpeg)"));

    if (!filePath.isEmpty()) {
        //Creació d'un nou canvas per guardar el desitgat sense modificar el de la ui
        Canvas* newCanv = new Canvas(this);

        newCanv->setStyleSheet("background-color: #ffffff");

        if (selectedResolution.isValid()) {
            newCanv->setFixedSize(selectedResolution.width(), selectedResolution.height());

        } else {
            selectedResolution = QSize(800, 600);
            newCanv->setFixedSize(selectedResolution.width(), selectedResolution.height());
        }

        //Agafar els valors modificats del gràfic i grarda-lo
        double heightRatio = 600.0/1770.0;
        newCanv->setBarAHeight(canv->getBarAHeight()*heightRatio);
        newCanv->setBarBHeight(canv->getBarBHeight()*heightRatio);
        newCanv->setColorA(canv->getColorA());
        newCanv->setColorB(canv->getColorB());
        newCanv->setChartTitle(canv->getChartTitle());

        newCanv->repaint();

        QPixmap chartImage = newCanv->grab();
        if (!chartImage.isNull()) {
            chartImage.save(filePath);
            statusBar()->showMessage("Chart saved to: " + filePath);
        } else {
            statusBar()->showMessage("Failed to save chart.");
        }
        delete newCanv;
    }
}

void MainWindow::changeTitle() {
    bool ok;
    QString newTitle = QInputDialog::getText(this, tr("Change Chart Title"), tr("Enter new chart title:"), QLineEdit::Normal, QString("POTATO"), &ok);
    if (ok && !newTitle.isEmpty()) {
        canv->setChartTitle(newTitle);
    }
}

//Mètodes del menú
void MainWindow::on_actionSave_triggered()
{
    saveChart();
}

void MainWindow::on_actionChange_Title_triggered()
{
    changeTitle();
}

void MainWindow::on_actionReset_triggered()
{
    canv->setBarAHeight(0);
    canv->setBarBHeight(0);

    QColor colorDefault = QColor(255, 255, 255);
    colorDefault.setAlpha(0);
    canv->setColorA(colorDefault);
    canv->setColorB(colorDefault);

    ui->spinBox_A->setValue(0);
    ui->spinBox_B->setValue(0);

    QString styleSheetDefault = "background-color: #ffffff;";
    ui->frameBarA->setStyleSheet(styleSheetDefault);
    ui->frameBarA->setStyleSheet(styleSheetDefault);

    QString defaultTitle = "DFAULT TITLE";
    canv->setChartTitle(defaultTitle);

    resolutionComboBox->setCurrentIndex(1);
}

