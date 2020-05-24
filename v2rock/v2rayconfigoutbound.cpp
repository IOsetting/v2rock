#include "v2rayconfigoutbound.h"

V2RayConfigOutbound::V2RayConfigOutbound() :
    blackholeSettings(0), dNSSettings(0), freedomSettings(0), hTTPSettings(0), mTProtoSettings(0),
    shadowSocksSettings(0), socksSettings(0), vMessSettings(0), streamSettings(0), mux(0)
{

}

V2RayConfigOutbound::~V2RayConfigOutbound()
{
    qDebug() << "V2RayConfigOutbound destruct";
    delete blackholeSettings;
    delete dNSSettings;
    delete freedomSettings;
    delete hTTPSettings;
    delete mTProtoSettings;
    delete shadowSocksSettings;
    delete socksSettings;
    delete vMessSettings;
    delete streamSettings;
    delete mux;
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
    delete blackholeSettings;
    if (value) {
        blackholeSettings = new OutboundBlackholeConfigurationObject(*value);
    } else {
        blackholeSettings = 0;
    }
}

OutboundDNSConfigurationObject *V2RayConfigOutbound::getDNSSettings() const
{
    return dNSSettings;
}

void V2RayConfigOutbound::setDNSSettings(OutboundDNSConfigurationObject *value)
{
    delete dNSSettings;
    if (value) {
        dNSSettings = new OutboundDNSConfigurationObject(*value);
    } else {
        dNSSettings = 0;
    }
}

OutboundFreedomConfigurationObject *V2RayConfigOutbound::getFreedomSettings() const
{
    return freedomSettings;
}

void V2RayConfigOutbound::setFreedomSettings(OutboundFreedomConfigurationObject *value)
{
    delete freedomSettings;
    if (value) {
        freedomSettings = new OutboundFreedomConfigurationObject(*value);
    } else {
        freedomSettings = 0;
    }
}

OutboundHTTPConfigurationObject *V2RayConfigOutbound::getHTTPSettings() const
{
    return hTTPSettings;
}

void V2RayConfigOutbound::setHTTPSettings(OutboundHTTPConfigurationObject *value)
{
    delete hTTPSettings;
    if (value) {
        hTTPSettings = new OutboundHTTPConfigurationObject(*value);
    } else {
        hTTPSettings = 0;
    }
}

OutboundMTProtoConfigurationObject *V2RayConfigOutbound::getMTProtoSettings() const
{
    return mTProtoSettings;
}

void V2RayConfigOutbound::setMTProtoSettings(OutboundMTProtoConfigurationObject *value)
{
    delete mTProtoSettings;
    if (value) {
        mTProtoSettings = new OutboundMTProtoConfigurationObject(*value);
    } else {
        mTProtoSettings = 0;
    }
}

OutboundShadowsocksConfigurationObject *V2RayConfigOutbound::getShadowSocksSettings() const
{
    return shadowSocksSettings;
}

void V2RayConfigOutbound::setShadowSocksSettings(OutboundShadowsocksConfigurationObject *value)
{
    delete shadowSocksSettings;
    if (value) {
        shadowSocksSettings = new OutboundShadowsocksConfigurationObject(*value);
    } else {
        shadowSocksSettings = 0;
    }
}

OutboundSocksConfigurationObject *V2RayConfigOutbound::getSocksSettings() const
{
    return socksSettings;
}

void V2RayConfigOutbound::setSocksSettings(OutboundSocksConfigurationObject *value)
{
    delete socksSettings;
    if (value) {
        socksSettings = new OutboundSocksConfigurationObject(*value);
    } else {
        socksSettings = 0;
    }
}

OutboundVMessConfigurationObject *V2RayConfigOutbound::getVMessSettings() const
{
    return vMessSettings;
}

void V2RayConfigOutbound::setVMessSettings(OutboundVMessConfigurationObject *value)
{
    delete vMessSettings;
    if (value) {
        vMessSettings = new OutboundVMessConfigurationObject(*value);
    } else {
        vMessSettings = 0;
    }
}

StreamSettingsObject *V2RayConfigOutbound::getStreamSettings() const
{
    return streamSettings;
}

void V2RayConfigOutbound::setStreamSettings(StreamSettingsObject *value)
{
    delete streamSettings;
    if (value) {
        streamSettings = new StreamSettingsObject(*value);
    } else {
        streamSettings = 0;
    }
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
        toJson(blackholeSettings, settingsObj);
        json["settings"] = settingsObj;
    }

    if (protocol == "dns" && dNSSettings) {
        QJsonObject settingsObj;
        toJson(dNSSettings, settingsObj);
        json["settings"] = settingsObj;
    }

    if (protocol == "freedom" && freedomSettings) {
        QJsonObject settingsObj;
        toJson(freedomSettings, settingsObj);
        json["settings"] = settingsObj;
    }

    if (protocol == "http" && hTTPSettings) {
        QJsonObject settingsObj;
        toJson(hTTPSettings, settingsObj);
        json["settings"] = settingsObj;
    }

    if (protocol == "mtproto" && mTProtoSettings) {
        QJsonObject settingsObj;
        toJson(mTProtoSettings, settingsObj);
        json["settings"] = settingsObj;
    }

    if (protocol == "shadowsocks" && shadowSocksSettings) {
        QJsonObject settingsObj;
        toJson(shadowSocksSettings, settingsObj);
        json["settings"] = settingsObj;
    }

    if (protocol == "socks" && socksSettings) {
        QJsonObject settingsObj;
        toJson(socksSettings, settingsObj);
        json["settings"] = settingsObj;
    }

    if (protocol == "vmess" && vMessSettings) {
        QJsonObject settingsObj;
        toJson(vMessSettings, settingsObj);
        json["settings"] = settingsObj;
    }

    if (streamSettings) {
        QJsonObject streamSettingsObj;
        toJson(streamSettings, streamSettingsObj);
        json["streamSettings"] = streamSettingsObj;

    } else {
        json["streamSettings"] = QJsonValue(QJsonValue::Null);
    }

    if (mux) {
        QJsonObject muxObj;
        toJson(mux, muxObj);
        json["mux"] = muxObj;
    } else {
        json["mux"] = QJsonValue(QJsonValue::Null);
    }
}

void V2RayConfigOutbound::fromJson(OutboundBlackholeConfigurationObject &settings, const QJsonObject &json)
{
    if (json.contains("response") && json["response"].isObject()) {
        QJsonObject responseObj = json["response"].toObject();
        if (responseObj.contains("type") && responseObj["type"].isString()) {
            settings.response.type = responseObj["type"].toString();
        } else {
            settings.response.type = "none";
        }
    } else {
        // Set it to default value, if the beneath json doesn't exist
        settings.response.type = "none";
    }
}

void V2RayConfigOutbound::toJson(OutboundBlackholeConfigurationObject *settings, QJsonObject &json)
{
    QJsonObject responseObj;
    responseObj["type"] = settings->response.type;
    json["response"] = responseObj;
}

void V2RayConfigOutbound::fromJson(OutboundDNSConfigurationObject &settings, const QJsonObject &json)
{
    if (json.contains("network") && json["network"].isString()) {
        settings.network = json["network"].toString();
    } else {
        settings.network = "tcp";
    }
    if (json.contains("address") && json["address"].isString()) {
        settings.address = json["address"].toString();
    } else {
        settings.address = "";
    }
    if (json.contains("port") && json["port"].isDouble()) {
        settings.port = json["port"].toInt();
    } else {
        settings.port = 0;
    }
}

void V2RayConfigOutbound::toJson(OutboundDNSConfigurationObject *settings, QJsonObject &json)
{
    json["network"] = settings->network;
    if (!settings->address.isEmpty()) {
        json["address"] = settings->address;
    }
    if (settings->port > 0) {
        json["port"] = settings->port;
    }
}

void V2RayConfigOutbound::fromJson(OutboundFreedomConfigurationObject &settings, const QJsonObject &json)
{
    if (json.contains("domainStrategy") && json["domainStrategy"].isString()) {
        settings.domainStrategy = json["domainStrategy"].toString();
    } else {
        settings.domainStrategy = "AsIs";
    }
    if (json.contains("redirect") && json["redirect"].isString()) {
        settings.redirect = json["redirect"].isString();
    } else {
        settings.redirect = "";
    }
    if (json.contains("userLevel") && json["userLevel"].isDouble()) {
        settings.userLevel = json["userLevel"].toInt();
    } else {
        settings.userLevel = 0;
    }
}

void V2RayConfigOutbound::toJson(OutboundFreedomConfigurationObject *settings, QJsonObject &json)
{
    json["domainStrategy"] = settings->domainStrategy;
    if (!settings->redirect.isEmpty()) {
        json["redirect"] = settings->redirect;
    }
    json["userLevel"] = settings->userLevel;
}

void V2RayConfigOutbound::fromJson(OutboundHTTPConfigurationObject &settings, const QJsonObject &json)
{
    if (json.contains("servers") && json["servers"].isArray()) {
        foreach(QJsonValue serverValue, json["servers"].toArray()) {
            if (serverValue.isObject()) {
                QJsonObject serverObj = serverValue.toObject();
                HTTPServerObject *server = new HTTPServerObject;
                if (serverObj.contains("address") && serverObj["address"].isString()) {
                    server->address = serverObj["address"].toString();
                }
                if (serverObj.contains("port") && serverObj["port"].isDouble()) {
                    server->port = serverObj["port"].toInt();
                }
                if (serverObj.contains("users") && serverObj["users"].isArray()) {
                    foreach(QJsonValue userValue, serverObj["users"].toArray()) {
                        if (userValue.isObject()) {
                            QJsonObject userObj = userValue.toObject();
                            AccountObject *user = new AccountObject;
                            if (userObj.contains("user") && userObj["user"].isString()) {
                                user->user = userObj["user"].toString();
                            }
                            if (userObj.contains("pass") && userObj["pass"].isString()) {
                                user->pass = userObj["pass"].toString();
                            }
                            server->users.append(user);
                        }
                    }
                }
                settings.servers.append(server);
            }
        }
    }
}

void V2RayConfigOutbound::toJson(OutboundHTTPConfigurationObject *settings, QJsonObject &json)
{
    QJsonArray serversArray;
    foreach(const HTTPServerObject *server, settings->servers) {
        QJsonObject serverObj;
        serverObj["address"] = server->address;
        serverObj["port"] = server->port;
        if (!server->users.isEmpty()) {
            QJsonArray usersArray;
            foreach (const AccountObject *user, server->users) {
                QJsonObject userObj;
                userObj["user"] = user->user;
                userObj["pass"] = user->pass;
                usersArray.append(userObj);
            }
            serverObj["users"] = usersArray;
        }
        serversArray.append(serverObj);
    }
    json["servers"] = serversArray;
}

void V2RayConfigOutbound::fromJson(OutboundMTProtoConfigurationObject __attribute__ ((unused)) &settings, const QJsonObject __attribute__ ((unused)) &json)
{
    // Nothing
}

void V2RayConfigOutbound::toJson(OutboundMTProtoConfigurationObject __attribute__ ((unused)) *settings, QJsonObject __attribute__ ((unused)) &json)
{
    // Nothing
}

void V2RayConfigOutbound::fromJson(OutboundShadowsocksConfigurationObject &settings, const QJsonObject &json)
{
    if (json.contains("servers") && json["servers"].isArray()) {
        foreach(QJsonValue serverValue, json["servers"].toArray()) {
            if (serverValue.isObject()) {
                QJsonObject serverObj = serverValue.toObject();
                ShadowsocksServerObject *server = new ShadowsocksServerObject;
                if (serverObj.contains("email") && serverObj["email"].isString()) {
                    server->email = serverObj["email"].toString();
                }
                if (serverObj.contains("address") && serverObj["address"].isString()) {
                    server->address = serverObj["address"].toString();
                }
                if (serverObj.contains("port") && serverObj["port"].isDouble()) {
                    server->port = serverObj["port"].toInt();
                }
                if (serverObj.contains("method") && serverObj["method"].isString()) {
                    server->method = serverObj["method"].toString();
                }
                if (serverObj.contains("password") && serverObj["password"].isString()) {
                    server->password = serverObj["password"].toString();
                }
                if (serverObj.contains("ota") && serverObj["ota"].isBool()) {
                    server->ota = serverObj["ota"].toBool();
                } else {
                    server->ota = false;
                }
                if (serverObj.contains("level") && serverObj["level"].isDouble()) {
                    server->level = serverObj["level"].toInt();
                }
                settings.servers.append(server);
            }
        }
    }
}

void V2RayConfigOutbound::toJson(OutboundShadowsocksConfigurationObject *settings, QJsonObject &json)
{
    QJsonArray serversArray;
    foreach(const ShadowsocksServerObject *server, settings->servers) {
        QJsonObject serverObj;
        serverObj["email"] = server->email;
        serverObj["address"] = server->address;
        serverObj["port"] = server->port;
        serverObj["method"] = server->method;
        serverObj["password"] = server->password;
        serverObj["ota"] = server->ota;
        serverObj["level"] = server->level;
        serversArray.append(serverObj);
    }
    json["servers"] = serversArray;
}

void V2RayConfigOutbound::fromJson(OutboundSocksConfigurationObject &settings, const QJsonObject &json)
{
    if (json.contains("servers") && json["servers"].isArray()) {
        foreach(QJsonValue serverValue, json["servers"].toArray()) {
            if (serverValue.isObject()) {
                QJsonObject serverObj = serverValue.toObject();
                SocksServerObject *server = new SocksServerObject;
                if (serverObj.contains("address") && serverObj["address"].isString()) {
                    server->address = serverObj["address"].toString();
                }
                if (serverObj.contains("port") && serverObj["port"].isDouble()) {
                    server->port = serverObj["port"].toInt();
                }
                if (serverObj.contains("users") && serverObj["users"].isArray()) {
                    foreach(QJsonValue userValue, serverObj["users"].toArray()) {
                        if (userValue.isObject()) {
                            QJsonObject userObj = userValue.toObject();
                            AccountUserObject *user = new AccountUserObject;
                            if (userObj.contains("user") && userObj["user"].isString()) {
                                user->user = userObj["user"].toString();
                            }
                            if (userObj.contains("pass") && userObj["pass"].isString()) {
                                user->pass = userObj["pass"].toString();
                            }
                            if (userObj.contains("level") && userObj["level"].isDouble()) {
                                user->level = userObj["level"].toInt();
                            }
                            server->users.append(user);
                        }
                    }
                }
                settings.servers.append(server);
            }
        }
    }
}

void V2RayConfigOutbound::toJson(OutboundSocksConfigurationObject *settings, QJsonObject &json)
{
    QJsonArray serversArray;
    foreach(const SocksServerObject *server, settings->servers) {
        QJsonObject serverObj;
        serverObj["address"] = server->address;
        serverObj["port"] = server->port;
        if (!server->users.isEmpty()) {
            QJsonArray usersArray;
            foreach(const AccountUserObject *user, server->users) {
                QJsonObject userObj;
                userObj["user"] = user->user;
                userObj["pass"] = user->pass;
                userObj["level"] = user->level;
                usersArray.append(userObj);
            }
            serverObj["users"] = usersArray;
        }
        serversArray.append(serverObj);
    }
    json["servers"] = serversArray;
}

void V2RayConfigOutbound::fromJson(OutboundVMessConfigurationObject &settings, const QJsonObject &json)
{
    if (json.contains("vnext") && json["vnext"].isArray()) {
        foreach(QJsonValue serverValue, json["vnext"].toArray()) {
            if (serverValue.isObject()) {
                QJsonObject serverObj = serverValue.toObject();
                VMessServerObject *vnext = new VMessServerObject;
                if (serverObj.contains("address") && serverObj["address"].isString()) {
                    vnext->address = serverObj["address"].toString();
                }
                if (serverObj.contains("port") && serverObj["port"].isDouble()) {
                    vnext->port = serverObj["port"].toInt();
                }

                if (serverObj.contains("users") && serverObj["users"].isArray()) {
                    foreach(QJsonValue userValue, serverObj["users"].toArray()) {
                        if (userValue.isObject()) {
                            QJsonObject userObj = userValue.toObject();
                            UserObject *user = new UserObject;
                            if (userObj.contains("id") && userObj["id"].isString()) {
                                user->id = userObj["id"].toString();
                            }
                            if (userObj.contains("alterId") && userObj["alterId"].isDouble()) {
                                user->alterId = userObj["alterId"].toInt();
                            }
                            if (userObj.contains("security") && userObj["security"].isString()) {
                                user->security = userObj["security"].toString();
                            } else {
                                user->security = "auto";
                            }
                            if (userObj.contains("level") && userObj["level"].isDouble()) {
                                user->level = userObj["level"].toInt();
                            }
                            vnext->users.append(user);
                        }
                    }
                }
                settings.vnext.append(vnext);
            }
        }
    }
}

void V2RayConfigOutbound::toJson(OutboundVMessConfigurationObject *settings, QJsonObject &json)
{
    QJsonArray vnextArray;
    foreach (const VMessServerObject *vnext, settings->vnext) {
        QJsonObject vnextObj;
        vnextObj["address"] = vnext->address;
        vnextObj["port"] = vnext->port;
        if (!vnext->users.isEmpty()) {
            QJsonArray usersArray;
            foreach (const UserObject *user, vnext->users) {
                QJsonObject userObj;
                userObj["id"] = user->id;
                userObj["alterId"] = user->alterId;
                userObj["level"] = user->level;
                userObj["security"] = user->security;
                usersArray.append(userObj);
            }
            vnextObj["users"] = usersArray;
        }
        vnextArray.append(vnextObj);
    }
    json["vnext"] = vnextArray;
}

void V2RayConfigOutbound::fromJson(StreamSettingsObject &settings, const QJsonObject &json)
{
    if (json.contains("network") && json["network"].isString()) {
        settings.network = json["network"].toString();
    } else {
        settings.network = "ws";
    }
    if (json.contains("security") && json["security"].isString()) {
        settings.security = json["security"].toString();
    } else {
        settings.security = "none";
    }
    if (json.contains("sockopt") && json["sockopt"].isObject()) {
        settings.sockopt = new SockoptObject;
        fromJson(*(settings.sockopt), json["sockopt"].toObject());
    } else {
        settings.sockopt = 0;
    }
    if (json.contains("tlsSettings") && json["tlsSettings"].isObject()) {
        settings.tlsSettings = new TransportTlsObject;
        fromJson(*(settings.tlsSettings), json["tlsSettings"].toObject());
    } else {
        settings.tlsSettings = 0;
    }
    if (json.contains("tcpSettings") && json["tcpSettings"].isObject()) {
        settings.tcpSettings = new TransportTcpObject;
        fromJson(*(settings.tcpSettings), json["tcpSettings"].toObject());
    } else {
        settings.tcpSettings = 0;
    }
    if (json.contains("kcpSettings") && json["kcpSettings"].isObject()) {
        settings.kcpSettings = new TransportKcpObject;
        fromJson(*(settings.kcpSettings), json["kcpSettings"].toObject());
    } else {
        settings.kcpSettings = 0;
    }
    if (json.contains("wsSettings") && json["wsSettings"].isObject()) {
        settings.wsSettings = new TransportWebSocketObject;
        fromJson(*(settings.wsSettings), json["wsSettings"].toObject());
    } else {
        settings.wsSettings = 0;
    }
    if (json.contains("httpSettings") && json["httpSettings"].isObject()) {
        settings.httpSettings = new TransportHTTPObject;
        fromJson(*(settings.httpSettings), json["httpSettings"].toObject());
    } else {
        settings.httpSettings = 0;
    }
    if (json.contains("dsSettings") && json["dsSettings"].isObject()) {
        settings.dsSettings = new TransportDomainSocketObject;
        fromJson(*(settings.dsSettings), json["dsSettings"].toObject());
    } else {
        settings.dsSettings = 0;
    }
    if (json.contains("quicSettings") && json["quicSettings"].isObject()) {
        settings.quicSettings = new TransportQuicObject;
        fromJson(*(settings.quicSettings), json["quicSettings"].toObject());
    } else {
        settings.quicSettings = 0;
    }
}

void V2RayConfigOutbound::toJson(StreamSettingsObject *settings, QJsonObject &json)
{
    json["network"] = settings->network;
    json["security"] = settings->security;

    if (settings->sockopt) {
        QJsonObject sockoptObj;
        toJson(settings->sockopt, sockoptObj);
        json["sockopt"] = sockoptObj;
    }

    if (settings->tlsSettings) {
        QJsonObject settingsObj;
        toJson(settings->tlsSettings, settingsObj);
        json["tlsSettings"] = settingsObj;
    } else {
        json["tlsSettings"] = QJsonValue(QJsonValue::Null);
    }

    if (settings->tcpSettings) {
        QJsonObject settingsObj;
        toJson(settings->tcpSettings, settingsObj);
        json["tcpSettings"] = settingsObj;
    } else {
        json["tcpSettings"] = QJsonValue(QJsonValue::Null);
    }

    if (settings->kcpSettings) {
        QJsonObject settingsObj;
        toJson(settings->kcpSettings, settingsObj);
        json["kcpSettings"] = settingsObj;
    } else {
        json["kcpSettings"] = QJsonValue(QJsonValue::Null);
    }

    if (settings->wsSettings) {
        QJsonObject settingsObj;
        toJson(settings->wsSettings, settingsObj);
        json["wsSettings"] = settingsObj;
    } else {
        json["wsSettings"] = QJsonValue(QJsonValue::Null);
    }

    if (settings->httpSettings) {
        QJsonObject settingsObj;
        toJson(settings->httpSettings, settingsObj);
        json["httpSettings"] = settingsObj;
    } else {
        json["httpSettings"] = QJsonValue(QJsonValue::Null);
    }

    if (settings->dsSettings) {
        QJsonObject settingsObj;
        toJson(settings->dsSettings, settingsObj);
        json["dsSettings"] = settingsObj;
    } else {
        json["dsSettings"] = QJsonValue(QJsonValue::Null);
    }

    if (settings->quicSettings) {
        QJsonObject settingsObj;
        toJson(settings->quicSettings, settingsObj);
        json["quicSettings"] = settingsObj;
    } else {
        json["quicSettings"] = QJsonValue(QJsonValue::Null);
    }
}

void V2RayConfigOutbound::fromJson(MuxObject &settings, const QJsonObject &json)
{
    if (json.contains("enabled") && json["enabled"].isBool()) {
        settings.enabled = json["enabled"].toBool();
    }
    if (json.contains("concurrency") && json["concurrency"].isDouble()) {
        settings.concurrency = json["concurrency"].toInt();
    }
}

void V2RayConfigOutbound::toJson(MuxObject *settings, QJsonObject &json)
{
    json["enabled"] = settings->enabled;
    json["concurrency"] = settings->concurrency;
}

void V2RayConfigOutbound::fromJson(SockoptObject &settings, const QJsonObject &json)
{
    if (json.contains("mark") && json["mark"].isDouble()) {
        settings.mark = json["mark"].toInt();
    }
    if (json.contains("tcpFastOpen") && json["tcpFastOpen"].isBool()) {
        settings.tcpFastOpen = json["tcpFastOpen"].toBool();
    }
    if (json.contains("tproxy") && json["tproxy"].isString()) {
        settings.tproxy = json["tproxy"].toString();
    }
}

void V2RayConfigOutbound::toJson(SockoptObject *settings, QJsonObject &json)
{
    json["mark"] = settings->mark;
    json["tcpFastOpen"] = settings->tcpFastOpen;
    json["tproxy"] = settings->tproxy;
}

void V2RayConfigOutbound::fromJson(TransportTlsObject &settings, const QJsonObject &json)
{
    if (json.contains("serverName") && json["serverName"].isString()) {
        settings.serverName = json["serverName"].toString();
    }
    if (json.contains("allowInsecure") && json["allowInsecure"].isBool()) {
        settings.allowInsecure = json["allowInsecure"].toBool();
    }
    if (json.contains("disableSystemRoot") && json["disableSystemRoot"].isBool()) {
        settings.disableSystemRoot = json["disableSystemRoot"].toBool();
    }
    if (json.contains("alpn") && json["alpn"].isArray()) {
        foreach (QJsonValue value, json["alpn"].toArray()) {
            if (value.isString()) {
                settings.alpn.append(value.toString());
            }
        }
    }
    if (json.contains("certificates") && json["certificates"].isArray()) {
        foreach (QJsonValue value, json["certificates"].toArray()) {
            if (value.isObject()) {
                QJsonObject obj = value.toObject();
                CertificateObject *certificate = new CertificateObject;
                if (obj.contains("usage") && obj["usage"].isString()) {
                    certificate->usage = obj["usage"].toString();
                }
                if (obj.contains("certificateFile") && obj["certificateFile"].isString()) {
                    certificate->certificateFile = obj["certificateFile"].toString();
                }
                if (obj.contains("keyFile") && obj["keyFile"].isString()) {
                    certificate->keyFile = obj["keyFile"].toString();
                }
                if (obj.contains("certificate") && obj["certificate"].isArray()) {
                    foreach (QJsonValue value, obj["certificate"].toArray()) {
                        if (value.isString()) {
                            certificate->certificate.append(value.toString());
                        }
                    }
                }
                if (obj.contains("key") && obj["key"].isArray()) {
                    foreach (QJsonValue value, obj["key"].toArray()) {
                        if (value.isString()) {
                            certificate->key.append(value.toString());
                        }
                    }
                }
                settings.certificates.append(*certificate);
            }
        }
    }
}

void V2RayConfigOutbound::toJson(TransportTlsObject *settings, QJsonObject &json)
{
    json["serverName"] = settings->serverName;
    json["allowInsecure"] = settings->allowInsecure;
    json["disableSystemRoot"] = settings->disableSystemRoot;
    QJsonArray alpnArray;
    foreach(const QString val, settings->alpn) {
        alpnArray.append(val);
    }
    json["alpn"] = alpnArray;

    QJsonArray certArray;
    foreach(const CertificateObject cert, settings->certificates) {
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
    json["certificates"] = certArray;
}

void V2RayConfigOutbound::fromJson(TransportTcpObject &settings, const QJsonObject &json)
{
    if (json.contains("header") && json["header"].isObject()) {
        QJsonObject headerObj = json["header"].toObject();
        if (headerObj.contains("type") && headerObj["type"].isString()) {
            settings.header.type = headerObj["type"].toString();
        }
        if (headerObj.contains("request") && headerObj["request"].isObject()) {
            QJsonObject requestObj = headerObj["request"].toObject();
            if (requestObj.contains("version") && requestObj["version"].isString()) {
                settings.header.request.version = requestObj["version"].toString();
            }
            if (requestObj.contains("method") && requestObj["method"].isString()) {
                settings.header.request.method = requestObj["method"].toString();
            }
            if (requestObj.contains("path") && requestObj["path"].isArray()) {
                foreach (QJsonValue value, requestObj["path"].toArray()) {
                    if (value.isString()) {
                        settings.header.request.path.append(value.toString());
                    }
                }
            }
            if (requestObj.contains("headers") && requestObj["headers"].isObject()) {
                QJsonObject headersObj = requestObj["headers"].toObject();
                foreach(const QString& key, headersObj.keys()) {
                    if (headersObj.value(key).isArray()) {
                        QStringList *list = new QStringList;
                        foreach (QJsonValue value, headersObj.value(key).toArray()) {
                            if (value.isString()) {
                                list->append(value.toString());
                            }
                        }
                        settings.header.request.headers.insert(key, *list);
                    }
                }
            }
        }
        if (headerObj.contains("response") && headerObj["response"].isObject()) {
            QJsonObject responseObj = headerObj["response"].toObject();
            if (responseObj.contains("version") && responseObj["version"].isString()) {
                settings.header.response.version = responseObj["version"].toString();
            }
            if (responseObj.contains("status") && responseObj["status"].isString()) {
                settings.header.response.status = responseObj["status"].toString();
            }
            if (responseObj.contains("reason") && responseObj["reason"].isString()) {
                settings.header.response.reason = responseObj["reason"].toString();
            }
            if (responseObj.contains("headers") && responseObj["headers"].isObject()) {
                QJsonObject headersObj = responseObj["headers"].toObject();
                foreach(const QString& key, headersObj.keys()) {
                    if (headersObj.value(key).isArray()) {
                        QStringList *list = new QStringList;
                        foreach (QJsonValue value, headersObj.value(key).toArray()) {
                            if (value.isString()) {
                                list->append(value.toString());
                            }
                        }
                        settings.header.response.headers.insert(key, *list);
                    }
                }
            }

        }
    }
}

void V2RayConfigOutbound::toJson(TransportTcpObject *settings, QJsonObject &json)
{
    QJsonObject headerObj;
    HTTPHeaderObject header = settings->header;
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

    json["header"] = headerObj;
}

void V2RayConfigOutbound::fromJson(TransportKcpObject &settings, const QJsonObject &json)
{
    if (json.contains("mtu") && json["mtu"].isDouble()) {
        settings.mtu = json["mtu"].toInt();
    }
    if (json.contains("tti") && json["tti"].isDouble()) {
        settings.tti = json["tti"].toInt();
    }
    if (json.contains("uplinkCapacity") && json["uplinkCapacity"].isDouble()) {
        settings.uplinkCapacity = json["uplinkCapacity"].toInt();
    }
    if (json.contains("downlinkCapacity") && json["downlinkCapacity"].isDouble()) {
        settings.downlinkCapacity = json["downlinkCapacity"].toInt();
    }
    if (json.contains("congestion") && json["congestion"].isBool()) {
        settings.congestion = json["congestion"].toBool();
    }
    if (json.contains("readBufferSize") && json["readBufferSize"].isDouble()) {
        settings.readBufferSize = json["readBufferSize"].toInt();
    }
    if (json.contains("writeBufferSize") && json["writeBufferSize"].isDouble()) {
        settings.writeBufferSize = json["writeBufferSize"].toInt();
    }
    if (json.contains("header") && json["header"].isObject()) {
        QJsonObject headerObj = json["header"].toObject();
        if (headerObj.contains("type") && headerObj["type"].isString()) {
            settings.header.type = headerObj["type"].toString();
        }
    }
}

void V2RayConfigOutbound::toJson(TransportKcpObject *settings, QJsonObject &json)
{
    json["mtu"] = settings->mtu;
    json["tti"] = settings->tti;
    json["uplinkCapacity"] = settings->uplinkCapacity;
    json["downlinkCapacity"] = settings->downlinkCapacity;
    json["congestion"] = settings->congestion;
    json["readBufferSize"] = settings->readBufferSize;
    json["writeBufferSize"] = settings->writeBufferSize;
    QJsonObject headerObj;
    headerObj["type"] = settings->header.type;
    json["header"] = headerObj;
}

void V2RayConfigOutbound::fromJson(TransportWebSocketObject &settings, const QJsonObject &json)
{
    if (json.contains("path") && json["path"].isString()) {
        settings.path = json["path"].toString();
    }
    if (json.contains("headers") && json["headers"].isObject()) {
        QJsonObject headersObj = json["headers"].toObject();
        foreach(const QString& key, headersObj.keys()) {
            if (headersObj.value(key).isString()) {
                settings.headers.insert(key, headersObj.value(key).toString());
            }
        }
    }
}

void V2RayConfigOutbound::toJson(TransportWebSocketObject *settings, QJsonObject &json)
{
    json["path"] = settings->path;
    QJsonObject headersObj;
    QMapIterator<QString, QString> it(settings->headers);
    while (it.hasNext()) {
        it.next();
        headersObj[it.key()] = it.value();
    }
    json["headers"] = headersObj;
}

void V2RayConfigOutbound::fromJson(TransportHTTPObject &settings, const QJsonObject &json)
{
    if (json.contains("host") && json["host"].isArray()) {
        foreach (QJsonValue value, json["host"].toArray()) {
            if (value.isString()) {
                settings.host.append(value.toString());
            }
        }
    }
    if (json.contains("path") && json["path"].isString()) {
        settings.path = json["path"].toString();
    }
}

void V2RayConfigOutbound::toJson(TransportHTTPObject *settings, QJsonObject &json)
{
    json["path"] = settings->path;
    QJsonArray hostArray;
    foreach (const QString path, settings->host) {
        hostArray.append(path);
    }
    json["host"] = hostArray;
}

void V2RayConfigOutbound::fromJson(TransportDomainSocketObject &settings, const QJsonObject &json)
{
    if (json.contains("path") && json["path"].isString()) {
        settings.path = json["path"].toString();
    }
}

void V2RayConfigOutbound::toJson(TransportDomainSocketObject *settings, QJsonObject &json)
{
    json["path"] = settings->path;
}

void V2RayConfigOutbound::fromJson(TransportQuicObject &settings, const QJsonObject &json)
{
    if (json.contains("security") && json["security"].isString()) {
        settings.security = json["security"].toString();
    }
    if (json.contains("key") && json["key"].isString()) {
        settings.key = json["key"].toString();
    }
    if (json.contains("header") && json["header"].isObject()) {
        QJsonObject headerObj = json["header"].toObject();
        if (headerObj.contains("type") && headerObj["type"].isString()) {
            settings.header.type = headerObj["type"].toString();
        }
    }
}

void V2RayConfigOutbound::toJson(TransportQuicObject *settings, QJsonObject &json)
{
    json["security"] = settings->security;
    json["key"] = settings->key;
    QJsonObject headerObj;
    headerObj["type"] = settings->header.type;
    json["header"] = headerObj;
}
