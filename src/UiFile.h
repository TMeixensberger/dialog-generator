#pragma once

#include <QString>
#include <QVector>

namespace dlgen::core {

/**
 * @brief Represents a widget parsed from a Qt .ui XML file.
 *
 * Contains the widget class name, optional object name, and any nested child
 * widgets. This is a lightweight value type used to represent the hierarchy
 * of <widget> elements found in a .ui file.
 */
struct Widget {
    QString className; /**< Widget class, e.g. "QPushButton" */
    QString name;      /**< Optional object name (the "name" attribute) */
    QVector<Widget> children; /**< Child widgets (nested <widget> elements) */
};

/**
 * @brief Result of parsing a .ui file.
 *
 * Contains the top-level widgets and an error message when parsing failed.
 */
struct UiFile {
    QVector<Widget> topLevelWidgets; /**< Top-level <widget> elements */
    QString error; /**< Non-empty when a parse error occurred */

    /**
     * @brief Convenience check whether parsing failed.
     * @return true if an error message is present
     */
    bool hasError() const { return !error.isEmpty(); }
};

} // namespace dlgen::core
