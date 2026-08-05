#include <QApplication>
#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include <iostream>
class MainWindow : public QMainWindow {

public:
    MainWindow(QWidget *parent = nullptr) : QMainWindow(parent) {}
    
    virtual ~MainWindow(){};

    void createUI() {
        // Hier erstellst du deine UI-Elemente, z.B. Labels, Buttons etc.
        // Zum Beispiel:
        QLabel *label = new QLabel("Hallo, Welt!", this);
        label->setGeometry(10, 10, 200, 20);

        QPushButton *button = new QPushButton("Klick mich!", this);
        button->setGeometry(10, 40, 100, 30);
    }
protected:
    void showEvent(QShowEvent *) override {
        // Hier kannst du Code einfügen, der ausgeführt werden soll, wenn das Fenster geöffnet wird.
    }
};

int main(int argc, char **argv) {
    QApplication app(argc, argv);

    MainWindow window;
    window.createUI();
    window.resize(400, 300); // Setze die Größe des Fensters
    window.show();

    QCoreApplication::exec();
    return 1;
}
