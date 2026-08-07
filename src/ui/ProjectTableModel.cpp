#include "ProjectTableModel.h"

#include "Project.h"
#include "ProjectFile.h"

ProjectTableModel::ProjectTableModel(QObject *parent)
    : QAbstractTableModel(parent)
{
}

void ProjectTableModel::setProject(dlgen::core::Project *project)
{
    beginResetModel();
    uiFileNames_.clear();
    if (project && project->isValid()) {
        uiFileNames_ = project->projectFile().uiFileNames();
    }
    endResetModel();
}

int ProjectTableModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid()) return 0;
    return uiFileNames_.size();
}

int ProjectTableModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid()) return 0;
    return ColumnCount;
}

QVariant ProjectTableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() >= uiFileNames_.size())
        return {};

    if (role == Qt::DisplayRole) {
        switch (index.column()) {
        case ColumnUiFile:
            return uiFileNames_.at(index.row());
        case ColumnSettings:
            return QStringLiteral("Settings");
        case ColumnPreview:
            return QStringLiteral("Preview");
        default:
            break;
        }
    }
    return {};
}

QVariant ProjectTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole || orientation != Qt::Horizontal)
        return {};

    switch (section) {
    case ColumnUiFile:
        return QStringLiteral("UI File");
    case ColumnSettings:
        return QStringLiteral("Settings");
    case ColumnPreview:
        return QStringLiteral("Preview");
    default:
        break;
    }
    return {};
}
