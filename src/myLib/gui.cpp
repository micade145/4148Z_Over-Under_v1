#include "myLib_h/gui.h"


void initDisplayGUI() {
    // **** Create tabs **** //
    lv_obj_t * tabview;
    tabview = lv_tabview_create(lv_scr_act(), NULL);

    lv_obj_t * autoSelectorTab = lv_tabview_add_tab(tabview, "AUTOSELECTOR");
    lv_obj_t * infoTab = lv_tabview_add_tab(tabview, "INFO");

    // **** Add buttons **** //
    
}