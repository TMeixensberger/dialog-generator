#include "DialogGenerator.h"
#include <functional>
#include <iostream>

using KeywordValueGenerator = std::function<QString()>;
using KeywordValues = QMap<QString, KeywordValueGenerator>;

namespace dlgen::generator {

bool DialogGenerator::generate(const ::dlgen::core::UiFile &uiFile) {

    // validate the configured template for this generator
    if (!checkTemplate(keywordValues().keys(), settings_.templates.Dialog)) {
        return false; // missing required keywords (none defined -> will pass)
    }

    auto generated = fillTemplate(settings_.templates.Dialog, keywordValues());
    
    std::cout << "Generated content:\n" << generated.toStdString() << std::endl;
    //toFile(generated);

    return true;
}

KeywordValues DialogGenerator::keywordValues() const {
    KeywordValues values = IGenerator::keywordValues();
    
    values.insert("$NAME$", [this]() { return settings_.name; });
    values.insert("$NAMESPACE$", debug());
    values.insert("$ROLES$", debug());
    values.insert("$WIDGETS$", debug());
    return values;
} 
} // namespace dlgen::generator
