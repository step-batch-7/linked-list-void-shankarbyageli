#ifndef __MOCHA_H_
#define __MOCHA_H_

typedef enum {
  __Failure,
  __Success
} __testStatus;

void describe(char *);
void test_case(char *, __testStatus);

#endif
