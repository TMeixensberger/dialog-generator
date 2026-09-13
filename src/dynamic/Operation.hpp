#pragma once

#include "widgets/DataProvider.hpp"
#include "widgets/IAbstractPersistor.hpp"
#include "widgets/IModelWidget.hpp"
#include <QString>
#include <memory>
#include <utility>

class Operation {
public:
    Operation(IModelWidget *widget,
              QString name,
              std::shared_ptr<IAbstractPersistor> persistor = nullptr)
        : widget(widget),
          name(std::move(name)),
          persistor(std::move(persistor)) {
    }

    IModelWidget *widget;
    QString name;
    std::shared_ptr<IAbstractPersistor> persistor;
};
