#pragma once

#include <QString>

namespace dlgen::core {

/**
 * @brief Settings that control generation behaviour.
 */
struct Settings {
    bool overwriteExisting = true; /**< if false, generation will fail when output files exist */
    int maxDepth = -1; /**< maximum traversal depth for generation (-1 = unlimited) */
    bool includeUnnamed = false; /**< whether unnamed widgets should be included in aggregated outputs */

    /**
     * @brief Templates for different generator outputs.
     *
     * Nested struct grouping template strings used by individual generators.
     */
    struct Templates {
        QString Dialog; /**< Template content for Dialog generator */
        QString Factory; /**< Template content for Factory generator */
        QString DataProvider; /**< Template content for DataProvider generator */
        QString Persistor; /**< Template content for Persistor generator */
    } templates; /**< Instance holding all generator templates */

    // Selected global keyword values used by templates.
    QString project = "PROJECT";   /**< Value used for $PROJECT$ */
    QString package = "PACKAGE";   /**< Value used for $PACKAGE$ */
    QString copyright = "COPYRIGHT"; /**< Value used for $COPYRIGHT$ */
    QString name = "NAME"; /**< Value used for $NAME$ */
    QString dialogNamespace = "NAMESPACE"; /**< Value used for $NAMESPACE$ */
};

/**
 * @brief Reads and writes Settings to disk.
 */
class SettingsStorage {
public:
    static bool read(const QString &filePath, Settings *settings, QString *errorString);
    static bool write(const QString &filePath, const Settings &settings, QString *errorString);
};

} // namespace dlgen::core
