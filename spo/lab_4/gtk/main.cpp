#include "../db.h"

#include <gtk/gtk.h>
#include <string>
#include <vector>
#include <iostream>

struct ListWidgetItem 
{
    std::string text_1;
    std::string text_2;
    std::string text_3;
    std::string text_4;
};

static GtkWidget *window;
static GtkWidget *main_grid;
static GtkWidget *buttons_widget;
static GtkWidget *list_widget;
static GtkWidget *check_box;
static std::vector<GtkWidget *> list_items;
static unsigned int list_size = 0;

void set_font_size(GtkWidget* widget, int font_size) 
{
    char css[100];
    snprintf(css, sizeof(css), "* { font-size: %dpx; }", font_size);
    
    GtkCssProvider *provider = gtk_css_provider_new();
    gtk_css_provider_load_from_data(provider, css, -1, NULL);
    
    GtkStyleContext *context = gtk_widget_get_style_context(widget);
    gtk_style_context_add_provider(context, GTK_STYLE_PROVIDER(provider), 
                                  GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
    g_object_unref(provider);
}

void set_widget_background(GtkWidget* widget, double r, double g, double b) 
{
    char css[100];
    snprintf(css, sizeof(css), 
             "* { background-color: rgba(%d, %d, %d, 1.0); }", 
             (int)(r * 255), (int)(g * 255), (int)(b * 255));
    
    GtkCssProvider *provider = gtk_css_provider_new();
    gtk_css_provider_load_from_data(provider, css, -1, NULL);
    
    GtkStyleContext *context = gtk_widget_get_style_context(widget);
    gtk_style_context_add_provider(context, GTK_STYLE_PROVIDER(provider), 
                                  GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

    g_object_unref(provider);
}

void clear_list(GtkWidget* parent) 
{
    GList *children, *iter;
    children = gtk_container_get_children(GTK_CONTAINER(parent));
    
    for(iter = children; iter != NULL; iter = g_list_next(iter)) 
    {
        GtkWidget *widget = GTK_WIDGET(iter->data);
        gtk_container_remove(GTK_CONTAINER(parent), widget);
    }
    
    g_list_free(children);
    
    list_items.clear();
    list_size = 0;
}

void add_item_to_list(GtkWidget* parent, ListWidgetItem list_data) 
{
    GtkWidget *item = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_widget_set_size_request(item, 1185, 50);
    
    GtkWidget *text_1 = gtk_label_new(list_data.text_1.c_str());
    gtk_widget_set_size_request(text_1, 100, 50);
    gtk_label_set_xalign(GTK_LABEL(text_1), 0.5);
    gtk_label_set_yalign(GTK_LABEL(text_1), 0.5);
    set_font_size(text_1, 15);
    
    GtkWidget *text_2 = gtk_label_new(list_data.text_2.c_str());
    gtk_widget_set_size_request(text_2, 501, 50);
    gtk_label_set_xalign(GTK_LABEL(text_2), 0.1);
    gtk_label_set_yalign(GTK_LABEL(text_2), 0.5);
    set_font_size(text_2, 15);
    
    GtkWidget *text_3 = gtk_label_new(list_data.text_3.c_str());
    gtk_widget_set_size_request(text_3, 292, 50);
    gtk_label_set_xalign(GTK_LABEL(text_3), 0.1);
    gtk_label_set_yalign(GTK_LABEL(text_3), 0.5);
    set_font_size(text_3, 15);
    
    GtkWidget *text_4 = gtk_label_new(list_data.text_4.c_str());
    gtk_widget_set_size_request(text_4, 292, 50);
    gtk_label_set_xalign(GTK_LABEL(text_4), 0.1);
    gtk_label_set_yalign(GTK_LABEL(text_4), 0.5);
    set_font_size(text_4, 15);
    
    gtk_box_pack_start(GTK_BOX(item), text_1, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(item), text_2, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(item), text_3, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(item), text_4, FALSE, FALSE, 0);
    
    GtkWidget *frame = gtk_frame_new(NULL);
    gtk_frame_set_shadow_type(GTK_FRAME(frame), GTK_SHADOW_ETCHED_IN);
    gtk_container_add(GTK_CONTAINER(frame), item);
    gtk_container_add(GTK_CONTAINER(parent), frame);
    
    list_items.push_back(frame);
    list_size++;
}

static void on_information_clicked(GtkWidget* widget, gpointer data) 
{
    GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(window),
                                              GTK_DIALOG_DESTROY_WITH_PARENT,
                                              GTK_MESSAGE_INFO,
                                              GTK_BUTTONS_OK,
                                              "Лабораторная работа 4\n---> Разработка кроссплатформенных программ\n---> Выполнил: Гаджибеков Б.Г\n---> Группа: 601-21");

    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
}

static void on_exit_clicked(GtkWidget* widget, gpointer data) 
{
    gtk_main_quit();
}

static void on_check_box_toggled(GtkWidget* widget, gpointer data) 
{
    clear_list(list_widget);
    add_item_to_list(list_widget, {"№", "Название", "Цена", "Наличие"});

    std::vector<table_element> table;

    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(widget)))    table = get_visible_products_table();
    else                                                            table = get_products_table();
    
    for (auto i : table)
    {
        add_item_to_list(list_widget, {i.id, i.name, i.price, i.availability});
    }
    
    gtk_widget_queue_draw(list_widget);
    gtk_widget_show_all(list_widget);
}

static void on_window_closed(GtkWidget* widget, gpointer data) 
{
    gtk_main_quit();
}

int main(int argc, char** argv) 
{
    gtk_init(&argc, &argv);
    
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "lab04 by GTK+3");
    gtk_window_set_default_size(GTK_WINDOW(window), 1600, 1000);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    
    main_grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(window), main_grid);
    gtk_grid_set_column_spacing(GTK_GRID(main_grid), 10);
    gtk_grid_set_row_spacing(GTK_GRID(main_grid), 10);
    gtk_container_set_border_width(GTK_CONTAINER(main_grid), 5);
    
    GtkWidget *scrolled_buttons = gtk_scrolled_window_new(NULL, NULL);
    gtk_widget_set_size_request(scrolled_buttons, 792, 990);
    buttons_widget = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_container_add(GTK_CONTAINER(scrolled_buttons), buttons_widget);
    set_widget_background(buttons_widget, 0.5, 0.5, 0.5);
    
    GtkWidget *scrolled_list = gtk_scrolled_window_new(NULL, NULL);
    gtk_widget_set_size_request(scrolled_list, 1185, 990);
    list_widget = gtk_box_new(GTK_ORIENTATION_VERTICAL, 2);
    gtk_container_add(GTK_CONTAINER(scrolled_list), list_widget);
    set_widget_background(list_widget, 0.5, 0.5, 0.5);
    
    gtk_grid_attach(GTK_GRID(main_grid), scrolled_buttons, 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(main_grid), scrolled_list, 1, 0, 1, 1);
    
    GtkWidget *information = gtk_button_new_with_label("О программе");
    set_font_size(information, 15);
    g_signal_connect(information, "clicked", G_CALLBACK(on_information_clicked), NULL);
    
    GtkWidget *exit_btn = gtk_button_new_with_label("Выход");
    set_font_size(exit_btn, 15);
    g_signal_connect(exit_btn, "clicked", G_CALLBACK(on_exit_clicked), NULL);
    
    check_box = gtk_check_button_new_with_label("Скрытые");
    set_font_size(check_box, 15);
    g_signal_connect(check_box, "toggled", G_CALLBACK(on_check_box_toggled), NULL);
    
    gtk_box_pack_start(GTK_BOX(buttons_widget), gtk_label_new(""), TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(buttons_widget), check_box, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(buttons_widget), information, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(buttons_widget), exit_btn, FALSE, FALSE, 0);

    std::vector<table_element> table = get_products_table();

    add_item_to_list(list_widget, {"№", "Название", "Цена", "Наличие"});
    for (auto i : table)
    {
        add_item_to_list(list_widget, {i.id, i.name, i.price, i.availability});
    }
    
    g_signal_connect(window, "destroy", G_CALLBACK(on_window_closed), NULL);
    
    gtk_widget_show_all(window);
    
    gtk_main();
    
    return 0;
}