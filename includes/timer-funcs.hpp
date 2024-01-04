#ifndef TIMER_FUNCS
#define TIMER_FUNCS

#include <gtk-3.0/gtk/gtk.h>
#include <chrono>
#include <iostream>
#include <string>
#include "globals.hpp"
#include "utils.hpp"
#include "timer-funcs.hpp"

using namespace std;

void startTimer();
void stopTimer();
void resetTimer();

#endif