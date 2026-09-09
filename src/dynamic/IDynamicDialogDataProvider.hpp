#pragma once

#include "Operations.hpp"

#include <QString>
#include <QVariant>

class IDynamicDialogDataProvider {
public:
    class Data {
    public:
        Data() = default;
        virtual ~Data() = default;

        QString name;
        QString no;
        QString operation;
        QVariant operationData; // Can hold any type of data associated with the operation
    };

    virtual ~IDynamicDialogDataProvider() = default;

    virtual const Data &getData() const = 0;
    virtual void setData(const Data &data) = 0;
};
