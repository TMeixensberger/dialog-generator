#pragma once

#include "DataProvider.hpp"
#include "IAbstractPersistor.hpp"
#include "IModelWidget.hpp"
#include "../Operation.hpp"

#include <QString>
#include <memory>
#include <type_traits>
#include <utility>

class OperationFactory {
public:
    template <typename TPersistor>
    Operation create(IModelWidget *widget, QString name) const {
        static_assert(std::is_base_of_v<IAbstractPersistor, TPersistor>,
                      "TPersistor must implement IAbstractPersistor");

        return Operation(
            widget,
            std::move(name),
            std::make_shared<TPersistor>(std::make_shared<DataProvider>()));
    }
};
