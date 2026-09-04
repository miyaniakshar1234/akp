/**
 * ============================================================================
 *  AKP ENGINE - INTERACTIVE CLI PROMPTS MODULE (akp/prompt.h)
 *  Author: Akshar Miyani | AKP Studio
 * ============================================================================
 */

#ifndef AKP_PROMPT_H
#define AKP_PROMPT_H

#ifdef __cplusplus
extern "C" {
#endif

#include "color.h"

#if AKP_OS_WIN
    #include <conio.h>
#else
    #include <termios.h>
    #include <unistd.h>
#endif

static inline bool akp_prompt_confirm(const char* question) {
    akp_init_console();
    printf(AKP_BOLD AKP_GOLD "❓ %s [y/N]: " AKP_RESET, question ? question : "Continue?");
    fflush(stdout);

#if AKP_OS_WIN
    int ch = _getch();
    printf("%c\n", ch);
    return (ch == 'y' || ch == 'Y');
#else
    struct termios oldt, newt;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    int ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    printf("%c\n", ch);
    return (ch == 'y' || ch == 'Y');
#endif
}

static inline void akp_prompt_password(const char* prompt, char* buffer, size_t max_len) {
    if (!buffer || max_len == 0) return;
    akp_init_console();
    printf(AKP_BOLD AKP_NEON_CYAN "🔑 %s " AKP_RESET, prompt ? prompt : "Enter Secret:");
    fflush(stdout);

    size_t idx = 0;
#if AKP_OS_WIN
    while (idx < max_len - 1) {
        int ch = _getch();
        if (ch == '\r' || ch == '\n') break;
        if (ch == '\b') {
            if (idx > 0) {
                idx--;
                printf("\b \b");
                fflush(stdout);
            }
        } else if (ch >= 32 && ch <= 126) {
            buffer[idx++] = (char)ch;
            printf(AKP_NEON_PINK "•" AKP_RESET);
            fflush(stdout);
        }
    }
    buffer[idx] = '\0';
    printf("\n");
#else
    struct termios oldt, newt;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    while (idx < max_len - 1) {
        int ch = getchar();
        if (ch == '\r' || ch == '\n') break;
        if (ch == 127 || ch == '\b') {
            if (idx > 0) {
                idx--;
                printf("\b \b");
                fflush(stdout);
            }
        } else if (ch >= 32 && ch <= 126) {
            buffer[idx++] = (char)ch;
            printf(AKP_NEON_PINK "•" AKP_RESET);
            fflush(stdout);
        }
    }
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    buffer[idx] = '\0';
    printf("\n");
#endif
}

static inline int akp_prompt_select(const char* title, const char* options[], int count) {
    if (!options || count <= 0) return -1;
    akp_init_console();

    int selected = 0;
    bool active = true;

    while (active) {
        printf("\r" AKP_BOLD AKP_NEON_CYAN "🎯 %s (Use ↑/↓ or 1-%d, Enter to pick):" AKP_RESET "\n", 
               title ? title : "Select Option", count);
        
        for (int i = 0; i < count; i++) {
            if (i == selected) {
                printf(AKP_BOLD AKP_NEON_PINK "  ► [%d] %-30s ◄" AKP_RESET "\n", i + 1, options[i]);
            } else {
                printf(AKP_DIM "    [%d] %-30s  " AKP_RESET "\n", i + 1, options[i]);
            }
        }

#if AKP_OS_WIN
        int ch = _getch();
        if (ch == 224 || ch == 0) {
            int code = _getch();
            if (code == 72) { /* UP */
                selected = (selected - 1 + count) % count;
            } else if (code == 80) { /* DOWN */
                selected = (selected + 1) % count;
            }
        } else if (ch == '\r' || ch == '\n') {
            active = false;
        } else if (ch >= '1' && ch < '1' + count) {
            selected = ch - '1';
            active = false;
        }
#else
        struct termios oldt, newt;
        tcgetattr(STDIN_FILENO, &oldt);
        newt = oldt;
        newt.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);
        int ch = getchar();
        if (ch == '\033') {
            getchar(); /* skip '[' */
            int arrow = getchar();
            if (arrow == 'A') selected = (selected - 1 + count) % count; /* UP */
            if (arrow == 'B') selected = (selected + 1) % count; /* DOWN */
        } else if (ch == '\n' || ch == '\r') {
            active = false;
        } else if (ch >= '1' && ch < '1' + count) {
            selected = ch - '1';
            active = false;
        }
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
#endif

        if (active) {
            /* Move cursor up by count + 1 lines to redraw in-place */
            printf("\x1b[%dA", count + 1);
        }
    }

    printf(AKP_BOLD AKP_NEON_GREEN "✔ Selected: %s" AKP_RESET "\n\n", options[selected]);
    return selected;
}

#ifdef __cplusplus
}
#endif

#endif /* AKP_PROMPT_H */
