#ifndef V2RAYCONFIGOUTBOUND_H
#define V2RAYCONFIGOUTBOUND_H

#include <QJsonArray>
#include <QJsonObject>
#include <QList>
#include <QMap>
#include <QString>

#include "v2raydef.h"

class V2RayConfigOutbound
{
public:
    V2RayConfigOutbound();
    void toJson(QJsonObject &json) const;

    QString getTag() const;
    void setTag(const QString &value);

    QString getProtocol() const;
    void setProtocol(const QString &value);

    OutboundBlackholeConfigurationObject *getBlackholeSettings() const;
    void setBlackholeSettings(OutboundBlackholeConfigurationObject *value);

    OutboundDNSConfigurationObject *getDNSSettings() const;
    void setDNSSettings(OutboundDNSConfigurationObject *value);

    OutboundFreedomConfigurationObject *getFreedomSettings() const;
    void setFreedomSettings(OutboundFreedomConfigurationObject *value);

    OutboundHTTPConfigurationObject *getHTTPSettings() const;
    void setHTTPSettings(OutboundHTTPConfigurationObject *value);

    OutboundMTProtoConfigurationObject *getTProtoSettings() const;
    void setTProtoSettings(OutboundMTProtoConfigurationObject *tProtoSettings);

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

private:
    QString tag;
    QString protocol;
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

#endif // V2RAYCONFIGOUTBOUND_H
