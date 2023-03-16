Projet Démonstrateur IoT

Partie interface microcontrôleur -> capteur

Cette bibliothèque permet de gérer les capteurs de la partie microcontrôleur du projet démonstrateur IoT.

Pour ce projet nous utilisons la library arduino pour le microcontrôleur ESP32 pour faciliter l'utilisation de la bibliothèque SoftwareSerial pour la liaison série entre le microcontrôleur et le capteur. Nous avons donc utilisé le port série 0 (RX0 et TX0) pour la liaison série entre le microcontrôleur et le capteur. Ce port est utilisé par le module USB du microcontrôleur.

fall_detection.h recence toutes les variables et fonctions proposé par le capteur.
fall_detection.cpp contient l'implémentation de certaines fonctions qui nous interessent dans le projet utilisant les variables de fall_detection.h
Main_Detection.cpp contient le code principal du projet utilisant les fonctions de fall_detection.cpp

Pour l'instant toutes les informations de présence ou de chute sont affichées sur le port série du microcontrôleur, cela est siffisant pour effectier les tests.Dans la suite les donées seront partagé avec la connexion EspNow.
