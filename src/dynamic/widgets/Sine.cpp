#include "Sine.hpp"

#include <QAbstractItemModel>
#include <QComboBox>
#include <QDoubleSpinBox>
#include <QLineEdit>
#include <QSpinBox>
#include <QStyledItemDelegate>

#include <limits>

namespace {

template <typename... Ts>
struct Overload : Ts... {
    using Ts::operator()...;
};

template <typename... Ts>
Overload(Ts...) -> Overload<Ts...>;

class SineItemDelegate final : public QStyledItemDelegate {
public:
    explicit SineItemDelegate(QObject *parent = nullptr)
        : QStyledItemDelegate(parent) {
    }

    void setEditorData(QWidget *editor,
                       const QModelIndex &index) const override
    {
        const QVariant data = index.data(Qt::DisplayRole);

        if (auto *spinBox = qobject_cast<QSpinBox *>(editor)) {
            const auto value = data.value<SineNumericValue>();
            if (const auto *intValue = std::get_if<int>(&value)) {
                spinBox->setValue(*intValue);
            }
            return;
        }

        if (auto *spinBox = qobject_cast<QDoubleSpinBox *>(editor)) {
            const auto value = data.value<SineNumericValue>();
            if (const auto *doubleValue = std::get_if<double>(&value)) {
                spinBox->setValue(*doubleValue);
            }
            return;
        }

        if (auto *lineEdit = qobject_cast<QLineEdit *>(editor)) {
            lineEdit->setText(data.toString());
            return;
        }

        if (auto *comboBox = qobject_cast<QComboBox *>(editor)) {
            comboBox->setCurrentIndex(data.toBool() ? 0 : 1);
        }
    }

    void setModelData(QWidget *editor,
                      QAbstractItemModel *model,
                      const QModelIndex &index) const override
    {
        if (auto *spinBox = qobject_cast<QSpinBox *>(editor)) {
            model->setData(
                index,
                QVariant::fromValue(SineNumericValue{spinBox->value()}),
                Qt::DisplayRole);
            return;
        }

        if (auto *spinBox = qobject_cast<QDoubleSpinBox *>(editor)) {
            model->setData(
                index,
                QVariant::fromValue(SineNumericValue{spinBox->value()}),
                Qt::DisplayRole);
            return;
        }

        if (auto *lineEdit = qobject_cast<QLineEdit *>(editor)) {
            model->setData(index, lineEdit->text(), Qt::DisplayRole);
            return;
        }

        if (auto *comboBox = qobject_cast<QComboBox *>(editor)) {
            model->setData(index, comboBox->currentIndex() == 0, Qt::DisplayRole);
        }
    }
};

}

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

    switch (widget) {
    case Widgets::minValue:
    case Widgets::maxValue: {
        const auto value = data.value<SineNumericValue>();
        return std::visit(Overload{
            [this](int value) -> QWidget * {
            auto *spinBox = new QSpinBox(this);
            spinBox->setRange(
                std::numeric_limits<int>::min(),
                std::numeric_limits<int>::max());
            spinBox->setValue(value);
            return spinBox;
            },
            [this](double value) -> QWidget * {
            auto *spinBox = new QDoubleSpinBox(this);
            spinBox->setRange(
                std::numeric_limits<double>::lowest(),
                std::numeric_limits<double>::max());
            spinBox->setDecimals(2);
            spinBox->setValue(value);
            return spinBox;
            }
        }, value);
    }
    case Widgets::comment:
        return new QLineEdit(this);
    case Widgets::active: {
        auto *comboBox = new QComboBox(this);
        comboBox->addItems({QStringLiteral("TRUE"), QStringLiteral("FALSE")});
        comboBox->setCurrentIndex(data.toBool() ? 0 : 1);
        return comboBox;
    }
    case Widgets::Count:
    default:
        return nullptr;
    }
}

int Sine::getType(Widgets column) const
{
    const QVariant data = m_model->data(m_model->index(0, column));

    switch (column) {
    case Widgets::minValue:
    case Widgets::maxValue:
        return static_cast<int>(data.value<SineNumericValue>().index());
    case Widgets::comment:
    case Widgets::active:
        return data.userType();
    case Widgets::Count:
    default:
        return QMetaType::UnknownType;
    }
}

void Sine::registerWidget(Widgets widget, QWidget *newWidget)
{
    if (auto *existingWidget = m_mapper->mappedWidgetAt(widget)) {
        m_mapper->removeMapping(existingWidget);
        ui.verticalLayout->removeWidget(existingWidget);
        delete existingWidget;
    }

    if (!newWidget) {
        m_widgetTypes.remove(widget);
        return;
    }

    ui.verticalLayout->addWidget(newWidget);
    m_mapper->addMapping(newWidget, widget);
    m_widgetTypes.insert(widget, getType(widget));
}

int Sine::columnCount() const
{
    return static_cast<int>(Widgets::Count);
}

void Sine::init()
{
    m_mapper = new QDataWidgetMapper(this);
    m_mapper->setModel(m_model);
    m_mapper->setItemDelegate(new SineItemDelegate(m_mapper));
    connect(m_model, &QAbstractItemModel::dataChanged, this,
            [this](const QModelIndex &topLeft, const QModelIndex &bottomRight) {
                for (int column = topLeft.column();
                     column <= bottomRight.column();
                     ++column) {
                    if (column < 0 || column >= static_cast<int>(Widgets::Count)) {
                        continue;
                    }
                    const auto widget = static_cast<Widgets>(column);
                    const int currentType = getType(widget);
                    if (!m_widgetTypes.contains(widget)
                        || m_widgetTypes.value(widget) == currentType) {
                        continue;
                    }

                    QWidget *newWidget = nullptr;
                    switch (widget) {
                    case Widgets::minValue:
                        newWidget = createWidget<Widgets::minValue>();
                        break;
                    case Widgets::maxValue:
                        newWidget = createWidget<Widgets::maxValue>();
                        break;
                    case Widgets::comment:
                        newWidget = createWidget<Widgets::comment>();
                        break;
                    case Widgets::active:
                        newWidget = createWidget<Widgets::active>();
                        break;
                    case Widgets::Count:
                    default:
                        break;
                    }
                    registerWidget(widget, newWidget);
                }
            });

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