#pragma once

#include "DynamicDialogPersistor.hpp"

#include <memory>

class DynamicDialog;

class DDFactory {
public:
    explicit DDFactory(IDynamicDialogDataProvider &dataProvider);
    ~DDFactory();
    std::unique_ptr<DynamicDialog> create() const;
    std::shared_ptr<DynamicDialogPersistor> persistor() const;

private:
    std::shared_ptr<DynamicDialogPersistor> m_dynamicDialogPersistor;
};
