#pragma once

#include <memory>
#include <QMainWindow>
#include "ui_MainWindow.h"

namespace dlgen::core {
class Project;
}

class ProjectTableModel;

class MainWindow : public QMainWindow {
public:
    explicit MainWindow(QWidget *parent = nullptr);
    virtual ~MainWindow();

private:
    void addUiFile();
    void loadProject();
    void createProject();
    void saveProject();
    void refreshTable();

    Ui::MainWindow ui;
    std::unique_ptr<dlgen::core::Project> project_;
    ProjectTableModel *tableModel_ = nullptr;
};
