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

#அந்தர்பாவ "FreeRTOS.h"
#அந்தர்பாவ "esp_attr.h"
#அந்தர்பாவ "sdkconfig.h"

#ifdef __GNUC__
    #define USED    __attribute__( ( used ) )
#இல்லையெனில்
    #define USED
#endif

/*
 * This file is no longer needed as AFTER FreeRTOS V10.14.1 OpenOCD is fixed in the kernel.
 * #ifdef CONFIG_ESP32_DEBUG_OCDAWARE
 *   const int USED DRAM_ATTR uxTopUsedPriority = configMAX_PRIORITIES - 1;
 * #endif
 */
