#pragma once

class DataProvider;
class QAbstractItemModel;

class IAbstractPersistor {
public:
    virtual ~IAbstractPersistor() = default;

    virtual void load() = 0;
    virtual void store() = 0;
    virtual DataProvider& dataProvider() const = 0;
    virtual void setModel(QAbstractItemModel& model) = 0;
};
