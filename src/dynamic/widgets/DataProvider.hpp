#pragma once

#include <QVariant>

class DataProvider {
public:
    DataProvider() = default;
    virtual ~DataProvider() = default;

    const QVariant &getData() const {
        return m_data;
    }

    void setData(const QVariant &data) {
        m_data = data;
    }

private:
    QVariant m_data;
};
