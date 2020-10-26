#ifndef V2ROCKNODE_H
#define V2ROCKNODE_H

#include <QDebug>
#include <QJsonObject>
#include <QString>
#include <QTextStream>

#include "v2rayconfigoutbound.h"

class V2RockNode
{
public:
    V2RockNode();
    V2RockNode(const V2RockNode& a);
    ~V2RockNode();

    QString getName() const;
    void setName(const QString &value);

    QString getProtocol() const;
    void setProtocol(const QString &value);

    int getType() const;
    void setType(int value);

    OutboundBlackholeConfigurationObject *getBlackholeSettings() const;
    void setBlackholeSettings(OutboundBlackholeConfigurationObject *value);

    OutboundDNSConfigurationObject *getDNSSettings() const;
    void setDNSSettings(OutboundDNSConfigurationObject *value);

    OutboundFreedomConfigurationObject *getFreedomSettings() const;
    void setFreedomSettings(OutboundFreedomConfigurationObject *value);

    OutboundHTTPConfigurationObject *getHTTPSettings() const;
    void setHTTPSettings(OutboundHTTPConfigurationObject *value);

    OutboundMTProtoConfigurationObject *getMTProtoSettings() const;
    void setMTProtoSettings(OutboundMTProtoConfigurationObject *value);

    OutboundShadowsocksConfigurationObject *getShadowSocksSettings() const;
    void setShadowSocksSettings(OutboundShadowsocksConfigurationObject *value);

    OutboundSocksConfigurationObject *getSocksSettings() const;
    void setSocksSettings(OutboundSocksConfigurationObject *value);

    OutboundVMessConfigurationObject *getVMessSettings() const;
    void setVMessSettings(OutboundVMessConfigurationObject *value);

    StreamSettingsObject *getStreamSettings() const;
    void setStreamSettings(StreamSettingsObject *value);

    MuxObject *getMux() const;
    void setMux(MuxObject *value);

    void read(const QJsonObject &json);
    void write(QJsonObject &json) const;
    void print(int indentation = 0) const;

private:
    QString name;
    QString protocol;
    int type;
    OutboundBlackholeConfigurationObject *blackholeSettings;
    OutboundDNSConfigurationObject *dNSSettings;
    OutboundFreedomConfigurationObject *freedomSettings;
    OutboundHTTPConfigurationObject *hTTPSettings;
    OutboundMTProtoConfigurationObject *mTProtoSettings;
    OutboundShadowsocksConfigurationObject *shadowSocksSettings;
    OutboundSocksConfigurationObject *socksSettings;
    OutboundVMessConfigurationObject *vMessSettings;
    StreamSettingsObject *streamSettings;
    MuxObject *mux;
};

#endif // V2ROCKNODE_H
