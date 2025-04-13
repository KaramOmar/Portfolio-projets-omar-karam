import pygame
import random
import pandas as pd
import matplotlib.pyplot as plt
# Initialisation de pygame

pygame.init()

# Paramètres du jeu
LARGEUR, HAUTEUR = 800, 600
TAILLE_CASE = 20
VITESSE_NIVEAUX = {'Débutant': 10, 'Intermédiaire': 12, 'Difficile': 15}

# Couleurs
NOIR = (0, 0, 0)
BLANC = (255, 255, 255)
VERT = (0, 255, 0)
ROUGE = (255, 0, 0)
BLEU = (0, 0, 255)
ORANGE = (255, 165, 0)

# Fenêtre de jeu
fenetre = pygame.display.set_mode((LARGEUR, HAUTEUR))
pygame.display.set_caption("Snake Game")

# Chargement du logo
logo = pygame.image.load("snake_logo.png")
logo = pygame.transform.scale(logo, (100, 100))


# Fonction pour afficher le menu
def menu():
    font = pygame.font.Font(None, 36)
    choix = ["Start", "Level", "Quitter"]
    niveau = "Intermédiaire"
    selection = 0

    while True:
        fenetre.fill(NOIR)
        fenetre.blit(logo, (LARGEUR // 2 - 50, 20))
        for i, option in enumerate(choix):
            couleur = ORANGE if i != selection else ROUGE
            texte = font.render(option, True, couleur)
            fenetre.blit(texte, (LARGEUR // 2 - texte.get_width() // 2, 150 + i * 50))
        pygame.display.flip()

        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                pygame.quit()
                exit()
            elif event.type == pygame.KEYDOWN:
                if event.key == pygame.K_DOWN:
                    selection = (selection + 1) % 3
                elif event.key == pygame.K_UP:
                    selection = (selection - 1) % 3
                elif event.key == pygame.K_RETURN:
                    if choix[selection] == "Start":
                        return niveau
                    elif choix[selection] == "Level":
                        return choisir_niveau()
                    elif choix[selection] == "Quitter":
                        pygame.quit()
                        exit()


def choisir_niveau():
    font = pygame.font.Font(None, 36)
    niveaux = list(VITESSE_NIVEAUX.keys())
    selection = 1

    while True:
        fenetre.fill(NOIR)
        for i, lvl in enumerate(niveaux):
            couleur = ORANGE if i != selection else ROUGE
            texte = font.render(lvl, True, couleur)
            fenetre.blit(texte, (LARGEUR // 2 - texte.get_width() // 2, 100 + i * 50))
        pygame.display.flip()

        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                pygame.quit()
                exit()
            elif event.type == pygame.KEYDOWN:
                if event.key == pygame.K_DOWN:
                    selection = (selection + 1) % 3
                elif event.key == pygame.K_UP:
                    selection = (selection - 1) % 3
                elif event.key == pygame.K_RETURN:
                    return jeu(niveaux[selection])


# Fonction principale du jeu
def jeu(niveau):
    serpent = [(100, 100)]
    direction = (TAILLE_CASE, 0)
    pomme = (random.randint(0, (LARGEUR // TAILLE_CASE) - 1) * TAILLE_CASE,
             random.randint(0, (HAUTEUR // TAILLE_CASE) - 1) * TAILLE_CASE)
    obstacles = []

    if niveau in ["Intermédiaire", "Difficile"]:
        for _ in range(5 if niveau == "Intermédiaire" else 10):
            obstacles.append((random.randint(0, (LARGEUR // TAILLE_CASE) - 1) * TAILLE_CASE,
                              random.randint(0, (HAUTEUR // TAILLE_CASE) - 1) * TAILLE_CASE))

    horloge = pygame.time.Clock()
    jeu_en_cours = True
    vitesse = VITESSE_NIVEAUX[niveau]

    while jeu_en_cours:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                jeu_en_cours = False
            elif event.type == pygame.KEYDOWN:
                if event.key == pygame.K_UP and direction != (0, TAILLE_CASE):
                    direction = (0, -TAILLE_CASE)
                elif event.key == pygame.K_DOWN and direction != (0, -TAILLE_CASE):
                    direction = (0, TAILLE_CASE)
                elif event.key == pygame.K_LEFT and direction != (TAILLE_CASE, 0):
                    direction = (-TAILLE_CASE, 0)
                elif event.key == pygame.K_RIGHT and direction != (-TAILLE_CASE, 0):
                    direction = (TAILLE_CASE, 0)

        tete = (serpent[0][0] + direction[0], serpent[0][1] + direction[1])
        if tete[0] < 0 or tete[0] >= LARGEUR or tete[1] < 0 or tete[
            1] >= HAUTEUR or tete in serpent or tete in obstacles:
            afficher_message("You Lose! Score: " + str(len(serpent) - 1))
            return

        serpent.insert(0, tete)
        if tete == pomme:
            pomme = (random.randint(0, (LARGEUR // TAILLE_CASE) - 1) * TAILLE_CASE,
                     random.randint(0, (HAUTEUR // TAILLE_CASE) - 1) * TAILLE_CASE)
        else:
            serpent.pop()

        fenetre.fill(NOIR)
        pygame.draw.rect(fenetre, BLEU, (*pomme, TAILLE_CASE // 2, TAILLE_CASE // 2))
        for segment in serpent:
            pygame.draw.rect(fenetre, ROUGE, (*segment, TAILLE_CASE, TAILLE_CASE))
        for obs in obstacles:
            pygame.draw.rect(fenetre, BLANC, (*obs, TAILLE_CASE, TAILLE_CASE))

        pygame.display.flip()
        horloge.tick(vitesse)


def afficher_message(message):
    font = pygame.font.Font(None, 50)
    texte = font.render(message, True, ROUGE)
    fenetre.fill(NOIR)
    fenetre.blit(texte, (LARGEUR // 2 - texte.get_width() // 2, HAUTEUR // 2 - texte.get_height() // 2))
    pygame.display.flip()
    pygame.time.delay(2000)

niveau_choisi = menu()
jeu(niveau_choisi)
pygame.quit()

