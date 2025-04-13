Require Import List.
Require Import String.
Import ListNotations.
Require Import Lia.
Open Scope string_scope.
Module Type EcoNotes.


(* Définition des types de données *)
Parameter Note : Type.
Parameter Categorie : Type.

(* Opérations sur les notes *)
Parameter creer_note : string -> Categorie -> Note.
Parameter ajouter_note : Note -> list Note -> list Note.
Parameter supprimer_note : Note -> list Note -> list Note.
Parameter trouver_note : string -> list Note -> option Note.
Parameter afficher_notes : list Note -> string.
Parameter afficher_note_Categorie : Categorie -> list Note -> string.
Parameter trouver_Categorie : string -> list Categorie -> option Categorie.
Parameter Rappel_note : Note -> string.
Parameter Sauvegarder_note : Note -> string.

(* Propriétés à vérifier *)

(* Propriétés de création de notes *)
Axiom creer_note_vide : forall (cat : Categorie), exists n : Note, creer_note "" cat = n.
Axiom creer_note_non_vide : forall (txt : string) (cat : Categorie), txt <> EmptyString -> exists n : Note, creer_note txt cat = n.

(* Propriétés d'ajout de notes *)
Axiom ajouter_note_non_existant : forall (n : Note) (l : list Note), ~ In n l -> In n (ajouter_note n l).
Axiom ajouter_note_existant : forall (n : Note) (l : list Note), In n l -> ajouter_note n l = l.

(* Propriétés de suppression de notes *)
Axiom supprimer_note_existant : forall (n : Note) (l : list Note), In n l -> ~ In n (supprimer_note n l).
Axiom supprimer_note_non_existant : forall (n : Note) (l : list Note), ~ In n l -> supprimer_note n l = l.

(* Propriétés de modification de notes *)
Axiom modification_note_vide : forall (txt : string) (cat : Categorie), txt <> EmptyString -> exists n' : Note, creer_note txt cat = n' /\ Rappel_note n' = txt.
Axiom modification_note_non_vide : forall (n : Note) (txt : string) (cat : Categorie), txt <> EmptyString -> exists n' : Note, creer_note txt cat = n' /\ Rappel_note n' = txt.

(* Propriétés de sauvegarde de notes *)
Axiom sauvegarde_ajout : forall (n : Note), Sauvegarder_note n = "Note enregistrée".

Axiom sauvegarde_modification : forall (n : Note) (txt : string) (cat : Categorie), txt <> EmptyString -> exists n' : Note, creer_note txt cat = n' /\ Sauvegarder_note n' = "Note enregistrée".

(* Propriétés de recherche et d'affichage des catégories *)
Axiom recherche_categorie : forall (cat : string) (lc : list Categorie), exists c : Categorie, trouver_Categorie cat lc = Some c.
Axiom affichage_categories : forall (c : Categorie) (ln : list Note), exists s : string, afficher_note_Categorie c ln = s.

(* Théorèmes *)


Theorem creer_note_vide_correct : forall (cat : Categorie), exists n : Note, creer_note "" cat = n.
Proof.
  intros cat.
  apply creer_note_vide.
Qed.

Theorem creer_note_non_vide_correct : forall (txt : string) (cat : Categorie), txt <> EmptyString -> exists n : Note, creer_note txt cat = n.
Proof.
  intros txt cat H.
  apply creer_note_non_vide.
  assumption.
Qed.

(* Théorèmes d'ajout de notes *)
Theorem ajouter_note_non_existant_correct : forall (n : Note) (l : list Note), ~ In n l -> In n (ajouter_note n l).
Proof.
  intros n l H.
  apply ajouter_note_non_existant.
  assumption.
Qed.

Theorem ajouter_note_existant_correct : forall (n : Note) (l : list Note), In n l -> ajouter_note n l = l.
Proof.
  intros n l H.
  apply ajouter_note_existant.
  assumption.
Qed.

Theorem supprimer_note_existant_correct : forall (n : Note) (l : list Note), In n l -> ~ In n (supprimer_note n l).
Proof.
  intros n l H.
  apply supprimer_note_existant.
  assumption.
Qed.

Theorem supprimer_note_non_existant_correct : forall (n : Note) (l : list Note), ~ In n l -> supprimer_note n l = l.
Proof.
  intros n l H.
  apply supprimer_note_non_existant.
  assumption.
Qed.


Theorem modification_note_vide_correct : forall (txt : string) (cat : Categorie), txt <> EmptyString -> exists n' : Note, creer_note txt cat = n' /\ Rappel_note n' = txt.
Proof.
  intros txt cat H.
  pose proof (modification_note_vide txt cat H) as [n' [Hcreer HRappel]].
  exists n'.
  split.
  - assumption.
  - assumption.
Qed.

Theorem modification_note_non_vide_correct : forall (n : Note) (txt : string) (cat : Categorie), txt <> EmptyString -> exists n' : Note, creer_note txt cat = n' /\ Rappel_note n' = txt.
Proof.
  intros n txt cat H.
  pose proof (modification_note_non_vide n txt cat H) as [n' [Hcreer HRappel]].
  exists n'.
  split.
  - assumption.
  - assumption.
Qed.


Theorem sauvegarde_ajout_correct : forall (n : Note) (l : list Note), In n (ajouter_note n l) -> Sauvegarder_note n = "Note enregistrée".
Proof.
  intros n l H.
  apply sauvegarde_ajout.
Qed.



Theorem sauvegarde_modification_correct : forall (n : Note) (txt : string) (cat : Categorie), txt <> EmptyString -> exists n' : Note, creer_note txt cat = n' /\ Sauvegarder_note n' = "Note enregistrée".
Proof.
  intros n txt cat H.
  pose proof (sauvegarde_modification n txt cat H) as [n' [Hcreer HSauvegarde]].
  exists n'.
  split.
  - assumption.
  - assumption.
Qed.


Theorem recherche_categorie_correct : forall (cat : string) (lc : list Categorie), exists c : Categorie, trouver_Categorie cat lc = Some c.
Proof.
  intros cat lc.
  apply recherche_categorie.
Qed.


Theorem affichage_categories_correct : forall (c : Categorie) (ln : list Note), exists s : string, afficher_note_Categorie c ln = s.
Proof.
  intros c ln.
  apply affichage_categories.
Qed.

End EcoNotes.
