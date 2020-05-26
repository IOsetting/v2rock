#include "maindialog.h"
#include "ui_maindialog.h"

MainDialog::MainDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MainDialog)
{
    ui->setupUi(this);
    this->setWindowTitle(tr("V2Rock"));
    /* Buttons */
    QHBoxLayout *hLayout = new QHBoxLayout;

    /* Import Button */
    btnImport = new QPushButton(tr("Import"));
    connect(btnImport, SIGNAL(clicked()), this, SLOT(btnImportClickHandler()));
    hLayout->addWidget(btnImport);

    /* Test Button */
    btnTest = new QPushButton(tr("Test"));
    connect(btnTest, SIGNAL(clicked()), this, SLOT(btnTestClickHandler()));
    hLayout->addWidget(btnTest);

    /* Start Button */
    btnStart = new QPushButton(tr("Start"));
    connect(btnStart, SIGNAL(clicked()), this, SLOT(btnStartClickHandler()));
    hLayout->addWidget(btnStart);

    /* Stop Button */
    btnStop = new QPushButton(tr("Stop"));
    connect(btnStop, SIGNAL(clicked()), this, SLOT(btnStopClickHandler()));
    hLayout->addWidget(btnStop);

    /* Settings Button */
    btnSettings = new QPushButton(tr("Settings"));
    connect(btnSettings, SIGNAL(clicked()), this, SLOT(btnSettingsClickHandler()));
    hLayout->addWidget(btnSettings);

    /* Quit Button */
    btnQuit = new QPushButton(tr("Quit"));
    connect(btnQuit, SIGNAL(clicked()), qApp, SLOT(quit()));
    hLayout->addWidget(btnQuit);

    /* Tree List */
    tree = new QTreeWidget;
    tree->setColumnCount(5);
    QStringList columnNames;
    columnNames << tr("ID") << "" << tr("Protocol") << tr("Name") << tr("Host") << tr("Port");
    tree->setHeaderLabels(columnNames);
    // Remove left white spaces
    tree->setRootIsDecorated(false);
    tree->setColumnWidth(0, 30);
    tree->hideColumn(0);
    tree->setColumnWidth(1, 20);
    tree->setColumnWidth(2, 50);
    tree->setColumnWidth(3, 210);
    tree->setColumnWidth(4, 190);
    tree->setColumnWidth(5, 50);
    connect(tree, SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)), this, SLOT(treeItemDoubleClicked(QTreeWidgetItem*,int)));
    tree->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(tree, SIGNAL(customContextMenuRequested(const QPoint &)), this, SLOT(contextMenu(const QPoint &)));

    logEdit = new QPlainTextEdit();
    logEdit->setMaximumBlockCount(3000);

    QVBoxLayout *vLayout = new QVBoxLayout(this);
    vLayout->addWidget(tree, 3);
    vLayout->addLayout(hLayout);
    vLayout->addWidget(logEdit, 1);

    // Dialogs
    dialogSettings = new SettingsDialog(this);
    dialogSettings->setModal(true);
    dialogNodeEdit = new NodeEditDialog(this);
    dialogNodeEdit->setModal(true);

    // Actions
    delAction = new QAction(tr("&Delete"), this);
    connect(delAction, SIGNAL(triggered()), this, SLOT(actDelHandler()));

    editAction = new QAction(tr("&Edit"), this);
    connect(editAction, SIGNAL(triggered()), this, SLOT(actEditHandler()));

    addAction = new QAction(tr("&New"), this);
    connect(addAction, SIGNAL(triggered()), this, SLOT(actAddHandler()));

    restoreAction = new QAction(tr("&Restore"), this);
    connect(restoreAction, SIGNAL(triggered()), this, SLOT(showNormal()));

    quitAction = new QAction(tr("&Quit"), this);
    connect(quitAction, &QAction::triggered, qApp, &QCoreApplication::quit);

    networkAccessManager = new QNetworkAccessManager();
    connect(networkAccessManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(networkAccessManagerFinished(QNetworkReply*)));

    pingProcess = new PingProcess();
    connect(pingProcess, SIGNAL(logReceived(QString)), this, SLOT(appendLog(QString)));
    connect(pingProcess, SIGNAL(finished(int,QProcess::ExitStatus)), this, SLOT(processFinished(int,QProcess::ExitStatus)));

    v2rockConfig = new V2RockConfig();
    connect(v2rockConfig, SIGNAL(logReceived(QString)), this, SLOT(appendLog(QString)));
    this->v2rockConfig->read();
    if (this->v2rockConfig->isEmpty()) {
        this->v2rockConfig->init();
        this->v2rockConfig->write();
    }
    this->reloadTreeList();

    // Icons
    icons = new QList<QIcon>;
    icons->append(QIcon(":/images/v2rock.png"));
    icons->append(QIcon(":/images/v2rock-on.png"));
    icons->append(QIcon(":/images/v2rock-on-active.png"));
    icons->append(QIcon(":/images/v2rock-off.png"));

    this->createTrayIcon();
    setWindowIcon(icons->at(0));

    this->updateBtnStatus(true);
    trayIcon->show();
}

MainDialog::~MainDialog()
{
    delete ui;
    delete networkAccessManager;
    delete pingProcess;
    delete v2rockConfig;
}

void MainDialog::showEvent(QShowEvent *ev)
{
    QDialog::showEvent(ev);
    showEventHandler();
}

void MainDialog::keyPressEvent(QKeyEvent *e)
{
    if(e->key() == Qt::Key_Escape) {
        qDebug() << "Ignored key:esc";
    } else if(e->key() == Qt::Key_Q && e->modifiers() == Qt::ControlModifier) {
        QApplication::quit();
    } else {
        QDialog::keyPressEvent(e);
    }
}

void MainDialog::closeEvent(QCloseEvent *event)
{
#ifdef Q_OS_OSX
    if (!event->spontaneous() || !isVisible()) {
        return;
    }
#endif
    if (trayIcon->isVisible()) {
        hide();
        event->ignore();
    }
}

void MainDialog::showEventHandler()
{
    // Do nothing
}

void MainDialog::selectTreeItem()
{
    int selected = this->v2rockConfig->getNodeIndex();
    QList<V2RockNode *> nodes = this->v2rockConfig->getNodes();
    if (!nodes.isEmpty())
    {
        for (int i = 0; i < nodes.length(); i++)
        {
            QTreeWidgetItem *item = tree->topLevelItem(i);
            if (selected == i) {
                this->v2rockConfig->setNodeIndex(selected);
                item->setText(1, "√");
            } else {
                item->setText(1, "");
            }
        }
    }
}

void MainDialog::reloadTreeList()
{
    tree->clear();
    QList<V2RockNode *> nodes = this->v2rockConfig->getNodes();
    if (!nodes.isEmpty()) {
        for (int i = 0; i < nodes.length(); i++) {
            QString address;
            int port = 0;
            if (nodes.at(i)->getProtocol() == "vmess") {
                address = nodes.at(i)->getVMessSettings()->vnext.at(0)->address;
                port = nodes.at(i)->getVMessSettings()->vnext.at(0)->port;
            } else if (nodes.at(i)->getProtocol() == "socks") {
                address = nodes.at(i)->getSocksSettings()->servers.at(0)->address;
                port = nodes.at(i)->getSocksSettings()->servers.at(0)->port;
            } else if (nodes.at(i)->getProtocol() == "shadowsocks") {
                address = nodes.at(i)->getShadowSocksSettings()->servers.at(0)->address;
                port = nodes.at(i)->getShadowSocksSettings()->servers.at(0)->port;
            } else if (nodes.at(i)->getProtocol() == "http") {
                address = nodes.at(i)->getHTTPSettings()->servers.at(0)->address;
                port = nodes.at(i)->getHTTPSettings()->servers.at(0)->port;
            } else if (nodes.at(i)->getProtocol() == "dns") {
                address = nodes.at(i)->getDNSSettings()->address;
                if (nodes.at(i)->getDNSSettings()->port > 0) {
                    port = nodes.at(i)->getDNSSettings()->port;
                }
            }
            this->addTreeItem(QString::number(i), nodes.at(i)->getName(), nodes.at(i)->getProtocol(), address, port);
        }
        this->selectTreeItem();
    }
}

void MainDialog::addTreeItem(const QString id, const QString name, const QString protocol, const QString host, int port)
{
    QTreeWidgetItem *treeItem = new QTreeWidgetItem(tree);
    treeItem->setText(0, id);
    treeItem->setText(1, "");
    treeItem->setText(2, protocol);
    treeItem->setText(3, name);
    treeItem->setText(4, host);
    treeItem->setText(5, QString::number(port));
}

void MainDialog::treeItemDoubleClicked(QTreeWidgetItem *item, int __attribute__ ((unused)) column)
{
    int selected = item->text(0).toInt();
    this->v2rockConfig->setNodeIndex(selected);
    this->v2rockConfig->write();
    this->selectTreeItem();
}

void MainDialog::updateBtnStatus(bool stopped)
{
    btnTest->setDisabled(!stopped);
    btnStart->setDisabled(!stopped);
    btnStop->setDisabled(stopped);
    if (stopped) {
        setIcon(0);
    } else {
        setIcon(2);
    }
}

void MainDialog::processFinished(int __attribute__ ((unused)) exitCode, QProcess::ExitStatus __attribute__ ((unused)) exitStatus)
{
    this->updateBtnStatus(true);
}

void MainDialog::btnImportClickHandler()
{
    if (btnImport->text() == "Import")
    {
        this->appendLog("Import nodes from: " + v2rockConfig->getSubscribeUrl());
        networkReply = networkAccessManager->get(QNetworkRequest(QUrl(v2rockConfig->getSubscribeUrl())));
        btnImport->setText("Cancel");
        QApplication::setOverrideCursor(Qt::WaitCursor);
    }
    else
    {
        if (networkReply)
        {
            networkReply->abort();
        }
        btnImport->setText("Import");
        QApplication::restoreOverrideCursor();
    }

}

void MainDialog::btnTestClickHandler()
{
    QTreeWidgetItem *item = tree->currentItem();
    if (item)
    {
        if (pingProcess->state() == QProcess::NotRunning)
        {
            QString domain = item->text(4);
            QString command = "ping";
            QStringList args;
            args << "-w" <<  "3" <<  domain;
            pingProcess->start(command, args);
            this->updateBtnStatus(false);
        }
        else
        {
            this->appendLog("Still running");
        }
    }
    else
    {
        this->appendLog("No item has been selected");
    }
}

void MainDialog::btnStartClickHandler()
{
    if (pingProcess->state() == QProcess::NotRunning)
    {
        QJsonObject jsonObj;
        QString *v2config = v2rockConfig->toV2RayJson(jsonObj);
        if (v2config)
        {
            QString command = v2rockConfig->getV2executablePath();
            QStringList args;
            args << "-c" <<  *v2config;
            pingProcess->start(command, args);
            this->updateBtnStatus(false);
        }
    }
    else
    {
        this->appendLog("Still running");
    }
}

void MainDialog::btnStopClickHandler()
{
    pingProcess->stop();
}

void MainDialog::btnSettingsClickHandler()
{
    dialogSettings->setV2rockConfig(this->v2rockConfig);
    if (dialogSettings->exec() == QDialog::Accepted)
    {
        this->v2rockConfig->write();
    }
}

void MainDialog::actDelHandler()
{
    QAction *act = qobject_cast<QAction *>(sender());
    QVariant variant = act->data();
    QTreeWidgetItem *item = (QTreeWidgetItem *) variant.value<void *>();
    int index = item->text(0).toInt();
    QString nodeName = item->text(3);

    QMessageBox::StandardButton reply = QMessageBox::question(
                this,
                "Conformation",
                QString("Do you want to delete node %1?").arg(nodeName),
                QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        this->v2rockConfig->delNode(index);
        this->v2rockConfig->write();
        this->appendLog(QString("Node %1 has been deleted").arg(nodeName));
        this->reloadTreeList();
    }
}

void MainDialog::actEditHandler()
{
    QAction *act = qobject_cast<QAction *>(sender());
    QVariant variant = act->data();
    QTreeWidgetItem *item = (QTreeWidgetItem *) variant.value<void *>();
    qDebug() << item->text(0);
    int index = item->text(0).toInt();
    QString nodeName = item->text(3);

    dialogNodeEdit->init(v2rockConfig, index);
    if (dialogNodeEdit->exec() == QDialog::Accepted)
    {
        this->v2rockConfig->write();
        this->appendLog(QString("Node %1 has been updated").arg(nodeName));
        this->reloadTreeList();
    }
}

void MainDialog::actAddHandler()
{
    QAction *act = qobject_cast<QAction *>(sender());
    QVariant variant = act->data();
    QTreeWidgetItem *item = (QTreeWidgetItem *) variant.value<void *>();
    int index(-1);
    if (item) {
        index = item->text(0).toInt();
    }
    dialogNodeEdit->init(v2rockConfig, index, true);
    if (dialogNodeEdit->exec() == QDialog::Accepted)
    {
        this->v2rockConfig->write();
        this->reloadTreeList();
    }
}

void MainDialog::contextMenu(const QPoint &point)
{
    QMenu menu(this);
    QTreeWidgetItem *item = tree->itemAt(point);
    if (item) {
        QVariant variant = qVariantFromValue((void *)item);
        addAction->setData(variant);
        editAction->setData(variant);
        delAction->setData(variant);
        menu.addAction(addAction);
        menu.addAction(editAction);
        menu.addAction(delAction);
        menu.exec(QCursor::pos());
    } else {
        QVariant variant = qVariantFromValue((void *)0);
        addAction->setData(variant);
        menu.addAction(addAction);
        menu.exec(QCursor::pos());
    }
}

void MainDialog::networkAccessManagerFinished(QNetworkReply *reply)
{
    btnImport->setText("Import");
    QApplication::restoreOverrideCursor();
    if (reply->error()) {
        this->appendLog("Import failed: " + reply->errorString());
        return;
    }
    QByteArray response = reply->readAll();
    reply->deleteLater();
    response = QByteArray::fromBase64(response);
    QList<QByteArray> lines = response.split('\n');
    QList<V2RockNode *> nodes;
    for(const QByteArray& line : lines)
    {
        if(line.startsWith("vmess://"))
        {
            QByteArray newline = QByteArray::fromBase64(line.mid(8, -1));
            QJsonParseError errorPtr;
            QJsonDocument doc = QJsonDocument::fromJson(newline, &errorPtr);
            if (doc.isNull()) {
                qDebug() << "Parse failed";
            } else {
                XinjieConfig *xinjieConfig;
                xinjieConfig = new XinjieConfig();
                xinjieConfig->read(doc.object());
                V2RockNode *node = new V2RockNode;
                xinjieConfig->write(*node);
                nodes.append(node);
            }
        }
        else
        {
            qDebug() << "Skipped: " + line;
        }
    }
    if (nodes.isEmpty()) {
        QMessageBox::critical(
                    this,
                    tr("Error"),
                    "No valid nodes in subscription. Nothing has been imported.",
                    QMessageBox::Ok);
        return;
    }
    this->v2rockConfig->setNodes(nodes);
    QString msg = tr("%1 nodes have been imported").arg(nodes.size());
    this->appendLog(msg);
    this->v2rockConfig->write();
    this->reloadTreeList();
}

void MainDialog::appendLog(const QString &text)
{
    logEdit->appendPlainText(text);
}

void MainDialog::createTrayIcon()
{
    trayIconMenu = new QMenu(this);
    trayIconMenu->addAction(restoreAction);
    trayIconMenu->addAction(quitAction);

    trayIcon = new QSystemTrayIcon(this);
    trayIcon->setContextMenu(trayIconMenu);
}

void MainDialog::setIcon(int index)
{
    QIcon icon = icons->at(index);
    trayIcon->setIcon(icon);
}
