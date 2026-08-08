#include "ProjectFile.h"

#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QJsonArray>
#include <QJsonDocument>
#include <QSaveFile>

namespace dlgen::core {

namespace {

bool writeJsonObject(const QString &filePath, const QJsonObject &jsonObject, QString *errorString) {
    QSaveFile file(filePath);
    if (!file.open(QIODevice::WriteOnly)) {
        if (errorString != nullptr) {
            *errorString = QStringLiteral("failed to open '%1' for writing").arg(filePath);
        }
        return false;
    }

    const QByteArray jsonBytes = QJsonDocument(jsonObject).toJson(QJsonDocument::Indented);
    const qint64 bytesWritten = file.write(jsonBytes);
    if (bytesWritten != static_cast<qint64>(jsonBytes.size())) {
        if (errorString != nullptr) {
            *errorString = QStringLiteral("failed to write '%1'").arg(filePath);
        }
        file.cancelWriting();
        return false;
    }

    if (!file.commit()) {
        if (errorString != nullptr) {
            *errorString = QStringLiteral("failed to commit '%1'").arg(filePath);
        }
        return false;
    }

    return true;
}

} // namespace

ProjectFile::ProjectFile(const QString &projectDirectory)
    : projectDirectory_(QDir(projectDirectory).absolutePath()),
      configFilePath_(QDir(projectDirectory_).filePath(QStringLiteral("config.json"))) {
    reload();
}

bool ProjectFile::reload() {
    errorString_.clear();
    uiFileNames_.clear();
    uiConfigFileNames_.clear();
    projectData_.clear();

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

    const QJsonObject config = document.object();
    uiFileNames_ = parseUiFileNames(config);
    uiConfigFileNames_ = parseUiConfigFileNames(config);
    if (uiConfigFileNames_.isEmpty()) {
        for (const auto &uiFileName : uiFileNames_) {
            uiConfigFileNames_.append(toUiConfigFileName(uiFileName));
        }
    }

    // TODO: Populate projectData_ from uiFiles and per-ui settings files.
    return true;
}

bool ProjectFile::save() {
    errorString_.clear();
    return writeJsonObject(configFilePath_, toJsonObject(), &errorString_);
}

void ProjectFile::loadUiFile(const QString &uiFilePath, const UiFile &uiFile, Settings settings) {
    const QString absoluteUiFilePath = QFileInfo(uiFilePath).absoluteFilePath();
    settings.uiFilePath = absoluteUiFilePath;

    if (!uiFileNames_.contains(absoluteUiFilePath)) {
        uiFileNames_.append(absoluteUiFilePath);
    }

    const QString uiConfigFileName = toUiConfigFileName(absoluteUiFilePath);
    if (!uiConfigFileNames_.contains(uiConfigFileName)) {
        uiConfigFileNames_.append(uiConfigFileName);
    }

    projectData_.append(Data(uiFile, settings));
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

const ProjectFile::ProjectData &ProjectFile::projectData() const {
    return projectData_;
}

const QStringList &ProjectFile::uiFileNames() const {
    return uiFileNames_;
}

const QStringList &ProjectFile::uiConfigFileNames() const {
    return uiConfigFileNames_;
}

QString ProjectFile::uiConfigFilePath(const QString &uiFileName) const {
    const int uiFileIndex = uiFileNames_.indexOf(uiFileName);
    if (uiFileIndex < 0 || uiFileIndex >= uiConfigFileNames_.size()) {
        return QString();
    }

    return QDir(projectDirectory_).filePath(uiConfigFileNames_.at(uiFileIndex));
}

QJsonObject ProjectFile::toJsonObject() const {
    QJsonArray uiFiles;
    for (const auto &uiFileName : uiFileNames_) {
        uiFiles.append(uiFileName);
    }

    QJsonArray uiConfigFiles;
    for (const auto &uiConfigFileName : uiConfigFileNames_) {
        uiConfigFiles.append(uiConfigFileName);
    }

    QJsonObject config;
    config.insert(QStringLiteral("uiFiles"), uiFiles);
    config.insert(QStringLiteral("uiConfigFiles"), uiConfigFiles);
    return config;
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

QStringList ProjectFile::parseUiConfigFileNames(const QJsonObject &config) {
    QStringList uiConfigFileNames;
    const QJsonValue uiConfigFilesValue = config.value(QStringLiteral("uiConfigFiles"));
    if (uiConfigFilesValue.isArray()) {
        const QJsonArray uiConfigFiles = uiConfigFilesValue.toArray();
        for (const auto &uiConfigFileValue : uiConfigFiles) {
            const QString uiConfigFileName = uiConfigFileValue.toString().trimmed();
            if (!uiConfigFileName.isEmpty()) {
                uiConfigFileNames.append(uiConfigFileName);
            }
        }
    }
    return uiConfigFileNames;
}

QString ProjectFile::toUiConfigFileName(const QString &uiFileName) {
    const QFileInfo uiFileInfo(uiFileName);
    return uiFileInfo.completeBaseName() + QStringLiteral(".json");
}

} // namespace dlgen::core
