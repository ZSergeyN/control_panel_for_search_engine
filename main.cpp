#include <QApplication>
#include <./ui_controlPanel.h>
#include "controlPanel.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    controlPanelMainWindow window(nullptr);
    Ui::MainWindow controlPanel;
    controlPanel.setupUi(&window);

    window.name = controlPanel.name;
    window.version = controlPanel.version;
    window.maxResponses = controlPanel.maxResponses;
    window.listForFiles = controlPanel.listForFiles;
    window.saveConfigButton = controlPanel.saveConfigButton;
    window.loadListFilesButton = controlPanel.loadListFilesButton;

    window.textRequest = controlPanel.textRequest;
    window.listRequest = controlPanel.listRequest;
    window.requestsLoadButton = controlPanel.requestsLoadButton;
    window.saveRequestsButton = controlPanel.saveRequestsButton;
    window.requestsClearButton = controlPanel.requestsClearButton;

    window.statusFile = controlPanel.statusFile;
    window.listResult = controlPanel.listResult;

    window.setFixedSize(502, 680);
    window.show();
    return QApplication::exec();
}
