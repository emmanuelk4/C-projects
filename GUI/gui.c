//gcc gui.c splashScreen.c functions.c-o gui.o `pkg-config --cflags --libs gtk+-3.0`

#include "splashScreen.h"
#include "functions.h"

int main (int argc, char *argv[] ) 
{
	//VAriable  declarations for ui features
	GtkWidget *window;
	GtkWidget *open, *edit, *image, *process, *analyze;
	GtkWidget *rectangle, *circle, *polygon, *hand, *zoom;
	GtkWidget *grid;
	GtkWidget *imagecont;
	GtkWidget *box;
	GtkWidget *canvas;
	GtkDrawingArea *drawing_area;
	struct counter count1;

	//Initalize GTK window
	count1.count = 0;
	gtk_init(&argc, &argv);
	

	if(showSplash("image.jpeg", 1000, 700, 700) != 0) {
		fprintf(stderr, "%d\n", errno);
	}

	//create new ui features
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	box = gtk_box_new(GTK_ORIENTATION_VERTICAL,5);
	imagecont = gtk_image_new();
	drawing_area =(GtkDrawingArea*) gtk_drawing_area_new();
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
	gtk_grid_attach(GTK_GRID(grid), (GtkWidget*)drawing_area, 1,2,1,1);

	
	
	//box
	gtk_widget_add_events(window, GDK_BUTTON_PRESS_MASK);

	//set window title
	gtk_window_set_title(GTK_WINDOW(window), "KIBICHO is BAE");
	//set window size
	gtk_window_set_default_size(GTK_WINDOW(window), 600,600);
	gtk_window_set_resizable(GTK_WINDOW(window), FALSE);
	//Set window width
	gtk_container_set_border_width(GTK_CONTAINER(window), 10);
	//add button to window container
	gtk_container_add(GTK_CONTAINER(window), grid);

	//Main signal to handle delete_event for window
	g_signal_connect(G_OBJECT(window), "delete_event", G_CALLBACK(delete_event), NULL);
//show open dialog when open clicked
	g_signal_connect(open, "clicked", G_CALLBACK(on_open_image), imagecont);
	//create drawing area
	g_signal_connect(drawing_area, "draw", G_CALLBACK(on_window_draw), NULL);
	g_signal_connect(window, "button-press-event", G_CALLBACK(clicked), NULL);
	//
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