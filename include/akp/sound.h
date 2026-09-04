/**
 * ============================================================================
 *  AKP ENGINE - RETRO AUDIO EFFECTS MODULE (akp/sound.h)
 *  Author: Akshar Miyani | AKP Studio
 * ============================================================================
 */

#ifndef AKP_SOUND_H
#define AKP_SOUND_H

#ifdef __cplusplus
extern "C" {
#endif

#include "color.h"

static inline void akp_sound_coin(void) {
#if AKP_OS_WIN
    Beep(988, 100);  /* B5 */
    Beep(1319, 250); /* E6 */
#else
    printf("\a"); fflush(stdout);
#endif
}

static inline void akp_sound_success(void) {
#if AKP_OS_WIN
    Beep(523, 100);  /* C5 */
    Beep(659, 100);  /* E5 */
    Beep(784, 150);  /* G5 */
    Beep(1046, 250); /* C6 */
#else
    printf("\a"); fflush(stdout);
#endif
}

static inline void akp_sound_alert(void) {
#if AKP_OS_WIN
    Beep(440, 200);
    Beep(330, 250);
#else
    printf("\a"); fflush(stdout);
#endif
}

static inline void akp_sound_fanfare(void) {
#if AKP_OS_WIN
    Beep(587, 120); /* D5 */
    Beep(587, 120);
    Beep(587, 120);
    Beep(784, 350); /* G5 */
#else
    printf("\a"); fflush(stdout);
#endif
}

#ifdef __cplusplus
}
#endif

#endif /* AKP_SOUND_H */

/* Verified: 2026-09-04 23:29:41 */
