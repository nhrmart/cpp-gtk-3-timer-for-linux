#include <gtk-3.0/gtk/gtk.h>
#include <chrono>
#include <iostream>
#include <string>
#include "globals.hpp"
#include "utils.hpp"
#include "timer-funcs.hpp"

using namespace std;

void startTimer()
{
  if (timerID == 0)
  {
    gtk_widget_set_sensitive(startBtn, FALSE);
    gtk_widget_set_sensitive(stopBtn, TRUE);
    gtk_widget_set_sensitive(resetBtn, TRUE);

    timePoint = chrono::steady_clock::now();

    timerID = g_timeout_add(
        1000,
        [](gpointer userData) -> gboolean
        {
          // auto now = chrono::steady_clock::now();
          // auto diff = chrono::duration_cast<chrono::seconds>(now - timePoint);

          _seconds++;

          if (_seconds >= 59) {
            _seconds = 0;
            _minutes++;

            saveInt("hours", _hours);
            saveInt("minutes", _minutes);
            saveInt("seconds", _seconds);
          }

          if (_minutes >= 59) {
            _minutes = 0;
            _hours++;
          }

          gtk_label_set_text(GTK_LABEL(hours), (_hours < 10 ? "0" + to_string(_hours) : to_string(_hours)).c_str());
          gtk_label_set_text(GTK_LABEL(minutes), (_minutes < 10 ? "0" + to_string(_minutes) : to_string(_minutes)).c_str());
          gtk_label_set_text(GTK_LABEL(seconds), (_seconds < 10 ? "0" + to_string(_seconds) : to_string(_seconds)).c_str());

          return G_SOURCE_CONTINUE;
        },
        nullptr);
  }
}

void stopTimer()
{
  if (timerID != 0)
  {
    g_source_remove(timerID);
    timerID = 0;

    saveInt("hours", _hours);
    saveInt("minutes", _minutes);
    saveInt("seconds", _seconds);

    gtk_widget_set_sensitive(startBtn, TRUE);
    gtk_widget_set_sensitive(stopBtn, FALSE);
    gtk_widget_set_sensitive(resetBtn, FALSE);
  }
}

void resetTimer()
{
  stopTimer();

  _hours = 0;
  _minutes = 0;
  _seconds = 0;

  saveInt("hours", 0);
  saveInt("minutes", 0);
  saveInt("seconds", 0);

  gtk_label_set_text(GTK_LABEL(hours), "00");
  gtk_label_set_text(GTK_LABEL(minutes), "00");
  gtk_label_set_text(GTK_LABEL(seconds), "00");
}
