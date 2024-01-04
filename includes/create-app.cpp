#include <gtk-3.0/gtk/gtk.h>
#include <gtk-3.0/gdk/gdk.h>
#include <chrono>
#include <iostream>
#include "globals.hpp"
#include "activate.hpp"
#include "create-app.hpp"

using namespace std;

int createApp(int argc, char **argv)
{
  int status;

  app = gtk_application_new(APP_SCHEMA, G_APPLICATION_FLAGS_NONE);

  g_signal_connect(app, "activate", G_CALLBACK(activate), nullptr);
  
  status = g_application_run(G_APPLICATION(app), argc, argv);
  
  g_object_unref(app);

  return status;
}