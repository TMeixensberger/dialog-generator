#include "DynamicDialog.hpp"

#include <QComboBox>
#include <QtGlobal>

DynamicDialog::DynamicDialog(QAbstractItemModel& model, QWidget *parent)
    : QDialog(parent), m_model(model) {
    ui.setupUi(this);

    m_mapper.setModel(&m_model);
    m_mapper.addMapping(ui.comboBox, static_cast<int>(DynamicDialog::Widgets::OperationSelection));
    m_mapper.toFirst();

    initOperations();
    initOperationWidget();
}

void DynamicDialog::initOperations() {
    const QModelIndex operationIndex = m_model.index(0, static_cast<int>(Widgets::OperationSelection));
    auto *operationSelection = qobject_cast<QComboBox*>(
        m_mapper.mappedWidgetAt(static_cast<int>(Widgets::OperationSelection)));
    Q_ASSERT(operationSelection);
    operationSelection->addItems(operationIndex.data(static_cast<int>(Roles::ListRole)).toStringList());
}

void DynamicDialog::initOperationWidget() {
    const QModelIndex operationDataIndex =
        m_model.index(0, static_cast<int>(Widgets::OperationData));
    auto *widget = operationDataIndex
                       .data(static_cast<int>(Roles::WidgetRole))
                       .value<QWidget *>();
    if (!widget) {
        return;
    }

    ui.operationStack->addWidget(widget);
    ui.operationStack->setCurrentWidget(widget);
}

DynamicDialog::~DynamicDialog() = default;
