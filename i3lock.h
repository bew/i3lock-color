#ifndef _I3LOCK_H
#define _I3LOCK_H

#include <stdbool.h>

// boy i sure hope this doesnt change in the future
#define NANOSECONDS_IN_SECOND 1000000000

/* This macro will only print debug output when started with --debug.
 * This is important because xautolock (for example) closes stdout/stderr by
 * default, so just printing something to stdout will lead to the data ending
 * up on the X11 socket (!). */
#define DEBUG(fmt, ...)                                   \
    do {                                                  \
        if (debug_mode)                                   \
            printf("[i3lock-debug] " fmt, ##__VA_ARGS__); \
    } while (0)

enum e_widget_type
{
    WIDGET_TYPE_INDICATOR,
    WIDGET_TYPE_TEXT,
};

enum e_widget_alignment
{
  TEXT_ALIGN_CENTER,
  TEXT_ALIGN_LEFT,
  TEXT_ALIGN_RIGHT,
};

enum e_line_uses
{
  LINE_USE_OWN_COLOR,
  LINE_USE_RING_COLOR,
  LINE_USE_INSIDE_COLOR,
};

enum e_text_provider
{
  TEXT_PROVIDER_STATIC,
  TEXT_PROVIDER_BUILTIN,
};

enum e_builtin_type
{
  TEXT_BUILTIN_DATETIME,
  TEXT_BUILTIN_LAYOUT,
  TEXT_BUILTIN_STATUS,
  TEXT_BUILTIN_MODIFIER,
};

enum e_status_desc_types
{
  STATUS_VERIFY,
  STATUS_WRONG,
  STATUS_NOINPUT,
};

// Widget description

typedef struct {
    double radius;
    double ring_width;

    char *ring_normal_color;
    char *ring_verify_color;
    char *ring_wrong_color;
    char *inside_normal_color;
    char *inside_verify_color;
    char *inside_wrong_color;
    char *ring_hl_onkey_color;
    char *ring_hl_onbackspace_color;
    char *ring_hl_separator_color;
    char *line_color;

    enum e_line_uses line_use_color;
} t_indicator_description;

typedef struct {
    enum e_text_provider provider;
    union {
        struct {
            enum e_builtin_type type;
            char *format;
        } builtin;
        char static_text[40];
    };
} t_text_description;

typedef struct {
    enum e_widget_type type;
    char x_expr[32];
    char y_expr[32];
    double size;
    enum e_widget_alignment align;
    char color[9];
    char font[32];
    bool show;

    union {
        t_indicator_description indicator;
        t_text_description text;
    };
} t_widget_description;


// Status description

struct t_status_description
{
    char *text;
    char *color;
};

#endif
