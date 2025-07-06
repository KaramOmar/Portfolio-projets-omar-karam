#ifndef __APPLICATION_H__
#define __APPLICATION_H__

/****************************************
 * Interface avec la couche application *
 ****************************************/

/* =========================================================== */
/* ==================== Mode non connecté ==================== */
/* =========================================================== */

/*
 * Lecture de données émanant de la couche application.
 * Paramètres (en sortie):
 *  - donnees : message devant être envoyé (issu de la couche application)
 *  - taille_msg : nombre d'octets de données à émettre (0 si pas de données)
 */
void de_application(unsigned char *donnees, int *taille_msg);

/*
 * Remise de données à la couche application.
 * Paramètres (en entrée):
 *  - donnees : données à remonter à l'application
 *  - taille_msg : taille des données en octets
 * Renvoie :
 *    -> 1 si le récepteur n'a plus rien à écrire (fichier terminé)
 *    -> 0 sinon
 */
int vers_application(unsigned char *donnees, int taille_msg);

/* ======================================================= */
/* ==================== Mode connecté ==================== */
/* ======================================================= */

/* Services du mode connecté */

/* demande d'établissement de connexion */
#define T_CONNECT          11
/* réponse à la demande de connexion : acceptation */
#define T_CONNECT_ACCEPT   12
/* réponse à la demande de connexion : refus */
#define T_CONNECT_REFUSE   13
/* transfert d'une unité de données au sein d'une connexion */
#define T_DATA             14
/* fermeture de connexion */
#define T_DISCONNECT       15

/*
 * Lecture du service demandé par la couche application. Ce service peut être :
 * une demande de connexion, un transfert d'une unité de données, ou encore
 * une demande de déconnexion.
 * Paramètres (en sortie):
 *   - service : service demandé par l'application (T_CONNECT, T_DATA ou T_DISCONNECT)
 *   - donnees : message devant être envoyé (issu de la couche application)
 *   - taille_msg : nombre d'octets de données à émettre (0 si pas de données)
 */
void de_application_mode_c(int *service, unsigned char *donnees, int *taille_msg);

/*
 * Remise du service à la couche application. Ce service peut être :
 * une demande de connexion, un transfert d'une unité de données, ou encore
 * une notification de déconnexion.
 * Paramètres (en entrée):
 *   - service : service remonté à la couche application (T_CONNECT, T_DATA ou T_DISCONNECT)
 *   - donnees : données à remonter à l'application
 *   - taille_msg : taille des données (0 si pas de données)
 * Renvoie :
 *   - Si service = T_CONNECT
 *     --> La réponse à la demande de connexion (T_CONNECT_ACCEPT ou T_CONNECT_REFUSE)
 *   - Si service ≠ T_CONNECT
 *     --> 0 si OK
 *   - Dans tous les cas : -1 si erreur
 */
int vers_application_mode_c(int service, unsigned char *donnees, int taille_msg);

#endif
