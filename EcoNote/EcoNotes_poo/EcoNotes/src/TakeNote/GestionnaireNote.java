package TakeNote;
import TakeNote.NotesIterables;
import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.time.LocalDate;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import TakeNote.CSVNote;
public class GestionnaireNote {
	private Map<CategorieNote, List<Note<String>>> notesParCategorie;
    private Note<String> noteCopiee; 
    private String cheminFichier;
    
    public GestionnaireNote(String cheminFichier) {
        this.cheminFichier = cheminFichier;
        this.notesParCategorie = chargerNotesDepuisCSV();
    }
    
    public GestionnaireNote() {
        notesParCategorie = new HashMap<>();
        for (CategorieNote categorie : CategorieNote.values()) {
            notesParCategorie.put(categorie, new ArrayList<>());
        }
    }
    
    private Map<CategorieNote, List<Note<String>>> chargerNotesDepuisCSV() {
        List<Note<String>> notes = CSVNote.lireDepuisCSV(cheminFichier);
        Map<CategorieNote, List<Note<String>>> notesMap = new HashMap<>();
        for (CategorieNote categorie : CategorieNote.values()) {
            notesMap.put(categorie, new ArrayList<>());
        }
        for (Note<String> note : notes) {
            try {
                // Vérifier si la catégorie existe dans l'énumération
                CategorieNote categorie = CategorieNote.valueOf(note.getCategorie().toUpperCase());
                notesMap.get(categorie).add(note);
            } catch (IllegalArgumentException e) {
                System.err.println("Catégorie non valide trouvée dans le fichier CSV : " + note.getCategorie());
            } catch (NullPointerException e) {
                System.err.println("Erreur : La catégorie " + note.getCategorie() + " n'existe pas.");
            }
        }

        return notesMap;
    }


    // Sauvegarder les notes dans le fichier CSV
    public void sauvegarderNotes() {
        CSVNote.exporterVersCSV(notesParCategorie, cheminFichier);
    }
    
    
    public NotesIterables obtenirNotesIterables(CategorieNote categorie) {
        List<Note<String>> notes = notesParCategorie.get(categorie);
        if (notes == null) {
            notes = new ArrayList<>();
        }
        return new NotesIterables(notes);
    }
    
    public void ajouterNote(String titre, String contenu, CategorieNote categorie, LocalDate date, boolean rappel, String messageRappel, String heureRappel) {
        List<Note<String>> notes = notesParCategorie.get(categorie);
        notes.add(new Note<>(titre, contenu, categorie.name(), date, rappel, messageRappel, heureRappel));
        sauvegarderNotes();
    }

    public Map<CategorieNote, List<Note<String>>> getNotesParCategorie() {
        return notesParCategorie;
    }


    // Obtenir toutes les notes d'une catégorie
    public List<Note<String>> obtenirNotes(CategorieNote categorie) {
        return notesParCategorie.get(categorie);
    }

    // Supprimer une note d'une catégorie spécifique
    public void supprimerNote(CategorieNote categorie, int indice) {
        List<Note<String>> notes = notesParCategorie.get(categorie);
        if (indice >= 0 && indice < notes.size()) {
            notes.remove(indice);
            sauvegarderNotes();
        }
    }

    
    // Modifier une note existante
    
    public void modifierNote(CategorieNote categorie, int nindex, String nouveauContenu) {
        List<Note<String>> notes = notesParCategorie.get(categorie);
        if (nindex >= 0 && nindex < notes.size()) {
            Note<String> note = notes.get(nindex);
            note.modifierContenu(nouveauContenu);
        }
    }

    // Afficher toutes les notes d'une catégorie
    public void afficherNotes(CategorieNote categorie) {
        List<Note<String>> notes = notesParCategorie.get(categorie);
        System.out.println("Notes dans la catégorie " + categorie + ":");
        for (Note<String> note : notes) {
            System.out.println("- " + note.getTitre() + ": " + note.getContenu());
        }
    }
    
    
 // Obtenir toutes les notes de toutes les catégories
    public List<Note<String>> obtenirToutesLesNotes() {
        List<Note<String>> toutesLesNotes = new ArrayList<>();
        for (List<Note<String>> notes : notesParCategorie.values()) {
            toutesLesNotes.addAll(notes);
        }
        return toutesLesNotes;
    }

   
    // Rechercher des notes par titre dans toutes les catégories
    public List<Note<String>> rechercherNotesParTitre(String titre) {
        List<Note<String>> notesTrouvees = new ArrayList<>();
        for (List<Note<String>> notes : notesParCategorie.values()) {
            for (Note<String> note : notes) {
                if (note.getTitre().equalsIgnoreCase(titre)) {
                    notesTrouvees.add(note);
                }
            }
        }
        return notesTrouvees;
    }

    // Copier une note par indice dans une catégorie
    public Note<String> copierNoteParIndice(int indice, CategorieNote categorie) {
        List<Note<String>> notes = notesParCategorie.get(categorie);
        if (indice >= 0 && indice < notes.size()) {
            return notes.get(indice);
        } else {
            return null;
        }
    }

    // Coller une note copiée dans une catégorie spécifique
    public void collerNoteCopiee(Note<String> noteCopiee, CategorieNote categorie) {
        if (noteCopiee != null) {
            List<Note<String>> listeNotes = notesParCategorie.get(categorie);
            if (listeNotes == null) {
                listeNotes = new ArrayList<>();
                notesParCategorie.put(categorie, listeNotes);
            }
            listeNotes.add(new Note<>(
                noteCopiee.getTitre(),
                noteCopiee.getContenu(),
                noteCopiee.getCategorie(),
                noteCopiee.getDate(),
                noteCopiee.isRappel(),
                noteCopiee.getMessageRappel(),
                noteCopiee.getHeureRappel()
            ));
            sauvegarderNotes(); 
        }
    }

    // Couper une note en fait par indice 0,1,2,3 ect..
    public Note<String> couperNoteParIndice(int indice, CategorieNote categorie) {
        List<Note<String>> notes = notesParCategorie.get(categorie);
        if (indice >= 0 && indice < notes.size()) {
            Note<String> noteCoupee = notes.remove(indice);
            sauvegarderNotes();
            return noteCoupee;
        } else {
            return null;
        }
    }

}

