//gcc gui.c -o gui `pkg-config --cflags --libs gtk+-3.0`
#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
//CALLBACKS
static void on_open_image(GtkButton *button, gpointer user_data)
{
	GtkWidget *image = GTK_WIDGET(user_data);
	GdkPixbuf *pb;
	GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_OPEN;
	GtkWidget *top_level = gtk_widget_get_toplevel(image);
	GtkFileFilter *filter = gtk_file_filter_new();
	GtkWidget *dialog = gtk_file_chooser_dialog_new(("open Image"), GTK_WINDOW(top_level),
													  action,
                                    					("_Cancel"),
                                     					GTK_RESPONSE_CANCEL,
                                     					("_Open"),
                                      					GTK_RESPONSE_ACCEPT,
                                      					NULL);
	gtk_file_filter_add_pixbuf_formats(filter);
	gtk_file_chooser_add_filter(GTK_FILE_CHOOSER(dialog), filter);

	switch(gtk_dialog_run(GTK_DIALOG(dialog))) 
	{
		case GTK_RESPONSE_ACCEPT:
		{
			gchar *file_name = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));
			pb = gdk_pixbuf_new_from_file(file_name, NULL);
			pb = gdk_pixbuf_scale_simple(pb,700,700,GDK_INTERP_BILINEAR);
			gtk_image_set_from_pixbuf(GTK_IMAGE(image), pb);
			break;
		}
		default:
			break;
	}
	gtk_widget_destroy(dialog);
}
//Popping up do you want close window
gint delete_event(GtkWidget *widget, GdkEvent *event, gpointer data) 
{
	gtk_main_quit();
	//if return TRUE will close
	return FALSE;
}

int main (int argc, char *argv[] ) 
{
	//VAriable  declarations for ui features
	GtkWidget *window;
	GtkWidget *open, *edit, *image, *process, *analyze;
	GtkWidget *rectangle, *circle, *polygon, *hand, *zoom;
	GtkWidget *grid;
	GtkWidget *imagecont;
	GtkWidget *box;

	//Initalize GTK window
	gtk_init(&argc, &argv);
	

	//create new ui features
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	box = gtk_box_new(GTK_ORIENTATION_VERTICAL,5);
	imagecont = gtk_image_new();
	gtk_box_pack_start(GTK_BOX(box),imagecont,TRUE,TRUE,0);

	open = gtk_button_new_with_label("open\n");
	edit = gtk_button_new_with_label("edit\n");
	image = gtk_button_new_with_label("image\n");
	process = gtk_button_new_with_label("process\n");
	analyze = gtk_button_new_with_label("analyze\n");
	edit = gtk_button_new_with_label("edit\n");

	rectangle = gtk_button_new_with_label("rectangle\n");
	circle = gtk_button_new_with_label("circle\n");
	polygon = gtk_button_new_with_label("polygon\n");
	hand = gtk_button_new_with_label("hand\n");
	zoom = gtk_button_new_with_label("analyze\n");
	grid = gtk_grid_new();
	//box

	gtk_grid_attach(GTK_GRID(grid), open, 0,0,1,1);
	gtk_grid_attach(GTK_GRID(grid), edit, 1,0,1,1);
	gtk_grid_attach(GTK_GRID(grid), image, 2,0,1,1);
	gtk_grid_attach(GTK_GRID(grid), process, 3,0,1,1);
	gtk_grid_attach(GTK_GRID(grid), analyze, 4,0,1,1);


	gtk_grid_attach(GTK_GRID(grid), rectangle, 0,1,1,1);
	gtk_grid_attach(GTK_GRID(grid), circle, 1,1,1,1);
	gtk_grid_attach(GTK_GRID(grid), polygon, 2,1,1,1);
	gtk_grid_attach(GTK_GRID(grid), hand, 3,1,1,1);
	gtk_grid_attach(GTK_GRID(grid), zoom, 4,1,1,1);
	gtk_grid_attach(GTK_GRID(grid), box, 1,2,1,1);

	
	
	
	//box
	
	//set window title
	gtk_window_set_title(GTK_WINDOW(window), "KIBICHO is BAE");
	//set window size
	gtk_window_set_default_size(GTK_WINDOW(window), 500,500);
	gtk_window_set_resizable(GTK_WINDOW(window), FALSE);
	//Set window width
	gtk_container_set_border_width(GTK_CONTAINER(window), 10);
	//add button to window container
	gtk_container_add(GTK_CONTAINER(window), grid);

	//Main signal to handle delete_event for window
	g_signal_connect(G_OBJECT(window), "delete_event", G_CALLBACK(delete_event), NULL);

	//show open dialog when open clicked
	g_signal_connect(open, "clicked", G_CALLBACK(on_open_image), imagecont);
	//signal to handle destroy event
	//signal to handle button click
	//g_signal_connect(G_OBJECT(button), "clicked",G_CALLBACK(hello), NULL);
	//signal to destroy window when button clicked
	//useful when trying to hide other widget in button
	//g_signal_connect_swapped(G_OBJECT(button), "clicked", G_CALLBACK(gtk_widget_destroy), G_OBJECT(window));

	//show widgets
	gtk_widget_show_all(window);

	gtk_main();
	return 0;
}