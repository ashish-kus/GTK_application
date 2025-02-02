#include <gtk/gtk.h>
#include <libnotify/notify.h>
// Callback function to handle button click and send a notification
static void on_button_click(GtkWidget *button, gpointer data) {
    // Initialize libnotify
    if (!notify_init("GTK+ Notification Example")) {
        g_print("Unable to initialize libnotify\n");
        return;
    }
    // Create and show notification
    NotifyNotification *notification = notify_notification_new("Button Clicked", "You clicked the button!", NULL);
    notify_notification_show(notification, NULL);
    // Free the notification object
    g_object_unref(G_OBJECT(notification));
}
static void on_window_close(GtkWidget *widget, gpointer data) {
    gtk_main_quit();
}
int main(int argc, char *argv[]) {
    // Initialize GTK
    gtk_init(&argc, &argv);
    // Initialize libnotify
    if (!notify_init("GTK+ Notification Example")) {
        g_print("Unable to initialize libnotify\n");
        return -1;
    }
    // Create a window
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "GTK+ C++ with Notification");
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 300);
    // Create a button
    GtkWidget *button = gtk_button_new_with_label("Click Me");
    g_signal_connect(button, "clicked", G_CALLBACK(on_button_click), NULL);
    // Add the button to the window
    gtk_container_add(GTK_CONTAINER(window), button);
    // Connect the signal to handle window close
    g_signal_connect(window, "destroy", G_CALLBACK(on_window_close), NULL);
    // Show the window and button
    gtk_widget_show_all(window);
    // Start GTK main loop
    gtk_main();
    // Cleanup libnotify
    notify_uninit();
    return 0;
}
