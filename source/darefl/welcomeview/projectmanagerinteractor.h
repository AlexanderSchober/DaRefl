// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef PROJECTMANAGERINTERACTOR_H
#define PROJECTMANAGERINTERACTOR_H

#include <string>

namespace ModelView
{
    enum class SaveChangesAnswer;
}

class QWidget;
class WelcomeViewSettings;

//! Provide save/discard/cancel and similar dialogs on user request.
//! Intended to work in pair with ProjectManagerDecorator.

// FIXME consider turning into interface class and switch ProjectManagerDecorator to it
// instead of all callbacks.

class ProjectManagerInteractor
{
public:
    ProjectManagerInteractor(QWidget* parent, WelcomeViewSettings* settings);

    std::string onSelectDirRequest();

    std::string onCreateDirRequest();

    ModelView::SaveChangesAnswer onSaveChangesRequest();

private:
    std::string selectDir() const;

    QWidget* m_parent{nullptr};
    WelcomeViewSettings* m_settings{nullptr};
};

#endif // PROJECTMANAGERINTERACTOR_H
