// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "refldockwindow.h"
#include "applicationmodels.h"
#include "dockscontroller.h"
#include "layereditor.h"
#include "quicksimeditor.h"
#include "reflwidgets.h"
#include "sldeditor.h"
#include <QLabel>
#include <QToolBar>

ReflDockWindow::ReflDockWindow(ApplicationModels* models, QWidget* parent)
    : QMainWindow(parent), toolbar(new QToolBar), docks_controller(new DocksController(this)),
      models(models)
{
    setup_toolbar();
    setup_centralwidget();

    docks_controller->addWidget(0, new MaterialEditor(models->materialModel(), this),
                                Qt::TopDockWidgetArea);
    docks_controller->addWidget(1, new LayerEditor(models, this), Qt::TopDockWidgetArea);

    docks_controller->addWidget(3, new SLDEditor(models, this), Qt::BottomDockWidgetArea);

    docks_controller->addWidget(4, new QuickSimEditor(models, this), Qt::BottomDockWidgetArea);
}

ReflDockWindow::~ReflDockWindow() = default;

void ReflDockWindow::setup_toolbar()
{
    const int toolbar_icon_size = 24;
    toolbar->setIconSize(QSize(toolbar_icon_size, toolbar_icon_size));
    addToolBar(toolbar);
    //    setCentralWidget(toolbar);
}

//! Central widget as horizontal thin line.

void ReflDockWindow::setup_centralwidget()
{
    auto central_widget = new QWidget;
    central_widget->setStyleSheet("background-color:red;");
    central_widget->setMinimumHeight(2);
    central_widget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    setCentralWidget(central_widget);
}
