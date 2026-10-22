/*
 * Since at least FreeRTOS V7.5.3 uxTopUsedPriority is no longer
 * present in the kernel, so it has to be supplied by other means for
 * OpenOCD's threads awareness.
 *
 * Add this file to your project, and, if you're using --gc-sections,
 * ``--undefined=uxTopUsedPriority'' (or
 * ``-Wl,--undefined=uxTopUsedPriority'' when using gcc for final
 * linking) to your LDFLAGS; same with all the other symbols you need.
 */

#ಅನ್ತರ್ಭಾವ "FreeRTOS.h"
#ಅನ್ತರ್ಭಾವ "esp_attr.h"
#ಅನ್ತರ್ಭಾವ "sdkconfig.h"

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ __GNUC__
    #ವ್ಯಾಖ್ಯಾನಿಸು ಬಳಸಿದ_2    __attribute__( ( ಬಳಸಿದ ) )
#ಇಲ್ಲದಿದ್ದರೆ
    #ವ್ಯಾಖ್ಯಾನಿಸು ಬಳಸಿದ_2
#ಆದರೆ_ಅಂತ್ಯ

/*
 * This file is no longer needed as AFTER FreeRTOS V10.14.1 OpenOCD is fixed in the kernel.
 * #ifdef CONFIG_ESP32_DEBUG_OCDAWARE
 *   const int USED DRAM_ATTR uxTopUsedPriority = configMAX_PRIORITIES - 1;
 * #endif
 */
