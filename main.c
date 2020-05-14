#include "linkedlist.h"

void print_main_menu() {
  printf("\nMain menu\n-----------\n");
  printf("(a) add a number to the end of the list\n");
  printf("(b) add a number to the start of the list\n");
  printf("(c) insert a number at a given position in the list\n");
  printf("(d) add a unique item on the list at the end (if it already exists, do not insert)\n");
  printf("(e) remove a number from the beginning of the list\n");
  printf("(f) remove a number from the end of the list\n");
  printf("(g) remove a number from a given position in the list\n");
  printf("(h) remove first occurrence of a number\n");
  printf("(i) remove all occurrences of a number\n");
  printf("(j) clear the whole list\n");
  printf("(k) check if a number exists in the list\n");
  printf("(l) display the list of numbers\n");
  printf("(m) exit\n\n");
}

void print_search_result(Status status, int value) {
  if(status) {
    printf("%d exist in the list\n", value);
  } else {
    printf("%d doesn't exist in the list\n", value);
  }
}

void display_list(List_ptr list) {
  Node_ptr p_Walk = list->first;
  printf("Total values in list: %d\n", list->length);
  while(p_Walk != NULL) {
    printf("%d\n", *(int *)p_Walk->element);
    p_Walk = p_Walk->next;
  }
}

void print_operation_status(Status status) {
  if(status) {
    printf("Operation Completed!\n");
  } else {
    printf("Operaion Failed!\n");
  }
}

int get_position() {
  int position;
  printf("Enter the position");
  scanf("%d", &position);
  return position;
}

Element get_input() {
  Element input = malloc(sizeof(int));
  printf("Enter the integer");
  scanf("%d", (int *)input);
  return input;
}

Status is_equal(Element e1, Element e2) {
  if(*(int *)e1 == *(int *)e2) {
    return Success;
  }
  return Failure;
}

void exec_operation(List_ptr list, char choice) {
  Element value;
  int position;
  Status status;
  Element element;
  switch(choice) {
    case 'a':
      value = get_input();
      status = add_to_list(list, value);
      break;
    case 'b':
      value = get_input();
      status = add_to_start(list, value);
      break;
    case 'c':
      value = get_input();
      position = get_position();
      status = insert_at(list, value, position);
      break;
    case 'd':
      value = get_input();
      status = add_unique(list, value, &is_equal);
      break;
    case 'e':
      element = remove_from_start(list);
      if(element != NULL) {
        printf("Removed: %d\n", *(int *)element);
      }
      break;
    case 'f':
      element = remove_from_end(list);
      if(element != NULL) {
        printf("Removed: %d\n", *(int *)element);
      }
      break;
    case 'g':
      position = get_position();
      element = remove_at(list, position);
      if(element != NULL) {
        printf("Removed: %d\n", *(int *)element);
      }
      break;
    case 'h':
      value = get_input();
      element = remove_first_occurrence(list, value, &is_equal);
      if(element != NULL) {
        printf("Removed: %d\n", *(int *)element);
      }
      break;
    case 'i':
      value = get_input();
      List_ptr new_list = remove_all_occurrences(list, value, &is_equal);
      if(new_list->first != NULL) {
        display_list(new_list);
      }
      break;
    case 'j':
      status = clear_list(list);
      break;
    case 'l':
      display_list(list);
      return;
    default:
      printf("Invalid option!\n");
      return;
  }
  print_operation_status(status);
}

char get_user_choice() {
  char choice;
  fflush(stdin);
  printf("Please enter the alphabet of the operation you would like to perform: ");
  scanf("%c", &choice);
  return choice;
}

Status is_odd(Element value) {
  return *(int *)value % 2;
}

int main(void) {
  List_ptr list = create_list();
  if(list == NULL) {
    printf("Memory allocation failed!\n");
    return 0;
  }
  print_main_menu();
  char choice = get_user_choice();
  while(choice != 'm') {
    exec_operation(list, choice);
    print_main_menu();
    choice = get_user_choice();
  }
  List_ptr mapped = filter(list, &is_odd);
  display_list(mapped);
  return 0;
}
