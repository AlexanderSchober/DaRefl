// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "layerselectionmodel.h"
#include "layeritems.h"
#include <QItemSelection>
#include <mvvm/viewmodel/viewmodel.h>
#include <mvvm/viewmodel/viewmodelutils.h>

LayerSelectionModel::LayerSelectionModel(ModelView::ViewModel* view_model, QObject* parent)
    : QItemSelectionModel(view_model, parent)
{
}

//! Selects all rows corresponding to given items.

void LayerSelectionModel::selectItems(std::vector<ModelView::SessionItem*> items)
{
    QModelIndexList indexes;
    for (auto item : items)
        indexes << viewModel()->indexOfSessionItem(item->getItem(LayerItem::P_NAME));

    if (indexes.empty())
        return;

    clearSelection();

    QItemSelection selection(indexes.front(), indexes.back());
    auto flags = QItemSelectionModel::SelectCurrent | QItemSelectionModel::Rows;
    select(selection, flags);
    //    setCurrentIndex(id, flags); What to do?
}

//! Selects whole row corresponding to given item.

void LayerSelectionModel::selectItem(ModelView::SessionItem* item)
{
    selectItems({item});
}

//! Returns vector of selected layers or multilayers.
//! We assume, that there is a single line selection mode switched on, and that
//! the columns contains property items related to either LayerItem or MultiLayerItem.

std::vector<ModelView::SessionItem*> LayerSelectionModel::selectedItems() const
{
    const QModelIndexList& selection = selectedRows();
    if (selection.empty())
        return {};

    std::vector<ModelView::SessionItem*> result;
    for (const auto& index : selection)
        if (auto item = viewModel()->sessionItemFromIndex(index); item)
            result.push_back(item->parent());

    return result;
}

const ModelView::ViewModel* LayerSelectionModel::viewModel() const
{
    return static_cast<const ModelView::ViewModel*>(model());
}
