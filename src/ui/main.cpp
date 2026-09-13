#include <QApplication>
#include <QObject>

#include "dynamic/DDFactory.hpp"
#include "dynamic/DynamicDialog.hpp"
#include "dynamic/DDDataProvider.hpp"
#include "dynamic/widgets/Sine.hpp"
#include <QTableView>

int main(int argc, char **argv) {
    QApplication app(argc, argv);
    DDDataProvider dataProv;
    DDDataProvider::Data data;
    data.name = "Test";
    data.no = "123";
    data.operation = "Sine";
    
    SineData sineData;
    sineData.minValue = 3;
    sineData.maxValue = 100.00;
    sineData.comment = QString::fromUtf8("This is a comment");
    sineData.active = true;
    data.operationData = QVariant::fromValue(sineData);

    dataProv.setData(data);
    DDFactory factory(dataProv);
    auto dlg = factory.create();

    QObject::connect(dlg.get(), &QDialog::accepted, [&factory](){ factory.persistor()->store(); });
    
    dlg->resize(400, 300);
    dlg->show();

    auto& dlgModel = factory.persistor()->model();
    auto table = new QTableView();
    table->setModel(&dlgModel);
    table->resize(400, 300);
    table->show();
    //MainWindow window;
    //window.resize(400, 300);
    //window.show();
    
    return QCoreApplication::exec();
}
