#include "functions.h"
/* count1al variables for storing mouse coordinates,
* count is index of arrays, coordx and coordy are x and y coordinates of the mouse
*/

struct counter count1;

/* Function: do_drawing
*Parameters: cairo_t
*Use: It sets cairo canvas settings, and draws shapes with a for loop
*Settings: are commented
*Note: printf is used during debugging to find mouse click coordinates :)
*/
void do_drawing(cairo_t *cr)
{
  cairo_set_source_rgb(cr, 0, 0, 0);//Line colour
  cairo_set_line_width(cr, 0.5);//Line width
  cairo_translate(cr, -170, -170);//Shift where line is seen

  //i is starting point, i+1 is next mouse coordinate 
  int i;
  for (i = 0; i < count1.count - 1; i++ ) {
  	cairo_move_to(cr, count1.coordx[i], count1.coordy[i]);
  	cairo_line_to(cr, count1.coordx[i+1], count1.coordy[i+1]);
  	printf("from x:%f, y:%f\t to: x:%f, y:%f\n",count1.coordx[i],count1.coordy[i], count1.coordx[i+1], count1.coordy[i+1]);
  	cairo_stroke(cr);    
  }
  //resets array so shape can be drawn again
  count1.count = 0;
}


gboolean on_window_draw (GtkWidget *widget, GdkEventExpose *event, gpointer data)
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

gboolean clicked(GtkWidget *widget, GdkEventButton *event,
	gpointer user_data)
{
	if (event->button == 1) {
		count1.coordx[count1.count] = event->x;
		count1.coordy[count1.count++] = event->y;
	}
	if (event->button == 3) {
		gtk_widget_queue_draw(widget);

	}

	return TRUE;
}
void on_open_image(GtkButton *button, gpointer user_data)
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