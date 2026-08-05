#pragma once

#include <QString>
#include <QIODevice>

#include "UiFile.h"

namespace dlgen::parser {

/**
 * @brief Parse a Qt Designer .ui XML from the given filename.
 *
 * The function will open the file for reading and parse its contents. On
 * success the returned UiFile will contain the parsed widget hierarchy in
 * topLevelWidgets. On error UiFile::error will contain a diagnostic string
 * describing the failure.
 *
 * @param filename Path to a .ui file to parse
 * @return dlgen::core::UiFile parsed representation or an error
 */
::dlgen::core::UiFile parseUiFile(const QString &filename);

} // namespace dlgen::parser
