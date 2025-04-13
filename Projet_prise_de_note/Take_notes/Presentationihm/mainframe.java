package Presentationihm;

import Dilogueihm.DialogNote;
import TakeNote.GestionnaireNoteControleur;
import Presentationihm.FrameNote;
public class mainframe {
	public static void main(String[] args) {
        
    	GestionnaireNoteControleur controleur = new GestionnaireNoteControleur();
    	DialogNote dialogNote = new DialogNote(controleur);
    	FrameNote frameNote = new FrameNote(dialogNote);
    	dialogNote.setFrameNote(frameNote);
    	dialogNote.initDialog();
    }


}
