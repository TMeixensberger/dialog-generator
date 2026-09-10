#pragma once

#include <QString>

#include "IModelWidget.hpp"
#include "ui_Sine.h"

struct SineData {
    QString leftOperand;
    QString rightOperand;
};

class Sine final : public IModelWidget {
public:
    explicit Sine(QWidget *parent = nullptr);

    void setModel(QAbstractItemModel &model) override;

private:
    Ui::Sine ui;
    QAbstractItemModel *m_model = nullptr;
};
