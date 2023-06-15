#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include "img.h"

int leitorPastas(void){
    DIR *dp;
  struct dirent *ep;

  dp = opendir ("../base/img/cantina/");
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
    leitorPastas();
}
