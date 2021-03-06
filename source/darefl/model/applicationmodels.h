// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef DAREFL_MODEL_APPLICATIONMODELS_H
#define DAREFL_MODEL_APPLICATIONMODELS_H

#include <memory>
#include <mvvm/interfaces/applicationmodelsinterface.h>

namespace ModelView
{
class SessionModel;
}

class MaterialModel;
class SampleModel;
class SLDElementModel;
class SLDElementController;
class JobModel;
class RealDataModel;

//!  Main class to holds all models of GUI session.

class ApplicationModels : public ModelView::ApplicationModelsInterface
{
public:
    ApplicationModels();
    ~ApplicationModels();

    MaterialModel* materialModel();
    SampleModel* sampleModel();
    SLDElementModel* sldViewModel();
    JobModel* jobModel();
    RealDataModel* realDataModel();

    std::vector<ModelView::SessionModel*> persistent_models() const override;

private:
    struct ApplicationModelsImpl;
    std::unique_ptr<ApplicationModelsImpl> p_impl;
};

#endif // DAREFL_MODEL_APPLICATIONMODELS_H
