#pragma once

#include <QString>
#include <vector>
#include <memory>

#include "UiFile.h"
#include "Settings.h"
#include "IGenerator.h"

namespace dlgen::generator {

/**
 * @brief Code/asset generator that emits files from a parsed UI description
 * (dlgen::core::UiFile).
 */
class Generator : public IGenerator {
public:
    Generator();

    Generator &applySettings(const Settings &s) override { settings_ = s; return *this; }
    Generator &setTargetPath(const QString &path) override { targetPath_ = path; return *this; }
    Generator &add(IGenerator *g) { gens_.emplace_back(g); return *this; }

    bool generate(const ::dlgen::core::UiFile &uiFile) override;

    QString targetFile() const override { return QStringLiteral("Generator"); }
    QString getTargetPath() const override { return targetPath_; }

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
    std::vector<std::unique_ptr<IGenerator>> gens_;
};

} // namespace dlgen::generator
