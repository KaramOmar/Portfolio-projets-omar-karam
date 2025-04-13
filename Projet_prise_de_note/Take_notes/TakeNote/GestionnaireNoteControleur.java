package TakeNote;
import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

// Controleur
public class GestionnaireNoteControleur {
	private List<Note<Object>> notes = new ArrayList<>();
	 private Note<Object> noteCopiee; // Pour stocker la note copiée
	 private List<Note<Object>> notesAnnulees = new ArrayList<>();

	 
	// Classe interne ModifierNote
	    private class ModifierNote {
	    	
	    	public void modifierLeContenu(Note<Object> note, Object nouveauContenu) {
	            note.modifierContenu(nouveauContenu);
	        }

	    }
	    
	    private ModifierNote modifierNote = new ModifierNote();
	    
	    public void ajouterNote(String titre,String contenu) {
	        notes.add(new Note<>(titre,contenu));
	    }
	    
	    
	    
	    public Note getNoteSelectionnee() {
	        if (notes.isEmpty()) {
	            return null;
	        } else {
	            return notes.get(notes.size() - 1);
	        }
	    }


	    
	    
	    public void supprimerNote(int nindex) {
	    	if(nindex>=0 && nindex<notes.size()) {
	    		notes.remove(nindex);
	    	}
	        
	    }
	    
	    public void sauvegarderNotesDansFichier(String nomFichier) {
	        try (BufferedWriter writer = new BufferedWriter(new FileWriter(nomFichier))) {
	            for (Note<Object> note : notes) {
	                writer.write(note.getTitre() + " - " + note.getContenu());
	                writer.newLine();
	            }
	            System.out.println("Les notes ont été sauvegardées dans le fichier : " + nomFichier);
	        } catch (IOException e) {
	            System.err.println("Une erreur est survenue lors de la sauvegarde des notes : " + e.getMessage());
	        }
	    }
	    
	    
	   
	    
	    public void sauvegarderNote() {
	        
	        System.out.println("Note sauvegardée");
	    }
	    
	    
	    public void ecrireNote(String titre,Object contenu) {
	    	notes.add(new Note<>(titre,contenu));
	    }

	 
	    
	    public void copierNote(int nindex) {
	    	if(nindex>=0 && nindex<notes.size()) {
	    		noteCopiee=notes.get(nindex);
	    		
	    		
	    	}
	    }
	    public void collerNote() {
	        if (noteCopiee != null) {
	            notes.add(new Note<>(noteCopiee.getTitre(),noteCopiee.getContenu()));
	            noteCopiee = null;
	        }
	    }

	    public void couperNote(int nindex) {
	        if(nindex>=0 && nindex<notes.size()) {
	        	copierNote(nindex);
	        	notes.remove(nindex);
	        }
	    }

	    public void annulerNote() {
	        if (!notes.isEmpty()) {
	            int dernierIndex = notes.size() - 1;
	            notes.remove(dernierIndex);
	        }
	    }
	    
	    public void retablirNote() {
	        if (!notesAnnulees.isEmpty()) {
	            int dernierIndex = notesAnnulees.size() - 1;
	            Note<Object> noteRetablie = notesAnnulees.remove(dernierIndex);
	            notes.add(noteRetablie);
	        }
	    }
	    
	    
	    
	    public void afficherNotes() {
	        for (Note<Object> note : notes) {
	            System.out.println(note.getContenu());
	        }
	    }

		public Object getContenuCopie() {
			if (noteCopiee != null) {
		        return noteCopiee.getContenu();
		    } else {
		        return null;
		    }
		}
		
		public String[] getNotesTitres() {
		    String[] titres = new String[notes.size()];
		    for (int i = 0; i < notes.size(); i++) {
		        titres[i] = notes.get(i).getTitre(); 
		    }
		    return titres;
		}
		
		
		
		
		

}
