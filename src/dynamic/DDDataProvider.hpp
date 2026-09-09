#pragma once

#include "IDynamicDialogDataProvider.hpp"

class DDDataProvider : public IDynamicDialogDataProvider {
public:
    DDDataProvider() = default;
    ~DDDataProvider() override = default;

    const Data &getData() const override;
    void setData(const Data &data) override;

private:
    Data m_data;
};
