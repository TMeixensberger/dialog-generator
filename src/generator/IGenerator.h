#pragma once

#include <QString>
#include <QFile>
#include <QTextStream>
#include <QDir>
#include <QStringList>
#include <QMap>
#include <functional>
#include "Settings.h"
#include "UiFile.h"

namespace dlgen::generator {

/**
 * @brief Interface for generators.
 *
 * Provides a minimal builder-style interface to configure a generator.
 */
class IGenerator {
public:
    using KeywordValueGenerator = std::function<QString()>;
    using KeywordValues = QMap<QString, KeywordValueGenerator>;

    virtual ~IGenerator() = default;

    /**
     * @brief Apply generator settings using a builder-style call.
     * @param s Settings to apply
     * @return reference to *this for chaining
     */
    virtual IGenerator &applySettings(const Settings &s) { settings_ = s; return *this; }

    /**
     * @brief Set the target path (directory or file) where files will be generated.
     * @param path Target directory or file path
     * @return reference to *this for chaining
     */
    virtual IGenerator &setTargetPath(const QString &path) { targetPath_ = path; return *this; }

    /**
     * @brief Return the target file name for this generator.
     *
     * Implementations should return the file name (or identifier) that will be
     * appended to the configured target path when writing output. For example,
     * a DialogGenerator may return "DialogGenerator" or a specific filename.
     */
    virtual QString targetFile() const = 0;

    /**
     * @brief Return the currently configured target path.
     *
     * Implementations must provide access to the target path previously set
     * via setTargetPath(). This is used by the provided helper to compute
     * the final path when writing files.
     */
    virtual QString getTargetPath() const { return targetPath_; }

    /**
     * @brief Convenience helper to write provided content into the configured target file.
     *
     * This implemented helper uses getTargetPath() and targetFile() to form the
     * destination path and writes `content` to that file. Returns true on success.
     *
     * @param content Text content to write to the target file
     * @return true if the file was written successfully, false otherwise
     */
    bool toFile(const QString &content) {
        QString path = getTargetPath();
        if (path.isEmpty()) return false;
        QString fname = targetFile();
        if (fname.isEmpty()) return false;
        QDir dir(path);
        QString full = dir.filePath(fname);
        QFile f(full);
        if (!f.open(QIODevice::WriteOnly | QIODevice::Truncate)) return false;
        QTextStream out(&f);
        out << content;
        f.close();
        return true;
    }

    /**
     * @brief Return a list of global keywords that should always be present in templates.
     *
     * Default implementation returns an empty list; concrete generators may
     * override to provide global keywords relevant to all templates.
     */
    virtual QStringList globalKeywords() const { return keywordValues().keys(); }

    /**
     * @brief Return a debug keyword value generator.
     *
     * The returned callable matches the value type of keywordValues entries
     * used by concrete generators. It returns a QString when invoked.
     */
    /**
     * @brief Return the set of keyword value generators for this generator.
     *
     * Concrete generators may override this to provide generator-specific
     * keyword replacement values. The default implementation returns a set of
     * globally supported keyword generators.
     */
    virtual KeywordValues keywordValues() const {
        KeywordValues values;
        values.insert("$DEBUG$", []() { return QStringLiteral("debug"); });
        values.insert("$PROJECT$", [this]() { return settings_.project; });
        values.insert("$PACKAGE$", [this]() { return settings_.package; });
        values.insert("$COPYRIGHT$", [this]() { return settings_.copyright; });
        return values;
    }

    /**
     * @brief Replace keywords in a template using the provided value generators.
     *
     * For each entry in `keywordValues` the key is searched in `templ` and
     * replaced with the QString produced by invoking the corresponding callable.
     * Returns the resulting filled template.
     */
    QString fillTemplate(const QString &templ, const KeywordValues &keywordValues) const {
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

    /**
     * @brief Check that the provided template contains all required keywords.
     *        The check also includes any global keywords returned by globalKeywords().
     * @param required list of keywords that must be present in the template
     * @param templ the template string to check
     * @return true if all keywords are present, false otherwise
     */
    bool checkTemplate(const QStringList &required, const QString &templ) const {
        QStringList all = required;
        const QStringList globals = globalKeywords();
        for (const QString &gk : globals) {
            if (!all.contains(gk)) all.append(gk);
        }
        for (const QString &kw : all) {
            if (!templ.contains(kw)) return false;
        }
        return true;
    }

    /**
     * @brief Perform generation for the provided parsed UiFile.
     * @param uiFile Parsed UI file to generate from
     * @return true on success, false on failure
     */
    virtual bool generate(const ::dlgen::core::UiFile &uiFile) = 0;

protected:
    Settings settings_;
    QString targetPath_;
};

} // namespace dlgen::generator
