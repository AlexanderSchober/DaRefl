// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "datasetitem.h"
#include "datasetconvenience.h"
#include "item_constants.h"

#include <mvvm/standarditems/axisitems.h>
#include <mvvm/standarditems/data1ditem.h>
#include <mvvm/standarditems/graphitem.h>
#include <vector>

using namespace ModelView;

// ----------------------------------------------------------------
DataGroupItem::DataGroupItem() : GraphViewportItem(::Constants::DataGroupItemType) {}

// ----------------------------------------------------------------
DataCollectionItem::DataCollectionItem() : CompoundItem(::Constants::DataCollectionItemType)
{
    const std::string data_group_tag = "data_groups";
    registerTag(TagInfo::universalTag(data_group_tag));
}

//! Check if a data group tag is present and return it if it is
DataGroupItem* DataCollectionItem::getDataGroup(const std::string tag) const
{
    std::vector<SessionItem*> items = getItems(data_group_tag);
    auto found = std::find_if(items.begin(), items.end(),
                              [&tag](const SessionItem* item) { return item->isTag(tag); });

    if (found == items.end())
        return nullptr;
    else
        return dynamic_cast<DataGroupItem*>(*found);
}

// ----------------------------------------------------------------
RealDataContainer::RealDataContainer() : ContainerItem() {}
