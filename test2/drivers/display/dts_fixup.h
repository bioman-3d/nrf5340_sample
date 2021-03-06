/*
 * Copyright (c) 2019 Jan Van Winkel <jan.van_winkel@dxplore.eu>
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifdef DT_INST_0_ILITEK_ILI9340_LABEL
#define DISPLAY_DEV_NAME DT_INST_0_ILITEK_ILI9340_LABEL
#endif

#ifdef DT_INST_0_SOLOMON_SSD1306FB_LABEL
#define DISPLAY_DEV_NAME DT_INST_0_SOLOMON_SSD1306FB_LABEL
#endif

#ifdef DT_INST_0_GOODDISPLAY_GDEH0213B1_LABEL
#define DISPLAY_DEV_NAME DT_INST_0_GOODDISPLAY_GDEH0213B1_LABEL
#endif

#ifdef DT_INST_0_SITRONIX_ST7789V_LABEL
#define DISPLAY_DEV_NAME DT_INST_0_SITRONIX_ST7789V_LABEL
#endif

#ifdef DT_INST_0_FSL_IMX6SX_LCDIF_LABEL
#define DISPLAY_DEV_NAME DT_INST_0_FSL_IMX6SX_LCDIF_LABEL
#endif

#ifdef CONFIG_SDL_DISPLAY_DEV_NAME
#define DISPLAY_DEV_NAME CONFIG_SDL_DISPLAY_DEV_NAME
#endif

#ifdef CONFIG_DUMMY_DISPLAY_DEV_NAME
#define DISPLAY_DEV_NAME CONFIG_DUMMY_DISPLAY_DEV_NAME
#endif
