#ifndef CANVAS_H
#define CANVAS_H

#include <QWidget>
#include <QPainter>

class Canvas : public QWidget
{
    Q_OBJECT
public:
    Canvas(QWidget *parent = nullptr);

    void setBarAHeight(int value);
    void setBarBHeight(int value);

    void setColorA(const QColor &color);
    void setColorB(const QColor &color);

    QSize getCanvasSize() const;

    int getBarAHeight() const;
    int getBarBHeight() const;
    QColor getColorA() const;
    QColor getColorB() const;
    QString getChartTitle() const;

    void setChartTitle(const QString &title);


protected:
    void paintEvent( QPaintEvent* );

private:
    int barAHeight;
    int barBHeight;

    QColor colorA;
    QColor colorB;

    QString chartTitle = "DEFAULT TITLE";

};

#endif // CANVAS_H
