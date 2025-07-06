package TakeNote;
import java.util.ArrayList;
import java.util.List;

// Entité
@SuppressWarnings("unused")

public class Note<T> {
    private T contenu;
    private String titre;

    public Note(String titre,T contenu) {
    	this.titre = titre;
        this.contenu = contenu;
    }
    
    public String getTitre() {
        return titre;
    }
    
    public void setTitre(String titre) {
        this.titre = titre;
    }
    
    

    public T getContenu() {
        return contenu;
    }

    public void modifierContenu(T nouveauContenu) {
        this.contenu = nouveauContenu;
    }
}