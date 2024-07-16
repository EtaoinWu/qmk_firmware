/*
 * Good on you for modifying your layout, this is the most nonQMK layout you will come across
 * There are three modes, Steno (the default), QWERTY (Toggleable) and a Momentary symbol layer
 *
 * Don't modify the steno layer directly, instead add chords using the keycodes and macros
 * from sten.h to the layout you want to modify.
 *
 * Observe the comment above processQWERTY!
 *
 * http://docs.gboards.ca
 */

#include QMK_KEYBOARD_H
#include "sten.h"

// Proper Layers
#define FUNCT   (LSD | LK | LP | LH)
#define MEDIA   (LSD | LK | LW | LR)
#define MOVE    (ST1 | ST2)
#define NUM     (RNO)
#define NUMSYM  (RU | RNO)

// QMK Layers
#define STENO_LAYER   0
#define COMBO         1

/* Keyboard Layout
 * ,---------------------------------.    ,------------------------------.
 * | FN  | LSU | LFT | LP | LH | ST1 |    | ST3 | RF | RP | RL | RT | RD |
 * |-----+-----+-----+----+----|-----|    |-----|----+----+----+----+----|
 * | PWR | LSD | LK  | LW | LR | ST2 |    | ST4 | RR | RB | RG | RS | RZ |
 * `---------------------------------'    `------------------------------'
 *                   ,---------------,    .---------------.
 *                   | LNO | LA | LO |    | RE | RU | RNO |
 *                   `---------------'    `---------------'
 */

// ,-----------------------------.    ,-----------------------------.
// |    |    |    |    |    |    |    |    |    |    |    |    |    |
// |----+----+----+----+----|----|    |----|----+----+----+----+----|
// |    |    |    |    |    |    |    |    |    |    |    |    |    |
// `-----------------------------'    `-----------------------------'

// Note: You can only use basic keycodes here!
// P() is just a wrapper to make your life easier.
// PC() applies the mapping to all of the StenoLayers.
//   To overload, declare it with P() first.
//   Be sure to enable in rules.mk and see colemak-dh for usage 
//
// FN is unavailable. That is reserved for system use.
// Chords containing PWR are always available, even in steno mode.
//
// http://docs.gboards.ca
uint32_t processQwerty(bool lookup) {
    // Specials
    REPORT_PREFIX(0);
    P( LSU | LFT | LP | LH | LNO
       | RNO | RF | RP | RL | RT,         SEND_STRING(VERSION); SEND_STRING(__DATE__));
    P( LNO | RNO | LA  | LO | RE | RU,    SEND(KC_MPLY));
    P( LFT | LK  | LP  | LW,              REPEAT());
    P( ST1 | ST2 | ST3 | ST4,             SEND(KC_BSPC));

    // Mouse Keys
    // P( LO  | LSD | LK,    CLICK_MOUSE(KC_MS_BTN2));
    // P( LO  | LR  | LW,    CLICK_MOUSE(KC_MS_BTN1));

    // Two-hand Thumb Specials
    // P( LNO | LA | RU | RNO,     ...);
    // P( LNO | LA | RE | RU,     ...);
    //         ,---------------,    .---------------.
    //         |     |    |    |    |    |    |     |
    //         `---------------'    `---------------'

    //    ,----*----*----,    .----*----*----.
    //    |    | C A P S |    | L O C K |    |
    //    `----*----*----'    `----*----*----'
    P( LA  | LO  | RE  | RU,    SEND(KC_CAPS));

    //    ,----*----*----,    .----*-----*----.
    //    |    | EN |    |    |    | TER |    |
    //    `----*----*----'    `----*-----*----'
    P( LA  | RU,                SEND(KC_ENTER));
    //    ,----*----*----,    .----*----*----.
    //    | 囧 | 囧 |    |    | 囧 |    |    | = Ctrl-Alt-Shift
    //    `----*----*----'    `----*----*----'
    P( LNO | LA  | RE,          SEND(KC_LCTL); SEND(KC_LSFT); SEND(KC_LALT));

    // One Thumb Specials & Mods
    //    Ctrl+Alt
    //  ,-----*-----*-----,
    //  | Alt | SPC | Ctrl|
    //  `-----*-----*-----'
    //             Win
    P( LNO | LA,    SEND(KC_LCTL); SEND(KC_LALT));
    P( LA | LO,     SEND(KC_LGUI));
    P( LNO,         SEND(KC_LALT));
    P( LA,          SEND(KC_SPACE));
    P( LO,          SEND(KC_LCTL));

    //                         Backspace
    //                       ,-----*-----*-----,
    //                       |Shift| SPC | Bksp|
    //                       `-----*-----*-----'
    //                                  Tab
    P( RE | RU,     SEND(KC_BACKSPACE));
    P( RU | RNO,    SEND(KC_TAB));
    P( RE,          SEND(KC_LSFT));
    P( RU,          SEND(KC_SPACE));
    P( RNO,         SEND(KC_BACKSPACE); ); // RNO is also the num layer

    // Right-hand Specials
    //                                    Control
    // ,-----------------.  ,---------------------.
    // |  |  |  |  |  |  |  |  |  |  |  |    |Bcsp| E
    // |--+--+--+--+--|--|  |--|--+--+--+---Win---| N
    // |  |  |  |  |  |  |  |  |  |  |  |    | Esc| T
    // `-----------------'  `---------------------'
    //                                      Alt
    P( RT | RD | RS | RZ,      SEND(KC_LGUI));
    P( RT | RD,                SEND(KC_LCTL));
    P( RS | RZ,                SEND(KC_LALT));
    P( RD | RZ,                SEND(KC_ENTER));
    P( RD,                     SEND(KC_BACKSPACE));
    P( RZ,                     SEND(KC_ESC));

    // Function Layer
    // ,---------------------------------.    ,---------------------------------.
    // |    |     |     |P R E F I X|    |    |    | F1  | F2  | F3  | F4  |    |
    // |----+-----+-----+-----+-----|----|    |----|--F5-+--F6-+--F7-+--F8-+----|
    // |    | F U N C T |     |     |    |    |    | F9  | F10 | F11 | F12 |    |
    // `---------------------------------'    `---------------------------------'
    REPORT_PREFIX(FUNCT);
    P( FUNCT | RF,         SEND(KC_F1));
    P( FUNCT | RP,         SEND(KC_F2));
    P( FUNCT | RL,         SEND(KC_F3));
    P( FUNCT | RT,         SEND(KC_F4));
    P( FUNCT | RF | RR,    SEND(KC_F5));
    P( FUNCT | RP | RB,    SEND(KC_F6));
    P( FUNCT | RL | RG,    SEND(KC_F7));
    P( FUNCT | RT | RS,    SEND(KC_F8));
    P( FUNCT | RR,         SEND(KC_F9));
    P( FUNCT | RG,         SEND(KC_F10));
    P( FUNCT | RB,         SEND(KC_F11));
    P( FUNCT | RS,         SEND(KC_F12));

    // Movement Layer
    // ,-----------------------------.    ,------------------------------.
    // |    |    |    |    |    |move|    |     |Home| ↑ | End|PgUp|    |
    // |----+----+----+----+----|----|    |-----|----+----+----+----+----|
    // |    |    |    |    |    |ment|    |     | ← | ↓ | → |PgDn|    |
    // `-----------------------------'    `------------------------------'
    REPORT_PREFIX(MOVE);
    P( MOVE | RP,     SEND(KC_UP));
    P( MOVE | RB,     SEND(KC_DOWN));
    P( MOVE | RR,     SEND(KC_LEFT));
    P( MOVE | RG,     SEND(KC_RIGHT));
    P( MOVE | RF,     SEND(KC_HOME));
    P( MOVE | RL,     SEND(KC_END));
    P( MOVE | RT,    SEND(KC_PGUP));
    P( MOVE | RS,    SEND(KC_PGDN));

    // Media Layer
    // ,-----------------------------.    ,-----------------------------.
    // |    |    |    |    |    |    |    |    |Play| V+ |Mute|    |    |
    // |----+----+----+----+----|----|    |----|----+----+----+----+----|
    // |    |   MEDIA  PREFIX   |    |    |    |Prev| V- |Next|    |    |
    // `-----------------------------'    `-----------------------------'
    REPORT_PREFIX(MEDIA);
    P( MEDIA | RP,    SEND(KC_AUDIO_VOL_UP));
    P( MEDIA | RB,    SEND(KC_AUDIO_VOL_DOWN));
    P( MEDIA | RR,    SEND(KC_MEDIA_PREV_TRACK));
    P( MEDIA | RG,    SEND(KC_MEDIA_NEXT_TRACK));
    P( MEDIA | RF,    SEND(KC_MEDIA_PLAY_PAUSE));
    P( MEDIA | RL,    SEND(KC_AUDIO_MUTE));

    // Number Row
    // ,-----------------------.    ,-----------------------.
    // |   | 1 | 2 | 3 | 4 | 5 |    | 6 | 7 | 8 | 9 | 0 |   |
    // |---+---+---+---+---|---|    |---|---+---+---+---+---|
    // |   |   |   |   |   |   |    |   |   |   |   |   |   |
    // `-----------------------'    `-----------------------'
    //             ,-----------,    .-----------.
    //             |   |   |   |    |   |   |NUM|
    //             `-----------'    `-----------'
    REPORT_PREFIX(NUM);
    P( RNO | LSU,    SEND(KC_1));
    P( RNO | LFT,    SEND(KC_2));
    P( RNO | LP,     SEND(KC_3));
    P( RNO | LH,     SEND(KC_4));
    P( RNO | ST1,    SEND(KC_5));
    P( RNO | ST3,    SEND(KC_6));
    P( RNO | RF,     SEND(KC_7));
    P( RNO | RP,     SEND(KC_8));
    P( RNO | RL,     SEND(KC_9));
    P( RNO | RT,     SEND(KC_0));
    // P( RNO | LA,     SEND(KC_5));
    // P( RNO | LO,     SEND(KC_0));

    // Number Symbols (Shift + Number Row)
    // ,-----------------------.    ,-----------------------.
    // |   | ! | @ | # | $ | % |    | ^ | & | * | ( | ) |   |
    // |---+---+---+---+---|---|    |---|---+---+---+---+---|
    // |   |   |   |   |   |   |    |   |   |   |   |   |   |
    // `-----------------------'    `-----------------------'
    //             ,-----------,    .-----------.
    //             |   |   |   |    |   |NUM-SYM|
    //             `-----------'    `-----------'
    REPORT_PREFIX(NUMSYM);
    P( NUMSYM | LSU,    SEND16(KC_EXCLAIM));     // !
    P( NUMSYM | LFT,    SEND16(KC_AT));          // @
    P( NUMSYM | LP,     SEND16(KC_HASH));        // #
    P( NUMSYM | LH,     SEND16(KC_DOLLAR));      // $
    P( NUMSYM | ST1,    SEND16(KC_PERCENT));     // %
    P( NUMSYM | ST3,    SEND16(KC_CIRCUMFLEX));  // ^
    P( NUMSYM | RF,     SEND16(KC_AMPERSAND));   // &
    P( NUMSYM | RP,     SEND16(KC_ASTERISK));    // *
    P( NUMSYM | RL,     SEND16(KC_LEFT_PAREN));  // (
    P( NUMSYM | RT,     SEND16(KC_RIGHT_PAREN)); // )

    // Symbols
    //  symbols row 1&2
    // ,-----------------------.    ,-------------------------.
    // |   | !   @   #   $   % |    | ^   &   *   (   )  Bksp |
    // |---+                 | |    | ?   _   +   {   }  Enter|
    // |SYM| ~   `   '   "   \ |    | /   -   =   [   ]  Esc  |
    // `-----------------------'    `-------------------------'
    REPORT_PREFIX(PWR);
    P( PWR | ST1 | ST2, SEND16(KC_PIPE));              // |
    P( PWR | ST3 | ST4, SEND16(KC_QUESTION));          // ?
    P( PWR | RF | RR,   SEND16(KC_UNDERSCORE));        // _
    P( PWR | RP | RB,   SEND16(KC_PLUS));              // +
    P( PWR | RL | RG,   SEND16(KC_LEFT_CURLY_BRACE));  // {
    P( PWR | RT | RS,   SEND16(KC_RIGHT_CURLY_BRACE)); // }
    //  symbols row 1
    P( PWR | LSU,       SEND16(KC_EXCLAIM));           // !
    P( PWR | LFT,       SEND16(KC_AT));                // @
    P( PWR | LP,        SEND16(KC_HASH));              // #
    P( PWR | LH,        SEND16(KC_DOLLAR));            // $
    P( PWR | ST1,       SEND16(KC_PERCENT));           // %
    P( PWR | ST3,       SEND16(KC_CIRCUMFLEX));        // ^
    P( PWR | RF,        SEND16(KC_AMPERSAND));         // &
    P( PWR | RP,        SEND16(KC_ASTERISK));          // *
    P( PWR | RL,        SEND16(KC_LEFT_PAREN));        // (
    P( PWR | RT,        SEND16(KC_RIGHT_PAREN));       // )
    //  symbols row 2
    P( PWR | LSD,       SEND16(KC_TILDE));             // ~
    P( PWR | LK,        SEND  (KC_GRAVE));             // `
    P( PWR | LW,        SEND  (KC_QUOTE));             // '
    P( PWR | LR,        SEND16(KC_DOUBLE_QUOTE));      // "
    P( PWR | ST2,       SEND  (KC_BACKSLASH));         // \ (backslash)
    P( PWR | ST4,       SEND  (KC_SLASH));             // /
    P( PWR | RR,        SEND  (KC_MINUS));             // -
    P( PWR | RB,        SEND  (KC_EQUAL));             // =
    P( PWR | RG,        SEND  (KC_LEFT_BRACKET));      // [
    P( PWR | RS,        SEND  (KC_RIGHT_BRACKET));     // ]
    //  symbols special
    P( PWR | RD,        SEND  (KC_BACKSPACE));
    P( PWR | RD | RZ,   SEND  (KC_ENTER));
    P( PWR | RZ,        SEND  (KC_ESC));
    //     ,-----------------,    .-----------------.
    //     | Tab | SPC | Del |    | Bksp| SPC |Enter|
    //     `-----------------'    `-----------------'
    //  symbols special: left thumb
    P( PWR | LNO,       SEND  (KC_TAB));
    P( PWR | LA,        SEND16(KC_SPACE));
    P( PWR | LO,        SEND  (KC_DELETE));
    //  symbols special: right thumb
    P( PWR | RE,        SEND  (KC_BACKSPACE));
    P( PWR | RU,        SEND  (KC_SPACE));
    P( PWR | RNO,       SEND  (KC_ENTER));
    P( PWR,             SEND  (KC_ESC));

    // Letters
    // ,-----------------------.    ,-------------------------.
    // |   | Q   W   E   R   T |    | Y   U   I   O   P  Bksp |
    // |---+ A   S   D   F   G |    | H   J   K   L   ;  Enter|
    // |   | Z   X   C   V   B |    | N   M   ,   .   /  Esc  |
    // `-----------------------'    `-------------------------'
    REPORT_PREFIX(0);
    P( LSU | LSD,    SEND(KC_A));
    P( LFT | LK,     SEND(KC_S));
    P( LP  | LW,     SEND(KC_D));
    P( LH  | LR,     SEND(KC_F));
    P( ST1 | ST2,    SEND(KC_G));
    P( ST3 | ST4,    SEND(KC_H));
    P( RF  | RR,     SEND(KC_J));
    P( RT  | RS,     SEND(KC_SEMICOLON));
    P( RG  | RL,     SEND(KC_L));
    P( RP  | RB,     SEND(KC_K));
    P( LSU,          SEND(KC_Q));
    P( LSD,          SEND(KC_Z));
    P( LFT,          SEND(KC_W));
    P( LK,           SEND(KC_X));
    P( LP,           SEND(KC_E));
    P( LW,           SEND(KC_C));
    P( LH,           SEND(KC_R));
    P( LR,           SEND(KC_V));
    P( ST1,          SEND(KC_T));
    P( ST2,          SEND(KC_B));
    P( ST3,          SEND(KC_Y));
    P( ST4,          SEND(KC_N));
    P( RF,           SEND(KC_U));
    P( RR,           SEND(KC_M));
    P( RP,           SEND(KC_I));
    P( RB,           SEND(KC_COMMA));
    P( RL,           SEND(KC_O));
    P( RG,           SEND(KC_DOT));
    P( RT,           SEND(KC_P));
    P( RS,           SEND(KC_SLASH));

    return 0;
}

// "Layers"
// Steno layer should be first in your map.
// When PWR | FN | ST3 | ST4 is pressed, the layer is increased to the next map. You must return to STENO_LAYER at the end.
// If you need more space for chords, remove the two gaming layers.
// Note: If using NO_ACTION_TAPPING, LT will not work!

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    // Main layer, everything goes through here
    [STENO_LAYER] = LAYOUT(
        STN_FN,  STN_S1,  STN_TL,  STN_PL,  STN_HL,  STN_ST1,       STN_ST3, STN_FR,  STN_PR,  STN_LR,  STN_TR,  STN_DR,
        STN_PWR, STN_S2,  STN_KL,  STN_WL,  STN_RL,  STN_ST2,       STN_ST4, STN_RR,  STN_BR,  STN_GR,  STN_SR,  STN_ZR,
                                   STN_N1,  STN_A,   STN_O,         STN_E,   STN_U,   STN_N7
    ),
    // Combo layer to use with Rime
    [COMBO] = LAYOUT(
        TO(STENO_LAYER), KC_Q,  KC_W,  KC_E,  KC_R,  KC_T,          KC_Y,  KC_U,  KC_I,    KC_O,  KC_P,    KC_BSLS,
        KC_EQL,          KC_A,  KC_S,  KC_D,  KC_F,  KC_G,          KC_H,  KC_J,  KC_K,    KC_L,  KC_DOT,  KC_SLASH,
                                       KC_C,  KC_V,  KC_B,          KC_N,  KC_M,  KC_COMM
    ),
};

// Don't fuck with this, thanks.
size_t keymapsCount  = ARRAY_SIZE(keymaps);
