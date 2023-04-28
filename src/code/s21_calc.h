#ifndef SRC_S21_CALC_H_
#define SRC_S21_CALC_H_

#include <cairo.h>
#include <gdk/gdk.h>
#include <gtk/gtk.h>
#include <locale.h>
#include <math.h>
#include <string.h>

#include "rpn.h"

static void add_to_buffer(GtkWidget *widget);

static void change_buttons(GtkWidget *widget);

static void main_window(GtkApplication *app);

static void calculate_this_sh(GtkWidget *widget);

static void draw_graph(GtkWidget *widget);

static void limits_window(GtkWidget *widget);

void draw_function(GtkDrawingArea *area, cairo_t *cr, int width, int height,
                   gpointer data);

static void place_button_on_grid(GtkWidget *grid, int x, int y, int width,
                                 int height, char *text, GCallback func,
                                 int mode);

static void calculator_window_buttons(GtkWidget *grid, int button_width,
                                      int button_height);

static void place_entry_on_grid(GtkWidget *grid, int x, int y, int width,
                                int height, int alignment, int buff_size,
                                int set_size, gint x_size, gint y_size,
                                const char *placeholder, gboolean editable);

static void place_label_on_grid(GtkWidget *grid, int x, int y, int width,
                                int height, gint x_size, gint y_size,
                                const char *text);

char *get_chars_from_entry(GtkWidget *grid, int x, int y);

static void add_chars_to_buffer(GtkWidget *entry, char *chars, gboolean status);

void line_graph(cairo_t *cr, char *expr, int width, int height,
                long double borders, long double x_min, long double x_max,
                long double y_min, long double y_max, double cl_r, double cl_g,
                double cl_b, double l_width);

static void line_draw(cairo_t *cr, long double x1, long double y1,
                      long double x2, long double y2, double col_r,
                      double col_g, double col_b, double width, int mode);

char *text_from_label(GtkWidget *grid, int x, int y);

long double ld_from_label(GtkWidget *grid, int x, int y);

long double pix_step(long double min, long double max);

void line_ox_oy(cairo_t *cr, int width, long double x_max, long double y_max,
                long double x_min, long double y_min, int height, int borders);

#endif  // SRC_S21_CALC_H_