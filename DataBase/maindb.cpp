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
#include <fstream>


using namespace std;

QStringList namesOfFiles; //lista nazw plików
QStringList th = {"DATA BADANIA", "GODZINA BADANIA", "ID", "NAZWA", "WZROST", "WIEK", "PŁEĆ", "WAGA", "DOLNY LIMIT WAGI", "GÓRNY LIMIT WAGI", "WAGA STANDARDOWA", "BEZTŁUSZCZOWA MASA CIAŁA", "DOLNY LIMIT BEZTŁUSZCZOWEJ MASY CIAŁA", "GÓRNY LIMIT BEZTŁUSZCZOWEJ MASY CIAŁA", "SLM.", "DOLNY LIMIT SLM", "temp9" , "temp10" };

fstream  fileName;
string filePatch = "C:/Accuniq/Standalone/INTERFACE WRITE/";

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
    dBSourceDates();
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
{  QSqlQuery query;
    fileName.close();
    QStringList loh;// nagłówki
    QStringList QSp; //lista str splitowanych do pojedycnych

    qDebug ()<< "Start::dBWczytajSuroweDane";
    QString th[16] = {"DATA_BADANIA", "GODZINA_BADANIA", "IDMN", "NAZWA", "WZROST", "WIEK", "PŁEĆ", "WAGA", "DOLNY_LIMIT_WAGI", "GÓRNY_LIMIT_WAGI", "WAGA_STANDARDOWA", "BEZTŁUSZCZOWA_MASA_CIAŁA", "DOLNY_LIMIT_BEZTŁUSZCZOWEJ_MASY_CIAŁA", "GÓRNY_LIMIT_BEZTŁUSZCZOWEJ_MASY_CIAŁA", "SLM", "DOLNY_LIMIT_SLM" }; // Tabela headów w title

    //*
    //Sprawdzam poprawnos headerów
    for (int i =0;i<=16-1 ;i++ ) {
        cout<<"Lista headerow: "<<endl;
        cout<<th[i].toStdString()<<endl;
    }
    //End sprawdzanie headerow
    //-----------------------------------------

    //*
    //Wczytuje do qstringlist stringi zesplitowane
    qWarning()<<"Ilosc plików"<<namesOfFiles.size();

    //otworzyc plik
    //wczytac dane
    //zesplitowac je
    for (int q=0;q<=namesOfFiles.size() -1;q++ ) // dla kazdego pliku
    {

        {
            string stringNameOfFile = namesOfFiles.at(q).toStdString();
            fileName.open(filePatch +stringNameOfFile,ios::in );
            cout<< "Wczytuje plik nr: "<< q << " "+ stringNameOfFile<<endl;

            if( fileName.good() == true )
            {
                cout << "Uzyskano dostep do pliku! "+ (namesOfFiles.at(q).toStdString()) << endl;
                //tu operacje na pliku
                string str; // bufor danych
                while(!fileName.eof())// dopuki nie osiągnięto końca pliku

                {
                    getline(fileName,str);
                    QString qStrSplited = QString::fromStdString(str); // zamineiam bufor str na Qstring

                    QSp = qStrSplited.split(';');

                    for (int i =0; i <= 17; i++) //na razie do 15 a ma byc... i <= QSp.size()-1
                        //{ for (int j=0;j<=;)
                    {
                        cout << QSp.at(i).toStdString()<<endl;
                    }
                    //                        if(!query.exec("INSERT INTO SourceDatess("+QString::fromStdString(th[0].toStdString())+","+QString::fromStdString(th[1].toStdString())+") VALUES ('" + QString::fromStdString(QSp.at(1).toStdString())+","+QString::fromStdString(QSp.at(2).toStdString()) + "')"))
                    if(!query.exec("INSERT INTO SourceDatess(DATA_BADANIA, GODZINA_BADANIA) VALUES (' cosike','dwauir')"))
                    {
                        qWarning() << "MainDB::addwartosc  - ERROR: " << query.lastError().text();
                    }

                }
            }
            else
            {
                cout << "Dostep do pliku zostal zabroniony!: " << + " " + stringNameOfFile<< endl;
            }
            fileName.close();
        }

    }


    //End
    //-----------------------------------------






    //    //for (int x =0 ;x<=15;x++)
    //    for (int x =1 ;x<=namesOfFiles.size()-1;x++) //1 poniewaz 0 to wpis testowy ///images.size()-1 ************8Zróbmy narazie do 16.
    //    {//fileName.close();

    //        loh.clear();
    //        //        cout <<" ***************************" <<endl;
    //        //        cout <<images.size() <<endl;

    //        //        cout <<" ***************************" <<endl;

    //        //        cout<< "Wczytuje plik " + (images.at(x).toStdString())<<endl;
    //        //string qFileName = images.at(x).toStdString();

    //        //wczytac dane z plikow
    //        //fileName.open(images.at(x).toStdString(),ios::in );


    //        fileName.open(filePatch +namesOfFiles.at(x).toStdString(),ios::in );
    //        //qDebug ()<< "Wchdze do If poraz " <<x;
    //        if( fileName.good() == true )
    //        {
    //            cout << "Uzyskano dostep do pliku!" << endl;
    //            //tu operacje na pliku
    //            string str; // bufor danych

    //            while(!fileName.eof())
    //                // while (fileName>>str)
    //            { // dopuki nie osiągnięto końca pliku

    //                cout <<"Plik numer: ";
    //                cout <<x<<endl;
    //                cout<< " o nazwie: " + (namesOfFiles.at(x).toStdString())<<endl;
    //                getline(fileName, str); // wczytywanie linii tesktu z pliku (do znaku końca linii) do zmiennej typu string

    //                //cout<<str<<endl;


    //                QSqlQuery query;
    //                QString str1 = "check";

    //                //TODO: Trzeba rodzieclic dane na pojedyncze komórki.

    //                QString qStrSplited = QString::fromStdString(str);
    //                QSp = qStrSplited.split(';');
    //                for (int i =0; i <= 15; i++) //na razie do 15 a ma byc... i <= QSp.size()-1
    //                {
    //                    //cout << QSp.at(i).toStdString()<<endl;

    //                }
    //                //out <<"Ilosc stringow po rodzeleniu:"<<endl;
    //                //cout <<"Rozmiar QSp. size: "<<QSp.size()<<endl;

    //                //TODO: Zrobic petle zeby nie pisać tego wszytskiego osobno
    //                // Lista headów w title

    //                //                 QString th[16] = {"DATA BADANIA", "GODZINA BADANIA", "ID", "NAZWA", "WZROST", "WIEK", "PŁEĆ", "WAGA", "DOLNY LIMIT WAGI", "GÓRNY LIMIT WAGI", "WAGA STANDARDOWA", "BEZTŁUSZCZOWA MASA CIAŁA", "DOLNY LIMIT BEZTŁUSZCZOWEJ MASY CIAŁA", "GÓRNY LIMIT BEZTŁUSZCZOWEJ MASY CIAŁA", "S.L.M.", "DOLNY LIMIT S.L.M." }; // Tabela headów w title
    //                //        th[] =

    //                //cout<<"Ilosc w th: "<<(th.size()) <<endl;
    //                //cout<<"Ilosc w th: "<<sizeof(th) <<endl;
    //                int rozmiartablicyTH = th.size()-1;

    //                for ( int c=0;c<=rozmiartablicyTH;c++ )
    //                {
    //                    loh.push_back(th[c]);// nagłówki
    //                    //loh.append(th[c]);
    //                }

    //                // sprawdzenie poprawnego zapisu do qstring list TH

    //                for (int rt=0;rt<=namesOfFiles.size()-1;rt++)
    //                {
    //                    for ( int t = 0; t <= loh.size()-1;t++)
    //                    {
    //                        cout<<"z qstringList nagłowki nr: "<< t<<endl;
    //                        cout<< (loh.at(t).toStdString() )<<endl;
    //                        cout<< (QSp.at(t).toStdString() )<<endl;

    //                        {
    //                            if(!query.exec("INSERT INTO SourceDatess("+QString::fromStdString(loh.at(rt).toStdString())+") VALUES ('" + QString::fromStdString(QSp.at(t).toStdString()) + "')"))
    //                            {
    //                                //qWarning() << "MainDB::addMiasto - ERROR: " << query.lastError().text();
    //                            }
    //                        }
    //                    }}



    //                //                if (!query.exec("INSERT INTO SourceDatess (data , godzina , IDMrn , name , Hight , Year_ofBirth , sex  , Weight, temp1 , temp2 , temp3 , temp4 , temp5 , temp6 , temp7 , temp8 , temp9 , temp10) VALUES('" + QSp.at(0).toStdString() + "','"+ QSp.at(1).toStdString() + "','"+ QSp.at(2).toStdString() + "','"+ QSp.at(3).toStdString() + "','"+ QSp.at(4).toStdString() + "','"+ QSp.at(5).toStdString() + "','"+ QSp.at(6).toStdString() + "','"+ QSp.at(7).toStdString() + "','"+ QSp.at(8).toStdString() + "','" + QSp.at(9).toStdString() + "','"+  QSp.at(10).toStdString() + "','"+ QSp.at(11).toStdString() + "','" + QSp.at(12).toStdString() + "','" + QSp.at(13).toStdString() + "','" + QSp.at(14).toStdString() + "','" + QSp.at(15).toStdString() + "','" + QSp.at(16).toStdString() + "','" + QSp.at(17).toStdString() + "')"))

    //                //                if (!query.exec("INSERT INTO SourceDatess (data , godzina , IDMrn , name , Hight ) VALUES('" + QString::fromStdString(QSp.at(0).toStdString()) + "','"+ QString::fromStdString(QSp.at(1).toStdString()) + "','"+ QString::fromStdString(QSp.at(2).toStdString()) + "','"+ QString::fromStdString(QSp.at(3).toStdString()) + "','"+  QString::fromStdString(QSp.at(4).toStdString()) + "')"))



    //                {
    //                    qWarning() << "MainWindow::DatabasePopulate - ERROR: " << query.lastError().text();
    //                }

    //                fileName.close();
    //            }
    //        }
    //        else

    //        {
    //            cout << "Dostep do pliku zostal zabroniony!: " <<+"."+namesOfFiles.at(x).toStdString()+"."<< endl;
    //        }



    //    }
    //    //for (int x=0; x <= loh.size()-1; x++)
    //    //    {
    //    //        if(!query.exec("INSERT INTO SourceDatess("+QString::fromStdString(loh.at(x).toStdString())+") VALUES ('" + QString::fromStdString(QSp.at(x).toStdString()) + "')"))
    //    //        {
    //    //            //qWarning() << "MainDB::addMiasto - ERROR: " << query.lastError().text();
    //    //        }
    //    //    }
    //    //dodac do bazy.

    fileName.close();
    qDebug ()<< "END::dBWczytajSuroweDane";
}

void mainDB::dBWczytajNazwyPlikow()
{

    QStringList nazwaPliku;


    QDir directory("C:/Accuniq/Standalone/INTERFACE WRITE/");
    //images = directory.entryList(QStringList() << "*.txt" << "*.txt",QDir::Files); ///pliki text
    namesOfFiles = directory.entryList(QStringList() << "*.csv" << "*.csv",QDir::Files); ///pliki csv
    //cout<<"'Ilosc plikow: "<<images.length()<<endl;
    //qDebug ()<< " Entry in loop";
    for (int x =0 ;x<=namesOfFiles.size()-1;x++)
    {
        //qDebug ()<< images.at(x);
    }
    addFileName();
}
void mainDB::addFileName()
{QSqlQuery query;
    for (int x =0 ;x<=namesOfFiles.size()-1;x++)
    {
        //qDebug ()<< images.at(x);


        if (!query.exec("INSERT INTO FilesNames (fileName) VALUES('" + namesOfFiles.at(x) + "')"))
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
    //    if (!query.exec("INSERT INTO FilesNames (fileName) VALUES('file_test_temp')")) {
    //        qWarning() << "MainWindow::DatabasePopulate - ERROR: " << query.lastError().text();
    //    }
    qWarning("Tworzenie tabeli FilesName - Zakończone ");
}
void mainDB::dBSourceDates()
{QSqlQuery query;
    QStringList th = {"DATA_BADANIA", "GODZINA_BADANIA", "IDMN", "NAZWA", "WZROST", "WIEK", "PŁEĆ", "WAGA", "DOLNY_LIMIT_WAGI", "GÓRNY_LIMIT_WAGI", "WAGA_STANDARDOWA", "BEZTŁUSZCZOWA_MASA_CIAŁA", "DOLNY_LIMIT_BEZTŁUSZCZOWEJ_MASY_CIAŁA", "GÓRNY_LIMIT_BEZTŁUSZCZOWEJ_MASY_CIAŁA", "SLM", "DOLNY_LIMIT_SLM" };

    qWarning("Tworzenie tabeli dane zrodłowe ");


    //    for (int x=0; x <= th.size()-1; x++)
    //    {
    //        if(!query.exec("CREATE TABLE IF NOT EXISTS SourceDatess(id INTEGER PRIMARY KEY, "+QString::fromStdString(th.at(x).toStdString())+ " TEXT )"))
    //        {
    //            //qWarning() << "MainDB::addMiasto - ERROR: " << query.lastError().text();
    //        }

    query.exec("CREATE TABLE IF NOT EXISTS SourceDatess  (id INTEGER PRIMARY KEY, DATA_BADANIA TEXT, GODZINA_BADANIA TEXT, IDMN TEXT, NAZWA TEXT, WZROST TEXT, WIEK TEXT, PŁEĆ  TEXT, WAGA TEXT, DOLNY_LIMIT_WAGI TEXT, GÓRNY_LIMIT_WAGI TEXT, WAGA_STANDARDOWA TEXT, BEZTŁUSZCZOWA_MASA_CIAŁA TEXT, DOLNY_LIMIT_BEZTŁUSZCZOWEJ_MASY_CIAŁA TEXT, GÓRNY_LIMIT_BEZTŁUSZCZOWEJ_MASY_CIAŁA TEXT, SLM TEXT, DOLNY_LIMIT_SLM TEXT, temp9 TEXT, temp10 TEXT )");

    if (!query.isActive()) {
        qWarning() << " Tworzenie Tabeli - ERROR: " << query.lastError().text();
    }

    if (!query.exec("INSERT INTO SourceDatess (DATA_BADANIA, GODZINA_BADANIA, IDMN, NAZWA , WZROST , WIEK , PŁEĆ , WAGA , DOLNY_LIMIT_WAGI , GÓRNY_LIMIT_WAGI , WAGA_STANDARDOWA , BEZTŁUSZCZOWA_MASA_CIAŁA , DOLNY_LIMIT_BEZTŁUSZCZOWEJ_MASY_CIAŁA , GÓRNY_LIMIT_BEZTŁUSZCZOWEJ_MASY_CIAŁA , SLM , DOLNY_LIMIT_SLM , temp9 , temp10 ) VALUES('2021-01-01', '09:00', '00001', 'Testowy', '200', '25', 'Mężczyzna', '80', 'temp', 'temp', 'temp', 'temp', 'temp', 'temp', 'temp', 'temp', 'temp', 'temp')")) {
        //        qWarning() << "MainWindow::DatabasePopulate - ERROR: " << query.lastError().text();
        //    }
        qWarning("Tworzenie tabeli FilesName - Zakończone ");
    }
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