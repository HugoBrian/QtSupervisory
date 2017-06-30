#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDateTime>
#include <QTimer>


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

}

void MainWindow::tcpConnect(){
    QString strIP;
    strIP = ui->lineEditIP->text();
    socket->connectToHost(strIP,1234);
    if(socket->waitForConnected(3000)){
        qDebug() << "Connected";
        ui->textBrowser->append("Connected");
    }
    else{
        qDebug() << "Disconnected";
        ui->textBrowser->append("Disconnected");
    }
}

void MainWindow::tcpDisconnect(){
    socket->disconnectFromHost();
    if(socket->waitForConnected(3000)){
        qDebug() << "Connected";
    }
    else{
        qDebug() << "Disconnected";
        ui->textBrowser->append("Disconnected");
    }
}


void MainWindow::putData(){
    QDateTime datetime;
    QString str,str2,numRand;
    qint64 msecdate;

    int max,mim,num;

    mim = ui->horizontalSliderMin->value() ;
    max = ui->horizontalSliderMax->value()+1 ;

    if(mim>=max){
        num = qrand()%max;
    }else{
        num = mim + (qrand()%(max-mim));
    }
    if(socket->state()== QAbstractSocket::ConnectedState){
        datetime = QDateTime::currentDateTime();
        msecdate = QDateTime::currentDateTime().toMSecsSinceEpoch();
        numRand = QString::number(num) + "\r\n";
        str = "set "+ QString::number(msecdate) + " " + numRand;
        str2 = "set "+ datetime.toString(Qt::ISODate)+ " "+ numRand;

        ui->textBrowser->append(str2);

        qDebug() << str;
        qDebug() << socket->write(str.toStdString().c_str()) << " bytes written";
        if(socket->waitForBytesWritten(3000)){
            qDebug() << "wrote";

        }
    }
}

void MainWindow::connectData()
{
    tcpConnect();
}

void MainWindow::disconnectData()
{
    tcpDisconnect();
}

void MainWindow::startData()
{

    milisec = ui->horizontalSliderTime->value() * 1000;
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(putData()));
    timer->start(milisec);

}

void MainWindow::stopData()
{
    timer->stop();
}



MainWindow::~MainWindow(){
    delete socket;
    delete ui;
}

