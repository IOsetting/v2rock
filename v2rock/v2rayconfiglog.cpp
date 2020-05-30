#include "v2rayconfiglog.h"

V2RayConfigLog::V2RayConfigLog()
{

}

V2RayConfigLog::V2RayConfigLog(const V2RayConfigLog &a) :
    loglevel(a.loglevel), access(a.access), error(a.error) {}

QString V2RayConfigLog::getLoglevel() const
{
    return loglevel;
}

void V2RayConfigLog::setLoglevel(const QString &value)
{
    loglevel = value;
}

QString V2RayConfigLog::getAccess() const
{
    return access;
}

void V2RayConfigLog::setAccess(const QString &value)
{
    access = value;
}

QString V2RayConfigLog::getError() const
{
    return error;
}

void V2RayConfigLog::setError(const QString &value)
{
    error = value;
}

void V2RayConfigLog::toJson(QJsonObject &json) const
{
    json["loglevel"] = loglevel;

    if (access.isEmpty()) {
        json["access"] = QJsonValue(QJsonValue::Null);
    } else {
        json["access"] = access;
    }

    if (error.isEmpty()) {
        json["error"] = QJsonValue(QJsonValue::Null);
    } else {
        json["error"] = error;
    }
}
