#include "Generator.h"
#include "DialogGenerator.h"
#include "FactoryGenerator.h"
#include "PersistorGenerator.h"
#include "DataProviderGenerator.h"

#include <QTextStream>
#include <QFile>
#include <QFileInfo>
#include <QDir>
#include <iostream>

using namespace dlgen::generator;

Generator::Generator() {
    // prefill with the available concrete generators
    gens_.emplace_back(std::make_unique<DialogGenerator>());
    gens_.emplace_back(std::make_unique<FactoryGenerator>());
    gens_.emplace_back(std::make_unique<PersistorGenerator>());
    gens_.emplace_back(std::make_unique<DataProviderGenerator>());
}

bool Generator::generate(const ::dlgen::core::UiFile &uiFile) {
    // targetPath_ must be set
    if (targetPath_.isEmpty()) return false;

    // Ensure targetPath_ is a directory (if it exists and is a file -> fail)
    QFileInfo info(targetPath_);
    if (info.exists() && info.isFile()) return false;

    if (!info.exists()) {
        // create directory
        if (!QDir().mkpath(targetPath_)) return false;
    }

    // Loop over each generator, apply settings, set target path and invoke generate
    for (const auto &gptr : gens_) {
        IGenerator *g = gptr.get();
        if (!g) continue;
        g->applySettings(settings_).setTargetPath(targetPath_);
        bool ok = g->generate(uiFile);
        if (!ok) return false; // stop on first failure
    }
    return true;
}
