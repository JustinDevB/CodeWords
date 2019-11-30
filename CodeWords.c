#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

#define SZ 5000

// Repeatedly exclusive or values until we cannot possibly get any new values

int codewords[SZ];

int isNew(int n, int top) {
    for (int i = 0; i < top; i++) {
	if (codewords[i] == n) {
	    return 0;
    }
  }
 return 1;
}

int main(int argc, char *argv[]) {

  FILE *fd;
  int size, bit, top;
  fd = fopen(argv[1], "r");

  if (fd == NULL) {
    perror("fopen");
    exit(1);
  }

  fscanf(fd, "%d", &size);

  top = size;
  int oldtop = 0, newtop = top;

 for (int i = 0; i < size; i++) {
   int ans = 0;
   for (int j = 0; j < size; j++) { 
     fscanf(fd, "%d", &bit);
     ans <<= 1;
     ans ^= bit;
   }
   codewords[i] = ans;
 }
 fclose(fd);
 do {
   newtop = top;
    for (int i = 0; i < size; i++) {
      for (int j = oldtop; j < newtop; j++) {
        int n = (codewords[j] ^ codewords[i]);

	if (isNew(n, top)) {
	  codewords[top] = n;
	  top++;
	 } 
      }
    
    }
  oldtop = newtop;

 } while (newtop < top);
 printf("Top: %d\n", top);
 printf("----------------------\n");
 for(int i=0; i<20; i++)
	  printf("%d\n", codewords[i]);
}
