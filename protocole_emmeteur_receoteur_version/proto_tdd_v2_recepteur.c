#include "application.h"
#include "couche_transport.h"
#include "services_reseau.h"
#include <stdio.h>

/* =============================== */
/* Programme principal - récepteur */
/* =============================== */
int main(int argc, char *argv[]) {
  unsigned char message[MAX_INFO]; /* message pour l'application */
  paquet_t paquet;                 /* paquet utilisé par le protocole */
  int fin = 0;                     /* condition d'arrêt */
  int seq_attendu = 0; /* numero du premier paquet que l'on va envoyer */

  init_reseau(RECEPTION);

  printf("[TRP] Initialisation reseau : OK.\n");
  printf("[TRP] Debut execution protocole transport.\n");

  /* tant que le récepteur reçoit des données */
  while (!fin) {
    de_reseau(&paquet);
    if (verifier_controle(paquet)) {
      if (seq_attendu == paquet.num_seq) {
        /* extraction des donnees du paquet recu */
        for (int i = 0; i < paquet.lg_info; i++) {
          message[i] = paquet.info[i];
        }
        /* remise des données à la couche application */
        fin = vers_application(message, paquet.lg_info);
        inc(&seq_attendu);
      }
      paquet.type = ACK;
      vers_reseau(&paquet);
    }
  }

  printf("[TRP] Fin execution protocole transport.\n");
  return 0;
}
