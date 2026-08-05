#pragma once

#include <QString>
#include "Settings.h"
#include "UiFile.h"

namespace dlgen::generator {

/**
 * @brief Interface for generators.
 *
 * Provides a minimal builder-style interface to configure a generator.
 */
class IGenerator {
public:
    virtual ~IGenerator() = default;

    /**
     * @brief Apply generator settings using a builder-style call.
     * @param s Settings to apply
     * @return reference to *this for chaining
     */
    virtual IGenerator &applySettings(const Settings &s) = 0;

    /**
     * @brief Set the target path (directory or file) where files will be generated.
     * @param path Target directory or file path
     * @return reference to *this for chaining
     */
    virtual IGenerator &setTargetPath(const QString &path) = 0;

    /**
     * @brief Perform generation for the provided parsed UiFile.
     * @param uiFile Parsed UI file to generate from
     * @return true on success, false on failure
     */
    virtual bool generate(const ::dlgen::core::UiFile &uiFile) = 0;
};

} // namespace dlgen::generator
