#ifndef V2RAYCONFIGINBOUND_H
#define V2RAYCONFIGINBOUND_H

#include <QDebug>
#include <QJsonArray>
#include <QJsonObject>
#include <QList>
#include <QMap>
#include <QString>

#include "v2raydef.h"

class V2RayConfigInbound
{
public:
    V2RayConfigInbound();
    void toJson(QJsonObject &json) const;

    QString getTag() const;
    void setTag(const QString &value);

    int getPort() const;
    void setPort(int value);

    QString getListen() const;
    void setListen(const QString &value);

    QString getProtocol() const;
    void setProtocol(const QString &value);

    SniffingObject *getSniffing() const;
    void setSniffing(SniffingObject *value);

    InboundDokodemoDoorConfigurationObject *getDokodemoDoorSettings() const;
    void setDokodemoDoorSettings(InboundDokodemoDoorConfigurationObject *value);

    InboundHTTPConfigurationObject *getHttpSettings() const;
    void setHttpSettings(InboundHTTPConfigurationObject *value);

    InboundMTProtoConfigurationObject *getTProtoSettings() const;
    void setTProtoSettings(InboundMTProtoConfigurationObject *tProtoSettings);

    InboundShadowsocksConfigurationObject *getShadowsocksSettings() const;
    void setShadowsocksSettings(InboundShadowsocksConfigurationObject *value);

    InboundSocksConfigurationObject *getSocksSettings() const;
    void setSocksSettings(InboundSocksConfigurationObject *value);

    InboundVMessConfigurationObject *getVMessSettings() const;
    void setVMessSettings(InboundVMessConfigurationObject *value);

private:
    QString tag;
    int port;
    QString listen;
    QString protocol;
    SniffingObject *sniffing;
    InboundDokodemoDoorConfigurationObject *dokodemoDoorSettings;
    InboundHTTPConfigurationObject *httpSettings;
    InboundMTProtoConfigurationObject *mTProtoSettings;
    InboundShadowsocksConfigurationObject *shadowsocksSettings;
    InboundSocksConfigurationObject *socksSettings;
    InboundVMessConfigurationObject *vMessSettings;
};

#endif // V2RAYCONFIGINBOUND_H
