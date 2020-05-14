#include "../linkedlist.h"
#include "../testLib/mocha.h"

Element create_element(int value) {
  Element new_element = malloc(sizeof(int));
  *(int *)new_element = value;
  return new_element;
}

Status is_int_equal(Element e1, Element e2) {
  return *(int *)e1 == *(int *)e2;
}

__testStatus create_empty_list() {
  List_ptr list = create_list();
  if(list->first == NULL && list->last == NULL && list->length == 0) {
    return __Success;
  }
  return __Failure;
}

__testStatus create_node_of_given_value() {
  Node_ptr node = create_node(create_element(10));
  if(node->next == NULL && *(int *)node->element == 10) {
    return __Success;
  }
  return __Failure;
}

__testStatus add_to_list_in_empty_list() {
  List_ptr list = create_list();
  Status s = add_to_list(list, create_element(10));
  if(list->first->element == list->last->element && s) {
    return __Success;
  }
  return __Failure;
}

__testStatus add_to_list_in_list_with_one_number() {
  List_ptr list = create_list();
  add_to_list(list, create_element(10));
  Status s = add_to_list(list, create_element(20));
  if(*(int *)list->last->element == 20 && s) {
    return __Success;
  }
  return __Failure;
}

__testStatus add_to_start_in_empty_list() {
  List_ptr list = create_list();
  Status s = add_to_start(list, create_element(10));
  if(*(int *)list->first->element == 10 && s) {
    return __Success;
  }
  return __Failure;
}

__testStatus add_to_start_in_list_with_one_number() {
  List_ptr list = create_list();
  add_to_list(list, create_element(10));
  Status s = add_to_start(list, create_element(20));
  if(*(int *)list->first->element == 20 && list->first != list->last && s) {
    return __Success;
  }
  return __Failure;
}

__testStatus insert_at_given_position() {
  List_ptr list = create_list();
  add_to_list(list, create_element(10));
  Status s = insert_at(list, create_element(20), 0);
  if(*(int *)list->first->element == 20 && s) {
    return __Success;
  }
  return __Failure;
}

__testStatus insert_at_invalid_position() {
  List_ptr list = create_list();
  Status s1 = insert_at(list, create_element(10), 1);
  Status s2 = insert_at(list, create_element(10), -1);
  if(list->length == 0 && !s1 && !s2) {
    return __Success;
  }
  return __Failure;
}

__testStatus add_unique_already_exist() {
  List_ptr list = create_list();
  add_to_list(list, create_element(10));
  Status s = add_unique(list, create_element(10), &is_int_equal);
  if(list->length == 1 && !s) {
    return __Success;
  }
  return __Failure;
}

__testStatus add_unique_does_not_exist() {
  List_ptr list = create_list();
  add_to_list(list, create_element(10));
  Status s = add_unique(list, create_element(30), &is_int_equal);
  if(list->length == 2 && s) {
    return __Success;
  }
  return __Failure;
}

__testStatus remove_from_beginning_in_empty_list() {
  List_ptr list = create_list();
  Element removed = remove_from_start(list);
  if(list->first == NULL && list->last == NULL && list->length == 0 && removed == NULL) {
    return __Success;
  }
  return __Failure;
}

__testStatus remove_from_beginning_in_list_with_one_number() {
  List_ptr list = create_list();
  add_to_list(list, create_element(10));
  Element removed = remove_from_start(list);
  if(*(int *)removed == 10 && list->first == NULL && list->last == NULL && list->length == 0) {
    return __Success;
  }
  return __Failure;
}

__testStatus remove_from_start_in_list() {
  List_ptr list = create_list();
  add_to_list(list, create_element(10));
  add_to_list(list, create_element(20));
  add_to_list(list, create_element(30));
  Element removed = remove_from_start(list);
  if(*(int *)removed == 10 && *(int *)list->first->element == 20 && *(int *)list->last->element == 30 && list->length == 2) {
    return __Success;
  }
  return __Failure;
}

__testStatus remove_from_end_of_empty_list() {
  List_ptr list = create_list();
  Element removed = remove_from_end(list);
  if(removed == NULL && list->first == NULL && list->last == NULL && list->length == 0) {
    return __Success;
  }
  return __Failure;
}

__testStatus remove_from_end_of_one_element_list() {
  List_ptr list = create_list();
  add_to_list(list, create_element(10));
  Element removed = remove_from_end(list);
  if(*(int *)removed == 10 && list->first == NULL && list->last == NULL && list->length == 0) {
    return __Success;
  }
  return __Failure;
}

__testStatus remove_from_end_of_list() {
  List_ptr list = create_list();
  add_to_list(list, create_element(10));
  add_to_list(list, create_element(20));
  add_to_list(list, create_element(30));
  Element removed = remove_from_end(list);
  if(*(int *)removed == 30 && *(int *)list->first->element == 10 && *(int *)list->last->element == 20 && list->length == 2) {
    return __Success;
  }
  return __Failure;
}

__testStatus remove_at_invalid_position() {
  List_ptr list = create_list();
  Element removed1 = remove_at(list, 1);
  Element removed2 = remove_at(list, -1);
  if(removed1 == NULL && removed2 == NULL && list->length == 0) {
    return __Success;
  }
  return __Failure;
}

__testStatus remove_at_given_valid_position() {
  List_ptr list = create_list();
  add_to_list(list, create_element(10));
  add_to_list(list, create_element(20));
  add_to_list(list, create_element(30));
  Element removed = remove_at(list, 1);
  if(*(int *)removed == 20 && list->length == 2 && *(int *)list->first->element == 10 && *(int *)list->last->element == 30) {
    return __Success;
  }
  return __Failure;
}

__testStatus remove_first_occurrence_element_not_exist() {
  List_ptr list = create_list();
  add_to_list(list, create_element(10));
  add_to_list(list, create_element(20));
  Element removed = remove_first_occurrence(list, create_element(15), &is_int_equal);
  if(removed == NULL && list->length == 2) {
    return __Success;
  }
  return __Failure;
}

__testStatus remove_first_occurrence_number_exist() {
  List_ptr list = create_list();
  add_to_list(list, create_element(10));
  add_to_list(list, create_element(20));
  Element removed = remove_first_occurrence(list, create_element(20), &is_int_equal);
  if(*(int *)removed == 20 && list->length == 1 && *(int *)list->last->element == 10) {
    return __Success;
  }
  return __Failure;
}

__testStatus remove_all_occurrences_number_not_exist() {
  List_ptr list = create_list();
  add_to_list(list, create_element(10));
  List_ptr removed_list = remove_all_occurrences(list, create_element(20), &is_int_equal);
  if(removed_list->length == 0 && list->length == 1) {
    return __Success;
  }
  return __Failure;
}

__testStatus remove_all_occurrences_number_exist() {
  List_ptr list = create_list();
  add_to_list(list, create_element(10));
  add_to_list(list, create_element(20));
  add_to_list(list, create_element(30));
  add_to_list(list, create_element(10));
  add_to_list(list, create_element(10));
  List_ptr removed_list = remove_all_occurrences(list, create_element(10), &is_int_equal);
  if(removed_list->length == 3 && list->length == 2 && *(int *)list->first->element == 20 && *(int *)list->last->element == 30) {
    return __Success;
  }
  return __Failure;
}

__testStatus clear_empty_list() {
  List_ptr list = create_list();
  clear_list(list);
  if(list->length == 0) {
    return __Success;
  }
  return __Failure;
}

__testStatus clear_list_with_elements() {
  List_ptr list = create_list();
  add_to_list(list, create_element(10));
  add_to_list(list, create_element(20));
  clear_list(list);
  if(list->length == 0 && list->first == NULL && list->last == NULL) {
    return __Success;
  }
  return __Failure;
}

int main(void) {
  describe("create list");
  test_case("should create a empty list", create_empty_list());

  describe("create node");
  test_case("should create node with given value", create_node_of_given_value());
  
  describe("add to end of the list");
  test_case("should add to the end of empty list", add_to_list_in_empty_list());
  test_case("should add to the end of list with one number", add_to_list_in_list_with_one_number());

  describe("add to start of the list");
  test_case("should add to the start of empty list", add_to_start_in_empty_list());
  test_case("should add to the start of list with one number", add_to_start_in_list_with_one_number());

  describe("insert at given position in the list");
  test_case("should not insert at invalid position", insert_at_invalid_position());
  test_case("should insert_at given position in list", insert_at_given_position());

  describe("add unique number to list");
  test_case("should not add if number already exist in list", add_unique_already_exist());
  test_case("should add to end if number doesn't exist in list", add_unique_does_not_exist());

  describe("remove from beginning of list");
  test_case("should not remove if list is empty", remove_from_beginning_in_empty_list());
  test_case("should remove the only number of list if list has one element", remove_from_beginning_in_list_with_one_number());
  test_case("should remove the first element of list with many elements", remove_from_start_in_list());

  describe("remove from end of the list");
  test_case("should not remove if list is empty", remove_from_end_of_empty_list());
  test_case("should remove from end in list with only element", remove_from_end_of_one_element_list());
  test_case("should remove from end in list with many elements", remove_from_end_of_list());

  describe("remove a number at given position in the list");
  test_case("should not remove if position is invalid", remove_at_invalid_position());
  test_case("should remove element from list given a valid position", remove_at_given_valid_position());

  describe("remove first occurrence of the element");
  test_case("should not remove if number doesn't exist in list", remove_first_occurrence_element_not_exist());
  test_case("should remove first occurrence of number if number exist in the list", remove_first_occurrence_number_exist());

  describe("remove all occurrences of the element");
  test_case("should not remove if number doesn't exist", remove_all_occurrences_number_not_exist());
  test_case("should remove all occurrences if number exist in the list", remove_all_occurrences_number_exist());

  describe("clear the list");
  test_case("should not clear if list is empty", clear_empty_list());
  test_case("should remove all elements from list", clear_list_with_elements());

  return 0;
}
