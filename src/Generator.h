#pragma once

#include <QString>

#include "UiFile.h"
#include "Settings.h"
#include "IGenerator.h"

namespace dlgen::generator {

/**
 * @brief Code/asset generator that emits files from a parsed UI description
 * (dlgen::core::UiFile).
 *
 * The Generator class is designed to produce one or multiple output files
 * under the provided target location. The generate() method performs the
 * generation and returns true on success. Settings may be applied using the
 * builder-style applySettings() method.
 */
class Generator : public IGenerator {
public:
    Generator() = default;

    /**
     * @brief Apply generator settings using a builder-style call.
     *
     * Example: Generator g; g.applySettings(settings).setTargetPath(path).generate(ui);
     *
     * @param s Settings to apply
     * @return reference to *this for chaining
     */
    Generator &applySettings(const Settings &s) override { settings_ = s; return *this; }

    /**
     * @brief Set the target path (directory or file) where files will be generated.
     *
     * This may be called in builder-style chaining before generate().
     *
     * @param path Target directory or file path
     * @return reference to *this for chaining
     */
    Generator &setTargetPath(const QString &path) override { targetPath_ = path; return *this; }

    /**
     * @brief Generate output for the provided uiFile using the previously set target path.
     *
     * The target path must have been set via setTargetPath() prior to calling
     * this method. If it is empty, generation fails.
     *
     * @param uiFile Parsed UI file to generate from
     * @return true on success, false on failure
     */
    bool generate(const ::dlgen::core::UiFile &uiFile) override;

    /**
     * @brief Builder DSL for constructing a configured Generator in a fluent style.
     *
     * Example:
     *   auto gen = Generator::Builder().settings(s).targetPath(p).build();
     */
    class Builder {
    public:
        Builder() = default;
        Builder &settings(const Settings &s) { settings_ = s; return *this; }
        Builder &targetPath(const QString &p) { targetPath_ = p; return *this; }
        Generator build() const {
            Generator g;
            g.settings_ = settings_;
            g.targetPath_ = targetPath_;
            return g;
        }
        // Convenience: build and directly generate
        bool generate(const ::dlgen::core::UiFile &uiFile) const {
            Generator g = build();
            return g.generate(uiFile);
        }
    private:
        Settings settings_;
        QString targetPath_;
    };

private:
    Settings settings_;
    QString targetPath_;
};

} // namespace dlgen::generator
