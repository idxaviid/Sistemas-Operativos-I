#include <stdio.h>
#include <string.h>
#include <math.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/signal.h>

#define SIZE 100

unsigned int alarm(unsigned int seconds);
void tostring(char [], int);
int min = 0;

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

void alarm_handler(int signum)
{

  
  //printf("%d\n",min);
  min++;

  if (min == 60)
  {
    min= 0;
  }

  //Pongo una alarma para 1 minuto
  alarm(60);
}

/******************************************************************************/

int main()
{

  //Defino el tamaño del buffer
  char str_id[SIZE];
  //Convierto el ID del proceso a cadena
  tostring(str_id,getpid());

  int fd;
  char *a = str_id;

  //Escribo el ID del proceso minutos
  fd = open("minutos.pid", O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
  write(fd,a,strlen(a));
  close(fd);

  //Pongo el handler de la alarma
  signal(SIGALRM, alarm_handler);

  //Programo la primera alarma
  alarm(60);

  //Hago que el programa se quede esperando una señal
  while(1)
  {
    pause();
  }

  return 0;
}

/******************************************************************************/



