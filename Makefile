VERSION = 1.00
CFLAGS = -Wall -Wpedantic -Wextra -std=c++11

S001 = code/src/gm_main.cpp
S002 = code/src/gm_run.cpp
S003 = code/src/gm_init.cpp
S004 = code/src/gm_draw.cpp
S005 = code/src/gm_update.cpp
S006 = code/src/gm_event.cpp
S007 = code/src/en_app.cpp
S008 = code/src/en_shader.cpp
S009 = code/src/en_file.cpp
S010 = code/src/en_3d_mdl.cpp

H001 = code/incl/gm_main.h
H002 = code/incl/gm_run.h
H003 = code/incl/gm_glb.h
H004 = code/incl/gm_init.h
H005 = code/incl/gm_draw.h
H006 = code/incl/gm_update.h
H007 = code/incl/gm_event.h
H008 = code/incl/gm_state.h
H009 = code/incl/en_app.h
H010 = code/incl/en_shader.h
H011 = code/incl/en_file.h
H012 = code/incl/en_3d_mdl.h
H013 = code/incl/en_glb.h
H014 = code/incl/en_error.h
H015 = code/incl/gm_error.h

SOURCE = $(S001) $(S002) $(S003) $(S004) $(S005) $(S006) $(S007) $(S008) $(S009) $(S010)
HEADER = $(H001) $(H002) $(H003) $(H004) $(H005) $(H006) $(H007) $(H008) $(H009) $(H010) $(H011) $(H012) $(H013) $(H014) $(H015)
SDL = -lSDL2
OGL = -lGL -lGLEW -lSOIL
OUT = -o 3d_fighter

3d_fighter: $(SOURCE) $(HEADER) $(LIBRARY)
	g++ $(CFLAGS) $(SOURCE) $(LIBRARY) $(SDL) $(OGL) $(OUT) 
