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
#include <vector>

using namespace dlgen::generator;

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

    // Create a list of IGenerator instances and populate with all available generators
    DialogGenerator dlg;
    FactoryGenerator factory;
    PersistorGenerator persistor;
    DataProviderGenerator dataProvider;

    std::vector<IGenerator*> gens;
    gens.push_back(&dlg);
    gens.push_back(&factory);
    gens.push_back(&persistor);
    gens.push_back(&dataProvider);

    // Loop over each generator, apply settings, set target path and invoke generate
    for (IGenerator *g : gens) {
        if (!g) continue;
        g->applySettings(settings_).setTargetPath(targetPath_);
        bool ok = g->generate(uiFile);
        if (!ok) return false; // stop on first failure
    }
    return true;
}
