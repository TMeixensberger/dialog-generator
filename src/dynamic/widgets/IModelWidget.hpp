#pragma once

#include <QWidget>

class QAbstractItemModel;

class IModelWidget : public QWidget {
public:
    explicit IModelWidget(QWidget *parent = nullptr)
        : QWidget(parent) {
    }

    virtual ~IModelWidget() = default;

    virtual void setModel(QAbstractItemModel &model) = 0;
};
