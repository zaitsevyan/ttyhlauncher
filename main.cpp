#include "launcherwindow.h"

#include "logger.h"
#include "settings.h"

#include <QApplication>
#include <QSplashScreen>
#include <QBitmap>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator t;
    QDate today = QDate::currentDate();
    if ( today.month() == 4 && today.day() == 1 )
    {
        t.load(":/translations/koi7.qm");
    }
    else
    {
        t.load(":/translations/ru.qm");
    }
    QApplication::installTranslator(&t);

    Settings::instance();
    Logger::logger();

    QPixmap logo(":/resources/logo.png");
    QSplashScreen *splash =
            new QSplashScreen(logo, Qt::FramelessWindowHint | Qt::SplashScreen);

    splash->setMask( logo.mask() );

    splash->show();
    Settings::instance()->updateLocalData();
    splash->close();

    delete splash;

    LauncherWindow w;
    w.show();

    return a.exec();
}
