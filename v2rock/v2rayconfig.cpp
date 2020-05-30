#include "v2rayconfig.h"

V2RayConfig::V2RayConfig() : policy(0), api(0), dns(0), stats(false)
{

}

V2RayConfig::~V2RayConfig()
{
    qDebug() << "Delete v2rayConfig";
    if (policy) delete policy;
    if (api) delete api;
    if (dns) delete dns;
    qDeleteAll(inbounds);
    qDeleteAll(outbounds);
}

DNSObject *V2RayConfig::getDns() const
{
    return dns;
}

void V2RayConfig::setDns(DNSObject *value)
{
    if (dns) delete dns;
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

QList<V2RayConfigInbound *> V2RayConfig::getInbounds() const
{
    return inbounds;
}

void V2RayConfig::appendInbound(V2RayConfigInbound *value)
{
    inbounds.append(value);
}

void V2RayConfig::clearInbounds()
{
    qDeleteAll(inbounds);
    inbounds.clear();
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
        toJson(dns, dnsObj);
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
    foreach (const V2RayConfigInbound *inbound, inbounds) {
        QJsonObject inboundObj;
        inbound->toJson(inboundObj);
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

void V2RayConfig::fromJson(DNSObject &settings, const QJsonObject &json)
{
    if (json.contains("tag") && json["tag"].isString()) {
        settings.tag = json["tag"].toString();
    } else {
        settings.tag = "dns-inbound";
    }
    if (json.contains("clientIp") && json["clientIp"].isString()) {
        settings.clientIp = json["clientIp"].toString();
    }
    if (json.contains("hosts") && json["hosts"].isObject()) {
        QJsonObject hostsObj = json["hosts"].toObject();
        foreach(const QString& key, hostsObj.keys()) {
            if (hostsObj.value(key).isString()) {
                settings.hosts.insert(key, hostsObj.value(key).toString());
            }
        }
    }
    if (json.contains("servers") && json["servers"].isArray()) {
        foreach(const QJsonValue& serverVal, json["servers"].toArray()) {
            if (serverVal.isString()) {
                settings.servers.append(serverVal.toString());
            } else if (serverVal.isObject()) {
                QJsonObject serverObj = serverVal.toObject();
                DNSServerObject *server = new DNSServerObject;
                fromJson(*server, serverObj);
                settings.serverObjects.append(server);
            }
        }
    }
}

void V2RayConfig::toJson(DNSObject *settings, QJsonObject &json)
{
    json["tag"] = settings->tag;
    json["clientIp"] = settings->clientIp;

    // QMap<QString, QString> hosts;
    QJsonObject hostsObj;
    QMapIterator<QString, QString> it(settings->hosts);
    while (it.hasNext()) {
        it.next();
        hostsObj[it.key()] = it.value();
    }
    json["hosts"] = hostsObj;

    // QStringList servers;
    // QList<DNSServerObject> serverObjects;
    QJsonArray serversArray;
    foreach (const QString server, settings->servers) {
        serversArray.append(server);
    }
    foreach (const DNSServerObject *server, settings->serverObjects) {
        QJsonObject serverObj;
        toJson(server, serverObj);
        serversArray.append(serverObj);
    }
    json["servers"] = serversArray;
}

void V2RayConfig::fromJson(DNSServerObject &settings, const QJsonObject &json)
{
    if (json.contains("address") && json["address"].isString()) {
        settings.address = json["address"].toString();
    }
    if (json.contains("port") && json["port"].isDouble()) {
        settings.port = json["port"].toInt();
    }
    if (json.contains("domains") && json["domains"].isArray()) {
        foreach(const QJsonValue& domainVal, json["domains"].toArray()) {
            if (domainVal.isString()) {
                settings.domains.append(domainVal.toString());
            }
        }
    }
    if (json.contains("expectIPs") && json["expectIPs"].isArray()) {
        foreach(const QJsonValue& ipVal, json["expectIPs"].toArray()) {
            if (ipVal.isString()) {
                settings.expectIPs.append(ipVal.toString());
            }
        }
    }
}

void V2RayConfig::toJson(const DNSServerObject *settings, QJsonObject &json)
{
    json["address"] = settings->address;
    if (!settings->domains.isEmpty()) {
        QJsonArray domainsArray;
        foreach (const QString domain, settings->domains) {
            domainsArray.append(domain);
        }
        json["domains"] = domainsArray;
    }
    if (!settings->expectIPs.isEmpty()) {
        QJsonArray ipsArray;
        foreach (const QString ip, settings->expectIPs) {
            ipsArray.append(ip);
        }
        json["expectIPs"] = ipsArray;
    }
    json["port"] = settings->port;
}
