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
#include "gens/DefaultTemplates.h"

    struct Templates {
        QString Dialog = Template::DialogGenerator; /**< Template content for Dialog generator (default from gens::DefaultTemplates) */
        QString Factory = Template::FactoryGenerator; /**< Template content for Factory generator (default from gens::DefaultTemplates) */
        QString DataProvider = Template::DataProviderGenerator; /**< Template content for DataProvider generator (default from gens::DefaultTemplates) */
        QString Persistor = Template::PersistorGenerator; /**< Template content for Persistor generator (default from gens::DefaultTemplates) */
    } templates; /**< Instance holding all generator templates */
};

} // namespace dlgen::generator
