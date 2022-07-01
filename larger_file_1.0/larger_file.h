
#define _XOPEN_SOURCE 500
#include <ftw.h>
#include <unistd.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

#define NB_MAX_FILES 10
#define MAX_FILE_NAME_SIZE 100
#define UNIT_SIZE 20

#define SEPARATOR ':'
#define DEFAULT_UNIT "octets"

typedef struct _File {
  char* path;
  unsigned long long size;
  char unit[UNIT_SIZE];
} File;

typedef struct _Files {
  File** files;
  unsigned int size;
} Files;

char* allocate_str(int size);
void free_str(char str[]);

File* new_file(char* path, unsigned long long size, char unit[]);
void free_file(File* file);

Files* new_files_array();
void init_files_array();
void free_files_array(Files* fs);

void assert_folder(const char path[]);

// /usr/lib/libreoffice/program/libmergedlo.so : 51143680 octets
void print_larger_file();

void larger_file(const char* path);
