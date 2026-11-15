// Ferris 0.1 (ATmega32u4, QMK) — same keymap as my ZMK corneish-zen / Besom,
// trimmed to 34 keys: Tab = both left thumbs together, Esc = A+Z combo.

#include QMK_KEYBOARD_H

enum layers { DEF, NAV, NUM, SYS };

// Home row mods (same mods as the ZMK boards)
#define HM_A LCTL_T(KC_A)
#define HM_S LGUI_T(KC_S)
#define HM_D LALT_T(KC_D)
#define HM_F LSFT_T(KC_F)
#define HM_J LSFT_T(KC_J)
#define HM_K LALT_T(KC_K)
#define HM_L LGUI_T(KC_L)
#define HM_QUOT LCTL_T(KC_QUOT)
#define HM_X RGUI_T(KC_X)
#define HM_DOT RGUI_T(KC_DOT)
#define SYS_Z LT(SYS, KC_Z)
#define SYS_SLSH LT(SYS, KC_SLSH)

// Thumbs
#define TH_SPC LT(NUM, KC_SPC)
#define TH_ENT LT(NAV, KC_ENT)
#define TH_DEL LT(NAV, KC_DEL)
#define TH_BSPC LT(NUM, KC_BSPC)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [DEF] = LAYOUT_split_3x5_2(
        KC_Q,  KC_W,  KC_E,  KC_R,  KC_T,        KC_Y,  KC_U,  KC_I,    KC_O,   KC_P,
        HM_A,  HM_S,  HM_D,  HM_F,  KC_G,        KC_H,  HM_J,  HM_K,    HM_L,   HM_QUOT,
        SYS_Z, HM_X,  KC_C,  KC_V,  KC_B,        KC_N,  KC_M,  KC_COMM, HM_DOT, SYS_SLSH,
                             TH_SPC, TH_ENT,     TH_DEL, TH_BSPC
    ),
    [NAV] = LAYOUT_split_3x5_2(
        KC_F1,          KC_F2,          KC_F3,          KC_F4,          XXXXXXX,    KC_HOME, KC_PGDN, KC_PGUP, KC_END,  XXXXXXX,
        LCTL_T(KC_F5),  LGUI_T(KC_F6),  LALT_T(KC_F7),  LSFT_T(KC_F8),  XXXXXXX,    KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, XXXXXXX,
        KC_F9,          KC_F10,         KC_F11,         KC_F12,         XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                                                        _______, _______,           _______, _______
    ),
    [NUM] = LAYOUT_split_3x5_2(
        KC_1,    KC_2,    KC_3,    KC_4,    KC_5,       KC_6,    KC_7,    KC_8,    KC_9,    KC_0,
        KC_LCTL, KC_LGUI, KC_LALT, KC_LSFT, KC_F11,     KC_F12,  KC_RSFT, KC_RALT, KC_LGUI, KC_RCTL,
        KC_ESC,  KC_GRV,  KC_MINS, KC_EQL,  XXXXXXX,    XXXXXXX, KC_LBRC, KC_RBRC, KC_BSLS, KC_SCLN,
                                   _______, _______,    _______, _______
    ),
    // Wired-only board, so no Bluetooth keys; Q = jump to bootloader for flashing.
    [SYS] = LAYOUT_split_3x5_2(
        QK_BOOT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                                   _______, _______,    _______, _______
    ),
};

// Chordal Hold handedness; thumbs are exempt so layer + same-hand key works.
const char chordal_hold_layout[MATRIX_ROWS][MATRIX_COLS] PROGMEM = LAYOUT_split_3x5_2(
    'L', 'L', 'L', 'L', 'L',    'R', 'R', 'R', 'R', 'R',
    'L', 'L', 'L', 'L', 'L',    'R', 'R', 'R', 'R', 'R',
    'L', 'L', 'L', 'L', 'L',    'R', 'R', 'R', 'R', 'R',
                   '*', '*',    '*', '*'
);

static bool is_thumb(keyrecord_t *record) {
    return record->event.key.row == 3 || record->event.key.row == 7;
}

// Thumbs react quicker, like the 150 ms layer-taps on the ZMK boards.
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    return is_thumb(record) ? 200 : TAPPING_TERM;
}

// Flow Tap for everything except the thumb layer keys, so a layer is always
// reachable right after typing.
uint16_t get_flow_tap_term(uint16_t keycode, keyrecord_t *record, uint16_t prev_keycode) {
    if (is_thumb(record)) return 0;
    if (is_flow_tap_key(keycode) && is_flow_tap_key(prev_keycode)) return FLOW_TAP_TERM;
    return 0;
}

// Vertical combos, as on the ZMK boards (top+home = number, home+bottom = symbol).
const uint16_t PROGMEM c_1[]    = {KC_Q, HM_A, COMBO_END};
const uint16_t PROGMEM c_2[]    = {KC_W, HM_S, COMBO_END};
const uint16_t PROGMEM c_3[]    = {KC_E, HM_D, COMBO_END};
const uint16_t PROGMEM c_4[]    = {KC_R, HM_F, COMBO_END};
const uint16_t PROGMEM c_5[]    = {KC_T, KC_G, COMBO_END};
const uint16_t PROGMEM c_6[]    = {KC_Y, KC_H, COMBO_END};
const uint16_t PROGMEM c_7[]    = {KC_U, HM_J, COMBO_END};
const uint16_t PROGMEM c_8[]    = {KC_I, HM_K, COMBO_END};
const uint16_t PROGMEM c_9[]    = {KC_O, HM_L, COMBO_END};
const uint16_t PROGMEM c_0[]    = {KC_P, HM_QUOT, COMBO_END};
const uint16_t PROGMEM c_esc[]  = {HM_A, SYS_Z, COMBO_END};
const uint16_t PROGMEM c_grv[]  = {HM_S, HM_X, COMBO_END};
const uint16_t PROGMEM c_mins[] = {HM_D, KC_C, COMBO_END};
const uint16_t PROGMEM c_eql[]  = {HM_F, KC_V, COMBO_END};
const uint16_t PROGMEM c_lbrc[] = {HM_J, KC_M, COMBO_END};
const uint16_t PROGMEM c_rbrc[] = {HM_K, KC_COMM, COMBO_END};
const uint16_t PROGMEM c_bsls[] = {HM_L, HM_DOT, COMBO_END};
const uint16_t PROGMEM c_scln[] = {HM_QUOT, SYS_SLSH, COMBO_END};
const uint16_t PROGMEM c_tab[]  = {TH_SPC, TH_ENT, COMBO_END};

combo_t key_combos[] = {
    COMBO(c_1, KC_1),       COMBO(c_2, KC_2),       COMBO(c_3, KC_3),       COMBO(c_4, KC_4),
    COMBO(c_5, KC_5),       COMBO(c_6, KC_6),       COMBO(c_7, KC_7),       COMBO(c_8, KC_8),
    COMBO(c_9, KC_9),       COMBO(c_0, KC_0),
    COMBO(c_esc, KC_ESC),   COMBO(c_grv, KC_GRV),   COMBO(c_mins, KC_MINS), COMBO(c_eql, KC_EQL),
    COMBO(c_lbrc, KC_LBRC), COMBO(c_rbrc, KC_RBRC), COMBO(c_bsls, KC_BSLS), COMBO(c_scln, KC_SCLN),
    COMBO(c_tab, KC_TAB),
};
