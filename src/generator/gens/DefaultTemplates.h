#pragma once

#include <QString>

namespace dlgen::generator {

/**
 * @brief Default template strings for concrete generators.
 *
 * The Template class holds inline const QString members for each concrete
 * generator in src/generator/gens. These are empty by default and can be
 * referenced by generators when a default template is required.
 */
class Template {
public:
    inline static const QString DialogGenerator = QStringLiteral("");
    inline static const QString FactoryGenerator = QStringLiteral("");
    inline static const QString DataProviderGenerator = QStringLiteral("");
    inline static const QString PersistorGenerator = QStringLiteral("");
};

} // namespace dlgen::generator
