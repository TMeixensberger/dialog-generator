#include "DDDataProvider.hpp"

const IDynamicDialogDataProvider::Data &DDDataProvider::getData() const {
    return m_data;
}

void DDDataProvider::setData(const Data &data) {
    m_data = data;
}
