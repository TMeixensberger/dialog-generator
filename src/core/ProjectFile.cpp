#include "ProjectFile.h"

#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QJsonArray>
#include <QJsonDocument>

namespace dlgen::core {

ProjectFile::ProjectFile(const QString &projectDirectory)
    : projectDirectory_(QDir(projectDirectory).absolutePath()),
      configFilePath_(QDir(projectDirectory_).filePath(QStringLiteral("config.json"))) {
    reload();
}

bool ProjectFile::reload() {
    errorString_.clear();
    config_ = QJsonObject();
    uiFileNames_.clear();
    uiConfigFileNames_.clear();

    const QFileInfo directoryInfo(projectDirectory_);
    if (!directoryInfo.exists() || !directoryInfo.isDir()) {
        errorString_ = QStringLiteral("project directory does not exist");
        return false;
    }

    QFile file(configFilePath_);
    if (!file.open(QIODevice::ReadOnly)) {
        errorString_ = QStringLiteral("failed to open config.json");
        return false;
    }

    QJsonParseError parseError;
    const QJsonDocument document = QJsonDocument::fromJson(file.readAll(), &parseError);
    if (parseError.error != QJsonParseError::NoError || !document.isObject()) {
        errorString_ = parseError.error != QJsonParseError::NoError
            ? parseError.errorString()
            : QStringLiteral("config.json must contain a JSON object");
        return false;
    }

    config_ = document.object();
    uiFileNames_ = parseUiFileNames(config_);
    for (const auto &uiFileName : uiFileNames_) {
        uiConfigFileNames_.append(toUiConfigFileName(uiFileName));
    }

    return true;
}

bool ProjectFile::isValid() const {
    return errorString_.isEmpty();
}

QString ProjectFile::errorString() const {
    return errorString_;
}

QString ProjectFile::projectDirectory() const {
    return projectDirectory_;
}

QString ProjectFile::configFilePath() const {
    return configFilePath_;
}

const QJsonObject &ProjectFile::config() const {
    return config_;
}

QJsonValue ProjectFile::value(const QString &key) const {
    return config_.value(key);
}

const QStringList &ProjectFile::uiFileNames() const {
    return uiFileNames_;
}

const QStringList &ProjectFile::uiConfigFileNames() const {
    return uiConfigFileNames_;
}

QString ProjectFile::uiConfigFilePath(const QString &uiFileName) const {
    return QDir(projectDirectory_).filePath(toUiConfigFileName(uiFileName));
}

QStringList ProjectFile::parseUiFileNames(const QJsonObject &config) {
    QStringList uiFileNames;
    const QJsonArray uiFiles = config.value(QStringLiteral("uiFiles")).toArray();
    for (const auto &uiFileValue : uiFiles) {
        const QString uiFileName = uiFileValue.toString().trimmed();
        if (!uiFileName.isEmpty()) {
            uiFileNames.append(uiFileName);
        }
    }
    return uiFileNames;
}

QString ProjectFile::toUiConfigFileName(const QString &uiFileName) {
    const QFileInfo uiFileInfo(uiFileName);
    return uiFileInfo.completeBaseName() + QStringLiteral(".json");
}

} // namespace dlgen::core
