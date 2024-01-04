#ifndef EVENT_LISTENERS_HPP
#define EVENT_LISTENERS_HPP

#include <gtk-3.0/gtk/gtk.h>
#include <gtk-3.0/gdk/gdk.h>
#include <chrono>
#include <iostream>
#include <string>

gboolean onKeyPress(GtkWidget *widget, GdkEventKey *event, gpointer userData);

#endif