#pragma once

#include <QString>
#include "gens/DefaultTemplates.h"

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
        QString Dialog = Template::DialogGenerator; /**< Template content for Dialog generator (default from gens::DefaultTemplates) */
        QString Factory = Template::FactoryGenerator; /**< Template content for Factory generator (default from gens::DefaultTemplates) */
        QString DataProvider = Template::DataProviderGenerator; /**< Template content for DataProvider generator (default from gens::DefaultTemplates) */
        QString Persistor = Template::PersistorGenerator; /**< Template content for Persistor generator (default from gens::DefaultTemplates) */
    } templates; /**< Instance holding all generator templates */

    // Selected global keyword values used by templates.
    QString project;   /**< Value used for $PROJECT$ */
    QString package;   /**< Value used for $PACKAGE$ */
    QString copyright; /**< Value used for $COPYRIGHT$ */
    QString name = "TEST"; /**< Value used for $NAME$ */
    QString dialogNamespace; /**< Value used for $NAMESPACE$ */
};

} // namespace dlgen::generator
