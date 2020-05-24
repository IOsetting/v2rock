#include "xinjieconfig.h"

XinjieConfig::XinjieConfig()
{

}

QString XinjieConfig::getHost() const
{
    return host;
}

void XinjieConfig::setHost(const QString &value)
{
    host = value;
}

QString XinjieConfig::getPath() const
{
    return path;
}

void XinjieConfig::setPath(const QString &value)
{
    path = value;
}

QString XinjieConfig::getTls() const
{
    return tls;
}

void XinjieConfig::setTls(const QString &value)
{
    tls = value;
}

bool XinjieConfig::getVerifyCert() const
{
    return verifyCert;
}

void XinjieConfig::setVerifyCert(bool value)
{
    verifyCert = value;
}

QString XinjieConfig::getAddress() const
{
    return address;
}

void XinjieConfig::setAddress(const QString &value)
{
    address = value;
}

int XinjieConfig::getPort() const
{
    return port;
}

void XinjieConfig::setPort(int value)
{
    port = value;
}

int XinjieConfig::getAid() const
{
    return aid;
}

void XinjieConfig::setAid(int value)
{
    aid = value;
}

QString XinjieConfig::getNet() const
{
    return net;
}

void XinjieConfig::setNet(const QString &value)
{
    net = value;
}

QString XinjieConfig::getHeaderType() const
{
    return headerType;
}

void XinjieConfig::setHeaderType(const QString &value)
{
    headerType = value;
}

QString XinjieConfig::getV() const
{
    return v;
}

void XinjieConfig::setV(const QString &value)
{
    v = value;
}

QString XinjieConfig::getType() const
{
    return type;
}

void XinjieConfig::setType(const QString &value)
{
    type = value;
}

QString XinjieConfig::getPs() const
{
    return ps;
}

void XinjieConfig::setPs(const QString &value)
{
    ps = value;
}

QString XinjieConfig::getRemark() const
{
    return remark;
}

void XinjieConfig::setRemark(const QString &value)
{
    remark = value;
}

QString XinjieConfig::getId() const
{
    return id;
}

void XinjieConfig::setId(const QString &value)
{
    id = value;
}

int XinjieConfig::getClazz() const
{
    return clazz;
}

void XinjieConfig::setClazz(int value)
{
    clazz = value;
}

void XinjieConfig::read(const QJsonObject &json)
{
    if (json.contains("host") && json["host"].isString()) {
        host = json["host"].toString();
    }
    if (json.contains("path") && json["path"].isString()) {
        path = json["path"].toString();
    }
    if (json.contains("tls") && json["tls"].isString()) {
        tls = json["tls"].toString();
    }
    if (json.contains("verify_cert") && json["verify_cert"].isBool()) {
        verifyCert = json["verify_cert"].toBool();
    }
    if (json.contains("add") && json["add"].isString()) {
        address = json["add"].toString();
    }
    if (json.contains("port")) {
        port = json["port"].toInt();
    }
    if (json.contains("aid")) {
        aid = json["aid"].toInt();
    }
    if (json.contains("net") && json["net"].isString()) {
        net = json["net"].toString();
    }
    if (json.contains("headerType") && json["headerType"].isString()) {
        headerType = json["headerType"].toString();
    }
    if (json.contains("v") && json["v"].isString()) {
        v = json["v"].toString();
    }
    if (json.contains("type") && json["type"].isString()) {
        type = json["type"].toString();
    }
    if (json.contains("ps") && json["ps"].isString()) {
        ps = json["ps"].toString();
    }
    if (json.contains("remark") && json["remark"].isString()) {
        remark = json["remark"].toString();
    }
    if (json.contains("id") && json["id"].isString()) {
        id = json["id"].toString();
    }
    if (json.contains("class")) {
        clazz = json["class"].toInt();
    }
}

void XinjieConfig::write(V2RockNode &node) const
{
    node.setProtocol("vmess");
    node.setName(remark);

    OutboundVMessConfigurationObject *vMessConfig = new OutboundVMessConfigurationObject();
    VMessServerObject *vMessServerObject = new VMessServerObject;
    vMessServerObject->address = address;
    vMessServerObject->port = port;
    UserObject *userObject = new UserObject;
    userObject->alterId = aid;
    userObject->id = id;
    userObject->level = 0;
    userObject->security = "auto";
    vMessServerObject->users.append(userObject);
    vMessConfig->vnext.append(vMessServerObject);
    node.setVMessSettings(vMessConfig);

    StreamSettingsObject *streamSettingsObject = new StreamSettingsObject();
    streamSettingsObject->network = "ws";
    streamSettingsObject->security = "none";
    streamSettingsObject->dsSettings = 0;
    streamSettingsObject->httpSettings = 0;
    streamSettingsObject->kcpSettings = 0;
    streamSettingsObject->quicSettings = 0;
    streamSettingsObject->tcpSettings = 0;
    streamSettingsObject->tlsSettings = 0;
    streamSettingsObject->wsSettings = new TransportWebSocketObject();
    streamSettingsObject->wsSettings->path = path;
    streamSettingsObject->wsSettings->headers.insert("Host", host);
    node.setStreamSettings(streamSettingsObject);

    MuxObject *mux = new MuxObject();
    mux->enabled = true;
    mux->concurrency = 8;
    node.setMux(mux);
}

void XinjieConfig::print(int indentation) const
{
    const QString indent(indentation * 2, ' ');
    QTextStream(stdout) << indent << "address:\t" << address << "\n";
}
