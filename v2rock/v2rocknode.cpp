#include "v2rocknode.h"

V2RockNode::V2RockNode() :
    blackholeSettings(0), dNSSettings(0), freedomSettings(0), hTTPSettings(0), mTProtoSettings(0),
    shadowSocksSettings(0), socksSettings(0), vMessSettings(0), streamSettings(0), mux(0)
{

}

V2RockNode::~V2RockNode()
{
    qDebug() << "V2RockNode destruct";
    delete blackholeSettings;
    delete dNSSettings;
    delete freedomSettings;
    delete hTTPSettings;
    delete mTProtoSettings;
    delete shadowSocksSettings;
    delete socksSettings;
    delVMessSettings();

    delete streamSettings->sockopt;
    delete streamSettings->tlsSettings;
    delete streamSettings->tcpSettings;
    delete streamSettings->kcpSettings;
    delete streamSettings->wsSettings;
    delete streamSettings->httpSettings;
    delete streamSettings->dsSettings;
    delete streamSettings->quicSettings;
    delete streamSettings;
    delete mux;
}

QString V2RockNode::getName() const
{
    return name;
}

void V2RockNode::setName(const QString &value)
{
    name = value;
}

QString V2RockNode::getProtocol() const
{
    return protocol;
}

void V2RockNode::setProtocol(const QString &value)
{
    protocol = value;
}

OutboundBlackholeConfigurationObject *V2RockNode::getBlackholeSettings() const
{
    return blackholeSettings;
}

void V2RockNode::setBlackholeSettings(OutboundBlackholeConfigurationObject *value)
{
    blackholeSettings = value;
}

OutboundDNSConfigurationObject *V2RockNode::getDNSSettings() const
{
    return dNSSettings;
}

void V2RockNode::setDNSSettings(OutboundDNSConfigurationObject *value)
{
    dNSSettings = value;
}

OutboundFreedomConfigurationObject *V2RockNode::getFreedomSettings() const
{
    return freedomSettings;
}

void V2RockNode::setFreedomSettings(OutboundFreedomConfigurationObject *value)
{
    freedomSettings = value;
}

OutboundHTTPConfigurationObject *V2RockNode::getHTTPSettings() const
{
    return hTTPSettings;
}

void V2RockNode::setHTTPSettings(OutboundHTTPConfigurationObject *value)
{
    hTTPSettings = value;
}

OutboundMTProtoConfigurationObject *V2RockNode::getMTProtoSettings() const
{
    return mTProtoSettings;
}

void V2RockNode::setMTProtoSettings(OutboundMTProtoConfigurationObject *mTProtoSettings)
{
    mTProtoSettings = mTProtoSettings;
}

OutboundShadowsocksConfigurationObject *V2RockNode::getShadowSocksSettings() const
{
    return shadowSocksSettings;
}

void V2RockNode::setShadowSocksSettings(OutboundShadowsocksConfigurationObject *value)
{
    shadowSocksSettings = value;
}

OutboundSocksConfigurationObject *V2RockNode::getSocksSettings() const
{
    return socksSettings;
}

void V2RockNode::setSocksSettings(OutboundSocksConfigurationObject *value)
{
    socksSettings = value;
}

OutboundVMessConfigurationObject *V2RockNode::getVMessSettings() const
{
    return vMessSettings;
}

void V2RockNode::setVMessSettings(OutboundVMessConfigurationObject *value)
{
    delVMessSettings();
    vMessSettings = value;
}

void V2RockNode::delVMessSettings()
{
    if (vMessSettings) {
        qDebug() << "Delete vMessSettings";
        if (!vMessSettings->vnext.isEmpty()) {
            foreach (VMessServerObject const *server, vMessSettings->vnext) {
                qDeleteAll(server->users);
            }
            qDeleteAll(vMessSettings->vnext);
        }
    }
    delete vMessSettings;
}

StreamSettingsObject *V2RockNode::getStreamSettings() const
{
    return streamSettings;
}

void V2RockNode::setStreamSettings(StreamSettingsObject *value)
{
    streamSettings = value;
}

MuxObject *V2RockNode::getMux() const
{
    return mux;
}

void V2RockNode::setMux(MuxObject *value)
{
    mux = value;
}

void V2RockNode::read(const QJsonObject &json)
{
    if (json.contains("name") && json["name"].isString()) {
        name = json["name"].toString();
    }
    if (json.contains("protocol") && json["protocol"].isString()) {
        protocol = json["protocol"].toString();
    }
    if (json.contains("blackholeSettings") && json["blackholeSettings"].isObject()) {
        blackholeSettings = new OutboundBlackholeConfigurationObject;
        V2RayConfigOutbound::fromJson(*blackholeSettings, json["blackholeSettings"].toObject());
    } else {
        blackholeSettings = 0;
    }
    if (json.contains("dNSSettings") && json["dNSSettings"].isObject()) {
        dNSSettings = new OutboundDNSConfigurationObject;
        V2RayConfigOutbound::fromJson(*dNSSettings, json["dNSSettings"].toObject());
    } else {
        dNSSettings = 0;
    }
    if (json.contains("freedomSettings") && json["freedomSettings"].isObject()) {
        freedomSettings = new OutboundFreedomConfigurationObject;
        V2RayConfigOutbound::fromJson(*freedomSettings, json["freedomSettings"].toObject());
    } else {
        freedomSettings = 0;
    }
    if (json.contains("hTTPSettings") && json["hTTPSettings"].isObject()) {
        hTTPSettings = new OutboundHTTPConfigurationObject;
        V2RayConfigOutbound::fromJson(*hTTPSettings, json["hTTPSettings"].toObject());
    } else {
        hTTPSettings = 0;
    }
    if (json.contains("mTProtoSettings") && json["mTProtoSettings"].isObject()) {
        mTProtoSettings = new OutboundMTProtoConfigurationObject;
        V2RayConfigOutbound::fromJson(*mTProtoSettings, json["mTProtoSettings"].toObject());
    } else {
        mTProtoSettings = 0;
    }
    if (json.contains("shadowSocksSettings") && json["shadowSocksSettings"].isObject()) {
        shadowSocksSettings = new OutboundShadowsocksConfigurationObject;
        V2RayConfigOutbound::fromJson(*shadowSocksSettings, json["shadowSocksSettings"].toObject());
    } else {
        shadowSocksSettings = 0;
    }
    if (json.contains("socksSettings") && json["socksSettings"].isObject()) {
        socksSettings = new OutboundSocksConfigurationObject;
        V2RayConfigOutbound::fromJson(*socksSettings, json["socksSettings"].toObject());
    } else {
        socksSettings = 0;
    }
    if (json.contains("vMessSettings") && json["vMessSettings"].isObject()) {
        vMessSettings = new OutboundVMessConfigurationObject;
        V2RayConfigOutbound::fromJson(*vMessSettings, json["vMessSettings"].toObject());
    } else {
        vMessSettings = 0;
    }
    if (json.contains("streamSettings") && json["streamSettings"].isObject()) {
        streamSettings = new StreamSettingsObject;
        V2RayConfigOutbound::fromJson(*streamSettings, json["streamSettings"].toObject());
    } else {
        streamSettings = 0;
    }
    if (json.contains("mux") && json["mux"].isObject()) {
        mux = new MuxObject;
        V2RayConfigOutbound::fromJson(*mux, json["mux"].toObject());
    } else {
        mux = 0;
    }
}

void V2RockNode::write(QJsonObject &json) const
{
    json["name"] = name;
    json["protocol"] = protocol;
    if (blackholeSettings) {
        QJsonObject jsonObj;
        V2RayConfigOutbound::toJson(blackholeSettings, jsonObj);
        json["blackholeSettings"] = jsonObj;
    }
    if (dNSSettings) {
        QJsonObject jsonObj;
        V2RayConfigOutbound::toJson(dNSSettings, jsonObj);
        json["dNSSettings"] = jsonObj;
    }
    if (freedomSettings) {
        QJsonObject jsonObj;
        V2RayConfigOutbound::toJson(freedomSettings, jsonObj);
        json["freedomSettings"] = jsonObj;
    }
    if (hTTPSettings) {
        QJsonObject jsonObj;
        V2RayConfigOutbound::toJson(hTTPSettings, jsonObj);
        json["hTTPSettings"] = jsonObj;
    }
    if (mTProtoSettings) {
        QJsonObject jsonObj;
        V2RayConfigOutbound::toJson(mTProtoSettings, jsonObj);
        json["mTProtoSettings"] = jsonObj;
    }
    if (shadowSocksSettings) {
        QJsonObject jsonObj;
        V2RayConfigOutbound::toJson(shadowSocksSettings, jsonObj);
        json["shadowSocksSettings"] = jsonObj;
    }
    if (socksSettings) {
        QJsonObject jsonObj;
        V2RayConfigOutbound::toJson(socksSettings, jsonObj);
        json["socksSettings"] = jsonObj;
    }
    if (vMessSettings) {
        QJsonObject jsonObj;
        V2RayConfigOutbound::toJson(vMessSettings, jsonObj);
        json["vMessSettings"] = jsonObj;
    }
    if (streamSettings) {
        QJsonObject jsonObj;
        V2RayConfigOutbound::toJson(streamSettings, jsonObj);
        json["streamSettings"] = jsonObj;
    }
    if (mux) {
        QJsonObject jsonObj;
        V2RayConfigOutbound::toJson(mux, jsonObj);
        json["mux"] = jsonObj;
    }
}

void V2RockNode::print(int indentation) const
{
    const QString indent(indentation * 2, ' ');
    QTextStream(stdout) << indent << "protocol:\t" << protocol << "\n";
    QTextStream(stdout) << indent << "name:\t" << name << "\n";
}
