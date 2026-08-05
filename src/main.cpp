#include <QApplication>
#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include <QFileDialog>

#include <iostream>
#include <ranges>
#include <functional>

#include "Parser.h"
#include "ui_MainWindow.h"

namespace {

// Private helper: print a parsed UiFile to stdout.
// The function lives in an anonymous namespace so it is not exported.
void printUiFile(const dlgen::core::UiFile &uiFile) {
    // Configure how deep the traversal should descend. Set to -1 for unlimited.
    const int maxDepth = 5;

    std::function<void(const dlgen::core::Widget&, int)> printRec;
    printRec = [&](const dlgen::core::Widget &w, int depth) {
        for (int i = 0; i < depth; ++i) std::cout << "  ";

        if (depth == 0)
            std::cout << "Top-level widget: ";
        else
            std::cout << "Child widget: ";

        std::cout << w.className.toStdString();
        if (!w.name.isEmpty()) std::cout << " (" << w.name.toStdString() << ")";
        std::cout << '\n';

        if (maxDepth >= 0 && depth >= maxDepth) return;
        for (const auto &child : w.children) printRec(child, depth + 1);
    };

    for (const auto &w : uiFile.topLevelWidgets) printRec(w, 0);
}

} // anonymous

class MainWindow : public QMainWindow {

public:
    MainWindow(QWidget *parent = nullptr) : QMainWindow(parent) {
        ui.setupUi(this);
        // Connect pushButton_2 to open a file selection dialog for .ui files
        connect(ui.pushButton_2, &QPushButton::clicked, this, [this]() {
            const QString filter = QStringLiteral("UI files (*.ui)");
            QString file = QFileDialog::getOpenFileName(this, QStringLiteral("Select UI File"), QString(), filter);
            if (!file.isEmpty()) {
                // place selected file path into the designated line edit
                auto uiFile = dlgen::parser::parseUiFile(file);

                // Print the parsed UI file using the private helper in the
                // anonymous namespace.
                printUiFile(uiFile);
            }
        });
    }
    
    virtual ~MainWindow(){};

    void createUI() {
    }
protected:
    void showEvent(QShowEvent *) override {
        // Hier kannst du Code einfügen, der ausgeführt werden soll, wenn das Fenster geöffnet wird.
    }

private:
    Ui::MainWindow ui;
};

int main(int argc, char **argv) {
    QApplication app(argc, argv);

    MainWindow window;
    window.createUI();
    window.resize(400, 300); // Setze die Größe des Fensters
    window.show();

    QCoreApplication::exec();
    return 0;
}
