// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef DAREFL_SLDEDITOR_SLDEDITOR_H
#define DAREFL_SLDEDITOR_SLDEDITOR_H

class SLDEditorActions;
class SLDEditorToolBar;
class SLDViewWidget;
class ApplicationModels;

#include <QWidget>

//! The SLD editor QWidget
class SLDEditor : public QWidget
{

public:
    SLDEditor(ApplicationModels* apps_model, QWidget* parent = nullptr);
    ~SLDEditor();

    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;

private:
    SLDEditorActions* p_editor_actions{nullptr};
    SLDEditorToolBar* p_editor_tollbar{nullptr};
    SLDViewWidget* p_view_widget{nullptr};
};

#endif // DAREFL_SLDEDITOR_SLDEDITOR_H
