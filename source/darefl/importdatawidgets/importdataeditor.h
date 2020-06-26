// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef IMPORTDATAEDITOR_H
#define IMPORTDATAEDITOR_H

#include <QWidget>
#include <string>

namespace ModelView
{
class SessionItem;
class GraphCanvas;
class GraphViewportItem;
class TopItemsTreeView;
class PropertyTreeView;
} // namespace ModelView

namespace DataImportLogic
{
class ImportOutput;
class ParsedFileOutptut;
} // namespace DataImportLogic

class RealDataModel;
class QToolBar;
class QTreeView;
class QBoxLayout;
class RealDataStruct;
class DataSelectionModel;
class DataViewModel;

//! Main editor to import user data.

class ImportDataEditor : public QWidget
{
    Q_OBJECT
public:
    ImportDataEditor(RealDataModel* model, QWidget* parent = nullptr);

private:
    void setupToolBar();
    void setupViews();
    void setupLayout();

    void selectionChanged();
    void setMergeEnabled(bool enabled);

    void addDataGroup();
    void mergeDataGroups();
    void invokeImportDialog();
    std::string selectedDataGroupItem() const;
    void onImportDialogAccept(DataImportLogic::ImportOutput import_output);
    RealDataStruct convertToRealDataStruct(const std::string& path,
                                           const DataImportLogic::ParsedFileOutptut* import_output,
                                           const int column);
    void deleteItem();
    void resetAll();

private:
    QTreeView* p_tree_view{nullptr};
    RealDataModel* p_model{nullptr};
    DataViewModel* p_view_model{nullptr};
    DataSelectionModel* p_data_selection_model{nullptr};
    QToolBar* p_toolbar{nullptr};
    ModelView::PropertyTreeView* p_property_tree{nullptr};
    ModelView::GraphCanvas* p_graph_canvas{nullptr};
};

#endif // IMPORTDATAEDITOR_H
