#include <QApplication>
#include <QObject>

#include "dynamic/DDFactory.hpp"
#include "dynamic/DynamicDialog.hpp"
#include "dynamic/DDDataProvider.hpp"

int main(int argc, char **argv) {
    QApplication app(argc, argv);
    DDDataProvider dataProv;
    DDDataProvider::Data data;
    data.name = "Test";
    data.no = "123";
    data.operation = "Add";
    
    dataProv.setData(data);
    DDFactory factory(dataProv);
    auto dlg = factory.create();

    QObject::connect(dlg.get(), &QDialog::accepted, [&factory](){ factory.persistor()->store(); });
    
    dlg->resize(400, 300);
    dlg->show();

    //MainWindow window;
    //window.resize(400, 300);
    //window.show();
    
    return QCoreApplication::exec();
}
