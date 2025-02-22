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
#include <QForeach>



    void controlPanelMainWindow::newConfigFile() {
        name->setText("SearchEngine");
        version->setText("0.1");
        maxResponses->setText("5");
        changeListFiles();
        saveConfigButton->setEnabled(true);
        loadListFilesButton->setEnabled(true);
    }

    QJsonDocument controlPanelMainWindow::openConfigFile() {
        QString docJson;
        QFile file("config.json");

        file.open(QIODevice::ReadOnly | QIODevice::Text);
        docJson = file.readAll();
        file.close();

        QJsonDocument textJson;

        if(!docJson.isNull())
        {
            textJson = QJsonDocument::fromJson(docJson.toUtf8());
        }
        return textJson;
    }

    void controlPanelMainWindow::printConfigFile() {

        QJsonDocument textJson = openConfigFile();
            if (textJson.isObject()) {

                saveConfigButton->setEnabled(true);
                loadListFilesButton->setEnabled(true);
                name->clear();
                version->clear();
                maxResponses->clear();
                listForFiles->clear();

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
        file.close();if(!docJson.isNull())
        {
            saveRequestsButton->setEnabled(true);
            requestsClearButton->setEnabled(true);
            listRequest->clear();

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
        for(int row = 0; row < listRequest->count(); ++row)
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
            if(status == 0) {
                statusFile->setText("OK");
            } else {
                statusFile->setText(QString::number(status));
            }

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

                    QJsonDocument listDocsJson = openConfigFile();
                    QJsonObject listDos = listDocsJson.object();
                    QJsonValue files = listDos.value("files");
                    QJsonArray filesList = files.toArray();
                    QList <QVariant> docs = filesList.toVariantList();

                    QJsonObject json = textJson.object();
                    QJsonObject answers = json.value("answers").toObject();
                    foreach(const QString numAnswer, answers.keys()) {
                        QJsonObject valueAnswer = answers.value(numAnswer).toObject();
                        listResult->addItem(numAnswer + ":");
                        if(valueAnswer["result"].toBool()) {
                            QString docName;
                            if(!(valueAnswer.find("relevance") == valueAnswer.end())) {
                                QJsonArray relevanceList = valueAnswer["relevance"].toArray();
                                QList <QVariant> lists = relevanceList.toVariantList();
                                foreach (QVariant resultText, lists) {
                                    QJsonObject result = resultText.toJsonObject();
                                    docName = docs[result["docid"].toInt()].toString();
                                    listResult->addItem("\t" + docName.right(docName.size() - 11));
                                }
                            } else {
                                docName = docs[valueAnswer["docId"].toInt()].toString();    // ToDo
                                listResult->addItem("\t" + docName.right(docName.size() - 11));
                            }
                        } else {
                            listResult->addItem("\t The result is missing");
                        }
                    }
                }

            }
        }
    }
