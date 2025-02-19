#include "controlPanel.h"

#include <QString>
#include <QFileDialog>
#include <QFile>
#include <QListView>
#include <QFileInfo>

#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonValue>
#include <QJsonParseError>



    void controlPanelMainWindow::newConfigFile() {
        name->setText("SearchEngine");
        version->setText("0.1");
        maxResponses->setText("5");
        changeListFiles();
        saveConfigButton->setEnabled(true);
        loadListFilesButton->setEnabled(true);
    }

    void controlPanelMainWindow::openConfigFile() {
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

    }

    void controlPanelMainWindow::saveConfigFile() {
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

    void controlPanelMainWindow::changeListFiles() {
        listForFiles->clear();
        for(auto& dirFiles: std::filesystem::recursive_directory_iterator("./resources/")){
            if (dirFiles.is_regular_file() && !dirFiles.path().extension().compare(".txt")) {
                listForFiles->addItem(QString(dirFiles.path().native()));
            }
        }

    }

    void controlPanelMainWindow::loadRequestFile() {
        QString docJson;
        QFile file("requests.json");

        file.open(QIODevice::ReadOnly | QIODevice::Text);
        docJson = file.readAll();
        file.close();
        if(!docJson.isNull())
        {
            saveRequestsButton->setEnabled(true);
            requestsClearButton->setEnabled(true);
            listRequest->clear();;

            QJsonDocument textJson = QJsonDocument::fromJson(docJson.toUtf8());
            if (textJson.isObject()) {
                QJsonObject json = textJson.object();
                QJsonValue requestsText = json.value("requests");
                QJsonArray requestsList = requestsText.toArray();
                QList <QVariant> lists = requestsList.toVariantList();
                foreach (QVariant currentFile, lists) {
                    listRequest->addItem(currentFile.toString());
                }
            }
        }
    }

    void controlPanelMainWindow::delListRequests() {
        listRequest->clear();
        saveRequestsButton->setEnabled(false);
        requestsClearButton->setEnabled(false);
    }

    void controlPanelMainWindow::saveRequestFile() {
        QJsonObject requestsText;

        QJsonArray requestsListText;
        for(int row = 0; row < listForFiles->count(); ++row)
        {
            QListWidgetItem *item = listRequest->item(row);
            requestsListText.push_back(item->text());
        }
        requestsText["requests"] = requestsListText;

        QJsonDocument docJson(requestsText);
        QString textJson = docJson.toJson(QJsonDocument::Indented);

        QFile file("requests.json");
        file.open(QIODevice::WriteOnly | QIODevice::Text);
        QTextStream stream( &file );
        stream << textJson;
        file.close();
    }

    void controlPanelMainWindow::addRequest() {
        if(!textRequest->displayText().isEmpty()) {
            listRequest->addItem(textRequest->text());
            textRequest->clear();
        }
    }

    void controlPanelMainWindow::startSearchEngine() {
        QString path = "./search_engine.exe";
        if(QFileInfo::exists(path)) {
            QProcess file;
            file.execute(path);
            int status = file.exitCode();
            statusFile->setText(QString::number(status));
            file.destroyed();

            QString docJson;
            QFile fileResult("answers.json");

            fileResult.open(QIODevice::ReadOnly | QIODevice::Text);
            docJson = fileResult.readAll();
            fileResult.close();
            if(!docJson.isNull())
            {
                listResult->clear();


                QJsonDocument textJson = QJsonDocument::fromJson(docJson.toUtf8());
                if (textJson.isObject()) {
                    QJsonObject json = textJson.object();
                    QJsonValue answers = json.value("answers");
                    QJsonObject answersText = answers.toObject();


                    QJsonValue req1 = answersText.value("request001");
                    QJsonObject req1Text = req1.toObject();


                    QJsonArray rel = req1Text["relevance"].toArray();


                    QList <QVariant> lists = rel.toVariantList();
                    foreach (QVariant currentFile, lists) {
                        QJsonObject q = currentFile.toJsonObject();

                        listResult->addItem(QString::number(q["docid"].toInt()) + ": " + QString::number(q["rank"].toInt()));

                    }
                }
            }
        }
    }
