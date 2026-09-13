#pragma once

#include "DataProvider.hpp"
#include "IAbstractPersistor.hpp"
#include "IModelWidget.hpp"
#include "../Operation.hpp"

#include <QStandardItemModel>
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

        auto model = new QStandardItemModel(1, widget->columnCount(), widget);
        auto persistor =
            std::make_shared<TPersistor>(std::make_shared<DataProvider>());

        widget->setModel(*model);
        persistor->setModel(*model);

        return Operation(widget, std::move(name), std::move(persistor));
    }
};
