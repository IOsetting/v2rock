#include "v2rayconfiginbound.h"

V2RayConfigInbound::V2RayConfigInbound() :
    sniffing(0), dokodemoDoorSettings(0), httpSettings(0), mTProtoSettings(0),
    shadowsocksSettings(0), socksSettings(0), vMessSettings(0)
{

}

V2RayConfigInbound::V2RayConfigInbound(const V2RayConfigInbound &a) :
    tag(a.tag), port(a.port), listen(a.listen), protocol(a.protocol),
    sniffing(0), dokodemoDoorSettings(0), httpSettings(0), mTProtoSettings(0),
    shadowsocksSettings(0), socksSettings(0), vMessSettings(0)
{
    if (a.sniffing) {
        sniffing = new SniffingObject(*(a.sniffing));
    }
    if (a.dokodemoDoorSettings) {
        dokodemoDoorSettings = new InboundDokodemoDoorConfigurationObject(*(a.dokodemoDoorSettings));
    }
    if (a.httpSettings) {
        httpSettings = new InboundHTTPConfigurationObject(*(a.httpSettings));
    }
    if (a.mTProtoSettings) {
        mTProtoSettings = new InboundMTProtoConfigurationObject(*(a.mTProtoSettings));
    }
    if (a.shadowsocksSettings) {
        shadowsocksSettings = new InboundShadowsocksConfigurationObject(*(a.shadowsocksSettings));
    }
    if (a.socksSettings) {
        socksSettings = new InboundSocksConfigurationObject(*(a.socksSettings));
    }
    if (a.vMessSettings) {
        vMessSettings = new InboundVMessConfigurationObject(*(a.vMessSettings));
    }
}

V2RayConfigInbound::~V2RayConfigInbound()
{
    if (sniffing) delete sniffing;
    if (dokodemoDoorSettings) delete dokodemoDoorSettings;
    if (httpSettings) delete httpSettings;
    if (mTProtoSettings) delete mTProtoSettings;
    if (shadowsocksSettings) delete shadowsocksSettings;
    if (socksSettings) delete socksSettings;
    if (vMessSettings) delete vMessSettings;
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

void V2RayConfigInbound::fromJson(const QJsonObject &json)
{
    if (json.contains("tag") && json["tag"].isString()) {
        tag = json["tag"].toString();
    }
    if (json.contains("port") && json["port"].isDouble()) {
        port = json["port"].toInt();
    }
    if (json.contains("listen") && json["listen"].isString()) {
        listen = json["listen"].toString();
    }
    if (json.contains("protocol") && json["protocol"].isString()) {
        protocol = json["protocol"].toString();
    }

    if (protocol == "socks" && json.contains("settings") && json["settings"].isObject()) {
        socksSettings = new InboundSocksConfigurationObject;
        fromJson(*socksSettings, json["settings"].toObject());
    } else {
        socksSettings = 0;
    }
    if (protocol == "http" && json.contains("settings") && json["settings"].isObject()) {
        httpSettings = new InboundHTTPConfigurationObject;
        fromJson(*httpSettings, json["settings"].toObject());
    } else {
        httpSettings = 0;
    }
    dokodemoDoorSettings = 0;
    mTProtoSettings = 0;
    shadowsocksSettings = 0;
    vMessSettings = 0;

    if (json.contains("sniffing") && json["sniffing"].isObject()) {
        sniffing = new SniffingObject;
        fromJson(*sniffing, json["sniffing"].toObject());
    } else {
        sniffing = 0;
    }

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
        toJson(socksSettings, settingsObj);
        json["settings"] = settingsObj;
    }

    if (protocol == "http" && httpSettings) {
        QJsonObject settingsObj;
        toJson(httpSettings, settingsObj);
        json["settings"] = settingsObj;
    }

    if (sniffing) {
        QJsonObject sniffingObj;
        toJson(sniffing, sniffingObj);
        json["sniffing"] = sniffingObj;
    } else {
        json["sniffing"] = QJsonValue(QJsonValue::Null);
    }
}

void V2RayConfigInbound::fromJson(AccountObject &account, const QJsonObject &json)
{
    if (json.contains("user") && json["user"].isString()) {
        account.user = json["user"].toString();
    }
    if (json.contains("pass") && json["pass"].isString()) {
        account.pass = json["pass"].toString();
    }
}

void V2RayConfigInbound::toJson(AccountObject *account, QJsonObject &json) const
{
    json["user"] = account->user;
    json["pass"] = account->pass;
}

void V2RayConfigInbound::fromJson(InboundHTTPConfigurationObject &settings, const QJsonObject &json)
{
    if (json.contains("timeout") && json["timeout"].isDouble()) {
        settings.timeout = json["timeout"].toInt();
    } else {
        settings.timeout = 1080;
    }
    if (json.contains("allowTransparent") && json["allowTransparent"].isBool()) {
        settings.allowTransparent = json["allowTransparent"].toBool();
    } else {
        settings.allowTransparent = false;
    }
    if (json.contains("userLevel") && json["userLevel"].isDouble()) {
        settings.userLevel = json["userLevel"].toInt();
    } else {
        settings.userLevel = 0;
    }
    if (json.contains("accounts") && json["accounts"].isArray()) {
        QJsonArray accounts = json["accounts"].toArray();
        for (int i = 0; i < accounts.size(); ++i) {
            AccountObject *account = new AccountObject;
            fromJson(*account, accounts[i].toObject());
            settings.accounts.append(account);
        }
    }
}

void V2RayConfigInbound::toJson(InboundHTTPConfigurationObject *settings, QJsonObject &json) const
{
    json["timeout"] = settings->timeout;
    json["allowTransparent"] = settings->allowTransparent;
    json["userLevel"] = settings->userLevel;
    // QList<struct AccountObject> *accounts;
    if (!settings->accounts.isEmpty()) {
        QJsonArray accountArray;
        foreach (const struct AccountObject *account, settings->accounts) {
            QJsonObject accountObj;
            accountObj["user"] = account->user;
            accountObj["pass"] = account->pass;
            accountArray.append(accountObj);
        }
        json["accounts"] = accountArray;
    }
}

void V2RayConfigInbound::fromJson(InboundSocksConfigurationObject &settings, const QJsonObject &json)
{
    if (json.contains("auth") && json["auth"].isString()) {
        settings.auth = json["auth"].toString();
    } else {
        settings.auth = "noauth";
    }
    if (json.contains("ip") && json["ip"].isString()) {
        settings.ip = json["ip"].toString();
    } else {
        settings.ip = "127.0.0.1";
    }
    if (json.contains("udp") && json["udp"].isBool()) {
        settings.udp = json["udp"].toBool();
    } else {
        settings.udp = false;
    }
    if (json.contains("accounts") && json["accounts"].isArray()) {
        QJsonArray accounts = json["accounts"].toArray();
        for (int i = 0; i < accounts.size(); ++i) {
            AccountObject *account = new AccountObject;
            fromJson(*account, accounts[i].toObject());
            settings.accounts.append(account);
        }
    }
}

void V2RayConfigInbound::toJson(InboundSocksConfigurationObject *settings, QJsonObject &json) const
{
    json["auth"] = settings->auth;
    json["ip"] = settings->ip;
    json["udp"] = settings->udp;
    // QList<struct AccountObject> *accounts;
    if (!settings->accounts.isEmpty()) {
        QJsonArray accountArray;
        foreach (const struct AccountObject *account, settings->accounts) {
            QJsonObject accountObj;
            accountObj["user"] = account->user;
            accountObj["pass"] = account->pass;
            accountArray.append(accountObj);
        }
        json["accounts"] = accountArray;
    }
}

void V2RayConfigInbound::fromJson(SniffingObject &sniffing, const QJsonObject &json)
{
    if (json.contains("enabled") && json["enabled"].isBool()) {
        sniffing.enabled = json["enabled"].toBool();
    } else {
        sniffing.enabled = false;
    }
    if (json.contains("destOverride") && json["destOverride"].isArray()) {
        QJsonArray array = json["destOverride"].toArray();
        for (int i = 0; i < array.size(); ++i) {
            sniffing.destOverride.append(array[i].toString());
        }
    }
}

void V2RayConfigInbound::toJson(SniffingObject *sniffing, QJsonObject &json) const
{
    json["enabled"] = sniffing->enabled;
    QJsonArray ovArray;
    foreach (const QString ov, sniffing->destOverride) {
        ovArray.append(ov);
    }
    json["destOverride"] = ovArray;
}
