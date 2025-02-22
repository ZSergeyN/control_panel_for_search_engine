<h1 align="center">Control panel for Search Engine</h1>
<p align="center">
<img src="https://img.shields.io/badge/made_by-ZSergeyN-blue">
<img src="https://img.shields.io/badge/language-C%2B%2B-red">

<h3 align="center"><i> Management utility search for words in documents</i> | <i> Утилита управления поиском слов в документах</i></h3>

## Description | Описание

![](https://img.shields.io/badge/ENG-blue)<br>
 A utility for managing a console application [(search_engine)](https://github.com/ZSergeyN/search_engine), that searches for queries in documents.<br>

![](https://img.shields.io/badge/RUS-red)<br>
 Утилита управления консольным приложением [(search_engine)](https://github.com/ZSergeyN/search_engine), выполняющим поиск запросов в документах.<br>

## Technologies | Технологии
![](https://img.shields.io/badge/C%2B%2B-17-green?style=for-the-badge)<br>

![](https://img.shields.io/badge/CMake-3.24-green?style=for-the-badge)<br>
<https://cmake.org/><br>

![](https://img.shields.io/badge/QT-6.8.1-green?style=for-the-badge)<br>
<https://www.qt.io/><br>

## Sections | Разделы
<br>*config.json*
  (Setting up the app | Настройка приложения)
  * name — the name of the application | название приложения
  * version — version number | номер версии
  * max_responses — maximum number of responses | максимальное количество ответов
  * files — file paths to search for | пути к файлам для поиска
  * new config — create a new configuration file | создать новый конфигурационный файл
  * open config — open the configuration file | открыть конфигурационный файл
  * save config — save the configuration file | сохранить конфигурационный файл
  * load list files — load a list of documents to search for | загрузить список документов для поиска
  
<br>*requests.json*
  (Query management | Управление запросами)
  * Load requests — upload a file with requests | загрузить файл с запросами
  * save requests — save requests to a file | сохранить запросы в файл
  * delete requests — delete requests from the list | удалить запросы из списка
  * add requests — add a request to the list | добавить запрос в список
  * Maximum of 1000 requests | Не более 1000 запросов
  * From one to ten words | От одного до десяти слов
  * All words consist of lowercase Latin letters | Все слова состоят из строчных латинских букв
  
<br>*answers.json*
(Search and output of the result | Поиск и вывод результата)
  * Search Engine — launching the search app | запуск приложения для поиска
  * status — the status of the search application | статус работы приложения для поиска
  * result – search result | результат поиска
  * request - request number | номер запроса
