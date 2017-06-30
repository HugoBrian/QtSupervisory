#ifndef PLOTTER_H
#define PLOTTER_H

#include <QWidget>
#include <QColor>
#include <QVector>

class Plotter : public QWidget
{
    Q_OBJECT
private:
    QVector<long> hora,valor;
    QColor fundo;

public:
    explicit Plotter(QWidget *parent = 0);
    void paintEvent(QPaintEvent *e);
    void timerEvent(QTimerEvent *e);
    void setFundo(int r, int g, int b);
    void setDados(QVector<long> _hora, QVector<long> _valor);

signals:

public slots:

};

#endif // PLOTTER_H
