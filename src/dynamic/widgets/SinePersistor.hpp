#pragma once

#include "DataProvider.hpp"
#include "IAbstractPersistor.hpp"
#include "Sine.hpp"

#include <QAbstractItemModel>

class SinePersistor final : public IAbstractPersistor {
public:
    explicit SinePersistor(std::shared_ptr<DataProvider> dataProvider)
        : m_dataProvider(dataProvider) {
    }

    void load() override {}
    void store() override {}

    void setModel(QAbstractItemModel &model) override {
        m_model = &model;
    }

    DataProvider& dataProvider() const {
        return *m_dataProvider;
    }

private:
    std::shared_ptr<DataProvider> m_dataProvider;
    QAbstractItemModel *m_model = nullptr;
};
