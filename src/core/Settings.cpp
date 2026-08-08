#include "Settings.h"

#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QSaveFile>

namespace dlgen::core {

namespace {

QJsonObject toJson(const Settings &settings) {
    QJsonObject templates;
    templates.insert(QStringLiteral("Dialog"), settings.templates.Dialog);
    templates.insert(QStringLiteral("Factory"), settings.templates.Factory);
    templates.insert(QStringLiteral("DataProvider"), settings.templates.DataProvider);
    templates.insert(QStringLiteral("Persistor"), settings.templates.Persistor);

    QJsonObject root;
    root.insert(QStringLiteral("overwriteExisting"), settings.overwriteExisting);
    root.insert(QStringLiteral("maxDepth"), settings.maxDepth);
    root.insert(QStringLiteral("includeUnnamed"), settings.includeUnnamed);
    root.insert(QStringLiteral("templates"), templates);
    root.insert(QStringLiteral("project"), settings.project);
    root.insert(QStringLiteral("package"), settings.package);
    root.insert(QStringLiteral("copyright"), settings.copyright);
    root.insert(QStringLiteral("name"), settings.name);
    root.insert(QStringLiteral("dialogNamespace"), settings.dialogNamespace);
    root.insert(QStringLiteral("uiFilePath"), settings.uiFilePath);
    return root;
}

bool fromJson(const QJsonObject &root, Settings *settings) {
    if (settings == nullptr) {
        return false;
    }

    Settings result;
    result.overwriteExisting = root.value(QStringLiteral("overwriteExisting")).toBool(result.overwriteExisting);
    result.maxDepth = root.value(QStringLiteral("maxDepth")).toInt(result.maxDepth);
    result.includeUnnamed = root.value(QStringLiteral("includeUnnamed")).toBool(result.includeUnnamed);

    const QJsonObject templates = root.value(QStringLiteral("templates")).toObject();
    result.templates.Dialog = templates.value(QStringLiteral("Dialog")).toString(result.templates.Dialog);
    result.templates.Factory = templates.value(QStringLiteral("Factory")).toString(result.templates.Factory);
    result.templates.DataProvider = templates.value(QStringLiteral("DataProvider")).toString(result.templates.DataProvider);
    result.templates.Persistor = templates.value(QStringLiteral("Persistor")).toString(result.templates.Persistor);

    result.project = root.value(QStringLiteral("project")).toString(result.project);
    result.package = root.value(QStringLiteral("package")).toString(result.package);
    result.copyright = root.value(QStringLiteral("copyright")).toString(result.copyright);
    result.name = root.value(QStringLiteral("name")).toString(result.name);
    result.dialogNamespace = root.value(QStringLiteral("dialogNamespace")).toString(result.dialogNamespace);
    result.uiFilePath = root.value(QStringLiteral("uiFilePath")).toString(result.uiFilePath);

    *settings = result;
    return true;
}

} // namespace

bool SettingsStorage::read(const QString &filePath, Settings *settings, QString *errorString) {
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) {
        if (errorString != nullptr) {
            *errorString = QStringLiteral("failed to open '%1' for reading").arg(filePath);
        }
        return false;
    }

    QJsonParseError parseError;
    const QJsonDocument document = QJsonDocument::fromJson(file.readAll(), &parseError);
    if (parseError.error != QJsonParseError::NoError || !document.isObject()) {
        if (errorString != nullptr) {
            *errorString = parseError.error != QJsonParseError::NoError
                ? parseError.errorString()
                : QStringLiteral("settings file must contain a JSON object");
        }
        return false;
    }

    if (!fromJson(document.object(), settings)) {
        if (errorString != nullptr) {
            *errorString = QStringLiteral("invalid settings output parameter");
        }
        return false;
    }

    if (errorString != nullptr) {
        errorString->clear();
    }
    return true;
}

bool SettingsStorage::write(const QString &filePath, const Settings &settings, QString *errorString) {
    QSaveFile file(filePath);
    if (!file.open(QIODevice::WriteOnly)) {
        if (errorString != nullptr) {
            *errorString = QStringLiteral("failed to open '%1' for writing").arg(filePath);
        }
        return false;
    }

    const QByteArray jsonBytes = QJsonDocument(toJson(settings)).toJson(QJsonDocument::Indented);
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

    if (errorString != nullptr) {
        errorString->clear();
    }
    return true;
}

} // namespace dlgen::core
