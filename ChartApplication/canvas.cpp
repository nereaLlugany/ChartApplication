#include "canvas.h"

//Constructora
Canvas::Canvas(QWidget *parent)
    : QWidget{parent}, barAHeight(0), barBHeight(0), colorA(Qt::transparent), colorB(Qt::transparent)
{}

//Setters
void Canvas::setBarAHeight(int value) {
    barAHeight = value*3;
    update();
}

void Canvas::setBarBHeight(int value) {
    barBHeight = value*3;
    update();
}

void Canvas::setColorA(const QColor &color) {
    colorA = color;
    update();
}

void Canvas::setColorB(const QColor &color) {
    colorB = color;
    update();
}

void Canvas::setChartTitle(const QString &title){
    chartTitle = title;
    update();
}

//Getters
QSize Canvas::getCanvasSize() const {
    return QSize(width(), height());
}

int Canvas::getBarAHeight() const{
    return barAHeight;
}
int Canvas::getBarBHeight() const{
    return barBHeight;
}
QColor Canvas::getColorA() const{
    return colorA;
}

QColor Canvas::getColorB() const{
    return colorB;
}

QString Canvas::getChartTitle() const{
    return chartTitle;
}
//Mètodes
void Canvas::paintEvent(QPaintEvent* event)
{
    QWidget::paintEvent(event);
    QPainter painter(this);

    //Agafar les mesures del Canvas on està tot dibuixat
    int canvasWidth = width();
    int canvasHeight = height();
    //Fer que ocupi tot el widget de la ui Chart
    setFixedSize(parentWidget()->width(), parentWidget()->height());

    //Mesures per poder modificar la mesura sense deformar res
    double widthRatio = double(canvasWidth) / 750.0;
    double heightRatio = double(canvasHeight) / 470.0;

    //Crear el "pinzell" per poder dibuixar les guies dels valors
    QPen dashedPen(Qt::black);
    dashedPen.setWidth(0.5);
    dashedPen.setStyle(Qt::DashLine);
    painter.setPen(dashedPen);

    painter.drawLine(140 * widthRatio, 390 * heightRatio, 650 * widthRatio, 390 * heightRatio); //Linia del 0
    painter.drawLine(140 * widthRatio, 315 * heightRatio, 650 * widthRatio, 315 * heightRatio); //Linia del 25
    painter.drawLine(140 * widthRatio, 240 * heightRatio, 650 * widthRatio, 240 * heightRatio); //Linia del 50
    painter.drawLine(140 * widthRatio, 165 * heightRatio, 650 * widthRatio, 165 * heightRatio); //Linia del 75
    painter.drawLine(140* widthRatio, 90 * heightRatio, 650 * widthRatio, 90 * heightRatio); //Linia del 100

    //Crear el "pinzell" per poder dibuixar tot el diagrama
    QPen pen(Qt::black);
    pen.setWidth(2.5 * widthRatio);
    painter.setPen(pen);

    //Eixos d’abscisses i ordenades
    painter.drawLine(150 * widthRatio, 50 * heightRatio, 150 * widthRatio, 390 * heightRatio); //Vertical
    painter.drawLine(150 * widthRatio, 390 * heightRatio, 650 * widthRatio, 390 * heightRatio); //Horizontal

    //Linies dels valors
    painter.drawLine(150 * widthRatio, 390 * heightRatio, 140 * widthRatio, 390 * heightRatio); //Linia del 0
    painter.drawLine(150 * widthRatio, 315 * heightRatio, 140 * widthRatio, 315 * heightRatio); //Linia del 25
    painter.drawLine(150 * widthRatio, 240 * heightRatio, 140 *widthRatio, 240 * heightRatio); //Linia del 50
    painter.drawLine(150 * widthRatio, 165 * heightRatio, 140 * widthRatio, 165 * heightRatio); //Linia del 75
    painter.drawLine(150* widthRatio, 90 * heightRatio, 140* widthRatio, 90 * heightRatio); //Linia del 100

    //"Àrea" dels rectangles que representen les barres del diagrama
    painter.fillRect(270 * widthRatio, 150 * heightRatio + (240 - barAHeight) * heightRatio, 60 * widthRatio, barAHeight * heightRatio,  colorA); //Rectangle A
    painter.fillRect(470 * widthRatio, 150 * heightRatio + (240 - barBHeight) * heightRatio, 60 * widthRatio, barBHeight * heightRatio,  colorB);//Rectangle B

    //"Perimetre" dels rectangles que representen les barres del diagrama
    painter.drawRect(270 * widthRatio, 150 * heightRatio + (240 - barAHeight) * heightRatio, 60 * widthRatio, barAHeight * heightRatio); //Rectangle A
    painter.drawRect(470 * widthRatio, 150 * heightRatio + (240 - barBHeight) * heightRatio, 60 * widthRatio, barBHeight * heightRatio);//Rectangle B

    //Definir les propietats del text del diagrama
    int fontSize = int(15 * widthRatio);
    painter.setFont(QFont("UD Digi Kyokasho N-B", fontSize, QFont::Bold));
    painter.drawText(QPointF(int(348 * widthRatio), int(55 * heightRatio)), chartTitle);

    fontSize = int(12 * widthRatio);
    painter.setFont(QFont("UD Digi Kyokasho N-B", fontSize, QFont::Bold));

    //Escriptura dels valors del diagrama
    painter.drawText(QPointF(int(120 * widthRatio), int(395 * heightRatio)), "0");
    painter.drawText(QPointF(int(110 * widthRatio), int(320 * heightRatio)), "25");
    painter.drawText(QPointF(int(110 * widthRatio), int(245 * heightRatio)), "50");
    painter.drawText(QPointF(int(110 * widthRatio), int(170 * heightRatio)), "75");
    painter.drawText(QPointF(int(100 * widthRatio), int(95 * heightRatio)), "100");

    //Escriptura per distinguir la barra A i la barra B
    painter.drawText(QPointF(int(300 * widthRatio), int(415 * heightRatio)), "A");
    painter.drawText(QPointF(int(500 * widthRatio), int(415 * heightRatio)), "B");
}
