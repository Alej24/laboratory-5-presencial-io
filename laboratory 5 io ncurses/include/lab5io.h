#ifndef LAB5IO_H
#define LAB5IO_H 

extern int stop_timer;
extern int current_target;
extern int last_click;
extern int win;
extern int timer_val;
extern int row, col;

void* ioDevices(void* params);

void TimerHandler(int param);

int get_quadrant(int x, int y);

void *mouse_listener(void *arg);

#endif // LAB5IO_H
