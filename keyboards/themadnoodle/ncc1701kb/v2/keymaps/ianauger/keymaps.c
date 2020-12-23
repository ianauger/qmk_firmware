#include QMK_KEYBOARD_H

enum custom_keycodes {
	BLOCK_PASTE = SAFE_RANGE,
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    /* LAYER 0
     * ,-----------------------.
     * |   <<  |  MUTE |  >>   |  ENCODER - PRESS (MUTE)  / KNOB (VOLUME CONTROL)
     * |-------+-------+-------|
     * |  STOP |  PLAY | MEDIA |
     * |-------+-------+-------|
     * | CALC  | MAIL  | TO L1 |
     * `-----------------------'
     */

    [0] = LAYOUT_ortho_3x3(
      KC_MPRV, KC_MUTE, KC_MNXT,
      KC_MSTP, KC_MPLY, KC_MSEL,
      KC_CALC, KC_MAIL, TO(1)
      ),


    /* LAYER 1
     * ,-----------------------.
     * | MODE+ |RGB TOG| MODE- |  ENCODER - PRESS (NA) / KNOB (Hue Control)
     * |-------+-------+-------|
     * |  SPD- |  SPD+ |Bright |
     * |-------+-------+-------|
     * |  SAT+ |  SAT- | TO L2 |
     * `-----------------------'
     */

    [1] = LAYOUT_ortho_3x3(
      RGB_MOD, RGB_TOG, RGB_RMOD,
      RGB_SPI, RGB_SPD, RGB_VAI,
      RGB_SAI, RGB_SAD, TO(2)
      ),


    /* LAYER 2 (MACROS)
     * ,-----------------------.
     * |       |       |       |  ENCODER - PRESS (NA) / KNOB (Arrow Left/Right)
     * |-------+-------+-------|
     * |       |       |       |
     * |-------+-------+-------|
     * |       |       |       |
     * `-----------------------'
     */

    [2] = LAYOUT_ortho_3x3(
      BLOCK_PASTE, KC_TRNS, KC_TRNS,
      KC_TRNS, KC_TRNS, KC_TRNS,
      KC_TRNS, KC_TRNS, TO(0)
      )

};

void encoder_update_user(uint8_t index, bool clockwise) {

  switch (get_highest_layer(layer_state)) {
      case 1:
          if (clockwise) {
              rgblight_increase_hue();
          } else {
              rgblight_decrease_hue();
          }
          break;
      default:
          if (clockwise) {
              tap_code(KC_VOLU);
          } else {
              tap_code(KC_VOLD);
          }
          break;

  }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
	switch (keycode) {
	case BLOCK_PASTE:
		if (record->event.pressed) {
			SEND_STRING("```"  SS_TAP(X_ENTER) SS_LCMD("v") SS_TAP(X_ENTER) "```" );
		}
		else {

		}
		break;
	}
	return true;
};
