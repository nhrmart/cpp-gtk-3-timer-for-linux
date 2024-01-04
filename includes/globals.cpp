#include "globals.hpp"

const char *APP_SCHEMA = "org.nhrdev.timer";
int _hours = 0;
int _minutes = 0;
int _seconds = 0;
guint timerID = 0;
chrono::steady_clock::time_point timePoint;

GtkApplication *app;

GtkWidget *menuBar;
GtkWidget *settingsMenu, *exitMenu;

GtkWidget *window;
GtkWidget *startBtn, *stopBtn, *resetBtn;
GtkWidget *hours, *minutes, *seconds;