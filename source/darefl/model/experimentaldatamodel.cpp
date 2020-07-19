// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <darefl/model/realdata_types.h>
#include <darefl/model/experimentaldataitems.h>
#include <darefl/model/experimentaldatamodel.h>

#include <mvvm/model/itemcatalogue.h>
#include <mvvm/model/modelutils.h>
#include <mvvm/standarditems/axisitems.h>
#include <mvvm/standarditems/containeritem.h>
#include <mvvm/standarditems/data1ditem.h>
#include <mvvm/standarditems/graphitem.h>
#include <mvvm/standarditems/graphviewportitem.h>

#include <algorithm>
#include <cmath>

using namespace ModelView;

namespace
{

std::unique_ptr<ItemCatalogue> CreateItemCatalogue()
{
    auto result = std::make_unique<ModelView::ItemCatalogue>();
    result->registerItem<CanvasItem>();
    result->registerItem<CanvasContainerItem>();
    return result;
}

} // namespace

ExperimentalDataModel::ExperimentalDataModel() : SessionModel("RealDataModel")
{
    setItemCatalogue(CreateItemCatalogue());
    insertDataContainer();
    insertDataCollection();
}

//! Create the data container item
ExperimentalDataContainerItem* ExperimentalDataModel::insertDataContainer()
{
    auto data_container_item = insertItem<ExperimentalDataContainerItem>(rootItem());
    return data_container_item;
}

//! Get the data container of the model
ExperimentalDataContainerItem* ExperimentalDataModel::dataContainer() const
{
    for (const auto item : rootItem()->children()) {
        if (dynamic_cast<ExperimentalDataContainerItem*>(item))
            return dynamic_cast<ExperimentalDataContainerItem*>(item);
    }

    return nullptr;
}

//! Create a new data node
CanvasContainerItem* ExperimentalDataModel::insertDataCollection()
{
    auto data_set_item = insertItem<CanvasContainerItem>(rootItem());
    return data_set_item;
}

//! Add a type unit sessionitem to the children
CanvasItem* ExperimentalDataModel::insertDataGroup(CanvasContainerItem* data_node)
{
    auto item = insertItem<CanvasItem>(data_node);
    return item;
}

//! This will manage the group item tagret and then insert the data.
//! The created group is then returned to allow insertion within the same
CanvasItem* ExperimentalDataModel::addDataToCollection(RealDataStruct data_struct,
                                                  CanvasContainerItem* data_node,
                                                  CanvasItem* data_group)
{
    auto group_item = data_group;
    if (!group_item) {
        group_item = insertDataGroup(data_node);
    }

    if (!data_struct.data.empty())
        addDataToGroup(group_item, data_struct);

    return group_item;
}

//! Insert the data into the group item
void ExperimentalDataModel::removeAllDataFromCollection(CanvasContainerItem* data_node)
{
    for (auto item : data_node->children()) {
        removeDataFromCollection({item});
    }
}

//! Insert the data into the group item
void ExperimentalDataModel::removeDataFromCollection(std::vector<ModelView::SessionItem*> item_to_remove)
{
    for (auto item : item_to_remove) {
        if (auto group_item = dynamic_cast<CanvasItem*>(item)) {
            for (auto temp_item : group_item->children()) {
                if (auto sub_item = dynamic_cast<GraphItem*>(temp_item))
                    removeDataFromGroup(sub_item);
            }
            removeItem(group_item->parent(), group_item->tagRow());
        } else if (auto subitem = dynamic_cast<GraphItem*>(item)) {
            removeDataFromGroup(subitem);
        }
    }
}

//! Insert the data into the group item
std::vector<std::pair<std::string, std::string>> ExperimentalDataModel::dataGroupNames() const
{
    auto items = Utils::FindItems<CanvasItem>(this);
    std::vector<std::pair<std::string, std::string>> output;
    for (auto item : items) {
        output.push_back(
            std::make_pair<std::string, std::string>(item->displayName(), item->identifier()));
    }
    return output;
}

//! Insert the data into the group item
void ExperimentalDataModel::addDataToGroup(CanvasItem* data_group, RealDataStruct& data_struct)
{
    if (data_struct.axis.empty()) {
        data_struct.axis.resize(data_struct.data.size());
        std::iota(data_struct.axis.begin(), data_struct.axis.end(), 0);
    }

    std::vector<double> axis_vec;
    std::vector<double> data_vec;

    for (int i = 0; i < data_struct.data.size(); ++i) {
        if (!std::isnan(data_struct.axis.at(i)) && !std::isnan(data_struct.data.at(i))) {
            axis_vec.push_back(data_struct.axis.at(i));
            data_vec.push_back(data_struct.data.at(i));
        }
    }

    auto data = insertItem<Data1DItem>(dataContainer(), {dataContainer()->defaultTag(), -1});
    data->setAxis(PointwiseAxisItem::create(axis_vec));
    data->setContent(data_vec);

    auto graph = insertItem<GraphItem>(data_group, {GraphViewportItem::T_ITEMS, -1});
    graph->setDisplayName(data_struct.data_name);
    graph->setData(data_struct.name);
    graph->setDataItem(data);
    // TODO hack to refresh the ViewDataItem display (please fix)
    moveItem(graph, graph->parent(), graph->tagRow());
}

//! Remove Graph and data items from the model
void ExperimentalDataModel::removeDataFromGroup(GraphItem* item)
{
    removeItem(item->dataItem()->parent(), item->dataItem()->tagRow());
    removeItem(item->parent(), item->tagRow());
}

//! check if all items are DataGroupItems, if yes return true
bool ExperimentalDataModel::checkAllGroup(std::vector<ModelView::SessionItem*>& items) const
{
    for (const auto item : items) {
        if (!dynamic_cast<CanvasItem*>(item))
            return false;
    }

    return true;
}

//! check if all items are DataGroupItems, if yes return true
ModelView::GraphViewportItem*
ExperimentalDataModel::checkAllGraph(std::vector<ModelView::SessionItem*>& items) const
{
    ModelView::GraphViewportItem* parent{nullptr};

    for (const auto item : items) {
        if (!dynamic_cast<ModelView::GraphItem*>(item))
            return nullptr;
        if (!parent) {
            parent = dynamic_cast<ModelView::GraphViewportItem*>(item->parent());
        } else {
            if (parent != dynamic_cast<ModelView::GraphViewportItem*>(item->parent()))
                return nullptr;
        }
    }

    return parent;
}

//! Check if an item should be editable or not
bool ExperimentalDataModel::itemEditable(ModelView::SessionItem* item) const
{
    if (dynamic_cast<GraphItem*>(item))
        return true;
    if (dynamic_cast<CanvasItem*>(item))
        return true;
    if (dynamic_cast<CanvasContainerItem*>(item))
        return true;
    return false;
}

//! Check if an item should be allowed to be dragged
bool ExperimentalDataModel::dragEnabled(ModelView::SessionItem* item) const
{
    if (dynamic_cast<GraphItem*>(item))
        return true;
    if (dynamic_cast<CanvasItem*>(item))
        return true;
    return false;
}

//! Check if an item should be allowed to be receive drops
bool ExperimentalDataModel::dropEnabled(ModelView::SessionItem* item) const
{
    if (dynamic_cast<CanvasItem*>(item))
        return true;
    return false;
}

//! process to the move of an item
bool ExperimentalDataModel::dragDropItem(ModelView::SessionItem* item, ModelView::SessionItem* target,
                                 int row)
{
    if (dynamic_cast<GraphItem*>(item) && dynamic_cast<CanvasItem*>(target)
        && target != item->parent()) {
        moveItem(dynamic_cast<GraphItem*>(item), dynamic_cast<CanvasItem*>(target),
                 {dynamic_cast<CanvasItem*>(target)->defaultTag(), row});
        return true;
    }

    if (dynamic_cast<CanvasItem*>(item) && dynamic_cast<CanvasItem*>(target)
        && target != item->parent()) {
        mergeItems(std::vector<ModelView::SessionItem*>{target, item});
        return true;
    }

    return false;
}

//! Merges all items present into the first of the vector
bool ExperimentalDataModel::mergeItems(std::vector<ModelView::SessionItem*> items)
{
    if (items.size() < 1)
        return false;

    for (int i = 1; i < items.size(); ++i) {
        for (auto child : items.at(i)->children()) {
            if (child->parent()->isSinglePropertyTag(child->tag()))
                continue;
            moveItem(child, items.at(0), {child->tag(), -1});
        }
        removeItem(items.at(i)->parent(), items.at(i)->tagRow());
    }

    return true;
}
