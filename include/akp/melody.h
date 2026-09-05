/**
 * ============================================================================
 *  AKP ENGINE - RETRO TERMINAL MELODY SYNTHESIZER (akp/melody.h)
 *  Author: Akshar Miyani | AKP Studio
 * ============================================================================
 */

#ifndef AKP_MELODY_H
#define AKP_MELODY_H

#ifdef __cplusplus
extern "C" {
#endif

#include "color.h"

/* Standard Musical Note Frequencies (Hz) */
#define AKP_NOTE_C4  262
#define AKP_NOTE_CS4 277
#define AKP_NOTE_D4  294
#define AKP_NOTE_DS4 311
#define AKP_NOTE_E4  330
#define AKP_NOTE_F4  349
#define AKP_NOTE_FS4 370
#define AKP_NOTE_G4  392
#define AKP_NOTE_GS4 415
#define AKP_NOTE_A4  440
#define AKP_NOTE_AS4 466
#define AKP_NOTE_B4  494
#define AKP_NOTE_C5  523
#define AKP_NOTE_CS5 554
#define AKP_NOTE_D5  587
#define AKP_NOTE_DS5 622
#define AKP_NOTE_E5  659
#define AKP_NOTE_F5  698
#define AKP_NOTE_G5  784
#define AKP_NOTE_A5  880
#define AKP_NOTE_B5  988
#define AKP_NOTE_C6  1046

static inline void akp_play_tone(int freq_hz, int duration_ms) {
#if AKP_OS_WIN
    if (freq_hz > 0) Beep(freq_hz, duration_ms);
    else Sleep(duration_ms);
#else
    if (freq_hz > 0) { printf("\a"); fflush(stdout); }
    usleep(duration_ms * 1000);
#endif
}

static inline void akp_melody_play(const int* freqs, const int* durations, int count, const char* name) {
    if (!freqs || !durations || count <= 0) return;
    akp_init_console();
    printf(AKP_BOLD AKP_NEON_PINK "🎵 Playing Retro Melody: %s...\n" AKP_RESET, name ? name : "Chiptune");

    for (int i = 0; i < count; i++) {
        akp_play_tone(freqs[i], durations[i]);
    }
}

/* Iconic Tetris (Korobeiniki) Theme */
static inline void akp_melody_tetris(void) {
    int notes[] = {
        AKP_NOTE_E5, AKP_NOTE_B4, AKP_NOTE_C5, AKP_NOTE_D5, AKP_NOTE_C5, AKP_NOTE_B4,
        AKP_NOTE_A4, AKP_NOTE_A4, AKP_NOTE_C5, AKP_NOTE_E5, AKP_NOTE_D5, AKP_NOTE_C5,
        AKP_NOTE_B4, AKP_NOTE_C5, AKP_NOTE_D5, AKP_NOTE_E5, AKP_NOTE_C5, AKP_NOTE_A4, AKP_NOTE_A4
    };
    int durs[] = {
        300, 150, 150, 300, 150, 150,
        300, 150, 150, 300, 150, 150,
        300, 150, 300, 300, 300, 300, 400
    };
    akp_melody_play(notes, durs, sizeof(notes)/sizeof(notes[0]), "Tetris Theme (Korobeiniki)");
}

/* Iconic Nokia Retro Tune */
static inline void akp_melody_nokia(void) {
    int notes[] = {
        AKP_NOTE_E5, AKP_NOTE_D5, AKP_NOTE_FS4, AKP_NOTE_GS4,
        AKP_NOTE_CS5, AKP_NOTE_B4, AKP_NOTE_D4, AKP_NOTE_E4,
        AKP_NOTE_B4, AKP_NOTE_A4, AKP_NOTE_CS4, AKP_NOTE_E4, AKP_NOTE_A4
    };
    int durs[] = {
        150, 150, 250, 250,
        150, 150, 250, 250,
        150, 150, 250, 250, 500
    };
    akp_melody_play(notes, durs, sizeof(notes)/sizeof(notes[0]), "Nokia Retro Chime");
}

/* Star Wars Imperial March Theme */
static inline void akp_melody_starwars(void) {
    int notes[] = {
        AKP_NOTE_G4, AKP_NOTE_G4, AKP_NOTE_G4, AKP_NOTE_DS4, AKP_NOTE_AS4,
        AKP_NOTE_G4, AKP_NOTE_DS4, AKP_NOTE_AS4, AKP_NOTE_G4
    };
    int durs[] = {
        350, 350, 350, 250, 150,
        350, 250, 150, 600
    };
    akp_melody_play(notes, durs, sizeof(notes)/sizeof(notes[0]), "Star Wars Imperial Fanfare");
}

#ifdef __cplusplus
}
#endif

#endif /* AKP_MELODY_H */
