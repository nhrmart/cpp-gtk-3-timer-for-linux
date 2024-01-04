#ifndef ACTIVATE_HPP
#define ACTIVATE_HPP

#include <gtk-3.0/gtk/gtk.h>
#include <gtk-3.0/gdk/gdk.h>
#include <chrono>
#include <iostream>
#include <string>
#include "globals.hpp"
#include "utils.hpp"
#include "timer-funcs.hpp"
#include "event-listeners.hpp"

using namespace std;

void createMenu(GtkWidget *window, gpointer userData);

void activate(GtkApplication *app, gpointer userData);

#endif