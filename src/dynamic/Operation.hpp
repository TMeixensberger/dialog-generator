#pragma once

#include "widgets/DataProvider.hpp"
#include "widgets/IAbstractPersistor.hpp"
#include <QString>
#include <QWidget>
#include <memory>
#include <utility>

class Operation {
public:
    Operation(QWidget *widget,
              QString name,
              std::shared_ptr<IAbstractPersistor> persistor = nullptr)
        : widget(widget),
          name(std::move(name)),
          persistor(std::move(persistor)) {
    }

    QWidget *widget;
    QString name;
    std::shared_ptr<IAbstractPersistor> persistor;
};
