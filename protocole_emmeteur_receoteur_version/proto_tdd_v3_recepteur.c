#include "application.h"
#include "couche_transport.h"
#include "services_reseau.h"
#include <stdio.h>

/* =============================== */
/* Programme principal - récepteur */
/* =============================== */
int main(int argc, char *argv[]) {
    unsigned char message[MAX_INFO]; /* message pour l'application */
    paquet_t paquet, p_controle;           /* paquet utilisé par le protocole */
    int fin = 0;                     /* condition d'arrêt */
    int seq_attendu = 0;

    init_reseau(RECEPTION);

    printf("[TRP] Initialisation reseau : OK.\n");
    printf("[TRP] Debut execution protocole transport.\n");

    /* tant que le récepteur reçoit des données */
    while (!fin) {
        // attendre();
        de_reseau(&paquet);
        if (verifier_controle(paquet) && seq_attendu == paquet.num_seq) {
            p_controle.num_seq = seq_attendu;
            /* extraction des donnees du paquet recu */
            for (int i = 0; i < paquet.lg_info; i++) {
                message[i] = paquet.info[i];
            }
            fin = vers_application(message, paquet.lg_info);
            inc(&seq_attendu);
        } else { p_controle.num_seq = seq_attendu - 1; }
        p_controle.lg_info = 0;
        p_controle.type = ACK;
        p_controle.somme_ctrl = generer_controle(p_controle);
        vers_reseau(&p_controle);
    }

    printf("[TRP] Fin execution protocole transport.\n");
    return 0;
}
