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

    void load() override
    {
        auto data = m_dataProvider->getData();
        if (data.userType() != qMetaTypeId<SineData>()) {
            return;
        }
        const auto sineData = data.value<SineData>();

        m_model->setData(index(Sine::Widgets::minValue), sineData.minValue);
        m_model->setData(index(Sine::Widgets::maxValue), sineData.maxValue);
        m_model->setData(index(Sine::Widgets::comment), sineData.comment);
        m_model->setData(index(Sine::Widgets::active), sineData.active);
    }
    void store() override
    {
        SineData sineData;
        sineData.minValue = m_model->data(index(Sine::Widgets::minValue));
        sineData.maxValue = m_model->data(index(Sine::Widgets::maxValue));
        sineData.comment = m_model->data(index(Sine::Widgets::comment));
        sineData.active = m_model->data(index(Sine::Widgets::active));

        m_dataProvider->setData(QVariant::fromValue(sineData));
    }

    void setModel(QAbstractItemModel &model) override {
        m_model = &model;

    }

    DataProvider& dataProvider() const override {
        return *m_dataProvider;
    }

private:
    QModelIndex index(Sine::Widgets widget) const {
        return m_model->index(0, widget);
    }

    std::shared_ptr<DataProvider> m_dataProvider;
    QAbstractItemModel *m_model = nullptr;
};
