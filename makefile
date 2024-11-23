# ----------------------------
# Makefile Options
# ----------------------------

NAME = COLD
ICON = icon.png
DESCRIPTION = "Winter Survival Game"
COMPRESSED = YES
COMPRESSED_MODE = zx0
ARCHIVED = NO
HAS_PRINTF = NO

CFLAGS = -Wall -Wextra -Oz
CXXFLAGS = -Wall -Wextra -Oz

# ----------------------------

include $(shell cedev-config --makefile)
