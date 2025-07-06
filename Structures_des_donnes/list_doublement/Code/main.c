
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"


int printList(int i){
	printf("%d ", i);
	return i;
}


int accumulate(int v, void *acc) {
	*((int*)acc)+=v;
	return v;
}


bool lt(int i, int j) {
	return i<j;
}


bool gt(int i, int j) {
	return i>j;
}


int main(int argc, char **argv){
	
	if (argc<2) {
		fprintf(stderr,"usage : %s num_exercice\n", argv[0]);
		return 1;
	}

	int num_exercice = atoi(argv[1]);
	if (num_exercice < 5) {
		List *l;
		if (num_exercice >= 1) {
			printf("-------- TEST PUSH_BACK --------\n");
			l = list_create();
			for (int i=0; i<10 ;i++)
				list_push_back(l, i);
			printf("List (%d) : ", list_size(l));
			list_map(l, printList);
			printf("\n");
			
			list_delete(&l);
		}
		
		if (num_exercice >= 2) {
			printf("-------- TEST PUSH_FRONT --------\n");
			l = list_create();
			for (int i=0; i<10 ;i++)
				list_push_front(l, i);
			printf("List (%d) : ", list_size(l));
			list_map(l, printList);
			printf("\n");
			int sum = 0;
			list_reduce(l, accumulate, &sum);
			printf("Sum is %d\n", sum);
		}
		
		if (num_exercice >= 3) {
			printf("-------- TEST POP_FRONT --------\n");
			printf("Pop front : %d\n", list_front(l));
			l = list_pop_front(l);
			printf("List (%d) : ", list_size(l));
			list_map(l, printList);
			printf("\n");
		
			printf("-------- TEST POP_BACK --------\n");
			printf("Pop back : %d\n", list_back(l));
			l = list_pop_back(l);
			printf("List (%d) : ", list_size(l));
			list_map(l, printList);
			printf("\n");
		}
		
		if (num_exercice >= 2) {
			list_delete(&l);
		}
		
		if (num_exercice >= 4) {
			printf("-------- TEST INSERT_AT	--------\n");
			l = list_create();
			for (int i=0; i<10 ;i++)
				list_insert_at(l, i/2 + i%2 , i);
			printf("List (%d) : ", list_size(l));
			list_map(l, printList);
			printf("\n");

			printf("-------- TEST REMOVE_AT	--------\n");
			for (int i=0; i<5 ;i++)
				list_remove_at(l, i);
			list_remove_at(l, list_size(l)-1);
			printf("List (%d) : ", list_size(l));
			list_map(l, printList);
			printf("\n");

			while(list_size(l))
				list_remove_at(l, list_size(l)/2);
			printf("List cleared (%d) \n", list_size(l));
			
			printf("-------- TEST AT	--------\n");
			for (int i=0; i<10 ;i++)
				list_push_back(l, i);

			printf("List (%d) : ", list_size(l));
			for (int i=0; i<list_size(l); ++i)
				printf("%d ", list_at(l, i));
			printf("\n");

			list_delete(&l);
		}
	} else {
		printf("-------- TEST SORT	--------\n");
		List * l = list_create();
		list_push_back(l, 5);
		list_push_back(l, 3);
		list_push_back(l, 4);
		list_push_back(l, 1);
		list_push_back(l, 6);
		list_push_back(l, 2);
		list_push_back(l, 3);
		list_push_back(l, 7);
		printf("Unsorted list    : List (%d) : ", list_size(l));
		list_map(l, printList);
		printf("\n");

		l = list_sort(l, gt);
		printf("Decreasing order : List (%d) : ", list_size(l));
		list_map(l, printList);
		printf("\n");

		l = list_sort(l, lt);
		printf("Increasing order : List (%d) : ", list_size(l));
		list_map(l, printList);
		printf("\n");

		list_delete(&l);
	}
	return 1;
}
