#pragma once

#include <QWidget>

#include "ui_Square.h"

class Square final : public QWidget {
public:
    explicit Square(QWidget *parent = nullptr);

private:
    Ui::Square ui;
};
