#include "larger_file.h"
#include <stdio.h>
#include <stdlib.h>

Files* files_array = NULL;

void init_files_array() {
  files_array = new_files_array();
}

char* allocate_str(int size) {
  char* name = (char*)malloc(size * sizeof(char));
  assert(name != NULL);
  return name;
}

void free_str(char str[]) {
  if(str == NULL) {
    return;
  }

  free(str);
}

File* new_file(char* path, unsigned long long size, char unit[]) {
  assert(path != NULL);
  assert(unit != NULL);
  assert(size >= 0);

  File* f = (File*)malloc(sizeof(File));
  assert(f != NULL);

  f->path = allocate_str(strlen(path) + 1);
  strcpy(f->path, path);
  f->size = size;
  strcpy(f->unit, unit);
  return f;
}

void free_file(File* file) {
  if(file == NULL) {
    return;
  }

  free_str(file->path);
  free(file);
}

File** init_files() {
  int i;
  File** fs = (File**)malloc(NB_MAX_FILES * sizeof(File*));

  for(i = 0; i < NB_MAX_FILES; i++) {
    fs[i] = new_file("", 0, DEFAULT_UNIT);
  }

  return fs;
}

Files* new_files_array() {
  Files* fs = (Files*)malloc(sizeof(Files));
  assert(fs != NULL);
  fs->files = init_files();
  fs->size = 0;
  return fs;
}

void free_files_array(Files* fs) {
  if(fs == NULL) {
    return;
  }

  int i;
  for(i = 0; i < NB_MAX_FILES; i++) {
    free_file(fs->files[i]);
  }

  free(fs->files);
  free(fs);
}

void assert_folder(const char path[]) {
  assert(path != NULL);
  assert(access(path, 0) == 0);
}

int size_comparator(unsigned long long first, unsigned long long second) {
  return (int) (second - first);
}

void sort_files() {
  int i, j;
  File* tmp = NULL;

  for(i = 0; i < files_array->size; i++)
  {
    j = i ;
    tmp = files_array->files[j];

    while(j > 0 && size_comparator(tmp->size, files_array->files[j - 1]->size) <= 0)
    {
      files_array->files[j] = files_array->files[j - 1] ;
      j -= 1 ;
    }
    
    files_array->files[j] = tmp;
  }
}

static int callback(const char *fpath, const struct stat *sb, int typeflag) {
  if(files_array->size >= NB_MAX_FILES) {
    return 1;
  }

  char* fpath_copy = allocate_str(strlen(fpath) + 1);
  strcpy(fpath_copy, fpath);
  files_array->files[files_array->size] = new_file(fpath_copy, (unsigned long long)sb->st_size, DEFAULT_UNIT);
  files_array->size += 1;

  free_str(fpath_copy);
  return 0;
}

void print_larger_file() {
  assert(files_array->files != NULL);

  int i;
  for(i = 0; i < files_array->size; i++) {
    printf("%s %c %llu %s\n", files_array->files[i]->path, SEPARATOR, files_array->files[i]->size, files_array->files[i]->unit);
  }
}

void larger_file(const char* path) {
  assert(path != NULL);
  init_files_array();

  if(ftw(path, callback, 10 * NB_MAX_FILES) == -1) {
    perror("error with ftw()\n");
    exit(EXIT_FAILURE);
  }

  sort_files();
  print_larger_file();

  free_files_array(files_array);
}
