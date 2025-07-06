open Csv
open Econote

let chemin_csv = "./ressources/notes.csv"

let default d = function
  | None -> d
  | Some v -> v

let lire_notes () =
  Csv.load chemin_csv

let ajouter_note note =
  let data = lire_notes () in
  let note_row = [
    string_of_categorie note.categorie;
    note.titre;
    note.contenu;
    note.date;
    string_of_bool note.rappel;
    default "" note.message_rappel;
    default "" note.heure_rappel
  ] in
  Csv.save chemin_csv (data @ [note_row])

let supprimer_note titre =
  let data = lire_notes () in
  let filtered = List.filter (fun row -> List.nth row 1 <> titre) data in
  Csv.save chemin_csv filtered

let modifier_note titre updated_note =
  let data = lire_notes () in
  let updated = List.map (fun row ->
    if List.nth row 1 = titre then [
      string_of_categorie updated_note.categorie;
      updated_note.titre;
      updated_note.contenu;
      updated_note.date;
      string_of_bool updated_note.rappel;
      default "" updated_note.message_rappel;
      default "" updated_note.heure_rappel
    ] else row
  ) data in
  Csv.save chemin_csv updated

let chercher_note titre =
  let data = lire_notes () in
  List.find_opt (fun row -> List.nth row 1 = titre) data

let afficher_toutes_les_notes () =
  let notes = lire_notes () in
  List.iter (fun row -> Printf.printf "Categorie: %s, Titre: %s, Contenu: %s, Date: %s, Rappel: %s, Message Rappel: %s, Heure Rappel: %s\n"
    (List.nth row 0) (List.nth row 1) (List.nth row 2) (List.nth row 3) (List.nth row 4) (List.nth row 5) (List.nth row 6)) notes

let calculer_caracteres () =
  let notes = lire_notes () in
  List.fold_left (fun acc row -> acc + String.length (List.nth row 2)) 0 notes








