#include "v2rockconfig.h"
#include "config.h"

V2RockConfig::V2RockConfig(QObject *parent) :
    QObject(parent), empty(true), dnsConfig(0), socksConfig(0), httpConfig(0)
{
    QString path = QStandardPaths::writableLocation(QStandardPaths::ConfigLocation);
    if (path.isEmpty())
    {
        qFatal("Cannot determine settings storage location");
    }
    workDir = path + "/v2rock";
    QDir *dir = new QDir(workDir);
    if (!dir->exists())
    {
        dir->mkpath(".");
        qDebug() << "Create nonexists path: " << workDir;
    }
}

V2RockConfig::~V2RockConfig()
{
    qDebug() << "Destruct V2RockConfig";
    bypassIps.clear();
    bypassDomains.clear();
    qDeleteAll(nodes);
    nodes.clear();
}

bool V2RockConfig::isEmpty() const
{
    return empty;
}

QString V2RockConfig::getWorkDir() const
{
    return workDir;
}

void V2RockConfig::setWorkDir(const QString &value)
{
    workDir = value;
}

QString V2RockConfig::getV2executablePath() const
{
    return v2executablePath;
}

void V2RockConfig::setV2executablePath(const QString &value)
{
    v2executablePath = value;
}

QString V2RockConfig::getSubscribeUrl() const
{
    return subscribeUrl;
}

void V2RockConfig::setSubscribeUrl(const QString &value)
{
    subscribeUrl = value;
}

QString V2RockConfig::getLoglevel() const
{
    return loglevel;
}

void V2RockConfig::setLoglevel(const QString &value)
{
    loglevel = value;
}

DNSObject *V2RockConfig::getDnsConfig() const
{
    return dnsConfig;
}

void V2RockConfig::setDnsConfig(DNSObject *value)
{
    dnsConfig = value;
}

void V2RockConfig::deleteDnsConfig()
{
    delete dnsConfig;
    dnsConfig = 0;
}

V2RayConfigInbound *V2RockConfig::getSocksConfig() const
{
    return socksConfig;
}

void V2RockConfig::setSocksConfig(V2RayConfigInbound *value)
{
    socksConfig = value;
}

void V2RockConfig::initSocksConfig(const QString &listen, const int port)
{
    socksConfig = new V2RayConfigInbound;
    socksConfig->setTag("socks-inbound");
    socksConfig->setProtocol("socks");
    socksConfig->setPort(port);
    socksConfig->setListen(listen);
    InboundSocksConfigurationObject *socksSettings = new InboundSocksConfigurationObject;
    socksSettings->auth = "noauth";
    socksSettings->ip = listen;
    socksSettings->udp = true;
    socksSettings->userLevel = 0;
    socksConfig->setSocksSettings(socksSettings);
    SniffingObject *sniffing = new SniffingObject;
    sniffing->enabled = true;
    sniffing->destOverride.append("http");
    sniffing->destOverride.append("tls");
    socksConfig->setSniffing(sniffing);
}

void V2RockConfig::deleteSocksConfig()
{
    delete socksConfig;
    socksConfig = 0;
}

V2RayConfigInbound *V2RockConfig::getHttpConfig() const
{
    return httpConfig;
}

void V2RockConfig::setHttpConfig(V2RayConfigInbound *value)
{
    httpConfig = value;
}

void V2RockConfig::initHttpConfig(const QString &listen, const int port)
{
    httpConfig = new V2RayConfigInbound;
    httpConfig->setTag("http-inbound");
    httpConfig->setProtocol("http");
    httpConfig->setPort(port);
    httpConfig->setListen(listen);
    InboundHTTPConfigurationObject *httpSettings = new InboundHTTPConfigurationObject;
    httpSettings->allowTransparent = false;
    httpSettings->timeout = 60 * 1000;
    httpSettings->userLevel = 0;
    httpConfig->setHttpSettings(httpSettings);
    SniffingObject *sniffing = new SniffingObject;
    sniffing->enabled = true;
    sniffing->destOverride.append("http");
    sniffing->destOverride.append("tls");
    httpConfig->setSniffing(sniffing);
}

void V2RockConfig::deleteHttpConfig()
{
    delete httpConfig;
    httpConfig = 0;
}

QList<QString> V2RockConfig::getBypassIps() const
{
    return bypassIps;
}

void V2RockConfig::setBypassIps(const QList<QString> &value)
{
    bypassIps = value;
}

QList<QString> V2RockConfig::getBypassDomains() const
{
    return bypassDomains;
}

void V2RockConfig::setBypassDomains(const QList<QString> &value)
{
    bypassDomains = value;
}

QList<V2RockNode *> V2RockConfig::getNodes() const
{
    return nodes;
}

void V2RockConfig::setNodes(const QList<V2RockNode *> &value)
{
    nodes = value;
}

void V2RockConfig::addNode(int index, V2RockNode *node)
{
    if (index >= nodes.size() || index < 0) {
        // append to the end
        nodes.append(node);
    } else {
        nodes.insert(index, node);
        if (nodeIndex >= index) nodeIndex++;
    }
}

void V2RockConfig::delNode(int index)
{
    if (index >= nodes.size()) {
        return;
    }
    nodes.removeAt(index);
    if (nodeIndex >= index) nodeIndex--;
}

int V2RockConfig::getNodeIndex() const
{
    return nodeIndex;
}

void V2RockConfig::setNodeIndex(int value)
{
    nodeIndex = value;
}

void V2RockConfig::init()
{
    v2executablePath = "/usr/bin/v2ray/v2ray";
    subscribeUrl = "";
    loglevel = "info";

    initSocksConfig("127.0.0.1", 1080);
    initHttpConfig("127.0.0.1", 1081);

    nodes.clear();

    bypassIps.clear();
    bypassIps.append("0.0.0.0/8");
    bypassIps.append("10.0.0.0/8");
    bypassIps.append("127.0.0.0/8");
    bypassIps.append("172.16.0.0/12");
    bypassIps.append("192.168.0.0/16");
    bypassIps.append("::1/128");
    bypassIps.append("fc00::/7");
    bypassIps.append("fe80::/10");

    bypassDomains.clear();
    bypassDomains.append("domain:baidu.com");
    bypassDomains.append("domain:bdstatic.com");
    bypassDomains.append("domain:baidustatic.com");
    bypassDomains.append("domain:qq.com");
    bypassDomains.append("domain:sogou.com");
    bypassDomains.append("domain:sogoucdn.com");
}

void V2RockConfig::read()
{
    QFile file(workDir + "/" + v2rock_config::main_config);
    if (!file.exists()) {
        return;
    }
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        emit logReceived("Configuration file cannot be read.");
        return;
    }
    QString data = file.readAll();
    file.close();

    QJsonParseError errorPtr;
    QJsonDocument doc = QJsonDocument::fromJson(data.toUtf8(), &errorPtr);
    if (doc.isNull()) {
        emit logReceived("Configuration file format is invalid.");
        return;
    }
    fromJson(doc.object());
    empty = false;
}

void V2RockConfig::write()
{
    emit logReceived("Writing configs...");
    QJsonObject jsonObj;
    toJson(jsonObj);
    QJsonDocument doc(jsonObj);
    QFile file(workDir + "/" + v2rock_config::main_config);
    if (!file.open(QFile::WriteOnly | QFile::Text | QFile::Truncate)) {
        emit logReceived("Error: file is not writable: " + workDir + "/" + v2rock_config::main_config);
    }
    file.write(doc.toJson());
    file.close();
    emit logReceived("Configs have been saved.");
}

void V2RockConfig::fromJson(const QJsonObject &json)
{
    if (json.contains("v2executablePath") && json["v2executablePath"].isString()) {
        v2executablePath = json["v2executablePath"].toString();
    }
    if (json.contains("subscribeUrl") && json["subscribeUrl"].isString()) {
        subscribeUrl = json["subscribeUrl"].toString();
    }
    if (json.contains("loglevel") && json["loglevel"].isString()) {
        loglevel = json["loglevel"].toString();
    }

    if (json.contains("nodeIndex")) {
        nodeIndex = json["nodeIndex"].toInt();
    }

    if (dnsConfig) {
        delete dnsConfig;
        dnsConfig = 0;
    }
    if (json.contains("dns")) {
        QJsonObject dnsObj = json["dns"].toObject();
        dnsConfig = new DNSObject;
        V2RayConfig::fromJson(*dnsConfig, dnsObj);
    }

    // Read httpConfig, delete the old one before reading
    if (httpConfig) {
        delete httpConfig;
        httpConfig = 0;
    }
    if (json.contains("httpConfig")) {
        httpConfig = new V2RayConfigInbound;
        httpConfig->fromJson(json["httpConfig"].toObject());
    }

    // Read socksConfig, delete the old one before reading
    if (socksConfig) {
        delete socksConfig;
        socksConfig = 0;
    }
    if (json.contains("socksConfig")) {
        socksConfig = new V2RayConfigInbound;
        socksConfig->fromJson(json["socksConfig"].toObject());
    }

    bypassIps.clear();
    if (json.contains("bypassIps") && json["bypassIps"].isArray()) {
        QJsonArray ips = json["bypassIps"].toArray();
        for (int i = 0; i < ips.size(); ++i) {
            if (ips[i].isString()) {
                bypassIps.append(ips[i].toString());
            }
        }
    }

    bypassDomains.clear();
    if (json.contains("bypassDomains") && json["bypassDomains"].isArray()) {
        QJsonArray domains = json["bypassDomains"].toArray();
        for (int i = 0; i < domains.size(); ++i) {
            if (domains[i].isString()) {
                bypassDomains.append(domains[i].toString());
            }
        }
    }

    qDeleteAll(nodes);
    nodes.clear();
    QJsonArray jnodes = json["nodes"].toArray();
    for (int i = 0; i < jnodes.size(); ++i) {
        QJsonObject jnode = jnodes[i].toObject();
        V2RockNode *node = new V2RockNode;
        node->read(jnode);
        nodes.append(node);
    }
    // Make sure nodeIndex is valid
    if (nodeIndex < 0 || nodeIndex >= nodes.size()) {
        nodeIndex = 0;
    }
}

void V2RockConfig::toJson(QJsonObject &json) const
{
    json["v2executablePath"] = v2executablePath;
    json["subscribeUrl"] = subscribeUrl;
    json["nodeIndex"] = nodeIndex;
    json["loglevel"] = loglevel;

    QJsonArray ipsArray;
    foreach (const QString ip, bypassIps) {
        ipsArray.append(ip);
    }
    json["bypassIps"] = ipsArray;

    QJsonArray domainsArray;
    foreach (const QString domain, bypassDomains) {
        domainsArray.append(domain);
    }
    json["bypassDomains"] = domainsArray;

    if (dnsConfig) {
        QJsonObject dnsObj;
        V2RayConfig::toJson(dnsConfig, dnsObj);
        json["dns"] = dnsObj;
    }

    if (socksConfig) {
        QJsonObject socksConfigObj;
        socksConfig->toJson(socksConfigObj);
        json["socksConfig"] = socksConfigObj;
    }

    if (httpConfig) {
        QJsonObject httpConfigObj;
        httpConfig->toJson(httpConfigObj);
        json["httpConfig"] = httpConfigObj;
    }

    QJsonArray nodesArray;
    foreach (const V2RockNode *node, nodes) {
        QJsonObject jobject;
        node->write(jobject);
        nodesArray.append(jobject);
    }
    json["nodes"] = nodesArray;
}

void V2RockConfig::print(int indentation) const
{
    const QString indent(indentation * 2, ' ');
    QTextStream(stdout) << indent << "v2executablePath:\t" << v2executablePath << "\n";
    QTextStream(stdout) << indent << "subscribeUrl:\t" << subscribeUrl << "\n";
    QTextStream(stdout) << indent << "nodeIndex:\t" << nodeIndex << "\n";
    QTextStream(stdout) << indent << "Bypass IPs:\n";
    for (const QString &ip : bypassIps) {
        QTextStream(stdout) << indent << indent << ip << "\n";
    }
    QTextStream(stdout) << indent << "Bypass Domains:\n";
    for (const QString &domain : bypassDomains) {
        QTextStream(stdout) << indent << indent << domain << "\n";
    }
    QTextStream(stdout) << indent << "Nodes:\n";
    for (const V2RockNode *node : nodes)
        node->print(2);
}

QString *V2RockConfig::toV2RayJson(QJsonObject &json)
{
    if (nodeIndex < 0 || nodeIndex >= nodes.size()) {
        emit logReceived("Error: Invalid selection " + QString::number(nodeIndex));
        return 0;
    }
    V2RockNode *node = nodes.at(nodeIndex);

    // Start to compose the V2Ray configs
    V2RayConfig v2rayConfig;
    // policy, stats, api, dns
    v2rayConfig.setPolicy(0);
    v2rayConfig.setStats(false);
    v2rayConfig.setApi(0);
    v2rayConfig.setDns(0);

    // log
    V2RayConfigLog v2rayConfigLog;
    v2rayConfigLog.setLoglevel(loglevel);
    v2rayConfigLog.setAccess("");
    v2rayConfigLog.setError("");
    v2rayConfig.setLog(v2rayConfigLog);

    // inbounds
    if (socksConfig) {
        V2RayConfigInbound *inbound = new V2RayConfigInbound(*socksConfig);
        v2rayConfig.appendInbound(inbound);
    }
    if (httpConfig) {
        V2RayConfigInbound *inbound = new V2RayConfigInbound(*httpConfig);
        v2rayConfig.appendInbound(inbound);
    }

    // outbounds
    // proxy outbound
    V2RayConfigOutbound *proxyOutbound = new V2RayConfigOutbound;
    proxyOutbound->setTag("proxy");
    proxyOutbound->setProtocol(node->getProtocol());
    if (node->getProtocol() == "vmess") {
        proxyOutbound->setVMessSettings(node->getVMessSettings());
    } else if (node->getProtocol() == "shadowsocks") {
        proxyOutbound->setShadowSocksSettings(node->getShadowSocksSettings());
    } else if (node->getProtocol() == "http") {
        proxyOutbound->setHTTPSettings(node->getHTTPSettings());
    } else if (node->getProtocol() == "mtproto") {
        proxyOutbound->setMTProtoSettings(node->getMTProtoSettings());
    } else if (node->getProtocol() == "socks") {
        proxyOutbound->setSocksSettings(node->getSocksSettings());
    } else if (node->getProtocol() == "dns") {
        proxyOutbound->setDNSSettings(node->getDNSSettings());
    }
    proxyOutbound->setStreamSettings(node->getStreamSettings());
    proxyOutbound->setMux(node->getMux());

    // direct outbound
    V2RayConfigOutbound *directOutbound = new V2RayConfigOutbound;
    directOutbound->setTag("direct");
    directOutbound->setProtocol("freedom");
    OutboundFreedomConfigurationObject *freedomSettings = new OutboundFreedomConfigurationObject;
    freedomSettings->domainStrategy = "AsIs";
    freedomSettings->redirect = "";
    freedomSettings->userLevel = 0;
    directOutbound->setFreedomSettings(freedomSettings);

    // block outbound
    V2RayConfigOutbound *blockOutbound = new V2RayConfigOutbound;
    blockOutbound->setTag("block");
    blockOutbound->setProtocol("blackhole");
    OutboundBlackholeConfigurationObject *blockSettings = new OutboundBlackholeConfigurationObject;
    blockSettings->response.type = "http";
    blockOutbound->setBlackholeSettings(blockSettings);

    v2rayConfig.clearOutbounds();
    v2rayConfig.appendOutbound(proxyOutbound);
    v2rayConfig.appendOutbound(directOutbound);
    v2rayConfig.appendOutbound(blockOutbound);

    // routing
    V2RayConfigRoute v2rayConfigRoute;
    v2rayConfigRoute.setDomainStrategy("IPIfNonMatch");

    RoutingRuleObject ipRule;
    ipRule.type = "field";
    ipRule.outboundTag = "direct";
    foreach (const QString ip, bypassIps) {
        ipRule.ip.append(ip);
    }

    RoutingRuleObject domainRule;
    domainRule.type = "field";
    domainRule.outboundTag = "direct";
    foreach (const QString domain, bypassDomains) {
        domainRule.domain.append(domain);
    }

    QList<RoutingRuleObject> rules;
    rules.append(ipRule);
    rules.append(domainRule);
    v2rayConfigRoute.setRules(rules);

    v2rayConfig.setRouting(v2rayConfigRoute);

    v2rayConfig.toJson(json);
    QJsonDocument doc(json);
    QString *configFilePath = new QString(workDir + "/" + v2rock_config::v2ray_config);
    QFile file(*configFilePath);
    if (!file.open(QFile::WriteOnly | QFile::Text | QFile::Truncate)) {
        emit logReceived("Error: file not writable: " + *configFilePath);
    }
    file.write(doc.toJson());
    file.close();
    emit logReceived("Configs have been saved.");
    return configFilePath;
}
