#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QTableWidgetItem>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


private:
    Ui::MainWindow *ui;
    QTimer *timer;

private slots:
    void timer_aufruf(void);
    void message_in (QByteArray data);



    void on_pushButton_clicked();
    void on_pushButton_SetHall_clicked();



    void on_pushButton_Save_clicked();
    void on_pushButton_Set_Mode_clicked();
    void on_pushButton_Get_State_clicked();
    void on_pushButton_Set_Application_Mode_clicked();
    void on_checkBox_Send_Cyclic_stateChanged(int arg1);
    void on_checkBox_Enable_RPS_Info_stateChanged(int arg1);
    void on_checkBox_Enable_Hall_Detection_stateChanged(int arg1);
    void on_checkBox_1H_stateChanged(int arg1);
    void on_checkBox_1L_stateChanged(int arg1);
    void on_checkBox_2H_stateChanged(int arg1);
    void on_checkBox_2L_stateChanged(int arg1);
    void on_checkBox_3H_stateChanged(int arg1);
    void on_checkBox_3L_stateChanged(int arg1);
};

#endif // MAINWINDOW_H
