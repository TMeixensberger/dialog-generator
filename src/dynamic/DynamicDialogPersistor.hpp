#pragma once

#include "IDynamicDialogDataProvider.hpp"
#include "DynamicDialog.hpp"
#include "Operation.hpp"
#include <QAbstractItemModel>
#include <QList>

class DynamicDialogPersistor {
public:
    DynamicDialogPersistor(IDynamicDialogDataProvider &dataProvider,
                           QList<Operation> operations);
    void load();
    void store();
    void setModel(QAbstractItemModel& model);
private:
    QModelIndex index(DynamicDialog::Widgets widget) const;

    IDynamicDialogDataProvider &m_dataProvider;
    QList<Operation> m_operations;
    QAbstractItemModel* m_model;
};
