package TakeNote;
import java.util.Scanner;

public class MainNote {
	
	public static void main(String[] args) {
		GestionnaireNoteControleur controleur = new GestionnaireNoteControleur();
        GestionnaireNoteBoundary boundary = new GestionnaireNoteBoundary(controleur);
        Scanner scanner = new Scanner(System.in);

        while (true) {
            System.out.println("\n--- Gestionnaire de Notes ---");
            System.out.println("1. Ajouter une note");
            System.out.println("2. Afficher les notes");
            System.out.println("3. Copier une note");
            System.out.println("4. Coller la note copiée");
            System.out.println("5. Couper une note");
            System.out.println("6. Annuler la dernière action");
            System.out.println("7. Rétablir la note annulée");
            System.out.println("8. Sauvegarder les notes dans un fichier");
            System.out.println("9. Quitter");
            System.out.print("Choisissez une option: ");

            int action = scanner.nextInt();
            scanner.nextLine(); 

            switch (action) {
                case 1: // Ajouter une note
                    System.out.print("Entrez le titre de la note : ");
                    String titre = scanner.nextLine();
                    System.out.print("Entrez le contenu de la note : ");
                    String contenu = scanner.nextLine();
                    controleur.ajouterNote(titre, contenu);
                    break;

                case 2: // Afficher les notes
                    controleur.afficherNotes();
                    break;

                case 3: // Copier
                    System.out.print("Veuillez entrer l'indice de la note à copier : ");
                    int indexCopie = scanner.nextInt();
                    scanner.nextLine();
                    boundary.copierNoteBO(indexCopie);
                    break;

                case 4: // Coller
                	System.out.print("Veuillez entrez l'indice de la note à coller : ");
                	int indexcoller=scanner.nextInt();
                    scanner.nextLine();
                    boundary.collerNoteBO();
                    break;

                case 5: // Couper
                    System.out.print("Veuillez entrez l'indice de la note à couper : ");
                    int indexCoupe = scanner.nextInt();
                    scanner.nextLine();
                    boundary.couperNoteBO(indexCoupe);
                    break;

                case 6: // Annuler
                    boundary.annulerNoteBO();
                    break;

                case 7: // Rétablir
                    boundary.retablirNoteBO();
                    break;

                case 8: // Sauvegarder dans un fichier
                    System.out.print("Entrez le chemin du fichier : ");
                    String cheminFichier = scanner.nextLine();
                    controleur.sauvegarderNotesDansFichier(cheminFichier);
                    break;

                case 9: // Quitter
                    System.out.println("Fermeture de l'application.");
                    scanner.close();
                    return;

                default:
                    System.out.println("Option non valide, veuillez réessayer.");
                    break;
            }
        }
    }

}
