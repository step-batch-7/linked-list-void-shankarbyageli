#include<stdio.h>
#include "mocha.h"

void describe(char *message) {
  static int desc_counter = 1;
  printf("%d) %s\n", desc_counter, message);
  desc_counter++;
}

void test_case(char *message, __testStatus s) {
  if(s) {
    printf("    ✅  ");
  } else {
    printf("    ❌ ");
  }
  printf("%s\n", message);
}
