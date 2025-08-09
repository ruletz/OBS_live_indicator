#include <obs-module.h>
#include <obs-frontend-api.h>

#include <QDockWidget>
#include <QLabel>
#include <QHBoxLayout>
#include <QMainWindow>

OBS_DECLARE_MODULE();
OBS_MODULE_USE_DEFAULT_LOCALE("obs-live-indicator", "en-US");

static QDockWidget *g_dock = nullptr;
static QLabel *g_label = nullptr;

static void on_frontend_event(enum obs_frontend_event event, void *private_data)
{
    UNUSED_PARAMETER(private_data);

    if (!g_dock || !g_label)
        return;

    switch (event) {
        case OBS_FRONTEND_EVENT_STREAMING_STARTED:
            g_label->setText(QStringLiteral("● LIVE"));
            g_label->setStyleSheet(QStringLiteral("color: red; font-weight: bold; font-size: 14pt;"));
            g_dock->show();
            break;
        case OBS_FRONTEND_EVENT_STREAMING_STOPPED:
            g_dock->hide();
            break;
        default:
            break;
    }
}

bool obs_module_load(void)
{
    blog(LOG_INFO, "obs-live-indicator: loading plugin");

    QMainWindow *mainWindow = obs_frontend_api_get_main_window();
    if (!mainWindow) {
        blog(LOG_WARNING, "obs-live-indicator: could not find main window");
        return false;
    }

    g_dock = new QDockWidget(QStringLiteral("Live Indicator"), mainWindow);
    QWidget *container = new QWidget(g_dock);
    QHBoxLayout *layout = new QHBoxLayout(container);
    layout->setContentsMargins(6, 6, 6, 6);

    g_label = new QLabel(container);
    g_label->setText(QStringLiteral(""));
    g_label->setAlignment(Qt::AlignCenter);

    layout->addWidget(g_label);
    container->setLayout(layout);
    g_dock->setWidget(container);

    obs_frontend_add_dock(g_dock);

    g_dock->hide();

    obs_frontend_add_event_callback(on_frontend_event, nullptr);

    blog(LOG_INFO, "obs-live-indicator: loaded successfully");
    return true;
}

void obs_module_unload(void)
{
    obs_frontend_remove_event_callback(on_frontend_event, nullptr);

    if (g_dock) {
        g_dock->hide();
        delete g_dock;
        g_dock = nullptr;
    }

    blog(LOG_INFO, "obs-live-indicator: unloaded");
}