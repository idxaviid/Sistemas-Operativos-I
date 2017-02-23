#include <stdio.h>
#include <string.h>
#include <math.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "rwpid.c"

#define SIZE 100

void tostring(char [], int);

/******************************************************************************/

void tostring(char str[], int num)
{
    int i, rem, len = 0, n;
 
    n = num;
    while (n != 0)
    {
        len++;
        n /= 10;
    }
    for (i = 0; i < len; i++)
    {
        rem = num % 10;
        num = num / 10;
        str[len - (i + 1)] = rem + '0';
    }
    str[len] = '\0';
}

/******************************************************************************/

void guardaId()
{
  //Defino el tamaño del buffer
  char str_id[SIZE];
  //Convierto el ID del proceso a cadena
  tostring(str_id,getpid());

  int fd;
  char *a = str_id;
  //Escribo el ID del proceso principal
  fd = open("principal.pid", O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
  write(fd,a,strlen(a));
  close(fd);

}

/******************************************************************************/
int main(void)
{

  guardaId();

  int len;
  int hh, mm, ss;
  char buffer[SIZE];

  ss = 00;
  mm = 00;
  hh = 00;

  sprintf(buffer, "%02d:%02d:%02d\n", hh, mm, ss);

  len = strlen(buffer);
  write(1, buffer, len);

  //Hago que el programa se quede esperando una señal
  pause();

  return 0;
}
/********************************************************************************/