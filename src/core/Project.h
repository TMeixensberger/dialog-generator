#pragma once

#include <memory>

#include <QString>

#include "ProjectFile.h"

namespace dlgen::core {

class ProjectFile;

/**
 * @brief Owns the active project state and delegates project file handling.
 */
class Project {
public:
    Project() = default;
    ~Project();

    bool load(const QString &projectDirectory);
    bool create(const QString &projectDirectory);
    bool save();
    bool addUiFile(const QString &path);

    bool isValid() const;
    QString errorString() const;

    ProjectFile &projectFile();
    const ProjectFile &projectFile() const;

private:
    std::unique_ptr<ProjectFile> projectFile_;
    QString errorString_;
};

} // namespace dlgen::core
