#pragma once

#include <QString>

#include "IGenerator.h"
#include "Settings.h"
#include "UiFile.h"

namespace dlgen::generator {

/**
 * @brief Specialized generator for data-provider-based output.
 *
 * DataProviderGenerator implements the IGenerator interface. The generate method is
 * intentionally left empty for you to implement the specific data-provider-generation
 * logic.
 */
class DataProviderGenerator : public IGenerator {
public:
    DataProviderGenerator() = default;

    /**
     * Apply settings (builder style). Returns concrete type reference for chaining.
     */
    DataProviderGenerator &applySettings(const Settings &s) override { settings_ = s; return *this; }

    /**
     * Set the target path (directory) for generation.
     */
    DataProviderGenerator &setTargetPath(const QString &path) override { targetPath_ = path; return *this; }

    /**
     * Perform generation for the provided UiFile.
     *
     * Implementation intentionally left empty — fill in data-provider-specific
     * generation steps here.
     */
    bool generate(const ::dlgen::core::UiFile &uiFile) override;

private:
    Settings settings_;
    QString targetPath_;
};

} // namespace dlgen::generator
