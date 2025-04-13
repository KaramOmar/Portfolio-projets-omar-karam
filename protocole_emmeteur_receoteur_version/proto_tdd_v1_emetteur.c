#include <stdio.h>
#include "application.h"
#include "couche_transport.h"
#include "services_reseau.h"

/* =============================== */
/* Programme principal - émetteur  */
/* =============================== */
int main(int argc, char* argv[]) {
    unsigned char message[MAX_INFO]; /* message de l'application */
    int taille_msg; /* taille du message */
    paquet_t paquet; /* paquet utilisé par le protocole */
    paquet_t p_controle;

    init_reseau(EMISSION);

    printf("[TRP] Initialisation reseau : OK.\n");
    printf("[TRP] Debut execution protocole transport.\n");
        /* lecture de donnees provenant de la couche application */
    de_application(message, &taille_msg);
        
        /* tant que l'émetteur a des données à envoyer */
    while (taille_msg != 0) {
            /* construction paquet */
        for (int i=0; i<taille_msg; i++) {
            paquet.info[i] = message[i];
        }
        paquet.lg_info = taille_msg;
        paquet.type = DATA;
        paquet.somme_ctrl = generer_controle(paquet);
            
            /* remise à la couche reseau */
        do {
            vers_reseau(&paquet);
            de_reseau(&p_controle);
        } while (paquet.type == NACK); // tant que le paquet n'a pas été envoyé
            
            /* lecture des donnees suivantes de la couche application */
            de_application(message, &taille_msg);
        }
    printf("[TRP] Fin execution protocole transfert de donnees (TDD).\n");
    return 0;
}