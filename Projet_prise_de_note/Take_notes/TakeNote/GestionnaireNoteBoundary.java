package TakeNote;
import java.util.List;
import java.util.ArrayList;
import TakeNote.Note;
import TakeNote.GestionnaireNoteControleur;

//Boundary
public class GestionnaireNoteBoundary {
	
	private GestionnaireNoteControleur controleur;

    public GestionnaireNoteBoundary(GestionnaireNoteControleur controleur) {
        this.controleur = controleur;
    }

    public void ajouterNoteBO(String titre,String contenu) {
        controleur.ajouterNote(titre,contenu);
    }
    
    public Note getNoteSelectionneeBO() {
        return controleur.getNoteSelectionnee();
    }
    public void supprimerNoteBO(int indexNote) {
    	controleur.supprimerNote(indexNote);
    }
    public void sauvegarderNotesDansFichierBO(String nomFichier) {
        controleur.sauvegarderNotesDansFichier(nomFichier); // Sauvegarder dans le fichier
    }
    
    public void sauvegarderNoteBO() {
        controleur.sauvegarderNote();// Affiche un message de sauvegarde
    }

    public void ecrireNoteBO(String titre,Object contenu){
    	controleur.ecrireNote(titre,contenu);
    	
    }
    
    
    public void copierNoteBO(int indexNote) {
    	controleur.copierNote(indexNote);
    }

    
    public void collerNoteBO() {
        controleur.collerNote();
    }
    public void couperNoteBO(int indexNote) {
    	controleur.couperNote(indexNote);
    	
    }
     
    public void annulerNoteBO() {
        controleur.annulerNote();
    }

    public void retablirNoteBO() {
        controleur.retablirNote();
    }

   
    public void afficherNotesBO() {
    	controleur.afficherNotes();
    }

}
