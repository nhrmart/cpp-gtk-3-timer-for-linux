#ifndef UTILS
#define UTILS

#include <gtk-3.0/gtk/gtk.h>
#include <gtk-3.0/gdk/gdk.h>
#include <chrono>
#include <iostream>
#include <string>

using namespace std;


void saveInt(string key, int value);

int getInt(string key);

void applyStyle(GtkWidget *widget, const char *style);

#endif