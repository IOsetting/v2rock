#ifndef V2ROCKNODE_H
#define V2ROCKNODE_H

#include <QJsonObject>
#include <QString>
#include <QTextStream>

class V2RockNode
{
public:
    V2RockNode();

    QString getProtocol() const;
    void setProtocol(const QString &value);

    QString getAddress() const;
    void setAddress(const QString &value);

    int getPort() const;
    void setPort(int value);

    QString getUserId() const;
    void setUserId(const QString &value);

    int getUserAid() const;
    void setUserAid(const int value);

    QString getUserEmail() const;
    void setUserEmail(const QString &value);

    QString getUserSecurity() const;
    void setUserSecurity(const QString &value);

    QString getStreamNetwork() const;
    void setStreamNetwork(const QString &value);

    QString getStreamWsPath() const;
    void setStreamWsPath(const QString &value);

    QString getStreamWsHeaderHost() const;
    void setStreamWsHeaderHost(const QString &value);

    QString getRemark() const;
    void setRemark(const QString &value);

    QString getPs() const;
    void setPs(const QString &value);

    void read(const QJsonObject &json);
    void write(QJsonObject &json) const;
    void print(int indentation = 0) const;

private:
    QString protocol;
    QString address;
    int port;
    QString userId;
    int userAid;
    QString userEmail;
    QString userSecurity;
    QString streamNetwork;
    QString streamWsPath;
    QString streamWsHeaderHost;
    QString remark;
    QString ps;
};

#endif // V2ROCKNODE_H
