#define _GNU_SOURCE
#include <fcntl.h>
#include <linux/input.h>
#include <curses.h>
#include <pthread.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define WIDTH 80
#define HEIGHT 24

volatile sig_atomic_t timer_expired = 0;
int current_target = -1;
int last_click = -1;
pthread_mutex_t lock;

void TimerHandler(int sig)
{
    timer_expired = 1;
}

void draw_grid()
{
    clear();
    for (int y = 0; y < HEIGHT; y++)
    {
        for (int x = 0; x < WIDTH; x++)
        {
            if (x == WIDTH / 2 || y == HEIGHT / 2)
            {
                mvaddch(y, x, '*');
            }
        }
    }
    refresh();
}

void highlight_quadrant(int q)
{
    int start_y = (q < 2) ? 0 : HEIGHT / 2 + 1;
    int end_y = (q < 2) ? HEIGHT / 2 - 1 : HEIGHT - 1;
    int start_x = (q % 2 == 0) ? 0 : WIDTH / 2 + 1;
    int end_x = (q % 2 == 0) ? WIDTH / 2 - 1 : WIDTH - 1;

    for (int y = start_y; y <= end_y; y++)
    {
        for (int x = start_x; x <= end_x; x++)
        {
            mvchgat(y, x, 1, A_REVERSE, 1, NULL);
        }
    }
    refresh();
}

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
    // Inicializar ncurses
    initscr();
    curs_set(0);
    keypad(stdscr, TRUE);
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_BLUE);

    pthread_mutex_init(&lock, NULL);

    pthread_t mouse_thread;
    pthread_create(&mouse_thread, NULL, mouse_listener, NULL);

    // Configurar señal de timer
    struct sigaction action;
    action.sa_handler = TimerHandler;
    action.sa_flags = 0;
    sigaction(SIGALRM, &action, NULL);

    // Configurar el temporizador
    timer_t timer_id;
    struct sigevent sev = {
        .sigev_notify = SIGEV_SIGNAL,
        .sigev_signo = SIGALRM};
    timer_create(CLOCK_MONOTONIC, &sev, &timer_id);

    srand(time(NULL));

    while (1)
    {
        draw_grid();
        int target = rand() % 4;
        current_target = target;
        last_click = -1;
        timer_expired = 0;

        mvprintw(0, 0, "Click en cuadrante: %d", target);
        highlight_quadrant(target);

        // Empezar el temporizador de 3 segundos
        struct itimerspec its;
        its.it_value.tv_sec = 3;
        its.it_value.tv_nsec = 0;
        its.it_interval.tv_sec = 0;
        its.it_interval.tv_nsec = 0;
        timer_settime(timer_id, 0, &its, NULL);

        // Esperar hasta que expire el timer o haya clic correcto
        int acierto = 0;
        while (!timer_expired)
        {
            usleep(100000);
            pthread_mutex_lock(&lock);
            if (last_click == target)
            {
                acierto = 1;
                pthread_mutex_unlock(&lock);
                break;
            }
            pthread_mutex_unlock(&lock);
        }

        if (acierto)
        {
            mvprintw(HEIGHT - 2, 0, "¡Correcto!");
        }
        else
        {
            mvprintw(HEIGHT - 2, 0, "¡Fallaste!");
        }

        refresh();
        sleep(1);
    }

    endwin();
    return 0;
}
