#include "pingprocess.h"

PingProcess::PingProcess(QObject *parent) : QObject(parent)
{
    process = new QProcess(this);
    connect(process, SIGNAL(started()), this, SLOT(verifyStatus()));
    connect(process, SIGNAL(finished(int,QProcess::ExitStatus)), this, SLOT(processFinished(int,QProcess::ExitStatus)));
}

PingProcess::~PingProcess()
{
    if (state() != QProcess::NotRunning)
    {
        qDebug() << "Kill process";
        process->kill();
    }
    delete process;
}

void PingProcess::start(const QString &command, const QStringList &args)
{
    if (state() == QProcess::NotRunning)
    {
        process->start(command, args);
        process->waitForStarted(7000);
    }
    else
    {
        emit logReceived("Still running...");
    }
}

void PingProcess::stop()
{
    if (state() == QProcess::NotRunning)
    {
        emit logReceived("Not running");
    }
    else
    {
        qDebug() << "Kill process";
        emit logReceived("Kill process");
        process->kill();
    }
}

QProcess::ProcessState PingProcess::state() const
{
    return process->state();
}

void PingProcess::verifyStatus()
{
    if(process->isReadable())
    {
        qDebug() << "Read on ...";
        connect(process, SIGNAL(readyReadStandardOutput()), this, SLOT(readyReadStandardOutput()));
    }
    else
    {
        qDebug() << "Not able to read ...";
    }
}

void PingProcess::processFinished(int exitCode, QProcess::ExitStatus exitStatus)
{
    qDebug() << "Finished: " << exitCode;
    disconnect(process, SIGNAL(readyReadStandardOutput()), this, SLOT(readyReadStandardOutput()));
    emit finished(exitCode, exitStatus);
}

void PingProcess::readyReadStandardOutput()
{
    QByteArray bytes = process->readAllStandardOutput();
    if (bytes.lastIndexOf("\n") == bytes.size() - 1)
    {
        bytes = bytes.mid(0, bytes.size() - 1);
    }
    emit logReceived(bytes);
    qDebug() << "output:" << bytes;
}
