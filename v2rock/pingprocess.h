#ifndef PINGPROCESS_H
#define PINGPROCESS_H

#include <QDebug>
#include <QObject>
#include <QProcess>

class PingProcess : public QObject
{
    Q_OBJECT

public:
    explicit PingProcess(QObject *parent = nullptr);
    ~PingProcess();
    void start(const QString &command, const QStringList &args);
    void stop();
    QProcess::ProcessState state() const;

signals:
     void logReceived(const QString&);
     void finished(int exitCode, QProcess::ExitStatus exitStatus);

public slots:
    void verifyStatus();
    void processFinished(int exitCode, QProcess::ExitStatus exitStatus);
    void readyReadStandardOutput();

private:
    QProcess *process;
};

#endif // PINGPROCESS_H
