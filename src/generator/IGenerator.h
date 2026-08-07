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
    virtual IGenerator &applySettings(const Settings &s);

    /**
     * @brief Set the target path (directory or file) where files will be generated.
     * @param path Target directory or file path
     * @return reference to *this for chaining
     */
    virtual IGenerator &setTargetPath(const QString &path);

    /**
     * @brief Return the currently configured target path.
     *
     * Implementations must provide access to the target path previously set
     * via setTargetPath(). This is used by the provided helper to compute
     * the full output path when writing files.
     */
    virtual QString getTargetPath() const;

    /**
     * @brief Convenience helper to write provided content into a file under the configured target path.
     *
     * This implemented helper uses getTargetPath() and the provided `filename`
     * to form the destination path and writes `content` to that file.
     * Returns true on success.
     *
     * @param content Text content to write to the target file
     * @param filename Name of the file to write inside the configured target path
     * @return true if the file was written successfully, false otherwise
     */
    bool toFile(const QString &content, const QString &filename);

    /**
     * @brief Return the set of keyword value generators for this generator.
     *
     * Concrete generators may override this to provide generator-specific
     * keyword replacement values. The default implementation returns a set of
     * globally supported keyword generators.
     */
    virtual KeywordValues keywordValues() const;

    /**
     * @brief Replace keywords in a template using the provided value generators.
     *
     * For each entry in `keywordValues` the key is searched in `templ` and
     * replaced with the QString produced by invoking the corresponding callable.
     * Returns the resulting filled template.
     */
    QString fillTemplate(const QString &templ, const KeywordValues &keywordValues) const;

    /**
     * @brief Check that the provided template contains all required keywords.
     * @param required list of keywords that must be present in the template
     * @param templ the template string to check
     * @return true if all keywords are present, false otherwise
     */
    bool checkTemplate(const QStringList &required, const QString &templ) const;

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
