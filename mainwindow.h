#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QFileDialog>
#include <QMessageBox>
#include <QProcess>
#include <QDebug>
#include <QSettings>
#include <QDesktopServices>
#include <QUrl>
#include <QString>

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
    void autoStart();
    void autoHideWin();
    int startRun();
    int getAutoRun();
    
private slots:
    void on_btOpen_clicked();

    void on_btQuit_clicked();
    
    void on_ckbAuto_stateChanged(int arg1);

    void on_btStart_clicked();

    void on_lbName_linkActivated(const QString &link);

    void on_cbHide_stateChanged(int arg1);

    void redFromStdOut();

    void redFromStdErr();

    void processError(QProcess::ProcessError error);

    void processFinished(int exitCode,QProcess::ExitStatus exitStatus);

private:
    Ui::MainWindow *ui;
    const QString gainstart="GoAgent is Starting!";
    const QString gastart="GoAgent Started!";
    const QString gafial="GoAgent start Failed!";
    const QString gatimeout="GoAgent start Timeout!";
    const QString gakill="GoAgent is terminated!";
    const QString garun="GoAgent is running!";
    const QString ganotrun="GoAgent is not running!";
    const QString ganotfind="GoAgent not find!";
    const QString errflag="error";
    bool bStart = false;
    bool bFinish = false;
    QSettings *configIni;
    const QString conf="gauiconf.ini";
    QProcess *p;

    int autoRun = 0;
    int autoHide = 0;
    QString filename;
};

#endif // MAINWINDOW_H
