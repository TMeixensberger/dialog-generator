#include "Square.hpp"

#include <QAbstractItemModel>

Square::Square(QWidget *parent)
    : IModelWidget(parent) {
    ui.setupUi(this);
}

void Square::setModel(QAbstractItemModel &model) {
    m_model = &model;
}

void Square::init() {
}

int Square::columnCount() const
{
    return static_cast<int>(Widgets::Count);
}