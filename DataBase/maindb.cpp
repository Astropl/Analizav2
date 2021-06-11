#include "maindb.h"
#include <iostream>
#include <QDebug>
#include <QString>
#include <QDir>
#include <QMainWindow>
#include <QSqlDatabase>
#include <QSqlDriver>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>

#include <map>
#include <list>
#include <stdlib.h>
#include <QList>


using namespace std;

QStringList images;


mainDB::mainDB(QWidget *parent) : QMainWindow(parent)
{

}
void mainDB::init()
{
    // inicjalizacja Bazy
    qWarning ()<<"Initializacja Bazy";
    DatabaseConnect();
    DatabasePopulate();
}

void mainDB::DatabaseConnect()
{
    qWarning("Database Connect");
    const QString DRIVER("QSQLITE");
    if (QSqlDatabase::isDriverAvailable(DRIVER)) {
        QSqlDatabase db = QSqlDatabase::addDatabase(DRIVER);
        db.setDatabaseName(
                    "C:/Users/pawel/Documents/Cplusplus/Analizav2/DataBase/2021.06.11.db");
        qWarning(" Powstała baza");

        if (db.open()) {
            qWarning() << (" Otwarto DB") << db.lastError().text();
            qWarning() << (" Otwarto DB") << db.isDriverAvailable(DRIVER);
            //qWarning() << (" Otwarto DB") << db.connectOptions().
        } else {
            qWarning() << (" Brak otwarcia") << db.lastError().text();
        }
    }
}

void mainDB::DatabasePopulate()
{
    qWarning("Database Wypelnianiae");
    dBFileNames();
    dBWczytajNazwyPlikow();
    dBWczytajSuroweDane();

    //    dBMiasta();
    //    dBWojewodztwa();
    //    dBKraj();
    //    dBProducent();
    //    dBModel();
    //    dBUrzadzenia();
    //    dBKontrahent();
    //    dBBaza();
    //    dBPrzypomnienie();
    //    dBStatistisc();
    //    dBInfoOTemacie();
    //    dBWazneDaty();

    //QSqlQuery query;
}

void mainDB::dBWczytajSuroweDane()
{QSqlQuery query;
    for (int x =0 ;x<=images.size()-1;x++)
    {
        qDebug ()<< images.at(x);
        //wczytac dane z plikow
        //dodac do bazy.
    }
}

void mainDB::dBWczytajNazwyPlikow()
{

    QStringList nazwaPliku;


    QDir directory("C:/Accuniq/Standalone/INTERFACE WRITE/");
    images = directory.entryList(QStringList() << "*.txt" << "*.txt",QDir::Files);
    cout<<images.length();
    qDebug ()<< " Entry in loop";
    for (int x =0 ;x<=images.size()-1;x++)
    {
        qDebug ()<< images.at(x);
    }
    addFileName();
}
void mainDB::addFileName()
{QSqlQuery query;
    for (int x =0 ;x<=images.size()-1;x++)
    {
        qDebug ()<< images.at(x);


        if (!query.exec("INSERT INTO FilesNames (fileName) VALUES('" + images.at(x) + "')"))
            qWarning() << "MainDB::FileNames - ERROR: " << query.lastError().text();
        //return 0;
    }
}
int mainDB::pobierzIloscPlikow(int iloscPlikow)
{
    QSqlQuery query;
    //QString testName;
    int rows = 0;
    if (query.exec("SELECT * FROM FilesNames")) {
        while (query.next()) {
            rows++;
        }
    }
    iloscPlikow = rows;
    return rows;
}

void mainDB::dBFileNames()
{
    QSqlQuery query;
    query.exec("PRAGMA foreign_keys = ON;"); // włączenia kluczy obcych
    qWarning("Tworzenie tabeli FilesNames ");
    query.exec("CREATE TABLE IF NOT EXISTS FilesNames  (id INTEGER PRIMARY KEY, fileName TEXT UNIQUE )");

    if (!query.isActive()) {
        qWarning() << " Tworzenie Tabeli - ERROR: " << query.lastError().text();
    }
    // query.exec("PRAGMA foreign_keys = ON;"); // włączenia kluczy obcych
    if (!query.exec("INSERT INTO FilesNames (fileName) VALUES('file_test_temp')")) {
        qWarning() << "MainWindow::DatabasePopulate - ERROR: " << query.lastError().text();
    }
    qWarning("Tworzenie tabeli FilesName - Zakończone ");
}
void mainDB::dBMainTable()
{
    //    QSqlQuery query;
    //    query.exec("PRAGMA foreign_keys = ON;"); // włączenia kluczy obcych
    //    qWarning("Tworzenie tabeli main ");
    //    query.exec("CREATE TABLE IF NOT EXISTS tableImport  (id INTEGER PRIMARY KEY, miasto TEXT UNIQUE )");

    //    if (!query.isActive()) {
    //        qWarning() << " Tworzenie Tabeli - ERROR: " << query.lastError().text();
    //    }
    //    // query.exec("PRAGMA foreign_keys = ON;"); // włączenia kluczy obcych
    //    if (!query.exec("INSERT INTO miasta (miasto) VALUES('Warszawa')")) {
    //        qWarning() << "MainWindow::DatabasePopulate - ERROR: " << query.lastError().text();
    //    }
    //    qWarning("Tworzenie tabeli Miasta - Zakończone ");
}