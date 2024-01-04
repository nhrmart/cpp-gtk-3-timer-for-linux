#include <gtk-3.0/gtk/gtk.h>
#include <gtk-3.0/gdk/gdk.h>
#include <chrono>
#include <iostream>
#include <string>
#include <map>
#include "globals.hpp"
#include "utils.hpp"
#include "timer-funcs.hpp"
#include "event-listeners.hpp"

using namespace std;

void createMenu(GtkWidget *rootBox, gpointer userData)
{
  try
  {
    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    menuBar = gtk_menu_bar_new();

    settingsMenu = gtk_menu_item_new_with_label("Settings");
    exitMenu = gtk_menu_item_new_with_label("Exit");

    gtk_menu_shell_append(GTK_MENU_SHELL(menuBar), settingsMenu);
    gtk_menu_shell_append(GTK_MENU_SHELL(menuBar), exitMenu);

    gtk_box_pack_start(GTK_BOX(vbox), menuBar, FALSE, FALSE, 0);

    gtk_container_add(GTK_CONTAINER(rootBox), vbox);
  }
  catch (exception error) {
    g_print("%s\n", error.what());
  }
}

void activate(GtkApplication *app, gpointer userData)
{

  GtkWidget *rootBox, *box;
  GtkWidget *grid;
  GtkWidget *frame;
  int unitWidth = 6;

  _hours = getInt("hours") ?: 0;
  _minutes = getInt("minutes") ?: 0;
  _seconds = getInt("seconds") ?: 0;

  g_print("hours: %d\nminutes: %d\nseconds: %d\n", _hours, _minutes, _seconds);

  window = gtk_application_window_new(GTK_APPLICATION(app));
  gtk_window_set_title(GTK_WINDOW(window), "Timer");
  gtk_window_set_default_size(GTK_WINDOW(window), 350, 150);

  g_signal_connect(window, "key-press-event", G_CALLBACK(onKeyPress), nullptr);

  const char *iconPath = "assets/images/icon.png";
  GdkPixbuf *icon = gdk_pixbuf_new_from_file(iconPath, nullptr);
  gtk_window_set_icon(GTK_WINDOW(window), icon);

  rootBox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);

  // createMenu(rootBox, userData);

  box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
  gtk_widget_set_halign(box, GTK_ALIGN_CENTER);
  gtk_widget_set_valign(box, GTK_ALIGN_CENTER);

  applyStyle(box, "box { padding: 10px; }");

  grid = gtk_grid_new();

  gtk_grid_set_row_spacing(GTK_GRID(grid), 10);
  gtk_grid_set_column_spacing(GTK_GRID(grid), 10);

  // hours
  frame = gtk_frame_new("Hours");
  gtk_frame_set_label_align(GTK_FRAME(frame), 0.5, 0);
  gtk_frame_set_shadow_type(GTK_FRAME(frame), GTK_SHADOW_NONE);
  gtk_widget_set_size_request(frame, 100, 100);
  applyStyle(frame, "frame { border: 1px solid #555; border-radius: 5px; padding: 10px; }");

  GtkWidget *insideBox1 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
  gtk_widget_set_halign(insideBox1, GTK_ALIGN_CENTER);
  gtk_widget_set_valign(insideBox1, GTK_ALIGN_CENTER);

  hours = gtk_label_new(
      _hours < 10 ? ("0" + to_string(_hours)).c_str() : (to_string(_hours)).c_str());

  applyStyle(hours, "label { font-weight: bold; font-size: 50px; }");
  gtk_container_add(GTK_CONTAINER(insideBox1), hours);

  gtk_container_add(GTK_CONTAINER(frame), insideBox1);
  gtk_grid_attach(GTK_GRID(grid), frame, 0, 0, unitWidth, 6);

  // minutes
  frame = gtk_frame_new("Minutes");
  gtk_frame_set_label_align(GTK_FRAME(frame), 0.5, 0);
  gtk_frame_set_shadow_type(GTK_FRAME(frame), GTK_SHADOW_NONE);
  gtk_widget_set_size_request(frame, 100, 100);
  applyStyle(frame, "frame { border: 1px solid #555; border-radius: 5px; padding: 10px; }");

  GtkWidget *insideBox2 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
  gtk_widget_set_halign(insideBox2, GTK_ALIGN_CENTER);
  gtk_widget_set_valign(insideBox2, GTK_ALIGN_CENTER);

  minutes = gtk_label_new(
      _minutes < 10 ? ("0" + to_string(_minutes)).c_str() : to_string(_minutes).c_str());

  applyStyle(minutes, "label { font-weight: bold; font-size: 50px; }");
  gtk_container_add(GTK_CONTAINER(insideBox2), minutes);

  gtk_container_add(GTK_CONTAINER(frame), insideBox2);
  gtk_grid_attach(GTK_GRID(grid), frame, 6, 0, unitWidth, 6);

  // seconds
  frame = gtk_frame_new("Seconds");
  gtk_frame_set_label_align(GTK_FRAME(frame), 0.5, 0);
  gtk_frame_set_shadow_type(GTK_FRAME(frame), GTK_SHADOW_NONE);
  gtk_widget_set_size_request(frame, 100, 100);
  applyStyle(frame, "frame { border: 1px solid #555; border-radius: 5px; padding: 10px; }");

  GtkWidget *insideBox3 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
  gtk_widget_set_halign(insideBox3, GTK_ALIGN_CENTER);
  gtk_widget_set_valign(insideBox3, GTK_ALIGN_CENTER);

  seconds = gtk_label_new(
      _seconds < 10 ? ("0" + to_string(_seconds)).c_str() : to_string(_seconds).c_str());

  applyStyle(seconds, "label { font-weight: bold; font-size: 50px; }");
  gtk_container_add(GTK_CONTAINER(insideBox3), seconds);

  gtk_container_add(GTK_CONTAINER(frame), insideBox3);
  gtk_grid_attach(GTK_GRID(grid), frame, 12, 0, unitWidth, 6);

  startBtn = gtk_button_new_with_label("Start");
  applyStyle(startBtn, "button { background: green; color: white; } button:active { background: darkgreen; } button:disabled { background: #333; }");
  g_signal_connect(startBtn, "clicked", G_CALLBACK(startTimer), nullptr);
  gtk_grid_attach(GTK_GRID(grid), startBtn, 0, 7, 6, 1);

  stopBtn = gtk_button_new_with_label("Stop");
  applyStyle(stopBtn, "button { background: firebrick; color: white; } button:active { background: darkred; } button:disabled { background: #333; }");
  g_signal_connect(stopBtn, "clicked", G_CALLBACK(stopTimer), nullptr);
  gtk_grid_attach(GTK_GRID(grid), stopBtn, 6, 7, 6, 1);

  resetBtn = gtk_button_new_with_label("Reset");
  applyStyle(resetBtn, "button { background: gray; color: white; } button:active { background: darkgray; } button:disabled { background: #333; }");
  g_signal_connect(resetBtn, "clicked", G_CALLBACK(resetTimer), nullptr);
  gtk_grid_attach(GTK_GRID(grid), resetBtn, 12, 7, 6, 1);

  gtk_widget_set_sensitive(startBtn, TRUE);
  gtk_widget_set_sensitive(stopBtn, FALSE);
  gtk_widget_set_sensitive(resetBtn, FALSE);

  gtk_container_add(GTK_CONTAINER(box), grid);
  gtk_container_add(GTK_CONTAINER(rootBox), box);
  gtk_container_add(GTK_CONTAINER(window), rootBox);

  gtk_widget_show_all(window);
}