#include "Sine.hpp"

#include <QAbstractItemModel>

Sine::Sine(QWidget *parent)
    : IModelWidget(parent) {
    ui.setupUi(this);
}

void Sine::setModel(QAbstractItemModel &model) {
    m_model = &model;
}
