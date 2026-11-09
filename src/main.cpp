#include "mainwindow.h"
#include <QApplication>
#include "cdrone.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    CDrone LeDrone(&w);
    LeDrone.InitialisationCommunication();

    /*
    //-----A Complété--------------
    // Boutons de l'IHM -> commandes du drone
    QObject::connect(&w, SIGNAL(DemandeDecollage()), &LeDrone, SLOT(Decoller()));
    QObject::connect(&w, SIGNAL(DemandeAtterrissage()), &LeDrone, SLOT(Atterrir()));
    */


    /*
    // Commandes de vol : MainWindow (signaux) -> CDrone (slots Decoller / Atterrir)
    QObject::connect(&w, &MainWindow::DemandeDecollage, &LeDrone, &CDrone::Decoller);
    QObject::connect(&w, &MainWindow::DemandeAtterrissage, &LeDrone, &CDrone::Atterrir);
    */

    //-----Plus de QObject::connect : MainWindow appelle directement CDrone via son pointeur--------------
    w.DefinirDrone(&LeDrone);
    w.AfficherMessageUtilisateur("Initialisation terminée");
    w.show();
    return a.exec();
}
