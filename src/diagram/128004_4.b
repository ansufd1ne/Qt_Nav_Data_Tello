class CDrone
!!!128004.cpp!!!	CDrone(inout PtMainWindows : MainWindow)

L_PtMainWindows=PtMainWindows;
!!!128132.cpp!!!	InitialisationCommunication(in  : void) : void

    qint64 NbCaracRecus;
    char tampon_recep[1000];
    quint16 Portdistant;
    QHostAddress AdresseDistante;
    udpSocketServeurReceptionDonneesDeVol.bind(QHostAddress::Any,8890);
    connect(&udpSocketServeurReceptionDonneesDeVol, SIGNAL(readyRead()),
            this, SLOT(DonneesDeVolRecues()));

    connect(&SocketPourCommandeAcquittementDrone, SIGNAL(readyRead()),
              this, SLOT(AcquittementCommandesRecues()));


    //Initialisation de la communication avec le drone pour demander l'envoie des données de vol
    //-----A compléter--------------
   
   

   
!!!128260.cpp!!!	DonneesDeVolRecues(in  : void) : void

     while (udpSocketServeurReceptionDonneesDeVol.hasPendingDatagrams())
     {
         QHostAddress L_IPDrone;
         quint16 L_PortDrone;
         QByteArray datagram;
         datagram.resize((int)udpSocketServeurReceptionDonneesDeVol.pendingDatagramSize());

         //Lecture des données de vol reçues
        //-----A compléter--------------
        
		//On sélectionne les éléments à afficher
         QList<QByteArray> L_Liste_Donnees_De_Vol = datagram.split(';');
         foreach (QByteArray Element_Liste_De_Vol, L_Liste_Donnees_De_Vol)
         {
             if(Element_Liste_De_Vol.contains("bat"))
             {
                 QList<QByteArray> L_Bat = Element_Liste_De_Vol.split(':');
                 PourcentageChargeBat=L_Bat.at(1).toInt();

             }

			//Faire de même pour yaw, roll et pitch
             //-----A compléter--------------

         }

	//Afficher les données de vol dans l'ihm (horizon artificiel, etc...)
       //-----A compléter--------------


 }
!!!128388.cpp!!!	AcquittementCommandesRecues(in  : void) : void


      while (SocketPourCommandeAcquittementDrone.hasPendingDatagrams())
      {
          QHostAddress L_IPDrone;
          quint16 L_PortDrone;
          QByteArray datagram;
          datagram.resize((int)SocketPourCommandeAcquittementDrone.pendingDatagramSize());

          //Lecture des données des acquittements reçus
         //-----A compléter--------------


          //Affaicher l'acquittement à destination de l'utilisateur
          //-----A compléter--------------


      }
