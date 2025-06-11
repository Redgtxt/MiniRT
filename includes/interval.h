#ifndef INTERVAL_H
#define INTERVAL_H
#include <stdbool.h> 

typedef struct s_interval
{
    double min;
    double max;
}t_interval;

double  interval_size(t_interval interval);
bool    interval_contains(double x,t_interval interval);
bool    interval_surrounds(double x,t_interval interval);
t_interval interval_create(double min, double max);
double  clamp(double x,t_interval interval);
#endif