#pragma once

#include <QString>

#include "IGenerator.h"
#include "Settings.h"
#include "UiFile.h"

namespace dlgen::generator {

/**
 * @brief Specialized generator for persistor-based output.
 */
class PersistorGenerator : public IGenerator {
public:
    PersistorGenerator() = default;

    PersistorGenerator &applySettings(const Settings &s) override { settings_ = s; return *this; }
    PersistorGenerator &setTargetPath(const QString &path) override { targetPath_ = path; return *this; }

    bool generate(const ::dlgen::core::UiFile &uiFile) override;

    QString targetFile() const override { return QStringLiteral("PersistorGenerator"); }
    QString getTargetPath() const override { return targetPath_; }

private:
    Settings settings_;
    QString targetPath_;
};

} // namespace dlgen::generator
