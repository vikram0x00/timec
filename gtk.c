#include <gtk/gtk.h>
#include <time.h>
#include <stdio.h>

#define NULL ((void *)0)

static void print_hello(GtkWidget *widget, gpointer data){
  g_print("Hello World\n");
}

static void update_time(struct tm *lt, char *string, GtkWidget *text){
  time_t result = time(NULL);
  lt = localtime(&result);
  sprintf(string, "%02d:%02d:%02d", lt->tm_hour, lt->tm_min, lt->tm_sec);
  gtk_label_set_text(GTK_LABEL(text), string);
}

static void activate(GtkApplication *app, gpointer user_data){
  GtkWidget *window;
  GtkWidget *text;
  struct tm *lt;
  time_t result;
  char t_str[100];
  
  text = gtk_label_new(t_str);

  

  window = gtk_application_window_new(app);
  gtk_window_set_title(GTK_WINDOW(window), "TimeC");
  gtk_window_set_default_size(GTK_WINDOW(window), 300, 300);
  gtk_window_set_child(GTK_WINDOW(window), text);
  gtk_window_present(GTK_WINDOW(window));
}

int main(int argc, char **argv){
  GtkApplication *app;
  int status;

  app = gtk_application_new("org.gtk.example", G_APPLICATION_DEFAULT_FLAGS);
  g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
  status = g_application_run(G_APPLICATION(app), argc, argv);
  g_object_unref(app);

  return status;
}