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
#define WIDTH 80
#define HEIGHT 24

int stop_timer = 0;
int current_target = -1;
int last_click = -1;
int timer_expired = -1;
int win = 0;
int timer_val = 3;

pthread_mutex_t lock;

int get_quadrant(int x, int y)
{
  if (x < WIDTH / 2 && y < HEIGHT / 2)
    return 0;
  if (x >= WIDTH / 2 && y < HEIGHT / 2)
    return 1;
  if (x < WIDTH / 2 && y >= HEIGHT / 2)
    return 2;
  return 3;
}

void *mouse_listener(void *arg)
{
  const char *device = "/dev/input/event6";
  int fd = open(device, O_RDONLY);
  if (fd == -1)
  {
    perror("No se pudo abrir el dispositivo de entrada");
    exit(1);
  }

  struct input_event ev;
  int mx = 0, my = 0;

  while (1)
  {
    if (read(fd, &ev, sizeof(ev)) == sizeof(ev))
    {
      if (ev.type == EV_ABS)
      {
        if (ev.code == ABS_X)
          mx = ev.value;
        if (ev.code == ABS_Y)
          my = ev.value;
      }
      if (ev.type == EV_KEY && ev.code == BTN_LEFT && ev.value == 1)
      {
        int q = get_quadrant(mx / 10, my / 10);
        pthread_mutex_lock(&lock);
        last_click = q;
        pthread_mutex_unlock(&lock);
      }
    }
  }

  close(fd);
  return NULL;
}

int main()
{
  int rand_num = 0;

  pthread_t thread_io;
  pthread_t mouse_thread;

  initscr();
  keypad(stdscr, TRUE);
  noecho();
  curs_set(0);

  pthread_mutex_init(&lock, NULL);
  pthread_create(&mouse_thread, NULL, mouse_listener, NULL);

  // Sets the attributes of the thread.
  pthread_attr_t attr;
  pthread_attr_init(&attr);

  struct sigaction action;
  action.sa_handler = TimerHandler;
  action.sa_flags = 0;
  sigaction(SIGALRM, &action, NULL);

  timer_t timer_id;

  timer_create(CLOCK_MONOTONIC, NULL, &timer_id);

  while (1)
  {
    clear();

    int row, col;

    getmaxyx(stdscr, row, col);

    srand(time(NULL));

    mvprintw(1, 0, "Timer: %d", timer_val);

    timer_val--;

    if (timer_val < 0 && last_click == -1) {
      mvprintw((row / 2) - 1, (col / 2) - 5, "You Lose!");
      timer_val = 3;
      rand_num = rand() % 4;
    } else if (timer_val > 0 && last_click != -1) {
      mvprintw((row / 2) - 1, (col / 2) - 5, "You Win!");
      timer_val = 3;
      rand_num = rand() % 4;
    }

    current_target = rand_num;
    // last_click = -1;
    // timer_expired = 0;

    pthread_create(&thread_io, &attr, ioDevices, (void *)&rand_num);

    struct itimerspec timer;

    // Timer parameters are configured
    // First shot of the timer
    timer.it_value.tv_sec = 1;
    timer.it_value.tv_nsec = 0;
    // Is 0 because it would be periodic otherwise
    timer.it_interval.tv_sec = 0;
    timer.it_interval.tv_nsec = 0;

    stop_timer = 0;

    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start); // Gets the initial time right before the timer starts.

    // The timer starts
    timer_settime(timer_id, 0, &timer, NULL);

    while (!stop_timer)
    {
      pause();
    }

    // Gets the time after the timer ends and calculates the time it took from start to finish.
    clock_gettime(CLOCK_MONOTONIC, &end);
    double elapsed_time = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1E9;

    refresh();
  }

  pthread_join(mouse_thread, NULL);
  pthread_join(thread_io, NULL);

  getch();
  endwin();

  return 0;
}

void TimerHandler(int param)
{
  stop_timer = 1;
}
