#include "ProjectTableModel.h"

#include "Project.h"

ProjectTableModel::ProjectTableModel(QObject *parent)
    : QAbstractTableModel(parent)
{
}

void ProjectTableModel::setProject(dlgen::core::Project *project)
{
    beginResetModel();
    projectData_ = (project && project->isValid())
        ? &project->projectFile().projectData()
        : nullptr;
    endResetModel();
}

int ProjectTableModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid()) return 0;
    return projectData_ ? projectData_->size() : 0;
}

int ProjectTableModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid()) return 0;
    return ColumnCount;
}

QVariant ProjectTableModel::data(const QModelIndex &index, int role) const
{
    if (!projectData_ || !index.isValid() || index.row() >= projectData_->size())
        return {};

    if (role == Qt::DisplayRole) {
        switch (index.column()) {
        case ColumnUiFile:
            return projectData_->at(index.row()).second.uiFilePath;
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
