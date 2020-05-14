#include<stdio.h>
#include<stdlib.h>
#include "linkedlist.h"

List_ptr create_list(void) {
  List_ptr empty_list = malloc(sizeof(LinkedList));
  if(empty_list == NULL) {
    return NULL;
  }
  empty_list->first = NULL;
  empty_list->last = NULL;
  empty_list->length = 0;
  return empty_list;
}

Node_ptr create_node(Element element) {
  Node_ptr new_node = malloc(sizeof(Node));
  if(new_node == NULL) {
    return NULL;
  }
  new_node->element = element;
  new_node->next = NULL;
  return new_node;
}

Status add_to_start(List_ptr list, Element element) {
  Node_ptr new_node = create_node(element);
  if(new_node == NULL) {
    return Failure;
  }
  if(list->first == NULL) {
    list->last = new_node;
  } else {
    new_node->next = list->first;
  }
  list->first = new_node;
  list->length++;
  return Success;
}

Status add_to_list(List_ptr list, Element element) {
  Node_ptr new_node = create_node(element);
  if(new_node == NULL) {
    return Failure;
  }
  if(list->last == NULL) {
    list->first = new_node;
  } else {
    list->last->next = new_node;
  }
  list->last = new_node;
  list->length++;
  return Success;
}

Status insert_at(List_ptr list, Element element, int position) {
  Node_ptr new_node, p_Walk;
  if(position < 0 || position > list->length) {
    return Failure;
  }
  if(position == 0) {
    return add_to_start(list, element);
  }
  if(position == list->length) {
    return add_to_list(list, element);
  }
  new_node = create_node(element);
  if(new_node == NULL) {
    return Failure;
  }
  p_Walk = list->first;
  while(position != 1) {
    p_Walk = p_Walk->next;
    position--;
  }
  new_node->next = p_Walk->next;
  p_Walk->next = new_node;
  list->length++;
  return Success;
} 

Status add_unique(List_ptr list, Element element, Matcher matcher) {
  Node_ptr p_Walk = list->first;
  while(p_Walk != NULL) {
    if((*matcher)(p_Walk->element, element)) {
      return Failure;
    }
  }
  return add_to_list(list, element);
}

Element remove_from_start(List_ptr list) {
  Node_ptr node_to_free;
  Element removed_element;
  if(list->first == NULL) {
    return NULL;
  }
  node_to_free = list->first;
  removed_element = node_to_free->element;
  if(list->length == 1) {
    list->last = NULL;
  }
  list->first = list->first->next;
  list->length--;
  free(node_to_free);
  return removed_element;
}

Element remove_from_end(List_ptr list) {
  Node_ptr p_Walk, node_to_free;
  Element removed_element;
  if(list->length == 1) {
    return remove_from_start(list);
  }
  if(list->last == NULL) {
    return NULL;
  }
  p_Walk = list->first;
  while(p_Walk->next != list->last) {
    p_Walk = p_Walk->next;
  }
  node_to_free = list->last;
  removed_element = node_to_free->element;
  p_Walk->next = NULL;
  list->last = p_Walk;
  list->length--;
  free(node_to_free);
  return removed_element;
}

Element remove_at(List_ptr list, int position) {
  Node_ptr p_Walk, node_to_free;
  Element removed_element;
  if(position < 0 || position >= list->length) {
    return NULL;
  }
  if(position == list->length - 1) {
    return remove_from_end(list);
  }
  if(position == 0) {
    return remove_from_start(list);
  }
  p_Walk = list->first;
  while(position != 1) {
    p_Walk = p_Walk->next;
    position--;
  }
  node_to_free = p_Walk->next;
  removed_element = node_to_free->element;
  p_Walk->next = p_Walk->next->next;
  list->length--;
  free(node_to_free);
  return removed_element;
}

Element remove_first_occurrence(List_ptr list, Element element, Matcher matcher) {
  Node_ptr p_Walk = list->first, previous_node, node_to_free;
  Element removed_element;
  while(p_Walk != NULL) {
    if((*matcher)(p_Walk->element, element)) {
      if(p_Walk == list->first) {
        return remove_from_start(list);
      }
      node_to_free = previous_node->next;
      if(p_Walk == list->last) {
        previous_node->next = NULL;
        list->last = previous_node;  
      } else {
        previous_node->next = p_Walk->next;
      }
      list->length--;
      removed_element = node_to_free->element;
      free(node_to_free);
      return removed_element;
    }
    previous_node = p_Walk;
    p_Walk = p_Walk->next;
  }
  return NULL;
}

List_ptr remove_all_occurrences(List_ptr list, Element element, Matcher matcher) {
  Node_ptr p_Walk = list->first, previous_node, node_to_free;
  Element removed_element;
  List_ptr new_list = create_list();
  Status status = Failure;
  while(p_Walk != NULL) {
    if((*matcher)(p_Walk->element, element)) {
      if(p_Walk == list->first) {
        removed_element = remove_from_start(list);
      } else {
        node_to_free = previous_node->next;
        removed_element = node_to_free->element;
        if(p_Walk == list->last) {
          previous_node->next = NULL;
          list->last = previous_node;
        } else {
          previous_node->next = p_Walk->next;
        }
        p_Walk = previous_node;
        list->length--;
        free(node_to_free);
      }
      add_to_list(new_list, removed_element);
    }
    previous_node = p_Walk;
    p_Walk = p_Walk->next;
  }
  return new_list;
}

Status clear_list(List_ptr list) {
  Node_ptr p_Walk = list->first, node_to_free;
  while(p_Walk != NULL) {
    node_to_free = p_Walk;
    p_Walk = p_Walk->next;
    free(node_to_free);
  }
  list->last = NULL;
  list->first = NULL;
  list->length = 0;
  return Success;
}

List_ptr map(List_ptr list, Mapper mapper) {
  Node_ptr p_Walk = list->first;
  List_ptr new_list = create_list();
  while(p_Walk != NULL) {
    add_to_list(new_list, (*mapper)(p_Walk->element));
    p_Walk = p_Walk->next;
  }
  return new_list;
}

List_ptr filter(List_ptr list, Predicate predicate) {
  Node_ptr p_Walk = list->first;
  List_ptr new_list = create_list();
  while(p_Walk != NULL) {
    if((*predicate)(p_Walk->element)) {
      add_to_list(new_list, p_Walk->element);
    }
    p_Walk = p_Walk->next;
  }
  return new_list;
}

Element reduce(List_ptr list, Element init, Reducer reducer) {
  Node_ptr p_Walk = list->first;
  while(p_Walk != NULL) {
    init = reducer(init, p_Walk->element);
    p_Walk = p_Walk->next;
  }
  return init;
}

void forEach(List_ptr list, ElementProcessor processor) {
  Node_ptr p_Walk = list->first;
  while(p_Walk != NULL) {
    processor(p_Walk->element);
    p_Walk = p_Walk->next;
  }
}

List_ptr reverse(List_ptr list) {
  List_ptr reversed_list = create_list();
  Node_ptr p_Walk = list->first;
  while(p_Walk != NULL) {
    add_to_start(reversed_list, p_Walk->element);
    p_Walk = p_Walk->next;
  }
  return reversed_list;
}
