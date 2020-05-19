#include <QApplication>

#include "config.h"
#include "maindialog.h"


bool isRunningAlready()
{
    QStringList arguments;
    arguments << "-A";

    QProcess *ch = new QProcess();
    ch->start("ps", arguments);
    ch->waitForFinished(5000);
    ch->waitForReadyRead(5000);
    QString line;
    int count = 0;
    while(!ch->atEnd())
    {
        line = QString::fromLatin1(ch->readLine());
        if(line.contains(QFileInfo(QCoreApplication::applicationFilePath()).fileName()))
            count++;
    }
    delete ch;

    return (count > 1) ? true : false;
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QApplication::setApplicationName(v2rock_config::name);
    QApplication::setApplicationVersion(v2rock_config::version);
    a.setQuitOnLastWindowClosed(false);

    if(isRunningAlready()) {
        QMessageBox::critical(
                    NULL,
                    "Error",
                    "V2rock is already running.",
                    QMessageBox::Ok);
        exit(0);
    }

    MainDialog w;
    w.show();

    return a.exec();
}
