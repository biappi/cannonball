#include "engine/ologo.hpp"

// Code to setup Outrun Logo Sprite In Attract Mode
//
// Note the logo is made of multiple sprite components

OLogo ologo;

const uint32_t OLogo::palm_frames[] = 
{ 
    SPRITE_LOGO_PALM1, SPRITE_LOGO_PALM2, SPRITE_LOGO_PALM3, SPRITE_LOGO_PALM2, 
    SPRITE_LOGO_PALM1, SPRITE_LOGO_PALM2, SPRITE_LOGO_PALM3, SPRITE_LOGO_PALM2,
};

const uint8_t OLogo::bg_pal[] = { 0x9A, 0x9B, 0x9C, 0x9D, 0x9E, 0x9A, 0x9B, 0x9C };

OLogo::OLogo()
{
}

OLogo::~OLogo()
{
}

void OLogo::enable(int16_t y)
{
    y_off = -y;

     entry_start = OSprites::SPRITE_ENTRIES - 0x10;

    // Enable block of sprites
    for (int i = entry_start; i < entry_start + 7; i++)
    {
        osprites.jump_table[i].init(i);
    }

    setup_sprite1(); 
    setup_sprite2();
    setup_sprite3();
    setup_sprite4();
    setup_sprite5();
    setup_sprite6();
    setup_sprite7();
}

void OLogo::disable()
{
    // Enable block of sprites
    for (int i = entry_start; i < entry_start + 7; i++)
    {
        osprites.jump_table[i].control &= ~OSprites::ENABLE;
    }
}

void OLogo::tick()
{
    sprite_logo_bg();
    sprite_logo_car();
    sprite_logo_bird1();
    sprite_logo_bird2();
    sprite_logo_road();
    sprite_logo_palm();
    sprite_logo_text();
}

// Animated Background Oval Sprite.
void OLogo::setup_sprite1()
{
    oentry *e = &osprites.jump_table[entry_start + 0];
    e->x = 0;
    e->y = 0x70 - y_off;
    e->road_priority = 0xFF;
    e->priority = 0x1FA;
    e->zoom = 0x7F;
    e->pal_src = 0x99;
    e->addr = SPRITE_LOGO_BG;
    osprites.map_palette(e);
}

// Sprite Car Graphic
void OLogo::setup_sprite2()
{
    oentry *e = &osprites.jump_table[entry_start + 1];
    e->x = -3;
    e->y = 0x88 - y_off;
    e->road_priority = 0x100;
    e->priority = 0x1FB;
    e->zoom = 0x7F;
    e->pal_src = 0x6E;
    e->addr = SPRITE_LOGO_CAR;
    osprites.map_palette(e);
}

// Sprite Flying Bird #1
void OLogo::setup_sprite3()
{
    oentry *e = &osprites.jump_table[entry_start + 2];
    e->x = 0x8;
    e->y = 0x4E - y_off;
    e->road_priority = 0x102;
    e->priority = 0x1FD;
    e->zoom = 0x7F;
    e->counter = 0;
    e->pal_src = 0x8B;
    e->addr = SPRITE_LOGO_BIRD1;
    osprites.map_palette(e);
}

// Sprite Flying Bird #2
void OLogo::setup_sprite4()
{
    oentry *e = &osprites.jump_table[entry_start + 3];
    e->x = 0x8;
    e->y = 0x4E - y_off;
    e->road_priority = 0x102;
    e->priority = 0x1FD;
    e->zoom = 0x7F;
    e->counter = 0x20;
    e->pal_src = 0x8C;
    e->addr = SPRITE_LOGO_BIRD2;
    osprites.map_palette(e);
}

// Sprite Road Base Section
void OLogo::setup_sprite5()
{
    oentry *e = &osprites.jump_table[entry_start + 4];
    e->x = -0x20;
    e->y = 0x8F - y_off;
    e->road_priority = 0x101;
    e->priority = 0x1FC;
    e->zoom = 0x7F;
    e->pal_src = 0x6E;
    e->addr = SPRITE_LOGO_BASE;
    osprites.map_palette(e);
}

// Palm Tree
void OLogo::setup_sprite6()
{
    oentry *e = &osprites.jump_table[entry_start + 5];
    e->x = -0x40;
    e->y = 0x6D - y_off;
    e->road_priority = 0x102;
    e->priority = 0x1FD;
    e->zoom = 0x7F;
    e->pal_src = 0x65;
    e->addr = SPRITE_LOGO_PALM1;
    osprites.map_palette(e);
}

// OutRun logo text
void OLogo::setup_sprite7()
{
    oentry *e = &osprites.jump_table[entry_start + 6];
    e->x = 0x11;
    e->y = 0x65 - y_off;
    e->road_priority = 0x103;
    e->priority = 0x1FE;
    e->zoom = 0x7F;
    e->counter = 0;
    e->pal_src = 0x65;
    e->addr = SPRITE_LOGO_TEXT;
    osprites.map_palette(e);
}

// Draw Background of OutRun logo in attract mode
void OLogo::sprite_logo_bg()
{
    oentry *e = &osprites.jump_table[entry_start + 0];
    e->reload++;
    uint16_t d0 = e->reload;
    uint16_t d1 = d0 - 1;
    d1 ^= d0;

    // Map new palette
    if (d1 & BIT_3)
    {
        e->pal_src = bg_pal[outils::random() & 7];
        osprites.map_palette(e);
    }

    osprites.do_spr_order_shadows(e);
}

void OLogo::sprite_logo_car()
{
    oentry *e = &osprites.jump_table[entry_start + 1];
    // Flicker background palette of car
    e->reload++;
    e->pal_src = ((e->reload & 2) >> 1) ? 0x8A : 0x6E;
    osprites.map_palette(e);
    osprites.do_spr_order_shadows(e);
}

void OLogo::sprite_logo_bird1()
{
    oentry *e = &osprites.jump_table[entry_start + 2];
    e->counter++;

    // Set Bird X Value
    uint16_t index = (e->counter << 1) & 0xFF;
    int8_t bird_x = roms.rom0.read8(DATA_MOVEMENT + index); // Note we sign the value here
    int8_t zoom = bird_x >> 3;
    e->x = (bird_x >> 3) + 8;

    // Set Zoom Lookup
    e->zoom = zoom + 0x70;

    // Set Bird Y Value
    index = (index << 1) & 0xFF;
    int8_t bird_y = roms.rom0.read8(DATA_MOVEMENT + index); // Note we sign the value here
    e->y = (bird_y >> 5) + 0x4E - y_off;

    // Set Frame
    e->reload++;
    uint16_t frame = (e->reload & 4) >> 2;
    e->addr = frame ? SPRITE_LOGO_BIRD2 : SPRITE_LOGO_BIRD1;
    osprites.do_spr_order_shadows(e);
}

void OLogo::sprite_logo_bird2()
{
    oentry *e = &osprites.jump_table[entry_start + 3];
    e->counter++;

    // Set Bird X Value
    uint16_t index = (e->counter << 1) & 0xFF;
    int8_t bird_x = roms.rom0.read8(DATA_MOVEMENT + index); // Note we sign the value here
    int8_t zoom = bird_x >> 3;
    e->x = (bird_x >> 3) - 2; // Different from sprite_logo_bird1

    // Set Zoom Lookup
    e->zoom = zoom + 0x70;

    // Set Bird Y Value
    index = (index << 1) & 0xFF;
    int8_t bird_y = roms.rom0.read8(DATA_MOVEMENT + index); // Note we sign the value here
    e->y = (bird_y >> 5) + 0x52 - y_off; // Different from sprite_logo_bird1

    // Set Frame
    e->reload++;
    uint16_t frame = (e->reload & 4) >> 2;
    e->addr = frame ? SPRITE_LOGO_BIRD2 : SPRITE_LOGO_BIRD1;
    osprites.do_spr_order_shadows(e);
}

void OLogo::sprite_logo_road()
{
    osprites.do_spr_order_shadows(&osprites.jump_table[entry_start + 4]); 
}

void OLogo::sprite_logo_palm()
{
    oentry *e = &osprites.jump_table[entry_start + 5]; 
    e->reload++; // Increment frame number
    e->addr = palm_frames[(e->reload & 0xE) >> 1];
    osprites.do_spr_order_shadows(e);
}

void OLogo::sprite_logo_text()
{
    osprites.do_spr_order_shadows(&osprites.jump_table[entry_start + 6]); 
}

// Blit Only: Used when frame skipping
void OLogo::blit()
{
    for (int i = 0; i < 7; i++)
        osprites.do_spr_order_shadows(&osprites.jump_table[entry_start + i]);
}
