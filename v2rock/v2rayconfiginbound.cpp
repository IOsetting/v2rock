#include "v2rayconfiginbound.h"

V2RayConfigInbound::V2RayConfigInbound() :
    sniffing(0), httpSettings(0), socksSettings(0), vMessSettings(0)
{

}

QString V2RayConfigInbound::getTag() const
{
    return tag;
}

void V2RayConfigInbound::setTag(const QString &value)
{
    tag = value;
}

int V2RayConfigInbound::getPort() const
{
    return port;
}

void V2RayConfigInbound::setPort(int value)
{
    port = value;
}

QString V2RayConfigInbound::getListen() const
{
    return listen;
}

void V2RayConfigInbound::setListen(const QString &value)
{
    listen = value;
}

QString V2RayConfigInbound::getProtocol() const
{
    return protocol;
}

void V2RayConfigInbound::setProtocol(const QString &value)
{
    protocol = value;
}

SniffingObject *V2RayConfigInbound::getSniffing() const
{
    return sniffing;
}

void V2RayConfigInbound::setSniffing(SniffingObject *value)
{
    sniffing = value;
}

InboundDokodemoDoorConfigurationObject *V2RayConfigInbound::getDokodemoDoorSettings() const
{
    return dokodemoDoorSettings;
}

void V2RayConfigInbound::setDokodemoDoorSettings(InboundDokodemoDoorConfigurationObject *value)
{
    dokodemoDoorSettings = value;
}

InboundHTTPConfigurationObject *V2RayConfigInbound::getHttpSettings() const
{
    return httpSettings;
}

void V2RayConfigInbound::setHttpSettings(InboundHTTPConfigurationObject *value)
{
    httpSettings = value;
}

InboundMTProtoConfigurationObject *V2RayConfigInbound::getTProtoSettings() const
{
    return mTProtoSettings;
}

void V2RayConfigInbound::setTProtoSettings(InboundMTProtoConfigurationObject *tProtoSettings)
{
    mTProtoSettings = tProtoSettings;
}

InboundShadowsocksConfigurationObject *V2RayConfigInbound::getShadowsocksSettings() const
{
    return shadowsocksSettings;
}

void V2RayConfigInbound::setShadowsocksSettings(InboundShadowsocksConfigurationObject *value)
{
    shadowsocksSettings = value;
}

InboundSocksConfigurationObject *V2RayConfigInbound::getSocksSettings() const
{
    return socksSettings;
}

void V2RayConfigInbound::setSocksSettings(InboundSocksConfigurationObject *value)
{
    socksSettings = value;
}

InboundVMessConfigurationObject *V2RayConfigInbound::getVMessSettings() const
{
    return vMessSettings;
}

void V2RayConfigInbound::setVMessSettings(InboundVMessConfigurationObject *value)
{
    vMessSettings = value;
}

void V2RayConfigInbound::toJson(QJsonObject &json) const
{
    json["tag"] = tag;
    json["port"] = port;
    json["listen"] = listen;
    json["protocol"] = protocol;

    json["settings"] = QJsonValue(QJsonValue::Null);
    if (protocol == "socks" && socksSettings) {
        QJsonObject settingsObj;
        settingsObj["auth"] = socksSettings->auth;
        settingsObj["ip"] = socksSettings->ip;
        settingsObj["udp"] = socksSettings->udp;
        // QList<struct AccountObject> *accounts;
        if (socksSettings->accounts) {
            QJsonArray accountArray;
            foreach (const struct AccountObject account, *(socksSettings->accounts)) {
                QJsonObject accountObj;
                accountObj["user"] = account.user;
                accountObj["pass"] = account.pass;
                accountArray.append(accountObj);
            }
            settingsObj["accounts"] = accountArray;
        }
        json["settings"] = settingsObj;
    }

    if (protocol == "http" && httpSettings) {
        QJsonObject settingsObj;
        settingsObj["timeout"] = httpSettings->timeout;
        settingsObj["allowTransparent"] = httpSettings->allowTransparent;
        settingsObj["userLevel"] = httpSettings->userLevel;
        // QList<struct AccountObject> *accounts;
        if (httpSettings->accounts) {
            QJsonArray accountArray;
            foreach (const struct AccountObject account, *(httpSettings->accounts)) {
                QJsonObject accountObj;
                accountObj["user"] = account.user;
                accountObj["pass"] = account.pass;
                accountArray.append(accountObj);
            }
            settingsObj["accounts"] = accountArray;
        }
        json["settings"] = settingsObj;
    }

    if (sniffing) {
        QJsonObject sniffingObj;
        sniffingObj["enabled"] = sniffing->enabled;
        QJsonArray ovArray;
        foreach (const QString ov, sniffing->destOverride) {
            ovArray.append(ov);
        }
        sniffingObj["destOverride"] = ovArray;
        json["sniffing"] = sniffingObj;
    } else {
        json["sniffing"] = QJsonValue(QJsonValue::Null);
    }
}
