#include "myLib_h/gui.h"

bool displayInfo = false;
int autoToRun = 1;

lv_res_t act1(lv_obj_t *btnm, const char *txt){
	//printf("red button: %s released\n", txt);
    // if(strcmp(txt, btnmMap[i]) == 0){
    autoToRun = 1;
    pros::screen::erase_line(0, 7, 600, 8);
    pros::screen::print(TEXT_MEDIUM_CENTER, 7, "AUTO TO RUN %d: %s", autoToRun, "DEFENSE SOLO");
	return LV_RES_OK; // return OK because the button matrix is not deleted
}
lv_res_t act2(lv_obj_t *btnm, const char *txt){
    autoToRun = 2;
    pros::screen::erase_line(0, 7, 600, 8);
    pros::screen::print(TEXT_MEDIUM_CENTER, 7, "AUTO TO RUN %d: %s", autoToRun, "DEFENSE ELIMS");
	return LV_RES_OK; // return OK because the button matrix is not deleted
}
lv_res_t act3(lv_obj_t *btnm, const char *txt){
    autoToRun = 3;
    pros::screen::erase_line(0, 7, 600, 8);
    pros::screen::print(TEXT_MEDIUM_CENTER, 7, "AUTO TO RUN %d: %s", autoToRun, "FOUR BALL");
	return LV_RES_OK; // return OK because the button matrix is not deleted
}
lv_res_t act4(lv_obj_t *btnm, const char *txt){
    autoToRun = 4;
    pros::screen::erase_line(0, 7, 600, 8);
    pros::screen::print(TEXT_MEDIUM_CENTER, 7, "AUTO TO RUN %d: %s", autoToRun, "PROG SKILLS");
	return LV_RES_OK; // return OK because the button matrix is not deleted
}

lv_res_t act5(lv_obj_t *btnm, const char *txt){
    autoToRun = 5;
    pros::screen::erase_line(0, 7, 600, 8);
    pros::screen::print(TEXT_MEDIUM_CENTER, 7, "AUTO TO RUN %d: %s", autoToRun, "DEFENSE 3 BALL");
	return LV_RES_OK; // return OK because the button matrix is not deleted
}
lv_res_t act6(lv_obj_t *btnm, const char *txt){
    autoToRun = 6;
    pros::screen::erase_line(0, 7, 600, 8);
    pros::screen::print(TEXT_MEDIUM_CENTER, 7, "AUTO TO RUN %d: %s", autoToRun, "FIVE BALL");
	return LV_RES_OK; // return OK because the button matrix is not deleted
}

void initGUI() {
    // **** Create tabs **** //
    lv_obj_t * tabview;
    tabview = lv_tabview_create(lv_scr_act(), NULL);

    lv_obj_t * autoSelectorTab = lv_tabview_add_tab(tabview, "AUTOSELECTOR");
    lv_obj_t * infoTab = lv_tabview_add_tab(tabview, "INFO");
    
    // **** Theme **** //
	// lv_theme_t *th = lv_theme_alien_init(360, NULL); //Set a HUE value and keep font default RED
	lv_theme_set_current(lv_theme_alien_init(349.5, NULL));

    // **** DISPLAY INFO **** //
    lv_obj_t * statesHeading = lv_label_create(infoTab, NULL);
    lv_obj_t * text1 = lv_label_create(infoTab, NULL);
    lv_obj_t * state1 = lv_label_create(infoTab, NULL);
    lv_obj_t * text2 = lv_label_create(infoTab, NULL);
    lv_obj_t * state2 = lv_label_create(infoTab, NULL);
    lv_obj_t * text3 = lv_label_create(infoTab, NULL);
    lv_obj_t * state3 = lv_label_create(infoTab, NULL);
    lv_obj_t * text4 = lv_label_create(infoTab, NULL);
    lv_obj_t * state4 = lv_label_create(infoTab, NULL);
    // lv_obj_t * odom1 = lv_label_create(infoTab, NULL);

    // **** AUTO buttons **** //
    lv_obj_t * defenseSoloBtn;
    lv_obj_t * defenseElimsBtn;
    lv_obj_t * offenseSafeBtn;
    lv_obj_t * offenseRiskyBtn;
    lv_obj_t * sixBallBtn;
    lv_obj_t * progSkillsBtn;

    defenseSoloBtn = lv_btn_create(autoSelectorTab, NULL);
    defenseElimsBtn = lv_btn_create(autoSelectorTab, NULL);
    offenseSafeBtn = lv_btn_create(autoSelectorTab, NULL);
    offenseRiskyBtn = lv_btn_create(autoSelectorTab, NULL);
    sixBallBtn = lv_btn_create(autoSelectorTab, NULL);
    progSkillsBtn = lv_btn_create(autoSelectorTab, NULL);

    lv_obj_set_size(defenseSoloBtn, 100, 50);
    lv_obj_set_size(defenseElimsBtn, 100, 50);
    lv_obj_set_size(offenseSafeBtn, 100, 50);
    lv_obj_set_size(offenseRiskyBtn, 100, 50);
    lv_obj_set_size(sixBallBtn, 100, 50);
    lv_obj_set_size(progSkillsBtn, 100, 50);

	lv_obj_set_pos(defenseSoloBtn, 0, 100);
    lv_obj_set_pos(defenseElimsBtn, 175, 100);
    lv_obj_set_pos(offenseSafeBtn, 350, 100);
    lv_obj_set_pos(offenseRiskyBtn, 0, 200);
    lv_obj_set_pos(sixBallBtn, 175, 200);
    lv_obj_set_pos(progSkillsBtn, 350, 200);

    while(true) {
        // Display heading
    lv_obj_align(statesHeading, infoTab, LV_ALIGN_IN_TOP_MID, -50, -10);
    lv_label_set_text(statesHeading, "ROBOT STATES");

        // Display robot states
    lv_obj_align(text1, infoTab, LV_ALIGN_IN_TOP_LEFT, 10, 0);
    lv_label_set_text(text1, "DRIVE: ");
    lv_obj_align(state1, text1, LV_ALIGN_OUT_RIGHT_TOP, 10, 0);

    lv_obj_align(text2, infoTab, LV_ALIGN_IN_TOP_LEFT, 10, 20);
    lv_label_set_text(text2, "PUNCHER: ");
    lv_obj_align(state2, text2, LV_ALIGN_OUT_RIGHT_TOP, 10, 0);

    lv_obj_align(text3, infoTab, LV_ALIGN_IN_TOP_LEFT, 10, 40);
    lv_label_set_text(text3, "PULLBACK: ");
    lv_obj_align(state3, text3, LV_ALIGN_OUT_RIGHT_TOP, 10, 0);

    lv_obj_align(text4, infoTab, LV_ALIGN_IN_TOP_LEFT, 10, 60);
    lv_label_set_text(text4, "ANGLE: ");
    lv_obj_align(state4, text4, LV_ALIGN_OUT_RIGHT_TOP, 10, 0);

    // lv_label_set_text(state1, states.driveStateString[states.driveState]);
    // lv_label_set_text(state2, states.puncherStateString[states.puncherState]);
    // lv_label_set_text(state3, states.puncherStateString[punchPullback]);
    // lv_label_set_text(state4, states.angleStateString[states.puncherAngleState]);
    // lv_label_set_text(statesText2, states.driveStateString[states.driveState]);

    // lv_label_set_text(statesText1, ("DRIVE STATE:   %s \n"
    //                                 "PUNCHER STATE: %s \n"
    //                                 "PULLBACK:      %d \n"
    //                                 "ANGLE STATE:   %s \n",
    //                                 states.driveStateString[states.driveState], 
    //                                 states.puncherStateString[states.puncherState], 
    //                                 punchPullback, 
    //                                 states.angleStateString[states.puncherAngleState]));

    //     // Display second half of robot states
    // lv_obj_align(statesText2, NULL, LV_ALIGN_OUT_RIGHT_TOP, 0, 0);
    // lv_label_set_text(statesText2, ("INTAKE STATE:  %s \n"
    //                                 "WINGS STATE:   %s \n"
    //                                 "BRAKE STATE:   %s \n",
    //                                 globalPose.x, globalPose.y, globalPose.theta, 
    //                                 states.driveStateString[states.driveState], 
    //                                 states.intakeStateString[states.intakeState],
    //                                 states.puncherStateString[states.puncherState], 
    //                                 punchPullback, 
    //                                 states.angleStateString[states.puncherAngleState],
    //                                 states.wingStateString[states.wingState],
    //                                 states.parkingBrakeStateString[states.parkingBrakeState]));

    //     // Display odom information
    // lv_obj_align(odomText, NULL, LV_ALIGN_IN_BOTTOM_MID, 0, 0);
    // lv_label_set_text(odomText, ("ROBOT POSITION:    X: %3.2f,    Y: %3.2f,    Theta: %3.2f \n" "%s",
    //                         globalPose.x, globalPose.y, globalPose.theta, ""));

    lv_btnm_set_action(defenseSoloBtn, act1);
    lv_btnm_set_action(defenseElimsBtn, act2);
    lv_btnm_set_action(offenseSafeBtn, act3);
    lv_btnm_set_action(offenseRiskyBtn, act4);
    lv_btnm_set_action(sixBallBtn, act5);
    lv_btnm_set_action(progSkillsBtn, act6);

	// lv_obj_align(defenseSoloBtn, NULL, LV_ALIGN_CENTER, 0, 0);
    // lv_obj_align(defenseElimsBtn, NULL, LV_ALIGN_CENTER, 0, 0);
    // while() {
    //     lv_label_set_text(t1, states.driveStateString[states.driveState]);
    //     lv_label_set_text(t2, states.puncherStateString[states.puncherState]);
    //     lv_label_set_text(t3, states.puncherStateString[punchPullback]);
    // }
    pros::delay(20);
    }
}
