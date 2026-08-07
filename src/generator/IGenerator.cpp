#include "IGenerator.h"

namespace dlgen::generator {

IGenerator &IGenerator::applySettings(const Settings &s) {
    settings_ = s;
    return *this;
}

IGenerator &IGenerator::setTargetPath(const QString &path) {
    targetPath_ = path;
    return *this;
}

QString IGenerator::getTargetPath() const {
    return targetPath_;
}

bool IGenerator::toFile(const QString &content, const QString &filename) {
    QString path = getTargetPath();
    if (path.isEmpty()) return false;
    if (filename.isEmpty()) return false;

    QDir dir(path);
    QString full = dir.filePath(filename);
    QFile f(full);
    if (!f.open(QIODevice::WriteOnly | QIODevice::Truncate)) return false;

    QTextStream out(&f);
    out << content;
    f.close();
    return true;
}

IGenerator::KeywordValues IGenerator::keywordValues() const {
    KeywordValues values;
    values.insert("$DEBUG$", []() { return QStringLiteral("debug"); });
    values.insert("$PROJECT$", [this]() { return settings_.project; });
    values.insert("$PACKAGE$", [this]() { return settings_.package; });
    values.insert("$COPYRIGHT$", [this]() { return settings_.copyright; });
    return values;
}

QString IGenerator::fillTemplate(const QString &templ, const KeywordValues &keywordValues) const {
    QString result = templ;
    for (auto it = keywordValues.constBegin(); it != keywordValues.constEnd(); ++it) {
        const QString &key = it.key();
        const KeywordValueGenerator &producer = it.value();
        QString val;
        if (producer) {
            val = producer();
        }
        result.replace(key, val);
    }
    return result;
}

bool IGenerator::checkTemplate(const QStringList &required, const QString &templ) const {
    QStringList all = required;
    const QStringList globals = keywordValues().keys();
    for (const QString &gk : globals) {
        if (!all.contains(gk)) all.append(gk);
    }
    for (const QString &kw : all) {
        if (!templ.contains(kw)) return false;
    }
    return true;
}

} // namespace dlgen::generator
