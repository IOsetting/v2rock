#include "v2rocknode.h"

V2RockNode::V2RockNode() : name(""), protocol("vmess"),
    blackholeSettings(0), dNSSettings(0), freedomSettings(0), hTTPSettings(0), mTProtoSettings(0),
    shadowSocksSettings(0), socksSettings(0), vMessSettings(0), streamSettings(0), mux(0)
{

}

V2RockNode::V2RockNode(const V2RockNode &a) :
    name(a.name), protocol(a.protocol),
    blackholeSettings(0), dNSSettings(0), freedomSettings(0), hTTPSettings(0), mTProtoSettings(0),
    shadowSocksSettings(0), socksSettings(0), vMessSettings(0), streamSettings(0), mux(0)
{
    if (a.getBlackholeSettings()) {
        blackholeSettings = new OutboundBlackholeConfigurationObject(*(a.getBlackholeSettings()));
    }
    if (a.getDNSSettings()) {
        dNSSettings = new OutboundDNSConfigurationObject(*(a.getDNSSettings()));
    }
    if (a.getFreedomSettings()) {
        freedomSettings = new OutboundFreedomConfigurationObject(*(a.getFreedomSettings()));
    }
    if (a.getHTTPSettings()) {
        hTTPSettings = new OutboundHTTPConfigurationObject(*(a.getHTTPSettings()));
    }
    if (a.getMTProtoSettings()) {
        mTProtoSettings = new OutboundMTProtoConfigurationObject(*(a.getMTProtoSettings()));
    }
    if (a.getShadowSocksSettings()) {
        shadowSocksSettings = new OutboundShadowsocksConfigurationObject(*(a.getShadowSocksSettings()));
    }
    if (a.getSocksSettings()) {
        socksSettings = new OutboundSocksConfigurationObject(*(a.getSocksSettings()));
    }
    if (a.getVMessSettings()) {
        vMessSettings = new OutboundVMessConfigurationObject(*(a.getVMessSettings()));
    }
    if (a.getStreamSettings()) {
        streamSettings = new StreamSettingsObject(*(a.getStreamSettings()));
    }
    if (a.getMux()) {
        mux = new MuxObject(*(a.getMux()));
    }
}

V2RockNode::~V2RockNode()
{
    qDebug() << "V2RockNode destruct";
    if (blackholeSettings) delete blackholeSettings;;
    if (dNSSettings) delete dNSSettings;
    if (freedomSettings) delete freedomSettings;
    if (hTTPSettings) delete hTTPSettings;
    if (mTProtoSettings) delete mTProtoSettings;
    if (shadowSocksSettings) delete shadowSocksSettings;
    if (socksSettings) delete socksSettings;
    if (vMessSettings) delete vMessSettings;
    if (streamSettings) delete streamSettings;
    if (mux) delete mux;
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
    if (hTTPSettings) delete hTTPSettings;
    hTTPSettings = value;
}

OutboundMTProtoConfigurationObject *V2RockNode::getMTProtoSettings() const
{
    return mTProtoSettings;
}

void V2RockNode::setMTProtoSettings(OutboundMTProtoConfigurationObject *value)
{
    if (mTProtoSettings) delete mTProtoSettings;
    mTProtoSettings = value;
}

OutboundShadowsocksConfigurationObject *V2RockNode::getShadowSocksSettings() const
{
    return shadowSocksSettings;
}

void V2RockNode::setShadowSocksSettings(OutboundShadowsocksConfigurationObject *value)
{
    if (shadowSocksSettings) delete shadowSocksSettings;
    shadowSocksSettings = value;
}

OutboundSocksConfigurationObject *V2RockNode::getSocksSettings() const
{
    return socksSettings;
}

void V2RockNode::setSocksSettings(OutboundSocksConfigurationObject *value)
{
    if (socksSettings) delete socksSettings;
    socksSettings = value;
}

OutboundVMessConfigurationObject *V2RockNode::getVMessSettings() const
{
    return vMessSettings;
}

void V2RockNode::setVMessSettings(OutboundVMessConfigurationObject *value)
{
    if (vMessSettings) delete vMessSettings;
    vMessSettings = value;
}

StreamSettingsObject *V2RockNode::getStreamSettings() const
{
    return streamSettings;
}

void V2RockNode::setStreamSettings(StreamSettingsObject *value)
{
    if (streamSettings) delete streamSettings;
    streamSettings = value;
}

MuxObject *V2RockNode::getMux() const
{
    return mux;
}

void V2RockNode::setMux(MuxObject *value)
{
    if (mux) delete mux;
    mux = value;
}

void V2RockNode::read(const QJsonObject &json)
{
    if (json.contains("name") && json["name"].isString()) {
        name = json["name"].toString();
    }
    if (json.contains("type") && json["type"].isDouble()) {
        type = json["type"].toInt();
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
    json["type"] = type;
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

int V2RockNode::getType() const
{
    return type;
}

void V2RockNode::setType(int value)
{
    type = value;
}
