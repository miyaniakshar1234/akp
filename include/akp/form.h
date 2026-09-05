/**
 * ============================================================================
 *  AKP ENGINE - INTERACTIVE FORM & INPUT WIZARD (akp/form.h)
 *  Author: Akshar Miyani | AKP Studio
 * ============================================================================
 */

#ifndef AKP_FORM_H
#define AKP_FORM_H

#ifdef __cplusplus
extern "C" {
#endif

#include "color.h"
#include <ctype.h>

#define AKP_FORM_MAX_FIELDS 16
#define AKP_FORM_BUFFER_SZ  128

typedef enum {
    AKP_FIELD_TEXT,
    AKP_FIELD_INT,
    AKP_FIELD_CONFIRM
} akp_field_type_t;

typedef struct {
    char label[64];
    akp_field_type_t type;
    char value[AKP_FORM_BUFFER_SZ];
    int int_val;
    bool bool_val;
} akp_form_field_t;

typedef struct {
    char title[64];
    int field_count;
    akp_form_field_t fields[AKP_FORM_MAX_FIELDS];
} akp_form_t;

static inline akp_form_t* akp_form_create(const char* title) {
    akp_form_t* f = (akp_form_t*)calloc(1, sizeof(akp_form_t));
    if (!f) return NULL;
    strncpy(f->title, title ? title : "Input Form", sizeof(f->title) - 1);
    f->field_count = 0;
    return f;
}

static inline void akp_form_add_text(akp_form_t* f, const char* label, const char* default_val) {
    if (!f || f->field_count >= AKP_FORM_MAX_FIELDS) return;
    akp_form_field_t* field = &f->fields[f->field_count++];
    strncpy(field->label, label, sizeof(field->label) - 1);
    field->type = AKP_FIELD_TEXT;
    if (default_val) strncpy(field->value, default_val, sizeof(field->value) - 1);
}

static inline void akp_form_add_int(akp_form_t* f, const char* label, int default_val) {
    if (!f || f->field_count >= AKP_FORM_MAX_FIELDS) return;
    akp_form_field_t* field = &f->fields[f->field_count++];
    strncpy(field->label, label, sizeof(field->label) - 1);
    field->type = AKP_FIELD_INT;
    field->int_val = default_val;
    snprintf(field->value, sizeof(field->value), "%d", default_val);
}

static inline void akp_form_add_confirm(akp_form_t* f, const char* label, bool default_val) {
    if (!f || f->field_count >= AKP_FORM_MAX_FIELDS) return;
    akp_form_field_t* field = &f->fields[f->field_count++];
    strncpy(field->label, label, sizeof(field->label) - 1);
    field->type = AKP_FIELD_CONFIRM;
    field->bool_val = default_val;
    snprintf(field->value, sizeof(field->value), "%s", default_val ? "Yes" : "No");
}

static inline void akp_form_render_header(akp_form_t* f) {
    akp_init_console();
    printf("\n" AKP_NEON_CYAN "╭───────────────────────────────────────────────────────────────╮\n" AKP_RESET);
    printf(AKP_NEON_CYAN "│ " AKP_BOLD AKP_NEON_YELLOW "📋 %-57s " AKP_RESET AKP_NEON_CYAN "│\n" AKP_RESET, f->title);
    printf(AKP_NEON_CYAN "├───────────────────────────────────────────────────────────────┤\n" AKP_RESET);
}

static inline void akp_form_execute(akp_form_t* f) {
    if (!f) return;
    akp_form_render_header(f);

    for (int i = 0; i < f->field_count; i++) {
        akp_form_field_t* field = &f->fields[i];
        printf(AKP_NEON_CYAN "│ " AKP_BOLD AKP_FG_WHITE "%-24s: " AKP_RESET, field->label);
        fflush(stdout);

        char input_buf[AKP_FORM_BUFFER_SZ];
        if (fgets(input_buf, sizeof(input_buf), stdin)) {
            /* Trim trailing newline */
            size_t len = strlen(input_buf);
            while (len > 0 && (input_buf[len - 1] == '\r' || input_buf[len - 1] == '\n')) {
                input_buf[--len] = '\0';
            }
            if (len > 0) {
                strncpy(field->value, input_buf, sizeof(field->value) - 1);
                if (field->type == AKP_FIELD_INT) {
                    field->int_val = atoi(input_buf);
                } else if (field->type == AKP_FIELD_CONFIRM) {
                    field->bool_val = (input_buf[0] == 'y' || input_buf[0] == 'Y');
                }
            }
        }
    }
    printf(AKP_NEON_CYAN "╰───────────────────────────────────────────────────────────────╯\n" AKP_RESET);
    printf(AKP_BOLD AKP_NEON_GREEN "✔ Form inputs successfully captured!\n\n" AKP_RESET);
}

static inline const char* akp_form_get_text(akp_form_t* f, int index) {
    if (!f || index < 0 || index >= f->field_count) return "";
    return f->fields[index].value;
}

static inline int akp_form_get_int(akp_form_t* f, int index) {
    if (!f || index < 0 || index >= f->field_count) return 0;
    return f->fields[index].int_val;
}

static inline bool akp_form_get_bool(akp_form_t* f, int index) {
    if (!f || index < 0 || index >= f->field_count) return false;
    return f->fields[index].bool_val;
}

static inline void akp_form_free(akp_form_t* f) {
    if (f) free(f);
}

#ifdef __cplusplus
}
#endif

#endif /* AKP_FORM_H */
