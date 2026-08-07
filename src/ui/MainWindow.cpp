#include "MainWindow.h"

#include <iostream>
#include <QPushButton>
#include <QFileDialog>

#include "Parser.h"
#include "Generator.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    ui.setupUi(this);
    connect(ui.pushButton_2, &QPushButton::clicked, this, &MainWindow::addUiFile);
}

MainWindow::~MainWindow() {}

void MainWindow::addUiFile() {
    const QString filter = QStringLiteral("UI files (*.ui)");
    QString file = QFileDialog::getOpenFileName(this, QStringLiteral("Select UI File"), QString(), filter);
    if (!file.isEmpty()) {
        auto uiFile = dlgen::parser::parseUiFile(file);

        dlgen::generator::Generator generator;
        generator.applySettings(dlgen::generator::Settings());
        generator.setTargetPath(QStringLiteral("./output"));
        generator.generate(uiFile);

        uiFile.forEachNamedChild([](const QString &cls, const QString &name){
            std::cout << cls.toStdString() << " (" << name.toStdString() << ")\n";
        });
    }
}
