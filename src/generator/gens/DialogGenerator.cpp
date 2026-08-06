#include "DialogGenerator.h"

namespace dlgen::generator {

bool DialogGenerator::generate(const ::dlgen::core::UiFile &uiFile) {
    // TODO: implement dialog-specific generation logic

    // define an empty keyword list for template validation
    QStringList requiredKeywords = { "$DIALOG$" }; // empty list

    // validate the configured template for this generator
    if (!checkTemplate(requiredKeywords, settings_.templates.Dialog)) {
        return false; // missing required keywords (none defined -> will pass)
    }

    (void)uiFile; // suppress unused parameter warning
    return false;
}

} // namespace dlgen::generator
