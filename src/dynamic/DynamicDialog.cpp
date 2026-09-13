#include "DynamicDialog.hpp"
#include "widgets/IModelWidget.hpp"

#include <QComboBox>
#include <QVariantList>
#include <QtGlobal>

DynamicDialog::DynamicDialog(QAbstractItemModel& model, QWidget *parent)
    : QDialog(parent), m_model(model) {
    ui.setupUi(this);

    m_mapper.setModel(&m_model);
    m_mapper.addMapping(ui.lineEditSignal, static_cast<int>(DynamicDialog::Widgets::SignalName));
    m_mapper.addMapping(ui.comboBox, static_cast<int>(DynamicDialog::Widgets::OperationSelection));
    m_mapper.toFirst();

    initOperations();
    initOperationWidget();

    connect(ui.comboBox, qOverload<int>(&QComboBox::currentIndexChanged),
            this, [this](int index) {
                ui.operationStack->setCurrentIndex(index);
                m_model.setData(
                    m_model.index(0, static_cast<int>(Widgets::OperationSelection)),
                    ui.comboBox->currentText(),
                    Qt::DisplayRole);
            });
    connect(ui.lineEditSignal, &QLineEdit::textChanged,
            this, [this](const QString &text) {
                m_model.setData(
                    m_model.index(0, static_cast<int>(Widgets::SignalName)),
                    text,
                    Qt::DisplayRole);
            });
}

void DynamicDialog::initOperations() {
    const QModelIndex operationIndex = m_model.index(0, static_cast<int>(Widgets::OperationSelection));
    auto *operationSelection = qobject_cast<QComboBox*>(
        m_mapper.mappedWidgetAt(static_cast<int>(Widgets::OperationSelection)));
    Q_ASSERT(operationSelection);
    operationSelection->addItems(operationIndex.data(static_cast<int>(Roles::ListRole)).toStringList());

    const int currentIndex = operationSelection->findText(operationIndex.data(Qt::DisplayRole).toString());
    if (currentIndex >= 0) {
        operationSelection->setCurrentIndex(currentIndex);
    }
}

void DynamicDialog::initOperationWidget() {
    const QModelIndex operationIndex =
        m_model.index(0, static_cast<int>(Widgets::OperationSelection));
    const QModelIndex operationDataIndex =
        m_model.index(0, static_cast<int>(Widgets::OperationData));

    const auto operations =
        operationIndex.data(static_cast<int>(Roles::ListRole)).toStringList();
    const auto widgetValues =
        operationDataIndex.data(static_cast<int>(Roles::ListRole)).toList();
    if (operations.size() != widgetValues.size()) {
        return;
    }

    for (const auto &widgetValue : widgetValues) {
        auto *widget = widgetValue.value<IModelWidget *>();
        if (!widget) {
            return;
        }

        widget->init();
        ui.operationStack->addWidget(widget);
    }

    ui.operationStack->setCurrentIndex(0);
}

DynamicDialog::~DynamicDialog() = default;
