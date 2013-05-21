#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    int readSet=readSetting();
    ui->setupUi(this);
    autoStart();
}

MainWindow::~MainWindow()
{
    if(bStart)
    {
        p->kill();
    }
    //int saveRet = saveSetting();
    delete ui;
}

int MainWindow::readSetting()
{
    if(QFile::exists(conf))
    {
        configIni = new QSettings(conf, QSettings::IniFormat);
        configIni->setIniCodec("UTF8");
        configIni->beginGroup("Settings");
//        QString atrun=configIni->value("autoRun").toString();
//        bool ok;
//        autoRun = atrun.toInt(&ok, 10);
        autoRun = configIni->value("autoRun").toInt();
        filename = configIni->value("filename").toString();
        configIni->endGroup();
        return 1;
    }
    else
    {
        return -1;
    }
}

int MainWindow::saveSetting()
{
    //if(QFile::exists(conf))
    configIni = new QSettings(conf, QSettings::IniFormat);
    if(!configIni)
        return -1;
    else
    {
        configIni->setIniCodec("UTF8");
        configIni->beginGroup("Settings");
        configIni->setValue("autoRun",autoRun);
        configIni->setValue("filename",filename);
        configIni->endGroup();
//        QString confPath = configIni->fileName();
//        QMessageBox::information(this, "Warning", confPath, QMessageBox::Ok);
        return 1;
    }
}

int MainWindow::startRun()
{
    p = new QProcess;
    p->start(filename);
    bStart = p->waitForStarted();
    if(!bStart)
    {
        ui->lbInfo->setText(gatimeout);
    }
    else
    {
        qDebug()<<QString::fromLocal8Bit(p->readAllStandardOutput());
        ui->lbInfo->setText(gastart);
    }
    if(bStart)
        return 1;
    else
        return -1;
}

void MainWindow::autoStart()
{
    if(autoRun>0)
        ui->ckbAuto->setCheckState(Qt::Checked);
    else
        ui->ckbAuto->setCheckState(Qt::Unchecked);
    if(autoRun>0)
    {
        int startret = startRun();
    }
}

void MainWindow::on_btOpen_clicked()
{
    if(!bStart)
    {
        //QMessageBox::information(this, "Warning", "GoAgentUI is running!", QMessageBox::Ok | QMessageBox::Cancel);
        QString tmpFileName = QFileDialog::getOpenFileName(
                    this,
                    "Open Proxy.py",
                    QDir::currentPath(),
                    "Python files (*.py);;All files(*.*)");
        if (!tmpFileName.isNull()) { //用户选择了文件
            filename = tmpFileName;
            int startret = startRun();
            int saveRet = saveSetting();
        }
        else // 用户取消选择
            ui->lbInfo->setText(ganotfind);
    }
    else
    {
        ui->lbInfo->setText(garun);
    }
}

void MainWindow::on_btQuit_clicked()
{
    if(bStart)
    {
        p->kill();
        ui->lbInfo->setText(gakill);
        bStart = false;
        //ui->btQuit->setText("Start(A)");
    }
    else
    {
        ui->lbInfo->setText(ganotrun);
    }
}

void MainWindow::on_ckbAuto_stateChanged(int arg1)
{
    autoRun = arg1;
    int saveRet = saveSetting();
}

void MainWindow::on_btStart_clicked()
{
    if(bStart)
    {
        ui->lbInfo->setText(garun);
    }
    else if(QFile::exists(filename))
    {
        int startret = startRun();
    }
    else
    {
        ui->lbInfo->setText(ganotfind);
    }
}

void MainWindow::on_lbName_linkActivated(const QString &link)
{
    //QMessageBox::information(this, "Warning", "buaazp!", QMessageBox::Ok);
    QDesktopServices::openUrl(QUrl(QLatin1String(link.toLatin1().data())));
}
