#include "lru.h"
#include <stdio.h>
#include <stdlib.h>
#include "cache.h"

void lru_init_queue(Set *set) {
  LRUNode *s = NULL;
  LRUNode **pp = &s;  // place to chain in the next node
  for (int i = 0; i < set->line_count; i++) {
    Line *line = &set->lines[i];
    LRUNode *node = (LRUNode *)(malloc(sizeof(LRUNode)));
    node->line = line;
    node->next = NULL;
    (*pp) = node;
    pp = &((*pp)->next);
  }
  set->lru_queue = s;
}

void lru_init(Cache *cache) {
  Set *sets = cache->sets;
  for (int i = 0; i < cache->set_count; i++) {
    lru_init_queue(&sets[i]);
  }
}

void lru_destroy(Cache *cache) {
  Set *sets = cache->sets;
  for (int i = 0; i < cache->set_count; i++) {
    LRUNode *p = sets[i].lru_queue;
    LRUNode *n = p;
    while (p != NULL) {
      p = p->next;
      free(n);
      n = p;
    }
    sets[i].lru_queue = NULL;
  }
}

void lru_fetch(Set *set, unsigned int tag, LRUResult *result) {
  // TODO:
  // Implement the LRU algorithm to determine which line in
  // the cache should be accessed.
  //
  LRUNode *prev=NULL;
  LRUNode *removed=NULL;
  Line *line=NULL;

  for(LRUNode *current = (set->lru_queue); current!=NULL; current=current->next)
    {
      line = current->line;

      if(line->valid && line->tag==tag)
	{
	  result->access=HIT;
	}
      else if(!(line->valid))
	{
	  line->valid=1;
	  line->tag = tag;
	  result->access = COLD_MISS;
	}
      else if(current->next == NULL)
	{
	  line->tag = tag;
	  result->access = CONFLICT_MISS;
	}
      else
	{
	  prev = current;
	  continue;
	}
      // Moving is a two step process 1) remove the node from wherever it is in the list and 2) add it to the beginning
      // Suppose we have two pointers to nodes, cur and prev
      // prev ->n ext = cur           before the change
      // prev -> next = cur -> next
      // If we want to remove from the beginning of the list, set -> lru_queue = cur -> next

      // Adding to the beginning of the list
      // node that we rem
      // set -> lru_queue = node that we removed
      //

      if(prev == NULL)
	{
	  set->lru_queue = current -> next;
	  removed = current;
	}
      else
	{
	  prev->next = current->next;
	  removed = current;
	}
      removed->next = set->lru_queue;
      set->lru_queue = removed;

      result->line = line;
      return;
    }
  
}
