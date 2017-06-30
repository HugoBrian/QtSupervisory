#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QDebug>
#include <QTimer>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void tcpConnect();
    void tcpDisconnect();

public slots:
    void putData();
    void connectData();
    void disconnectData();
    void startData();
    void stopData();
private:
    Ui::MainWindow *ui;
    QTcpSocket *socket;
    int milisec;
    QTimer *timer;
};

#endif // MAINWINDOW_H
