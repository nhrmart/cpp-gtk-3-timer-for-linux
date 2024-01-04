#ifndef GLOBALS_HPP
#define GLOBALS_HPP

#include <gtk-3.0/gtk/gtk.h>
#include <gtk-3.0/gdk/gdk.h>
#include <chrono>
#include <iostream>
#include <string>

using namespace std;

extern const char *APP_SCHEMA;
extern int _hours;
extern int _minutes;
extern int _seconds;
extern guint timerID;
extern chrono::steady_clock::time_point timePoint;

extern GtkApplication *app;

extern GtkWidget *menuBar;
extern GtkWidget *settingsMenu, *exitMenu;

extern GtkWidget *window;
extern GtkWidget *startBtn, *stopBtn, *resetBtn;
extern GtkWidget *hours, *minutes, *seconds;

#endif