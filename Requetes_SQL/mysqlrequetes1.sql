--- Employé
INSERT INTO Employe (NumE, Nom, Prenom, DateNaissance)
VALUES 
(1, 'Deschamps', 'Fleur', TO_DATE('04/03/1995', 'DD/MM/YYYY'));

INSERT INTO Employe (NumE, Nom, Prenom, DateNaissance)
VALUES 
(2, 'Dubois', 'Pierre', TO_DATE('15/08/1990', 'DD/MM/YYYY'));

INSERT INTO Employe (NumE, Nom, Prenom, DateNaissance)
VALUES 
(3, 'Martin', 'Sophie', TO_DATE('22/04/1985', 'DD/MM/YYYY'));

INSERT INTO Employe (NumE, Nom, Prenom, DateNaissance)
VALUES 
(4, 'Lefevre', 'Antoine', TO_DATE('10/11/1998', 'DD/MM/YYYY'));

--- Stade

INSERT INTO Stade (NumS, NomS, Villes)
VALUES 
(1, 'Stade 1', 'Toulouse');

INSERT INTO Stade (NumS, NomS, Villes)
VALUES 
(2, 'Stade 2', 'Paris');
INSERT INTO Stade (NumS, NomS, Villes)
VALUES 
(3, 'Stade 3', 'Nice');

INSERT INTO Stade (NumS, NomS, Villes)
VALUES 
(3, 'Stade 3', 'Marseille');

INSERT INTO Stade (NumS, NomS, Villes)
VALUES 
(4, 'Stade 4', 'Lille');

INSERT INTO Stade (NumS, NomS, Villes)
VALUES 
(5, 'Stade 5', 'Rennes');

INSERT INTO Stade (NumS, NomS, Villes)
VALUES 
(6, 'Stade 6', 'Bourdeaux');

INSERT INTO Stade (NumS, NomS, Villes)
VALUES 
(7, 'Stade 7', 'Lyon');

--- Fournisseur
INSERT INTO Fournisseur (NumF, NomF, LigneAdresse, CodePostal, VilleF)
VALUES 
(1, 'SoGood', '21 rue de la République', '75000', 'Paris');

INSERT INTO Fournisseur (NumF, NomF, LigneAdresse, CodePostal, VilleF)
VALUES 
(2, 'SoBon', '11 route de Paris', '35000', 'Rennes');

INSERT INTO Fournisseur (NumF, NomF, LigneAdresse, CodePostal, VilleF)
VALUES 
(3, 'TastyBites', '123 Avenue des Gourmands', '69000', 'Lyon');

INSERT INTO Fournisseur (NumF, NomF, LigneAdresse, CodePostal, VilleF)
VALUES 
(4, 'FreshDrinks', '45 Rue de la Fraîcheur', '33000', 'Bordeaux');

---Produit

INSERT INTO Produit (NumP, Description, Type, Categorie)
VALUES 
(1, 'Sandwichs chèvre tomate', 'végétarien', 'salé');
INSERT INTO Produit (NumP, Description, Type, Categorie)
VALUES 
(2, 'Donuts chocolat', 'végétarien', 'sucré');
INSERT INTO Produit (NumP, Description, Type, Categorie)
VALUES 
(3, 'Sandwichs thon mayo', 'viande', 'salé');


INSERT INTO Produit (NumP, Description, Type, Categorie)
VALUES 
(4, 'Salade César', 'végétarien', 'salé');

INSERT INTO Produit (NumP, Description, Type, Categorie)
VALUES 
(5, 'Smoothie Fraise-Banane', 'végétarien', 'sucré');

INSERT INTO Produit (NumP, Description, Type, Categorie)
VALUES 
(6, 'Wrap Poulet Avocat', 'viande', 'salé');

--- Matchs
INSERT INTO MATCHS (NumM, Equipe1, Equipe2, DateM, HeureM, NumS)
VALUES 
(1, 'Équipe A', 'Équipe B', TO_DATE('11/06/2019', 'DD/MM/YYYY'), '20:00', 1);

INSERT INTO MATCHS (NumM, Equipe1, Equipe2, DateM, HeureM, NumS)
VALUES 
(2, 'Équipe C', 'Équipe D', TO_DATE('12/06/2019', 'DD/MM/YYYY'), '19:30', 2);

INSERT INTO MATCHS (NumM, Equipe1, Equipe2, DateM, HeureM, NumS)
VALUES 
(3, 'Équipe E', 'Équipe F', TO_DATE('13/06/2019', 'DD/MM/YYYY'), '18:45', 3);


---Buvette
INSERT INTO Buvette (NumB, Emplacement)
VALUES 
(1, 'Aile Ouest, Stade 1, Toulouse, 20:00-22:00, Équipe A – Équipe B, 11/06/2019');
INSERT INTO Buvette (NumB, Emplacement)
VALUES 
(2, 'Aile Est, Stade 1, Toulouse, 19:00-22:00, Équipe A – Équipe B, 11/06/2019');

INSERT INTO Buvette (NumB, Emplacement)
VALUES 
(3, 'Aile Nord, Stade 2, Paris, 18:00-21:00, Équipe C – Équipe D, 12/06/2019');

INSERT INTO Buvette (NumB, Emplacement)
VALUES 
(4, 'Aile Sud, Stade 3, Marseille, 17:30-20:30, Équipe E – Équipe F, 13/06/2019');

----Travailler
INSERT INTO TRAVAILLER (NumE, NumM, NumB, HeureDebut, HeureFin)
VALUES 
(1, 1, 1, '19:00', '20:00');
INSERT INTO TRAVAILLER (NumE, NumM, NumB, HeureDebut, HeureFin)
VALUES 
(1, 1, 2, '20:30', '22:00');

INSERT INTO TRAVAILLER (NumE, NumM, NumB, HeureDebut, HeureFin)
VALUES 
(2, 2, 3, '18:30', '21:00');
INSERT INTO TRAVAILLER (NumE, NumM, NumB, HeureDebut, HeureFin)
VALUES 
(3, 3, 4, '17:00', '20:30');


Select * FROM PRODUIT;
Select * FROM STADE;
Select * FROM FOURNISSEUR;

---Fournir

INSERT INTO FOURNIR (DateL, NumP, NumS, NumF, Quantite, PrixUnitaire)
VALUES 
('11/06/2019', 1, 1, 1, 250, 1.60);
INSERT INTO FOURNIR (DateL, NumP, NumS, NumF, Quantite, PrixUnitaire)
VALUES 
('11/06/2019', 2, 1, 1, 130, 1.25);
INSERT INTO FOURNIR (DateL, NumP, NumS, NumF, Quantite, PrixUnitaire)
VALUES 
('11/06/2019', 3, 1, 2, 130, 1.35);

INSERT INTO FOURNIR (DateL, NumP, NumS, NumF, Quantite, PrixUnitaire)
VALUES 
('12/06/2019', 4, 2, 3, 150, 4.50);

INSERT INTO FOURNIR (DateL, NumP, NumS, NumF, Quantite, PrixUnitaire)
VALUES 
('12/06/2019', 5, 3, 4, 100, 3.75);

INSERT INTO FOURNIR (DateL, NumP, NumS, NumF, Quantite, PrixUnitaire)
VALUES 
('13/06/2019', 6, 4, 3, 120, 5.20);

SELECT * FROM TRAVAILLER;
SELECT * FROM FOURNIR;

