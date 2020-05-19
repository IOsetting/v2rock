#include "v2rayconfigoutbound.h"

V2RayConfigOutbound::V2RayConfigOutbound() :
    blackholeSettings(0), dNSSettings(0), freedomSettings(0), hTTPSettings(0), mTProtoSettings(0),
    shadowSocksSettings(0), vMessSettings(0), streamSettings(0), mux(0)
{

}

QString V2RayConfigOutbound::getTag() const
{
    return tag;
}

void V2RayConfigOutbound::setTag(const QString &value)
{
    tag = value;
}

QString V2RayConfigOutbound::getProtocol() const
{
    return protocol;
}

void V2RayConfigOutbound::setProtocol(const QString &value)
{
    protocol = value;
}

OutboundBlackholeConfigurationObject *V2RayConfigOutbound::getBlackholeSettings() const
{
    return blackholeSettings;
}

void V2RayConfigOutbound::setBlackholeSettings(OutboundBlackholeConfigurationObject *value)
{
    blackholeSettings = value;
}

OutboundDNSConfigurationObject *V2RayConfigOutbound::getDNSSettings() const
{
    return dNSSettings;
}

void V2RayConfigOutbound::setDNSSettings(OutboundDNSConfigurationObject *value)
{
    dNSSettings = value;
}

OutboundFreedomConfigurationObject *V2RayConfigOutbound::getFreedomSettings() const
{
    return freedomSettings;
}

void V2RayConfigOutbound::setFreedomSettings(OutboundFreedomConfigurationObject *value)
{
    freedomSettings = value;
}

OutboundHTTPConfigurationObject *V2RayConfigOutbound::getHTTPSettings() const
{
    return hTTPSettings;
}

void V2RayConfigOutbound::setHTTPSettings(OutboundHTTPConfigurationObject *value)
{
    hTTPSettings = value;
}

OutboundMTProtoConfigurationObject *V2RayConfigOutbound::getTProtoSettings() const
{
    return mTProtoSettings;
}

void V2RayConfigOutbound::setTProtoSettings(OutboundMTProtoConfigurationObject *tProtoSettings)
{
    mTProtoSettings = tProtoSettings;
}

OutboundShadowsocksConfigurationObject *V2RayConfigOutbound::getShadowSocksSettings() const
{
    return shadowSocksSettings;
}

void V2RayConfigOutbound::setShadowSocksSettings(OutboundShadowsocksConfigurationObject *value)
{
    shadowSocksSettings = value;
}

OutboundSocksConfigurationObject *V2RayConfigOutbound::getSocksSettings() const
{
    return socksSettings;
}

void V2RayConfigOutbound::setSocksSettings(OutboundSocksConfigurationObject *value)
{
    socksSettings = value;
}

OutboundVMessConfigurationObject *V2RayConfigOutbound::getVMessSettings() const
{
    return vMessSettings;
}

void V2RayConfigOutbound::setVMessSettings(OutboundVMessConfigurationObject *value)
{
    vMessSettings = value;
}

StreamSettingsObject *V2RayConfigOutbound::getStreamSettings() const
{
    return streamSettings;
}

void V2RayConfigOutbound::setStreamSettings(StreamSettingsObject *value)
{
    streamSettings = value;
}

MuxObject *V2RayConfigOutbound::getMux() const
{
    return mux;
}

void V2RayConfigOutbound::setMux(MuxObject *value)
{
    mux = value;
}

void V2RayConfigOutbound::toJson(QJsonObject &json) const
{
    json["tag"] = tag;
    json["protocol"] = protocol;
    json["settings"] = QJsonValue(QJsonValue::Null);

    if (protocol == "blackhole" && blackholeSettings) {
        QJsonObject settingsObj;
        //struct ResponseObject response
        QJsonObject responseObj;
        responseObj["type"] = blackholeSettings->response.type;
        settingsObj["response"] = responseObj;
        json["settings"] = settingsObj;
    }

    if (protocol == "dns" && dNSSettings) {
        QJsonObject settingsObj;
        settingsObj["address"] = dNSSettings->address;
        settingsObj["network"] = dNSSettings->network;
        settingsObj["port"] = dNSSettings->port;
        json["settings"] = settingsObj;
    }

    if (protocol == "freedom" && freedomSettings) {
        QJsonObject settingsObj;
        settingsObj["domainStrategy"] = freedomSettings->domainStrategy;
        if (freedomSettings->redirect) {
            settingsObj["redirect"] = *(freedomSettings->redirect);
        }
        settingsObj["userLevel"] = freedomSettings->userLevel;
        json["settings"] = settingsObj;
    }

    if (protocol == "http" && hTTPSettings) {
        QJsonObject settingsObj;
        //QList<HTTPServerObject> servers;
        QJsonArray serversArray;
        foreach(const HTTPServerObject server, hTTPSettings->servers) {
            QJsonObject serverObj;
            serverObj["address"] = server.address;
            serverObj["port"] = server.port;
            if (server.users) {
                QJsonArray usersArray;
                foreach (const AccountObject user, *(server.users)) {
                    QJsonObject userObj;
                    userObj["user"] = user.user;
                    userObj["pass"] = user.pass;
                    usersArray.append(userObj);
                }
                serverObj["users"] = usersArray;
            }
            serversArray.append(serverObj);
        }
        settingsObj["servers"] = serversArray;

        json["settings"] = settingsObj;
    }

    if (protocol == "mtproto" && mTProtoSettings) {
        QJsonObject settingsObj;
        // Empty
        json["settings"] = settingsObj;
    }

    if (protocol == "shadowsocks" && shadowSocksSettings) {
        QJsonObject settingsObj;
        QJsonArray serversArray;
        foreach(const ShadowsocksServerObject server, shadowSocksSettings->servers) {
            QJsonObject serverObj;
            serverObj["email"] = server.email;
            serverObj["address"] = server.address;
            serverObj["port"] = server.port;
            serverObj["method"] = server.method;
            serverObj["password"] = server.password;
            serverObj["ota"] = server.ota;
            serverObj["level"] = server.level;
            serversArray.append(serverObj);
        }
        settingsObj["servers"] = serversArray;
        json["settings"] = settingsObj;
    }

    if (protocol == "socks" && socksSettings) {
        QJsonObject settingsObj;
        QJsonArray serversArray;
        foreach(const SocksServerObject server, socksSettings->servers) {
            QJsonObject serverObj;
            serverObj["address"] = server.address;
            serverObj["port"] = server.port;
            if (server.users) {
                QJsonArray usersArray;
                foreach(const AccountUserObject user, *(server.users)) {
                    QJsonObject userObj;
                    userObj["user"] = user.user;
                    userObj["pass"] = user.pass;
                    userObj["level"] = user.level;
                    usersArray.append(userObj);
                }
                serverObj["users"] = usersArray;
            }
            serversArray.append(serverObj);
        }
        settingsObj["servers"] = serversArray;
        json["settings"] = settingsObj;
    }

    if (protocol == "vmess" && vMessSettings) {
        QJsonObject settingsObj;
        QJsonArray vnextArray;
        foreach (const VMessServerObject vnext, vMessSettings->vnext) {
            QJsonObject vnextObj;
            vnextObj["address"] = vnext.address;
            vnextObj["port"] = vnext.port;
            if (vnext.users) {
                QJsonArray usersArray;
                foreach (const UserObject user, *(vnext.users)) {
                    QJsonObject userObj;
                    userObj["id"] = user.id;
                    userObj["alterId"] = user.alterId;
                    userObj["level"] = user.level;
                    userObj["security"] = user.security;
                    usersArray.append(userObj);
                }
                vnextObj["users"] = usersArray;
            }
            vnextArray.append(vnextObj);
        }
        settingsObj["vnext"] = vnextArray;
        json["settings"] = settingsObj;
    }

    if (streamSettings) {
        QJsonObject streamSettingsObj;
        streamSettingsObj["network"] = streamSettings->network;
        streamSettingsObj["security"] = streamSettings->security;

        if (streamSettings->sockopt) {
            QJsonObject sockoptObj;
            sockoptObj["mark"] = streamSettings->sockopt->mark;
            sockoptObj["tcpFastOpen"] = streamSettings->sockopt->tcpFastOpen;
            sockoptObj["tproxy"] = streamSettings->sockopt->tproxy;
            streamSettingsObj["sockopt"] = sockoptObj;
        }

        if (streamSettings->tlsSettings) {
            QJsonObject settingsObj;
            settingsObj["serverName"] = streamSettings->tlsSettings->serverName;
            settingsObj["allowInsecure"] = streamSettings->tlsSettings->allowInsecure;
            settingsObj["disableSystemRoot"] = streamSettings->tlsSettings->disableSystemRoot;
            QJsonArray alpnArray;
            foreach(const QString val, streamSettings->tlsSettings->alpn) {
                alpnArray.append(val);
            }
            settingsObj["alpn"] = alpnArray;

            QJsonArray certArray;
            foreach(const CertificateObject cert, streamSettings->tlsSettings->certificates) {
                QJsonObject certObj;
                certObj["usage"] = cert.usage;
                certObj["certificateFile"] = cert.certificateFile;
                certObj["keyFile"] = cert.keyFile;
                QJsonArray cerArray;
                foreach(const QString val, cert.certificate) {
                    cerArray.append(val);
                }
                certObj["certificate"] = cerArray;

                QJsonArray keyArray;
                foreach(const QString val, cert.key) {
                    keyArray.append(val);
                }
                certObj["key"] = keyArray;
                certArray.append(certObj);
            }
            settingsObj["certificates"] = certArray;

            streamSettingsObj["tlsSettings"] = settingsObj;
        } else {
            streamSettingsObj["tlsSettings"] = QJsonValue(QJsonValue::Null);
        }

        if (streamSettings->tcpSettings) {
            QJsonObject settingsObj;
            QJsonObject headerObj;
            HTTPHeaderObject header = streamSettings->tcpSettings->header;
            headerObj["type"] = header.type;

            // header request
            QJsonObject requestObj;
            HTTPRequestObject request = header.request;
            requestObj["version"] = request.version;
            requestObj["method"] = request.method;
            QJsonArray pathArray;
            foreach(const QString val, request.path) {
                pathArray.append(val);
            }
            requestObj["path"] = pathArray;
            QJsonObject reqHeaderObj;
            QMapIterator<QString, QStringList> it(request.headers);
            while (it.hasNext()) {
                it.next();
                QJsonArray reqHeaderValArray;
                foreach(const QString val, it.value()) {
                    reqHeaderValArray.append(val);
                }
                reqHeaderObj[it.key()] = reqHeaderValArray;

            }
            requestObj["headers"] = reqHeaderObj;
            headerObj["request"] = requestObj;

            // header response
            QJsonObject responseObj;
            HTTPResponseObject response = header.response;
            responseObj["version"] = response.version;
            responseObj["status"] = response.status;
            responseObj["reason"] = response.reason;
            QJsonObject resHeaderObj;
            QMapIterator<QString, QStringList> it2(response.headers);
            while (it2.hasNext()) {
                it2.next();
                QJsonArray resHeaderValArray;
                foreach(const QString val, it2.value()) {
                    resHeaderValArray.append(val);
                }
                resHeaderObj[it2.key()] = resHeaderValArray;

            }
            responseObj["headers"] = resHeaderObj;
            headerObj["response"] = responseObj;

            settingsObj["header"] = headerObj;
            streamSettingsObj["tcpSettings"] = settingsObj;
        } else {
            streamSettingsObj["tcpSettings"] = QJsonValue(QJsonValue::Null);
        }

        if (streamSettings->kcpSettings) {
            QJsonObject settingsObj;
            settingsObj["mtu"] = streamSettings->kcpSettings->mtu;
            settingsObj["tti"] = streamSettings->kcpSettings->tti;
            settingsObj["uplinkCapacity"] = streamSettings->kcpSettings->uplinkCapacity;
            settingsObj["downlinkCapacity"] = streamSettings->kcpSettings->downlinkCapacity;
            settingsObj["congestion"] = streamSettings->kcpSettings->congestion;
            settingsObj["readBufferSize"] = streamSettings->kcpSettings->readBufferSize;
            settingsObj["writeBufferSize"] = streamSettings->kcpSettings->writeBufferSize;
            QJsonObject headerObj;
            headerObj["type"] = streamSettings->kcpSettings->header.type;
            settingsObj["header"] = headerObj;
            streamSettingsObj["kcpSettings"] = settingsObj;
        } else {
            streamSettingsObj["kcpSettings"] = QJsonValue(QJsonValue::Null);
        }

        if (streamSettings->wsSettings) {
            QJsonObject settingsObj;
            settingsObj["path"] = streamSettings->wsSettings->path;
            QJsonObject headersObj;
            QMapIterator<QString, QString> it(streamSettings->wsSettings->headers);
            while (it.hasNext()) {
                it.next();
                headersObj[it.key()] = it.value();
            }
            settingsObj["headers"] = headersObj;
            streamSettingsObj["wsSettings"] = settingsObj;
        } else {
            streamSettingsObj["wsSettings"] = QJsonValue(QJsonValue::Null);
        }

        if (streamSettings->httpSettings) {
            QJsonObject settingsObj;
            settingsObj["path"] = streamSettings->httpSettings->path;
            QJsonArray hostArray;
            foreach (const QString path, streamSettings->httpSettings->host) {
                hostArray.append(path);
            }
            settingsObj["host"] = hostArray;
            streamSettingsObj["httpSettings"] = settingsObj;
        } else {
            streamSettingsObj["httpSettings"] = QJsonValue(QJsonValue::Null);
        }

        if (streamSettings->dsSettings) {
            QJsonObject settingsObj;
            settingsObj["path"] = streamSettings->dsSettings->path;
            streamSettingsObj["dsSettings"] = settingsObj;
        } else {
            streamSettingsObj["dsSettings"] = QJsonValue(QJsonValue::Null);
        }

        if (streamSettings->quicSettings) {
            QJsonObject settingsObj;
            settingsObj["security"] = streamSettings->quicSettings->security;
            settingsObj["key"] = streamSettings->quicSettings->key;
            QJsonObject headerObj;
            headerObj["type"] = streamSettings->quicSettings->header.type;
            settingsObj["header"] = headerObj;
            streamSettingsObj["quicSettings"] = settingsObj;
        } else {
            streamSettingsObj["quicSettings"] = QJsonValue(QJsonValue::Null);
        }
        json["streamSettings"] = streamSettingsObj;

    } else {
        json["streamSettings"] = QJsonValue(QJsonValue::Null);
    }

    if (mux) {
        QJsonObject muxObj;
        muxObj["enabled"] = mux->enabled;
        muxObj["concurrency"] = mux->concurrency;
        json["mux"] = muxObj;
    } else {
        json["mux"] = QJsonValue(QJsonValue::Null);
    }
}
