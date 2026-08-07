#pragma once

#include <QAbstractTableModel>
#include <QStringList>

namespace dlgen::core {
class Project;
}

class ProjectTableModel : public QAbstractTableModel {
    Q_OBJECT
public:
    enum Column {
        ColumnUiFile = 0,
        ColumnSettings,
        ColumnPreview,
        ColumnCount
    };

    explicit ProjectTableModel(QObject *parent = nullptr);

    void setProject(dlgen::core::Project *project);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

private:
    QStringList uiFileNames_;
};
