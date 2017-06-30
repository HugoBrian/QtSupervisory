#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDateTime>
#include <QHostAddress>
#include <QTimer>
#include <QListWidget>
#include <QVector>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    socket = new QTcpSocket(this);



    connect(ui->pushButtonConnect,
            SIGNAL(clicked(bool)),
            this,
            SLOT(connectData()));

    connect(ui->pushButtonDisconnect,
            SIGNAL(clicked(bool)),
            this,
            SLOT(disconnectData()));


    connect(ui->pushButtonStart,
            SIGNAL(clicked(bool)),
            this,
            SLOT(startData()));

    connect(ui->pushButtonStop,
            SIGNAL(clicked(bool)),
            this,
            SLOT(stopData()));

    connect(ui->pushButtonUpdate,
            SIGNAL(clicked(bool)),
            this,
            SLOT(upData()));


}

void MainWindow::tcpConnect(){
    QString strIP;
    strIP = ui->lineEditIP->text();
    socket->connectToHost(strIP,1234);
    if(socket->waitForConnected(3000)){
        qDebug() << "Connected";
    }
    else{
        qDebug() << "Disconnected";
    }
    ui->widgetPlotter->setFundo(100,100,100);
}

void MainWindow::tcpDisconnect(){
    socket->disconnectFromHost();
    if(socket->waitForConnected(3000)){
        qDebug() << "Connected";
    }
    else{
        qDebug() << "Disconnected";
    }
}

void MainWindow::getData(){
    QString str;
    QByteArray array;
    QStringList list;
    qint64 thetime;
    QVector<long> vetorhora,vetorvalor;

    qDebug() << "to get data...";
    if(socket->state() == QAbstractSocket::ConnectedState){
        if(socket->isOpen()){
            qDebug() << "reading...";
            socket->write("get 127.0.0.1 5\r\n");
            socket->waitForBytesWritten();
            socket->waitForReadyRead();
            qDebug() << socket->bytesAvailable();
            while(socket->bytesAvailable()){
                str = socket->readLine().replace("\n","").replace("\r","");
                list = str.split(" ");
                if(list.size() == 2){
                    bool ok;
                    str = list.at(0);
                    thetime = str.toLongLong(&ok);
                    vetorhora.push_back(thetime);

                    str = list.at(1);
                    vetorvalor.push_back(str.toLongLong(&ok));

                    qDebug() << thetime << ": " << str;  

                }
            }
            qDebug() << "VALOR : " << "0" << vetorvalor.value(0);
            qDebug() << "VALOR : " << "1" << vetorvalor.value(1);
            qDebug() << "VALOR : " << "2" << vetorvalor.value(2);
            qDebug() << "VALOR : " << "3" << vetorvalor.value(3);
            qDebug() << "VALOR : " << "4" << vetorvalor.value(4);
            ui->widgetPlotter->setDados(vetorhora, vetorvalor);
        }
    }
}

void MainWindow::connectData(){
    tcpConnect();
    QHostAddress IP;
    QString IPs;

    IPs = ui->lineEditIP->text();
   // IP = socket->peerAddress();
   // IPs = IP.toString();
    ui->listWidget->addItem(IPs);
    //qDebug() <<	ui->listWidget->count();


}

void MainWindow::disconnectData(){
    tcpDisconnect();
}

void MainWindow::startData(){

    milisec = ui->horizontalSliderTime->value() * 1000;
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(getData()));
    timer->start(milisec);

}

void MainWindow::stopData(){
    timer->stop();
}

void MainWindow::upData(){
    tcpDisconnect();
    QString str;
    int x;
    for(int i=0;i<ui->listWidget->count();i++){
        bool y = ui->listWidget->item(i)->isSelected();
        if(y){x=i;}
    }
    str = ui->listWidget->item(x)->text();

    socket->connectToHost(str,1234);
    if(socket->waitForConnected(3000)){
        qDebug() << "Connected";
    }
    else{
        qDebug() << "Disconnected";
    }

}

MainWindow::~MainWindow()
{
    delete socket;
    delete ui;
}
