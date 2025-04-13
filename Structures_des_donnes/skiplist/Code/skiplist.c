#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "skiplist.h"
#include "rng.h"
#include <time.h>


typedef struct s_Node* Node ;

struct s_Node {
	int value;
	Node *next;
	Node *previous;
};


struct s_SkipList {

	unsigned int level_max;
	unsigned int level_current;
	unsigned int size;
	Node sentinel;

	RNG rng;
};

struct s_SkipListIterator {
	Node cursor;
	unsigned char direction;
	Node sentinel;
};





//==================================== STATIC HELPERS

static Node node_create(SkipList sl,int value){
	Node n =malloc(sizeof(struct s_Node));
	assert(n);
	n->value=value;
	n->next=malloc(sl->level_max*sizeof(Node));
	n->previous=malloc(sl->level_max*sizeof(Node));
	return n;
}

static void node_delete(Node n){
	free(n->next);
	free(n->previous);
	free(n);
}



//==================================== CREATE
SkipList skiplist_create(int level) {
	assert(level>0);
	SkipList sl =malloc(sizeof(struct s_SkipList));
	assert(sl);
	sl->level_max=level;
	sl->level_current=1;
	sl->size=0;
	sl->rng=rng_initialize(0);
	// sentinel
	Node s=node_create(sl,INT_MAX);
	for (unsigned int i = 0; i < sl->level_max; ++i){
		s->next[i]=s;
		s->previous[i]=s;
	}
	sl->sentinel=s;
	return sl;
}


//==================================== DELETE
void skiplist_delete(SkipList sl) {
	assert(sl);
	Node s=sl->sentinel;
	if (sl->size>0){
		Node n=s->next[0];
		Node var;
		while(n!=s){
			var=n;
			n=n->next[0];
			node_delete(var);
			sl->size--;
		}
	}
	node_delete(s);
	free(sl);
}
//===================================== SIZE
unsigned int skiplist_size(SkipList sl){
	return sl->size;
}


static Node sl_get_node_before_value(SkipList sl, Node ** collected,int value){
	assert(sl);
	Node cursor=sl->sentinel;
	(*collected)=malloc(sl->level_max*sizeof(Node));
	int lv=sl->level_current;
	while (lv--) {
		while(cursor->next[lv] != sl->sentinel &&  cursor->next[lv]->value<value)
			cursor=cursor->next[lv];
		(*collected)[lv]=cursor;
	}
	return cursor;
}

static void sl_generate_node(SkipList sl, Node * collected,int value){
	unsigned int nlv=rng_get_value(&sl->rng, sl->level_max-1)+1;
	while (sl->level_current<nlv) {
		collected[sl->level_current]=sl->sentinel;
		sl->level_current++;
	}
	Node new=node_create(sl,value);
	while (nlv--) {
		new->next[nlv]=collected[nlv]->next[nlv];
		new->previous[nlv]=collected[nlv];

		new->previous[nlv]->next[nlv]=new;
		new->next[nlv]->previous[nlv]=new;
	}
	sl->size++;
}

//===================================== INSERT

SkipList skiplist_insert(SkipList sl, int value) {
	Node * collected;
	Node cursor=sl_get_node_before_value(sl, &collected, value);
	Node next=cursor->next[0];
	bool is_end = next==sl->sentinel;
	bool is_value_exist = next->value==value;
	if (is_end || !is_value_exist)
		sl_generate_node(sl,collected,value);
	free(collected);
	return sl;
}


SkipList skiplist_remove(SkipList sl, int value){
	Node * collected;
	Node cursor=sl_get_node_before_value(sl, &collected, value);
	Node next=cursor->next[0];
	bool is_end = next==sl->sentinel;
	bool is_value_exist = next->value==value;
	if (!is_end && is_value_exist){
		unsigned int lv=0;
		while (lv<sl->level_current && collected[lv]->next[lv] == next){
			collected[lv]->next[lv] = next->next[lv];
			next->next[lv]->previous[lv]=collected[lv];
			lv++;
		}
        while(sl->level_current>1 && sl->sentinel->next[sl->level_current-1] == sl->sentinel)
            sl->level_current--;
        node_delete(next);
        sl->size--;
	}
	free(collected);
	return sl;
}




bool skiplist_search(SkipList d, int value, unsigned int *nb_operations){
	Node x = malloc(sizeof(struct s_Node));
	x = d->sentinel;
	*nb_operations=0;
	for (int i=d->level_current-1;i>=0;i--)
	{
		/* code */
		while  (x->next[i]->value<value)
		{
			/* code */
			x = x->next[i];
			(*nb_operations)++;
		}
		if (x->next[i]->value==value)
		{
			(*nb_operations)++;
			return true;

		}
		
	}
	
	x = x->next[0];
	(*nb_operations)++;


	if(x->value==value){
		return true;
	}
	else{
		return false;
	}
}



int skiplist_at(SkipList sl, unsigned int i){
	assert(sl && i<sl->size);
	Node cursor = sl->sentinel;
	unsigned int pos=-1;
	while (cursor->next[0]!=sl->sentinel && pos!=i) {
		cursor=cursor->next[0];
		pos++;
	}
	return cursor->value;
}



void skiplist_map(SkipList sl, ScanOperator f, void *user_data){
	assert(sl);
	Node cursor=sl->sentinel->next[0];
	while(cursor!=sl->sentinel){
		f(cursor->value,user_data);
		cursor=cursor->next[0];
	}
}


SkipListIterator skiplist_iterator_create(SkipList sl, unsigned char direction){
	assert(sl);
	assert(direction==FORWARD_ITERATOR || direction==BACKWARD_ITERATOR);
	SkipListIterator iter=malloc(sizeof(struct s_SkipListIterator));
	assert(iter);
	iter->direction=direction;
	iter->sentinel=sl->sentinel;
	iter->cursor=NULL;
	return iter;
}

void skiplist_iterator_delete(SkipListIterator iter){
	assert(iter);
	free(iter);
}

SkipListIterator skiplist_iterator_begin(SkipListIterator iter){
	assert(iter);
	if (iter->direction==FORWARD_ITERATOR)
		iter->cursor=iter->sentinel->next[0];
	else
		iter->cursor=iter->sentinel->previous[0];
	return iter;
}

bool skiplist_iterator_end(SkipListIterator iter){
	assert(iter && iter->cursor);
	return iter->cursor==iter->sentinel;
}

SkipListIterator skiplist_iterator_next(SkipListIterator iter){
	assert(iter && iter->cursor);
	if (iter->direction==FORWARD_ITERATOR)
		iter->cursor=iter->cursor->next[0];
	else
		iter->cursor=iter->cursor->previous[0];
	return iter;
}

int skiplist_iterator_value(SkipListIterator iter){
	assert(iter && iter->cursor);
	return iter->cursor->value;
	
}
