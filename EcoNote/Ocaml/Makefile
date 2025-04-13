# Nom du fichier exécutable
EXEC=main

# Sources
SRC=Econote.ml BaseDeDonneesNotes.ml main.ml

# Compiler et lier avec ocamlfind et ocamlopt
OCAMLOPT=ocamlfind ocamlopt -package csv -linkpkg

all: $(EXEC)

$(EXEC):
	$(OCAMLOPT) -o $(EXEC) $(SRC)

clean:
	rm -f *.cmi *.cmo *.o *.cmx $(EXEC)

.PHONY: all clean
