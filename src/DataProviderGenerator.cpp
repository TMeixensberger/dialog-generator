#include "DataProviderGenerator.h"

namespace dlgen::generator {

bool DataProviderGenerator::generate(const ::dlgen::core::UiFile &uiFile) {
    // TODO: implement data-provider-specific generation logic

    // define an empty keyword list for template validation
    QStringList requiredKeywords; // empty list

    // validate the configured template for this generator
    if (!checkTemplate(requiredKeywords, settings_.templates.DataProvider)) {
        return false; // missing required keywords (none defined -> will pass)
    }

    (void)uiFile; // suppress unused parameter warning
    return false;
}

} // namespace dlgen::generator
