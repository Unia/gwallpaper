/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * callbacks.c
 * Copyright (C) 2013 Jente Hidskes <jthidskes@outlook.com>
 *
 * Phosphorus is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Phosphorus is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <gtk/gtk.h>
#include <glib/gi18n.h>
#include <glib/gprintf.h>

#include "phosphorus.h"
#include "background.h"

void on_apply_button_clicked (GtkButton *button, gpointer user_data) {
	GtkTreeIter iter;
	GtkTreePath *path;
	GtkTreeModel *model;

	cfg.config_changed = 1;
	model = gtk_icon_view_get_model (GTK_ICON_VIEW (icon_view));
	path = gtk_tree_model_get_path (model, &iter); //FIXME: fails
	if (!gtk_tree_model_get_iter (model, &iter, path)) {
		g_fprintf (stderr, "Error: can not determine activated wallpaper (from apply button).\n");
		return;
	}
	gtk_tree_path_free (path);
	gtk_tree_model_get (model, &iter, 1, &cfg.set_wp, -1);

	set_background ();
}

void on_combo_changed (GtkComboBox *combo, gpointer user_data) {
	cfg.config_changed = 1;
	cfg.wp_mode = gtk_combo_box_get_active (combo);
}

void on_item_activated (GtkIconView *view, GtkTreePath *path, gpointer user_data) {
	GtkTreeModel *model;
	GtkTreeIter iter;

	cfg.config_changed = 1;
	model = gtk_icon_view_get_model (GTK_ICON_VIEW (icon_view));
	if (!gtk_tree_model_get_iter (model, &iter, path)) {
		g_fprintf (stderr, "Error: can not determine activated wallpaper (from item activated).\n");
		return;
	}
	gtk_tree_model_get (model, &iter, 1, &cfg.set_wp, -1);

	set_background ();
}

void on_color_button_clicked (GtkColorButton *button, gpointer user_data) {
	cfg.config_changed = 1;
	gtk_color_chooser_get_rgba (GTK_COLOR_CHOOSER (button), &cfg.bg_color);
}