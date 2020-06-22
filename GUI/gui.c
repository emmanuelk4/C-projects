//gcc gui.c -o gui.o `pkg-config --cflags --libs gtk+-3.0`
#include <gtk/gtk.h>
#include "splashScreen.h"
#include <stdio.h>
#include <stdlib.h>	
#include <cairo.h>
#include <errno.h>

//function prototypes
static void do_drawing(cairo_t *);
static gboolean on_draw_event(GtkWidget *widget, cairo_t *cr, gpointer user_data);
static void do_drawing(cairo_t *cr);
static gboolean clicked(GtkWidget *widget, GdkEventButton *event, gpointer user_data);
static gboolean on_window_draw (GtkWidget *widget, GdkEventExpose *event, gpointer data);
static void on_open_image(GtkButton *button, gpointer user_data);
gint delete_event(GtkWidget *widget, GdkEvent *event, gpointer data);
//end of function prototypes


/* Global variables for storing mouse coordinates,
* count is index of arrays, coordx and coordy are x and y coordinates of the mouse
*/
struct {
	int count;
	double coordx[100];
	double coordy[100];
} glob;

/* Function: do_drawing
*Parameters: cairo_t
*Use: It sets cairo canvas settings, and draws shapes with a for loop
*Settings: are commented
*Note: printf is used during debugging to find mouse click coordinates :)
*/
static void do_drawing(cairo_t *cr)
{
  cairo_set_source_rgb(cr, 0, 0, 0);//Line colour
  cairo_set_line_width(cr, 0.5);//Line width
  cairo_translate(cr, -170, -170);//Shift where line is seen

  //i is starting point, i+1 is next mouse coordinate 
  int i;
  for (i = 0; i < glob.count - 1; i++ ) {
  	cairo_move_to(cr, glob.coordx[i], glob.coordy[i]);
  	cairo_line_to(cr, glob.coordx[i+1], glob.coordy[i+1]);
  	printf("from x:%f, y:%f\t to: x:%f, y:%f\n",glob.coordx[i],glob.coordy[i], glob.coordx[i+1], glob.coordy[i+1]);
  	cairo_stroke(cr);    
  }
  //resets array so shape can be drawn again
  //glob.count = 0;
}


static gboolean on_window_draw (GtkWidget *widget, GdkEventExpose *event, gpointer data)
{

	GdkWindow *window = gtk_widget_get_window(widget);
	cairo_region_t *cairo_region = cairo_region_create();
	GdkDrawingContext *drawing_context = gdk_window_begin_draw_frame(window, cairo_region);

	cairo_t *cr;
	cr = gdk_drawing_context_get_cairo_context(drawing_context);

	do_drawing(cr);
       // say: "I'm finished drawing
	gdk_window_end_draw_frame(window,drawing_context);


	cairo_region_destroy (cairo_region);
    //    return FALSE;
}

static gboolean clicked(GtkWidget *widget, GdkEventButton *event,
	gpointer user_data)
{
	if (event->button == 1) {
		glob.coordx[glob.count] = event->x;
		glob.coordy[glob.count++] = event->y;
	}
	if (event->button == 3) {
		gtk_widget_queue_draw(widget);
	}

	return TRUE;
}
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
	GtkWidget *canvas;
	GtkDrawingArea *drawing_area;

	//Initalize GTK window
	glob.count = 0;
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