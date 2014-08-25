#include <QtCore>
#include <QObject>
#include <QStandardPaths>
#include <QSysInfo>

#include "settings.h"

/*
 * Versions feature plan:
 *     - 0.1 -- implemented settings;
 *     - 0.2 -- implemented interaction with master-server;
 *     - 0.3 -- implemented interaction with update-server;
 *     - 0.4 -- implemented game launch;
 *     - 0.5 -- implemented logger, some bugfixes, code cleanups;
 *     - 0.6 -- ????
 *     - 1.0 -- PROFIT^WRELEASE!
*/
const QString Settings::launcherVerion = "0.5";

// Master-server links
const QString Settings::authUrl          = "http://master.ttyh.ru/index.php?act=login";
const QString Settings::changePasswrdUrl = "http://master.ttyh.ru/index.php?act=chpass";
const QString Settings::skinUploadUrl    = "http://master.ttyh.ru/index.php?act=setskin";
const QString Settings::feedbackUrl      = "http://master.ttyh.ru/index.php?act=feedback";

// Update server links
const QString Settings::getVersionsUrl   = "http://update.ttyh.ru/index.php?act=versions"; // + &client=<client_id>
const QString Settings::getFilelistUrl   = "http://update.ttyh.ru/index.php?act=filelist"; // + &client=<client_id>&version=<version_id>
const QString Settings::updateUrl        = "http://update.ttyh.ru/data/"; // + <client_id>/<version_id>/<file_name>

Settings* Settings::myInstance = 0;
Settings* Settings::instance() {
    if (myInstance == 0) myInstance = new Settings();
    return myInstance;
}

Settings::Settings() : QObject()
{
    dataPath = QStandardPaths::writableLocation(QStandardPaths::DataLocation);

    QString setPath = QStandardPaths::writableLocation(QStandardPaths::ConfigLocation);
    settings = new QSettings(setPath + "/ttyhlauncher/config.ini", QSettings::IniFormat);

    clientStrIDs = new QStringList();
    clientNames = new QStringList();

    appendClient("classic", "Классический клиент");
    appendClient("industrial", "Индустриальный клиент");
}

void Settings::appendClient(QString strid, QString name) {
    clientStrIDs->append(strid);
    clientNames->append(name);
}

QStringList Settings::getClientsNames() { return *clientNames; }
int Settings::getClientId(QString name) { return clientNames->indexOf(name); }
int Settings::strIDtoID(QString strid) { return clientStrIDs->indexOf(strid); }
QString Settings::getClientName(int id) { return clientNames->at(id); }
QString Settings::getClientStrId(int id) { return clientStrIDs->at(id); }

int Settings::loadActiveClientId() {
    QString strid = settings->value("launcher/client", clientStrIDs->at(0)).toString();
    return strIDtoID(strid);
}

void Settings::saveActiveClientId(int id) {
    QString client = getClientStrId(id);
    settings->setValue("launcher/client", client);
}

QString Settings::loadLogin() { return settings->value("launcher/login", "Player").toString(); }
void Settings::saveLogin(QString login) { settings->setValue("launcher/login", login); }

bool Settings::loadPassStore() { return settings->value("launcher/save_password", false).toBool(); }
void Settings::savePassStore(bool state) { settings->setValue("launcher/save_password", state); }

// Password stored as base64-encoded string
QString Settings::loadPassword() {
    QString encodedPass = settings->value("launcher/password", "").toString();
    QByteArray ba; ba.append(encodedPass);
    return QByteArray::fromBase64(ba);
}

void Settings::savePassword(QString password) {
    QByteArray ba; ba.append(password);
    settings->setValue("launcher/password", QString(ba.toBase64()));
}

QString Settings::makeMinecraftUuid() {
    QString def = QString(QUuid::createUuid().toByteArray().toBase64());
    QString id = settings->value("launcher/revision", def).toString();
    settings->setValue("launcher/revision", id);
    QByteArray encoded; encoded.append(id);
    return QString(QByteArray::fromBase64(encoded));
}

QRect Settings::loadWindowGeometry() {return qvariant_cast<QRect>(settings->value("launcher/window_geometry", QRect(-1, -1, 600, 400))); }
void Settings::saveWindowGeometry(QRect geom) { settings->setValue("launcher/window_geometry", geom); }

bool Settings::loadMaximizedState() {return settings->value("launcher/window_maximized", false).toBool();}
void Settings::saveMaximizedState(bool state) { settings->setValue("launcher/window_maximized", state); }

// Client settings
QString Settings::loadClientVersion() {
    int cid = loadActiveClientId();
    return settings->value("client-" + getClientStrId(cid) + "/version", "latest").toString();
}

void Settings::saveClientVersion(QString strid) {
    int cid = loadActiveClientId();
    settings->setValue("client-" + getClientStrId(cid) + "/version", strid);
}

bool Settings::loadClientJavaState() {
    int cid = loadActiveClientId();
    return settings->value("client-" + getClientStrId(cid) + "/custom_java", false).toBool();
}

void Settings::saveClientJavaState(bool state) {
    int cid = loadActiveClientId();
    settings->setValue("client-" + getClientStrId(cid) + "/custom_java", state);
}

QString Settings::loadClientJava() {
    int cid = loadActiveClientId();
    return settings->value("client-" + getClientStrId(cid) + "/java", "").toString();
}

void Settings::saveClientJava(QString java) {
    int cid = loadActiveClientId();
    settings->setValue("client-" + getClientStrId(cid) + "/java", java);
}

bool Settings::loadClientJavaArgsState() {
    int cid = loadActiveClientId();
    return settings->value("client-" + getClientStrId(cid) + "/add_args", false).toBool();
}

void Settings::saveClientJavaArgsState(bool state) {
    int cid = loadActiveClientId();
    settings->setValue("client-" + getClientStrId(cid) + "/add_args", state);
}

QString Settings::loadClientJavaArgs() {
    int cid = loadActiveClientId();
    return settings->value("client-" + getClientStrId(cid) + "/args", "").toString();
}

void Settings::saveClientJavaArgs(QString args) {
    int cid = loadActiveClientId();
    settings->setValue("client-" + getClientStrId(cid) + "/args", args);
}

// Directories
QString Settings::getBaseDir() {
    return dataPath;
}

QString Settings::getClientDir() {
    return dataPath + "/client_" + getClientStrId(loadActiveClientId());
}

QString Settings::getAssetsDir() {
    return dataPath + "/assets";
}

QString Settings::getLibsDir() {
    return dataPath + "/libraries";
}

QString Settings::getVersionsDir() {
    return getClientDir() + "/versions";
}

QString Settings::getNativesDir() {
    return getClientDir() + "/natives";
}

// Platform information
QString Settings::getOsName() {
#ifdef Q_OS_WIN
    return "windows";
#endif
#ifdef Q_OS_OSX
    return "osx";
#endif
#ifdef Q_OS_LINUX
    return "linux";
#endif
}

QString Settings::getOsVersion() {
#ifdef Q_OS_WIN
    switch (QSysInfo::WindowsVersion) {
        case QSysInfo::WV_95:           return "95, OMFG!";
        case QSysInfo::WV_98:           return "98";
        case QSysInfo::WV_Me:           return "Me";
        case QSysInfo::WV_NT:           return "NT";
        case QSysInfo::WV_2000:         return "2000";
        case QSysInfo::WV_XP:           return "XP";
        case QSysInfo::WV_2003:         return "2003";
        case QSysInfo::WV_VISTA:        return "Vista";
        case QSysInfo::WV_WINDOWS7:     return "7";
        case QSysInfo::WV_WINDOWS8:     return "8";
        case QSysInfo::WV_WINDOWS8_1:   return "8.1";
        default:                        return "unknown";
    }
#endif

#ifdef Q_OS_OSX
    switch (QSysInfo::MacVersion) {
        case QSysInfo::MV_10_6:     return "10.6";
        case QSysInfo::MV_10_7:     return "10.7";
        case QSysInfo::MV_10_8:     return "10.8";
        case QSysInfo::MV_10_9:     return "10.9";
        default:                    return "unknown";
    }
#endif

#ifdef Q_OS_LINUX
    QProcess* lsbRelease = new QProcess(this);
    lsbRelease->start("lsb_release", QStringList() << "-d");

    if (!lsbRelease->waitForStarted())  return "NO_LSB_DISTRO";
    if (!lsbRelease->waitForFinished()) return "ERROR";

    // Get value from output: "Description:\t<value>\n"
    QString releaseInfo = lsbRelease->readLine().split('\t').last();
    releaseInfo = releaseInfo.split('\n').first();

    delete lsbRelease;
    return releaseInfo;
#endif
}

QString Settings::getWordSize() {
    return QString::number(QSysInfo::WordSize);
}
