package TakeNote;
import java.time.LocalDate;
import java.util.ArrayList;
import java.util.List;
import java.util.Map;
import java.util.Scanner;
import java.util.Collections;

import TakeNote.CSVNote;
import TakeNote.CategorieNote;
import TakeNote.GestionnaireNote;
import TakeNote.Note;
import TakeNote.NotesIterables;
import TakeNote.Rappel;

public class MainNote {
    private static Note<String> noteCopiee; // Pour stocker la note copiée ou coupée

    public static void main(String[] args) {
        // Chemin fichier CSV
        String cheminFichier = "Chemin fichier";

        // Initialiser le gestionnaire de notes avec le chemin du fichier CSV
        GestionnaireNote gestionnaire = new GestionnaireNote(cheminFichier);

        //les entrées utilisateur
        Scanner scanner = new Scanner(System.in);
        

        // Menu
        while (true) {
        	System.out.println("\n--- Gestionnaire de Notes ---");
        	System.out.println("1. Ajouter une note");
        	System.out.println("2. Afficher toutes les notes");
        	System.out.println("3. Rechercher une note par titre");
        	System.out.println("4. Copier une note");
        	System.out.println("5. Coller la note copiée");
        	System.out.println("6. Couper une note");
        	System.out.println("7. Sauvegarder les notes dans un fichier CSV");
        	System.out.println("8. Supprimer une note");
        	System.out.println("9. Modifier une note");
        	System.out.println("10. Quitter");
        	System.out.print("Choisissez une option : ");

            int action = scanner.nextInt();
            scanner.nextLine(); 

            switch (action) {
            	
            case 1: // Ajouter une note
            		System.out.print("Entrez le titre de la note : ");
            		String titre = scanner.nextLine();
            		System.out.print("Entrez le contenu de la note : ");
            		String contenu = scanner.nextLine();
            		System.out.print("Entrez la catégorie de la note : ");
            		String categorieStr = scanner.nextLine().toUpperCase();
            		CategorieNote categorie;
            		try {
            			categorie = CategorieNote.valueOf(categorieStr);
            		} catch (IllegalArgumentException e) {
            			System.out.println("Catégorie non valide.");
            			break;
                }

            		// Obtenir la date 
            		LocalDate date = LocalDate.now();

            		// Rappel ou non
            		System.out.print("Voulez-vous activer un rappel pour cette note (Oui/Non) ? ");
            		boolean rappel = scanner.nextLine().equalsIgnoreCase("Oui");

            		// Message de rappel et de l'heure du rappel
            		String messageRappel = "";
            		String heureRappel = "";

            		if (rappel) {
            			System.out.print("Entrez le message du rappel : ");
            			messageRappel = scanner.nextLine();
            			System.out.print("Entrez l'heure du rappel au format HH:MM : ");
            			heureRappel = scanner.nextLine();
            		}

            		// Ajouter la note au gestionnaire
            		gestionnaire.ajouterNote(titre, contenu, categorie, date, rappel, messageRappel, heureRappel);
            		break;

               

                
            	case 2: // Afficher toutes les notes
                    List<Note<String>> toutesLesNotes = gestionnaire.obtenirToutesLesNotes();
                    if (toutesLesNotes.isEmpty()) {
                        System.out.println("Aucune note disponible.");
                    } else {
                        for (Note<String> note : toutesLesNotes) {
                            System.out.println(note.getTitre() + ": " + note.getDate() + ", Rappel: " + note.getMessageRappel());
                        }
                    }
                    break;

                
                case 3: // Rechercher une note par titre
                    System.out.print("Entrez le titre de la note à rechercher : ");
                    String rechercheTitre = scanner.nextLine().trim();
                    List<Note<String>> notesTrouvees = gestionnaire.rechercherNotesParTitre(rechercheTitre);
                    if (notesTrouvees.isEmpty()) {
                        System.out.println("Aucune note trouvée avec ce titre.");
                    } else {
                        System.out.println("Les notes trouvées :");
                        for (Note<String> note : notesTrouvees) {
                            System.out.println(note.getTitre() + ": " + note.getContenu() + ", " + note.getDate());
                        }
                    }
                    break;

                
                case 4: // Copier une note
                    System.out.print("Entrez la catégorie de la note à copier : ");
                    String categorieCopieStr = scanner.nextLine().toUpperCase();
                    CategorieNote categorieCopie;
                    try {
                        categorieCopie = CategorieNote.valueOf(categorieCopieStr);
                    } catch (IllegalArgumentException e) {
                        System.out.println("Catégorie non valide.");
                        break;
                    }
                    System.out.print("Entrez l'indice de la note à copier : ");
                    int indexCopier = scanner.nextInt();
                    scanner.nextLine();
                    noteCopiee = gestionnaire.copierNoteParIndice(indexCopier, categorieCopie);
                    if (noteCopiee != null) {
                        System.out.println("La note " + noteCopiee.getTitre() + " a été copiée.");
                    } else {
                        System.out.println("Indice invalide.");
                    }
                    break;

                
                case 5: // Coller la note copiée
                    if (noteCopiee != null) {
                        System.out.print("Entrez la catégorie dans laquelle coller la note copiée : ");
                        String categorieCollerStr = scanner.nextLine().toUpperCase();
                        CategorieNote categorieColler;
                        try {
                            categorieColler = CategorieNote.valueOf(categorieCollerStr);
                        } catch (IllegalArgumentException e) {
                            System.out.println("Catégorie non valide.");
                            break;
                        }
                        gestionnaire.collerNoteCopiee(noteCopiee, categorieColler);
                        System.out.println("La note " + noteCopiee.getTitre() + " a été collée.");
                    } else {
                        System.out.println("Aucune note copiée.");
                    }
                    break;

                
                
                case 6: // Couper une note
                    System.out.print("Entrez la catégorie de la note à couper : ");
                    String categorieCouperStr = scanner.nextLine().toUpperCase();
                    CategorieNote categorieCouper;
                    try {
                        categorieCouper = CategorieNote.valueOf(categorieCouperStr);
                    } catch (IllegalArgumentException e) {
                        System.out.println("Catégorie non valide.");
                        break;
                    }
                    System.out.print("Entrez l'indice de la note à couper : ");
                    int indexCouper = scanner.nextInt();
                    scanner.nextLine();
                    noteCopiee = gestionnaire.couperNoteParIndice(indexCouper, categorieCouper);
                    if (noteCopiee != null) {
                        System.out.println("La note " + noteCopiee.getTitre() + " a été coupée.");
                    } else {
                        System.out.println("Indice invalide.");
                    }
                    break;

                
                
                case 7: // Sauvegarder les notes dans un fichier CSV
                    gestionnaire.sauvegarderNotes();
                    System.out.println("Notes sauvegardées dans le fichier CSV.");
                    break;

                
               
                
                case 8: // Supprimer une note
                    System.out.print("Entrez la catégorie de la note à supprimer : ");
                    String categorieSupprimerStr = scanner.nextLine().toUpperCase();
                    CategorieNote categorieSupprimer;
                    try {
                        categorieSupprimer = CategorieNote.valueOf(categorieSupprimerStr);
                    } catch (IllegalArgumentException e) {
                        System.out.println("Catégorie non valide.");
                        break;
                    }

                    // Afficher les notes disponibles dans cette catégorie
                    List<Note<String>> notesDansCategorie = gestionnaire.obtenirNotes(categorieSupprimer);
                    if (notesDansCategorie == null || notesDansCategorie.isEmpty()) {
                        System.out.println("Aucune note disponible dans cette catégorie.");
                        break;
                    }

                    // Afficher la liste avec les indices
                    for (int i = 0; i < notesDansCategorie.size(); i++) {
                        System.out.println(i + " - " + notesDansCategorie.get(i).getTitre());
                    }

                    // Demander l'indice de la note à supprimer
                    System.out.print("Entrez l'indice de la note à supprimer : ");
                    int indexSupprimer = scanner.nextInt();
                    scanner.nextLine(); // Consomme la ligne restante

                    // Vérifier l'indice et effectuer la suppression
                    if (indexSupprimer >= 0 && indexSupprimer < notesDansCategorie.size()) {
                        gestionnaire.supprimerNote(categorieSupprimer, indexSupprimer);
                        System.out.println("La note a été supprimée.");
                    } else {
                        System.out.println("Indice invalide.");
                    }
                    break;
                
                 
                
                
                
                
                
                
                
                case 9: // Modifier une note
                    System.out.print("Entrez la catégorie de la note à modifier : ");
                    String categorieModifierStr = scanner.nextLine().toUpperCase();
                    CategorieNote categorieModifier;

                    try {
                        categorieModifier = CategorieNote.valueOf(categorieModifierStr);
                    } catch (IllegalArgumentException e) {
                        System.out.println("Catégorie non valide.");
                        break;
                    }

                    NotesIterables<String> notesIterables = gestionnaire.obtenirNotesIterables(categorieModifier);
                    List<Note<String>> notesDansCategorie1 = new ArrayList<>();

                    for (Note<String> note : notesIterables) {
                        notesDansCategorie1.add(note);
                    }

                   
                    if (notesDansCategorie1.isEmpty()) {
                        System.out.println("Aucune note disponible dans cette catégorie.");
                        break;
                    }

                    // Afficher les notes  avec  indices 0 1 é etc...
                    for (int i = 0; i < notesDansCategorie1.size(); i++) {
                        System.out.println(i + " - " + notesDansCategorie1.get(i).getTitre() + ": " + notesDansCategorie1.get(i).getContenu());
                    }

                    //  l'indice de la note à modifier
                    System.out.print("Entrez l'indice de la note à modifier : ");
                    int indexModifier = scanner.nextInt();
                    scanner.nextLine(); 

                    //ON Vérifier si l'indice est valide
                    if (indexModifier >= 0 && indexModifier < notesDansCategorie1.size()) {
                        System.out.print("Entrez le nouveau contenu : ");
                        String nouveauContenu = scanner.nextLine();
                        gestionnaire.modifierNote(categorieModifier, indexModifier, nouveauContenu);
                        System.out.println("La note a été modifiée.");
                    } else {
                        System.out.println("Indice invalide.");
                    }
                    break;


                  
                
                case 10: // Quitter
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
