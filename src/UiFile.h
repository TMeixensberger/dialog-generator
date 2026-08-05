#pragma once

#include <QString>
#include <QVector>
#include <QPair>
#include <QSet>
#include <functional>

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
 *
 * This type also provides utility functions to operate on the parsed tree.
 */
class UiFile {
public:
    QVector<Widget> topLevelWidgets; /**< Top-level <widget> elements */
    QString error; /**< Non-empty when a parse error is present */

    /**
     * @brief Convenience check whether parsing failed.
     * @return true if an error message is present
     */
    bool hasError() const { return !error.isEmpty(); }

    /**
     * @brief Aggregate a flat list of (className, name) pairs for all widgets
     * in the parsed tree.
     *
     * Widgets that do not have a name (empty name) are excluded. Duplicate
     * entries are deduplicated by the widget name: only the first occurrence
     * of a given name is included in the result.
     *
     * @return QVector<QPair<QString,QString>> list of (className, name)
     */
    QVector<QPair<QString, QString>> aggregateChildrenByName() const {
        QVector<QPair<QString, QString>> result;
        QSet<QString> seenNames;

        std::function<void(const Widget&)> visit = [&](const Widget &w) {
            if (!w.name.isEmpty()) {
                if (!seenNames.contains(w.name)) {
                    seenNames.insert(w.name);
                    result.append(qMakePair(w.className, w.name));
                }
            }
            for (const auto &child : w.children) visit(child);
        };

        for (const auto &w : topLevelWidgets) visit(w);
        return result;
    }

    /**
     * @brief Visit each named child widget and invoke the provided callback.
     *
     * The callback is invoked with (className, name) for each widget that
     * has a non-empty name. Duplicate names are filtered: only the first
     * occurrence of a particular name will be visited.
     *
     * @param visitor Callable invoked for each (className, name) pair
     */
    void forEachNamedChild(const std::function<void(const QString&, const QString&)> &visitor) const {
        QSet<QString> seenNames;
        std::function<void(const Widget&)> visit = [&](const Widget &w) {
            if (!w.name.isEmpty()) {
                if (!seenNames.contains(w.name)) {
                    seenNames.insert(w.name);
                    visitor(w.className, w.name);
                }
            }
            for (const auto &child : w.children) visit(child);
        };
        for (const auto &w : topLevelWidgets) visit(w);
    }
};

} // namespace dlgen::core
