#pragma once
#include <QMainWindow>
#include <QtWidgets>
#include <QListWidget>
#include <QPushButton>



class controlPanelMainWindow : public QMainWindow {

    Q_OBJECT

private:


public:
    controlPanelMainWindow(QWidget* parent = nullptr) : QMainWindow(parent) {};
    QString file_path;
    QLabel* name = nullptr;
    QLabel* version;
    QLabel* statusFile;
    QLineEdit* maxResponses;
    QLineEdit* textRequest;
    QListWidget* listForFiles;
    QListWidget* listRequest;
    QListWidget* listResult;
    QPushButton* saveConfigButton;
    QPushButton* loadListFilesButton;
    QPushButton* requestsLoadButton;
    QPushButton* saveRequestsButton;
    QPushButton* requestsClearButton;
    QPushButton* requestAddButton;
    QPushButton* startSearchEngineButtion;


public slots:
    void newConfigFile();

    QJsonDocument openConfigFile();

    void printConfigFile();

    void saveConfigFile();

    void changeListFiles();

    void loadRequestFile();

    void delListRequests();

    void saveRequestFile();

    void addRequest();

    void startSearchEngine();
};
