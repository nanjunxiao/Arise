
#include <stdio.h>

int main(int argc, char **argv) {

  FILE *f1=NULL, *f2=NULL;
  char c1, c2;
  int same=1;

  if (argc!=3) {
    fprintf(stdout, "usage: _compare file1 file2\n");
    return -1;
  }

  f1=fopen(argv[1], "rb");
  f2=fopen(argv[2], "rb");

  if (!f1 || !f2){
    fprintf(stdout, "Files are not existent!\n");
    return -1;
  }

  while (!feof(f1) && !feof(f2)) {
    c1=fgetc(f1);
    c2=fgetc(f2);
    if (c1!=c2) {
      same=0;
      break;
    }
  }

  if (same && feof(f1) && feof(f2)) {
    same=1;
  }
  else {
    same=0;
  }

  if (same==1)  {
    fprintf(stdout, "OK: %s vs. %s\n", argv[1], argv[2]);
  }
  else {
    fprintf(stdout, "ERROR: %s vs. %s\n", argv[1], argv[2]);
  }

  fclose(f1);
  fclose(f2);

  return 0;
}
