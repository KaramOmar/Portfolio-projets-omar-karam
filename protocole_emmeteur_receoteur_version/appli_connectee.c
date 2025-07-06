/************************************************************
 *      APPLICATION de transfert de fichiers                *
 *                                                          *
 *  --> L'application s'appuie sur les services de          *
 *      transmission de la couche transport en mode         *
 *      connecté                                            *
 *                                                          *
 * E. Lavinal - Univ. de Toulouse III - Paul Sabatier       *
 ************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "application.h"
#include "config.h"

#define LECTURE_MAX 96

#define NON_CONNECTE 0
#define EN_COURS 1
#define CONNECTE 2

static int etat_connexion = NON_CONNECTE;
static FILE *fichier = NULL;

/*
 * Lecture du service demandé par la couche application. Ce service peut être :
 * une demande de connexion, un transfert d'une unité de données, ou encore
 * une demande de déconnexion.
 * Paramètres (en sortie):
 *   - service : service demandé par l'application (T_CONNECT, T_DATA ou T_DISCONNECT)
 *   - donnees : message devant être envoyé (issu de la couche application)
 *   - taille_msg : nombre d'octets de données à émettre (0 si pas de données)
 */
void de_application_mode_c(int *service, unsigned char *donnees, int *taille_msg) {

    switch (etat_connexion) {

        case NON_CONNECTE:
            /* demande de connexion */
            *service = T_CONNECT;
            *taille_msg = 0;
            printf("[APP] Demande de connexion transport...\n");
            etat_connexion = EN_COURS;
            break;

        case CONNECTE:
            if ( !feof(fichier) ) {
                /* lecture du fichier, au max LECTURE_MAX données */
                /* fread(void *restrict ptr, size_t size, size_t nitems,
                * FILE *restrict stream); */
                *taille_msg = fread(donnees, 1, LECTURE_MAX, fichier);
                *service = T_DATA;
                printf("\n[APP] Lecture fichier.\n");
            }
            else {
                /* fin du fichier donc déconnexion */
                fclose(fichier);
                *service = T_DISCONNECT;
                *taille_msg = 0;
                printf("[APP] Fin du fichier, demande de déconnexion.\n");
                etat_connexion = NON_CONNECTE;
            }
            break;

        case EN_COURS:
            printf("[APP] Patientez, en cours de connexion...");
            break;

        default:
            printf("[APP] Problème état de la connexion !");

    } /* switch */
}

/*
 * Remise du service à la couche application. Ce service peut être :
 * une demande de connexion, un transfert d'une unité de données, ou encore
 * une notification de déconnexion.
 * Paramètres (en entrée):
 *   - service : service remonté à la couche application (T_CONNECT, T_DATA ou T_DISCONNECT)
 *   - donnees : données à remonter à l'application
 *   - taille_msg : taille des données (0 si pas de données)
 * Renvoie :
 *   - Si service = CONNECT
 *     --> La réponse à la demande de connexion (T_CONNECT_ACCEPT ou T_CONNECT_REFUSE)
 *   - Si service ≠ CONNECT
 *     --> 0 si OK
 *   - Dans tous les cas : -1 si erreur
 */
int vers_application_mode_c(int service, unsigned char *donnees, int taille_msg) {
    char nom_fichier[30];

    switch (service) {

        case T_CONNECT:

            if (etat_connexion == NON_CONNECTE) {
                /* demande de connexion reçue. Par défaut, on accepte. */
                printf("[APP] Demande de connexion recue (on accepte)\n");
                /* ouverture du fichier en ecriture */
                conf_fichier_reception(nom_fichier);
                fichier = fopen(nom_fichier, "w");
                if (fichier == NULL) {
                    perror("[APP] Probleme ouverture fichier en écriture\n");
                    return T_CONNECT_REFUSE;
                }
                etat_connexion = CONNECTE;
                return T_CONNECT_ACCEPT; /* acceptation de connexion */
            }
            else {
                fprintf(stderr, "[APP] ATTENTION, demande de connexion recue dans ");
                fprintf(stderr, "un état incohérent !\n");
                return -1;
            }
            break;

        case T_CONNECT_ACCEPT:

            if (etat_connexion == EN_COURS) {
                /* réponse à la demande de connexion -> OK */
                printf("[APP] Réponse demande de connexion : acceptée.\n");
                /* ouverture du fichier en lecture */
                conf_fichier_emission(nom_fichier);
                fichier = fopen(nom_fichier, "r");
                if (fichier == NULL) {
                    perror("[APP] Probleme ouverture fichier en lecture\n");
                    exit(1);
                }
                etat_connexion = CONNECTE;
            }
            else {
                fprintf(stderr, "[APP] ATTENTION, réponse de connexion recue dans ");
                fprintf(stderr, "un état incohérent !\n");
                return -1;
            }
            break;

        case T_CONNECT_REFUSE:

            if (etat_connexion == EN_COURS) {
                /* réponse à la demande de connexion -> NOT OK */
                printf("[APP] Réponse demande de connexion : refusée.\n");
                exit(1);
            }
            else {
                fprintf(stderr, "[APP] ATTENTION, réponse de connexion recue dans ");
                fprintf(stderr, "un état incohérent !\n");
                return -1;
            }
            break;

        case T_DATA:

            if (etat_connexion == CONNECTE) {
                /* données reçues */
                if (fichier == NULL) {
                    perror("[APP] Données reçues mais fichier non ouvert !\n");
                    exit(1);
                }
                /* ecriture des données dans le fichier */
                printf("[APP] Ecriture fichier.\n\n");
                fwrite(donnees, 1, taille_msg, fichier);
                fflush(fichier);
            }
            else {
                fprintf(stderr, "[APP] ATTENTION, données recues hors connexion !\n");
                return -1;
            }
            break;

        case T_DISCONNECT:

            if (etat_connexion == CONNECTE) {
                /* deconnexion recue */
                fclose(fichier);
                printf("[APP] Déconnexion recue. Fichier fermé.\n");
                etat_connexion = NON_CONNECTE;
            }
            else {
                fprintf(stderr, "[APP] ATTENTION, déconnexion recue hors connexion !\n");
                return -1;
            }
            break;

        default:
            /* service inconnu */
            printf("[APP] vers_application_mode_c: service inconnu !\n");
    } /* switch */
    return 0;
}
