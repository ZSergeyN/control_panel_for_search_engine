#pragma once
#include <QMainWindow>
#include <QtWidgets/QLabel>
#include <QFileDialog>
#include <QtWidgets/QLineEdit>
#include <QFile>
#include <QListView>
#include <QListWidget>
#include <QPushButton>

#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonValue>
#include <QJsonParseError>


class controlPanelMainWindow : public QMainWindow {

    Q_OBJECT

private:


public:
    controlPanelMainWindow(QWidget* parent = nullptr) : QMainWindow(parent) {}
    QString file_path;
    QLabel* name = nullptr;
    QLabel* version;
    QLineEdit* maxResponses;
    QListWidget* listForFiles;
    QPushButton* saveConfigButton;
    QPushButton* loadListFilesButton;

public slots:
    void newConfigFile() {
        name->setText("SearchEngine");
        version->setText("0.1");
        maxResponses->setText("5");
        changeListFiles();
        saveConfigButton->setEnabled(true);
        loadListFilesButton->setEnabled(true);
    };

    void openConfigFile() {
        QString docJson;
        QFile file("config.json");

        file.open(QIODevice::ReadOnly | QIODevice::Text);
        docJson = file.readAll();
        file.close();
        if(!docJson.isNull())
        {
            saveConfigButton->setEnabled(true);
            loadListFilesButton->setEnabled(true);
            name->clear();
            version->clear();
            maxResponses->clear();
            listForFiles->clear();

            QJsonDocument textJson = QJsonDocument::fromJson(docJson.toUtf8());
            if (textJson.isObject()) {
                QJsonObject json = textJson.object();
                QJsonValue config = json.value("config");
                if (config.isObject())
                {
                    QJsonObject configText = config.toObject();
                    name->setText(QString(configText["name"].toString()));
                    version->setText(configText["version"].toString());
                    maxResponses->setText(QString::number(configText["max_responses"].toInt()));
                }
                QJsonValue files = json.value("files");
                QJsonArray filesList = files.toArray();
                QList <QVariant> lists = filesList.toVariantList();
                foreach (QVariant currentFile, lists) {
                    listForFiles->addItem(currentFile.toString());
                }
            }
        }

    };

    void saveConfigFile() {
        QJsonObject configText;
        configText["name"] = name->text();
        configText["version"] = version->text();
        configText["max_responses"] = maxResponses->text().toInt();
        QJsonObject recordText;
        recordText["config"] = configText;

        QJsonArray filesList;
        for(int row = 0; row < listForFiles->count(); ++row)
        {
            QListWidgetItem *item = listForFiles->item(row);
            filesList.push_back(item->text());
        }
        recordText["files"] = filesList;

        QJsonDocument docJson(recordText);
        QString textJson = docJson.toJson(QJsonDocument::Indented);

        QFile file("config.json");
        file.open(QIODevice::WriteOnly | QIODevice::Text);
        QTextStream stream( &file );
        stream << textJson;
        file.close();
    }

    void changeListFiles() {
        listForFiles->clear();
        for(auto& dirFiles: std::filesystem::recursive_directory_iterator("./resources/")){
            if (dirFiles.is_regular_file() && !dirFiles.path().extension().compare(".txt")) {
                listForFiles->addItem(QString(dirFiles.path().native()));
            }
        }

    }
};
