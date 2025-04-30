#include <ctype.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include "lab5io.h"
#include <curses.h>
#include <time.h>
#include <signal.h>
#include <sys/resource.h>
#include <sys/signal.h>
#include <wait.h>
#include <pthread.h>

#define ENTER_NCURSES 10

int stop_timer = 0;

int main() {
  pthread_t thread_io;

  // Sets the attributes of the thread.
  pthread_attr_t attr;
  pthread_attr_init(&attr);

  struct sigaction action;
  action.sa_handler = TimerHandler;
  action.sa_flags = 0;
  sigaction(SIGALRM, &action, NULL);

  timer_t timer_id;

  timer_create(CLOCK_MONOTONIC, NULL, &timer_id);

  initscr();
  keypad(stdscr, TRUE);
  noecho();
  curs_set(0);

  while (1) {
    clear();
    
    srand(time(NULL));

    int rand_num = rand() % 4;

    pthread_create(&thread_io, &attr, ioDevices, (void*)&rand_num);

    struct itimerspec timer;

    // Timer parameters are configured
    // First shot of the timer
    timer.it_value.tv_sec = 0;
    timer.it_value.tv_nsec =50000000;
    // Is 0 because it would be periodic otherwise
    timer.it_interval.tv_sec = 0;
    timer.it_interval.tv_nsec = 0;

    stop_timer = 0;

    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start); // Gets the initial time right before the timer starts.

    // The timer starts
    timer_settime(timer_id, 0, &timer, NULL);

    while (!stop_timer) {
      pause();
    }

    // Gets the time after the timer ends and calculates the time it took from start to finish.
    clock_gettime(CLOCK_MONOTONIC, &end);
    double elapsed_time = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1E9;
    
    // mvprintw(5, 5, "%f", elapsed_time);
    refresh();
  }

  pthread_join(thread_io, NULL);

  getch();
  endwin();

  return 0;
}

void TimerHandler(int param) {
  stop_timer = 1;
}