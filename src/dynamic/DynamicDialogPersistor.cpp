#include "DynamicDialogPersistor.hpp"
#include "DynamicDialog.hpp"

#include <QDebug>

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

    for (const auto &operation : m_operations)
    {
        if (operation.name != data.operation) {
            continue;
        }
        operation.persistor->dataProvider().setData(data.operationData);
        operation.persistor->load();
    }
    m_model->setData(index(DynamicDialog::Widgets::SignalName),
                     data.name,
                     static_cast<int>(Qt::DisplayRole));
    m_model->setData(index(DynamicDialog::Widgets::OperationSelection), QVariant::fromValue(data.operation), static_cast<int>(Qt::DisplayRole));
    m_model->setData(index(DynamicDialog::Widgets::OperationSelection), QVariant::fromValue(operationNames), static_cast<int>(DynamicDialog::Roles::ListRole));
    m_model->setData(index(DynamicDialog::Widgets::OperationData),
                     widgets,
                     static_cast<int>(DynamicDialog::Roles::ListRole));
    m_model->setData(index(DynamicDialog::Widgets::OperationData), QVariant::fromValue(data.operationData), static_cast<int>(Qt::DisplayRole));
}

void DynamicDialogPersistor::store() {
    if (!m_model) {
        qWarning() << "Cannot store dynamic dialog data without a model.";
        return;
    }

    const QString operationName =
        index(DynamicDialog::Widgets::OperationSelection).data(Qt::DisplayRole).toString();
    for (const auto &operation : m_operations) {
        if (operation.name != operationName) {
            continue;
        }

        if (!operation.persistor) {
            qWarning() << "No persistor configured for operation:" << operationName;
            return;
        }

        operation.persistor->store();

        auto operationData = operation.persistor->dataProvider().getData();

        auto dataIndex = m_model->index(0, static_cast<int>(DynamicDialog::Widgets::OperationData));
        m_model->setData(dataIndex, QVariant::fromValue(operationData), static_cast<int>(Qt::DisplayRole));
        return;
    }

    qWarning() << "No operation found for name:" << operationName;
}

void DynamicDialogPersistor::setModel(QAbstractItemModel& model) 
{
    m_model = &model;

}

QAbstractItemModel& DynamicDialogPersistor::model() const
{
    return *m_model;
}

QModelIndex DynamicDialogPersistor::index(DynamicDialog::Widgets widget) const 
{
    return m_model->index(0, static_cast<int>(widget));
}