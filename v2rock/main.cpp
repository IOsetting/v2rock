#include <QApplication>
#include <QtGlobal>
#include <QLibraryInfo>
#include <QScreen>
#include <QTranslator>

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
    // Qt::AA_EnableHighDpiScaling must be set before QCoreApplication is created.
#if QT_VERSION >= QT_VERSION_CHECK(5, 6, 0)
    bool EnableHighDpiScaling = false;
    {
        // This is a hack to avoid double-size-window issue on Qt under 5.12
        QApplication a(argc, argv);
        if ( a.screens().at(0)->geometry().width() > 1920) EnableHighDpiScaling = true;
    }
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling, EnableHighDpiScaling);
#endif
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

    QTranslator qtTranslator;
    qtTranslator.load("qt_" + QLocale::system().name(), QLibraryInfo::location(QLibraryInfo::TranslationsPath));
    a.installTranslator(&qtTranslator);

    QTranslator v2rockTranslator;
    bool bret = v2rockTranslator.load("v2rock_" + QLocale::system().name(), ":/languages");
    if(!bret) {
       qDebug() << QString("No language file: v2rock_%1.qm").arg(QLocale::system().name());
    }
    a.installTranslator(&v2rockTranslator);

    MainDialog w;
    w.show();

    return a.exec();
}
