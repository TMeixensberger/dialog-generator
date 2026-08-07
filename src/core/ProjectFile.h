#pragma once

#include <QJsonObject>
#include <QJsonValue>
#include <QString>
#include <QStringList>

namespace dlgen::core {

/**
 * @brief Loads and exposes project configuration files from a project directory.
 *
 * A project directory is expected to contain a top-level `config.json` file.
 * The parsed JSON object is kept in memory and can be queried directly, while
 * the referenced UI file names from the `uiFiles` array are tracked together
 * with their derived per-UI config file names.
 */
class ProjectFile {
public:
    explicit ProjectFile(const QString &projectDirectory);

    bool reload();

    bool isValid() const;
    QString errorString() const;

    QString projectDirectory() const;
    QString configFilePath() const;

    const QJsonObject &config() const;
    QJsonValue value(const QString &key) const;

    const QStringList &uiFileNames() const;
    const QStringList &uiConfigFileNames() const;
    /**
     * @brief Return the absolute path to the derived config file for a tracked UI file.
     * @return Empty string when uiFileName is not part of the loaded project config.
     */
    QString uiConfigFilePath(const QString &uiFileName) const;

private:
    static QStringList parseUiFileNames(const QJsonObject &config);
    static QString toUiConfigFileName(const QString &uiFileName);

    QString projectDirectory_;
    QString configFilePath_;
    QJsonObject config_;
    QStringList uiFileNames_;
    QStringList uiConfigFileNames_;
    QString errorString_;
};

} // namespace dlgen::core
