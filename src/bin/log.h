#include <glib.h>

void log_install_backtrace_printer();
void log_set_level(const gchar *level);
void log_handler(const gchar *log_domain, GLogLevelFlags log_level, const gchar *message, gpointer user_data);
