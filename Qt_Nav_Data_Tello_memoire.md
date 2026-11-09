# Mémoire projet : Qt_Nav_Data_Tello

Projet : `T:\CHAUMEIL\TP OSI4_UDP\Dossier Etudiants\Qt_Nav_Data_Tello`
Projet de référence (partie UDP) : `T:\CHAUMEIL\TP OSI4_UDP\Dossier Etudiants\Serveur_UDP_Qt_Console`
Date : 2026-11-09

## Objectif
Afficher les données de vol d'un drone Tello (QUdpSocket) dans l'IHM Qt, puis ajouter des boutons Décoller / Atterrir. Code commenté en français.

## Fichiers modifiés

### cdrone.cpp
- `CDrone()` : mémorise le pointeur `MainWindow`, initialise `PourcentageChargeBat`, `Tangage`, `Roulis`, `Lacet` à 0.
- `InitialisationCommunication()` : bind du socket de données sur le port 8890, connexion des signaux `readyRead`, envoi de `"command"` (mode SDK) à `IP_DRONE`:8889 via `SocketPourCommandeAcquittementDrone`.
- `DonneesDeVolRecues()` : `readDatagram`, `split(';')` puis `split(':')`, lecture de `bat`, `yaw`, `roll`, `pitch` (comparaison exacte du nom, `trimmed()`), puis appel de `MainWindow::AfficherDonneesVol(...)`.
- `AcquittementCommandesRecues()` : lit la réponse (`ok`/`error`) et l'affiche avec `AfficherMessageUtilisateur("Réponse du drone : ...")`.
- Ajouts boutons : `EnvoyerCommande(QByteArray)`, `Decoller()` (envoie `"takeoff"`), `Atterrir()` (envoie `"land"`).
- Retrait de `#include <windows.h>` (inutile).

### cdrone.h
- Déclaration de `Decoller()` et `Atterrir()` (public slots) et de `EnvoyerCommande()` (private).
- `IP_DRONE` a été changé par l'utilisateur : `"172.20.24.38"` (valeur utilisée dans le serveur console). Précédemment `192.168.1.36`.

### mainwindow.ui / .h / .cpp
- `.ui` : deux `QPushButton` : `BoutonDecoller` (« Décoller ») et `BoutonAtterrir` (« Atterrir »), sous la zone de messages (selon la capture de l'énoncé).
- `.h` : déclaration anticipée `class CDrone;` (évite l'inclusion circulaire, `cdrone.h` inclut `mainwindow.h`), membre privé `CDrone *ptr_drone`, méthode publique `DefinirDrone(CDrone*)`, slots privés `on_BoutonDecoller_clicked()` et `on_BoutonAtterrir_clicked()`. Les signaux `DemandeDecollage()` / `DemandeAtterrissage()` sont **mis en commentaire** (plus utilisés).
- `.cpp` : `#include "cdrone.h"`, `ptr_drone` initialisé à `nullptr` dans le constructeur. Chaque slot déclare un pointeur local sur son bouton (`ptr_decoller`, `ptr_atterir`, type `QPushButton*`), vérifie que `ptr_drone` n'est pas nul (sinon message « Drone non initialisé »), appelle **directement** `ptr_drone->Decoller()` / `ptr_drone->Atterrir()`, puis affiche « Commande de vol : <texte du bouton> demandé ».

### main.cpp
- Plus aucun `QObject::connect` actif (anciens `connect` SIGNAL/SLOT et syntaxe `&Classe::méthode` mis en commentaire).
- Un seul appel : `w.DefinirDrone(&LeDrone);` donne à `MainWindow` son pointeur vers `CDrone`.

## Historique de la conception des commandes de vol
1. `emit` de signaux dans `MainWindow` + `QObject::connect` SIGNAL/SLOT dans `main.cpp`.
2. Refonte d'après l'UML : même principe, syntaxe `&MainWindow::DemandeDecollage` → `&CDrone::Decoller`.
3. **Version actuelle** : pointeur `ptr_drone` dans `MainWindow`, appel direct de `Decoller()` / `Atterrir()`, plus de `connect` dans `main.cpp`.
Règle : le code remplacé est mis en commentaire, jamais supprimé.

## Diagramme UML
Fichier : `T:\Claude\Qt_Nav_Data_Tello_UML.png` (régénéré le 2026-11-09, la source BOUML du dossier `diag/` n'a pas été modifiée).
Changements par rapport à la capture d'origine : `MainWindow` perd les signaux `DemandeDecollage()` / `DemandeAtterrissage()`, gagne l'attribut `ptr_drone` et la méthode `DefinirDrone()` ; nouvelle association `MainWindow` → `CDrone` (`ptr_drone`), en plus de `CDrone` → `MainWindow` (`L_PtMainWindows`). Les deux classes se connaissent donc mutuellement.

## Convention de commentaires
Marqueur `//-----A Complété--------------` (version de l'utilisateur) placé au-dessus de chaque partie ajoutée, sur le modèle des anciens `-----A compléter-----`. Pas de marqueur dans le `.ui` (XML régénéré par Qt Designer).

## Ce qui est repris du serveur console
Envoi de `"command"` vers le port 8889, bind sur 8890 avec `QHostAddress::Any`, boucle `hasPendingDatagrams` / `readDatagram`, découpage par `;`, gestion de `ok`/`error`.
Non repris : `QString` + `startsWith` (j'ai gardé `QByteArray`, comme le squelette du TP), socket alloué par `new`, affichage `cout`, champs `agx/agy/agz`.
Deux sockets (données / commandes) comme dans le squelette `cdrone.h`.

## Problème de compilation rencontré
`ld.exe: skipping incompatible libqfi.a / qfi.dll ... cannot find -lqfi`
Cause : `qfi.dll` est en 32 bits (Intel i386), le kit utilisé était MinGW 64-bit.
Solution : utiliser le kit **Desktop Qt 5.12.3 MinGW 32-bit** (Projets → activer ce kit, Nettoyer tout, Exécuter qmake, recompiler). Copier `qfi.dll` à côté de l'exécutable si besoin.

## Savoir si le drone est connecté
UDP sans connexion : aucune erreur si le drone est absent. Indices :
- message « Réponse du drone : ok » après `command` ;
- BAT ≠ 0 % et Pitch/Roll/Yaw qui bougent.
Prérequis : PC sur le Wi-Fi du Tello, bonne `IP_DRONE` (192.168.10.1 en Wi-Fi direct du Tello), pare-feu Windows autorisant l'application.
Amélioration proposée (non faite) : indicateur « connecté / non connecté » avec `QTimer` (timeout 2 s sans données de vol).

## Non vérifié
Aucune compilation ni test avec un drone réel effectués par Claude (y compris la version avec `ptr_drone`).
