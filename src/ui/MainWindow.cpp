#include "MainWindow.h"

#include <iostream>
#include <QDir>
#include <QFile>
#include <QPushButton>
#include <QFileDialog>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QMessageBox>

#include "ProjectFile.h"
#include "Parser.h"
#include "Generator.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    ui.setupUi(this);
    connect(ui.pushButton_2, &QPushButton::clicked, this, &MainWindow::addUiFile);
    connect(ui.actionLoadProject, &QAction::triggered, this, &MainWindow::loadProject);
    connect(ui.actionCreateProject, &QAction::triggered, this, &MainWindow::createProject);
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

    auto projectFile = std::make_unique<dlgen::core::ProjectFile>(directory);
    if (!projectFile->isValid()) {
        QMessageBox::critical(this, QStringLiteral("Failed to load project"), projectFile->errorString());
        return;
    }

    projectFile_ = std::move(projectFile);
}

void MainWindow::createProject() {
    const QString directory = QFileDialog::getExistingDirectory(this, QStringLiteral("Select Directory for New Project"));
    if (directory.isEmpty()) {
        return;
    }

    const QString configFilePath = QDir(directory).filePath(QStringLiteral("config.json"));
    if (QFile::exists(configFilePath)) {
        QMessageBox::warning(this, QStringLiteral("Project already exists"), QStringLiteral("config.json already exists in this directory"));
        return;
    }

    QFile configFile(configFilePath);
    if (!configFile.open(QIODevice::WriteOnly | QIODevice::NewOnly)) {
        QMessageBox::critical(this, QStringLiteral("Failed to create project"), QStringLiteral("Could not create config.json"));
        return;
    }

    const QJsonObject config{{QStringLiteral("uiFiles"), QJsonArray()}};
    const QByteArray configBytes = QJsonDocument(config).toJson(QJsonDocument::Indented);
    const qint64 bytesWritten = configFile.write(configBytes);
    if (bytesWritten != static_cast<qint64>(configBytes.size())) {
        configFile.close();
        if (!QFile::remove(configFilePath)) {
            QMessageBox::critical(this, QStringLiteral("Failed to create project"), QStringLiteral("Could not clean up invalid config.json"));
            return;
        }
        QMessageBox::critical(this, QStringLiteral("Failed to create project"), QStringLiteral("Could not write config.json"));
        return;
    }

    if (!configFile.flush()) {
        configFile.close();
        if (!QFile::remove(configFilePath)) {
            QMessageBox::critical(this, QStringLiteral("Failed to create project"), QStringLiteral("Could not clean up invalid config.json"));
            return;
        }
        QMessageBox::critical(this, QStringLiteral("Failed to create project"), QStringLiteral("Could not write config.json"));
        return;
    }
    configFile.close();

    auto projectFile = std::make_unique<dlgen::core::ProjectFile>(directory);
    if (!projectFile->isValid()) {
        if (!QFile::remove(configFilePath)) {
            QMessageBox::critical(
                this,
                QStringLiteral("Failed to create project"),
                QStringLiteral("Could not clean up invalid config.json (%1)").arg(projectFile->errorString())
            );
            return;
        }
        QMessageBox::critical(this, QStringLiteral("Failed to create project"), projectFile->errorString());
        return;
    }

    projectFile_ = std::move(projectFile);
}
