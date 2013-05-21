#include "mainwindow.h"
#include <QApplication>
#include <QtSingleApplication>

int main(int argc, char *argv[])
{
    QtSingleApplication app(argc, argv);
    if (app.isRunning())
    {
        app.sendMessage("raies");
        QMessageBox::information(NULL, "Warning", "GoAgentUI is running!", QMessageBox::Ok);
        return EXIT_SUCCESS;
    }
    MainWindow w;
    w.show();
    app.setActivationWindow(&w, true);
    
    return app.exec();
}
