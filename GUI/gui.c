//gcc gui.c -o gui `pkg-config --cflags --libs gtk+-3.0`
#include <gtk/gtk.h>
//CALLBACKS
void hello(GtkWidget *widget, gpointer data) 
{
	g_print("Hello World\n");
}
//Popping up do you want close window
gint delete_event(GtkWidget *widget, GdkEvent *event, gpointer data) 
{
	g_print ("Deletion occurred\n");
	return FALSE;
}

void destroy (GtkWidget *widget, gpointer data)
{
	gtk_main_quit();
}

int main (int argc, char *argv[] ) 
{
	//VAriable  declarations for ui features
	GtkWidget *window;
	GtkWidget *button;

	//Initalize GTK window
	gtk_init(&argc, &argv);

	//create new ui features
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	button = gtk_button_new_with_label("Hello World\n");

	//Set window width
	gtk_container_set_border_width(GTK_CONTAINER(window), 10);
	//add button to window container
	gtk_container_add(GTK_CONTAINER(window), button);

	//signal to handle delete_event
	g_signal_connect(G_OBJECT(window), "delete_event", G_CALLBACK(delete_event), NULL);
	//signal to handle destroy event
	g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(destroy), NULL);
	//signal to handle button click
	g_signal_connect(G_OBJECT(button), "clicked",G_CALLBACK(hello), NULL);
	//signal to destroy window when button clicked
	//useful when trying to hide other widget in button
	g_signal_connect_swapped(G_OBJECT(button), "clicked", G_CALLBACK(gtk_widget_destroy), G_OBJECT(window));

	//show widgets
	gtk_widget_show(button);
	gtk_widget_show(window);

	gtk_main();
	return 0;
}