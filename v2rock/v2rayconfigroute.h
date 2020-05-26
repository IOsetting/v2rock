#ifndef V2RAYCONFIGROUTE_H
#define V2RAYCONFIGROUTE_H

#include <QJsonArray>
#include <QJsonObject>
#include <QList>
#include <QString>

#include "v2raydef.h"

class V2RayConfigRoute
{
public:
    V2RayConfigRoute();
    void toJson(QJsonObject &json) const;

    QString getDomainStrategy() const;
    void setDomainStrategy(const QString &value);

    QList<RoutingRuleObject> getRules() const;
    void setRules(const QList<RoutingRuleObject> &value);

    QList<RoutingBalancerObject *> getBalancers() const;
    void setBalancers(QList<RoutingBalancerObject *> &value);

private:
    //  "AsIs" | "IPIfNonMatch" | "IPOnDemand"
    QString domainStrategy;
    QList<RoutingRuleObject> rules;
    QList<RoutingBalancerObject *> balancers;
};

#endif // V2RAYCONFIGROUTE_H
