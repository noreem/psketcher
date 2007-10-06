/*
 * Initial main.c file generated by Glade. Edit as required.
 * Glade will not overwrite this file.
 */

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <gtk/gtk.h>
#include <glade/glade.h>

#include "Support.h"
#include "Callbacks.h"

// global
OccGtkGLView* theViewer = 0;
GdkGLConfig *glconfig = 0;

int main (int argc, char *argv[])
{
theViewer = new OccGtkGLView();

  GladeXML *MainWindowXML;
  GtkWidget *MainWindow;

#ifdef ENABLE_NLS
  bindtextdomain (GETTEXT_PACKAGE, PACKAGE_LOCALE_DIR);
  bind_textdomain_codeset (GETTEXT_PACKAGE, "UTF-8");
  textdomain (GETTEXT_PACKAGE);
#endif

  gtk_set_locale ();
  gtk_init (&argc, &argv);
  
  //gtkgl
  gtk_gl_init (&argc, &argv);

  //add_pixmap_directory (PACKAGE_DATA_DIR "/" PACKAGE "/pixmaps");
	add_pixmap_directory (PACKAGE_DATA_DIR);

  /* Try double-buffered visual */
    glconfig = gdk_gl_config_new_by_mode (GdkGLConfigMode(GDK_GL_MODE_RGB    |
		GDK_GL_MODE_DEPTH  |
		GDK_GL_MODE_DOUBLE));
    if (glconfig == NULL)
    {
	g_print ("*** Cannot find the double-buffered visual.\n");
	g_print ("*** Trying single-buffered visual.\n");

	/* Try single-buffered visual */
	glconfig = gdk_gl_config_new_by_mode (GdkGLConfigMode(GDK_GL_MODE_RGB   |
		    GDK_GL_MODE_DEPTH));
	if (glconfig == NULL)
	{
	    g_print ("*** No appropriate OpenGL-capable visual found.\n");
	    exit(-1);
	}
    }

	MainWindowXML = glade_xml_new(PACKAGE_DATA_DIR "/ark3d.glade", "MainWindow", NULL);
	if (MainWindowXML == NULL)
	{
	    g_print ("*** Failed creating main window.\n");
	    exit(-1);
	}
	
  GtkWidget* draw = glade_xml_get_widget(MainWindowXML, "drawingarea1");

	/* Set OpenGL-capability to the widget. */
    gtk_widget_set_gl_capability (draw,
	    glconfig,
	    NULL,
	    TRUE,
	    GDK_GL_RGBA_TYPE);
	
  /* connect signal handlers */
  glade_xml_signal_autoconnect(MainWindowXML);

  // show the main window
  MainWindow = glade_xml_get_widget(MainWindowXML, "MainWindow");
  gtk_widget_show (MainWindow);
	
  g_signal_connect ((gpointer) MainWindow, "destroy", G_CALLBACK(gtk_main_quit),
            NULL);
	
  gtk_main ();
  return 0;
}

