package Dilogueihm;
import java.awt.Dimension;
import java.awt.Toolkit;
import java.awt.datatransfer.Clipboard;
import java.awt.datatransfer.DataFlavor;
import java.awt.datatransfer.StringSelection;
import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;

import javax.swing.BoxLayout;
import javax.swing.JFileChooser;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTextArea;
import javax.swing.JTextField;
import javax.swing.undo.CannotRedoException;
import javax.swing.undo.CannotUndoException;

import Presentationihm.FrameNote;
import TakeNote.GestionnaireNoteControleur;
public class DialogNote {
	
	private FrameNote frameNote;
    private GestionnaireNoteControleur controleur;

    public DialogNote(GestionnaireNoteControleur controleur) {
        this.controleur = controleur;
    }
    
    public void setFrameNote(FrameNote frameNote) {
        this.frameNote = frameNote;
    }
    
    
    public void initDialog() {
    	if (this.frameNote != null) {
            this.frameNote.setVisible(true);
        } else {
           
            System.err.println("Erreur : FrameNote n'a pas été initialisé dans DialogNote.");
        }
    }
    
    public void refreshNotesDG() {
    	String[] titres = controleur.getNotesTitres();
        frameNote.mettreAJourAffichageNotes(titres);
        
    }
    
    public void ajouterNoteDG() {
    	JTextField titreField = new JTextField(20);

        JTextArea contenuArea = new JTextArea(5, 20);
        contenuArea.setLineWrap(true);
        contenuArea.setWrapStyleWord(true);  

        
        JScrollPane scrollPane = new JScrollPane(contenuArea);

        
        JPanel panel = new JPanel();
        panel.setLayout(new BoxLayout(panel, BoxLayout.Y_AXIS));
        panel.add(new JLabel("Titre:"));
        panel.add(titreField);
        panel.add(new JLabel("Contenu:"));
        panel.add(scrollPane);

        int resultat = JOptionPane.showConfirmDialog(frameNote, panel, 
                 "Ajouter une nouvelle note", JOptionPane.OK_CANCEL_OPTION, JOptionPane.PLAIN_MESSAGE);

       
        if (resultat == JOptionPane.OK_OPTION) {
            String titre = titreField.getText();
            String contenu = contenuArea.getText();
            if (!titre.isEmpty() && !contenu.isEmpty()) {  
                controleur.ajouterNote(titre, contenu);  
                refreshNotesDG();  
            } else {
                JOptionPane.showMessageDialog(frameNote,
                    "Le titre et le contenu de la note ne peuvent pas être vides",
                    "Erreur",
                    JOptionPane.ERROR_MESSAGE);
            }
        }
    }
    
    
    
    
    public void ajouterNouvelleNote(String titre, String contenu) {
        controleur.ajouterNote(titre, contenu);
        frameNote.mettreAJourAffichageNotes(controleur.getNotesTitres());
    }
    
    
    public void ouvrirNoteDG() {
    	JFileChooser fileChooser = new JFileChooser();
        fileChooser.setDialogTitle("Ouvrir Note");
        // utili= utilisateur
        int utiliSelection = fileChooser.showOpenDialog(frameNote);

        if (utiliSelection == JFileChooser.APPROVE_OPTION) {
            String cheminFichier = fileChooser.getSelectedFile().getAbsolutePath();
            
            String contenuNote = lireContenuFichier(cheminFichier);
            afficherContenuNote(contenuNote);
        }
    }

    private String lireContenuFichier(String cheminFichier) {
    	StringBuilder contenu = new StringBuilder();
        try {
            BufferedReader reader = new BufferedReader(new FileReader(cheminFichier));
            String ligne;
            while ((ligne = reader.readLine()) != null) {
                contenu.append(ligne).append("\n");
            }
            reader.close();
        } catch (IOException e) {
            e.printStackTrace();
            return "Erreur de la lecture du fichier";
         }
        return contenu.toString();
        
    }

   
    



    
    private void afficherContenuNote(String contenu) {
    	JTextArea textArea = new JTextArea(contenu);
        textArea.setEditable(false);  
        textArea.setLineWrap(true);
        textArea.setWrapStyleWord(true);

        JScrollPane scrollPane = new JScrollPane(textArea); 
        scrollPane.setPreferredSize(new Dimension(350, 150)); 

        JOptionPane.showMessageDialog(null, scrollPane, "Contenu de la Note", JOptionPane.INFORMATION_MESSAGE);
        
    }
    
    public void sauvegarderNoteDG() {
    	JFileChooser fileChooser = new JFileChooser();
        fileChooser.setDialogTitle("Sauvegarder les Notes");
        fileChooser.setFileSelectionMode(JFileChooser.FILES_ONLY);
        int utiliSelection = fileChooser.showSaveDialog(frameNote);

        // Si l'utilisateur confirme le choix du fichier
        if (utiliSelection == JFileChooser.APPROVE_OPTION) {
            String cheminFichier = fileChooser.getSelectedFile().getAbsolutePath();
            controleur.sauvegarderNotesDansFichier(cheminFichier);

            // Affichage le message de confirmation
            JOptionPane.showMessageDialog(frameNote, "Notes sauvegardées dans : " + cheminFichier);
        }
    	
        
    }
    
    
    
    public void sauvegarderSousNoteDG() {
        JFileChooser fileChooser = new JFileChooser();
        fileChooser.setDialogTitle("Enregistrer Sous");

        int utiliSelection = fileChooser.showSaveDialog(frameNote);

        if (utiliSelection == JFileChooser.APPROVE_OPTION) {
            String cheminFichier = fileChooser.getSelectedFile().getAbsolutePath();
            controleur.sauvegarderNotesDansFichier(cheminFichier);
            JOptionPane.showMessageDialog(frameNote, "Notes sauvegardées sous : " + cheminFichier);
        }
    }

    
    
    
    public void copierDG() {
    	JTextArea textArea = frameNote.getTextArea(); 
        String text = textArea.getSelectedText();

        if (text != null) {
            StringSelection selection = new StringSelection(text);
            Clipboard clipboard = Toolkit.getDefaultToolkit().getSystemClipboard();
            clipboard.setContents(selection, selection);
        }
    }
    	
      
    
    
    public void couperDG() {
    	JTextArea textArea = frameNote.getTextArea();
        String text = textArea.getSelectedText();

        if (text != null) {
            // je vais Copier d'abord le texte sélectionné
            StringSelection selection = new StringSelection(text);
            Clipboard clipboard = Toolkit.getDefaultToolkit().getSystemClipboard();
            clipboard.setContents(selection, selection);

            //Supprimer le texte sélectionné 
            textArea.replaceRange("", textArea.getSelectionStart(), textArea.getSelectionEnd());
        }
    }
    	
    
    
    
    public void collerDG() {
    	JTextArea textArea = frameNote.getTextArea(); 
        Clipboard clipboard = Toolkit.getDefaultToolkit().getSystemClipboard();
        try {
            
            if (clipboard.isDataFlavorAvailable(DataFlavor.stringFlavor)) {
                String data = (String) clipboard.getData(DataFlavor.stringFlavor);
                textArea.replaceSelection(data); // Collez le texte 
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
    	 
        
    

    public void annulerDG() {
    	try {
            if (frameNote.getUndoManager().canUndo()) {
                frameNote.getUndoManager().undo();
            }
        } catch (CannotUndoException e) {
            e.printStackTrace();
        }

    }
    	
    public void retablirDG() {
    	
    	try {
            if (frameNote.getUndoManager().canRedo()) {
                frameNote.getUndoManager().redo();
            }
        } catch (CannotRedoException e) {
            e.printStackTrace();
        }
    	
    }

    public void quitterApplicationDG() {
        int confirmer = JOptionPane.showConfirmDialog(null, "Êtes-vous sûr de vouloir quitter ?", "Confirmation de sortie", JOptionPane.YES_NO_OPTION);
        if (confirmer == JOptionPane.YES_OPTION) {
            System.exit(0);
        }
    }

    public void afficherAideDG() {
    	JOptionPane.showMessageDialog(frameNote, "Aide de l'application...");
    }

    


   
	







}