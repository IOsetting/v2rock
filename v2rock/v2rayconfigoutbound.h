#ifndef V2RAYCONFIGOUTBOUND_H
#define V2RAYCONFIGOUTBOUND_H

#include <QDebug>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QList>
#include <QMap>
#include <QString>

#include "v2raydef.h"

class V2RayConfigOutbound
{
public:
    V2RayConfigOutbound();
    ~V2RayConfigOutbound();

    void toJson(QJsonObject &json) const;

    static void fromJson(OutboundBlackholeConfigurationObject &settings, const QJsonObject &json);
    static void toJson(OutboundBlackholeConfigurationObject *settings, QJsonObject &json);

    static void fromJson(OutboundDNSConfigurationObject &settings, const QJsonObject &json);
    static void toJson(OutboundDNSConfigurationObject *settings, QJsonObject &json);

    static void fromJson(OutboundFreedomConfigurationObject &settings, const QJsonObject &json);
    static void toJson(OutboundFreedomConfigurationObject *settings, QJsonObject &json);

    static void fromJson(OutboundHTTPConfigurationObject &settings, const QJsonObject &json);
    static void toJson(OutboundHTTPConfigurationObject *settings, QJsonObject &json);

    static void fromJson(OutboundMTProtoConfigurationObject &settings, const QJsonObject &json);
    static void toJson(OutboundMTProtoConfigurationObject *settings, QJsonObject &json);

    static void fromJson(OutboundShadowsocksConfigurationObject &settings, const QJsonObject &json);
    static void toJson(OutboundShadowsocksConfigurationObject *settings, QJsonObject &json);

    static void fromJson(OutboundSocksConfigurationObject &settings, const QJsonObject &json);
    static void toJson(OutboundSocksConfigurationObject *settings, QJsonObject &json);

    static void fromJson(OutboundVMessConfigurationObject &settings, const QJsonObject &json);
    static void toJson(OutboundVMessConfigurationObject *settings, QJsonObject &json);

    static void fromJson(StreamSettingsObject &settings, const QJsonObject &json);
    static void toJson(StreamSettingsObject *settings, QJsonObject &json);

    static void fromJson(MuxObject &settings, const QJsonObject &json);
    static void toJson(MuxObject *settings, QJsonObject &json);

    static void fromJson(SockoptObject &settings, const QJsonObject &json);
    static void toJson(SockoptObject *settings, QJsonObject &json);

    static void fromJson(TransportTlsObject &settings, const QJsonObject &json);
    static void toJson(TransportTlsObject *settings, QJsonObject &json);

    static void fromJson(TransportTcpObject &settings, const QJsonObject &json);
    static void toJson(TransportTcpObject *settings, QJsonObject &json);

    static void fromJson(TransportKcpObject &settings, const QJsonObject &json);
    static void toJson(TransportKcpObject *settings, QJsonObject &json);

    static void fromJson(TransportWebSocketObject &settings, const QJsonObject &json);
    static void toJson(TransportWebSocketObject *settings, QJsonObject &json);

    static void fromJson(TransportHTTPObject &settings, const QJsonObject &json);
    static void toJson(TransportHTTPObject *settings, QJsonObject &json);

    static void fromJson(TransportDomainSocketObject &settings, const QJsonObject &json);
    static void toJson(TransportDomainSocketObject *settings, QJsonObject &json);

    static void fromJson(TransportQuicObject &settings, const QJsonObject &json);
    static void toJson(TransportQuicObject *settings, QJsonObject &json);

    static void fromJson(QMap<QString, QStringList> &settings, const QJsonObject &json);
    static void toJson(QMap<QString, QStringList> *settings, QJsonObject &json);

    static void fromJson(QMap<QString, QString> &settings, const QJsonObject &json);
    static void toJson(QMap<QString, QString> *settings, QJsonObject &json);

    static QString toText(const QJsonObject &json);

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
