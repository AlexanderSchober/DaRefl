// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef DAREFL_WELCOMEVIEW_OPENPROJECTWIDGET_H
#define DAREFL_WELCOMEVIEW_OPENPROJECTWIDGET_H

#include <QWidget>
#include <memory>

class QBoxLayout;
class QPushButton;

//! Widget with buttons to create new project or open existing one.
//! Occupies right part of WelcomeView.

class OpenProjectWidget : public QWidget
{
    Q_OBJECT
public:
    explicit OpenProjectWidget(QWidget* parent = nullptr);

    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;

signals:
    void createNewProjectRequest();
    void openExistingProjectRequest();
    void saveProjectRequest();
    void saveProjectAsRequest();

private:
    QBoxLayout* createButtonLayout();
    QBoxLayout* createTempButtonLayout();

    QPushButton* new_project_button{nullptr};
    QPushButton* open_project_button{nullptr};
    QPushButton* save_project_button{nullptr};
    QPushButton* saveas_project_button{nullptr};
};

#endif // DAREFL_WELCOMEVIEW_OPENPROJECTWIDGET_H
