#ifndef V2ROCKCONFIG_H
#define V2ROCKCONFIG_H

#include <QDebug>
#include <QDir>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonParseError>
#include <QList>
#include <QObject>
#include <QStandardPaths>
#include <QString>

#include "v2rocknode.h"
#include "v2rayconfig.h"

class V2RockConfig : public QObject
{
    Q_OBJECT

public:
    explicit V2RockConfig(QObject *parent = nullptr);
    ~V2RockConfig();

    bool isEmpty() const;

    QString getWorkDir() const;
    void setWorkDir(const QString &value);

    QString getV2executablePath() const;
    void setV2executablePath(const QString &value);

    QString getSubscribeUrl() const;
    void setSubscribeUrl(const QString &value);

    V2RayConfigInbound *getSocksConfig() const;
    void setSocksConfig(V2RayConfigInbound *value);
    void initSocksConfig(const QString &listen, const int port);
    void deleteSocksConfig();

    V2RayConfigInbound *getHttpConfig() const;
    void setHttpConfig(V2RayConfigInbound *value);
    void initHttpConfig(const QString &listen, const int port);
    void deleteHttpConfig();

    QList<QString> getBypassIps() const;
    void setBypassIps(const QList<QString> &value);

    QList<QString> getBypassDomains() const;
    void setBypassDomains(const QList<QString> &value);

    QList<V2RockNode *> getNodes() const;
    void setNodes(const QList<V2RockNode *> &value);

    int getNodeIndex() const;
    void setNodeIndex(int value);

    void init();
    void read();
    void write();
    void print(int indentation) const;

    QString *toV2RayJson(QJsonObject &json);

signals:
    void logReceived(const QString&);

private:
    bool empty;
    QString workDir;
    QString v2executablePath;
    QString subscribeUrl;
    V2RayConfigInbound *socksConfig;
    V2RayConfigInbound *httpConfig;
    QList<QString> bypassIps;
    QList<QString> bypassDomains;
    QList<V2RockNode *> nodes;
    int nodeIndex;

    void fromJson(const QJsonObject &json);
    void toJson(QJsonObject &json) const;
};

#endif // V2ROCKCONFIG_H
