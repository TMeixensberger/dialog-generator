#include "PersistorGenerator.h"

namespace dlgen::generator {

bool PersistorGenerator::generate(const ::dlgen::core::UiFile &uiFile) {
    // TODO: implement persistor-specific generation logic

    // define an empty keyword list for template validation
    QStringList requiredKeywords; // empty list

    // validate the configured template for this generator
    if (!checkTemplate(requiredKeywords, settings_.templates.Persistor)) {
        return false; // missing required keywords (none defined -> will pass)
    }

    (void)uiFile; // suppress unused parameter warning
    return false;
}

} // namespace dlgen::generator
