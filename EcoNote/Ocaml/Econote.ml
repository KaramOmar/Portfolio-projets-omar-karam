type categorie = Emission | Dechets | Ressources | Conforme | Autre

type note = {
  titre : string;
  contenu : string;
  date : string;
  categorie : categorie;
  rappel : bool;
  message_rappel : string option;
  heure_rappel : string option;
}

let create_note titre contenu date categorie rappel message_rappel heure_rappel = {
  titre;
  contenu;
  date;
  categorie;
  rappel;
  message_rappel;
  heure_rappel;
}

let string_of_categorie = function
  | Emission -> "Emission"
  | Dechets -> "Dechets"
  | Ressources -> "Ressources"
  | Conforme -> "Conforme"
  | Autre -> "Autre"

let categorie_of_string = function
  | "Emission" -> Emission
  | "Dechets" -> Dechets
  | "Ressources" -> Ressources
  | "Conforme" -> Conforme
  | _ -> Autre


let default d = function
  | None -> d
  | Some v -> v

let voir_note note =
  Printf.printf "Titre: %s\nContenu: %s\nDate: %s\nCategorie: %s\nRappel: %s\nMessage Rappel: %s\nHeure Rappel: %s\n"
    note.titre note.contenu note.date
    (string_of_categorie note.categorie)
    (if note.rappel then "Oui" else "Non")
    (default "" note.message_rappel)
    (default "" note.heure_rappel)

let get_titre notes =
  List.map (fun note -> note.titre) notes

let add_note notes note =
  note :: notes

let search_note_par_titre notes titre =
  List.find_opt (fun note -> note.titre = titre) notes

let remove_note notes titre =
  List.filter (fun note -> note.titre <> titre) notes

let voir_tous_notes notes =
  List.iter voir_note notes

let total_characters notes =
  List.fold_left (fun acc note -> acc + String.length note.contenu) 0 notes





