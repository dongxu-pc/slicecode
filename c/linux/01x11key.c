/*************************************************************************
	> File Name: 01x11key.c
	> Author: dong xu
	> Mail: gwmxyd@163.com 
	> Created Time: 2016年04月17日 星期日 21时46分59秒
 ************************************************************************/

#include<stdio.h>
#include <gtk/gtk.h>
#include <gdk/gdkkeysyms.h>
#include <fakekey/fakekey.h>
#include <X11/keysym.h>


Display* disp ;
FakeKey *fk;

static char *keyboard_display[] = 
{
    "A\0", "B\0", "C\0", "D\0", "E\0", "F\0", "G\0"
};

static gushort keyboard_send[] = 
{
    XK_A, XK_B, XK_C, XK_D, XK_E, XK_F, XK_G
};

void da_call (GtkDialog *dialog, gint response_id, gpointer user_data) 
{
    if (GTK_RESPONSE_OK == response_id)
        g_print("OK_Pressed");
    else if (GTK_RESPONSE_CANCEL == response_id)
        g_print("CANCEL_Pressed");
}

gboolean bt_release (GtkWidget *widget, GdkEventButton *event,
        gpointer user_data) 
{
    gint i = GPOINTER_TO_UINT(user_data);
    fakekey_press_keysym(fk, keyboard_send[i], 0);
    fakekey_release(fk);

    return TRUE;
}

void clicked_callback(GtkButton *button, GtkWindow *window) {
    gint i, j;
    GtkWidget *button1;
    GtkWidget *win = gtk_window_new (GTK_WINDOW_POPUP);

    GtkWidget *vbox = gtk_vbox_new(FALSE, 5);
    GtkWidget *hbox;

    for ( i = 0 ; i < 7; i++) 
    {
        hbox = gtk_hbox_new(FALSE, 5);
        for (j = 0 ; j < 7; j++ ) {
            button1 = gtk_button_new_with_label (keyboard_display[j]);
            gtk_box_pack_start_defaults(GTK_BOX(hbox), button1);
            g_signal_connect(G_OBJECT(button1), "button-release-event",
                    G_CALLBACK(bt_release), GUINT_TO_POINTER (j));
        }
        gtk_box_pack_start_defaults(GTK_BOX(vbox), hbox);
    }

    gtk_container_add(GTK_CONTAINER(win), vbox);

    gtk_window_move (GTK_WINDOW (win), 200, 200); /* 设置窗口位置 */
    gtk_widget_show_all(win);
}

int main(int argc, char *argv[]) 
{
    GtkWidget *window;
    GtkWidget *button;
    GtkWidget *entry;
    GtkWidget *vbox;

    gtk_init(&argc, &argv);
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "GtkDialog");

    disp = XOpenDisplay(NULL);
    if( disp == NULL )
        return 1;
    fk = fakekey_init(disp);

    vbox = gtk_vbox_new(FALSE, 5);
    button = gtk_button_new_with_label("按我");

    gtk_container_add(GTK_CONTAINER(window), vbox);
    gtk_box_pack_start_defaults(GTK_BOX(vbox), button);

    entry = gtk_entry_new();
    gtk_box_pack_start_defaults(GTK_BOX(vbox), entry);

    g_signal_connect(GTK_OBJECT(window), "destroy",
            G_CALLBACK(gtk_main_quit), NULL);
    g_signal_connect(GTK_OBJECT(button), "clicked",
            G_CALLBACK(clicked_callback), window);

    gtk_widget_show_all(window);

    gtk_main();

    return 0;
}
