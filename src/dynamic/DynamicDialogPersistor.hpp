#pragma once

#include "IDynamicDialogDataProvider.hpp"
#include "DynamicDialog.hpp"
#include <QAbstractItemModel>

class DynamicDialogPersistor {
public:
    explicit DynamicDialogPersistor(IDynamicDialogDataProvider &dataProvider);
    void load();
    void store();
    void setModel(QAbstractItemModel& model);
private:
    QModelIndex index(DynamicDialog::Widgets widget) const;

    IDynamicDialogDataProvider &m_dataProvider;
    QAbstractItemModel* m_model;
};
