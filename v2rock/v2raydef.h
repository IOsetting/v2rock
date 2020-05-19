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
};

struct AccountUserObject {
    QString user;
    QString pass;
    int level;
};

struct UserObject {
    QString id;
    int alterId;
    //  "aes-128-gcm" | "chacha20-poly1305" | "auto" | "none"
    QString security;
    int level;
};

struct MTProtoUserObject {
    QString email;
    int level;
    QString secret;
};

struct VMessClientObject {
    QString id;
    int level;
    int alterId;
    QString email;
};

struct VMessDefaultObject {
    int level;
    int alterId;
};

struct VMessDetourObject {
    QString to;
};

struct MuxObject {
    bool enabled;
    int concurrency;
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
};

struct InboundHTTPConfigurationObject {
    int timeout;
    QList<struct AccountObject> *accounts;
    bool allowTransparent;
    int userLevel;
};

struct InboundMTProtoConfigurationObject {
    QList<struct MTProtoUserObject> *users;
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
};

struct InboundSocksConfigurationObject {
    // "noauth" | "password"
    QString auth;
    QList<struct AccountObject> *accounts;
    bool udp;
    QString ip;
    int userLevel;
};

struct InboundVMessConfigurationObject {
    QList<VMessClientObject> clients;
    VMessDefaultObject dephault;
    VMessDetourObject detour;
    bool disableInsecureEncryption;
};
/*
    Inbound Settings End
*/


struct ResponseObject {
    // "http" | "none"
    QString type;
};

struct SniffingObject {
    bool enabled;
    // "http" | "tls"
    QStringList destOverride;
};

struct HTTPServerObject {
    QString address;
    int port;
    QList<struct AccountObject> *users;
};

struct ShadowsocksServerObject {
    QString email;
    QString address;
    int port;
    QString method;
    QString password;
    bool ota;
    int level;
};

struct SocksServerObject {
    QString address;
    int port;
    QList<struct AccountUserObject> *users;
};

struct VMessServerObject {
    QString address;
    int port;
    QList<struct UserObject> *users;
};

/*
    Outbound Settings
*/
struct OutboundBlackholeConfigurationObject
{
    struct ResponseObject response;
};

struct OutboundDNSConfigurationObject {
    QString network;
    QString address;
    int port;
};

struct OutboundFreedomConfigurationObject {
    // "AsIs" | "UseIP" | "UseIPv4" | "UseIPv6"
    QString domainStrategy;
    QString *redirect;
    int userLevel;
};

struct OutboundHTTPConfigurationObject {
    QList<HTTPServerObject> servers;
};

struct OutboundMTProtoConfigurationObject {
    // Empty
};

struct OutboundShadowsocksConfigurationObject {
    QList<ShadowsocksServerObject> servers;
};

struct OutboundSocksConfigurationObject {
    QList<SocksServerObject> servers;
};

struct OutboundVMessConfigurationObject {
    QList<VMessServerObject> vnext;
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
};

struct HTTPHeaderObject {
    QString type;
    struct HTTPRequestObject request;
    struct HTTPResponseObject response;
};

struct HeaderObject {
    // "none", "srtp", "utp", "wechat-video", "dtls", "wireguard"
    QString type;
};


/*
    Transport Settings
*/
struct TransportDomainSocketObject {
    QString path;
};

struct TransportHTTPObject {
    QStringList host;
    QString path;
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
};

struct TransportQuicObject {
    // "none" | "aes-128-gcm" | "chacha20-poly1305"
    QString security;
    QString key;
    struct HeaderObject header;
};

struct TransportTcpObject {
    struct HTTPHeaderObject header;
};

struct TransportWebSocketObject {
    QString path;
    // "Host",
    QMap<QString, QString> headers;
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
};

struct SockoptObject {
    int mark;
    bool tcpFastOpen;
    // "redirect" | "tproxy" | "off"
    QString tproxy;
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
