// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

#include "bcat.h"
#if defined(OLED_ENABLE)
#include "bcat_oled.h"
#endif

#define _MAIN 0
#define _FN 1
#define _TG 2

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * ┌───┬───┬───┐
     * │ A │ B │ C │
     * ├───┼───┼───┤
     * │ D │ E │ F │
     * └───┴───┴───┘
     *
     * [0] = LAYOUT_ortho_2x3(
     *     KC_A,    KC_B,    KC_C,
     *     KC_D,    KC_E,    KC_F
     * )
     */

    /*
     * ┌───┬───┬───┐
     * │ Q │ W │ E │
     * ├───┼───┼───┤
     * │CTL│SPC│MO1│
     * └───┴───┴───┘
     */
    [_MAIN] = LAYOUT_ortho_2x3(
        KC_MPRV,   KC_MNXT,  KC_MUTE,
        KC_MPLY,   KC_PSCR,  MO(1)
    ),
    /*
     * ┌───┬───┬───┐
     * │ ^ │VL+│TG2│
     * ├───┼───┼───┤
     * │ ^ │ ^ │ ^ │
     * └───┴───┴───┘
     */
    [_FN] = LAYOUT_ortho_2x3(
        KC_LCTL,   KC_SPC,    KC_TRNS,
        KC_TRNS,   TG(2),     MO(1)
    ),
    /*
     * ┌───┬───┬───┐
     * │MPL│ ^ │ ^ │
     * ├───┼───┼───┤
     * │MPR│VL-│ ^ │
     * └───┴───┴───┘
     */
    [_TG] = LAYOUT_ortho_2x3(
        KC_TRNS,   KC_TRNS,   KC_TRNS,
        QK_BOOT,   TG(2),     MO(1)
    )
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [_MAIN] =  { ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [_FN] =    { ENCODER_CCW_CW(KC_TRNS, KC_TRNS)},
    [_TG] =    { ENCODER_CCW_CW(KC_BRID, KC_BRIU)}
};
#endif

#if defined(OLED_ENABLE)
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return OLED_ROTATION_90;
}

void oled_task_keymap(const oled_keyboard_state_t *keyboard_state) {
    render_oled_layers();
    oled_advance_page(/*clearPageRemainder=*/false);
    render_oled_indicators(keyboard_state->leds);
    oled_advance_page(/*clearPageRemainder=*/false);
    oled_advance_page(/*clearPageRemainder=*/false);
    render_oled_wpm(keyboard_state->wpm);
    render_oled_pet(/*col=*/0, /*line=*/12, keyboard_state);
}
#endif
