#include "v2rocknode.h"

V2RockNode::V2RockNode()
{

}

QString V2RockNode::getProtocol() const
{
    return protocol;
}

void V2RockNode::setProtocol(const QString &value)
{
    protocol = value;
}

QString V2RockNode::getAddress() const
{
    return address;
}

void V2RockNode::setAddress(const QString &value)
{
    address = value;
}

int V2RockNode::getPort() const
{
    return port;
}

void V2RockNode::setPort(int value)
{
    port = value;
}

QString V2RockNode::getUserId() const
{
    return userId;
}

void V2RockNode::setUserId(const QString &value)
{
    userId = value;
}

int V2RockNode::getUserAid() const
{
    return userAid;
}

void V2RockNode::setUserAid(const int value)
{
    userAid = value;
}

QString V2RockNode::getUserEmail() const
{
    return userEmail;
}

void V2RockNode::setUserEmail(const QString &value)
{
    userEmail = value;
}

QString V2RockNode::getUserSecurity() const
{
    return userSecurity;
}

void V2RockNode::setUserSecurity(const QString &value)
{
    userSecurity = value;
}

QString V2RockNode::getStreamNetwork() const
{
    return streamNetwork;
}

void V2RockNode::setStreamNetwork(const QString &value)
{
    streamNetwork = value;
}

QString V2RockNode::getStreamWsPath() const
{
    return streamWsPath;
}

void V2RockNode::setStreamWsPath(const QString &value)
{
    streamWsPath = value;
}

QString V2RockNode::getStreamWsHeaderHost() const
{
    return streamWsHeaderHost;
}

void V2RockNode::setStreamWsHeaderHost(const QString &value)
{
    streamWsHeaderHost = value;
}

QString V2RockNode::getRemark() const
{
    return remark;
}

void V2RockNode::setRemark(const QString &value)
{
    remark = value;
}

QString V2RockNode::getPs() const
{
    return ps;
}

void V2RockNode::setPs(const QString &value)
{
    ps = value;
}

void V2RockNode::read(const QJsonObject &json)
{
    if (json.contains("protocol") && json["protocol"].isString()) {
        protocol = json["protocol"].toString();
    }
    if (json.contains("address") && json["address"].isString()) {
        address = json["address"].toString();
    }
    if (json.contains("port")) {
        port = json["port"].toInt();
    }
    if (json.contains("userId") && json["userId"].isString()) {
        userId = json["userId"].toString();
    }
    if (json.contains("userAid")) {
        userAid = json["userAid"].toInt();
    }
    if (json.contains("userEmail") && json["userEmail"].isString()) {
        userEmail = json["userEmail"].toString();
    }
    if (json.contains("userSecurity") && json["userSecurity"].isString()) {
        userSecurity = json["userSecurity"].toString();
    }
    if (json.contains("streamNetwork") && json["streamNetwork"].isString()) {
        streamNetwork = json["streamNetwork"].toString();
    }
    if (json.contains("streamWsPath") && json["streamWsPath"].isString()) {
        streamWsPath = json["streamWsPath"].toString();
    }
    if (json.contains("streamWsHeaderHost") && json["streamWsHeaderHost"].isString()) {
        streamWsHeaderHost = json["streamWsHeaderHost"].toString();
    }
    if (json.contains("ps") && json["ps"].isString()) {
        ps = json["ps"].toString();
    }
    if (json.contains("remark") && json["remark"].isString()) {
        remark = json["remark"].toString();
    }
}

void V2RockNode::write(QJsonObject &json) const
{
    json["protocol"] = protocol;
    json["address"] = address;
    json["port"] = port;
    json["userId"] = userId;
    json["userAid"] = userAid;
    json["userEmail"] = userEmail;
    json["userSecurity"] = userSecurity;
    json["streamNetwork"] = streamNetwork;
    json["streamWsPath"] = streamWsPath;
    json["streamWsHeaderHost"] = streamWsHeaderHost;
    json["ps"] = ps;
    json["remark"] = remark;
}

void V2RockNode::print(int indentation) const
{
    const QString indent(indentation * 2, ' ');
    QTextStream(stdout) << indent << "protocol:\t" << protocol << "\n";
    QTextStream(stdout) << indent << "address:\t" << address << "\n";
    QTextStream(stdout) << indent << "port:\t" << port << "\n";
    QTextStream(stdout) << indent << "userId:\t" << userId << "\n";
    QTextStream(stdout) << indent << "userAid:\t" << userAid << "\n";
    QTextStream(stdout) << indent << "userEmail:\t" << userEmail << "\n";
    QTextStream(stdout) << indent << "userSecurity:\t" << userSecurity << "\n";
    QTextStream(stdout) << indent << "streamNetwork:\t" << streamNetwork << "\n";
    QTextStream(stdout) << indent << "streamWsPath:\t" << streamWsPath << "\n";
    QTextStream(stdout) << indent << "streamWsHeaderHost:\t" << streamWsHeaderHost << "\n";
    QTextStream(stdout) << indent << "ps:\t" << ps << "\n";
    QTextStream(stdout) << indent << "remark:\t" << remark << "\n";
}

