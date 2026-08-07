#pragma once

#include <QJsonObject>
#include <QJsonValue>
#include <QString>
#include <QStringList>

namespace dlgen::core {

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
