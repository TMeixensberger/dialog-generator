#include "DialogGenerator.h"
#include <iostream>

namespace dlgen::generator {

bool DialogGenerator::generate(const ::dlgen::core::UiFile &uiFile) {

    // validate the configured template for this generator
    if (!checkTemplate(keywordValues().keys(), settings_.templates.Dialog)) {
        return false; // missing required keywords (none defined -> will pass)
    }

    auto generated = fillTemplate(settings_.templates.Dialog, keywordValues());
    
    std::cout << "Generated content:\n" << generated.toStdString() << std::endl;
    //toFile(generated, "DialogGenerator.txt");

    return true;
}

KeywordValues DialogGenerator::keywordValues() const {
    KeywordValues values = IGenerator::keywordValues();

    values.insert("$NAME$", settings_.name);
    values.insert("$NAMESPACE$", settings_.dialogNamespace);
    values.insert("$ROLES$", QStringLiteral(""));
    values.insert("$WIDGETS$", QStringLiteral(""));

    return values;
} 
} // namespace dlgen::generator
