
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

typedef struct s_LinkedElement {
	int value;
	struct s_LinkedElement *previous;
	struct s_LinkedElement *next;
} LinkedElement;


struct s_List {
	LinkedElement *sentinel;
	int size;
};



typedef struct s_SubList SubList;
/*Liste sans sentinel*/

struct s_SubList
{
	int size;
	LinkedElement *queue;
	LinkedElement *head;
};

/*-----------------------------------------------------------------*/

List *list_create() {
	List *l = malloc(sizeof (List));
	l->sentinel = malloc(sizeof(LinkedElement));
	l->sentinel->next = l->sentinel;
	l->sentinel->previous = l->sentinel;
	l->size = 0;
	return l;
}

/*-----------------------------------------------------------------*/

List *list_push_back(List *l, int v) {
	LinkedElement *e = malloc(sizeof(LinkedElement));
	e->value = v;
	e->previous = l->sentinel->previous;
	e->next = l->sentinel;
	l->sentinel->previous = e;
	e->previous->next = e;
  (l->size)++;
	return l;
}

/*-----------------------------------------------------------------*/

void list_delete(ptrList *l) {
  while((*l)->size){
    LinkedElement *temp = (*l)->sentinel->next;
    (*l)->sentinel->next = temp->next;
    temp->next->previous = (*l)->sentinel;
    free(temp);
    ((*l)->size)--;
  }
  *l=NULL;
}

/*-----------------------------------------------------------------*/

List *list_push_front(List *l, int v) {
	LinkedElement *e = malloc(sizeof(LinkedElement));
	e->next = l->sentinel->next;
	e->value = v;
	e->previous = l->sentinel;
	e->next->previous = e;
	l->sentinel->next = e;
	(l->size)++;
	return l;
}

/*-----------------------------------------------------------------*/

int list_front(List *l) {
	return(l->sentinel->next->value);
}

/*-----------------------------------------------------------------*/

int list_back(List *l) {
	return(l->sentinel->previous->value);
}

/*-----------------------------------------------------------------*/

List *list_pop_front(List *l) {
	LinkedElement *first, *second;
	first = l->sentinel->next;
	second = first->next;
	second->previous = l->sentinel;
	l->sentinel->next = second;
	--(l->size);
	free(first);
	return l;
}

/*-----------------------------------------------------------------*/

List *list_pop_back(List *l){
	LinkedElement *last, *befor_last;
	last = l->sentinel->previous;
	befor_last = last->previous;
	l->sentinel->previous = befor_last;
	befor_last->next = l->sentinel;
	--(l->size);
	free(last);
	return l;
}

/*-----------------------------------------------------------------*/

List *list_insert_at(List *l, int p, int v) {
	if (p==0)
		return list_push_front(l,v);
	if (p==l->size)
		return list_push_back(l,v);
	LinkedElement *insert = l->sentinel->next;
	LinkedElement *e = malloc(sizeof(LinkedElement));
	e->value = v;
	while(p--)insert = insert->next;
	insert->previous->next = e;
	e->previous = insert->previous;
	e->next = insert;
	insert->previous = e; 
	++(l->size);
	return l;
}

/*-----------------------------------------------------------------*/

List *list_remove_at(List *l, int p) {
	LinkedElement *e = l->sentinel->next;
	while(p--)e = e->next;
	e->previous->next = e->next;
	e->next->previous = e->previous;
	free(e);
	--(l->size);
	return l;
}

/*-----------------------------------------------------------------*/

int list_at(List *l, int p) {
	LinkedElement *e = l->sentinel->next;
	while(p--)e = e->next;
	return (e->value);
}

/*-----------------------------------------------------------------*/

bool list_is_empty(List *l) {
	return (l->size == 0);
}

/*-----------------------------------------------------------------*/

int list_size(List *l) {
	return (l->size);
}

/*-----------------------------------------------------------------*/

List * list_map(List *l, SimpleFunctor f) {
	for (LinkedElement *e = l->sentinel->next; e != l->sentinel; e = e->next)
	e->value = f(e->value);

	return l;
}


List *list_reduce(List *l, ReduceFunctor f, void *userData)
{
	for(LinkedElement *e = l->sentinel->next; e != l->sentinel; e = e->next)
	e->value = f(e->value, userData);
	return l;
}

/*-----------------------------------------------------------------*/
SubList * sublist_create(){
	SubList *sl =(SubList *)malloc(sizeof(SubList));
	assert(sl);
	sl->head=NULL;
	sl->queue=NULL;
	sl->size=0;
	return sl;
}

SubList  *list_split(SubList *l)
{
	assert(l);
	assert(l->size>1);
	SubList *resultat = sublist_create();
	int c = ((l->size) / 2)- 1;
	LinkedElement *temp = l->head;
	while (c-- > 0){
		temp = temp->next;
	}
	resultat->head = temp;
	resultat->queue = temp->next;
	resultat->size = 2;//l->size;
	return resultat;
}


SubList *push_back_sublist(SubList *l,LinkedElement *e){
	assert(l);
	if (!l->size){
		e->next=NULL;
		e->previous=NULL;
		l->head=e;
		l->queue=e;
	}else{
		e->next=NULL;
		e->previous=l->queue;
		e->previous->next=e;
		l->queue=e;
	}
	l->size++;
	return l;
}



LinkedElement * sublist_pop_front(SubList * sl){
	assert(sl->size>0);
	LinkedElement *e =sl->head;
	sl->head=e->next;
	e->next=NULL;
	e->previous=NULL;
	sl->size--;
	return e;
}


SubList *list_merge(SubList *leftlist, SubList *rightlist,OrderFunctor f){
	SubList *list = sublist_create();
	LinkedElement * element;
	while (leftlist->size || rightlist->size)
	{
		if (leftlist->size && (!rightlist->size  ||   f(leftlist->head->value,rightlist->head->value) ) ){
			element=sublist_pop_front(leftlist);
		}else {
			element=sublist_pop_front(rightlist);
		}
		push_back_sublist(list,element);
	}

	return list;
}


SubList *list_mergesort(SubList *l, OrderFunctor f){

		if(l->head==l->queue){
			return l;
		}else{
			int is_odd=l->size%2==1;


			SubList *l_left = sublist_create();
			SubList *l_right = sublist_create();

			l_left->size=l->size/2 +is_odd;
			l_right->size=l->size/2;

			SubList * separator = list_split(l);

			l_right->queue = l->queue;
			l_right->head =separator->queue ;  /*(list_split(l))->queue; (cette fonction retourne une liste dont la queue est le premier
																									  element de rightlist,et le head est le dernier element de leftlist)*/
			l_right->head->previous=NULL;
			l_right->queue->next=NULL;

			l_left->head=l->head;
			l_left->queue=separator->head;//(list_split(l))->head;

			l_left->head->previous=NULL;
			l_right->queue->next=NULL;


			SubList * merged=list_merge(list_mergesort(l_left,f),list_mergesort(l_right,f),f);


			free(l_left);
			free(l_right);
			free(separator);

			return merged;
		}
	}

List *list_sort(List *l, OrderFunctor f){
	SubList *l1 = sublist_create();
	l1->head = l->sentinel->next;
	l1->head->previous = NULL;
	l1->queue = l->sentinel->previous;
	l1->queue->next = NULL;
	l1->size = l->size;

	l1 = list_mergesort(l1,f);

	l->sentinel->next = l1->head;
	l->sentinel->previous = l1->queue;
	l->sentinel->next->previous=l->sentinel;
	l->sentinel->previous->next=l->sentinel;

	free(l1);

	return l;
}