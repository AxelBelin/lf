#include "larger_file.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
  if(argc < 2) {
    printf("Usage: ./larger_file <directory>\n");
    return 1;
  }

  assert_folder(argv[1]);
  larger_file(argv[1]);
  return 0;
}
