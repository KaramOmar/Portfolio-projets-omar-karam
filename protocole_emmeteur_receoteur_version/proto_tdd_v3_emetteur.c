#include "application.h"
#include "couche_transport.h"
#include "services_reseau.h"
#include <stdio.h>

/* =============================== */
/* Programme principal - émetteur  */
/* =============================== */
int main(int argc, char *argv[]) {
  unsigned char message[MAX_INFO]; /* message de l'application */
  int taille_msg = 1;              /* taille du message */
  paquet_t paquet[SEQ_NUM_SIZE];   /* paquet utilisé par le protocole */
  paquet_t p_controle;
  int code_retour, borne_inf = 0, curseur = 0, taille_fenetre = 4, i;

  init_reseau(EMISSION);

  printf("[TRP] Initialisation reseau : OK.\n");
  printf("[TRP] Debut execution protocole transport.\n");

  /* tant que l'émetteur a des données à envoyer */
  while ((taille_msg != 0 || curseur != borne_inf)) {
    if (dans_fenetre(borne_inf, curseur, taille_fenetre) && taille_msg != 0) {
      /* lecture de donnees provenant de la couche application */
      de_application(message, &taille_msg);
      /* construction paquet */
      if (taille_msg != 0) {
        for (int i = 0; i < taille_msg; i++) {
          paquet[curseur].info[i] = message[i];
        }
        paquet[curseur].type = DATA;
        paquet[curseur].lg_info = taille_msg;
        paquet[curseur].num_seq = curseur;
        paquet[curseur].somme_ctrl = generer_controle(paquet[curseur]);
        // remise a la couche reseau
        vers_reseau(&paquet[curseur]);
        if (borne_inf == curseur) depart_temporisateur(100);
        inc(&curseur);
      }
    } else { // timeout
      code_retour = attendre();
      if (code_retour == PAQUET_RECU) { // paquet reçu
        de_reseau(&p_controle);
        /* décalage de la fenêtre */
        if (verifier_controle(p_controle) &&
            dans_fenetre(borne_inf, p_controle.num_seq, taille_fenetre)) {
          borne_inf = (p_controle.num_seq + 1) % SEQ_NUM_SIZE;
          if (borne_inf == curseur) arret_temporisateur();
        }
      } else {
        i = borne_inf;
        depart_temporisateur(100);
        while (i != curseur) {
          vers_reseau(&paquet[i]);
          inc(&i);
        }
      }
    }
  }
  printf("[TRP] Fin execution protocole transfert de donnees (TDD).\n");
  return 0;
}
