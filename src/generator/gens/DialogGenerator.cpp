#include "DialogGenerator.h"
#include <functional>
#include <iostream>

namespace dlgen::generator {

bool DialogGenerator::generate(const ::dlgen::core::UiFile &uiFile) {
    // TODO: implement dialog-specific generation logic

    // define an empty keyword list for template validation
    QStringList requiredKeywords = { "$NAMESPACE$", "$NAME$", "$ROLES$", "$WIDGETS$" }; // empty list

    // validate the configured template for this generator
    if (!checkTemplate(requiredKeywords, settings_.templates.Dialog)) {
        return false; // missing required keywords (none defined -> will pass)
    }

    QMap<QString, std::function<QString()>> keywordValues;

    keywordValues.insert("$DEBUG$", debug());
    
    auto generated = fillTemplate(settings_.templates.Dialog, keywordValues);
    
    std::cout << "Generated content:\n" << generated.toStdString() << std::endl;
    //toFile(generated);

    return true;
}

} // namespace dlgen::generator
