#include "v2rayconfig.h"

V2RayConfig::V2RayConfig() : policy(0), api(0), dns(0), stats(false)
{

}

V2RayConfig::~V2RayConfig()
{
    qDebug() << "Delete v2rayConfig";
    delete policy;
    delete api;
    delete dns;
    qDeleteAll(outbounds);

    /*
    QList<V2RayConfigInbound> inbounds;
    V2RayConfigRoute routing;*/
}

DNSObject *V2RayConfig::getDns() const
{
    return dns;
}

void V2RayConfig::setDns(DNSObject *value)
{
    dns = value;
}

ApiObject *V2RayConfig::getApi() const
{
    return api;
}

void V2RayConfig::setApi(ApiObject *value)
{
    api = value;
}

PolicyObject *V2RayConfig::getPolicy() const
{
    return policy;
}

void V2RayConfig::setPolicy(PolicyObject *value)
{
    policy = value;
}

bool V2RayConfig::getStats() const
{
    return stats;
}

void V2RayConfig::setStats(bool value)
{
    stats = value;
}

V2RayConfigLog V2RayConfig::getLog() const
{
    return log;
}

void V2RayConfig::setLog(const V2RayConfigLog &value)
{
    log = value;
}

QList<V2RayConfigInbound> V2RayConfig::getInbounds() const
{
    return inbounds;
}

void V2RayConfig::setInbounds(const QList<V2RayConfigInbound> &value)
{
    inbounds = value;
}

QList<V2RayConfigOutbound *> V2RayConfig::getOutbounds() const
{
    return outbounds;
}

void V2RayConfig::appendOutbound(V2RayConfigOutbound *value)
{
    outbounds.append(value);
}

void V2RayConfig::clearOutbounds()
{
    qDeleteAll(outbounds);
    outbounds.clear();
}

V2RayConfigRoute V2RayConfig::getRouting() const
{
    return routing;
}

void V2RayConfig::setRouting(const V2RayConfigRoute &value)
{
    routing = value;
}

void V2RayConfig::toJson(QJsonObject &json) const
{
    // PolicyObject *policy;
    if (policy) {
        //QMap<QString, LevelPolicyObject> levels;
        QJsonObject levelsObj;
        QMapIterator<QString, LevelPolicyObject> it(policy->levels);
        while (it.hasNext()) {
            it.next();
            QJsonObject levelObj;
            levelObj["handshake"] = it.value().handshake;
            levelObj["connIdle"] = it.value().connIdle;
            levelObj["uplinkOnly"] = it.value().uplinkOnly;
            levelObj["downlinkOnly"] = it.value().downlinkOnly;
            levelObj["statsUserUplink"] = it.value().statsUserUplink;
            levelObj["statsUserDownlink"] = it.value().statsUserDownlink;
            levelObj["bufferSize"] = it.value().bufferSize;
            levelsObj[it.key()] = levelObj;
        }

        //SystemPolicyObject system;
        QJsonObject systemObj;
        systemObj["statsInboundDownlink"] = policy->system.statsInboundDownlink;
        systemObj["statsInboundUplink"] = policy->system.statsInboundUplink;

        QJsonObject policyObj;
        policyObj["levels"] = levelsObj;
        policyObj["system"] = systemObj;
        json["policy"] = policyObj;
    } else {
        json["policy"] = QJsonValue(QJsonValue::Null);
    }

    if (api) {
        QJsonObject apiObj;
        // QString tag;
        apiObj["tag"] = api->tag;

        //QStringList services;
        QJsonArray serviceArray;
        foreach (const QString service, api->services) {
            serviceArray.append(service);
        }
        apiObj["services"] = serviceArray;
        json["api"] = apiObj;
    } else {
        json["api"] = QJsonValue(QJsonValue::Null);
    }

    // DNSObject *dns;
    if (dns) {
        QJsonObject dnsObj;
        dnsObj["tag"] = dns->tag;
        dnsObj["clientIp"] = dns->clientIp;

        // QMap<QString, QString> hosts;
        QJsonObject hostsObj;
        QMapIterator<QString, QString> it(dns->hosts);
        while (it.hasNext()) {
            it.next();
            hostsObj[it.key()] = it.value();
        }
        dnsObj["hosts"] = hostsObj;

        // QStringList servers;
        // QList<DNSServerObject> serverObjects;
        QJsonArray serversArray;
        foreach (const QString server, dns->servers) {
            serversArray.append(server);
        }
        foreach (const DNSServerObject server, dns->serverObjects) {
            QJsonObject serverObj;
            serverObj["address"] = server.address;
            QJsonArray domainsArray;
            foreach (const QString domain, server.domains) {
                domainsArray.append(domain);
            }
            serverObj["domains"] = domainsArray;
            serverObj["port"] = server.port;
            serversArray.append(serverObj);
        }
        dnsObj["servers"] = serversArray;

        json["dns"] = dnsObj;
    } else {
        json["dns"] = QJsonValue(QJsonValue::Null);
    }

    // bool stats;
    if (stats) {
        QJsonObject statsObj;
        json["stats"] = statsObj;
    } else {
        json["stats"] = QJsonValue(QJsonValue::Null);
    }

    // V2RayConfigLog log;
    QJsonObject logObj;
    log.toJson(logObj);
    json["log"] = logObj;

    // QList<V2RayConfigInbound> inbounds;
    QJsonArray inboundArray;
    foreach (const V2RayConfigInbound inbound, inbounds) {
        QJsonObject inboundObj;
        inbound.toJson(inboundObj);
        inboundArray.append(inboundObj);
    }
    json["inbounds"] = inboundArray;

    // QList<V2RayConfigOutbound *> outbounds;
    QJsonArray outboundArray;
    foreach (const V2RayConfigOutbound *outbound, outbounds) {
        QJsonObject outboundObj;
        outbound->toJson(outboundObj);
        outboundArray.append(outboundObj);
    }
    json["outbounds"] = outboundArray;

    // V2RayConfigRoute routing;
    QJsonObject routeObj;
    routing.toJson(routeObj);
    json["routing"] = routeObj;
}
