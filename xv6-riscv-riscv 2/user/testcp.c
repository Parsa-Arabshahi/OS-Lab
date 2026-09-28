#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(void)
{
  int x = 10;

  printf("before checkpoint x=%d\n", x);

  if(checkpoint(0) == 0){
      x = 99;
      printf("modified x=%d\n", x);
      restore(0);
  } else {
      printf("after restore x=%d\n", x);
  }

  exit(0);
}