// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "sldeditor.h"

#include "applicationmodels.h"
#include "graphicsscene.h"
#include "sldeditoractions.h"
#include "sldeditortoolbar.h"
#include "sldviewwidget.h"

#include "styleutils.h"
#include <QVBoxLayout>
#include <mvvm/plotting/graphcanvas.h>

//! The constructor
SLDEditor::SLDEditor(ApplicationModels* apps_models, QWidget* parent)
    : QWidget(parent), p_view_widget(new SLDViewWidget(apps_models, this)),
      p_editor_actions(new SLDEditorActions(apps_models->sldViewModel(), this)),
      p_editor_tollbar(new SLDEditorToolBar(p_editor_actions))
{
    setWindowTitle("SLD editor");

    auto layout = new QVBoxLayout;
    layout->addWidget(p_editor_tollbar);
    layout->addWidget(p_view_widget);
    setLayout(layout);

    connect(p_editor_tollbar, &SLDEditorToolBar::resetViewport, [this]() {
        GraphicsScene* scene_item = dynamic_cast<GraphicsScene*>(p_view_widget->scene());
        if (!scene_item)
            return;
        scene_item->graphCanvas()->update_viewport();
    });
}

//! The destructor
SLDEditor::~SLDEditor() = default;

QSize SLDEditor::sizeHint() const
{
    return StyleUtils::DockSizeHint();
}

QSize SLDEditor::minimumSizeHint() const
{
    return StyleUtils::DockMinimumSizeHint();
}
