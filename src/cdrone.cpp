#include "cdrone.h"
#include <QUdpSocket>
#include <QHostAddress>

// Constructeur : mémorise le pointeur vers l'IHM pour pouvoir y afficher les données
CDrone::CDrone(MainWindow *PtMainWindows)
{
    L_PtMainWindows = PtMainWindows;

    // Valeurs initiales pour éviter d'afficher des valeurs aléatoires
    PourcentageChargeBat = 0;
    Tangage = 0;
    Roulis = 0;
    Lacet = 0;
}

void CDrone::InitialisationCommunication(void)
{
    // Socket d'écoute des données de vol : le drone les envoie sur le port 8890 de notre PC
    udpSocketServeurReceptionDonneesDeVol.bind(QHostAddress::Any, Num_Port_Navdata);
    connect(&udpSocketServeurReceptionDonneesDeVol, SIGNAL(readyRead()),
            this, SLOT(DonneesDeVolRecues()));

    // Socket des commandes : les réponses ("ok"/"error") reviennent sur ce même socket
    connect(&SocketPourCommandeAcquittementDrone, SIGNAL(readyRead()),
            this, SLOT(AcquittementCommandesRecues()));

    //-----A Complété--------------
    // Initialisation de la communication avec le drone pour demander l'envoi des données de vol :
    // la commande "command" fait passer le Tello en mode SDK (port de commande 8889).
    // Une fois en mode SDK, il envoie automatiquement l'état de vol vers le port 8890.
    QByteArray CommandeInit = "command";
    SocketPourCommandeAcquittementDrone.writeDatagram(CommandeInit,
                                                      QHostAddress(IP_DRONE),
                                                      Num_Port_Command);
}


// Slot appelé à chaque réception de données de vol (signal readyRead)
void CDrone::DonneesDeVolRecues(void)
{
    while (udpSocketServeurReceptionDonneesDeVol.hasPendingDatagrams())
    {
        QHostAddress L_IPDrone;
        quint16 L_PortDrone;
        QByteArray datagram;
        datagram.resize((int)udpSocketServeurReceptionDonneesDeVol.pendingDatagramSize());

        //-----A Complété--------------
        // Lecture des données de vol reçues
        udpSocketServeurReceptionDonneesDeVol.readDatagram(datagram.data(), datagram.size(),
                                                           &L_IPDrone, &L_PortDrone);

        // On sélectionne les éléments à afficher
        // Trame type : "pitch:0;roll:0;yaw:0;vgx:0;...;bat:87;...;agx:0.00;\r\n"
        QList<QByteArray> L_Liste_Donnees_De_Vol = datagram.split(';');
        foreach (QByteArray Element_Liste_De_Vol, L_Liste_Donnees_De_Vol)
        {
            //-----A Complété--------------
            // (bat, yaw, roll et pitch traités ici)
            // Chaque élément est de la forme "nom:valeur"
            QList<QByteArray> L_Champ = Element_Liste_De_Vol.split(':');
            if (L_Champ.size() < 2)
                continue;   // élément vide ou mal formé (ex: "\r\n" final)

            // trimmed() retire espaces, \r et \n éventuels
            QByteArray L_Nom = L_Champ.at(0).trimmed();
            int L_Valeur = L_Champ.at(1).trimmed().toInt();

            if (L_Nom == "bat")
                PourcentageChargeBat = L_Valeur;
            else if (L_Nom == "yaw")
                Lacet = L_Valeur;
            else if (L_Nom == "roll")
                Roulis = L_Valeur;
            else if (L_Nom == "pitch")
                Tangage = L_Valeur;
        }

        //-----A Complété--------------
        // Afficher les données de vol dans l'IHM (horizon artificiel, etc...)
        L_PtMainWindows->AfficherDonneesVol(Tangage, Roulis, Lacet, PourcentageChargeBat);
    }
}

//-----A Complété--------------
// Envoie une commande texte au drone (port de commande 8889)
void CDrone::EnvoyerCommande(const QByteArray &P_Commande)
{
    SocketPourCommandeAcquittementDrone.writeDatagram(P_Commande,
                                                      QHostAddress(IP_DRONE),
                                                      Num_Port_Command);
}

//-----A Complété--------------
// Slot connecté au bouton "Décoller"
void CDrone::Decoller(void)
{
    EnvoyerCommande("takeoff");
}

//-----A Complété--------------
// Slot connecté au bouton "Atterrir"
void CDrone::Atterrir(void)
{
    EnvoyerCommande("land");
}

// Slot appelé à chaque réception d'un acquittement de commande
void CDrone::AcquittementCommandesRecues(void)
{
    while (SocketPourCommandeAcquittementDrone.hasPendingDatagrams())
    {
        QHostAddress L_IPDrone;
        quint16 L_PortDrone;
        QByteArray datagram;
        datagram.resize((int)SocketPourCommandeAcquittementDrone.pendingDatagramSize());

        //-----A Complété--------------
        // Lecture des acquittements reçus ("ok", "error", ...)
        SocketPourCommandeAcquittementDrone.readDatagram(datagram.data(), datagram.size(),
                                                         &L_IPDrone, &L_PortDrone);

        //-----A Complété--------------
        // Afficher l'acquittement à destination de l'utilisateur
        L_PtMainWindows->AfficherMessageUtilisateur("Réponse du drone : "
                                                    + QString::fromLatin1(datagram).trimmed());
    }
}
