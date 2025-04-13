#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // Pour sleep()
#include "application.h"
#include "couche_transport.h"
#include "services_reseau.h"

#define TAILLE_FENETRE_MAX 8 // Taille maximale de la fenêtre
#define INTERVALLE_TEMPS 1 // Intervalle de temps pour le timeout

/* =============================== */
/* Programme principal - émetteur  */
/* =============================== */

// Indicateur d'activité du temporisateur
int temporisateur_actif = 0;

// Démarrer le temporisateur pour un paquet spécifique
void demarrer_temporisateur() {
    if (!temporisateur_actif) {
        temporisateur_actif = 1;
        sleep(INTERVALLE_TEMPS);
        temporisateur_actif = 0; // Réinitialiser après expiration
    }
}

int main(int argc, char *argv[]) {
    unsigned char donnees[MAX_INFO];
    int longueur; // taille de message
    paquet_t tampons[SEQ_NUM_SIZE]; // Stockage temporaire des paquets
    uint8_t prochain = 0; 
    uint8_t fenetre_debut = 0; 
    int taille_fenetre = TAILLE_FENETRE_MAX; // Taille de la fenêtre de transmission

    
    if (argc == 2) {
        int nouvelle_taille = atoi(argv[1]);
        if (nouvelle_taille <= TAILLE_FENETRE_MAX)
            taille_fenetre = nouvelle_taille;
    }

    init_reseau(EMISSION);
    printf("[Émetteur] Prêt pour l'envoi de données.\n");

    
    de_application(donnees, &longueur);
    while (longueur > 0 || fenetre_debut != prochain) {
        if ((prochain - fenetre_debut < taille_fenetre) && longueur > 0) {
            // Préparation du paquet à envoyer
            tampons[prochain].lg_info = longueur;
            tampons[prochain].type = DATA;
            tampons[prochain].num_seq = prochain;
            for (int j = 0; j < longueur; ++j) {
                tampons[prochain].info[j] = donnees[j];
            }
            tampons[prochain].somme_ctrl = generer_controle(tampons[prochain]);
            vers_reseau(&tampons[prochain]);

            demarrer_temporisateur();
            inc(&prochain);
            de_application(donnees, &longueur);
        } else {
            // Gestion de l'attente 
            int action = attendre();
            if (action == -1) {
                de_reseau(&tampons[fenetre_debut]);
                if (verifier_controle(tampons[fenetre_debut]) && fenetre_debut < prochain) {
                    inc(&fenetre_debut);
                }
            } else {
                // Renvoi des paquets 
                for (int j = fenetre_debut; j < prochain; ++j) {
                    vers_reseau(&tampons[j]);
                }
            }
        }
    }

    printf("[Émetteur] Fin de l'envoi de données.\n");
    return 0;
}
