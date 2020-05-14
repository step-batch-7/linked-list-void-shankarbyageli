#include<stdio.h>
#include<stdlib.h>
#include "linkedlist.h"

List_ptr create_list(void) {
  List_ptr empty_list = malloc(sizeof(List));
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
