#include "Project.h"

#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QtGlobal>

#include "Generator.h"
#include "Parser.h"

namespace dlgen::core {

Project::~Project() = default;

bool Project::load(const QString &projectDirectory) {
    errorString_.clear();

    auto projectFile = std::make_unique<ProjectFile>(projectDirectory);
    if (!projectFile->isValid()) {
        errorString_ = projectFile->errorString();
        return false;
    }

    projectFile_ = std::move(projectFile);
    return true;
}

bool Project::create(const QString &projectDirectory) {
    errorString_.clear();

    const QString configFilePath = QDir(projectDirectory).filePath(QStringLiteral("config.json"));
    if (QFile::exists(configFilePath)) {
        errorString_ = QStringLiteral("config.json already exists in this directory");
        return false;
    }

    QFile configFile(configFilePath);
    if (!configFile.open(QIODevice::WriteOnly | QIODevice::NewOnly)) {
        errorString_ = QStringLiteral("Could not create config.json");
        return false;
    }

    const QJsonObject config{{QStringLiteral("uiFiles"), QJsonArray()}};
    const QByteArray configBytes = QJsonDocument(config).toJson(QJsonDocument::Indented);
    const qint64 bytesWritten = configFile.write(configBytes);
    if (bytesWritten != static_cast<qint64>(configBytes.size()) || !configFile.flush()) {
        configFile.close();
        QFile::remove(configFilePath);
        errorString_ = QStringLiteral("Could not write config.json");
        return false;
    }
    configFile.close();

    auto projectFile = std::make_unique<ProjectFile>(projectDirectory);
    if (!projectFile->isValid()) {
        QFile::remove(configFilePath);
        errorString_ = projectFile->errorString();
        return false;
    }

    projectFile_ = std::move(projectFile);
    return true;
}

bool Project::save() {
    if (!projectFile_) {
        errorString_ = QStringLiteral("No project loaded");
        return false;
    }

    if (!projectFile_->save()) {
        errorString_ = projectFile_->errorString();
        return false;
    }

    errorString_.clear();
    return true;
}

bool Project::addUiFile(const QString &path) {
    if (!projectFile_) {
        errorString_ = QStringLiteral("No project loaded");
        return false;
    }

    const QFileInfo sourceInfo(path);
    if (!sourceInfo.exists() || !sourceInfo.isFile()) {
        errorString_ = QStringLiteral("UI file does not exist");
        return false;
    }

    const QString sourcePath = sourceInfo.absoluteFilePath();
    const QString copiedPath = QDir(projectFile_->projectDirectory()).filePath(sourceInfo.fileName());

    if (QFileInfo(copiedPath).absoluteFilePath() != sourcePath) {
        if (QFile::exists(copiedPath) && !QFile::remove(copiedPath)) {
            errorString_ = QStringLiteral("Could not replace existing UI file in project directory");
            return false;
        }
        if (!QFile::copy(sourcePath, copiedPath)) {
            errorString_ = QStringLiteral("Could not copy UI file into project directory");
            return false;
        }
    }

    if (!loadUiFile(copiedPath)) {
        return false;
    }
    errorString_.clear();
    return true;
}

bool Project::isValid() const {
    return errorString_.isEmpty() && projectFile_ != nullptr;
}

QString Project::errorString() const {
    return errorString_;
}

ProjectFile &Project::projectFile() {
    Q_ASSERT(projectFile_);
    return *projectFile_;
}

const ProjectFile &Project::projectFile() const {
    Q_ASSERT(projectFile_);
    return *projectFile_;
}

bool Project::loadUiFile(const QString &uiFilePath) {
    const auto uiFile = dlgen::parser::parseUiFile(uiFilePath);
    if (uiFile.hasError()) {
        errorString_ = uiFile.error;
        return false;
    }

    dlgen::generator::Generator generator;
    generator.applySettings(dlgen::core::Settings());
    generator.setTargetPath(QStringLiteral("./output"));
    if (!generator.generate(uiFile)) {
        errorString_ = QStringLiteral("Could not generate output from UI file");
        return false;
    }

    return true;
}

} // namespace dlgen::core
