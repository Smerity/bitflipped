#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

// https://stackoverflow.com/questions/9596945/how-to-get-appropriate-timestamp-in-c-for-logs
char *timestamp()
{
  time_t ltime; /* calendar time */
  ltime = time(NULL); /* get current cal time */
  return asctime(localtime(&ltime));
}

int main() {
  size_t bytes = 1073741824;
  unsigned int tests = 0;
  unsigned char total = 0;

  printf("=== Bitflipped ===\n");
  printf("==================\n");
  printf("Allocating a gigabyte ...\n");
  unsigned char *buffer = (unsigned char *)calloc(bytes, 1);

  printf("Run started: %s\n", timestamp());

  fflush(stdout);
  while (total == 0) {
    // We aren't going to miss a bitflip by being slow
    sleep(30);

    // Naively walk through and tally all zero bytes
    for (size_t i = 0; i < bytes; ++i) {
      total += buffer[i];
    }

    // Keep the user sane that it isn't frozen :)
    fprintf(stderr, "\rTest run #%d", tests);
    ++tests;
  }

  printf("--- !!! ---");
  printf("Error detected: %s\n", timestamp());
  printf("Result should be 0 but is %d\n", total);
  printf("Total tests run: %d\n", tests);
  fflush(stdout);
}
