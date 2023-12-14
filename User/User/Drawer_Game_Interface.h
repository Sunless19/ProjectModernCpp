#pragma once

#include <QMainWindow>
#include "ui_Drawer_Game_Interface.h"
#include <qevent.h>
#include <qpainter.h>
#include<QScreen>
#include<qrect.h>
class Drawer_Game_Interface : public QMainWindow
{
	Q_OBJECT

public:
	Drawer_Game_Interface(QWidget *parent = nullptr);
	~Drawer_Game_Interface();
protected:
    void mousePressEvent(QMouseEvent* event) override;  //
    void mouseMoveEvent(QMouseEvent* event) override;   // aceste 3 functii au rolul de a implementa desenul
    void mouseReleaseEvent(QMouseEvent* event) override;//
    bool isPointInsideAllowedRegion(const QPoint& point);
    void paintEvent(QPaintEvent* event) override;       // pt. updatarea desenului
    void resizeEvent(QResizeEvent* event) override;     // verif. ca QImaginea pe care desenam sa fie minim de dimensiunea widgetului
private:
	Ui::Drawer_Game_InterfaceClass ui;
    Ui::Drawer_Game_InterfaceClass drawdrawAreaUi;  // Adaugati aceasta linie
    void drawLineTo(const QPoint& endPoint);                // excuta actiunea efectiva de desenare
    void resizeImage(QImage* image, const QSize& newSize);  // schimba marimile imaginii

    bool modified = false;
    bool scribbling = false;        // este true daca se tine apasat click in zona de desenare
    int myPenWidth = 1;
    QColor myPenColor = Qt::blue;
    QImage image;                   // contine imaginea desenata
    QPoint lastPoint;               // tine minte ultima pozitie a unei actiuni�a�mouse-ului
};