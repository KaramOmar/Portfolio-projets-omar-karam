INSERT INTO employe (NumE, Nom, Prenom, DateNaissance) VALUES 
    (13, 'Karam', 'Omar', To_Date('14/12/2001', 'DD/MM/YYYY'));
    
    
SELECT * FROM employe;

SELECT * FROM produit WHERE 
     Categorie = 'sucré';
     
SELECT * FROM fournir WHERE 
    quantite < 600;
    
    
SELECT Equipe1, Equipe2, NomS FROM matchs, stade WHERE matchs.nums = stade.nums;

SELECT DISTINCT Description FROM produit, fournir WHERE 
    fournir.nump = produit.nump;
    
SELECT * FROM matchs WHERE 
    DateM = to_date('16/06/2018', 'DD/MM/YYYY');
    
SELECT B.*, E.Nom, E.Prenom
FROM BUVETTE B
JOIN TRAVAILLER T ON B.NumB = T.NumB
JOIN EMPLOYE E ON T.NumE = E.NumE;


SELECT DISTINCT fournisseur.numf, nomf FROM fournisseur, fournir, produit WHERE 
    fournir.numf = fournisseur.numf and 
    fournir.nump = produit.nump and 
    produit.type = 'viande';
    

SELECT DISTINCT employe.nume, nom, prenom FROM employe, travailler, matchs WHERE
    employe.nume = travailler.nume and
    travailler.numm = matchs.numm and
    matchs.datem = to_date('20/06/2018', 'DD/MM/YYYY') and
    to_date(travailler.heuredebut, 'HH24:MI') >= to_date('21:00', 'HH24:MI');
    


SELECT DISTINCT produit.* FROM produit, fournir WHERE
    produit.nump = fournir.nump and
    fournir.prixunitaire >= 3.50;
    
SELECT DISTINCT *FROM  employe WHERE
    datenaissance >= to_date('01/01/1994', 'DD/MM/YYYY') and
    datenaissance < to_date('01/01/1995', 'DD/MM/YYYY');
    
    
Select DISTINCt matchs. * FROM matchs, stade where
    matchs.nums = stade.nums and
    (stade.nums = 2 or stade.nums = 3);
    
    
SELECT Emp1.nume, Emp1.nom, Emp1.Prenom, Emp2.nume, Emp2.nom, Emp2.Prenom FROM employe Emp1, employe Emp2 WHERE 
    Emp1.nume <> emp2.nume and 
    emp1.prenom = emp2.prenom and 
    emp1.nume < emp2.nume;    



SELECT COUNT (*) FROM matchs m1, matchs m2 WHERE m1.numm <> m2.numm and m1.datem < to_date ('28/06/2018', 'DD/MM/YY') and m2.datem < to_date ('28/06/2018', 'DD/MM/YY') and 
    ((m1.equipe1 = m2.equipe1 and m1.equipe2 = m2.equipe2) or (m1.equipe1 = m2.equipe2 and m1.equipe2 = m2.equipe1));   
    
    
Select distinct employe.* from employe, Travailler t1, Travailler t2 where
    t1.nume = t2.nume and
    t1.nume = employe.nume and
    t1.numb <> t2.numb;
    
Select distinct employe.* from employe, Travailler t1, Travailler t2 where
    t1.nume = t2.nume and
    t1.nume = employe.nume and
    t1.numb <> t2.numb and
    t1.numm = t2.numm;