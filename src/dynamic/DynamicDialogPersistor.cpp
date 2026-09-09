#include "DynamicDialogPersistor.hpp"
#include "DynamicDialog.hpp"
#include "widgets/Sine.hpp"
#include "widgets/Square.hpp"

DynamicDialogPersistor::DynamicDialogPersistor(IDynamicDialogDataProvider &dataProvider)
    : m_dataProvider(dataProvider) {
}

void DynamicDialogPersistor::load()
{
    const QStringList operations = { "Sine", "Square", "Multiply", "Divide" };
    const auto data = m_dataProvider.getData();
    QVariantList widgets;
    widgets.append(QVariant::fromValue<QWidget *>(new Sine));
    for (qsizetype i = 1; i < operations.size(); ++i) {
        widgets.append(QVariant::fromValue<QWidget *>(new Square));
    }

    m_model->setData(index(DynamicDialog::Widgets::OperationSelection), QVariant::fromValue(data.operation), static_cast<int>(Qt::DisplayRole));
    m_model->setData(index(DynamicDialog::Widgets::OperationSelection), QVariant::fromValue(operations), static_cast<int>(DynamicDialog::Roles::ListRole));
    m_model->setData(index(DynamicDialog::Widgets::OperationData),
                     widgets,
                     static_cast<int>(DynamicDialog::Roles::ListRole));
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