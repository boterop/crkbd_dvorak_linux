#include QMK_KEYBOARD_H
#include <stdio.h>

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_split_3x6_3(LT(3, KC_TAB), KC_SCLN, KC_COMM, KC_DOT, KC_P, KC_Y, KC_F, KC_G, KC_C, KC_R, KC_L, KC_BSPC, LCTL_T(KC_ESC), KC_A, KC_O, KC_E, KC_U, KC_I, KC_D, KC_H, KC_T, KC_N, KC_S, KC_MINS, KC_LSFT, KC_QUOT, KC_Q, KC_J, KC_K, KC_X, KC_B, KC_M, KC_W, KC_V, KC_Z, RSFT_T(KC_SLSH), KC_LGUI, MO(1), KC_SPC, KC_SPC, LT(2, KC_ENT), KC_LALT),
    [1] = LAYOUT_split_3x6_3(KC_TAB, KC_NO, KC_NO, KC_F2, KC_NO, KC_PSCR, KC_PSCR, KC_NO, KC_UP, KC_NO, KC_NO, KC_NO, LCTL_T(KC_ESC), LCTL(KC_Y), KC_LSFT, KC_LALT, KC_TAB, KC_NO, KC_NO, KC_LEFT, KC_DOWN, KC_RGHT, KC_NO, KC_NO, KC_BRID, LCTL(KC_Z), LCTL(KC_X), LCTL(KC_C), LCTL(LSFT(KC_V)), KC_VOLD, KC_VOLU, KC_MPRV, KC_MPLY, KC_MNXT, KC_NO, KC_BRIU, KC_LGUI, KC_TRNS, KC_SPC, KC_SPC, MO(4), KC_RALT),
    [2] = LAYOUT_split_3x6_3(KC_NO, KC_EXLM, KC_AT, KC_LPRN, KC_RPRN, KC_PERC, KC_EQL, KC_NO, KC_NO, KC_NO, KC_NO, KC_DEL, LCTL_T(KC_ESC), KC_NO, KC_NO, KC_LCBR, KC_RCBR, KC_NO, KC_EXLM, KC_HASH, KC_SLSH, KC_BSLS, KC_PIPE, KC_DLR, KC_NO, KC_NO, KC_NO, KC_LBRC, KC_RBRC, KC_NO, KC_NO, KC_GRV, KC_CIRC, KC_AT, KC_AMPR, KC_TILD, KC_LGUI, MO(4), KC_SPC, KC_SPC, MO(2), KC_RALT),
    [3] = LAYOUT_split_3x6_3(KC_NO, KC_ACL2, KC_BTN1, KC_MS_U, KC_BTN2, KC_WH_U, KC_PPLS, KC_1, KC_2, KC_3, KC_MINS, KC_NO, LCTL_T(KC_ESC), KC_ACL1, KC_MS_L, KC_MS_D, KC_MS_R, KC_WH_D, KC_PAST, KC_4, KC_5, KC_6, KC_SLSH, KC_NO, KC_NO, KC_ACL0, KC_NO, KC_NO, KC_NO, KC_NO, KC_0, KC_7, KC_8, KC_9, KC_0, KC_NO, KC_LGUI, MO(1), KC_SPC, KC_SPC, LT(2, KC_ENT), KC_RALT),
    [4] = LAYOUT_split_3x6_3(QK_BOOT, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, RGB_TOG, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, RGB_RMOD, RGB_HUD, RGB_SAD, RGB_SPD, RGB_VAD, RGB_VAI, RGB_SPI, RGB_SAI, RGB_HUI, RGB_MOD, KC_NO, KC_LGUI, KC_TRNS, KC_SPC, KC_SPC, KC_TRNS, KC_RALT)};

#if defined(ENCODER_ENABLE) && defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {

};
#endif

#ifdef OLED_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation)
{
    if (!is_keyboard_master())
    {
        return OLED_ROTATION_180;
    }

    return rotation;
}

#define L_DVORAK 0
#define L_NAVIGATE 2
#define L_SYMBOLS 4
#define L_NUMPAD 8
#define L_ADJUST 16

void render_status(void)
{
    oled_write_P(PSTR("Layer: "), false);
    switch (layer_state)
    {
    case L_DVORAK:
        oled_write_ln_P(PSTR("Dvorak"), false);
        break;
    case L_NAVIGATE:
        oled_write_ln_P(PSTR("Navigate"), false);
        break;
    case L_SYMBOLS:
        oled_write_ln_P(PSTR("Symbols"), false);
        break;
    case L_NUMPAD:
        oled_write_ln_P(PSTR("Numpad"), false);
        break;
    default:
        oled_write_ln_P(PSTR("Adjust"), false);
        break;
    }
}

static void render_logo(void)
{
    static const char PROGMEM qmk_logo[] = {
        0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F, 0x90, 0x91, 0x92, 0x93, 0x94,
        0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xAA, 0xAB, 0xAC, 0xAD, 0xAE, 0xAF, 0xB0, 0xB1, 0xB2, 0xB3, 0xB4,
        0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF, 0xD0, 0xD1, 0xD2, 0xD3, 0xD4, 0x00};

    oled_write_P(qmk_logo, false);
}

bool oled_task_user(void)
{
    if (is_keyboard_master())
    {
        render_status();
    }
    else
    {
        render_logo();
        oled_scroll_left();
    }
    return false;
}
#endif
