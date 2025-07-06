#include <stdio.h>
#include <stdlib.h>
#include "application.h"
#include "couche_transport.h"
#include "services_reseau.h"

#define MAX_TAILLE_FENETRE 8 // Taille maximale de la fenêtre autorisée
#define INTERVAL_TEMPO 1 //  Temporisateur en secondes


/* =============================== */
/* Programme principal - récepteur */
/* =============================== */

int main(int argc, char *argv[]) {
    paquet_t trame_recue; // Utilisation de 'trame_recue' pour le paquet reçu
    uint8_t num_seq_vise = 0; // Numéro de séquence attendu
    int en_cours = 1; //  Pour contrôler la boucle principale
    int taille_fenetre_effective = 4; // Taille de la fenêtre d'envoi active
    int compteur_paquets = 0; // Pour compter les paquets reçus correctement

    // Configuration de la taille de la fenêtre
    if (argc == 2 && atoi(argv[1]) <= SEQ_NUM_SIZE / 2) {
        taille_fenetre_effective = atoi(argv[1]);
    }

    init_reseau(RECEPTION);
    printf("[Récepteur] Prêt et en attente de données...\n");
    
    // Boucle principale de réception
    for (;en_cours;) {
        de_reseau(&trame_recue); // Réception d'une trame du réseau
        // Vérifie si la trame reçue est correcte
        if (verifier_controle(trame_recue)) {
            uint8_t ecart = (trame_recue.num_seq + SEQ_NUM_SIZE - num_seq_vise) % SEQ_NUM_SIZE;
            // Si la trame est dans la fenêtre de réception
            
            if (ecart < taille_fenetre_effective) {
                
                num_seq_vise = (trame_recue.num_seq + 1) % SEQ_NUM_SIZE;
                trame_recue.type = ACK; // Préparation de l'acquittement
                vers_reseau(&trame_recue); // Envoi de l'acquittement
                compteur_paquets++;
                if (vers_application(trame_recue.info, trame_recue.lg_info)) en_cours = 0;
            } else if (ecart >= SEQ_NUM_SIZE - taille_fenetre_effective && ecart < SEQ_NUM_SIZE) {
                trame_recue.type = ACK;
                vers_reseau(&trame_recue);
            }
            // Une condition pour terminer la réception si tous les paquets ont été reçus
            if (compteur_paquets >= SEQ_NUM_SIZE) en_cours = 0;
        }
    }

    printf("[Récepteur] Transmission terminée.\n");
    return 0;
}
