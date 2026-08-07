#include "MainWindow.h"

#include <iostream>
#include <QPushButton>
#include <QFileDialog>
#include <QMessageBox>

#include "Project.h"
#include "Parser.h"
#include "Generator.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    ui.setupUi(this);
    connect(ui.pushButton_2, &QPushButton::clicked, this, &MainWindow::addUiFile);
    connect(ui.actionLoadProject, &QAction::triggered, this, &MainWindow::loadProject);
    connect(ui.actionCreateProject, &QAction::triggered, this, &MainWindow::createProject);
    connect(ui.actionSaveProject, &QAction::triggered, this, &MainWindow::saveProject);
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

void MainWindow::loadProject() {
    const QString directory = QFileDialog::getExistingDirectory(this, QStringLiteral("Select Project Directory"));
    if (directory.isEmpty()) {
        return;
    }

    auto project = std::make_unique<dlgen::core::Project>();
    if (!project->load(directory)) {
        QMessageBox::critical(this, QStringLiteral("Failed to load project"), project->errorString());
        return;
    }

    project_ = std::move(project);
}

void MainWindow::createProject() {
    const QString directory = QFileDialog::getExistingDirectory(this, QStringLiteral("Select Directory for New Project"));
    if (directory.isEmpty()) {
        return;
    }

    auto project = std::make_unique<dlgen::core::Project>();
    if (!project->create(directory)) {
        QMessageBox::critical(this, QStringLiteral("Failed to create project"), project->errorString());
        return;
    }
    project_ = std::move(project);
}

void MainWindow::saveProject() {
    if (!project_) {
        QMessageBox::warning(this, QStringLiteral("No project loaded"), QStringLiteral("Load or create a project before saving"));
        return;
    }

    if (!project_->save()) {
        QMessageBox::critical(this, QStringLiteral("Failed to save project"), project_->errorString());
        return;
    }
}
