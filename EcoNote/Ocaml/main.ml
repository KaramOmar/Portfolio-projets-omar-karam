open Econote
open BaseDeDonneesNotes

let () =
  let action = Sys.argv.(1) in
  match action with
  | "-c" ->
    let titre = Sys.argv.(2) in
    let contenu = Sys.argv.(3) in
    let date = Sys.argv.(4) in
    let categorie = categorie_of_string (Sys.argv.(5)) in
    let rappel = bool_of_string (Sys.argv.(6)) in
    let message_rappel = Some (Sys.argv.(7)) in
    let heure_rappel = Some (Sys.argv.(8)) in
    let note = create_note titre contenu date categorie rappel message_rappel heure_rappel in
    ajouter_note note;
    Printf.printf "Note creer et sauvegarder.\n"
  | "-r" ->
    afficher_toutes_les_notes ()
  | "-u" ->
    let titre = Sys.argv.(2) in
    let contenu = Sys.argv.(3) in
    let date = Sys.argv.(4) in
    let categorie = categorie_of_string (Sys.argv.(5)) in
    let rappel = bool_of_string (Sys.argv.(6)) in
    let message_rappel = Some (Sys.argv.(7)) in
    let heure_rappel = Some (Sys.argv.(8)) in
    let updated_note = create_note titre contenu date categorie rappel message_rappel heure_rappel in
    modifier_note titre updated_note;
    Printf.printf "Note updated.\n"
  | "-d" ->
    let titre = Sys.argv.(2) in
    supprimer_note titre;
    Printf.printf "Note supprimer.\n"
  | "-s" ->
    let titre = Sys.argv.(2) in
    (match chercher_note titre with
     | Some row -> Printf.printf "Note Trouvé: %s, %s, %s, %s, %s, %s, %s\n"
                     (List.nth row 0) (List.nth row 1) (List.nth row 2) (List.nth row 3) (List.nth row 4) (List.nth row 5) (List.nth row 6)
     | None -> Printf.printf "Note pas trouvé\n")
  | "-t" ->
    let total_chars = calculer_caracteres () in
    Printf.printf "Total characters pour tous les notes: %d\n" total_chars
  | _ -> Printf.printf "command inconnue\n"

let () =
  try
    let ic = open_in chemin_csv in
    close_in ic;
    print_endline "Fichier accessible et prêt pour lecture/écriture."
  with
  | Sys_error err -> Printf.printf "Erreur lors de l'accès au fichier: %s\n" err








