#include "DDFactory.hpp"
#include "DynamicDialog.hpp"

#include <qstandarditemmodel.h>
#include <memory>

DDFactory::DDFactory(IDynamicDialogDataProvider &dataProvider)
    : m_dynamicDialogPersistor(std::make_shared<DynamicDialogPersistor>(dataProvider)) {
}

DDFactory::~DDFactory() = default;

std::unique_ptr<DynamicDialog> DDFactory::create() const {
    auto* pModel = new QStandardItemModel(1, static_cast<int>(DynamicDialog::Widgets::Count));
    m_dynamicDialogPersistor->setModel(*pModel);
    m_dynamicDialogPersistor->load();
    return std::make_unique<DynamicDialog>(*pModel);
}

std::shared_ptr<DynamicDialogPersistor> DDFactory::persistor() const {
    return m_dynamicDialogPersistor;
}
