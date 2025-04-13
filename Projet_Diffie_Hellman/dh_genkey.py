import random
import threading
import queue


# je calcule  la puissance modulaire (a^e % n)
def puissance_mod_n(a, e, n):
    return pow(a, e, n)


# Alice choisit sa clé privée a et calcule sa clé publique A
def alice(p, g, queue):
    a = random.randint(1, p - 1)  # Choisir a aléatoirement
    A = puissance_mod_n(g, a, p)  # Calcul de A = g^a % p
    print(f"[Alice] Choisit a = {a}, calcule A = {A}")
    print(f"[Alice] Connaît seulement a = {a}")
    queue.put(A)  # Envoie A à Bob
    B = queue.get()  # Reçoit B de Bob
    print(f"[Alice] Reçoit B = {B} de Bob")  # Affichage de la clé publique reçue
    S_Alice = puissance_mod_n(g, a, p)  #g^a % p pour Alice
    print(f"[Alice] Calcule la clé partagée S = {S_Alice} en utilisant la formule S = g^a % p")

    # Envoie la clé partagée à Bob via la queue
    queue.put(S_Alice)


# Bob choisit sa clé privée b et calcule sa clé publique B
def bob(p, g, queue):
    b = random.randint(1, p - 1)  # Choisir b aléatoirement
    B = puissance_mod_n(g, b, p)  # Calcul de B = g^b % p
    print(f"[Bob] Choisit b = {b}, calcule B = {B}")
    print(f"[Bob] Connaît seulement b = {b}")
    queue.put(B)  # Envoie B à Alice
    A = queue.get()  # Reçoit A d'Alice
    print(f"[Bob] Reçoit A = {A} d'Alice")
    S_Bob = puissance_mod_n(g, b, p)  # Utiliser g^b % p pour Bob
    print(f"[Bob] Calcule la clé partagée S = {S_Bob} en utilisant la formule S = g^b % p")

    # Envoie la clé partagée à Alice
    queue.put(S_Bob)

    # Affichage pour Eve
    print(f"Eve peut connaître A = {A} et B = {B} mais ne peut pas calculer la clé secrète.")



# j'Extrais  la valeur numérique des paramètres dans le fichier
def extraire_parametre(fichier, nom_parametre):
    with open(fichier, 'r') as file:
        for line in file:
            if line.startswith(nom_parametre):
                return int(line.split('=')[1].strip())
    return None  # Si le paramètre n'est pas trouvé


# Main
def main():
    # Paramètres p et g depuis le fichier param.txt
    p = extraire_parametre('param.txt', 'p')
    g = extraire_parametre('param.txt', 'g')

    if p is None or g is None:
        print("Erreur : Impossible de charger les paramètres p et g depuis param.txt.")
        return

    print(f"Paramètres chargés depuis param.txt : p = {p}, g = {g}")

    # Queue pour la communication entre Alice et Bob
    q = queue.Queue()

    # Lancement des threads pour Alice et Bob
    thread_alice = threading.Thread(target=alice, args=(p, g, q))
    thread_bob = threading.Thread(target=bob, args=(p, g, q))

    # Démarrer les threads
    thread_alice.start()
    thread_bob.start()

    # Attendre la fin des threads
    thread_alice.join()
    thread_bob.join()

    # Récupérer les clés partagées
    S_Alice = q.get()  # Clé partagée d'Alice
    S_Bob = q.get()  # Clé partagée de Bob

    # Ici je verifie  si les clés partagées correspondent c'est à dire sont correcte ou pas 
    if S_Alice == S_Bob:
        print(f"Clé partagée correcte : {S_Alice}")
    else:
        print(f"Erreur : Les clés partagées ne correspondent pas. Alice : {S_Alice}, Bob : {S_Bob}")


    
        with open("key.txt", "w") as file:
            file.write(f"Clé partagée : {S_Alice}\n")
        print("La clé partagée a été enregistrée dans key.txt.")



if __name__ == '__main__':
    main()

