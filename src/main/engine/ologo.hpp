#pragma once

#include "stdint.hpp"
#include "osprites.hpp"
#include "outils.hpp"

class OLogo
{
public:
	OLogo();
	~OLogo();
	void enable(int16_t y);
    void disable();
	void tick();
    void blit();

private:
	// Palm Tree Frame Addresses
	static const uint32_t palm_frames[];

	// Background Palette Entries
	static const uint8_t bg_pal[];
	
    uint8_t entry_start;

    // Y Offset To Draw Logo At
    int16_t y_off;
	
	void setup_sprite1();
	void setup_sprite2();
	void setup_sprite3();
	void setup_sprite4();
	void setup_sprite5();
	void setup_sprite6();
	void setup_sprite7();

	void sprite_logo_bg();
	void sprite_logo_car();
	void sprite_logo_bird1();
	void sprite_logo_bird2();
	void sprite_logo_road();
	void sprite_logo_palm();
	void sprite_logo_text();
};

extern OLogo ologo;