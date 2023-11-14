#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv)
{
  int time[] = {(1 > 2), 60, 45, 56, 33, 120, 60, 45, 33, 30, 78,120,33,120,33,60,45,60,30,78,120,33,45,33,56,60,45,60,45,45,45,45,30, 60};
  printf ("%d", time[0]);
  for (int i = 1; i < argc; i++){
    int sum = 30;
    char *cur = argv[i];
    int curs = atoi(cur);
    for(int i = 0 ;i < curs; i++){
      sum+= time[i];
    }
    printf("\n SUM%d: %d\n", i, sum);
  }
  return 0;
}
