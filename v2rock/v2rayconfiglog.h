#ifndef V2RAYCONFIGLOG_H
#define V2RAYCONFIGLOG_H

#include <QJsonObject>
#include <QString>

class V2RayConfigLog
{
public:
    V2RayConfigLog();
    void toJson(QJsonObject &json) const;

    QString getLoglevel() const;
    void setLoglevel(const QString &value);


    QString getAccess() const;
    void setAccess(const QString &value);

    QString getError() const;
    void setError(const QString &value);

private:
    //LogLevel {debug, info, warning, error, none};
    QString loglevel;
    QString access;
    QString error;
};

#endif // V2RAYCONFIGLOG_H
