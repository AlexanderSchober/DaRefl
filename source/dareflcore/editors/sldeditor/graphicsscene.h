// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef GRAPHICSPROXY_GRAPHICSSCENE_H
#define GRAPHICSPROXY_GRAPHICSSCENE_H

#include <QGraphicsScene>
#include <memory>

namespace ModelView
{
class GraphCanvas;
class SceneAdapterInterface;
class GraphViewportItem;
} // namespace ModelView

class CustomPlotProxyWidget;
class RegionOfInterestItem;

//! Custom graphics scene to show QCustomPlot with additional elements on top.
class GraphicsScene : public QGraphicsScene
{
    Q_OBJECT

public:
    GraphicsScene(QObject* parent = nullptr);
    ~GraphicsScene() override;

    void setContext();
    void setItem(ModelView::GraphViewportItem* viewport_item);
    ModelView::GraphCanvas* graphCanvas() const;
    ModelView::SceneAdapterInterface* sceneAdapter() const;
    void update_size(const QSize& newSize);

private:
    void createPlotProxy(ModelView::GraphCanvas* plot_canvas);
    CustomPlotProxyWidget* plot_proxy{nullptr};
    std::unique_ptr<ModelView::SceneAdapterInterface> scene_adapter;
    ModelView::GraphCanvas* graph_canvas{nullptr};
};

#endif //  GRAPHICSPROXY_GRAPHICSSCENE_H
