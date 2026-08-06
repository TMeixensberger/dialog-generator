#include "FactoryGenerator.h"

namespace dlgen::generator {

bool FactoryGenerator::generate(const ::dlgen::core::UiFile &uiFile) {
    // TODO: implement factory-specific generation logic

    // define an empty keyword list for template validation
    QStringList requiredKeywords; // empty list

    // validate the configured template for this generator
    if (!checkTemplate(requiredKeywords, settings_.templates.Factory)) {
        return false; // missing required keywords (none defined -> will pass)
    }

    (void)uiFile; // suppress unused parameter warning
    return false;
}

} // namespace dlgen::generator
