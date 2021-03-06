// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <darefl/sldeditor/layerelementitem.h>
#include <darefl/sldeditor/sldeditoractions.h>
#include <darefl/sldeditor/sldelementmodel.h>

#include <QDebug>
#include <mvvm/model/modelutils.h>
#include <mvvm/viewmodel/viewmodel.h>

using namespace ModelView;

struct SLDEditorActions::SLDEditorActionsImpl {
    SLDElementModel* sld_element_model{nullptr};
    SLDEditorActionsImpl(SLDElementModel* sld_element_model) : sld_element_model(sld_element_model)
    {
    }
};

SLDEditorActions::SLDEditorActions(SLDElementModel* sld_element_model, QObject* parent)
    : QObject(parent), p_impl(std::make_unique<SLDEditorActionsImpl>(sld_element_model))
{
}

SLDEditorActions::~SLDEditorActions() = default;
