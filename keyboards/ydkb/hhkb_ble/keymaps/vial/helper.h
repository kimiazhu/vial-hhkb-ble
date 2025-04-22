//#include QMK_KEYBOARD_H
#ifndef MOD_NULL
    #define MODS_NULL 0
#endif

#define DEFAULT_LAYER 0
#define FUNCTION_LAYER 1
#define WIN_LAYER 2
#define MAC_LAYER 3

// 调用这个方法之前，先用 IS_LAYER_ON(3) 判断一下当前是否在 macOS 层
/*
bool handle_mac(uint16_t keycode, keyrecord_t *record, uint16_t curr_key, uint8_t curr_mods, uint16_t to, uint8_t to_mods) {
    if (record->event.pressed) {
        if (keycode == curr_key && (curr_mods == MOD_BIT(KC_LSFT))) {
            if (to_mods) {
                register_mods(to_mods);
            }
            register_code(to);
            return false;
        }
    } else {
        if (keycode == curr_key && (curr_mods == MOD_BIT(KC_LSFT))) {
            unregister_code(to);
            if (to_mods) {
                unregister_mods(to_mods);
            }
            return false;
        }
    }
    return true;
}
*/
#define RALT_RELEASED_TO_CLEAR_MOD_AND_LAYER \
    unregister_mods(MOD_MASK_CSAG); \
    custom_mapping_flag = 0; \
    is_combination_active = false; \
    clear_mods(); \
    layer_clear(); \
    curr_layer = 0; \
    held_mods = 0;

#define MOVE_to_LAYER(layer) \
    else if ((keycode == KC_##layer || keycode == KC_F##layer) && held_mods == MOD_BIT(KC_RALT)) { \
        layer_move(layer); \
        curr_layer = layer; \
    }

#define HANDLE_UP(flag, trigger, expected_mods, to, to_mods) \
    else if (keycode == trigger && flag == custom_mapping_flag) { \
        unregister_code(to); \
        if (to_mods) { \
            unregister_mods(to_mods); \
        } \
        custom_mapping_flag = 0; \
    }
        // uint8_t e = expected_mods; uint8_t c = held_mods;
        // uprintf("e: %d, c: %d, eq: %d, ee: %d\n", expected_mods, held_mods, (held_mods & expected_mods), (e==c));
#define HANDLE_DOWN_WIN(flag, trigger, expected_mods, to, to_mods) \
    else if (IS_LAYER_ON(2) && (trigger == keycode) && (held_mods == expected_mods)) { \
        if (to_mods) { \
            add_mods(to_mods); \
        } \
        register_code(to); \
        custom_mapping_flag = flag; \
    }
/*
#define HANDLE_UP_WIN(trigger, expected_mods, to, to_mods) \
    else if (keycode == trigger && custom_mapping_flag) { \
        if (to_mods) { \
            unregister_mods(held_mods); \
        } \
        unregister_code(to); \
    }
*/

#define HANDLE_DOWN_MAC(flag, trigger, expected_mods, to, to_mods) \
    else if (IS_LAYER_ON(3) && (trigger == keycode) && (held_mods == expected_mods)) { \
        if (to_mods) { \
            add_mods(to_mods); \
        } \
        register_code(to); \
        custom_mapping_flag = flag; \
    }
/*
#define HANDLE_UP_MAC(trigger, expected_mods, to, to_mods) \
    else if (keycode == trigger && custom_mapping_flag == flag) { \
        if (to_mods) { \
            unregister_mods(held_mods); \
        } \
        unregister_code(to); \
        custom_mapping_flag = flag; \
    }
*/
        // uprintf("f: %d, e: %d, h: %d, to: %d, tm: %d, eq: %d\n", trigger, expected_mods, held_mods, to, to_mods, (held_mods==expected_mods));
#define HANDLE_DOWN_BTH(flag, trigger, expected_mods, to, to_mods) \
    else if ((trigger == keycode) && (held_mods == expected_mods)) { \
        if (to_mods) { \
            add_mods(to_mods); \
        } \
        register_code(to); \
        custom_mapping_flag = flag; \
    }

/*
#define HANDLE_UP_BTH(trigger, expected_mods, to, to_mods) \
    else if (keycode == trigger && custom_mapping_flag) { \
        uprintf("keycode: %d, to: %d, to_mods: %d\n", keycode, to, to_mods); \
        if (to_mods) { \
            unregister_mods(held_mods); \
        } \
        unregister_code(to); \
        custom_mapping_flag = flag; \
    }
*/
/*
#define HANDLE_DOWN_BOTH(trigger, expected_mods, to, to_mods) \
    else if ((IS_LAYER_ON(3) || IS_LAYER_ON(2)) && (trigger == keycode) && (held_mods == expected_mods)) { \
        if (to_mods) { \
            register_mods(to_mods); \
        } \
        register_code(to); \
        is_custom_keymapping_active = true; \
    }
#define HANDLE_UP_BOTH(trigger, expected_mods, to, to_mods) \
    else if (keycode == trigger && is_custom_keymapping_active) { \
        unregister_code(to); \
        if (to_mods) { \
            unregister_mods(MOD_MASK_CSAG); \
        } \
        is_custom_keymapping_active = false; \
    }
*/
