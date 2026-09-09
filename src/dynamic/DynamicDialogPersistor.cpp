#include "DynamicDialogPersistor.hpp"
#include "DynamicDialog.hpp"

DynamicDialogPersistor::DynamicDialogPersistor(
    IDynamicDialogDataProvider &dataProvider,
    QList<Operation> operations)
    : m_dataProvider(dataProvider),
      m_operations(std::move(operations)) {
}

void DynamicDialogPersistor::load()
{
    const auto data = m_dataProvider.getData();
    QStringList operationNames;
    QVariantList widgets;
    for (const auto &operation : m_operations) {
        operationNames.append(operation.name);
        widgets.append(QVariant::fromValue(operation.widget));
    }

    m_model->setData(index(DynamicDialog::Widgets::OperationSelection), QVariant::fromValue(data.operation), static_cast<int>(Qt::DisplayRole));
    m_model->setData(index(DynamicDialog::Widgets::OperationSelection), QVariant::fromValue(operationNames), static_cast<int>(DynamicDialog::Roles::ListRole));
    m_model->setData(index(DynamicDialog::Widgets::OperationData),
                     widgets,
                     static_cast<int>(DynamicDialog::Roles::ListRole));
    m_model->setData(index(DynamicDialog::Widgets::OperationData), QVariant::fromValue(data.operationData), static_cast<int>(Qt::DisplayRole));
}

void DynamicDialogPersistor::store() {
    int i = 0;
    std::ignore = i;
}

void DynamicDialogPersistor::setModel(QAbstractItemModel& model) 
{
    m_model = &model;

}

QModelIndex DynamicDialogPersistor::index(DynamicDialog::Widgets widget) const 
{
    return m_model->index(0, static_cast<int>(widget));
}