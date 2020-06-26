// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef WELCOMEVIEW_H
#define WELCOMEVIEW_H

#include <QWidget>
#include <memory>

namespace ModelView
{
class ProjectManagerInterface;
}

class ApplicationModels;
class RecentProjectWidget;
class OpenProjectWidget;
class WelcomeViewSettings;
class ProjectManagerInteractor;

//! Welcome view. Main widget on first tab of MainWindow.

class WelcomeView : public QWidget
{
    Q_OBJECT
public:
    WelcomeView(ApplicationModels* models, QWidget* parent = nullptr);
    ~WelcomeView();

    bool canCloseProject() const;

public slots:
    void onCreateNewProject();
    void onOpenExistingProject(const QString &dirname = {});
    void onSaveCurrentProject();
    void onSaveProjectAs();

private:
    void init_project_manager();
    void setup_connections();
    void update_current_project_name();
    void update_recent_project_names();

    ApplicationModels* m_models{nullptr};
    std::unique_ptr<ModelView::ProjectManagerInterface> m_project_manager;
    RecentProjectWidget* m_recent_project_widget{nullptr};
    OpenProjectWidget* m_open_project_widget{nullptr};
    std::unique_ptr<WelcomeViewSettings> m_settings;
    std::unique_ptr<ProjectManagerInteractor> m_interactor;
};

#endif // WELCOMEVIEW_H
