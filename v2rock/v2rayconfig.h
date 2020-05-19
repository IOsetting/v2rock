#ifndef V2RAYCONFIG_H
#define V2RAYCONFIG_H

#include <QJsonArray>
#include <QJsonObject>
#include <QList>
#include <QString>

#include "v2rayconfiginbound.h"
#include "v2rayconfiglog.h"
#include "v2rayconfigoutbound.h"
#include "v2rayconfigroute.h"

class V2RayConfig
{
public:
    V2RayConfig();
    void toJson(QJsonObject &json) const;

    PolicyObject *getPolicy() const;
    void setPolicy(PolicyObject *value);

    ApiObject *getApi() const;
    void setApi(ApiObject *value);

    DNSObject *getDns() const;
    void setDns(DNSObject *value);

    bool getStats() const;
    void setStats(bool value);

    V2RayConfigLog getLog() const;
    void setLog(const V2RayConfigLog &value);

    QList<V2RayConfigInbound> getInbounds() const;
    void setInbounds(const QList<V2RayConfigInbound> &value);

    QList<V2RayConfigOutbound> getOutbounds() const;
    void setOutbounds(const QList<V2RayConfigOutbound> &value);

    V2RayConfigRoute getRouting() const;
    void setRouting(const V2RayConfigRoute &value);

private:
    PolicyObject *policy;
    ApiObject *api;
    DNSObject *dns;
    bool stats;
    V2RayConfigLog log;
    QList<V2RayConfigInbound> inbounds;
    QList<V2RayConfigOutbound> outbounds;
    V2RayConfigRoute routing;
};

#endif // V2RAYCONFIG_H
