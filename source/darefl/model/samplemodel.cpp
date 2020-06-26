// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "samplemodel.h"
#include "layeritems.h"
#include <mvvm/model/itemcatalogue.h>

using namespace ModelView;

namespace
{
const std::string model_name{"SampleModel"};
std::unique_ptr<ItemCatalogue> CreateItemCatalogue()
{
    auto result = std::make_unique<ItemCatalogue>();
    result->registerItem<MultiLayerItem>();
    result->registerItem<LayerItem>();
    result->registerItem<RoughnessItem>();
    return result;
}
} // namespace

SampleModel::SampleModel() : SessionModel(model_name)
{
    init_model();
}

SampleModel::SampleModel(std::shared_ptr<ModelView::ItemPool> pool) : SessionModel(model_name, pool)
{
    init_model();
}

//! Populate the model with default MultiLayer with 3 layers.

void SampleModel::create_default_multilayer()
{
    auto multilayer = insertItem<MultiLayerItem>();

    auto top = insertItem<LayerItem>(multilayer);
    top->setProperty(LayerItem::P_NAME, std::string("Ambient"));
    auto middle = insertItem<LayerItem>(multilayer);
    middle->setProperty(LayerItem::P_NAME, std::string("Middle"));
    auto substrate = insertItem<LayerItem>(multilayer);
    substrate->setProperty(LayerItem::P_NAME, std::string("Substrate"));

    middle->setProperty(LayerItem::P_THICKNESS, 42.0);
}

void SampleModel::init_model()
{
    setItemCatalogue(CreateItemCatalogue());
}
