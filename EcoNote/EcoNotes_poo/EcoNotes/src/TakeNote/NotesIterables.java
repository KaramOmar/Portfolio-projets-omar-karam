package TakeNote;

import java.util.Iterator;
import java.util.List;

public class NotesIterables<T> implements Iterable<Note<T>> {
    private List<Note<T>> notes;

    public NotesIterables(List<Note<T>> notes) {
        this.notes = notes;
    }

    
    @Override
    public Iterator<Note<T>> iterator() {
        return new NotesIterator();
    }

    // Classe interne NotesIterator 
    private class NotesIterator implements Iterator<Note<T>> {
        private int index = 0;

        @Override
        public boolean hasNext() {
            return index < notes.size();
        }

        @Override
        public Note<T> next() {
            return notes.get(index++);
        }
    }
}
