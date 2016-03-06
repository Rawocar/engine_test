VERSION = 1.00
CFLAGS = -Wall -Wpedantic -Wextra -std=c++11

# ----------------------------------------------
# ENGINE
# ----------------------------------------------

# SRC --> ENGINE

ES001 = code/src/en_app.cpp
ES002 = code/src/en_shader.cpp
ES003 = code/src/en_file.cpp
ES004 = code/src/en_3d_mdl.cpp
ES005 = code/src/en_string.cpp
ES006 = code/src/en_math.cpp
ES007 = code/src/en_light.cpp

# HEADER --> ENGINE

EH001 = code/incl/en_app.h
EH002 = code/incl/en_shader.h
EH003 = code/incl/en_file.h
EH004 = code/incl/en_3d_mdl.h
EH005 = code/incl/en_glb.h
EH006 = code/incl/en_error.h
EH007 = code/incl/en_string.h
EH008 = code/incl/en_light.h
EH009 = code/incl/en_math.h

# ----------------------------------------------
# GAME
# ----------------------------------------------

# SRC --> GAME

GS001 = code/src/gm_main.cpp
GS002 = code/src/gm_run.cpp
GS003 = code/src/gm_init.cpp
GS004 = code/src/gm_draw.cpp
GS005 = code/src/gm_update.cpp
GS006 = code/src/gm_event.cpp

# HEADER --> GAME

H015 = code/incl/gm_error.h
H001 = code/incl/gm_main.h
H002 = code/incl/gm_run.h
H003 = code/incl/gm_glb.h
H004 = code/incl/gm_init.h
H005 = code/incl/gm_draw.h
H006 = code/incl/gm_update.h
H007 = code/incl/gm_event.h
H008 = code/incl/gm_state.h

# ----------------------------------------------
# COMPILE
# ----------------------------------------------

E_SRC = $(ES001) $(ES002) $(ES003) $(ES004) $(ES005) $(ES006) $(ES007)
G_SRC = $(GS001) $(GS002) $(GS003) $(GS004) $(GS005) $(GS006) 

E_HEAD = $(EH001) $(EH002) $(EH003) $(EH004) $(EH005) $(EH006) $(EH007) $(EH008) $(EH009)
G_HEAD = $(GH001) $(GH002) $(GH003) $(GH004) $(GH005) $(GH006) $(GH007) $(GH008)

SDL = -lSDL2
OGL = -lGL -lGLEW -lSOIL
LIBRARY = $(SDL) $(OGL)
OUT = -o 3d_fighter

3d_fighter: $(E_SRC) $(G_SRC) $(E_HEAD) $(G_HEAD) $(LIBRARY)
	g++ $(CFLAGS) $(E_SRC) $(G_SRC) $(LIBRARY) $(OUT) 
