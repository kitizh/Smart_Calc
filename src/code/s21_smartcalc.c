#include "s21_calc.h"

int main(int argc, char **argv) {
  GtkApplication *app;
  int status;

  app = gtk_application_new("org.gtk.example", G_APPLICATION_FLAGS_NONE);
  g_signal_connect(app, "activate", G_CALLBACK(main_window), NULL);
  status = g_application_run(G_APPLICATION(app), argc, argv);
  g_object_unref(app);

  return status;
}

static void main_window(GtkApplication *app) {
  GtkWidget *window;
  GtkWidget *grid;

  window = gtk_application_window_new(app);
  gtk_window_set_title(GTK_WINDOW(window), "SmartCalc v1.0");

  grid = gtk_grid_new();

  gtk_window_set_child(GTK_WINDOW(window), grid);

  gtk_grid_set_column_homogeneous(GTK_GRID(grid), TRUE);
  gtk_grid_set_row_homogeneous(GTK_GRID(grid), TRUE);
  gtk_grid_set_column_spacing(GTK_GRID(grid), 3);
  gtk_grid_set_row_spacing(GTK_GRID(grid), 3);

  place_entry_on_grid(grid, 0, 0, 6, 1, 1, 300, 0, 0, 0, "Entry", FALSE);
  place_entry_on_grid(grid, 1, 1, 4, 1, 0, 30, 0, 0, 0, "0.0", FALSE);
  calculator_window_buttons(grid, 100, 50);

  gtk_widget_show(window);
}

static void calculate_this_sh(GtkWidget *widget) {
  GtkWidget *grid;
  GtkWidget *entry;
  GtkWidget *entry_x;
  GtkEntryBuffer *buffer;
  GtkEntryBuffer *buffer_x;
  guint lenght;
  int n_chars = 0;
  const gchar *text;
  const gchar *text_x;
  char *e;
  long double x = 0.0;
  int ppp = 0;
  str_stack out;
  create_stack(100 * 2, 300, &out);
  char *fine_buf = calloc(300, sizeof(char));
  char *res = calloc(300, sizeof(char));
  char *fine_buf_x = calloc(300, sizeof(char));

  grid = gtk_widget_get_parent(widget);
  entry = gtk_grid_get_child_at(GTK_GRID(grid), 0, 0);
  buffer = gtk_entry_get_buffer(GTK_ENTRY(entry));
  entry_x = gtk_grid_get_child_at(GTK_GRID(grid), 1, 1);
  buffer_x = gtk_entry_get_buffer(GTK_ENTRY(entry_x));
  lenght = gtk_entry_buffer_get_length(buffer);
  text = gtk_entry_buffer_get_text(buffer);
  text_x = gtk_entry_buffer_get_text(buffer_x);
  sprintf(fine_buf_x, "%s", text_x);
  sprintf(fine_buf, "%s", text);
  setlocale(LC_ALL, "C");
  x = strtold(fine_buf_x, &e);

  ppp = rpn(fine_buf, res, &out);

  if (strcmp(res, "ERROR")) {
    calc_handler(&out, ppp, res, x);
  }

  gtk_entry_buffer_delete_text(buffer, 0, lenght);
  n_chars = strlen(res);
  gtk_entry_set_placeholder_text(GTK_ENTRY(entry), NULL);
  gtk_entry_buffer_insert_text(buffer, -1, res, n_chars);

  free(fine_buf);
  free(fine_buf_x);
  free(res);
  clean_stack(&out);
}

static void limits_window(GtkWidget *widget) {
  GtkWidget *grid;
  GtkWidget *entry_m;
  GtkEntryBuffer *buffer;
  GtkWidget *button;
  const gchar *text;
  char *fine_buf = calloc(300, sizeof(char));

  grid = gtk_widget_get_parent(widget);
  entry_m = gtk_grid_get_child_at(GTK_GRID(grid), 0, 0);
  buffer = gtk_entry_get_buffer(GTK_ENTRY(entry_m));
  text = gtk_entry_buffer_get_text(buffer);
  sprintf(fine_buf, "%s", text);

  GtkWidget *c_grid;
  GtkWidget *c_window;
  c_window = gtk_window_new();
  gtk_window_set_title(GTK_WINDOW(c_window), "limits");
  gtk_window_set_default_size(GTK_WINDOW(c_window), 500, 200);
  c_grid = gtk_grid_new();

  gtk_window_set_child(GTK_WINDOW(c_window), c_grid);

  place_label_on_grid(c_grid, 0, 0, 4, 1, 500, 50, fine_buf);
  place_label_on_grid(c_grid, 0, 1, 1, 1, 125, 50, "x_min =");
  place_label_on_grid(c_grid, 0, 2, 1, 1, 125, 50, "x_max =");
  place_label_on_grid(c_grid, 2, 1, 1, 1, 125, 50, "y_min =");
  place_label_on_grid(c_grid, 2, 2, 1, 1, 125, 50, "y_max =");
  place_entry_on_grid(c_grid, 1, 1, 1, 1, 1, 30, 1, 125, 50, "0.0", TRUE);
  place_entry_on_grid(c_grid, 1, 2, 1, 1, 1, 30, 1, 125, 50, "0.0", TRUE);
  place_entry_on_grid(c_grid, 3, 1, 1, 1, 1, 30, 1, 125, 50, "0.0", TRUE);
  place_entry_on_grid(c_grid, 3, 2, 1, 1, 1, 30, 1, 125, 50, "0.0", TRUE);
  place_button_on_grid(c_grid, 0, 8, 4, 1, "DRAW", G_CALLBACK(draw_graph), 1);

  button = gtk_grid_get_child_at(GTK_GRID(c_grid), 0, 8);
  gtk_widget_set_size_request(button, 500, 50);

  gtk_widget_show(c_window);

  free(fine_buf);
}

static void draw_graph(GtkWidget *widget) {
  GtkWidget *grid;
  GtkWidget *c_grid;
  GtkWidget *window;
  GtkWidget *drawing_area;

  grid = gtk_widget_get_parent(widget);

  const char *fine_buf = text_from_label(grid, 0, 0);
  const char *fine_buf_x_min = get_chars_from_entry(grid, 1, 1);
  const char *fine_buf_x_max = get_chars_from_entry(grid, 1, 2);
  const char *fine_buf_y_min = get_chars_from_entry(grid, 3, 1);
  const char *fine_buf_y_max = get_chars_from_entry(grid, 3, 2);

  window = gtk_window_new();
  gtk_window_set_title(GTK_WINDOW(window), "graph");
  gtk_window_set_default_size(GTK_WINDOW(window), 820, 980);  // 500 700
  c_grid = gtk_grid_new();

  gtk_window_set_child(GTK_WINDOW(window), c_grid);
  drawing_area = gtk_drawing_area_new();
  gtk_drawing_area_set_content_width(GTK_DRAWING_AREA(drawing_area), 820);
  gtk_drawing_area_set_content_height(GTK_DRAWING_AREA(drawing_area), 820);
  gtk_drawing_area_set_draw_func(GTK_DRAWING_AREA(drawing_area), draw_function,
                                 NULL, NULL);
  gtk_grid_attach(GTK_GRID(c_grid), drawing_area, 0, 1, 4, 4);

  place_label_on_grid(c_grid, 0, 0, 4, 1, 820, 50, fine_buf);
  place_label_on_grid(c_grid, 0, 6, 1, 1, 205, 50, "x_min =");
  place_label_on_grid(c_grid, 0, 7, 1, 1, 205, 50, "x_max =");
  place_label_on_grid(c_grid, 2, 6, 1, 1, 205, 50, "y_min =");
  place_label_on_grid(c_grid, 2, 7, 1, 1, 205, 50, "y_max =");
  place_label_on_grid(c_grid, 1, 6, 1, 1, 205, 50, fine_buf_x_min);
  place_label_on_grid(c_grid, 1, 7, 1, 1, 205, 50, fine_buf_x_max);
  place_label_on_grid(c_grid, 3, 6, 1, 1, 205, 50, fine_buf_y_min);
  place_label_on_grid(c_grid, 3, 7, 1, 1, 205, 50, fine_buf_y_max);

  gtk_window_present(GTK_WINDOW(window));
}

void draw_function(GtkDrawingArea *area, cairo_t *cr, int width, int height,
                   gpointer data) {
  GtkWidget *grid;
  long double borders = 90.0;
  setlocale(LC_ALL, "C");
  grid = gtk_widget_get_parent(GTK_WIDGET(area));
  char expr[300] = {0};
  sprintf(expr, "%s", text_from_label(grid, 0, 0));
  long double x_min = ld_from_label(grid, 1, 6);
  long double x_max = ld_from_label(grid, 1, 7);
  long double y_min = ld_from_label(grid, 3, 6);
  long double y_max = ld_from_label(grid, 3, 7);
  int error = 0;
  if ((y_min > y_max) || (x_min > x_max)) {
    error = 1;
  }
  if (!error) {
    line_graph(cr, expr, width, height, borders, x_min, x_max, y_min, y_max,
               179.0, 0.0, 89.0, 2.0);
    line_ox_oy(cr, width, x_max, y_max, x_min, y_min, height, borders);
    long double number_x = pix_step(x_min, y_max);
    long double number_y = pix_step(y_min, y_max);
    long double pix_gr_step_x =
        (width - borders) / ((x_max - x_min) / number_x);
    long double pix_gr_step_y =
        (width - borders) / ((y_max - y_min) / number_y);
    long double start_number_ox = ceil(y_min / number_y) * number_y;
    long double start_number_oy = ceil(x_min / number_x) * number_x;
    long double start_x =
        ((start_number_oy - x_min) / number_x) * pix_gr_step_x + borders;
    long double start_y =
        ((-start_number_ox + y_min) / number_y) * pix_gr_step_y + height -
        borders;
    long double number_for_drawing = start_number_ox;

    for (long double i = start_y; i > 0.0; i -= pix_gr_step_y) {
      line_draw(cr, borders - 8, i, width, i, 0.8, 0.8, 0.8, 0.8, 0);
      line_draw(cr, borders - 65, i + 4, number_for_drawing, 0, 0.5, 0.5, 0.5,
                0.8, 1);
      number_for_drawing += number_y;
    }
    number_for_drawing = start_number_oy;
    for (long double i = start_x; i < width; i += pix_gr_step_x) {
      line_draw(cr, i, 0, i, height - borders + 8, 0.8, 0.8, 0.8, 0.8, 0);
      line_draw(cr, i - 2, height - borders + 25, number_for_drawing, 0, 0.5,
                0.5, 0.5, 0.8, 1);
      number_for_drawing += number_x;
    }
  }
}

long double pix_step(long double min, long double max) {
  long double counter = 1;
  if ((max - min) / 10 >= 1) {
    while (1) {
      if ((max - min) / 10 >= counter) {
        counter *= 2;
      } else {
        counter /= 2;
        break;
      }
    }
  } else {
    while (1) {
      if ((max - min) / 10 < counter) {
        counter /= 2;
      } else {
        counter *= 2;
        break;
      }
    }
  }
  return counter;
}

void line_graph(cairo_t *cr, char *expr, int width, int height,
                long double borders, long double x_min, long double x_max,
                long double y_min, long double y_max, double cl_r, double cl_g,
                double cl_b, double l_width) {
  char *res = calloc(300, sizeof(char));
  long double step_x =
      (x_max - x_min) / (width - borders);  // lenght не может быть 0!
  long double step_y =
      (y_max - y_min) / (height - borders);  // сколько в одном pix
  long double res_y = 0;
  int ppp = 0;
  char *e;
  str_stack out;
  create_stack(300 * 2, 300, &out);
  ppp = rpn(expr, res, &out);
  // фон
  cairo_set_source_rgb(cr, 1.0, 1.0, 1.0);
  cairo_paint(cr);
  // рамка
  line_draw(cr, borders, height - borders, width, height - borders, 0.0, 0.0,
            0.0, 1.0, 0);
  line_draw(cr, borders, 0, borders, height - borders, 0.0, 0.0, 0.0, 1.0, 0);

  cairo_set_line_width(cr, l_width);
  cairo_set_source_rgb(cr, cl_r, cl_g, cl_b);

  int set = 0;
  for (long double i = x_min; i <= x_max; i += step_x) {
    calc_handler(&out, ppp, res, i);
    res_y = strtold(res, &e);
    if ((isnormal(res_y)) && ((y_max - res_y) / step_y < width - borders)) {
      if (!set) {
        cairo_move_to(cr, (i - x_min) / step_x + borders,
                      (y_max - res_y) / step_y);
        set = 1;
      } else {
        cairo_line_to(cr, (i - x_min) / step_x + borders,
                      (y_max - res_y) / step_y);
      }
    } else {
      set = 0;
    }
  }
  clean_stack(&out);
  cairo_stroke(cr);
  free(res);
}

static void line_draw(cairo_t *cr, long double x1, long double y1,
                      long double x2, long double y2, double col_r,
                      double col_g, double col_b, double width, int mode) {
  char char_number[40] = {0};
  cairo_set_line_width(cr, width);
  cairo_set_source_rgb(cr, col_r, col_g, col_b);
  cairo_move_to(cr, x1, y1);
  if (!mode) {
    cairo_line_to(cr, x2, y2);
  } else {
    sprintf(char_number, "%Lf", x2);
    cairo_show_text(cr, char_number);
  }
  cairo_stroke(cr);
}

static void place_button_on_grid(GtkWidget *grid, int x, int y, int width,
                                 int height, char *text, GCallback func,
                                 int mode) {
  GtkWidget *button;
  if (mode < 2) {
    button = gtk_button_new_with_label(text);
  } else {
    button = gtk_toggle_button_new_with_label(text);
  }
  if (mode == 0) {
    gtk_widget_set_sensitive(button, FALSE);
  } else if (mode != 4) {
    g_signal_connect(button, "clicked", func, NULL);
  }
  gtk_grid_attach(GTK_GRID(grid), button, x, y, width, height);
}

long double ld_from_label(GtkWidget *grid, int x, int y) {
  char *e;
  char *text = (char *)text_from_label(grid, x, y);
  long double res = strtold(text, &e);
  return res;
}

void line_ox_oy(cairo_t *cr, int width, long double x_max, long double y_max,
                long double x_min, long double y_min, int height, int borders) {
  if ((x_min < 0) && (x_max > 0)) {
    line_draw(cr, width - x_max / ((x_max - x_min) / (width - borders)), 0.0,
              width - x_max / ((x_max - x_min) / (width - borders)),
              height - borders + 8, 179.0, 0.0, 89.0, 0.8, 0);
  }

  if ((y_min < 0) && (y_max > 0)) {
    line_draw(cr, borders - 8, y_max / ((y_max - y_min) / (height - borders)),
              width, y_max / ((y_max - y_min) / (height - borders)), 179.0, 0.0,
              89.0, 0.8, 0);
  }
}

char *get_chars_from_entry(GtkWidget *grid, int x, int y) {
  GtkWidget *entry;
  GtkEntryBuffer *buffer;
  entry = gtk_grid_get_child_at(GTK_GRID(grid), x, y);
  buffer = gtk_entry_get_buffer(GTK_ENTRY(entry));
  char *text = (char *)gtk_entry_buffer_get_text(buffer);
  return (char *)text;
}

char *text_from_label(GtkWidget *grid, int x, int y) {
  GtkWidget *label;
  label = gtk_grid_get_child_at(GTK_GRID(grid), x, y);
  char *text = (char *)gtk_label_get_text(GTK_LABEL(label));
  return (char *)text;
}

static void place_label_on_grid(GtkWidget *grid, int x, int y, int width,
                                int height, gint x_size, gint y_size,
                                const char *text) {
  GtkWidget *label;

  label = gtk_label_new(text);
  gtk_grid_attach(GTK_GRID(grid), label, x, y, width, height);
  gtk_widget_set_size_request(label, x_size, y_size);
}

static void place_entry_on_grid(GtkWidget *grid, int x, int y, int width,
                                int height, int alignment, int buff_size,
                                int set_size, gint x_size, gint y_size,
                                const char *placeholder, gboolean editable) {
  GtkWidget *entry;
  GtkEntryBuffer *buffer;
  buffer = gtk_entry_buffer_new(NULL, buff_size);

  entry = gtk_entry_new_with_buffer(buffer);
  gtk_grid_attach(GTK_GRID(grid), entry, x, y, width, height);
  gtk_entry_set_alignment(GTK_ENTRY(entry), alignment);
  gtk_entry_set_placeholder_text(GTK_ENTRY(entry), placeholder);
  gtk_editable_set_editable(GTK_EDITABLE(entry), editable);
  if (set_size) {
    gtk_widget_set_size_request(entry, x_size, y_size);
  }
}

static void calculator_window_buttons(GtkWidget *grid, int button_width,
                                      int button_height) {
  GCallback add_func = G_CALLBACK(add_to_buffer);
  GtkWidget *button;

  place_button_on_grid(grid, 0, 1, 1, 1, "x=", NULL, 4);
  place_button_on_grid(grid, 5, 1, 1, 1, "<--", add_func, 1);

  place_button_on_grid(grid, 0, 2, 1, 1, "Inv", G_CALLBACK(change_buttons), 2);
  place_button_on_grid(grid, 1, 2, 1, 1, "x!", add_func, 1);
  place_button_on_grid(grid, 2, 2, 1, 1, "x", add_func, 1);
  place_button_on_grid(grid, 3, 2, 1, 1, "(", add_func, 1);
  place_button_on_grid(grid, 4, 2, 1, 1, ")", add_func, 1);
  place_button_on_grid(grid, 5, 2, 1, 1, "AC", add_func, 1);

  place_button_on_grid(grid, 0, 3, 1, 1, "e", add_func, 0);
  place_button_on_grid(grid, 1, 3, 1, 1, "x^y", add_func, 1);
  place_button_on_grid(grid, 2, 3, 1, 1, "7", add_func, 1);
  place_button_on_grid(grid, 3, 3, 1, 1, "8", add_func, 1);
  place_button_on_grid(grid, 4, 3, 1, 1, "9", add_func, 1);
  place_button_on_grid(grid, 5, 3, 1, 1, "/", add_func, 1);

  place_button_on_grid(grid, 0, 4, 1, 1, "pi", add_func, 1);
  place_button_on_grid(grid, 1, 4, 1, 1, "ln", add_func, 1);
  place_button_on_grid(grid, 2, 4, 1, 1, "4", add_func, 1);
  place_button_on_grid(grid, 3, 4, 1, 1, "5", add_func, 1);
  place_button_on_grid(grid, 4, 4, 1, 1, "6", add_func, 1);
  place_button_on_grid(grid, 5, 4, 1, 1, "*", add_func, 1);

  place_button_on_grid(grid, 0, 5, 1, 1, "cos", add_func, 1);
  place_button_on_grid(grid, 1, 5, 1, 1, "log", add_func, 1);
  place_button_on_grid(grid, 2, 5, 1, 1, "1", add_func, 1);
  place_button_on_grid(grid, 3, 5, 1, 1, "2", add_func, 1);
  place_button_on_grid(grid, 4, 5, 1, 1, "3", add_func, 1);
  place_button_on_grid(grid, 5, 5, 1, 1, "-", add_func, 1);

  place_button_on_grid(grid, 0, 6, 1, 1, "sin", add_func, 1);
  place_button_on_grid(grid, 1, 6, 1, 1, "sqrt", add_func, 1);
  place_button_on_grid(grid, 2, 6, 1, 1, "0", add_func, 1);
  place_button_on_grid(grid, 3, 6, 1, 1, ".", add_func, 1);
  place_button_on_grid(grid, 4, 6, 1, 1, "=", G_CALLBACK(calculate_this_sh), 1);
  place_button_on_grid(grid, 5, 6, 1, 1, "+", add_func, 1);

  place_button_on_grid(grid, 0, 7, 1, 1, "tan", add_func, 1);
  place_button_on_grid(grid, 1, 7, 1, 1, "mod", add_func, 1);
  place_button_on_grid(grid, 2, 7, 2, 1, "graph", G_CALLBACK(limits_window), 1);
  place_button_on_grid(grid, 4, 7, 2, 1, "cred/dep", add_func, 0);

  button = gtk_grid_get_child_at(GTK_GRID(grid), 0, 1);
  gtk_widget_set_size_request(button, button_width, button_height);
}

static void add_to_buffer(GtkWidget *widget) {
  GtkWidget *grid;
  GtkWidget *entry;
  const gchar *label;
  char chars[15] = {0};
  GtkWidget *x_button;
  gboolean status;

  grid = gtk_widget_get_parent(widget);
  x_button = gtk_grid_get_child_at(GTK_GRID(grid), 0, 1);
  status = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(x_button));

  if (status) {
    entry = gtk_grid_get_child_at(GTK_GRID(grid), 1, 1);
  } else {
    entry = gtk_grid_get_child_at(GTK_GRID(grid), 0, 0);
  }
  label = gtk_button_get_label(GTK_BUTTON(widget));

  sprintf(chars, "%s", label);
  gtk_entry_set_placeholder_text(GTK_ENTRY(entry), NULL);

  add_chars_to_buffer(entry, chars, status);
}

static void add_chars_to_buffer(GtkWidget *entry, char *chars,
                                gboolean status) {
  GtkEntryBuffer *buffer;
  gint lenght;
  int n_chars = strlen(chars);
  char new_buf[15] = {0};

  buffer = gtk_entry_get_buffer(GTK_ENTRY(entry));
  lenght = gtk_entry_buffer_get_length(buffer);

  if (n_chars == 1) {
    gtk_entry_buffer_insert_text(buffer, -1, chars, 1);

  } else if (chars[0] == 'x') {
    if (n_chars == 2) {
      gtk_entry_buffer_insert_text(buffer, -1, "!", 1);
    } else {
      gtk_entry_buffer_insert_text(buffer, -1, "^", 1);
    }
  } else if (chars[0] == 'p') {
    gtk_entry_buffer_insert_text(buffer, -1, "pi", 2);
  } else if (chars[0] == '<') {
    gtk_entry_buffer_delete_text(buffer, lenght - 1, 1);

  } else if (chars[0] == 'A') {
    gtk_entry_buffer_delete_text(buffer, 0, lenght);

    if (!status) {
      gtk_entry_set_placeholder_text(GTK_ENTRY(entry), "Entry");
    } else {
      gtk_entry_set_placeholder_text(GTK_ENTRY(entry), "0.0");
    }

  } else {
    if (strcmp(chars, "mod")) {
      sprintf(new_buf, "%s(", chars);
    } else {
      sprintf(new_buf, "%s", chars);
    }
    gtk_entry_buffer_insert_text(buffer, -1, new_buf, n_chars + 1);
  }
}

static void change_buttons(GtkWidget *widget) {
  GtkWidget *grid;
  GtkWidget *cos_button;
  GtkWidget *sin_button;
  GtkWidget *tan_button;
  gboolean status;

  grid = gtk_widget_get_parent(widget);
  status = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(widget));

  cos_button = gtk_grid_get_child_at(GTK_GRID(grid), 0, 5);
  sin_button = gtk_grid_get_child_at(GTK_GRID(grid), 0, 6);
  tan_button = gtk_grid_get_child_at(GTK_GRID(grid), 0, 7);

  if (!status) {
    gtk_button_set_label(GTK_BUTTON(cos_button), "cos");
    gtk_button_set_label(GTK_BUTTON(sin_button), "sin");
    gtk_button_set_label(GTK_BUTTON(tan_button), "tan");
  } else {
    gtk_button_set_label(GTK_BUTTON(cos_button), "acos");
    gtk_button_set_label(GTK_BUTTON(sin_button), "asin");
    gtk_button_set_label(GTK_BUTTON(tan_button), "atan");
  }
}