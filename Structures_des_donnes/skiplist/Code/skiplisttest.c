#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "skiplist.h"

/**
 *	@defgroup SkipListTest Test program for SkipList Implantation
 *  @brief Definition of the SkipList type and operators
 *  @{
 */

/** Print a usage message for this program.

 @code{.unparsed}
 $skiplisttest -id num
 where id is :
 c : construct and print the skiplist with data read from file ../Test/test_files/construct_num.txt
 s : construct the skiplist with data read from file ../Test/test_files/construct_num.txt and search elements from file test_files/search_num..txt
 Print statistics about the searches.
 i : construct the skiplist with data read from file ../Test/test_files/construct_num.txt and search, using an iterator, elements read from file test_files/search_num.txt
 Print statistics about the searches.
 r : construct the skiplist with data read from file test_files/construct_num.txt, remove values read from file test_files/remove_num.txt and print the list in reverse order

 and num is the file number for input.
 @endcode
 */
void usage(const char *command) {
	printf("usage : %s -id num\n", command);
	printf("where id is :\n");
	printf("\tc : construct and print the skiplist with data read from file test_files/construct_num.txt\n");
	printf("\ts : construct the skiplist with data read from file test_files/construct_num.txt and search elements from file test_files/search_num..txt\n\t\tPrint statistics about the searches.\n");
	printf("\ti : construct the skiplist with data read from file test_files/construct_num.txt and search, using an iterator, elements read from file test_files/search_num.txt\n\t\tPrint statistics about the searches.\n");
	printf("\tr : construct the skiplist with data read from file test_files/construct_num.txt, remove values read from file test_files/remove_num.txt and print the list in reverse order\n");
	printf("and num is the file number for input\n");
}

/** Return the filename associated with the action to perform and the number of a test.

 @param action Describe the action associated with the file to load. Must be one of "construct" "search" or "remove"
 @param filenumber Number of the file to load. Corresponds to the number of the test to perform.
 @return fileame  in a relative form

 @code{.c}
 char *filename = gettestfilename("construct", 2);
 @endcode
 will set filename to @code{.c}"../Test/test_files/construct_2.txt"@endcode

 */
char *gettestfilename(const char *action, int numtest) {
	const char *testdir ="../Test/test_files/";
	int l = strlen(testdir) + strlen(action) + strlen("_xxx.txt");
	char *name = malloc(l*sizeof(char));
	sprintf(name, "%s%s_%d.txt", testdir, action, numtest);
	return name;
}

/** Build a list corresponding to the fiven file number.
 */
SkipList buildlist(int num) {
	SkipList d;
	FILE *input;
	unsigned int level;
	unsigned int nb_values;
	int value;

	char *constructfromfile = gettestfilename("construct", num);
	input = fopen(constructfromfile, "r");
	if (input!=NULL) {

		if(fscanf(input, "%u", &level)){};
		d = skiplist_create(level);

		if(fscanf(input, "%u", &nb_values)){};
		for (unsigned int i=0;i< nb_values; ++i) {
			if(fscanf(input, "%d", &value)){};
			d = skiplist_insert(d, value);
		}
	} else {
		printf("Unable to open file %s\n", constructfromfile);
		free(constructfromfile);
		exit (1);
	}
	free(constructfromfile);
	fclose(input);
	return d;
}

/*----------------------------------------------------------------------------------------------*/
static void printValue(int value,void * user_data){
	(void)user_data;
	printf("%d ", value);
}




/** Exercice 1.
 	Programming and test of skiplist construction.
 */
void test_construction(int num){
	SkipList sl= buildlist(num);
	printf("Skiplist (%d)\n",skiplist_size(sl));
	skiplist_map(sl, printValue, NULL);
	skiplist_delete(sl);
}

/** Exercice 2.
 Programming and test of skiplist search operator.
 */



void test_search(int num){
	SkipList sl= buildlist(num);
	FILE *input;
	unsigned int nb_values;
	int value;
	unsigned int nb_op;
	unsigned int nb_op_global=0;
	unsigned int nb_op_min;
	unsigned int nb_op_max;
	//unsigned int nb_op_mean=0;
	unsigned int nb_found=0;
	unsigned int nb_not_found=0;

	char *searchfromfile = gettestfilename("search", num);
	input = fopen(searchfromfile, "r");
	if (input!=NULL) {
		if(fscanf(input, "%u", &nb_values)){};
		for (unsigned int i=0;i< nb_values; ++i) {
			if(fscanf(input, "%d", &value)){};
			if (skiplist_search(sl, value, &nb_op)){
				printf("%d -> true\n",value);
				nb_found++;
			}else{
				printf("%d -> false\n",value);
				nb_not_found++;
			}
			if (i==0){
				nb_op_min=nb_op;
				nb_op_max=nb_op;
			}else{
				if (nb_op<nb_op_min) nb_op_min=nb_op;
				if (nb_op>nb_op_max) nb_op_max=nb_op;
			}
			nb_op_global+=nb_op;
			//nb_op_mean=(nb_op_min+nb_op_max)/2;
		}
		printf("Statistics :\n");
		printf("\tSize of the list : %d \n",skiplist_size(sl));
		printf("Search %d values :\n",nb_values);
		printf("\tFound %d\n",nb_found);
		printf("\tNot found %d\n",nb_not_found);
		printf("\tMin number of operations : %d\n",nb_op_min);
		printf("\tMax number of operations : %d\n",nb_op_max);
		//printf("\tMean number of operations :%d/%d=%d\n",nb_op_global,nb_values,(nb_op_global/nb_values) );
		printf("\tMean number of operations : %d\n",(nb_op_global/nb_values) );

	} else {
		printf("Unable to open file %s\n", searchfromfile);
		free(searchfromfile);
		skiplist_delete(sl);
		exit (1);
	}
	free(searchfromfile);
	fclose(input);
	skiplist_delete(sl);

}

/** Exercice 3.
 Programming and test of naïve search operator using iterators.
 */
void test_search_iterator(int num){
	SkipList sl= buildlist(num);
	SkipListIterator iter=skiplist_iterator_create(sl, FORWARD_ITERATOR);
	FILE *input;
	unsigned int nb_values;
	int value;
	unsigned int nb_op;
	unsigned int nb_op_global=0;
	unsigned int nb_op_min;
	unsigned int nb_op_max;
	//unsigned int nb_op_mean=0;
	unsigned int nb_found=0;
	unsigned int nb_not_found=0;
	bool found;

	char *searchfromfile = gettestfilename("search", num);
	input = fopen(searchfromfile, "r");
	if (input!=NULL) {
		if(fscanf(input, "%u", &nb_values)){};
		for (unsigned int i=0;i< nb_values; ++i) {
			if(fscanf(input, "%d", &value)){};
			found=false;
			nb_op=0;
			for(SkipListIterator e=skiplist_iterator_begin(iter);!skiplist_iterator_end(iter);e=skiplist_iterator_next(e)){
				nb_op++;
				if (skiplist_iterator_value(e)==value){
					found=true;
					break;
				}
			}
			if (found){
				printf("%d -> true\n",value);
				nb_found++;
			}else{
				printf("%d -> false\n",value);
				nb_not_found++;
			}
			if (i==0){
				nb_op_min=nb_op;
				nb_op_max=nb_op;
			}else{
				if (nb_op<nb_op_min) nb_op_min=nb_op;
				if (nb_op>nb_op_max) nb_op_max=nb_op;
			}
			nb_op_global+=nb_op;
			//nb_op_mean=(nb_op_min+nb_op_max)/2;
		}
		printf("Statistics :\n");
		printf("\tSize of the list : %d \n",skiplist_size(sl));
		printf("Search %d values :\n",nb_values);
		printf("\tFound %d\n",nb_found);
		printf("\tNot found %d\n",nb_not_found);
		printf("\tMin number of operations : %d\n",nb_op_min);
		printf("\tMax number of operations : %d\n",nb_op_max);
		//printf("\tMean number of operations :%d/%d=%d\n",nb_op_global,nb_values,(nb_op_global/nb_values) );
		printf("\tMean number of operations : %d\n",(nb_op_global/nb_values) );

	} else {
		printf("Unable to open file %s\n", searchfromfile);
		free(searchfromfile);
		skiplist_iterator_delete(iter);
		skiplist_delete(sl);
		exit (1);
	}
	free(searchfromfile);
	fclose(input);
	skiplist_iterator_delete(iter);
	skiplist_delete(sl);
}

/** Exercice 4.
 Programming and test of skiplist remove operator.
 */
void test_remove(int num){
	SkipList sl= buildlist(num);
	SkipListIterator iter=skiplist_iterator_create(sl, BACKWARD_ITERATOR);
	FILE *input;
	unsigned int nb_values;
	int value;
	char *removefromfile = gettestfilename("remove", num);
	input = fopen(removefromfile, "r");
	if (input!=NULL) {
		if(fscanf(input, "%u", &nb_values)){};
		for (unsigned int i=0;i< nb_values; ++i) {
			if(fscanf(input, "%d", &value)){
				
			};
			skiplist_remove(sl, value);
		}
		printf("Skiplist (%d)\n",skiplist_size(sl));
		for(SkipListIterator e=skiplist_iterator_begin(iter);!skiplist_iterator_end(iter);e=skiplist_iterator_next(e)){
			printf("%d ",skiplist_iterator_value(e));
		}

	} else {
		printf("Unable to open file %s\n", removefromfile);
		free(removefromfile);
		skiplist_iterator_delete(iter);
		skiplist_delete(sl);
		exit (1);
	}
	free(removefromfile);
	fclose(input);
	skiplist_iterator_delete(iter);
	skiplist_delete(sl);
}

/** Function you ca use to generate dataset for testing.
 */
void generate(int nbvalues);


int main(int argc, const char *argv[]){
	if (argc < 3) {
		usage(argv[0]);
		return 1;
	}
	switch (argv[1][1]) {
		case 'c' :
			test_construction(atoi(argv[2]));
			break;
		case 's' :
			test_search(atoi(argv[2]));
			break;
		case 'i' :
			test_search_iterator(atoi(argv[2]));
			break;
		case 'r' :
			test_remove(atoi(argv[2]));
			break;
		case 'g' :
			generate(atoi(argv[2]));
			break;
		default :
			usage(argv[0]);
			return 1;
	}
	return 0;
}


/* Generates a set of test files for a given number of value. */

void generate(int nbvalues){
	FILE *output;
	int depth;
	int maxvalue;
	output = fopen("construct.txt", "w");
	srand(nbvalues);
	depth = rand()%16;
	maxvalue = rand()%10 * nbvalues;
	fprintf(output, "%d\n%d\n", depth, nbvalues);
	for (int i=0; i< nbvalues; ++i) {
		fprintf(output, "%d\n", rand()%maxvalue);
	}
	fclose(output);
	output = fopen("search.txt", "w");
	srand(rand());
	nbvalues *= depth/4;
	fprintf(output, "%d\n", nbvalues);
	for (int i=0; i< nbvalues; ++i) {
		fprintf(output, "%d\n", rand()%maxvalue);
	}
	fclose(output);
}


/** @} */

/**
 @mainpage
 @section TP45 Implantation du TAD Listes à raccourci.
 @subsection SkipLists SkipLists
 Les listes à raccourcis, nommées SkipLists, sont une alternative aux arbres de
 recherche équilibrés que nous verrons dans la suite du cours.

 Inventées par William Pugh en 1902, elles reposent sur une structure de données
 linéaire construite de manière probabiliste.
 Les opérations de dictionnaire définies sur les listes à raccourcis sont simples à
 programmer, élégantes, et l’aspect probabiliste permet de démontrer une complexité
 moyenne en O(log(N)) au lieu des O(N) inhérents aux structures linéaires.

 Toutefois, l’aspect probabiliste de la structure de données ne permet pas d’assurer
 la complexité en pire cas, comme on pourra le faire sur les arbres équilibrés, mais
 donne, en pratique, une structure extrêmement efficace (la probabilité de construire
 une structure non efficace étant très faible). Nous ne ferons pas de démonstration
 ici, et il ne vous est pas demandé d’en effectuer une, les étudiants curieux
 pourront se rapporter à leur cours de complexité et à l’analyse fournie dans
 l’article de William Pugh, accessible sur Moodle et sur la <a href="https://dl.acm.org/citation.cfm?id=78977"> bibliothèque ACM</a>.

 @note \anchor WP-skiplist-1990 William Pugh, <a href="https://dl.acm.org/citation.cfm?id=78977">Skip lists : a probabilistic alternative to balanced trees</a> in Communications of the ACM, June 1990, 33(6) 668-676

 @subsection Objectifs Objectifs du TP
 - Implantation du TAD SkipList
 - Implantation d'un itérateur sur une SkipList
 - Comparaison empirique des opérations de dictionnaires sur les SkipList et en utilisant un itérateur.

 */
