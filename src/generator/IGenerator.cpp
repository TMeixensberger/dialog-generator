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
    values.insert("$PROJECT$", settings_.project);
    values.insert("$PACKAGE$", settings_.package);
    values.insert("$COPYRIGHT$", settings_.copyright);
    return values;
}

QString IGenerator::fillTemplate(const QString &templ, const KeywordValues &keywordValues) const {
    QString result = templ;
    for (auto it = keywordValues.constBegin(); it != keywordValues.constEnd(); ++it) {
        result.replace(it.key(), it.value());
    }
    return result;
}
 
QString IGenerator::formatDebugComment(const KeywordValues &vals) const {
    QStringList lines;
    lines.append(QStringLiteral("/*"));
    lines.append(QStringLiteral(" * WARNING: The following code is generated and contains debug information."));
    lines.append(QStringLiteral(" *"));
    for (const QString &key : vals.keys()) {
        QString cleanKey = key;
        if (cleanKey.startsWith(QLatin1Char('$')) && cleanKey.endsWith(QLatin1Char('$')) && cleanKey.size() > 2) {
            cleanKey = cleanKey.mid(1, cleanKey.size() - 2);
        }
        lines.append(QStringLiteral(" * %1: %2").arg(cleanKey, vals.value(key)));
    }
    lines.append(QStringLiteral(" */"));
    return lines.join(QLatin1Char('\n'));
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
