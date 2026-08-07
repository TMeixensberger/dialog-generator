#pragma once

#include <QMainWindow>
#include "ui_MainWindow.h"

class MainWindow : public QMainWindow {
public:
    explicit MainWindow(QWidget *parent = nullptr);
    virtual ~MainWindow();

    void createUI();

protected:
    void showEvent(QShowEvent *) override;

private:
    Ui::MainWindow ui;
};
