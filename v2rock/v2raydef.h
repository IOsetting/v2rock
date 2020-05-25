#ifndef V2RAYDEF_H
#define V2RAYDEF_H

#include <QList>
#include <QMap>
#include <QString>

/*
    Policy Objects
*/
struct LevelPolicyObject {
    int handshake;
    int connIdle;
    int uplinkOnly;
    int downlinkOnly;
    bool statsUserUplink;
    bool statsUserDownlink;
    int bufferSize;
};

struct SystemPolicyObject {
    bool statsInboundUplink;
    bool statsInboundDownlink;
};

struct PolicyObject {
    QMap<QString, LevelPolicyObject> levels;
    SystemPolicyObject system;
};
/*
    Policy Objects End
*/

struct ApiObject {
    QString tag;
    QStringList services;
};


/*
    DNS Objects
*/
struct DNSServerObject {
    QString address;
    int port;
    QStringList domains;
};

struct DNSObject {
    QString tag;
    QString clientIp;
    QMap<QString, QString> hosts;
    QStringList servers;
    QList<DNSServerObject> serverObjects;
};
/*
    DNS Objects End
*/


struct AccountObject {
    QString user;
    QString pass;

    AccountObject(){}
    AccountObject(const AccountObject& a) :
        user(a.user), pass(a.pass) {}
};

struct AccountUserObject {
    QString user;
    QString pass;
    int level;

    AccountUserObject(){}
    AccountUserObject(const AccountUserObject& a) :
        user(a.user), pass(a.pass), level(a.level) {}
};

struct UserObject {
    QString id;
    int alterId;
    //  "aes-128-gcm" | "chacha20-poly1305" | "auto" | "none"
    QString security;
    int level;

    UserObject(){}
    UserObject(const UserObject& a) :
        id(a.id), alterId(a.alterId), security(a.security), level(a.level) {}
};

struct MTProtoUserObject {
    QString email;
    int level;
    QString secret;

    MTProtoUserObject(){}
    MTProtoUserObject(const MTProtoUserObject& a) :
        email(a.email), level(a.level), secret(a.secret) {}
};

struct VMessClientObject {
    QString id;
    int level;
    int alterId;
    QString email;

    VMessClientObject(){}
    VMessClientObject(const VMessClientObject& a) :
        id(a.id), level(a.level), alterId(a.alterId), email(a.email) {}
};

struct VMessDefaultObject {
    int level;
    int alterId;

    VMessDefaultObject(){}
    VMessDefaultObject(const VMessDefaultObject& a) :
        level(a.level), alterId(a.alterId) {}
};

struct VMessDetourObject {
    QString to;

    VMessDetourObject(){}
    VMessDetourObject(const VMessDetourObject& a) : to(a.to) {}
};

struct MuxObject {
    bool enabled;
    int concurrency;

    MuxObject(){}
    MuxObject(const MuxObject& a) : enabled(a.enabled), concurrency(a.concurrency) {}
};


/*
    Inbound Settings
*/
struct InboundDokodemoDoorConfigurationObject {
    QString address;
    int port;
    // "tcp" | "udp" | "tcp,udp"
    QString network;
    int timeout;
    bool followRedirect;
    int userLevel;

    InboundDokodemoDoorConfigurationObject(){}
    InboundDokodemoDoorConfigurationObject(const InboundDokodemoDoorConfigurationObject& a) :
        address(a.address), port(a.port), network(a.network), timeout(a.timeout),
        followRedirect(a.followRedirect), userLevel(a.userLevel) {}
};

struct InboundHTTPConfigurationObject {
    int timeout;
    QList<struct AccountObject *> accounts;
    bool allowTransparent;
    int userLevel;

    InboundHTTPConfigurationObject(){}
    InboundHTTPConfigurationObject(const InboundHTTPConfigurationObject& a) :
        timeout(a.timeout), allowTransparent(a.allowTransparent), userLevel(a.userLevel) {
        foreach(AccountObject *dummy, a.accounts) {
            AccountObject *account = new AccountObject(*dummy);
            accounts.append(account);
        }
    }
    ~InboundHTTPConfigurationObject() {
        foreach(AccountObject *account, accounts) {
            delete account;
        }
    }
};

struct InboundMTProtoConfigurationObject {
    QList<struct MTProtoUserObject *> users;

    InboundMTProtoConfigurationObject(){}
    InboundMTProtoConfigurationObject(const InboundMTProtoConfigurationObject& a) {
        foreach(MTProtoUserObject *dummy, a.users) {
            MTProtoUserObject *user = new MTProtoUserObject(*dummy);
            users.append(user);
        }
    }
    ~InboundMTProtoConfigurationObject() {
        foreach (MTProtoUserObject *user, users) {
            delete user;
        }
    }
};

struct InboundShadowsocksConfigurationObject {
    QString email;
    // "aes-256-cfb" "aes-128-cfb" "chacha20" "chacha20-ietf"
    // "aes-256-gcm" "aes-128-gcm" "chacha20-poly1305" "chacha20-ietf-poly1305"
    QString method;
    QString password;
    int level;
    bool ota;
    //"tcp" | "udp" | "tcp,udp"
    QString network;

    InboundShadowsocksConfigurationObject(){}
    InboundShadowsocksConfigurationObject(const InboundShadowsocksConfigurationObject& a) :
        email(a.email), method(a.method), password(a.password), level(a.level), ota(a.ota),
        network(a.network) {}
};

struct InboundSocksConfigurationObject {
    // "noauth" | "password"
    QString auth;
    QList<struct AccountObject *> accounts;
    bool udp;
    QString ip;
    int userLevel;

    InboundSocksConfigurationObject(){}
    InboundSocksConfigurationObject(const InboundSocksConfigurationObject& a) :
        auth(a.auth), udp(a.udp), ip(a.ip), userLevel(a.userLevel) {
        foreach(AccountObject *dummy, a.accounts) {
            AccountObject *account = new AccountObject(*dummy);
            accounts.append(account);
        }
    }
    ~InboundSocksConfigurationObject() {
        foreach (AccountObject *account, accounts) {
            delete account;
        }
    }
};

struct InboundVMessConfigurationObject {
    QList<VMessClientObject *> clients;
    VMessDefaultObject dephault;
    VMessDetourObject detour;
    bool disableInsecureEncryption;

    InboundVMessConfigurationObject(){}
    InboundVMessConfigurationObject(const InboundVMessConfigurationObject& a) :
        dephault(a.dephault), detour(a.detour),disableInsecureEncryption(a.disableInsecureEncryption) {
        foreach(VMessClientObject *dummy, a.clients) {
            VMessClientObject *client = new VMessClientObject(*dummy);
            clients.append(client);
        }
    }
    ~InboundVMessConfigurationObject() {
        foreach(VMessClientObject *client, clients) {
            delete client;
        }
    }
};
/*
    Inbound Settings End
*/


struct ResponseObject {
    // "http" | "none"
    QString type;

    ResponseObject(){}
    ResponseObject(const ResponseObject& a) : type(a.type) {}
};

struct SniffingObject {
    bool enabled;
    // "http" | "tls"
    QStringList destOverride;

    SniffingObject(){}
    SniffingObject(const SniffingObject& a) : enabled(a.enabled), destOverride(a.destOverride) {}
};

struct HTTPServerObject {
    QString address;
    int port;
    QList<struct AccountObject *> users;

    HTTPServerObject(){}
    HTTPServerObject(const HTTPServerObject& a) :
        address(a.address), port(a.port) {
        foreach (AccountObject * dummy, a.users) {
            AccountObject *user = new AccountObject(*dummy);
            users.append(user);
        }
    }
};

struct ShadowsocksServerObject {
    QString email;
    QString address;
    int port;
    // "aes-256-cfb" "aes-128-cfb" "chacha20" "chacha20-ietf" "aes-256-gcm" "aes-128-gcm" "chacha20-poly1305" 或 "chacha20-ietf-poly1305"
    QString method;
    QString password;
    bool ota;
    int level;

    ShadowsocksServerObject(){}
    ShadowsocksServerObject(const ShadowsocksServerObject& a) :
    email(a.email), address(a.address), port(a.port), method(a.method), password(a.password),
    ota(a.ota), level(a.level) {}
};

struct SocksServerObject {
    QString address;
    int port;
    QList<struct AccountUserObject *> users;

    SocksServerObject(){}
    SocksServerObject(const SocksServerObject& a) :
        address(a.address), port(a.port) {
        foreach (AccountUserObject * dummy, a.users) {
            AccountUserObject *user = new AccountUserObject(*dummy);
            users.append(user);
        }
    }
};

struct VMessServerObject {
    QString address;
    int port;
    QList<struct UserObject *> users;

    VMessServerObject(){}
    VMessServerObject(const VMessServerObject& a) :
        address(a.address), port(a.port) {
        foreach (UserObject * dummy, a.users) {
            UserObject *user = new UserObject(*dummy);
            users.append(user);
        }
    }
    ~VMessServerObject() {
        foreach (UserObject * user, users) {
            delete user;
        }
    }
};

/*
    Outbound Settings
*/
struct OutboundBlackholeConfigurationObject
{
    struct ResponseObject response;

    OutboundBlackholeConfigurationObject(){}
    OutboundBlackholeConfigurationObject(const OutboundBlackholeConfigurationObject& a) :
        response(a.response) {}
};

struct OutboundDNSConfigurationObject {
    // "tcp" | "udp"
    QString network;
    QString address;
    int port;

    OutboundDNSConfigurationObject(){}
    OutboundDNSConfigurationObject(const OutboundDNSConfigurationObject& a) :
        network(a.network), address(a.address), port(a.port) {}
};

struct OutboundFreedomConfigurationObject {
    // "AsIs" | "UseIP" | "UseIPv4" | "UseIPv6"
    QString domainStrategy;
    QString redirect;
    int userLevel;

    OutboundFreedomConfigurationObject(){}
    OutboundFreedomConfigurationObject(const OutboundFreedomConfigurationObject& a) :
        domainStrategy(a.domainStrategy), redirect(a.redirect), userLevel(a.userLevel) {}
};

struct OutboundHTTPConfigurationObject {
    QList<HTTPServerObject *> servers;

    OutboundHTTPConfigurationObject(){}
    OutboundHTTPConfigurationObject(const OutboundHTTPConfigurationObject& a) {
        foreach (HTTPServerObject *dummy, a.servers) {
            HTTPServerObject *server = new HTTPServerObject(*dummy);
            servers.append(server);
        }
    }
    ~OutboundHTTPConfigurationObject() {
        foreach (HTTPServerObject * server, servers) {
            delete server;
        }
    }
};

struct OutboundMTProtoConfigurationObject {
    // Empty
};

struct OutboundShadowsocksConfigurationObject {
    QList<ShadowsocksServerObject *> servers;

    OutboundShadowsocksConfigurationObject(){}
    OutboundShadowsocksConfigurationObject(const OutboundShadowsocksConfigurationObject& a) {
        foreach (ShadowsocksServerObject *dummy, a.servers) {
            ShadowsocksServerObject *server = new ShadowsocksServerObject(*dummy);
            servers.append(server);
        }
    }
    ~OutboundShadowsocksConfigurationObject() {
        foreach (ShadowsocksServerObject * server, servers) {
            delete server;
        }
    }
};

struct OutboundSocksConfigurationObject {
    QList<SocksServerObject *> servers;

    OutboundSocksConfigurationObject(){}
    OutboundSocksConfigurationObject(const OutboundSocksConfigurationObject& a) {
        foreach (SocksServerObject *dummy, a.servers) {
            SocksServerObject *server = new SocksServerObject(*dummy);
            servers.append(server);
        }
    }
    ~OutboundSocksConfigurationObject() {
        foreach (SocksServerObject * server, servers) {
            delete server;
        }
    }
};

struct OutboundVMessConfigurationObject {
    QList<VMessServerObject *> vnext;

    OutboundVMessConfigurationObject(){}
    OutboundVMessConfigurationObject(const OutboundVMessConfigurationObject& a) {
        foreach (VMessServerObject *dummy, a.vnext) {
            VMessServerObject *server = new VMessServerObject(*dummy);
            vnext.append(server);
        }
    }
    ~OutboundVMessConfigurationObject() {
        foreach (VMessServerObject * server, vnext) {
            delete server;
        }
    }
};

/*
    Outbound Settings End
*/


struct HTTPRequestObject {
    // "1.1"
    QString version;
    // "GET"
    QString method;
    // ["/"]
    QStringList path;
    // "Host", "User-Agent", "Accept-Encoding", "Connection", "Pragma"
    QMap<QString, QStringList> headers;

    HTTPRequestObject(){}
    HTTPRequestObject(const HTTPRequestObject& a) :
        version(a.version), method(a.method), path(a.path), headers(a.headers) {}
};

struct HTTPResponseObject {
    // "1.1"
    QString version;
    // 200
    QString status;
    // "OK"
    QString reason;
    // "Content-Type", "Transfer-Encoding", "Connection", "Pragma"
    QMap<QString, QStringList> headers;

    HTTPResponseObject(){}
    HTTPResponseObject(const HTTPResponseObject& a) :
        version(a.version), status(a.status), reason(a.reason), headers(a.headers) {}
};

struct HTTPHeaderObject {
    QString type;
    struct HTTPRequestObject *request;
    struct HTTPResponseObject *response;

    HTTPHeaderObject(){}
    HTTPHeaderObject(const HTTPHeaderObject& a) : type(a.type) {
        if (a.request) {
            request = new HTTPRequestObject(*(a.request));
        } else {
            request = 0;
        }
        if (a.response) {
            response = new HTTPResponseObject(*(a.response));
        } else {
            response = 0;
        }
    }
    ~HTTPHeaderObject() {
        if (request) delete request;
        if (response) delete response;
    }
};

struct HeaderObject {
    // "none", "srtp", "utp", "wechat-video", "dtls", "wireguard"
    QString type;

    HeaderObject(){}
    HeaderObject(const HeaderObject& a) : type(a.type) {}
};


/*
    Transport Settings
*/
struct TransportDomainSocketObject {
    QString path;

    TransportDomainSocketObject(){}
    TransportDomainSocketObject(const TransportDomainSocketObject& a) : path(a.path) {}
};

struct TransportHTTPObject {
    QStringList host;
    QString path;

    TransportHTTPObject(){}
    TransportHTTPObject(const TransportHTTPObject& a) :
        host(a.host), path(a.path) {}
};

struct TransportKcpObject {
    int mtu;
    int tti;
    int uplinkCapacity;
    int downlinkCapacity;
    bool congestion;
    int readBufferSize;
    int writeBufferSize;
    struct HeaderObject header;

    TransportKcpObject(){}
    TransportKcpObject(const TransportKcpObject& a) :
        mtu(a.mtu), tti(a.tti), uplinkCapacity(a.uplinkCapacity), downlinkCapacity(a.downlinkCapacity),
        congestion(a.congestion), readBufferSize(a.readBufferSize), writeBufferSize(a.writeBufferSize),
        header(a.header) {}
};

struct TransportQuicObject {
    // "none" | "aes-128-gcm" | "chacha20-poly1305"
    QString security;
    QString key;
    struct HeaderObject header;

    TransportQuicObject() : security("none") {}
    TransportQuicObject(const TransportQuicObject& a) :
        security(a.security), key(a.key), header(a.header) {}
};

struct TransportTcpObject {
    struct HTTPHeaderObject header;

    TransportTcpObject(){}
    TransportTcpObject(const TransportTcpObject& a) : header(a.header) {}
};

struct TransportWebSocketObject {
    QString path;
    // "Host",
    QMap<QString, QString> headers;

    TransportWebSocketObject(){}
    TransportWebSocketObject(const TransportWebSocketObject& a) :
        path(a.path), headers(a.headers){}
};

struct CertificateObject {
    // "encipherment" | "verify" | "issue"
    QString usage;
    QString certificateFile;
    QStringList certificate;
    QString keyFile;
    QStringList key;
};

struct TransportTlsObject {
    QString serverName;
    bool allowInsecure;
    QStringList alpn;
    QList<struct CertificateObject> certificates;
    bool disableSystemRoot;

    TransportTlsObject(){}
    TransportTlsObject(const TransportTlsObject& a) :
        serverName(a.serverName), allowInsecure(a.allowInsecure), alpn(a.alpn),
        certificates(a.certificates), disableSystemRoot(a.disableSystemRoot){}
};

struct SockoptObject {
    int mark;
    bool tcpFastOpen;
    // "redirect" | "tproxy" | "off"
    QString tproxy;

    SockoptObject(){}
    SockoptObject(const SockoptObject& a) :
        mark(a.mark), tcpFastOpen(a.tcpFastOpen), tproxy(a.tproxy) {}
};

struct StreamSettingsObject {
    // "tcp" | "kcp" | "ws" | "http" | "domainsocket" | "quic"
    QString network;
    // "none" | "tls"
    QString security;
    struct SockoptObject *sockopt;
    struct TransportTlsObject *tlsSettings;
    struct TransportTcpObject *tcpSettings;
    struct TransportKcpObject *kcpSettings;
    struct TransportWebSocketObject *wsSettings;
    struct TransportHTTPObject *httpSettings;
    struct TransportDomainSocketObject *dsSettings;
    struct TransportQuicObject *quicSettings;

    StreamSettingsObject() : sockopt(0), tlsSettings(0), tcpSettings(0),
        kcpSettings(0), wsSettings(0), httpSettings(0), dsSettings(0), quicSettings(0) {}

    StreamSettingsObject(const StreamSettingsObject& a) :
        network(a.network), security(a.security), sockopt(0), tlsSettings(0), tcpSettings(0),
        kcpSettings(0), wsSettings(0), httpSettings(0), dsSettings(0), quicSettings(0) {
        if (a.sockopt) {
            sockopt = new SockoptObject(*(a.sockopt));
        }
        if (a.tlsSettings) {
            tlsSettings = new TransportTlsObject(*(a.tlsSettings));
        }
        if (a.tcpSettings) {
            tcpSettings = new TransportTcpObject(*(a.tcpSettings));
        }
        if (a.kcpSettings) {
            kcpSettings = new TransportKcpObject(*(a.kcpSettings));
        }
        if (a.wsSettings) {
            wsSettings = new TransportWebSocketObject(*(a.wsSettings));
        }
        if (a.httpSettings) {
            httpSettings = new TransportHTTPObject(*(a.httpSettings));
        }
        if (a.dsSettings) {
            dsSettings = new TransportDomainSocketObject(*(a.dsSettings));
        }
        if (a.quicSettings) {
            quicSettings = new TransportQuicObject(*(a.quicSettings));
        }
    }

    ~StreamSettingsObject() {
        if (sockopt) delete sockopt;
        if (tlsSettings) delete tlsSettings;
        if (tcpSettings) delete tcpSettings;
        if (kcpSettings) delete kcpSettings;
        if (wsSettings) delete wsSettings;
        if (httpSettings) delete httpSettings;
        if (dsSettings) delete dsSettings;
        if (quicSettings) delete quicSettings;
    }
};

/*
    Transport Settings End
*/


/*
    Routing Objects
*/
struct RoutingRuleObject {
    // "field"
    QString type;
    // Subdomain (recommended): Begining with "domain:"
    // Full domain: Begining with "full:" and the rest is a domain.
    // Pre-defined domain list: Begining with "geosite:" and the rest is a name, such as geosite:google or geosite:cn.
    // category-ads, category-ads-all, cn (geolocation-cn + tld-cn), google, facebook, geolocation-cn, geolocation-!cn, speedtest, tld-cn
    QStringList *domain;
    QStringList *ip;
    // "53,443,1000-2000"
    QString *port;
    // "tcp" | "udp" | "tcp,udp"
    QString *network;
    QStringList *source;
    // An array of email address
    QStringList *user;
    QStringList *inboundTag;
    // "http" | "tls" | "bittorrent"
    QStringList *protocol;
    //Detect HTTP GET: "attrs[':method'] == 'GET'"
    //Detect HTTP Path: "attrs[':path'].startswith('/test')"
    //Detect Content Type: "attrs['accept'].index('text/html') >= 0"
    QString *attrs;
    QString *outboundTag;
    // V2Ray will use the balancer to select an outbound. Either outboundTag or balancerTag must be specified.
    // When both are specified, outboundTag takes priority
    QString *balancerTag;
};

struct RoutingBalancerObject {
    QString tag;
    // An array of strings. These strings are used to select outbounds with prefix matching. For example,
    // with the following outbound tags: [ "a", "ab", "c", "ba" ]，selector ["a"] matches [ "a", "ab" ].
    // When multiple outbounds are selected, load balancer for now picks one final outbound at random.
    QStringList selector;
};
/*
    Routing Objects End
*/


#endif // V2RAYDEF_H
