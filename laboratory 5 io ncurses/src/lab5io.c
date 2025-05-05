#define _GNU_SOURCE
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
#include <linux/input.h>

#define ENTER_NCURSES 10

/** @brief Divides the ncruses window between four quadrants.  Once divided, it draws ### on one of the four
 * quadrants randomly.
 * 
 * 
 * 
 * @param params
 */
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

pthread_mutex_t mutex;

int get_quadrant(int x, int y)
{
  if (x < col / 2 && y < row / 2)
    return 0;
  if (x >= (col / 2) && y < row / 2)
    return 1;
  if (x < col / 2 && y >= (row / 2))
    return 2;
  return 3;
}

void *mouse_listener(void *arg)
{
  const char *device = "/dev/input/event6";
  int fd = open(device, O_RDONLY);
  if (fd == -1) {
    perror("Cannot open input device");
    exit(1);
  }

  struct input_event ev;

  double mouse_x = 32767.0;
  double mouse_y = 32767.0;

  const double sensitivity = 200.0;  

  while (1) {
    if (read(fd, &ev, sizeof(ev)) == sizeof(ev)) {
      if (ev.type == EV_REL) {
        if (ev.code == REL_X) {
          mouse_x += ev.value * sensitivity;
          if (mouse_x < 0) mouse_x = 0;
          if (mouse_x > 65535) mouse_x = 65535;
        }
        if (ev.code == REL_Y) {
          mouse_y += ev.value * sensitivity;
          if (mouse_y < 0) mouse_y = 0;
          if (mouse_y > 65535) mouse_y = 65535;
        }
      }

      if (ev.type == EV_KEY && ev.code == BTN_LEFT && ev.value == 1) {
        pthread_mutex_lock(&mutex);
        getmaxyx(stdscr, row, col);

        int terminal_x = (int)(mouse_x * col / 65535.0);
        int terminal_y = (int)(mouse_y * row / 65535.0);

        last_click = get_quadrant(terminal_x, terminal_y);

        pthread_mutex_unlock(&mutex);
      }
    }
  }

  close(fd);
  return NULL;
}
