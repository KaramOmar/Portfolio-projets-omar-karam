package TakeNote;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.time.LocalDate;
import java.time.format.DateTimeFormatter;
import java.time.format.DateTimeParseException;
import java.util.ArrayList;
import java.util.List;
import java.util.Map;

public class CSVNote {
	private static final DateTimeFormatter DATE_FORMAT = DateTimeFormatter.ofPattern("yyyy-MM-dd");

    //lire les notes depuis un fichier CSV
    public static List<Note<String>> lireDepuisCSV(String cheminFichier) {
        List<Note<String>> notes = new ArrayList<>();

        try (BufferedReader br = new BufferedReader(new FileReader(cheminFichier))) {
            String ligne;
            boolean premiereLigne = true; 

            while ((ligne = br.readLine()) != null) {
                if (premiereLigne) {
                    premiereLigne = false;
                    continue;
                }
                String[] elements = ligne.split(",\\s*");
                if (elements.length == 7) {
                    String categorie = elements[0];
                    String titre = elements[1];
                    String contenu = elements[2];
                    LocalDate date = null;

                    // Convertir la date
                    try {
                        date = LocalDate.parse(elements[3], DATE_FORMAT);
                    } catch (DateTimeParseException e) {
                        System.err.println("Erreur de format de date : " + elements[3]);
                        continue;
                    }

                    boolean rappel = "Oui".equalsIgnoreCase(elements[4]);
                    String messageRappel = elements[5];
                    String heureRappel = elements[6];

                    // Ajouter une note à la liste
                    notes.add(new Note<>(titre, contenu, categorie, date, rappel, messageRappel, heureRappel));
                }
            }
        } catch (IOException e) {
            System.err.println("Erreur lors de la lecture du fichier CSV : " + e.getMessage());
        }

        return notes;
    }
    
	
	public static void exporterVersCSV(Map<CategorieNote, List<Note<String>>> notesParCategorie, String cheminFichier) {
        try (FileWriter writer = new FileWriter(cheminFichier)) {
            writer.write("Categorie, Titre, Contenu, Date, Rappel, MessageRappel, HeureRappel\n");

            for (CategorieNote categorie : notesParCategorie.keySet()) {
                List<Note<String>> notes = notesParCategorie.get(categorie);

                // Parcourir chaque note
                for (Note<String> note : notes) {
                    writer.write(String.format("%s, %s, %s, %s, %s, %s, %s\n",
                            categorie,
                            note.getTitre(),
                            note.getContenu(),
                            note.getDate(),
                            note.isRappel() ? "Oui" : "Non",
                            note.getMessageRappel() != null ? note.getMessageRappel() : "",
                            note.getHeureRappel() != null ? note.getHeureRappel() : ""));
                }
            }
            System.out.println("Les notes ont été exportées dans le fichier CSV : " + cheminFichier);
        } catch (IOException e) {
            System.err.println("Erreur lors de l'exportation des notes dans le fichier CSV : " + e.getMessage());
        }
    }
}
