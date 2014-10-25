# List of all the board related files.
BOARDSRC += ../common/common.c
BOARDSRC += ../common/board.c
BOARDSRC += ../common/stm32f0xx_flash.c

# Required include directories
BOARDINC = ../common

include ../common/SSD1306/driver.mk
