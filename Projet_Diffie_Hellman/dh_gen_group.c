#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <unistd.h> 
#include "dh_prime.h"

long genPrimeSophieGermain(long min, long max, int *cpt);
long seek_generator(long start, long p);


void print_usage() {
    printf("Usage: dh_gen_group -o <output_file>\n");
}

// je verifie ici  si un nombre est premier
bool is_prime(long n) {
    if (n < 2) return false;
    for (long i = 2; i * i <= n; i++) {
        if (n % i == 0) return false;
    }
    return true;
}

int main(int argc, char *argv[]) {
    if (argc != 3 || strcmp(argv[1], "-o") != 0) {
        print_usage();
        return EXIT_FAILURE;
    }

    const char *output_file = argv[2];

    //si le fichier de sortie existe déjà
    if (access(output_file, F_OK) == 0) {
        fprintf(stderr, "Erreur : Le fichier '%s' existe déjà.\n", output_file);
        return EXIT_FAILURE;
    }

    FILE *file = fopen(output_file, "w");
    if (!file) {
        perror("Erreur d'ouverture du fichier");
        return EXIT_FAILURE;
    }

    // Paramètres pour la génération
    long min = 1000;
    long max = 10000; // Bornes pour le nombre premier
    int attempt_count = 0;
    srand(time(NULL)); // Initialisation de la graine aléatoire

    // Générer un nombre premier de Sophie Germain
    long prime = genPrimeSophieGermain(min, max, &attempt_count);
    if (prime == -1 || !is_prime(prime)) {
        fprintf(stderr, "Échec de la génération d'un nombre premier valide.\n");
        fclose(file);
        return EXIT_FAILURE;
    }
    printf("Nombre premier de Sophie Germain généré après %d tentatives : %ld\n", attempt_count, prime);

    // Chercher un générateur
    long generator = seek_generator(2, prime);
    if (generator == -1) {
        fprintf(stderr, "Échec de la génération d'un générateur.\n");
        fclose(file);
        return EXIT_FAILURE;
    }
    printf("Générateur trouvé : %ld\n", generator);

    // Écrire les résultats dans le fichier
    fprintf(file, "p = %ld\ng = %ld\n", prime, generator);
    fclose(file);

    printf("Paramètres générés et écrits dans le fichier : p = %ld, g = %ld\n", prime, generator);
    return EXIT_SUCCESS;
}

