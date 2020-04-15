TARGET = cannonball

MAIN_OBJS = \
    src/main/main.o \
    src/main/romloader.o \
    src/main/trackloader.o \
    src/main/roms.o \
    src/main/video.o \
    src/main/utils.o

FRONTEND_OBJS = \
    src/main/frontend/cabdiag.o \
    src/main/frontend/config.o \
    src/main/frontend/menu.o \
    src/main/frontend/ttrial.o

HW_VIDEO_OBJS = \
    src/main/hwvideo/hwroad.o \
    src/main/hwvideo/hwsprites.o \
    src/main/hwvideo/hwtiles.o


HW_AUDIO_OBJS = \
    src/main/hwaudio/segapcm.o \
    src/main/hwaudio/soundchip.o \
    src/main/hwaudio/ym2151.o

SDL_GL_BACKEND = \
    src/main/sdl/audio.o \
    src/main/sdl/timer.o \
    src/main/sdl/input.o \
    src/main/sdl/renderbase.o \
    src/main/sdl/rendergl.o

SDL_BACKEND = \
    src/main/sdl/audio.o \
    src/main/sdl/timer.o \
    src/main/sdl/input.o \
    src/main/sdl/renderbase.o \
    src/main/sdl/rendersw.o

SRC_ENGINE = \
    src/main/engine/oanimseq.o \
    src/main/engine/oattractai.o \
    src/main/engine/obonus.o \
    src/main/engine/ocrash.o \
    src/main/engine/oferrari.o \
    src/main/engine/ohiscore.o \
    src/main/engine/ohud.o \
    src/main/engine/oinitengine.o \
    src/main/engine/oinputs.o \
    src/main/engine/olevelobjs.o \
    src/main/engine/ologo.o \
    src/main/engine/omap.o \
    src/main/engine/omusic.o \
    src/main/engine/ooutputs.o \
    src/main/engine/opalette.o \
    src/main/engine/oroad.o \
    src/main/engine/osmoke.o \
    src/main/engine/osprite.o \
    src/main/engine/osprites.o \
    src/main/engine/ostats.o \
    src/main/engine/otiles.o \
    src/main/engine/otraffic.o \
    src/main/engine/outils.o \
    src/main/engine/outrun.o \
    src/main/directx/ffeedback.o \
    src/main/cannonboard/asyncserial.o \
    src/main/cannonboard/interface.o

SRC_ENGINE_AUDIO = \
    src/main/engine/audio/osound.o \
    src/main/engine/audio/osoundint.o


OBJS = \
    $(MAIN_OBJS) \
    $(FRONTEND_OBJS) \
    $(HW_VIDEO_OBJS) \
    $(HW_AUDIO_OBJS) \
    $(SDL_BACKEND) \
    $(SRC_ENGINE) \
    $(SRC_ENGINE_AUDIO)

CANNONBALL_CFLAGS = -DNO_BOOST

PSPSDK=$(shell psp-config --pspsdk-path)
PSPBIN = $(PSPSDK)/../bin

SDL_CFLAGS = $(shell $(PSPBIN)/sdl-config --cflags)
SDL_LIBS = $(shell $(PSPBIN)/sdl-config --static-libs)

INCDIR = src/main
CFLAGS = -O2 -G0 -Wall $(CANNONBALL_CFLAGS) $(SDL_CFLAGS)
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti
ASFLAGS = $(CFLAGS)

LIBDIR =
LIBS = $(SDL_LIBS) -lstdc++ -lm

EXTRA_TARGETS = EBOOT.PBP
PSP_EBOOT_TITLE = Cannonball

include $(PSPSDK)/lib/build.mak

