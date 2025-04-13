package dialog;

import interface_noyau_fonctionnel.InterfaceNoyauFonctionnel;
import java.awt.EventQueue;
import java.time.LocalDate;
import presentation.FrameReservation;

public class DialogReservation {

    private FrameReservation frameReservation;
    private InterfaceNoyauFonctionnel inf;

    public DialogReservation(InterfaceNoyauFonctionnel inf) {
        this.inf = inf;
    }

    public void initDialog() {
        frameReservation = new FrameReservation();
        frameReservation.initFrame();
        frameReservation.setDialog(this);
        frameReservation.setVisible(true);
    }

    public void handleDateSelectedEvent(LocalDate date) {
        // sauvegarder la date 
        frameReservation.enableHourSelector();
    }

    public void handleTimeSelectedEvent(String time) {
        //TODO
        throw new UnsupportedOperationException("Not implemented yet");
    }

    public void handleNumOfPersonsSelectedEvent(int nbPersons) {
        //TODO
        throw new UnsupportedOperationException("Not implemented yet");
    }

    public void handleTableSelectedEvent(int numTable) {
        //TODO
        throw new UnsupportedOperationException("Not implemented yet");
    }

    public void handleCancelEvent() {
        //TODO
        throw new UnsupportedOperationException("Not implemented yet");
    }

    public void handleValidationEvent() {
        //TODO
        LocalDate selectedDate = frameReservation.getSelectedDate();
        String selectedTime = frameReservation.getSelectedTime();
        int selectedPersons = frameReservation.getSelectedPersons();
        int selectedTable = frameReservation.getSelectedTable();
        if (selectedDate != null && selectedTime != null && selectedPersons > 0 && selectedTable > 0) {
            String[] availableTables = inf.trouverTableDisponible(selectedDate.getDayOfMonth(), selectedDate.getMonthValue(), selectedPersons, selectedTime);
            if (selectedTable <= availableTables.length) {
                frameReservation.displayConfirmationMessage(selectedDate, selectedTime, selectedPersons, "Table " + selectedTable);
            }   
            else {
                System.out.println("La table sélectionnée n'est pas disponible.");
            }
        } 
        else {
        System.out.println("Veuillez sélectionner toutes les informations nécessaires pour la réservation.");
    }
        

    }

    public static void main(String[] args) {
        DialogReservation dialog = new DialogReservation(new InterfaceNoyauFonctionnel());
        EventQueue.invokeLater(() -> {
            dialog.initDialog();
        });
    }

}
