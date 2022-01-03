#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#define PORT 4444

int main(int argc, char const *argv[])
{

	//Sélection du mode 

	printf("Bienvenue sur cette application de sondage.\n");
	bool proceed = true;
	int reponse, num;
	while (proceed) {
		printf("Entrez 1 pour participer au sondage ou 2 pour voir les résultats.\n");	
		scanf("%d", &num);
		reponse = num;
		if (reponse == 1 || reponse == 2) {
			proceed = false;
		}
		else {
			printf("Commande inconnue, veuillez reessayer.\n");
		}
	}

	int r1 = 0;
	int r2 = 0;
	int r3 = 0;

	if (reponse == 1) { //Mode sondage
		


		proceed = true;
		while (proceed) { //Question 1
			printf("Aimez-vous l'informatique ? 1-oui, 2-non\n");
			scanf("%d", &r1);
			if (r1 == 1 || r1 == 2) {
				proceed = false;
			}
			else {
				printf("Commande inconnue, veuillez reessayer.\n");
			}
		}

		proceed = true;
		while (proceed) { //Question 2
			printf("Aimez-vous la programmation réseau ? 1-oui, 2-non\n");
			scanf("%d", &r2);
			if (r2 == 1 || r2 == 2) {
				proceed = false;
			}
			else {
				printf("Commande inconnue, veuillez reessayer.\n");
			}
		}

		proceed = true;
		while (proceed) { //Question 3
			printf("Aimez-vous Monsieur Cervelle ? 1-oui, 2-non\n");
			scanf("%d", &r3);
			if (r3 == 1 || r3 == 2) {
				proceed = false;
			}
			else {
				printf("Commande inconnue, veuillez reessayer.\n");
			}
		}

		printf("\nEnvoi des réponses au serveur... \n\n");
	}

	char envoi[] = "000"; //chaîne de caractères envoyée dans la socket
	envoi[0] = (char)r1;
	envoi[1] = (char)r2;
	envoi[2] = (char)r3;
 
	int sock = 0;
	struct sockaddr_in serv_addr;

	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		printf("\n Erreur de creation de socket \n");
		return -1;
	}

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(PORT);

	// Conversion de l'adrasse IP texte -> binaire
	if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0)
	{
		printf("\n Adresse Invalide \n");
		return -1;
	}

	if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
	{
		printf("\nEchec de Connexion avec le serveur.\n");
		return -1;
	}
	send(sock , envoi , sizeof(envoi) , 0 ); //envoi de la socket contenant les réponses.

	if (reponse == 2) { //mode résultats
		printf("Demande de résultats au serveur...\n\n");
		int buffer[6] = {0};
		int valread = (int)read( sock , buffer, 1024);
		printf("Résultats reçus !\n\n");

		printf("Q1 : Aimez-vous l'informatique ?\nSur %d participants, %d %% ont répondu oui !\n\n", buffer[0], (int)(100*(double)buffer[1]/(double)buffer[0]));

		printf("Q2 : Aimez-vous la programmation réseau ?\nSur %d participants, %d %% ont répondu oui !\n\n", buffer[2], (int)(100*(double)buffer[3]/(double)buffer[2]));

		printf("Q3 : Aimez-vous Monsieur Cervelle ?\nSur %d participants, %d %% ont répondu oui !\n\n", buffer[4], (int)(100*(double)buffer[5]/(double)buffer[4]));



		valread += 1; //opération bidon pour enlever le "warning : set but not used"
	}

	return 0;
}
