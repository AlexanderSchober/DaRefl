// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "layerviewmodelcontroller.h"
#include "layeritems.h"
#include <mvvm/viewmodel/rowstrategyinterface.h>
#include <mvvm/viewmodel/standardchildrenstrategies.h>
#include <mvvm/viewmodel/standardviewitems.h>
#include <mvvm/viewmodel/viewmodel.h>

using namespace ModelView;

//! Custom strategy to form table rows for nested multilayers and layers.

class CustomLayerRowStrategy : public RowStrategyInterface
{
public:
    QStringList horizontalHeaderLabels() const
    {
        return QStringList() << "Name"
                             << "Nr."
                             << "Material"
                             << "Thickness"
                             << "Sigma";
    }

    std::vector<std::unique_ptr<ViewItem>> constructRefRow(SessionItem* item)
    {
        std::vector<std::unique_ptr<ViewItem>> result;

        // multilayer row contains its name, repetion and placeholders (instead of material and
        // thickness)
        if (auto multilayer = dynamic_cast<MultiLayerItem*>(item)) {
            result.emplace_back(
                std::make_unique<ViewDataItem>(multilayer->getItem(LayerItem::P_NAME)));
            //            result.push_back(new ViewLabelItem(multilayer));
            result.emplace_back(std::make_unique<ViewDataItem>(
                multilayer->getItem(MultiLayerItem::P_NREPETITIONS)));
            result.emplace_back(std::make_unique<ViewEmptyItem>()); // instead of P_MATERIAL
            result.emplace_back(std::make_unique<ViewEmptyItem>()); // instead of P_THICKNESS
            result.emplace_back(std::make_unique<ViewEmptyItem>()); // instead of P_ROUGHNESS
        }

        // layer row contains its name, placeholder for repetition, layer material and thickness
        if (auto layer = dynamic_cast<LayerItem*>(item)) {
            result.emplace_back(std::make_unique<ViewDataItem>(layer->getItem(LayerItem::P_NAME)));
            //            result.push_back(new ViewLabelItem(layer));
            result.emplace_back(std::make_unique<ViewEmptyItem>()); // instead of P_NREPETITIONS
            result.emplace_back(
                std::make_unique<ViewDataItem>(layer->getItem(LayerItem::P_MATERIAL)));
            result.emplace_back(
                std::make_unique<ViewDataItem>(layer->getItem(LayerItem::P_THICKNESS)));
            result.emplace_back(std::make_unique<ViewDataItem>(
                layer->getItem(LayerItem::P_ROUGHNESS)->getItem(RoughnessItem::P_SIGMA)));
        }

        return result;
    }
};

LayerViewModelController::LayerViewModelController(SessionModel* model, ViewModel* view_model)
    : ViewModelController(model, view_model)
{
    setRowStrategy(std::make_unique<CustomLayerRowStrategy>());
    setChildrenStrategy(std::make_unique<TopItemsStrategy>());
}
