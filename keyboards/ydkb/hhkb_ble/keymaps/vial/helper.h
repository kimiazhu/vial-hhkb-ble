//#include QMK_KEYBOARD_H
#ifndef MOD_NULL
    #define MODS_NULL 0
#endif

#define DEFAULT_LAYER 0
#define FUNCTION_LAYER 1
#define WIN_LAYER 2
#define MAC_LAYER 3

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

#define HANDLE_DOWN_WIN(flag, trigger, expected_mods, to, to_mods) \
    else if (IS_LAYER_ON(2) && (trigger == keycode) && (held_mods == expected_mods)) { \
        if (to_mods) { \
            add_mods(to_mods); \
        } \
        register_code(to); \
        custom_mapping_flag = flag; \
    }

#define HANDLE_DOWN_MAC(flag, trigger, expected_mods, to, to_mods) \
    else if (IS_LAYER_ON(3) && (trigger == keycode) && (held_mods == expected_mods)) { \
        if (to_mods) { \
            add_mods(to_mods); \
        } \
        register_code(to); \
        custom_mapping_flag = flag; \
    }

#define HANDLE_DOWN_BTH(flag, trigger, expected_mods, to, to_mods) \
    else if ((trigger == keycode) && (held_mods == expected_mods)) { \
        if (to_mods) { \
            add_mods(to_mods); \
        } \
        register_code(to); \
        custom_mapping_flag = flag; \
    }

