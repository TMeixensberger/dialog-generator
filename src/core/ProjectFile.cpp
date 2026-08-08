#include "ProjectFile.h"

#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QJsonArray>
#include <QJsonDocument>
#include <QSaveFile>

#include "Parser.h"

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

    const QJsonArray uiFiles = document.object().value(QStringLiteral("uiFiles")).toArray();
    for (const auto &uiFileValue : uiFiles) {
        const QString uiFilePath = uiFileValue.toString().trimmed();
        if (!uiFilePath.isEmpty()) {
            if (!loadUiFile(uiFilePath, &errorString_)) {
                return false;
            }
        }
    }

    return true;
}

bool ProjectFile::save() {
    errorString_.clear();
    return writeJsonObject(configFilePath_, toJsonObject(), &errorString_);
}

bool ProjectFile::loadUiFile(const QString &uiFilePath, QString *errorString) {
    const auto uiFile = dlgen::parser::parseUiFile(uiFilePath);
    if (uiFile.hasError()) {
        if (errorString != nullptr) {
            *errorString = uiFile.error;
        }
        return false;
    }

    const QString absoluteUiFilePath = QFileInfo(uiFilePath).absoluteFilePath();
    const QString settingsFilePath = absoluteUiFilePath + QStringLiteral(".settings");
    Settings settings;
    if (!SettingsStorage::read(settingsFilePath, &settings, errorString)) {
        return false;
    }

    settings.uiFilePath = absoluteUiFilePath;
    projectData_.append(Data(uiFile, settings));
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

const ProjectFile::ProjectData &ProjectFile::projectData() const {
    return projectData_;
}

QJsonObject ProjectFile::toJsonObject() const {
    QJsonArray uiFiles;
    for (const auto &data : projectData_) {
        uiFiles.append(data.second.uiFilePath);
    }

    QJsonObject config;
    config.insert(QStringLiteral("uiFiles"), uiFiles);
    return config;
}

} // namespace dlgen::core
