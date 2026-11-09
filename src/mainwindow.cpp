#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QMessageBox>
#include <QPushButton>
#include "cdrone.h"   // définition complète de CDrone (appel de Decoller / Atterrir)

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    ptr_drone(nullptr)
{
ui->setupUi(this);
//Message de départ
QString MessageColore="<br><span style=\"color: red;\">Initialisation du drone</span>";
ui->textEdit_Messages->insertHtml(MessageColore);
}


void MainWindow::AfficherMessageUtilisateur(QString P_Message)
{
    QString MessageColore="<br><span style=\"color: green;\">"+P_Message+"</span>";
    ui->textEdit_Messages->insertHtml(MessageColore);
}

void MainWindow::AfficherDonneesVol(int P_Tangage,int P_Roulis,int P_Lacet,int P_PourcentageBat)
{
    //Affichage dans les zones LineEdit
    QString L_Tangage = QString::number(P_Tangage);
    ui->LineEditPitch->setText(L_Tangage+" °");

    QString L_Roulis = QString::number(P_Roulis);
    ui->LineEditRoll->setText(L_Roulis+" °");

    QString L_Lacet = QString::number(P_Lacet);
    ui->LineEditYaw->setText(L_Lacet+" °");

    QString Batt = QString::number(P_PourcentageBat);
    ui->LineEditBat->setText(Batt+" %");

    //mise à jour du widget qfi
    ui->graphicsView->setRoll(-P_Roulis);
    ui->graphicsView->setPitch(P_Tangage);
    ui->graphicsView->setHeading(P_Lacet);
    ui->graphicsView->update();
}


/*
//-----A Complété--------------
// Clic sur "Décoller" : on prévient l'utilisateur et on émet le signal vers CDrone
void MainWindow::on_BoutonDecoller_clicked(void)
{
    AfficherMessageUtilisateur("Commande envoyée : décollage");
    emit DemandeDecollage();
}

//-----A Complété--------------
// Clic sur "Atterrir" : on prévient l'utilisateur et on émet le signal vers CDrone
void MainWindow::on_BoutonAtterrir_clicked(void)
{
    AfficherMessageUtilisateur("Commande envoyée : atterrissage");
    emit DemandeAtterrissage();
}
*/



/* VERSION PRÉCÉDENTE avec signaux (mise en commentaire)
//-----Version avec pointeurs--------------
// Clic sur "Décoller" : pointeur vers le bouton cliqué, émet la demande vers CDrone
void MainWindow::on_BoutonDecoller_clicked(void)
{
    QPushButton *ptr_decoller = ui->BoutonDecoller;   // pointeur sur le bouton "Décoller"
    emit DemandeDecollage();
    AfficherMessageUtilisateur("Commande de vol : " + ptr_decoller->text() + " demandé");
}

// Clic sur "Atterrir" : pointeur vers le bouton cliqué, émet la demande vers CDrone
void MainWindow::on_BoutonAtterrir_clicked(void)
{
    QPushButton *ptr_atterir = ui->BoutonAtterrir;    // pointeur sur le bouton "Atterrir"
    emit DemandeAtterrissage();
    AfficherMessageUtilisateur("Commande de vol : " + ptr_atterir->text() + " demandé");
}
*/

//-----Version avec pointeur vers CDrone--------------
// Mémorise le pointeur vers le drone (appelée depuis main.cpp)
void MainWindow::DefinirDrone(CDrone *P_PtDrone)
{
    ptr_drone = P_PtDrone;
}

// Clic sur "Décoller" : appel direct de CDrone::Decoller() via le pointeur
void MainWindow::on_BoutonDecoller_clicked(void)
{
    QPushButton *ptr_decoller = ui->BoutonDecoller;   // pointeur sur le bouton "Décoller"
    if (ptr_drone == nullptr)
    {
        AfficherMessageUtilisateur("Drone non initialisé : commande impossible");
        return;
    }
    ptr_drone->Decoller();
    AfficherMessageUtilisateur("Commande de vol : " + ptr_decoller->text() + " demandé");
}

// Clic sur "Atterrir" : appel direct de CDrone::Atterrir() via le pointeur
void MainWindow::on_BoutonAtterrir_clicked(void)
{
    QPushButton *ptr_atterir = ui->BoutonAtterrir;    // pointeur sur le bouton "Atterrir"
    if (ptr_drone == nullptr)
    {
        AfficherMessageUtilisateur("Drone non initialisé : commande impossible");
        return;
    }
    ptr_drone->Atterrir();
    AfficherMessageUtilisateur("Commande de vol : " + ptr_atterir->text() + " demandé");
}

MainWindow::~MainWindow()
{
    delete ui;
}



