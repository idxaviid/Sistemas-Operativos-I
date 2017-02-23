#include <stdlib.h>
#include <stdio.h>
int main()
{

  char *ptr_one;
  char *ptr_five;

  ptr_one = (char *)malloc(sizeof(char));
  if (ptr_one == NULL){
    printf("ERROR in MALLOC");
    return 1;
  }
  *ptr_one='C';
  printf("%c\n", *ptr_one);
 ///************** Uncomment when exercise 1 it is  done. 
 free(ptr_one); 

  ptr_five = (char *)malloc(sizeof(char)*5);
  if (ptr_five == NULL){
    printf("ERROR in MALLOC");
    return 1;
  }
  *ptr_five='C';
  ptr_five[1] = 'A';
  ptr_five[2] = 'S';
  ptr_five[3] = 'A';
  ptr_five[4] = '\0';
  printf("%s\n", ptr_five);
  free(ptr_five); 
 //*************/
  return 0;



}
