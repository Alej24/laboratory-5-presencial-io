#include <ctype.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include "lab5io.h"
#include <ncurses.h>
#include <time.h>
#include <signal.h>
#include <sys/resource.h>
#include <sys/signal.h>
#include <wait.h>
#include <pthread.h>

#define ENTER_NCURSES 10

void *ioDevices(void *params)
{
  int *rand_num = (int *)params;
  int num = *rand_num;

  int row, col;

  getmaxyx(stdscr, row, col);

  for (int i = 0; i < row + 1; i++)
  {
    mvprintw(i, col / 2, "*");
  }

  for (int i = 0; i < col + 1; i++)
  {
    mvprintw(row / 2, i, "*");
  }

  mvprintw(0, 0, "Current cuadrant: %d", num);

  if (num == 0)
  {
    mvprintw(row / 4, col / 4, "###");
  }
  if (num == 1)
  {
    mvprintw(row / 4, (col / 2) + (col / 4), "###");
  }
  if (num == 2)
  {
    mvprintw((row / 2) + (row / 4), col / 4, "###");
  }
  if (num == 3)
  {
    mvprintw((row / 2) + (row / 4), (col / 2) + (col / 4), "###");
  }
}