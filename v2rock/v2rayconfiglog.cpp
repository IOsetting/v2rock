#include "v2rayconfiglog.h"

V2RayConfigLog::V2RayConfigLog() : access(0), error(0)
{

}

QString V2RayConfigLog::getLoglevel() const
{
    return loglevel;
}

void V2RayConfigLog::setLoglevel(const QString &value)
{
    loglevel = value;
}

QString *V2RayConfigLog::getAccess() const
{
    return access;
}

void V2RayConfigLog::setAccess(QString *value)
{
    access = value;
}

QString *V2RayConfigLog::getError() const
{
    return error;
}

void V2RayConfigLog::setError(QString *value)
{
    error = value;
}

void V2RayConfigLog::toJson(QJsonObject &json) const
{
    json["loglevel"] = loglevel;

    if (access) {
        json["access"] = *access;
    } else {
        json["access"] = QJsonValue(QJsonValue::Null);
    }

    if (error) {
        json["error"] = *error;
    } else {
        json["error"] = QJsonValue(QJsonValue::Null);
    }
}
