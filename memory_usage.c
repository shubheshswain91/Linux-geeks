#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
 
#define BUFFER_SIZE 338 /* We are bothered about only the 
                           first 338 bytes of the /proc/meminfo file */
#define PROC_MEM_FILE "/proc/meminfo"
 
struct meminfo {
  unsigned long total;
  unsigned long free;
  unsigned long buffered;
  unsigned long cached;
  unsigned long swapcached;
  unsigned long swaptotal;
  unsigned long swapfree;
};
 
/* Extract numbers from a string between the start and end indices */
unsigned long extract_number(char *str, int start, int end)
{
  int i, j;
  char buf[end-start];
 
  for (i=start, j=0; i<end; i++)
    isdigit(str[i]) && (buf[j++] = str[i]);
  buf[j] = '\0';
 
  return strtoul(buf, NULL, 0) * 1024;
}
 
/* Parse the contents of /proc/meminfo file into the meminfo structure */
int get_memory_stats(struct meminfo *mem)
{
 
  char buf[BUFFER_SIZE];
  int in;
 
  if ((in = open(PROC_MEM_FILE, O_RDONLY)) total = extract_number(buf, 9, 22);
  mem->free = extract_number(buf, 35, 49);
  mem->buffered = extract_number(buf, 61, 75);
  mem->cached = extract_number(buf, 86, 101);
  mem->swapcached = extract_number(buf, 116, 127);
  mem->swaptotal = extract_number(buf, 297, 309);
  mem->swapfree = extract_number(buf, 322, 335);
 
  return 0;
 
}
 
int main(int argc, char **argv)
{
 
  struct meminfo memory;
 
  if (get_memory_stats(&memory) < 0) {
    fprintf(stderr, "%s: %s.\n", argv[0], strerror(errno));
    return -1;
  }
 
  printf("Total memory: %10lu bytes.\n", memory.total);
  printf("Free memory:  %10lu bytes.\n", memory.free);
  printf("Buffered:     %10lu bytes.\n", memory.buffered);
  printf("Cached:       %10lu bytes.\n", memory.cached);
  printf("Swap Cached:  %10lu bytes.\n", memory.swapcached);
  printf("Swap Total:   %10lu bytes.\n", memory.swaptotal);
  printf("Swap Free:    %10lu bytes.\n", memory.swapfree);
 
  return 0;
}