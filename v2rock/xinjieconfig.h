#ifndef XINJIECONFIG_H
#define XINJIECONFIG_H

#include <QJsonObject>
#include <QString>
#include <QTextStream>

#include "v2rocknode.h"

class XinjieConfig
{
public:
    XinjieConfig();

    QString getHost() const;
    void setHost(const QString &value);

    QString getPath() const;
    void setPath(const QString &value);

    QString getTls() const;
    void setTls(const QString &value);

    bool getVerifyCert() const;
    void setVerifyCert(bool value);

    QString getAddress() const;
    void setAddress(const QString &value);

    int getPort() const;
    void setPort(int value);

    int getAid() const;
    void setAid(int value);

    QString getNet() const;
    void setNet(const QString &value);

    QString getHeaderType() const;
    void setHeaderType(const QString &value);

    QString getV() const;
    void setV(const QString &value);

    QString getType() const;
    void setType(const QString &value);

    QString getPs() const;
    void setPs(const QString &value);

    QString getRemark() const;
    void setRemark(const QString &value);

    QString getId() const;
    void setId(const QString &value);

    int getClazz() const;
    void setClazz(int value);

    void read(const QJsonObject &json);
    void write(V2RockNode &node) const;
    void print(int indentation = 0) const;

private:
    QString host;
    QString path;
    QString tls;
    bool verifyCert;
    QString address;
    int port;
    int aid;
    QString net;
    QString headerType;
    QString v;
    QString type;
    QString ps;
    QString remark;
    QString id;
    int clazz;

};

#endif // XINJIECONFIG_H
