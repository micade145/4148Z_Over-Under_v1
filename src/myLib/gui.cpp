#include "myLib_h/gui.h"


void initGUI() {
    // **** Create tabs **** //
    lv_obj_t * tabview;
    tabview = lv_tabview_create(lv_scr_act(), NULL);

    lv_obj_t * autoSelectorTab = lv_tabview_add_tab(tabview, "AUTOSELECTOR");
    lv_obj_t * infoTab = lv_tabview_add_tab(tabview, "INFO");

    // **** Theme **** //
	// lv_theme_t *th = lv_theme_alien_init(360, NULL); //Set a HUE value and keep font default RED
	lv_theme_set_current(lv_theme_alien_init(349.5, NULL));

    // **** Add buttons **** //
    lv_obj_t * autonButton;

}

