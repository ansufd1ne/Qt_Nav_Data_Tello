#ifndef CDRONE_H
#define CDRONE_H
#include <QUdpSocket>
#include <QObject>
#include <QTimer>
#include "mainwindow.h"

#define Num_Port_Navdata 8890
#define Num_Port_Command 8889

#define IP_DRONE "172.20.24.38"

class CDrone : public QObject
{
Q_OBJECT
private:
 QUdpSocket udpSocketServeurReceptionDonneesDeVol;
 QUdpSocket SocketPourCommandeAcquittementDrone;
 MainWindow *L_PtMainWindows;

int PourcentageChargeBat;
int Tangage;
int Roulis;
int Lacet;

public:
    CDrone(MainWindow *PtMainWindows);
    void InitialisationCommunication(void);

public slots :
void DonneesDeVolRecues(void);
void AcquittementCommandesRecues(void);
//-----A Complété--------------
void Decoller(void);     // envoie "takeoff" au drone
void Atterrir(void);     // envoie "land" au drone

private:
//-----A Complété--------------
void EnvoyerCommande(const QByteArray &P_Commande);   // envoi d'une commande UDP au drone

};

#endif // CDRONE_H
