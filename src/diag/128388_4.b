class MainWindow
!!!129028.cpp!!!	MainWindow(inout parent : QWidget = nullptr)

ui->setupUi(this);
//Message de départ
QString MessageColore="<br><span style=\"color: red;\">Initialisation du drone</span>";
ui->textEdit_Messages->insertHtml(MessageColore);
!!!129412.cpp!!!	AfficherMessageUtilisateur(in P_Message : QString) : void

    QString MessageColore="<br><span style=\"color: green;\">"+P_Message+"</span>";
    ui->textEdit_Messages->insertHtml(MessageColore);
!!!129284.cpp!!!	AfficherDonneesVol(in P_Tangage : int, in P_Roulis : int, in P_Lacet : int, in P_PourcentageBat : int) : void

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
!!!129796.cpp!!!	on_BoutonDecoller_clicked(in  : void) : void

    AfficherMessageUtilisateur("Commande envoyée : décollage");
    emit DemandeDecollage();
!!!129924.cpp!!!	on_BoutonAtterrir_clicked(in  : void) : void

    AfficherMessageUtilisateur("Commande envoyée : atterrissage");
    emit DemandeAtterrissage();
!!!129156.cpp!!!	~MainWindow()

    delete ui;
