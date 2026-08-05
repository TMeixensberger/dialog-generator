#include "Parser.h"

#include <QXmlStreamReader>
#include <QTextStream>
#include <QFile>

namespace {

// Recursively parse a <widget> element at the current reader position and
// return a Widget value. The QXmlStreamReader is advanced past the matching
// </widget> end element on return.
static dlgen::core::Widget parseWidgetRec(QXmlStreamReader &xml) {
    dlgen::core::Widget w;
    QXmlStreamAttributes attrs = xml.attributes();
    w.className = attrs.value("class").toString();
    w.name = attrs.value("name").toString();

    // read until matching </widget>
    while (!xml.atEnd()) {
        xml.readNext();
        if (xml.isStartElement()) {
            if (xml.name() == QLatin1String("widget")) {
                // recurse into child widget
                w.children.append(parseWidgetRec(xml));
            }
            // ignore other start elements
        } else if (xml.isEndElement() && xml.name() == QLatin1String("widget")) {
            // end of this widget
            break;
        }
    }

    return w;
}

// Internal device-based parser. Kept in the anonymous namespace so it is not
// exposed in the public header: callers should use parseUiFile(const QString&).
static dlgen::core::UiFile parseUiFromDevice(QIODevice *device) {
    dlgen::core::UiFile result;
    if (!device || !device->isOpen()) {
        result.error = QStringLiteral("device not open");
        return result;
    }

    QXmlStreamReader xml(device);

    while (!xml.atEnd()) {
        xml.readNext();
        if (xml.isStartElement()) {
            if (xml.name() == QLatin1String("widget")) {
                result.topLevelWidgets.append(parseWidgetRec(xml));
            }
        }
    }

    if (xml.hasError()) {
        result.error = xml.errorString();
    }

    return result;
}

} // anonymous

namespace dlgen::parser {

::dlgen::core::UiFile parseUiFile(const QString &filename) {
    QFile file(filename);
    ::dlgen::core::UiFile result;
    if (!file.open(QIODevice::ReadOnly)) {
        result.error = QStringLiteral("failed to open file");
        return result;
    }
    // call internal device-based parser
    return parseUiFromDevice(&file);
}

} // namespace dlgen::parser
