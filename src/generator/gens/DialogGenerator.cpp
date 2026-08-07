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

DialogGenerator::KeywordValues DialogGenerator::keywordValues() const {
    DialogGenerator::KeywordValues values = IGenerator::keywordValues();

    values.insert("$NAME$", settings_.name);
    values.insert("$NAMESPACE$", settings_.dialogNamespace);
    values.insert("$ROLES$", QStringLiteral(""));
    values.insert("$WIDGETS$", QStringLiteral(""));

    auto debugValue = [](const KeywordValues &vals) {
        QStringList lines;
        lines.append(QStringLiteral("/*"));
        for (auto it = vals.constBegin(); it != vals.constEnd(); ++it) {
            lines.append(QStringLiteral(" * %1: %2").arg(it.key(), it.value()));
        }
        lines.append(QStringLiteral(" */"));
        return lines.join(QLatin1Char('\n'));
    }(values);

    values.insert("$DEBUG$", debugValue);

    return values;
} 
} // namespace dlgen::generator
