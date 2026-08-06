#pragma once

#include <QString>

namespace dlgen::generator {

/**
 * @brief Default template strings for concrete generators.
 *
 * The Template class holds inline const QString members for each concrete
 * generator in src/generator/gens. These are empty by default and can be
 * referenced by generators when a default template is required.
 */
class Template {
public:
    inline static const QString DialogGenerator = QStringLiteral(R"(
$DEBUG$
/**
 * @file
 * @par Project: $PROJECT$
 * @par Package: $PACKAGE$
 * 
 * @brief $BRIEF$
 * 
 * @copyright $COPYRIGHT$
 * All rights reserved.
 */

#ifndef I$NAME$DIALOG_HPP
#define I$NAME$DIALOG_HPP

#include <QDialog>
#include <QWidget>

namespace $NAMESPACE$ {

/** 
 * @brief Interface for $NAME$ dialogs.
*/
class I$NAME$Dialog : public QDialog {
    Q_OBJECT

    public:
    /**
     *  @brief Constructor for I$NAME$Dialog.
     *  @param parent The parent widget for the dialog.
     */
    explicit I$NAME$Dialog(QWidget *parent = nullptr);

    /**
     *  @brief Destructor for I$NAME$Dialog.
     */
    virtual ~I$NAME$Dialog();

    enum Roles {
        EnabledRole = Qt::UserRole + 1, /**< Role for the enabled state of the dialog. */
        $ROLES$
    };

    enum Widgets {
        $WIDGETS$,
        Count ///< Last entry to indicate the number of widgets in the enum
    };
};
} // namespace $NAMESPACE$

#endif // I$NAME$DIALOG_HPP
)");
    inline static const QString FactoryGenerator = QStringLiteral("");
    inline static const QString DataProviderGenerator = QStringLiteral("");
    inline static const QString PersistorGenerator = QStringLiteral("");
};

} // namespace dlgen::generator
