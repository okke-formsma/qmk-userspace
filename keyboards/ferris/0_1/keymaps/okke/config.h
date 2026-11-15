#pragma once

/* QMK's take on "timeless" home row mods:
 * - CHORDAL_HOLD: a tap-hold key only becomes a mod/layer when the next key
 *   is on the opposite hand (thumbs are exempt, see chordal_hold_layout).
 * - FLOW_TAP_TERM: while typing fast, home row keys are always taps
 *   (like ZMK's require-prior-idle-ms).
 * - PERMISSIVE_HOLD + a long tapping term: holding a key a bit too long while
 *   typing slowly still types a letter; a nested tap decides the hold.
 */
#define CHORDAL_HOLD
#define PERMISSIVE_HOLD
#define FLOW_TAP_TERM 150
#define TAPPING_TERM 280
#define TAPPING_TERM_PER_KEY
#define QUICK_TAP_TERM 175

/* Vertical combos, same timing as the ZMK keymaps. */
#define COMBO_TERM 100
/* Combos are position-based on every layer, as in ZMK. */
#define COMBO_ONLY_FROM_LAYER 0
