#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QFileDialog>
#include <QString>
#include <QMessageBox>
#include <QDebug>
#include <QDir>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    projectNetwork = new CityNetwork();
    QStringList titles;

    titles << "City" << "Population";
    ui->tableWidget_Overview->setColumnCount(2);
    ui->tableWidget_Overview->setRowCount(20);
    ui->tableWidget_Overview->setHorizontalHeaderLabels(titles);
    //ui->pushButton_addCity->setAutoDefault(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

//closes application when clicked
void MainWindow::on_pushButton_quit_clicked()
{
    close();
}

//switches to starting page from default data
void MainWindow::on_pushButton_back_01_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

//switches to starting page from custom data
void MainWindow::on_pushButton_back_02_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

//gives information about the project "Epidemionator"
void MainWindow::on_pushButton_about_clicked()
{

    //setStyleSheet("QMessageBox{border: none;font-family: Arial; font-style: normal;  font-size: 11pt; color: rgb(255,255,255) ; }");
    QMessageBox::information(this, "About", "Der Epidemionator wurde im Zuge eines Forschungsseminars\n"
                                            "am Institut fuer Informatik der TU Chemnitz ins Leben gerufen.\n\n"
                                            "Unter Betreuung von Dr. Müller [...]");

}

//switches to default data page
void MainWindow::on_pushButton_default_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

//switches to custom data page
void MainWindow::on_pushButton_custom_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}


//selects directory, creates text file (used for overview and saving projects)
//and creates new project
void MainWindow::on_pushButton_selectDir01_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Creating new Project..."),
                                                             "C://", "Text File (*.txt)");
    if (fileName.isEmpty()){
        return;
    }
    else{
        QFile projectFile(fileName);
        QFileInfo fi(projectFile);
        QString directory = fi.filePath();
        QDir dir(directory);

        dir.setCurrent(directory);
        dir.setPath(directory);
        qDebug() << directory;

        if (!projectFile.open(QIODevice::WriteOnly | QIODevice::ReadOnly)){
            QMessageBox::information(this, tr("Unable to open file."), projectFile.errorString());
            return;
        }

        QTextStream stream (&projectFile);
        //HIER WAS ANDERES EINFUEGEN!!
        stream << "S U M M A R Y" << endl;
        projectFile.close();
        this->projectNetwork->setDirectory(directory);
        this->projectNetwork->setName(fileName);
       // CityNetwork *projectNetwork = new CityNetwork(fileName, directory); //Stuerzt hier irgendwie ab
    }
    ui->stackedWidget->setCurrentIndex(3);

}

void MainWindow::on_lineEdit_Population_returnPressed()
{
    on_pushButton_addCity_clicked();
}


//adds City to City Network: cityname and population as user input
void MainWindow::on_pushButton_addCity_clicked()
{
    QDir dir = this->projectNetwork->getDirectory();

    QDir::setCurrent(this->projectNetwork->getDirectory());
   // qDebug() << "App path: " << qApp->applicationDirPath();
   // qDebug() << "Dir: " << dir.absolutePath();

    //Saving the city name and its population
    QString cityName = ui->lineEdit_Cityname->text();
    int population = ui->lineEdit_Population->text().toInt();

    //check for duplicates
    for (int i = 0; i < this->projectNetwork->getSize(); i++){
        if (cityName == projectNetwork->getCityByIndex(i).getName()){
            //setStyleSheet("QMessageBox{border: none;font-family: Arial; font-style: normal;  font-size: 11pt; color: rgb(255,255,255) ; }");
            QMessageBox::information(this, "Error","Eine Stadt mit diesem Namen existiert bereits.");
            return;
        }
    }

    //display saved cities beneath the line edits in table widget
    ui->tableWidget_Overview->setItem(projectNetwork->getSize(), 0, new QTableWidgetItem(cityName));
    ui->tableWidget_Overview->setItem(projectNetwork->getSize(), 1, new QTableWidgetItem(ui->lineEdit_Population->text()));

    //Clear line-edit
    ui->lineEdit_Cityname->clear();
    ui->lineEdit_Population->clear();

    //write into file
    QFile projectFile(this->projectNetwork->getName());
    if (!projectFile.open(QIODevice::ReadOnly | QIODevice::WriteOnly | QIODevice::Text))
        return;
    QTextStream out(&projectFile);
    int i = 0;
    while (!out.atEnd()){
        out.readLine();
        i++;
    }

    out << endl << cityName << " " << population;

    //add the city to city network
    CityNode *anotherCity = new CityNode(cityName, population);
    this->projectNetwork->addCity(*anotherCity);
}

//continues to connection-input
void MainWindow::on_pushButton_continue_02_clicked()
{
    if (this->projectNetwork->getSize() == 0){
        QMessageBox::information(this, "Error", "Sie haben keinerlei Eingabe getaetigt. Bitte Daten eingeben.\n");
        return;
    }
    ui->stackedWidget->setCurrentIndex(4);
    ui->label_cityToConnect->setText(this->projectNetwork->getCityByIndex(0).getName());
}

//switches back to city/population-input
void MainWindow::on_pushButton_back_04_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}


void MainWindow::on_lineEdit_distance_returnPressed()
{
    on_pushButton_addCon_clicked();
}

//creats and adds connections between cities
//neighbours and distances through user input
/*
 *        what about false Additions?--> falsch herum eingegeben oder Stadtname, der nicht Teil des Networks ist
 *        are Neighbours added or not? qDebug tells another story -> check out addConnection-functions in .cpp files
 *        in gui: swap distance & city for user friendly usability
 *
 * */
void MainWindow::on_pushButton_addCon_clicked()
{
    int i = 0;

    while (i < this->projectNetwork->getSize()){

        if (ui->label_cityToConnect->text() == this->projectNetwork->getCityByIndex(i).getName()){

            //get information from lineEdits (entered by user)
            QString neighbourCity = ui->lineEdit_city->text();
            float distanceToCity = ui->lineEdit_distance->text().toFloat();
            bool validInput = false;

            //check if input is correct (falsche nicht enthaltende Staedte, ungueltige Entfernungen)
            // + add more checks for incorrect inputs
            if (!this->projectNetwork->isPartOfNetwork(neighbourCity)){
                        QMessageBox::information(this, "Error!", "City is not part of your city network.");
            }

            if (distanceToCity < 0){
                 QMessageBox::information(this, "Error!", "Distance below 0!");
                 validInput = false;
            }else validInput = true;


            if (validInput){
                ui->lineEdit_city->clear();
                ui->lineEdit_distance->clear();

                    //search for neighbourCity in CityNetwork
                    int j = 0;

                    while (j < this->projectNetwork->getSize()){
                        if (this->projectNetwork->getCityByIndex(j).getName() == neighbourCity){

                            //check for duplicate-neighbours
                            if (this->projectNetwork->getCityByIndex(i).isConnectedTo(this->projectNetwork->getCityByIndex(j))){
                                QMessageBox::information(this, "Fehler!", "Diese Verbindung existiert bereits!");
                                return;
                            }

                            CityNode cityFrom = this->projectNetwork->getCityByIndex(i);
                            CityNode cityTo = this->projectNetwork->getCityByIndex(j);


                            Connection *newEdge;
                            newEdge = new Connection(cityFrom, cityTo, distanceToCity);

                            this->projectNetwork->addConnection(newEdge);
                            j++;

                         }else j++;
                    }
            }
        }
        //else i++;
     i++;
     }
    this->projectNetwork->printDetails();
}


//Selects next city to be connected
/*
 * Bei Beispiel Stadt2 - bzw bei zweiter Stadt passiert danach nichts am Button
 * addConnection :(
 *
 */
void MainWindow::on_pushButton_nextC_clicked()
{
    for (int i = 0; i < this->projectNetwork->getSize(); i++){
        if (i == this->projectNetwork->getSize()){
            return;
        }
        if (this->projectNetwork->getCityByIndex(i).getName() == ui->label_cityToConnect->text()){
            ui->label_cityToConnect->setText(this->projectNetwork->getCityByIndex(i+1).getName());
            return;
        }
    }
}


//selects directory of existing file (used for overview and starts default project)
void MainWindow::on_pushButton_selectDir02_clicked()
{

    QString fileName = QFileDialog::getOpenFileName(this, tr("Open"), "C://", "Text File (*.txt)");

    if (fileName.isEmpty())
        return;
    else {
        QFile file(fileName);
        if (!file.open(QIODevice::ReadWrite)){
            QMessageBox::information(this, tr("Fehler, Datei kann nicht geöffnet werden"), file.errorString());
            return;
        }
    }
    /*
    else {

        QFile file(fileName);

        if (!file.open(QIODevice::ReadOnly)) {
            QMessageBox::information(this, tr("Unable to open file"),
                file.errorString());
            return;
        }

        QDataStream in(&file);
        in.setVersion(QDataStream::Qt_4_5);
        contacts.clear();   // clear existing contacts
        in >> contacts;
     */

}

//swaps back to default-select-directory-page
void MainWindow::on_pushButton_back_03_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}



