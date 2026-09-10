#pragma once

#include <QDialog>
#include <QAbstractItemModel>
#include <QDataWidgetMapper>
#include "ui_DynamicDialog.h"

class DynamicDialog : public QDialog {
public:

    enum class Widgets : int
    {
        SignalName,
        OperationSelection,
        OperationData,
        Count
    };

    enum class Roles : int
    {
        ListRole = Qt::UserRole + 1,
        WidgetRole,
    };

    explicit DynamicDialog(QAbstractItemModel& model, QWidget *parent = nullptr);
    ~DynamicDialog() override;

private:
    void initOperations();
    void initOperationWidget();

    Ui::DynamicDialog ui;
    QAbstractItemModel& m_model;
    QDataWidgetMapper m_mapper;
};
