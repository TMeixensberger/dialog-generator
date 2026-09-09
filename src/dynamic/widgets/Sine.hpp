#pragma once

#include <QWidget>

#include "ui_Sine.h"

class Sine final : public QWidget {
public:
    explicit Sine(QWidget *parent = nullptr);

private:
    Ui::Sine ui;
};
