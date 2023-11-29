#pragma once

#include <QMainWindow>
#include <qevent.h>
#include <qpainter.h>
#include "ui_DrawArea.h"

class DrawArea : public QMainWindow
{
	Q_OBJECT

public:
	DrawArea(QWidget *parent = nullptr);
	~DrawArea();

    bool openImage(const QString& fileName);                         //incarca o imagine din fisier, poate fi modificata
    bool saveImage(const QString& fileName, const char* fileFormat); //salveaza imaginea curenta intr-un fisier
    void setPenColor(const QColor& newColor);                        
    void setPenWidth(int newWidth);

    bool isModified() const { return modified; }    // verifica daca s-a modificat ceva fata de starea anterioara
    QColor penColor() const { return myPenColor; }  // tine minte culoarea selectata
    int penWidth() const { return myPenWidth; }     // tine minte grosimea selectata

public slots:
    void clearImage();  //sterge imaginea curenta
    void print();       //afisarea imaginii curente

protected:
    void mousePressEvent(QMouseEvent* event) override;  //
    void mouseMoveEvent(QMouseEvent* event) override;   // aceste 3 functii au rolul de a implementa desenul
    void mouseReleaseEvent(QMouseEvent* event) override;//

    void paintEvent(QPaintEvent* event) override;       // pt. updatarea desenului
    void resizeEvent(QResizeEvent* event) override;     // verif. ca QImaginea pe care desenam sa fie minim de dimensiunea widgetului

private:
    Ui::DrawAreaClass ui;

    void drawLineTo(const QPoint& endPoint);                // excuta actiunea efectiva de desenare
    void resizeImage(QImage* image, const QSize& newSize);  // schimba marimile imaginii

    bool modified = false;
    bool scribbling = false;        // este true daca se tine apasat click in zona de desenare
    int myPenWidth = 1;
    QColor myPenColor = Qt::blue;
    QImage image;                   // contine imaginea desenata
    QPoint lastPoint;               // tine minte ultima pozitie a unei actiuni a mouse-ului
};
