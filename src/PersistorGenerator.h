#pragma once

#include <QString>

#include "IGenerator.h"
#include "Settings.h"
#include "UiFile.h"

namespace dlgen::generator {

/**
 * @brief Specialized generator for persistor-based output.
 *
 * PersistorGenerator implements the IGenerator interface. The generate method is
 * intentionally left empty for you to implement the specific persistor-generation
 * logic.
 */
class PersistorGenerator : public IGenerator {
public:
    PersistorGenerator() = default;

    /**
     * Apply settings (builder style). Returns concrete type reference for chaining.
     */
    PersistorGenerator &applySettings(const Settings &s) override { settings_ = s; return *this; }

    /**
     * Set the target path (directory) for generation.
     */
    PersistorGenerator &setTargetPath(const QString &path) override { targetPath_ = path; return *this; }

    /**
     * Perform generation for the provided UiFile.
     *
     * Implementation intentionally left empty — fill in persistor-specific
     * generation steps here.
     */
    bool generate(const ::dlgen::core::UiFile &uiFile) override;

    QString targetFile() const override { return QStringLiteral("PersistorGenerator"); }
    QString getTargetPath() const override { return targetPath_; }

private:
    Settings settings_;
    QString targetPath_;
};

} // namespace dlgen::generator
