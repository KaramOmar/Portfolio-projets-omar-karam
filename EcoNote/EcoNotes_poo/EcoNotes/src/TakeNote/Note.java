package TakeNote;

import java.time.LocalDate;
import java.util.Objects;

public class Note<T> implements Comparable<Note<T>> {
    private String titre;
    private T contenu;
    private String categorie;
    private LocalDate date;
    private boolean rappel;
    private String messageRappel;
    private String heureRappel;

    public Note(String titre, T contenu, String categorie, LocalDate date, boolean rappel, String messageRappel, String heureRappel) {
        this.titre = titre;
        this.contenu = contenu;
        this.categorie = categorie;
        this.date = date;
        this.rappel = rappel;
        this.messageRappel = messageRappel;
        this.heureRappel = heureRappel;
    }

    //compareTo
    @Override
    public int compareTo(Note<T> autre) {
        // je compare  les notes par titre, puis par date
        int titreComparaison = this.titre.compareTo(autre.titre);
        if (titreComparaison != 0) {
            return titreComparaison;
        }
        return this.date.compareTo(autre.date);
    }

    //equals
    @Override
    public boolean equals(Object obj) {
        if (this == obj) return true;
        if (obj == null || getClass() != obj.getClass()) return false;
        Note<T> note = (Note<T>) obj;
        return Objects.equals(titre, note.titre) && Objects.equals(date, note.date);
    }

    //  hashCode
    @Override
    public int hashCode() {
        return Objects.hash(titre, date);
    }

    public String getTitre() {
        return titre;
    }

    public T getContenu() {
        return contenu;
    }

    public String getCategorie() {
        return categorie;
    }

    public LocalDate getDate() {
        return date;
    }

    public boolean isRappel() {
        return rappel;
    }

    public String getMessageRappel() {
        return messageRappel;
    }

    public String getHeureRappel() {
        return heureRappel;
    }
    
    public void modifierContenu(T nouveauContenu) {
        this.contenu = nouveauContenu;
    }

}
