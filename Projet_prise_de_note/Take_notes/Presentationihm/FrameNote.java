package Presentationihm;
import java.awt.BorderLayout;
import java.awt.FlowLayout;
import java.awt.Font;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.KeyEvent;

import javax.swing.DefaultListModel;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JList;
import javax.swing.JMenu;
import javax.swing.JMenuBar;
import javax.swing.JMenuItem;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTextArea;
import javax.swing.undo.UndoManager;

import Dilogueihm.DialogNote;
import TakeNote.GestionnaireNoteControleur;

public class FrameNote extends JFrame {
	  private JTextArea textArea;
	  private JList<String> listNotes;
	  private DialogNote dialogNote;
	  private UndoManager undoManager = new UndoManager();
	  private DefaultListModel<String> listModel;
	  
	  public FrameNote(DialogNote dialogNote) {
		  this.dialogNote = dialogNote;
		  listModel = new DefaultListModel<>();
	      listNotes = new JList<>(listModel);
		  setTitle(" Prise Notes");
		  setSize(800, 600);
		  setLocationRelativeTo(null);
		  setDefaultCloseOperation(EXIT_ON_CLOSE);
        

        //la barre Menu
        JMenuBar menuBar = new JMenuBar();
        
      //TextAREA
        textArea = new JTextArea();
        //JScrollPane
        JScrollPane scrollPane = new JScrollPane(textArea);
        
        getContentPane().add(scrollPane, BorderLayout.CENTER);
        setVisible(true);
        
        
        


        // menu Fichier
        JMenu fileMenu = new JMenu("Fichier");
        fileMenu.setMnemonic(KeyEvent.VK_F);
        menuBar.add(fileMenu);

        // menu Fichier
        JMenuItem addNoteItem = new JMenuItem("Ajouter Note");
        JMenuItem openNoteItem = new JMenuItem("Ouvrir Note");
        JMenuItem saveItem = new JMenuItem("Enregistrer");
        JMenuItem saveAsItem = new JMenuItem("Enregistrer Sous");
        JMenuItem quitItem = new JMenuItem("Quitter");

        fileMenu.add(addNoteItem);
        fileMenu.add(openNoteItem);
        fileMenu.add(saveItem);
        fileMenu.add(saveAsItem);
        fileMenu.addSeparator(); 
        fileMenu.add(quitItem);
        
  
        
        addNoteItem.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                dialogNote.ajouterNoteDG(); 
            }
        });
        
        
        saveItem.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                dialogNote.sauvegarderNoteDG();
            }
        });
        
        
        
        saveAsItem.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                dialogNote.sauvegarderSousNoteDG();
            }
        });
        
        
        openNoteItem.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                dialogNote.ouvrirNoteDG();
            }
        });
        
        
        
        quitItem.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
            	 dialogNote.quitterApplicationDG();
            }
        });
        
        
        
        
        //  menu Édition
        JMenu editMenu = new JMenu("Edit");
        editMenu.setMnemonic(KeyEvent.VK_E);
        menuBar.add(editMenu);

        //  menu Édition
        JMenuItem undoItem = new JMenuItem("Annuler");
        JMenuItem redoItem = new JMenuItem("Rétablir");
        JMenuItem copyItem = new JMenuItem("Copier");
        JMenuItem cutItem = new JMenuItem("Couper");
        JMenuItem pasteItem = new JMenuItem("Coller");

        editMenu.add(undoItem);
        editMenu.add(redoItem);
        editMenu.add(copyItem);
        editMenu.add(cutItem);
        editMenu.add(pasteItem);

        
        setJMenuBar(menuBar);
        
       
        //Anuller
        undoItem.addActionListener(new ActionListener() {
        public void actionPerformed(ActionEvent e) {
            dialogNote.annulerDG();
        }
    });
        
        //Rétablir
        
        redoItem.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                dialogNote.retablirDG();
            }
        });
        editMenu.add(redoItem);
        
        
        
       
        
        //copier
        copyItem.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                dialogNote.copierDG();
            }
        });
        
        //coller
        pasteItem.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                dialogNote.collerDG();
            }
        });
        
        
        //couper
        cutItem.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                dialogNote.couperDG();
            }
        });
        editMenu.add(cutItem);
        
     //Aide
        JMenu helpMenu = new JMenu("Help");
        helpMenu.setMnemonic(KeyEvent.VK_H);
        menuBar.add(helpMenu);

        // menu "Aide"
        JMenuItem aboutItem = new JMenuItem("À propos");
        helpMenu.add(aboutItem);

        // À propos
        aboutItem.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                AfficherHelpDialog();
            }
        });

        
    //}
        
        
    
    JPanel bottomPanel = new JPanel(new FlowLayout(FlowLayout.RIGHT));
    JButton addButton = new JButton("+");
    addButton.setFont(new Font("Arial", Font.BOLD, 24));  // la police Arial
    addButton.addActionListener(new ActionListener() {
        @Override
        public void actionPerformed(ActionEvent e) {
        	String titre = JOptionPane.showInputDialog("Entrez le titre de la note");
            String contenu = JOptionPane.showInputDialog("Entrez le contenu de la note");
            dialogNote.ajouterNouvelleNote(titre, contenu);
        }
    });
    
    bottomPanel.add(addButton);

   
    getContentPane().add(bottomPanel, BorderLayout.SOUTH);
    
    JTextArea textArea_1 = new JTextArea();
    getContentPane().add(textArea_1, BorderLayout.NORTH);

    
    setJMenuBar(menuBar);

    setVisible(true);
}
	  
	  
	  
	 public UndoManager getUndoManager() {
	        return undoManager;
	  }
	 
	 public JTextArea getTextArea() {
		    return textArea;
		}
    
	 
	 
	 private void AfficherHelpDialog() {
        String helpMessage = "Comment utiliser l'application :\n"
            + "- Utilisez 'Fichier > Ajouter Note' pour créer une nouvelle note.\n"
            + "- Utilisez 'Fichier > Enregistrer' pour sauvegarder les notes.\n"
            + "- Utilisez 'Edit' pour copier, couper et coller du texte.\n";
            

        JOptionPane.showMessageDialog(this, helpMessage, "À propos", JOptionPane.INFORMATION_MESSAGE);
    }
    
	 public void mettreAJourAffichageNotes(String[] titres) {
			// TODO Auto-generated method stub
		 listModel.clear();
		 for (String titre : titres) {
			 listModel.addElement(titre);
	        }
			
		}
    
    
	
}