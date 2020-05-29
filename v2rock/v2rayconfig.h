#ifndef V2RAYCONFIG_H
#define V2RAYCONFIG_H

#include <QDebug>
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
    ~V2RayConfig();

    void toJson(QJsonObject &json) const;

    static void fromJson(DNSObject &settings, const QJsonObject &json);
    static void toJson(DNSObject *settings, QJsonObject &json);

    static void fromJson(DNSServerObject &settings, const QJsonObject &json);
    static void toJson(const DNSServerObject *settings, QJsonObject &json);

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

    QList<V2RayConfigInbound *> getInbounds() const;
    void appendInbound(V2RayConfigInbound *value);
    void clearInbounds();

    QList<V2RayConfigOutbound *> getOutbounds() const;
    void appendOutbound(V2RayConfigOutbound *value);
    void clearOutbounds();

    V2RayConfigRoute getRouting() const;
    void setRouting(const V2RayConfigRoute &value);

private:
    PolicyObject *policy;
    ApiObject *api;
    DNSObject *dns;
    bool stats;
    V2RayConfigLog log;
    QList<V2RayConfigInbound *> inbounds;
    QList<V2RayConfigOutbound *> outbounds;
    V2RayConfigRoute routing;
};

#endif // V2RAYCONFIG_H
