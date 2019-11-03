#include <stdio.h>

int read_file_to_mem(const char *filename, const int offset, char *mem, size_t mem_size) {
  printf("%s\n", filename);

  FILE *file;
  unsigned long filesize;

  file = fopen(filename, "rb");

  if (file == NULL) {
    printf("Failed to open file\n");
    return 0;
  }

  fseek(file, 0, SEEK_END);
	filesize=ftell(file);
	fseek(file, 0, SEEK_SET);

  if (filesize + offset <= mem_size) {
    printf("Loading %ld bytes starting at memory address 0x%x\n", filesize, offset);
  } else {
    printf("Failed to open file - file too large");
    return 0;
  }

  unsigned char *buf = mem + offset;

  fread(buf, filesize, 1, file);
	fclose(file);
  return 1;
}