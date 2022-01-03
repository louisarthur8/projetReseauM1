#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#define PORT 4444
int main(int argc, char const *argv[])
{
	int server_fd, new_socket, valread = 0;
	struct sockaddr_in address;
	int opt = 1;
	int addrlen = sizeof(address);
	
	// Création socket
	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
	{
		perror("socket failed");
		exit(EXIT_FAILURE);
	}
	
	// attache de la socket au port
	if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
												&opt, sizeof(opt)))
	{
		perror("setsockopt");
		exit(EXIT_FAILURE);
	}
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons( PORT );
	
	// Attache de la socket au port
	if (bind(server_fd, (struct sockaddr *)&address,
								sizeof(address))<0)
	{
		perror("bind failed");
		exit(EXIT_FAILURE);
	}
	if (listen(server_fd, 3) < 0)
	{
		perror("listen");
		exit(EXIT_FAILURE);
	}
	if ((new_socket = accept(server_fd, (struct sockaddr *)&address,
					(socklen_t*)&addrlen))<0)
	{
		perror("accept");
		exit(EXIT_FAILURE);
	}

	char buffer[3] = {0};

	valread = (int)read( new_socket , buffer, 3);
	printf("Communication reçue...\n\n");

	if (buffer[0] != 0) { //mode sondage

		printf("Réponse question 1 : %d\n",buffer[0] );
		printf("Réponse question 2 : %d\n",buffer[1] );
		printf("Réponse question 3 : %d\n\n",buffer[2] );

		printf("Inscription des réponses dans les fichiers...");

		FILE* f1 = NULL;
		f1 = fopen("q1.txt", "a"); //ouverture du fichier en mode ajout
		if (f1 != NULL) {
			fputc(buffer[0]+'0', f1);
			fclose(f1);
		}
		else { //erreur dans l'ouverture du fichier
			printf("Erreur : impossible d'ouvrir le fichier");
		}
		
		FILE* f2 = NULL;
		f2 = fopen("q2.txt", "a"); //ouverture du fichier en mode ajout
		if (f2 != NULL) {
			fputc(buffer[1]+'0', f2);
			fclose(f2);
		}
		else { //erreur dans l'ouverture du fichier
			printf("Erreur : impossible d'ouvrir le fichier");
		}

		FILE* f3 = NULL;
		f3 = fopen("q3.txt", "a"); //ouverture du fichier en mode ajout
		if (f3 != NULL) {
			fputc(buffer[2]+'0', f3);
			fclose(f3);
		}
		else { //erreur dans l'ouverture du fichier
			printf("Erreur : impossible d'ouvrir le fichier");
		}	
		printf(" OK\n");
	}

	else { //mode résultats du sondage
		printf("Résultats demandés...\n\nQ1 : Lecture des résultats : \n\n");
		
		int result = 0;
		int nbOui1 = 0;
		int nbTotal1 = 0;
	
		FILE* f1 = NULL;
		f1 = fopen("q1.txt", "r"); //ouverture du fichier en mode ajout
		if (f1 != NULL) {
			do
			{
				result = fgetc(f1);
				//printf("%c", result);
				if (result == '1' || result == '2') {
					nbTotal1 ++;
					if (result == '1') {
						nbOui1 ++;
					}
				}
			} while (result != EOF);
			printf("Nombre de oui : %d\nTotal de participants : %d\n\n", nbOui1, nbTotal1);
		}
		else { //erreur dans l'ouverture du fichier
			printf("Erreur : impossible d'ouvrir le fichier");
		}
		
		printf("Q2 : Lecture des résultats\n\n");

		result = 0;
		int nbOui2 = 0;
		int nbTotal2 = 0;
	
		FILE* f2 = NULL;
		f2 = fopen("q2.txt", "r"); //ouverture du fichier en mode ajout
		if (f2 != NULL) {
			do
			{
				result = fgetc(f2);
				//printf("%c", result);
				if (result == '1' || result == '2') {
					nbTotal2 ++;
					if (result == '1') {
						nbOui2 ++;
					}
				}				
			} while (result != EOF);
			printf("Nombre de oui : %d\nTotal de participants : %d\n", nbOui2, nbTotal2);
		}
		else { //erreur dans l'ouverture du fichier
			printf("Erreur : impossible d'ouvrir le fichier");
		}
		
		printf("\nQ3 : Lecture des résultats\n\n");

		result = 0;
		int nbOui3 = 0;
		int nbTotal3 = 0;
	
		FILE* f3 = NULL;
		f3 = fopen("q3.txt", "r"); //ouverture du fichier en mode ajout
		if (f3 != NULL) {
			do
			{
				result = fgetc(f3);
				//printf("%c", result);
				if (result == '1' || result == '2') {
					nbTotal3 ++;
					if (result == '1') {
						nbOui3 ++;
					}
				}
				
			} while (result != EOF);
			printf("Nombre de oui : %d\nTotal de participants : %d\n", nbOui3, nbTotal3);
		}
		else { //erreur dans l'ouverture du fichier
			printf("Erreur : impossible d'ouvrir le fichier");
		}

		printf("\nCréation du contenu de la socket...\n");
		int envoi[6];
		envoi[0] = nbTotal1;
		envoi[1] = nbOui1;
		envoi[2] = nbTotal2;
		envoi[3] = nbOui2;
		envoi[4] = nbTotal3;
		envoi[5] = nbOui3;
		printf("Envoi de la socket au client...\n");
		send(new_socket , envoi , sizeof(envoi) , 0 ); //envoi de la socket contenant les résultats du sondage.


	}
	valread +=1; //opération bidon pour enlever le "warning : set but not used"
	return 0;
}
