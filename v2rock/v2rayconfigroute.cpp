#include "v2rayconfigroute.h"

V2RayConfigRoute::V2RayConfigRoute()
{

}

QString V2RayConfigRoute::getDomainStrategy() const
{
    return domainStrategy;
}

void V2RayConfigRoute::setDomainStrategy(const QString &value)
{
    domainStrategy = value;
}

QList<RoutingRuleObject> V2RayConfigRoute::getRules() const
{
    return rules;
}

void V2RayConfigRoute::setRules(const QList<RoutingRuleObject> &value)
{
    rules = value;
}

QList<RoutingBalancerObject *> V2RayConfigRoute::getBalancers() const
{
    return balancers;
}

void V2RayConfigRoute::setBalancers(QList<RoutingBalancerObject *> &value)
{
    balancers = value;
}

void V2RayConfigRoute::toJson(QJsonObject &json) const
{
    json["domainStrategy"] = domainStrategy;

    QJsonArray rulesArray;
    foreach (const RoutingRuleObject rule, rules) {
        QJsonObject ruleObj;
        ruleObj["type"] = rule.type; // "field"
        if (!rule.port.isEmpty()) {
            ruleObj["port"] = rule.port;
        }
        if (!rule.network.isEmpty()) {
            ruleObj["network"] = rule.network;
        }
        if (!rule.attrs.isEmpty()) {
            ruleObj["attrs"] = rule.attrs;
        }
        if (!rule.outboundTag.isEmpty()) {
            ruleObj["outboundTag"] = rule.outboundTag;
        }
        if (!rule.balancerTag.isEmpty()) {
            ruleObj["balancerTag"] = rule.balancerTag;
        }
        if (!rule.domain.isEmpty()) {
            QJsonArray jArray;
            foreach(const QString val, rule.domain) {
                jArray.append(val);
            }
            ruleObj["domain"] = jArray;
        }
        if (!rule.ip.isEmpty()) {
            QJsonArray jArray;
            foreach(const QString val, rule.ip) {
                jArray.append(val);
            }
            ruleObj["ip"] = jArray;
        }
        if (!rule.source.isEmpty()) {
            QJsonArray jArray;
            foreach(const QString val, rule.source) {
                jArray.append(val);
            }
            ruleObj["source"] = jArray;
        }
        if (!rule.user.isEmpty()) {
            QJsonArray jArray;
            foreach(const QString val, rule.user) {
                jArray.append(val);
            }
            ruleObj["user"] = jArray;
        }
        if (!rule.inboundTag.isEmpty()) {
            QJsonArray jArray;
            foreach(const QString val, rule.inboundTag) {
                jArray.append(val);
            }
            ruleObj["inboundTag"] = jArray;
        }
        if (!rule.protocol.isEmpty()) {
            QJsonArray jArray;
            foreach(const QString val, rule.protocol) {
                jArray.append(val);
            }
            ruleObj["protocol"] = jArray;
        }
        rulesArray.append(ruleObj);
    }
    json["rules"] = rulesArray;

    if (!balancers.isEmpty()) {
        QJsonArray balancersArray;
        foreach (const RoutingBalancerObject *balancer, balancers) {
            QJsonObject balancerObj;
            balancerObj["tag"] = balancer->tag;
            QJsonArray jArray;
            foreach(const QString val, balancer->selector) {
                jArray.append(val);
            }
            balancerObj["selector"] = jArray;
            balancersArray.append(balancerObj);
        }
        json["balancers"] = balancersArray;
    }

}
