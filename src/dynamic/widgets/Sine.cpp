#include "Sine.hpp"

#include <QAbstractItemModel>
#include <QComboBox>
#include <QDoubleSpinBox>
#include <QLineEdit>
#include <QSpinBox>

#include <limits>

Sine::Sine(QWidget *parent)
    : IModelWidget(parent) {
    ui.setupUi(this);
}

void Sine::setModel(QAbstractItemModel &model)
{
    m_model = &model;
}

template <Sine::Widgets widget>
QWidget *Sine::createWidget()
{
    const QVariant data = m_model->data(
        m_model->index(0, widget));
    const int dataId = data.userType();

    switch (widget) {
    case Widgets::minValue:
    case Widgets::maxValue:
        switch (dataId) {
        case QMetaType::Int: {
            auto *spinBox = new QSpinBox(this);
            spinBox->setRange(
                std::numeric_limits<int>::min(),
                std::numeric_limits<int>::max());
            return spinBox;
        }
        case QMetaType::Double: {
            auto *spinBox = new QDoubleSpinBox(this);
            spinBox->setRange(
                std::numeric_limits<double>::lowest(),
                std::numeric_limits<double>::max());
            spinBox->setDecimals(2);
            return spinBox;
        }
        default:
            return nullptr;
        }
    case Widgets::comment:
        if (dataId == QMetaType::QString) {
            return new QLineEdit(this);
        }
        return nullptr;
    case Widgets::active:
        if (dataId == QMetaType::Bool) {
            auto *comboBox = new QComboBox(this);
            comboBox->addItems({QStringLiteral("TRUE"), QStringLiteral("FALSE")});
            return comboBox;
        }
        return nullptr;
    case Widgets::Count:
    default:
        return nullptr;
    }
}

int Sine::getType(Widgets column) const
{
    return m_model->data(m_model->index(0, column)).userType();
}

void Sine::registerWidget(Widgets widget, QWidget *newWidget)
{
    if (auto *existingWidget = m_mapper->mappedWidgetAt(widget)) {
        m_mapper->removeMapping(existingWidget);
        ui.verticalLayout->removeWidget(existingWidget);
        delete existingWidget;
    }

    if (!newWidget) {
        return;
    }

    ui.verticalLayout->addWidget(newWidget);
    m_mapper->addMapping(newWidget, widget);
}

int Sine::columnCount() const
{
    return static_cast<int>(Widgets::Count);
}

void Sine::init()
{
    m_mapper = new QDataWidgetMapper(this);
    m_mapper->setModel(m_model);

    if (auto *minValueWidget = createWidget<Widgets::minValue>()) {
        registerWidget(Widgets::minValue, minValueWidget);
    }
    if (auto *maxValueWidget = createWidget<Widgets::maxValue>()) {
        registerWidget(Widgets::maxValue, maxValueWidget);
    }
    if (auto *commentWidget = createWidget<Widgets::comment>()) {
        registerWidget(Widgets::comment, commentWidget);
    }
    if (auto *activeWidget = createWidget<Widgets::active>()) {
        registerWidget(Widgets::active, activeWidget);
    }
    m_mapper->setSubmitPolicy(QDataWidgetMapper::AutoSubmit);
    m_mapper->toFirst();
}