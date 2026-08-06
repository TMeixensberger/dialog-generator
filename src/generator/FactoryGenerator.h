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

    FactoryGenerator &applySettings(const Settings &s) override { settings_ = s; return *this; }
    FactoryGenerator &setTargetPath(const QString &path) override { targetPath_ = path; return *this; }

    bool generate(const ::dlgen::core::UiFile &uiFile) override;

    QString targetFile() const override { return QStringLiteral("FactoryGenerator"); }
    QString getTargetPath() const override { return targetPath_; }

private:
    Settings settings_;
    QString targetPath_;
};

} // namespace dlgen::generator
