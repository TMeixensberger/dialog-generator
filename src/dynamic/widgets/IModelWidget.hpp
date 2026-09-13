#pragma once

#include <QWidget>

class QAbstractItemModel;

class IModelWidget : public QWidget {
    Q_OBJECT

public:
    explicit IModelWidget(QWidget *parent = nullptr)
        : QWidget(parent) {
    }

    virtual ~IModelWidget() = default;

    virtual void init() = 0;
    virtual void setModel(QAbstractItemModel &model) = 0;
    [[nodiscard]] virtual int columnCount() const = 0;
};

Q_DECLARE_METATYPE(IModelWidget *)
