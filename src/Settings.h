#pragma once

#include <QString>

namespace dlgen::generator {

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
        QString Dialog = QString(); /**< Template content for Dialog generator (empty by default) */
        QString Factory = QString(); /**< Template content for Factory generator (empty by default) */
        QString DataProvider = QString(); /**< Template content for DataProvider generator (empty by default) */
        QString Persistor = QString(); /**< Template content for Persistor generator (empty by default) */
    } templates; /**< Instance holding all generator templates */
};

} // namespace dlgen::generator
