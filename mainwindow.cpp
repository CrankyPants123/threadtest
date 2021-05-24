#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    mythread = new MyThread();
    thread = new QThread(this);
    connect(mythread,&MyThread::myThreadrun,this,&MainWindow::dealThread);
    mythread->moveToThread(thread);
    connect(mythread,&MyThread::myThreadrun,this,&MainWindow::dealThread);

}

MainWindow::~MainWindow()
{
    delete ui;
}
MyThread::MyThread(QObject *parent){

}
void MyThread::run(){
    while(isrun == true){
        QThread::sleep(1);
        emit myThreadrun();
        qDebug()<<"child thread"<<QThread::currentThreadId();
        if(isrun == false)
            break;
    }
}

void MyThread::start(){
    qDebug()<<"开始";
    this->isrun = true;
}

void MyThread::stop(){
    qDebug() << "停止";
    this->isrun = false;
}

void MainWindow::on_pushButton_clicked()
{
    if(thread->isRunning() == true){
        return;
    }
    thread->start();
    mythread->start();
    emit runThread();
}

void MainWindow::on_stop_button_clicked()
{
    if(thread->isRunning() == false){
        return;
    }
    mythread->stop();
    thread->quit();
    thread->wait();
}
void MainWindow::dealThreadclose() {
    on_stop_button_clicked();
    delete mythread;
}

void MainWindow::dealThread() {
    static int i = 0;
    i++;
    ui->lcdNumber->display(i);
}
