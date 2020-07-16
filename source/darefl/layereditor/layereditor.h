// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef DAREFL_LAYEREDITOR_LAYEREDITOR_H
#define DAREFL_LAYEREDITOR_LAYEREDITOR_H

#include <QWidget>

class ApplicationModels;
class LayerEditorActions;
class LayerEditorToolBar;
class LayerEditorWidget;

namespace ModelView
{
class AbstractViewModel;
}

//! Layer editor.

class LayerEditor : public QWidget
{
    Q_OBJECT
public:
    LayerEditor(QWidget* parent = nullptr);
    ~LayerEditor();

    void setModels(ApplicationModels* models);

    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;
    void selectionChanged();

private:
    LayerEditorActions* p_actions{nullptr};
    LayerEditorToolBar* p_toolbar{nullptr};
    LayerEditorWidget* p_editor_widget{nullptr};
};

#endif // DAREFL_LAYEREDITOR_LAYEREDITOR_H