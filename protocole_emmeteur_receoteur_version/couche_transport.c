#include <stdio.h>
#include "couche_transport.h"
#include "services_reseau.h"
#include "application.h"

int paquet_num = 0;
/* ************************************************************************** */
/* *************** Fonctions utilitaires couche transport ******************* */
/* ************************************************************************** */

// RAJOUTER VOS FONCTIONS DANS CE FICHIER...
    uint8_t generer_controle(struct paquet_s paq) {
    uint8_t ctrl = paq.type ^ paq.num_seq ^ paq.lg_info;
    for (int i = 0; i < paq.lg_info; i++) {
        ctrl ^= paq.info[i];
    }
    return ctrl;
}
    // pour vérifier une somme de contrôle dans le paquet reçu
bool verifier_controle(struct paquet_s paq) {
    uint8_t ctrl_recu = generer_controle(paq);
    if (ctrl_recu == paq.somme_ctrl)
        return true;
    return false;
}

void inc(int *numero) {
  (*numero) = ((*numero) + 1) % SEQ_NUM_SIZE;
}




/* ===================== Fenêtre d'anticipation ============================= */

/*--------------------------------------*/
/* Fonction d'inclusion dans la fenetre */
/*--------------------------------------*/
int dans_fenetre(unsigned int inf, unsigned int pointeur, int taille) {

    unsigned int sup = (inf+taille-1) % SEQ_NUM_SIZE;

    return
        /* inf <= pointeur <= sup */
        ( inf <= sup && pointeur >= inf && pointeur <= sup ) ||
        /* sup < inf <= pointeur */
        ( sup < inf && pointeur >= inf) ||
        /* pointeur <= sup < inf */
        ( sup < inf && pointeur <= sup);



}
