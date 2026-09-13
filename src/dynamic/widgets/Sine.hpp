#pragma once

#include <QVariant>
#include <QDataWidgetMapper>
#include <QAbstractItemModel>

#include "IModelWidget.hpp"
#include "ui_Sine.h"

struct SineData {
    QVariant minValue;
    QVariant maxValue;
    QString comment;
    bool active;
};
Q_DECLARE_METATYPE(SineData)

class Sine final : public IModelWidget {
public:

    enum Widgets : int
    {
        minValue,
        maxValue,
        comment,
        active,
        Count
    };

    explicit Sine(QWidget *parent = nullptr);

    void setModel(QAbstractItemModel &model) override;
    [[nodiscard]] int columnCount() const override;
    void init() override;
private:
    template <Widgets widget>
    QWidget *createWidget();

    void registerWidget(Widgets widget, QWidget *newWidget);
    int getType(Widgets column) const;

    Ui::Sine ui;
    QAbstractItemModel *m_model = nullptr;
    QDataWidgetMapper *m_mapper = nullptr;
};
