#include QMK_KEYBOARD_H
#include "./helper.h"

#if 0
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {LAYOUT_all(KC_NO)};
#else
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] =
{
  [0] = {
    { KC_2,   KC_Q,   KC_W,   KC_S,   KC_A,   KC_Z,   KC_X,   KC_C,   },
    { KC_3,   KC_4,   KC_R,   KC_E,   KC_D,   KC_F,   KC_V,   KC_B,   },
    { KC_5,   KC_6,   KC_Y,   KC_T,   KC_G,   KC_H,   KC_N,   KC_NO,  },
    { KC_1,   KC_ESC, KC_TAB, KC_LCTL,KC_LSFT,KC_LALT,KC_LGUI,KC_SPC, },
    { KC_7,   KC_8,   KC_U,   KC_I,   KC_K,   KC_J,   KC_M,   KC_NO,  },
    { KC_BSLS,KC_GRV, KC_BSPC,KC_ENT, MO(1),  KC_RSFT,KC_RALT,KC_RGUI,},
    { KC_9,   KC_0,   KC_O,   KC_P,   KC_SCLN,KC_L,   KC_COMM,KC_NO,  },
    { KC_MINS,KC_EQL, KC_RBRC,KC_LBRC,KC_QUOT,KC_SLSH,KC_DOT, KC_CAPS,},
    { KC_LCTL,MO(1),  MO(1),  MO(1),  KC_LEFT,KC_DOWN,KC_UP,  KC_RGHT,}
    },
  [1] = {
    { KC_F2,  USER00, KC_TRNS,KC_VOLU,KC_VOLD,USER03, KC_TRNS,KC_TRNS,},
    { KC_F3,  KC_F4,  KC_TRNS,USER02, KC_MUTE,KC_TRNS,KC_TRNS,USER01, },
    { KC_F5,  KC_F6,  KC_TRNS,KC_TRNS,KC_TRNS,KC_PAST,KC_PPLS,KC_TRNS,},
    { KC_F1,  KC_PWR, KC_CAPS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,},
    { KC_F7,  KC_F8,  USER04, KC_PSCR,KC_HOME,KC_PSLS,KC_PMNS,KC_TRNS,},
    { KC_INS, KC_DEL, KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,},
    { KC_F9,  KC_F10, KC_SLCK,KC_PAUS,KC_LEFT,KC_PGUP,KC_END, KC_TRNS,},
    { KC_F11, KC_F12, KC_TRNS,KC_UP,  KC_RGHT,KC_DOWN,KC_PGDN,KC_TRNS,},
    { KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_MUTE,KC_VOLD,KC_TRNS,KC_VOLU,}
    },
};

// static bool is_custom_keymapping_active = false; // 标记一组用户自定义快捷键生效，用于按键释放的时候触发 unregister_code
static uint8_t custom_mapping_flag = 0; // 用于标记当前的自定义快捷键

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    static uint8_t held_mods = 0;
    // 用来标记是否有组合键被激活，如果仅仅是修饰键被按下并释放，这时候应该直接发送给系统，
    // 比如 GUI 键单独按下释放用于激活系统菜单，SHIFT 单独按下释放用于切换输入法
    static bool is_combination_active = false;
    static int curr_layer = 0;

    if (record->event.pressed) {
        if (IS_LAYER_ON(WIN_LAYER) || IS_LAYER_ON(MAC_LAYER)) {
            if (keycode >= KC_LCTL && keycode <= KC_RGUI) { // 按下修饰键，记录下即可
                held_mods |= MOD_BIT(keycode);
                return false;
            } else { // 当前按下的是普通按键
                if (held_mods) { // 当前按下的是普通按键，但此时修饰键处于按下状态
                    is_combination_active = true; // 激活组合键标记位
                    //uprintf("PRESSED, trigger: %d, held_mods: %d\n", keycode, held_mods);
                    if (0) {}
                    MOVE_to_LAYER(1)
                    MOVE_to_LAYER(2)
                    MOVE_to_LAYER(3)
                    HANDLE_DOWN_BTH(1, KC_H, (MOD_BIT(KC_LCTL)), KC_LEFT, MODS_NULL)
                    HANDLE_DOWN_BTH(2, KC_J, (MOD_BIT(KC_LCTL)), KC_DOWN, MODS_NULL)
                    HANDLE_DOWN_BTH(3, KC_K, (MOD_BIT(KC_LCTL)), KC_UP, MODS_NULL)
                    HANDLE_DOWN_BTH(4, KC_L, (MOD_BIT(KC_LCTL)), KC_RIGHT, MODS_NULL)
                    HANDLE_DOWN_BTH(5, KC_H, (MOD_BIT(KC_LALT)), KC_LEFT, (MOD_BIT(KC_LCTL))) // 终端后退一个单词
                    HANDLE_DOWN_BTH(6, KC_L, (MOD_BIT(KC_LALT)), KC_RIGHT, (MOD_BIT(KC_LCTL))) // 终端前进一个单词
                    HANDLE_DOWN_BTH(7, KC_ESC, (MOD_BIT(KC_LSFT)), KC_GRV, (MOD_BIT(KC_LSFT)))
                    HANDLE_DOWN_BTH(8, KC_ESC, (MOD_BIT(KC_LCTL)), KC_GRV, MODS_NULL)
                    HANDLE_DOWN_BTH(9, KC_BSPC, (MOD_BIT(KC_LSFT)), KC_BSLS, (MOD_BIT(KC_LSFT)))
                    HANDLE_DOWN_BTH(10, KC_BSPC, (MOD_BIT(KC_LCTL)), KC_BSLS, MODS_NULL)
                    HANDLE_DOWN_BTH(11, KC_E, (MOD_BIT(KC_LCTL)), KC_END, MODS_NULL)
                    HANDLE_DOWN_BTH(12, KC_QUOT, (MOD_BIT(KC_LCTL)), KC_BSPC, MODS_NULL)
                    HANDLE_DOWN_BTH(13, KC_SCLN, (MOD_BIT(KC_LCTL)), KC_ENT, MODS_NULL)
                    HANDLE_DOWN_BTH(14, KC_B, (MOD_BIT(KC_LCTL)), KC_BSPC, MODS_NULL)
                    HANDLE_DOWN_BTH(15, KC_ESC, (MOD_BIT(KC_LALT)), KC_GRV, (MOD_BIT(KC_LALT)))
                    HANDLE_DOWN_BTH(16, KC_U, (MOD_BIT(KC_LALT)), KC_PGUP, MODS_NULL)
                    HANDLE_DOWN_BTH(17, KC_D, (MOD_BIT(KC_LALT)), KC_PGDN, MODS_NULL)
                    HANDLE_DOWN_BTH(18, KC_J, (MOD_BIT(KC_LALT)), KC_PGUP, MODS_NULL)
                    HANDLE_DOWN_BTH(19, KC_K, (MOD_BIT(KC_LALT)), KC_PGDN, MODS_NULL)
                    HANDLE_DOWN_BTH(20, KC_D, (MOD_BIT(KC_LCTL)), KC_DEL, MODS_NULL)
                    HANDLE_DOWN_MAC(21, KC_R, (MOD_BIT(KC_LCTL)), KC_R, (MOD_BIT(KC_LGUI)))
                    HANDLE_DOWN_WIN(22, KC_A, (MOD_BIT(KC_LGUI)), KC_A, (MOD_BIT(KC_LCTL))) // win+A -> 全选
                    HANDLE_DOWN_WIN(23, KC_A, (MOD_BIT(KC_LCTL)), KC_HOME, MODS_NULL)
                    HANDLE_DOWN_WIN(24, KC_Q, (MOD_BIT(KC_LGUI)), KC_F4, (MOD_BIT(KC_LALT))) // win+Q -> 关闭窗口
                    HANDLE_DOWN_WIN(25, KC_N, (MOD_BIT(KC_LCTL)), KC_F2, MODS_NULL) // ctrl+n -> rename
                    HANDLE_DOWN_WIN(26, KC_C, (MOD_BIT(KC_LGUI)), KC_C, (MOD_BIT(KC_LCTL))) // win+c -> 复制
                    HANDLE_DOWN_WIN(27, KC_V, (MOD_BIT(KC_LGUI)), KC_V, (MOD_BIT(KC_LCTL))) // win+v -> 粘贴
                    HANDLE_DOWN_WIN(28, KC_X, (MOD_BIT(KC_LGUI)), KC_X, (MOD_BIT(KC_LCTL))) // win+x -> 剪切
                    HANDLE_DOWN_WIN(29, KC_F, (MOD_BIT(KC_LGUI)), KC_F, (MOD_BIT(KC_LCTL))) // win+f -> find
                    HANDLE_DOWN_WIN(30, KC_S, (MOD_BIT(KC_LGUI)), KC_S, (MOD_BIT(KC_LCTL))) // win+f -> save
                    HANDLE_DOWN_WIN(31, KC_W, (MOD_BIT(KC_LGUI)), KC_W, (MOD_BIT(KC_LCTL))) // win+w -> close tab
                    HANDLE_DOWN_WIN(32, KC_Z, (MOD_BIT(KC_LGUI)), KC_Z, (MOD_BIT(KC_LCTL))) // win+z -> undo
                    HANDLE_DOWN_WIN(33, KC_Y, (MOD_BIT(KC_LGUI)), KC_Y, (MOD_BIT(KC_LCTL))) // win+y -> redo
                    HANDLE_DOWN_BTH(34, KC_L, (MOD_BIT(KC_LCTL)|MOD_BIT(KC_LSFT)), KC_END, (MOD_BIT(KC_LSFT))) // select to end
                    HANDLE_DOWN_BTH(35, KC_H, (MOD_BIT(KC_LCTL)|MOD_BIT(KC_LSFT)), KC_HOME, (MOD_BIT(KC_LSFT))) // select to home
                    HANDLE_DOWN_BTH(36, KC_J, (MOD_BIT(KC_LCTL)|MOD_BIT(KC_LSFT)), KC_DOWN, (MOD_BIT(KC_LSFT))) // select to next line
                    HANDLE_DOWN_BTH(37, KC_K, (MOD_BIT(KC_LCTL)|MOD_BIT(KC_LSFT)), KC_UP, (MOD_BIT(KC_LSFT))) // select to before line
                    HANDLE_DOWN_BTH(38, KC_B, (MOD_BIT(KC_LCTL)|MOD_BIT(KC_LSFT)), KC_LEFT, (MOD_BIT(KC_LSFT))) // select to previous character
                    HANDLE_DOWN_BTH(39, KC_F, (MOD_BIT(KC_LCTL)|MOD_BIT(KC_LSFT)), KC_RIGHT, (MOD_BIT(KC_LSFT))) // select to next character
                    HANDLE_DOWN_WIN(40, KC_L, (MOD_BIT(KC_LGUI)), KC_L, (MOD_BIT(KC_LCTL))) // Win: LWin+L -> browser address bar
                    HANDLE_DOWN_WIN(41, KC_U, (MOD_BIT(KC_LGUI)), KC_Z, (MOD_BIT(KC_LCTL))) // Win: LWin+u -> undo
                    HANDLE_DOWN_WIN(42, KC_SLSH, (MOD_BIT(KC_LGUI)), KC_SLSH, (MOD_BIT(KC_LCTL))) // Win: LWin+/ -> comment code
                    HANDLE_DOWN_WIN(43, KC_H, (MOD_BIT(KC_LALT)|MOD_BIT(KC_LSFT)), KC_LEFT, (MOD_BIT(KC_LCTL)|MOD_BIT(KC_LSFT))) // Win: select to previous word
                    HANDLE_DOWN_WIN(44, KC_L, (MOD_BIT(KC_LALT)|MOD_BIT(KC_LSFT)), KC_RIGHT, (MOD_BIT(KC_LCTL)|MOD_BIT(KC_LSFT))) // Win: select to next word
                    HANDLE_DOWN_MAC(45, KC_H, (MOD_BIT(KC_LALT)|MOD_BIT(KC_LSFT)), KC_LEFT, (MOD_BIT(KC_LALT)|MOD_BIT(KC_LSFT))) // mac: select to previous word
                    HANDLE_DOWN_MAC(46, KC_L, (MOD_BIT(KC_LALT)|MOD_BIT(KC_LSFT)), KC_RIGHT, (MOD_BIT(KC_LALT)|MOD_BIT(KC_LSFT))) // mac: select to next word
                    else {
                        register_mods(held_mods);
                        register_code(keycode);
                    }
                    return false;
                }
            }
        } else { // layer 0 and layer 1, currently we only have 4 layers
            if (keycode == KC_RALT) { // 单独按下RALT，也只记录，不发送给系统，用于组合键切换层
                held_mods |= MOD_BIT(KC_RALT);
                return false;
            } else if (keycode == KC_1 || keycode == KC_2 || keycode == KC_3 || keycode == KC_F1 || keycode == KC_F2 || keycode == KC_F3) {
                if (held_mods == MOD_BIT(KC_RALT)) { // 切换层
                    is_combination_active = true;
                    if (0) {}
                    MOVE_to_LAYER(1)
                    MOVE_to_LAYER(2)
                    MOVE_to_LAYER(3)
                    return false;
                }
            }
        }
    } else { // 释放按键
        if (IS_LAYER_ON(WIN_LAYER) || IS_LAYER_ON(MAC_LAYER)) {
            if (keycode >= KC_LCTL && keycode <= KC_RGUI) {
                held_mods &= ~MOD_BIT(keycode);
                if (!is_combination_active) {
                    if (keycode == KC_RALT) { // RALT用作一个层切换键，加数组激活指定层，短按时用于清除修饰键并返回0层
                        RALT_RELEASED_TO_CLEAR_MOD_AND_LAYER
                    } else { tap_code(keycode); }
                }
                if (!held_mods) { // 所有的 mods 组合键都释放了
                    is_combination_active = false;
                }
                return false;
            } else { // 释放普通按键的分支逻辑
                if (keycode == MO(1)) {unregister_code(MO(1));layer_move(curr_layer);}
                HANDLE_UP(1, KC_H, (MOD_BIT(KC_LCTL)), KC_LEFT, MODS_NULL)
                HANDLE_UP(2, KC_J, (MOD_BIT(KC_LCTL)), KC_DOWN, MODS_NULL)
                HANDLE_UP(3, KC_K, (MOD_BIT(KC_LCTL)), KC_UP, MODS_NULL)
                HANDLE_UP(4, KC_L, (MOD_BIT(KC_LCTL)), KC_RIGHT, MODS_NULL)
                HANDLE_UP(5, KC_H, (MOD_BIT(KC_LALT)), KC_LEFT, (MOD_BIT(KC_LCTL))) // 终端后退一个单词
                HANDLE_UP(6, KC_L, (MOD_BIT(KC_LALT)), KC_RIGHT, (MOD_BIT(KC_LCTL))) // 终端前进一个单词
                HANDLE_UP(7, KC_ESC, (MOD_BIT(KC_LSFT)), KC_GRV, (MOD_BIT(KC_LSFT)))
                HANDLE_UP(8, KC_ESC, (MOD_BIT(KC_LCTL)), KC_GRV, MODS_NULL)
                HANDLE_UP(9, KC_BSPC, (MOD_BIT(KC_LSFT)), KC_BSLS, (MOD_BIT(KC_LSFT)))
                HANDLE_UP(10, KC_BSPC, (MOD_BIT(KC_LCTL)), KC_BSLS, MODS_NULL)
                HANDLE_UP(11, KC_E, (MOD_BIT(KC_LCTL)), KC_END, MODS_NULL)
                HANDLE_UP(12, KC_QUOT, (MOD_BIT(KC_LCTL)), KC_BSPC, MODS_NULL)
                HANDLE_UP(13, KC_SCLN, (MOD_BIT(KC_LCTL)), KC_ENT, MODS_NULL)
                HANDLE_UP(14, KC_B, (MOD_BIT(KC_LCTL)), KC_BSPC, MODS_NULL)
                HANDLE_UP(15, KC_ESC, (MOD_BIT(KC_LALT)), KC_GRV, (MOD_BIT(KC_LALT)))
                HANDLE_UP(16, KC_U, (MOD_BIT(KC_LALT)), KC_PGUP, MODS_NULL)
                HANDLE_UP(17, KC_D, (MOD_BIT(KC_LALT)), KC_PGDN, MODS_NULL)
                HANDLE_UP(18, KC_J, (MOD_BIT(KC_LALT)), KC_PGUP, MODS_NULL)
                HANDLE_UP(19, KC_K, (MOD_BIT(KC_LALT)), KC_PGDN, MODS_NULL)
                HANDLE_UP(20, KC_D, (MOD_BIT(KC_LCTL)), KC_DEL, MODS_NULL)
                HANDLE_UP(21, KC_R, (MOD_BIT(KC_LCTL)), KC_R, (MOD_BIT(KC_LGUI)))
                HANDLE_UP(22, KC_A, (MOD_BIT(KC_LGUI)), KC_A, (MOD_BIT(KC_LCTL))) // win+A -> 全选
                HANDLE_UP(23, KC_A, (MOD_BIT(KC_LCTL)), KC_HOME, MODS_NULL)
                HANDLE_UP(24, KC_Q, (MOD_BIT(KC_LGUI)), KC_F4, (MOD_BIT(KC_LALT))) // win+Q -> 关闭窗口
                HANDLE_UP(25, KC_N, (MOD_BIT(KC_LCTL)), KC_F2, MODS_NULL) // ctrl+n -> rename
                HANDLE_UP(26, KC_C, (MOD_BIT(KC_LGUI)), KC_C, (MOD_BIT(KC_LCTL))) // win+c -> 复制
                HANDLE_UP(27, KC_V, (MOD_BIT(KC_LGUI)), KC_V, (MOD_BIT(KC_LCTL))) // win+v -> 粘贴
                HANDLE_UP(28, KC_X, (MOD_BIT(KC_LGUI)), KC_X, (MOD_BIT(KC_LCTL))) // win+x -> 剪切
                HANDLE_UP(29, KC_F, (MOD_BIT(KC_LGUI)), KC_F, (MOD_BIT(KC_LCTL))) // win+f -> find
                HANDLE_UP(30, KC_S, (MOD_BIT(KC_LGUI)), KC_S, (MOD_BIT(KC_LCTL))) // win+f -> save
                HANDLE_UP(31, KC_W, (MOD_BIT(KC_LGUI)), KC_W, (MOD_BIT(KC_LCTL))) // win+w -> close tab
                HANDLE_UP(32, KC_Z, (MOD_BIT(KC_LGUI)), KC_Z, (MOD_BIT(KC_LCTL))) // win+z -> undo
                HANDLE_UP(33, KC_Y, (MOD_BIT(KC_LGUI)), KC_Y, (MOD_BIT(KC_LCTL))) // win+y -> redo
                HANDLE_UP(34, KC_L, (MOD_BIT(KC_LCTL)|MOD_BIT(KC_LSFT)), KC_END, (MOD_BIT(KC_LSFT))) // select to end
                HANDLE_UP(35, KC_H, (MOD_BIT(KC_LCTL)|MOD_BIT(KC_LSFT)), KC_HOME, (MOD_BIT(KC_LSFT))) // select to home
                HANDLE_UP(36, KC_J, (MOD_BIT(KC_LCTL)|MOD_BIT(KC_LSFT)), KC_DOWN, (MOD_BIT(KC_LSFT))) // select to next line
                HANDLE_UP(37, KC_K, (MOD_BIT(KC_LCTL)|MOD_BIT(KC_LSFT)), KC_UP, (MOD_BIT(KC_LSFT))) // select to before line
                HANDLE_UP(38, KC_B, (MOD_BIT(KC_LCTL)|MOD_BIT(KC_LSFT)), KC_LEFT, (MOD_BIT(KC_LSFT))) // select to previous character
                HANDLE_UP(39, KC_F, (MOD_BIT(KC_LCTL)|MOD_BIT(KC_LSFT)), KC_RIGHT, (MOD_BIT(KC_LSFT))) // select to next character
                HANDLE_UP(40, KC_L, (MOD_BIT(KC_LGUI)), KC_L, (MOD_BIT(KC_LCTL))) // Win: LWin+L -> browser address bar
                HANDLE_UP(41, KC_U, (MOD_BIT(KC_LGUI)), KC_Z, (MOD_BIT(KC_LCTL))) // Win: LWin+u -> undo
                HANDLE_UP(42, KC_SLSH, (MOD_BIT(KC_LGUI)), KC_SLSH, (MOD_BIT(KC_LCTL))) // Win: LWin+/ -> comment code
                HANDLE_UP(43, KC_H, (MOD_BIT(KC_LALT)|MOD_BIT(KC_LSFT)), KC_LEFT, (MOD_BIT(KC_LCTL)|MOD_BIT(KC_LSFT))) // Win: select to next word
                HANDLE_UP(44, KC_L, (MOD_BIT(KC_LALT)|MOD_BIT(KC_LSFT)), KC_RIGHT, (MOD_BIT(KC_LCTL)|MOD_BIT(KC_LSFT))) // Win: select to next word
                HANDLE_UP(45, KC_H, (MOD_BIT(KC_LALT)|MOD_BIT(KC_LSFT)), KC_LEFT, (MOD_BIT(KC_LALT)|MOD_BIT(KC_LSFT))) // mac: select to previous word
                HANDLE_UP(46, KC_L, (MOD_BIT(KC_LALT)|MOD_BIT(KC_LSFT)), KC_RIGHT, (MOD_BIT(KC_LALT)|MOD_BIT(KC_LSFT))) // mac: select to next word
                else {
                    unregister_code(keycode);
                    // unregister_mods(MOD_MASK_CSAG);
                    unregister_mods(held_mods);
                    custom_mapping_flag = 0;
                    // clear_mods();
                }
                return false;
            }
        } else { // layer 0 and layer 1
            if (keycode == KC_RALT) {
                held_mods &= ~MOD_BIT(KC_RALT);
                if (!is_combination_active) {
                    RALT_RELEASED_TO_CLEAR_MOD_AND_LAYER
                }
                if (!held_mods) { // 所有的 mods 组合键都释放了
                    is_combination_active = false;
                }
                return false;
            }
        }
    }
    return true;
}

#endif
