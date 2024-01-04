#include <gtk-3.0/gtk/gtk.h>
#include <gtk-3.0/gdk/gdk.h>
#include <chrono>
#include <iostream>
#include <string>
#include "event-listeners.hpp"

gboolean onKeyPress(GtkWidget *widget, GdkEventKey *event, gpointer userData)
{
  if ((event->state && GDK_META_MASK) && event->keyval == GDK_KEY_Escape)
  {
    g_print("Ctrl + ESC key pressed\n");
  }

  return TRUE;
}