#pragma once

#include <QString>

#include "IGenerator.h"
#include "Settings.h"
#include "UiFile.h"

namespace dlgen::generator {

/**
 * @brief Specialized generator for dialog-based output.
 */
class DialogGenerator : public IGenerator {
public:
    DialogGenerator() = default;


    bool generate(const ::dlgen::core::UiFile &uiFile) override;

    QString targetFile() const override { return QStringLiteral("DialogGenerator"); }

private:
    // settings_ and targetPath_ are provided by the IGenerator base class
};

} // namespace dlgen::generator
