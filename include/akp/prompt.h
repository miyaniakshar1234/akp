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

#ifdef __cplusplus
}
#endif

#endif /* AKP_PROMPT_H */
