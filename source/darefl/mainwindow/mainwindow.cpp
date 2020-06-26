// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "mainwindow.h"
#include "applicationmodels.h"
#include "importwindow.h"
#include "mainbarwidget.h"
#include "refldockwindow.h"
#include "welcomeview.h"
#include <QCloseEvent>
#include <QCoreApplication>
#include <QFileDialog>
#include <QMenuBar>
#include <QSettings>

namespace
{
const QString main_window_group = "MainWindow";
const QString size_key = "size";
const QString pos_key = "pos";
} // namespace

MainWindow::MainWindow() : models(std::make_unique<ApplicationModels>())
{
    init_application();
    init_views();
    setCentralWidget(bar_widget);
}

MainWindow::~MainWindow() = default;

void MainWindow::closeEvent(QCloseEvent* event)
{
    if (welcome_view->canCloseProject()) {
        write_settings();
        event->accept();
    } else {
        event->ignore();
    }
}

void MainWindow::init_application()
{
    QCoreApplication::setApplicationName("quickrefl");
    QCoreApplication::setApplicationVersion("0.1");
    QCoreApplication::setOrganizationName("qt-mvvm");

    QSettings settings;
    if (settings.childGroups().contains(main_window_group)) {
        settings.beginGroup(main_window_group);
        resize(settings.value(size_key, QSize(400, 400)).toSize());
        move(settings.value(pos_key, QPoint(200, 200)).toPoint());
        settings.endGroup();
    }
}

void MainWindow::init_views()
{
    welcome_view = new WelcomeView(models.get());
    import_window = new ImportWindow(models.get());
    refl_window = new ReflDockWindow(models.get());
    bar_widget = new MainBarWidget;

    bar_widget->addWidget(welcome_view, "Project");
    bar_widget->addWidget(import_window, "Data");
    bar_widget->addWidget(refl_window, "Simulation");
    bar_widget->addWidget(new QWidget, "Fitting");
    bar_widget->addWidget(new QWidget, "Export");
    bar_widget->addWidget(new QWidget, "Settings");
    bar_widget->setCurrentIndex(1);
}

void MainWindow::write_settings()
{
    QSettings settings;
    settings.beginGroup(main_window_group);
    settings.setValue(size_key, size());
    settings.setValue(pos_key, pos());
    settings.endGroup();
}
