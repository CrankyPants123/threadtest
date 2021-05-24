#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QThread>
#include <QDebug>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE
class MyThread : public QObject{
    Q_OBJECT
public:
    MyThread(QObject *parent = nullptr);
    void run();
    void start();
    void stop();

    bool isrun = false;
signals:
    void myThreadrun();

private:
};
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void dealThread();
    MyThread *mythread = nullptr;
    QThread *thread = nullptr;
private slots:
    void on_pushButton_clicked();
    void dealThreadclose();

    void on_stop_button_clicked();

private:
    Ui::MainWindow *ui;
signals:
    void runThread();
    void stopThread();
};

#endif // MAINWINDOW_H
