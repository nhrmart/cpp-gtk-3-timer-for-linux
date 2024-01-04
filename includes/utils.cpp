#include <gtk-3.0/gtk/gtk.h>
#include <gtk-3.0/gdk/gdk.h>
#include <chrono>
#include <iostream>
#include <string>
#include "utils.hpp"

using namespace std;

void saveInt(string key, int value)
{
  const char *SCHEMA = "org.nhrdev.timer";
  GSettings *settings = g_settings_new(SCHEMA);

  g_settings_set_int(settings, key.c_str(), value);
}


int getInt(string key)
{
  const char *SCHEMA = "org.nhrdev.timer";
  GSettings *settings = g_settings_new(SCHEMA);

  return (int) g_settings_get_int(settings, key.c_str());
}


void applyStyle(GtkWidget *widget, const char *style)
{
  GtkStyleContext *context = gtk_widget_get_style_context(widget);
  GtkCssProvider *provider = gtk_css_provider_new();

  gtk_css_provider_load_from_data(provider, style, -1, nullptr);
  gtk_style_context_add_provider(context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
  g_object_unref(provider);
}