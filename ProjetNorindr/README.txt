Projet de Louis-Arthur Norindr

Sujet : Logiciel de sondage à 2 choix

Comment lancer le projet :
Ouvrir 2 fenêtre du terminal différentes.
Positionner la première dans le dossier "client" du projet, puis faire "make"
Positionner la seconde dans le dossier "server" du projet, puis faire "make"
Exécuter server.exe, puis client.exe dans leurs fenêtres respectives.

Comment tester le projet :
La première fenre à avoir la main est le client.
Celui-ci peut choisir entre participer au sondage, ou avoir les résultats.
S'il participe au sondage, il répond à 3 questions. Les résultats sont envoyés au serveur, qui les stock dans des fichiers. Il est possible de voir ces fichiers dans le dossier server. Il faut alors relancer server.exe, puis client.exe.
Si le client choisit d'avoir les résultats, il en envoie la requête au serveur, qui lui renvoie les résultats. Les fichiers sont déjà remplis de quelques données lors du premier lancement.
