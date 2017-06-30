#include "plotter.h"
#include <QPainter>
#include <QPen>
#include <QBrush>
#include <QDebug>

using namespace std;

Plotter::Plotter(QWidget *parent) : QWidget(parent){
    startTimer(10);
}

void Plotter::timerEvent(QTimerEvent *e){
    repaint();
}


void Plotter::paintEvent(QPaintEvent *e){

    // cria um objeto pintor
    QPainter p(this);

    // faz com que a linha seja desenhada
    // com tracos suaves
    p.setRenderHint(QPainter::Antialiasing);

    // cria um objeto de caneta
    QPen pen;
    // cria um objeto de pincel
    QBrush brush;
    // define a cor da caneta
    pen.setColor(QColor(255,0,0));
    pen.setWidth(2);

    // informa ao painter qual a caneta a ser
    // usada
    p.setPen(pen);

    // define a cor do pincel
    brush.setColor(fundo);
    brush.setStyle(Qt::SolidPattern);

    // informa ao painter qual o pincel a ser
    // usado
    p.setBrush(brush);
    p.drawRect(0,0,width(),y1());

    pen.setColor(QColor(0,0,255));
    p.setPen(pen);

    fundo.setRgb(200,200,255);
    p.setBackground(fundo);

    // desenha a linha do eixo de coordenadas
    //p.drawLine(0,height()/2,width(),height()/2);

    int x1,y1,x2;
    x1 = 0;
    y1 = height();
    x2 = width();

    p.drawLine(x1,  (y1 - valor.value(0)*8),100,(y1 - valor.value(1)*8));
    p.drawLine(100, (y1 - valor.value(1)*8),200,(y1 - valor.value(2)*8));
    p.drawLine(200, (y1 - valor.value(2)*8),300,(y1 - valor.value(3)*8));
    p.drawLine(300, (y1 - valor.value(3)*8),x2 ,(y1 - valor.value(4)*8));



    /*
    for(int i=1; i<width(); i++){
        if(valor.value(i) == valor.value(i-1)){
            x2 = 10;
        }else{
            x2 = x2 + 10;
        }
    y2 = height() - valor.value(i)*5 ;
    p.drawLine(x1, y1, x2, y2);

    x1 = x2;
    y1 = y2;
    }
    */



    /*
  x1 = 0;
  y1 = height()/2*(1- amp*sin(2*3.14*omega+teta));
  for(int i=1; i<width(); i++){
    x2 = i;
    y2 = height()/2*(1-amp*sin(2*3.14*omega*x2/width()+teta));
    p.drawLine(x1, y1, x2, y2);
    x1 = x2;
    y1 = y2;
  }
  */
}

void Plotter::setFundo(int r, int g, int b){
    fundo.setRgb(r,g,b);
    repaint();
}

void Plotter::setDados(QVector<long> _hora, QVector<long> _valor)
{
    this->hora = _hora;
    this->valor = _valor;
}
