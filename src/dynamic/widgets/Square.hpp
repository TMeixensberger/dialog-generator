#pragma once

#include "IModelWidget.hpp"
#include "ui_Square.h"

class Square final : public IModelWidget {
public:
    explicit Square(QWidget *parent = nullptr);

    enum Widgets : int
    {
        topLeft,
        bottomRight,
        Count
    };

    void setModel(QAbstractItemModel &model) override;
    [[nodiscard]] int columnCount() const override;
    void init() override;
private:
    Ui::Square ui;
    QAbstractItemModel *m_model = nullptr;
};
