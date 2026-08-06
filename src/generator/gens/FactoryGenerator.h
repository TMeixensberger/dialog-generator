#pragma once

#include <QString>

#include "IGenerator.h"
#include "Settings.h"
#include "UiFile.h"

namespace dlgen::generator {

/**
 * @brief Specialized generator for factory-based output.
 */
class FactoryGenerator : public IGenerator {
public:
    FactoryGenerator() = default;

    bool generate(const ::dlgen::core::UiFile &uiFile) override;

    KeywordValues keywordValues() const override { return {}; }

    QString targetFile() const override { return QStringLiteral("FactoryGenerator"); }

private:
    // settings_ and targetPath_ are provided by the IGenerator base class
};

} // namespace dlgen::generator
