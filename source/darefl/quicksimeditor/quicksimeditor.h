// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef DAREFL_QUICKSIMEDITOR_QUICKSIMEDITOR_H
#define DAREFL_QUICKSIMEDITOR_QUICKSIMEDITOR_H

#include <QWidget>
#include <memory>

namespace ModelView
{
class GraphCanvas;
}

class JobModel;
class ApplicationModels;
class QuickSimController;
class QuickSimEditorToolBar;

//! Quick reflectivity simulations.

class QuickSimEditor : public QWidget
{
    Q_OBJECT
public:
    QuickSimEditor(ApplicationModels* app_models, QWidget* parent = nullptr);
    ~QuickSimEditor();

    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;

private:
    void setup_toolbar_connections();
    void setup_controller_connections();

    ApplicationModels* app_models{nullptr};
    QuickSimController* sim_controller{nullptr};
    QuickSimEditorToolBar* toolbar{nullptr};
    ModelView::GraphCanvas* spec_canvas{nullptr};
};

#endif // DAREFL_QUICKSIMEDITOR_QUICKSIMEDITOR_H
