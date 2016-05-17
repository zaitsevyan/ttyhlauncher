#ifndef LAUNCHERWINDOW_H
#define LAUNCHERWINDOW_H

#include <QMainWindow>
#include <QActionGroup>

#include "settings.h"
#include "logger.h"
#include "datafetcher.h"
#include "gamerunner.h"

namespace Ui {
class LauncherWindow;
}

class LauncherWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit LauncherWindow(QWidget *parent = 0);
    ~LauncherWindow();
    void closeEvent (QCloseEvent* event);
    void keyPressEvent(QKeyEvent* pe);

signals:
    void windowClosed();

private slots:
    void appendToLog(const QString& text);
    QString escapeString(const QString& string);

    void showSettingsDialog();
    void showSkinLoadDialog();
    void showUpdateManagerDialog();
    void showFeedBackDialog();
    void showAboutDialog();

    void offlineModeChanged();
    void hideWindowModeChanged();
    void fetchNewsModeChanged();

    void newsFetched(bool result);

    void freezeInterface();
    void unfreezeInterface();

    void playButtonClicked();
    void gameRunnerError(const QString& message);
    void gameRunnerNeedUpdate(const QString& message);
    void gameRunnerStarted();
    void gameRunnerFinished(int exitCode);

    void showError(const QString & message);

private:
    Ui::LauncherWindow *ui;
    QActionGroup *newsGroup;

    Settings* settings;
    Logger* logger;

    DataFetcher newsFetcher;
    GameRunner* gameRunner;

    void log(const QString& line);

    void appendLineToLog(const QString& line);

    void storeParameters();

    void showUpdateDialog(const QString message);
};

#endif // LAUNCHERWINDOW_H
