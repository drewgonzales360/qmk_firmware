/*
This is free and unencumbered software released into the public domain.

Anyone is free to copy, modify, publish, use, compile, sell, or
distribute this software, either in source code form or as a compiled
binary, for any purpose, commercial or non-commercial, and by any
means.

In jurisdictions that recognize copyright laws, the author or authors
of this software dedicate any and all copyright interest in the
software to the public domain. We make this dedication for the benefit
of the public at large and to the detriment of our heirs and
successors. We intend this dedication to be an overt act of
relinquishment in perpetuity of all present and future rights to this
software under copyright law.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
OTHER DEALINGS IN THE SOFTWARE.

For more information, please refer to <http://unlicense.org/>
*/

#include QMK_KEYBOARD_H

#define _LAYER0 0
#define _LAYER1 1
#define _LAYER2 2

enum custom_keycodes {
    LAYER0 = SAFE_RANGE,
    LAYER1,
    LAYER2,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_LAYER0] = LAYOUT(KC_GRV, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_BSPC, KC_LSFT, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_LCTL, KC_Z, KC_X, KC_C, KC_V, KC_B, TT(2), KC_NO, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_SFTENT, KC_LALT, KC_LGUI, TT(1), KC_NO, KC_SPC, KC_ESC),
    [_LAYER1] = LAYOUT(KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_PIPE, KC_PAST, KC_COLN, KC_PEQL, KC_PMNS, KC_BSLS, KC_PGUP, KC_HOME, KC_UP, KC_END, KC_LBRC, KC_RBRC, KC_CAPS, KC_LCTL, KC_LSFT, KC_LGUI, KC_LALT, KC_BSPC, KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, KC_LCBR, KC_RCBR, KC_HASH, KC_DLR, KC_AMPR, KC_PLUS, KC_UNDS, KC_AT, KC_TRNS, KC_NO, KC_NO, KC_PGUP, KC_NO, KC_PGDN, KC_LPRN, KC_RPRN, KC_NO, TO(0), KC_TRNS, KC_NO, KC_NO, KC_NO),
    [_LAYER2] = LAYOUT(KC_NO, KC_NO, KC_NO, KC_NO, BL_TOGG, BL_INC, KC_NO, KC_P7, KC_P8, KC_P9, KC_PAST, KC_PSLS, RGB_TOG, RGB_RMOD, RGB_MOD, KC_NO, BL_BRTG, BL_DEC, KC_NO, KC_P4, KC_P5, KC_P6, KC_PPLS, KC_PMNS, RGB_HUI, RGB_SAI, RGB_VAI, RGB_SPI, KC_NO, BL_STEP, KC_NO, KC_P1, KC_P2, KC_P3, KC_PEQL, KC_VOLU, RGB_HUD, RGB_SAD, RGB_VAD, RGB_SPD, KC_NO, KC_NO, KC_TRNS, KC_NO, KC_NO, KC_P0, KC_PDOT, KC_PENT, KC_NO, KC_VOLD, KC_NO, TO(0), KC_TRNS, KC_NO, KC_NO, KC_NO)
};

uint8_t mod_state;
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // Store the current modifier state in the variable for later reference
    mod_state = get_mods();

    switch (keycode) {
        // delete when shift and backspace are pressed.
        case KC_BSPC: {
            // Initialize a boolean variable that keeps track
            // of the delete key status: registered or not?
            static bool delkey_registered;
            if (record->event.pressed) {
                // Detect the activation of either shift keys
                if (mod_state & MOD_MASK_SHIFT) {
                    // First temporarily canceling both shifts so that
                    // shift isn't applied to the KC_DEL keycode
                    del_mods(MOD_MASK_SHIFT);
                    register_code(KC_DEL);
                    // Update the boolean variable to reflect the status of KC_DEL
                    delkey_registered = true;
                    // Reapplying modifier state so that the held shift key(s)
                    // still work even after having tapped the Backspace/Delete key.
                    set_mods(mod_state);
                    return false;
                }
            } else { // on release of KC_BSPC
                // In case KC_DEL is still being sent even after the release of KC_BSPC
                if (delkey_registered) {
                    unregister_code(KC_DEL);
                    delkey_registered = false;
                    return false;
                }
            }
            // Let QMK process the KC_BSPC keycode as usual outside of shift
            return true;
        }
    }
    return true;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    switch (get_highest_layer(state)) {
        case _LAYER1: {
            rgblight_sethsv(HSV_RED);
            break;
        }
        case _LAYER2: {
            rgblight_sethsv(HSV_ORANGE);
            break;
        }
        default: {
            rgblight_sethsv(HSV_BLUE);
            break;
        }
    }
    return state;
}
