#pragma once

#include <QJsonObject>
#include <QPair>
#include <QString>
#include <QVector>

#include "Settings.h"
#include "UiFile.h"

namespace dlgen::core {

/**
 * @brief Loads and persists project configuration from a project directory.
 *
 * A project directory is expected to contain a top-level `config.json` file
 * that tracks the UI files belonging to the project. Each tracked UI file is
 * parsed and paired with its per-file settings on load.
 */
class ProjectFile {
public:
    using Data = QPair<UiFile, Settings>;
    using ProjectData = QVector<Data>;

    explicit ProjectFile(const QString &projectDirectory);

    bool reload();
    bool save();

    /**
     * @brief Parse a UI file and its sibling settings file and add them to the project.
     * @param uiFilePath Absolute or relative path to the .ui file.
     * @param errorString Optional; set on failure.
     * @return True on success.
     */
    bool loadUiFile(const QString &uiFilePath, QString *errorString = nullptr);

    bool isValid() const;
    QString errorString() const;

    QString projectDirectory() const;
    QString configFilePath() const;

    const ProjectData &projectData() const;

private:
    QJsonObject toJsonObject() const;

    QString projectDirectory_;
    QString configFilePath_;
    ProjectData projectData_;
    QString errorString_;
};

} // namespace dlgen::core
