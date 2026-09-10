#pragma once

#include "IModelWidget.hpp"
#include "ui_Square.h"

class Square final : public IModelWidget {
public:
    explicit Square(QWidget *parent = nullptr);

    void setModel(QAbstractItemModel &model) override;

private:
    Ui::Square ui;
    QAbstractItemModel *m_model = nullptr;
};
