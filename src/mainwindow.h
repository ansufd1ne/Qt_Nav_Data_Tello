#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

// Déclaration anticipée (cdrone.h inclut mainwindow.h : évite l'inclusion circulaire)
class CDrone;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void AfficherDonneesVol(int P_Tangage, int P_Roulis, int P_Lacet, int P_PourcentageBat);
    void AfficherMessageUtilisateur(QString P_Message);
//-----A Complété--------------
/*
signals:
    // Émis quand l'utilisateur clique sur un bouton ; CDrone s'y connecte (voir main.cpp)
    void DemandeDecollage(void);
    void DemandeAtterrissage(void);

private slots:
    // Slots appelés automatiquement (convention on_<objet>_<signal>) au clic sur les boutons
    void on_BoutonDecoller_clicked(void);
    void on_BoutonAtterrir_clicked(void);
*/


/* VERSION PRÉCÉDENTE avec signaux + QObject::connect dans main.cpp (mise en commentaire)
signals:
    // Commandes de vol émises vers CDrone (connexion réalisée dans main.cpp)
    void DemandeDecollage(void);
    void DemandeAtterrissage(void);
*/

//-----Version avec pointeur vers CDrone (plus de QObject::connect dans main.cpp)--------------
public:
    // Mémorise le pointeur vers le drone : permet d'appeler directement Decoller() / Atterrir()
    void DefinirDrone(CDrone *P_PtDrone);

private slots:
    // Clic sur les boutons de l'IHM (connexion automatique via le nom on_<objet>_<signal>)
    void on_BoutonDecoller_clicked(void);
    void on_BoutonAtterrir_clicked(void);

private:
    Ui::MainWindow *ui;
    CDrone *ptr_drone;   // pointeur vers le drone (nullptr tant que DefinirDrone n'a pas été appelée)

};

#endif // MAINWINDOW_H
