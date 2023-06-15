#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include "img.h"


int leitorPastas(char*pasta){
    DIR *dp;
  struct dirent *ep;

  dp = opendir (pasta);
  if (dp != NULL)
    {
      while (ep = readdir (dp))
        puts (ep->d_name);
      (void) closedir (dp);
    }
  else
    perror ("Couldn't open the directory");

  return 0;
}


int main (void){
    
    char localidades[] ="../base/img/";
    
    leitorPastas(localidades);
}
