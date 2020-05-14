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

Status are_equal(List_ptr list, int *array) {
  Node_ptr p_Walk = list->first;
  for(size_t i = 0; i < list->length; i++) {
    if(array[i] != *(int *)p_Walk->element) {
      return Failure;
    }
    p_Walk = p_Walk->next;
  }
  return Success;
}

Status is_even(Element element) {
  return *(int *)element % 2 == 0;
}

Element add(Element num1, Element num2) {
  *(int *)num1 = *(int *)num1 + *(int *)num2;
  return num1;
}

Element multiply_by_two(Element element) {
  Element new_element = malloc(sizeof(int));
  *(int *)new_element = *(int *)element * 2;
  return new_element;
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

__testStatus map_multiply_by_two() {
  List_ptr list = create_list();
  for(size_t i = 0; i < 4; i++) {
    add_to_list(list, create_element(i + 1));
  }
  int mapping_result[] = {2, 4, 6, 8};
  List_ptr mapped_list = map(list, &multiply_by_two);
  if(mapped_list->length == 4 && are_equal(mapped_list, mapping_result)) {
    return __Success;
  }
  return __Failure;
}

__testStatus map_empty_list() {
  List_ptr list = create_list();
  List_ptr mapped_list = map(list, &multiply_by_two);
  if(mapped_list->length == 0) {
    return __Success;
  }
  return __Failure;
}

__testStatus filter_even_numbers() {
  List_ptr list = create_list();
  for(size_t i = 0; i < 4; i++) {
    add_to_list(list, create_element(i + 1));
  }
  int result[] = {2, 4};
  List_ptr filtered_list = filter(list, &is_even);
  if(filtered_list->length == 2 && are_equal(filtered_list, result)) {
    return __Success;
  }
  return __Failure;
}

__testStatus filter_empty_array() {
  List_ptr list = create_list();
  List_ptr filtered_list = filter(list, &is_even);
  if(filtered_list->length == 0) {
    return __Success;
  }
  return __Failure;
}

__testStatus filter_array_returning_empty() {
  List_ptr list = create_list();
  add_to_list(list, create_element(1));
  List_ptr filtered_list = filter(list, &is_even);
  if(filtered_list->length == 0) {
    return __Success;
  }
  return __Failure;
}

__testStatus reduce_empty_array() {
  List_ptr list = create_list();
  Element result = reduce(list, create_element(1), &add);
  if(*(int *)result == 1) {
    return __Success;
  }
  return __Failure;
}

__testStatus sum_of_all() {
  List_ptr list = create_list();
  for(size_t i = 0; i < 4; i++) {
    add_to_list(list, create_element(i + 1));
  }
  Element result = reduce(list, create_element(0), &add);
  if(*(int *)result == 10) {
    return __Success;
  }
  return __Failure;
}

__testStatus reverse_empty_list() {
  List_ptr list = create_list();
  List_ptr reversed = reverse(list);
  if(reversed->length == 0) {
    return __Success;
  }
  return __Failure;
}

__testStatus reverse_given_list() {
  List_ptr list = create_list();
  for(size_t i = 0; i < 4; i++) {
    add_to_list(list, create_element(i + 1));
  }
  List_ptr reversed = reverse(list);
  int result[] = {4, 3, 2, 1};
  if(reversed->length == 4 && are_equal(reversed ,result)) {
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

  describe("map function");
  test_case("should return array of same length as source array with mapped values", map_multiply_by_two());
  test_case("should return empty array if source array is empty", map_empty_list());

  describe("filter function");
  test_case("should return array of filtered values based on predicate", filter_even_numbers());
  test_case("should return empty array if src is empty", filter_empty_array());
  test_case("should return empty array if filtered values are 0", filter_array_returning_empty());

  describe("reduce function");
  test_case("should return initial value if src array is empty", reduce_empty_array());
  test_case("should return sum of all numbers in src array", sum_of_all());

  describe("reverse function");
  test_case("should return empty list if src list is empty", reverse_empty_list());
  test_case("should return reversed list of given list", reverse_given_list());

  return 0;
}
