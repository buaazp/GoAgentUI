#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>
#include <QProcess>
#include <QDebug>
#include <QSettings>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    int readSetting();
    int saveSetting();
    
private slots:
    void on_btOpen_clicked();

    void on_btQuit_clicked();
    
    void on_ckbAuto_stateChanged(int arg1);

    void on_btStart_clicked();

private:
    Ui::MainWindow *ui;
    QString gastart="GoAgent Started!";
    QString gafial="GoAgent Failed!";
    QString gatimeout="GoAgent Timeout!";
    QString gakill="GoAgent terminated!";
    QString garun="GoAgent is running!";
    QString ganotrun="GoAgent is not running!";
    QString ganotfind="GoAgent not find!";
    bool bStart = false;
    QSettings *configIni;
    QString conf="./config.ini";
    QProcess *p;

    int autoRun = 0;
    QString filename;
};

#endif // MAINWINDOW_H
