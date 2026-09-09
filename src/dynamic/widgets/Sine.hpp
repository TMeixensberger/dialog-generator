#pragma once

#include <QWidget>
#include <QString>

#include "ui_Sine.h"

struct SineData {
    QString leftOperand;
    QString rightOperand;
};

class Sine final : public QWidget {
public:
    explicit Sine(QWidget *parent = nullptr);

private:
    Ui::Sine ui;
};
