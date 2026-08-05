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
};

} // namespace dlgen::generator
