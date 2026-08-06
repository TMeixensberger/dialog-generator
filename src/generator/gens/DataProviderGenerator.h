#pragma once

#include <QString>

#include "IGenerator.h"
#include "Settings.h"
#include "UiFile.h"

namespace dlgen::generator {

/**
 * @brief Specialized generator for data-provider-based output.
 */
class DataProviderGenerator : public IGenerator {
public:
    DataProviderGenerator() = default;

    bool generate(const ::dlgen::core::UiFile &uiFile) override;

    QString targetFile() const override { return QStringLiteral("DataProviderGenerator"); }

private:
    // settings_ and targetPath_ are provided by the IGenerator base class
};

} // namespace dlgen::generator
