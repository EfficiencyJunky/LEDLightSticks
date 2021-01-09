/*-------------------------------------------------------------------------------------------------------*
 *                          GRADIENT PALETTES                                                            *
 * Below are a handful of Gradient Palettes that make it easier to apply a range of colors               *
 *        to an animation without changing the animation itself                                          *
 * A great resource on creating color palettes here: https://www.youtube.com/watch?v=Ukq0tH2Tnkc         *
 * Here's a great website for creating palettes (multiply position by 2.55): https://cssgradient.io/     *
 * Another great site for creating palettes: https://coolors.co/gradient-palette/f44369-3e3b92?number=7  *
 * Or find a pallete someone else has made here: http://soliton.vm.bytemark.co.uk/pub/cpt-city/          *
 * In order to use CPT-City you'll need to use the PaletteKnife Bookmarklet                              *
 * Get the Bookmarklet here: http://fastled.io/tools/paletteknife/                                       *
 *-------------------------------------------------------------------------------------------------------*/

#ifndef GradientPalettes_h
#define GradientPalettes_h

// Gradient Color Palette definitions for 33 different cpt-city color palettes.
//    956 bytes of PROGMEM for all of the palettes together,
//   +618 bytes of PROGMEM for gradient palette code (AVR).
//  1,494 bytes total for all 34 color palettes and associated code.

// Gradient palette "ib_jul01_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/ing/xmas/tn/ib_jul01.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 16 bytes of program space.


DEFINE_GRADIENT_PALETTE( ib_jul01_gp ) {
    0, 194,  1,  1,
   94,   1, 29, 18,
  132,  57,131, 28,
  255, 113,  1,  1};



// Gradient palette "es_vintage_57_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/es/vintage/tn/es_vintage_57.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 20 bytes of program space.

DEFINE_GRADIENT_PALETTE( es_vintage_57_gp ) {
    0,   2,  1,  1,
   53,  18,  1,  0,
  104,  69, 29,  1,
  153, 167,135, 10,
  255,  46, 56,  4};

// Gradient palette "es_vintage_01_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/es/vintage/tn/es_vintage_01.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 32 bytes of program space.

DEFINE_GRADIENT_PALETTE( es_vintage_01_gp ) {
    0,   4,  1,  1,
   51,  16,  0,  1,
   76,  97,104,  3,
  101, 255,131, 19,
  127,  67,  9,  4,
  153,  16,  0,  1,
  229,   4,  1,  1,
  255,   4,  1,  1};

// Gradient palette "es_rivendell_15_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/es/rivendell/tn/es_rivendell_15.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 20 bytes of program space.

DEFINE_GRADIENT_PALETTE( es_rivendell_15_gp ) {
    0,   1, 14,  5,
  101,  16, 36, 14,
  165,  56, 68, 30,
  242, 150,156, 99,
  255, 150,156, 99};

// Gradient palette "rgi_15_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/ds/rgi/tn/rgi_15.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 36 bytes of program space.

DEFINE_GRADIENT_PALETTE( rgi_15_gp ) {
    0,   4,  1, 31,
   31,  55,  1, 16,
   63, 197,  3,  7,
   95,  59,  2, 17,
  127,   6,  2, 34,
  159,  39,  6, 33,
  191, 112, 13, 32,
  223,  56,  9, 35,
  255,  22,  6, 38};

// Gradient palette "retro2_16_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/ma/retro2/tn/retro2_16.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 8 bytes of program space.

DEFINE_GRADIENT_PALETTE( retro2_16_gp ) {
    0, 188,135,  1,
  255,  46,  7,  1};

// Gradient palette "Analogous_1_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/nd/red/tn/Analogous_1.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 20 bytes of program space.

DEFINE_GRADIENT_PALETTE( Analogous_1_gp ) {
    0,   3,  0,255,
   63,  23,  0,255,
  127,  67,  0,255,
  191, 142,  0, 45,
  255, 255,  0,  0};

// Gradient palette "es_pinksplash_08_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/es/pink_splash/tn/es_pinksplash_08.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 20 bytes of program space.

DEFINE_GRADIENT_PALETTE( es_pinksplash_08_gp ) {
    0, 126, 11,255,
  127, 197,  1, 22,
  175, 210,157,172,
  221, 157,  3,112,
  255, 157,  3,112};

// Gradient palette "es_pinksplash_07_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/es/pink_splash/tn/es_pinksplash_07.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 28 bytes of program space.

DEFINE_GRADIENT_PALETTE( es_pinksplash_07_gp ) {
    0, 229,  1,  1,
   61, 242,  4, 63,
  101, 255, 12,255,
  127, 249, 81,252,
  153, 255, 11,235,
  193, 244,  5, 68,
  255, 232,  1,  5};

// Gradient palette "Coral_reef_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/nd/other/tn/Coral_reef.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 24 bytes of program space.

DEFINE_GRADIENT_PALETTE( Coral_reef_gp ) {
    0,  40,199,197,
   50,  10,152,155,
   96,   1,111,120,
   96,  43,127,162,
  139,  10, 73,111,
  255,   1, 34, 71};

// Gradient palette "es_ocean_breeze_068_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/es/ocean_breeze/tn/es_ocean_breeze_068.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 24 bytes of program space.

DEFINE_GRADIENT_PALETTE( es_ocean_breeze_068_gp ) {
    0, 100,156,153,
   51,   1, 99,137,
  101,   1, 68, 84,
  104,  35,142,168,
  178,   0, 63,117,
  255,   1, 10, 10};

// Gradient palette "es_ocean_breeze_036_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/es/ocean_breeze/tn/es_ocean_breeze_036.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 16 bytes of program space.

DEFINE_GRADIENT_PALETTE( es_ocean_breeze_036_gp ) {
    0,   1,  6,  7,
   89,   1, 99,111,
  153, 144,209,255,
  255,   0, 73, 82};

// Gradient palette "departure_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/mjf/tn/departure.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 88 bytes of program space.

DEFINE_GRADIENT_PALETTE( departure_gp ) {
    0,   8,  3,  0,
   42,  23,  7,  0,
   63,  75, 38,  6,
   84, 169, 99, 38,
  106, 213,169,119,
  116, 255,255,255,
  138, 135,255,138,
  148,  22,255, 24,
  170,   0,255,  0,
  191,   0,136,  0,
  212,   0, 55,  0,
  255,   0, 55,  0};

// Gradient palette "es_landscape_64_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/es/landscape/tn/es_landscape_64.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 36 bytes of program space.

DEFINE_GRADIENT_PALETTE( es_landscape_64_gp ) {
    0,   0,  0,  0,
   37,   2, 25,  1,
   76,  15,115,  5,
  127,  79,213,  1,
  128, 126,211, 47,
  130, 188,209,247,
  153, 144,182,205,
  204,  59,117,250,
  255,   1, 37,192};

// Gradient palette "es_landscape_33_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/es/landscape/tn/es_landscape_33.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 24 bytes of program space.

DEFINE_GRADIENT_PALETTE( es_landscape_33_gp ) {
    0,   1,  5,  0,
   19,  32, 23,  1,
   38, 161, 55,  1,
   63, 229,144,  1,
   66,  39,142, 74,
  255,   1,  4,  1};

// Gradient palette "rainbowsherbet_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/ma/icecream/tn/rainbowsherbet.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 28 bytes of program space.

DEFINE_GRADIENT_PALETTE( rainbowsherbet_gp ) {
    0, 255, 33,  4,
   43, 255, 68, 25,
   86, 255,  7, 25,
  127, 255, 82,103,
  170, 255,255,242,
  209,  42,255, 22,
  255,  87,255, 65};

// Gradient palette "gr65_hult_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/hult/tn/gr65_hult.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 24 bytes of program space.

DEFINE_GRADIENT_PALETTE( gr65_hult_gp ) {
    0, 247,176,247,
   48, 255,136,255,
   89, 220, 29,226,
  160,   7, 82,178,
  216,   1,124,109,
  255,   1,124,109};

// Gradient palette "gr64_hult_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/hult/tn/gr64_hult.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 32 bytes of program space.

DEFINE_GRADIENT_PALETTE( gr64_hult_gp ) {
    0,   1,124,109,
   66,   1, 93, 79,
  104,  52, 65,  1,
  130, 115,127,  1,
  150,  52, 65,  1,
  201,   1, 86, 72,
  239,   0, 55, 45,
  255,   0, 55, 45};

// Gradient palette "GMT_drywet_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/gmt/tn/GMT_drywet.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 28 bytes of program space.

DEFINE_GRADIENT_PALETTE( GMT_drywet_gp ) {
    0,  47, 30,  2,
   42, 213,147, 24,
   84, 103,219, 52,
  127,   3,219,207,
  170,   1, 48,214,
  212,   1,  1,111,
  255,   1,  7, 33};

// // Gradient palette "ib15_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/ing/general/tn/ib15.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 24 bytes of program space.

DEFINE_GRADIENT_PALETTE( ib15_gp ) {
    0, 113, 91,147,
   72, 157, 88, 78,
   89, 208, 85, 33,
  107, 255, 29, 11,
  141, 137, 31, 39,
  255,  59, 33, 89};

// Gradient palette "Fuschia_7_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/ds/fuschia/tn/Fuschia-7.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 20 bytes of program space.

DEFINE_GRADIENT_PALETTE( Fuschia_7_gp ) {
    0,  43,  3,153,
   63, 100,  4,103,
  127, 188,  5, 66,
  191, 161, 11,115,
  255, 135, 20,182};

// Gradient palette "es_emerald_dragon_08_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/es/emerald_dragon/tn/es_emerald_dragon_08.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 16 bytes of program space.

DEFINE_GRADIENT_PALETTE( es_emerald_dragon_08_gp ) {
    0,  97,255,  1,
  101,  47,133,  1,
  178,  13, 43,  1,
  255,   2, 10,  1};

// Gradient palette "lava_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/neota/elem/tn/lava.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 52 bytes of program space.

DEFINE_GRADIENT_PALETTE( lava_gp ) {
    0,   0,  0,  0,
   46,  18,  0,  0,
   96, 113,  0,  0,
  108, 142,  3,  1,
  119, 175, 17,  1,
  146, 213, 44,  2,
  174, 255, 82,  4,
  188, 255,115,  4,
  202, 255,156,  4,
  218, 255,203,  4,
  234, 255,255,  4,
  244, 255,255, 71,
  255, 255,255,255};

// Gradient palette "fire_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/neota/elem/tn/fire.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 28 bytes of program space.

DEFINE_GRADIENT_PALETTE( fire_gp ) {
    0,   1,  1,  0,
   76,  32,  5,  0,
  146, 192, 24,  0,
  197, 220,105,  5,
  240, 252,255, 31,
  250, 252,255,111,
  255, 255,255,255};

// Gradient palette "Colorfull_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/nd/atmospheric/tn/Colorfull.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 44 bytes of program space.

DEFINE_GRADIENT_PALETTE( Colorfull_gp ) {
    0,  10, 85,  5,
   25,  29,109, 18,
   60,  59,138, 42,
   93,  83, 99, 52,
  106, 110, 66, 64,
  109, 123, 49, 65,
  113, 139, 35, 66,
  116, 192,117, 98,
  124, 255,255,137,
  168, 100,180,155,
  255,  22,121,174};

// Gradient palette "Magenta_Evening_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/nd/atmospheric/tn/Magenta_Evening.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 28 bytes of program space.

DEFINE_GRADIENT_PALETTE( Magenta_Evening_gp ) {
    0,  71, 27, 39,
   31, 130, 11, 51,
   63, 213,  2, 64,
   70, 232,  1, 66,
   76, 252,  1, 69,
  108, 123,  2, 51,
  255,  46,  9, 35};

// Gradient palette "Pink_Purple_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/nd/atmospheric/tn/Pink_Purple.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 44 bytes of program space.

DEFINE_GRADIENT_PALETTE( Pink_Purple_gp ) {
    0,  19,  2, 39,
   25,  26,  4, 45,
   51,  33,  6, 52,
   76,  68, 62,125,
  102, 118,187,240,
  109, 163,215,247,
  114, 217,244,255,
  122, 159,149,221,
  149, 113, 78,188,
  183, 128, 57,155,
  255, 146, 40,123};

// Gradient palette "Sunset_Real_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/nd/atmospheric/tn/Sunset_Real.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 28 bytes of program space.

DEFINE_GRADIENT_PALETTE( Sunset_Real_gp ) {
    0, 120,  0,  0,
   22, 179, 22,  0,
   51, 255,104,  0,
   85, 167, 22, 18,
  135, 100,  0,103,
  198,  16,  0,130,
  255,   0,  0,160};

// Gradient palette "es_autumn_19_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/es/autumn/tn/es_autumn_19.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 52 bytes of program space.

DEFINE_GRADIENT_PALETTE( es_autumn_19_gp ) {
    0,  26,  1,  1,
   51,  67,  4,  1,
   84, 118, 14,  1,
  104, 137,152, 52,
  112, 113, 65,  1,
  122, 133,149, 59,
  124, 137,152, 52,
  135, 113, 65,  1,
  142, 139,154, 46,
  163, 113, 13,  1,
  204,  55,  3,  1,
  249,  17,  1,  1,
  255,  17,  1,  1};

// Gradient palette "BlacK_Blue_Magenta_White_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/nd/basic/tn/BlacK_Blue_Magenta_White.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 28 bytes of program space.

DEFINE_GRADIENT_PALETTE( BlacK_Blue_Magenta_White_gp ) {
    0,   0,  0,  0,
   42,   0,  0, 45,
   84,   0,  0,255,
  127,  42,  0,255,
  170, 255,  0,255,
  212, 255, 55,255,
  255, 255,255,255};

// Gradient palette "BlacK_Magenta_Red_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/nd/basic/tn/BlacK_Magenta_Red.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 20 bytes of program space.

DEFINE_GRADIENT_PALETTE( BlacK_Magenta_Red_gp ) {
    0,   0,  0,  0,
   63,  42,  0, 45,
  127, 255,  0,255,
  191, 255,  0, 45,
  255, 255,  0,  0};


// RENAMED THIS ONE AND RELOCATED TO FIRE ANIMATIONS DOWN BELOW
// Gradient palette "BlacK_Red_Magenta_Yellow_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/nd/basic/tn/BlacK_Red_Magenta_Yellow.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 28 bytes of program space.

// DEFINE_GRADIENT_PALETTE( BlacK_Red_Magenta_Yellow_gp ) {
//     0,   0,  0,  0,
//    42,  42,  0,  0,
//    84, 255,  0,  0,
//   127, 255,  0, 45,
//   170, 255,  0,255,
//   212, 255, 55, 45,
//   255, 255,255,  0};



// Gradient palette "Blue_Cyan_Yellow_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/nd/basic/tn/Blue_Cyan_Yellow.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 20 bytes of program space.

DEFINE_GRADIENT_PALETTE( Blue_Cyan_Yellow_gp ) {
    0,   0,  0,255,
   63,   0, 55,255,
  127,   0,255,255,
  191,  42,255, 45,
  255, 255,255,  0};

  // Gradient palette "bhw1_28_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/bhw/bhw1/tn/bhw1_28.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 32 bytes of program space.

DEFINE_GRADIENT_PALETTE( bhw1_28_gp ) {
    0,  75,  1,221,
   30, 252, 73,255,
   48, 169,  0,242,
  119,   0,149,242,
  170,  43,  0,242,
  206, 252, 73,255,
  232,  78, 12,214,
  255,   0,149,242};






// Single array of defined cpt-city color palettes.
// This will let us programmatically choose one based on
// a number, rather than having to activate each explicitly 
// by name every time.
// Since it is const, this array could also be moved 
// into PROGMEM to save SRAM, but for simplicity of illustration
// we'll keep it in a regular SRAM array.
//
// This list of color palettes acts as a "playlist"; you can
// add or delete, or re-arrange as you wish.
// const TProgmemRGBGradientPalettePtr gGradientPalettes[] = {
//     bhw1_28_gp,
//     Sunset_Real_gp,
//     es_rivendell_15_gp,
//     es_ocean_breeze_036_gp,
//     rgi_15_gp,
//     retro2_16_gp,
//     Analogous_1_gp,
//     es_pinksplash_08_gp,
//     Coral_reef_gp,
//     es_ocean_breeze_068_gp,
//     es_pinksplash_07_gp,
//     es_vintage_01_gp,
//     departure_gp,
//     es_landscape_64_gp,
//     es_landscape_33_gp,
//     rainbowsherbet_gp,
//     gr65_hult_gp,
//     gr64_hult_gp,
//     GMT_drywet_gp,
//     ib_jul01_gp,
//     es_vintage_57_gp,
//     ib15_gp,
//     Fuschia_7_gp,
//     es_emerald_dragon_08_gp,
//     lava_gp,
//     fire_gp,
//     Colorfull_gp,
//     Magenta_Evening_gp,
//     Pink_Purple_gp,
//     es_autumn_19_gp,
//     BlacK_Blue_Magenta_White_gp,
//     BlacK_Magenta_Red_gp,
//     BlacK_Red_Magenta_Yellow_gp,
//     Blue_Cyan_Yellow_gp 
// };


// // Count of how many cpt-city gradients are defined:
// const uint8_t gGradientPaletteCount = sizeof( gGradientPalettes) / sizeof( TProgmemRGBGradientPalettePtr );



// *************** ALL OPTIONS NOTES ***************************
// const TProgmemRGBGradientPalettePtr LEDStripController::GRADIENT_PALETTES[] = {
//     rainbowsherbet_gp,          // YES!    // Unicorn colors (aka yummy)
//     ib_jul01_gp,                // YES!!   // dragon colors - green and red fire orange
//     Coral_reef_gp,              // WHOA    // cool blue to warm blue
//     Sunset_Real_gp,             // NOICE   // purple, pink, and orange
//     Analogous_1_gp,             // NOICE   // retro wave - purple and pink
//     BlacK_Red_Magenta_Yellow_gp,// OK+    // Tropical - fruity - yellow, red, purple
//     Blue_Cyan_Yellow_gp         // OK+    // Tropical - carribean - beach
//     es_autumn_19_gp,            // OK+    // interesting redish orange yellow - fall colors
//     rgi_15_gp,                  // OK+      // magenta, and lavender
//     es_pinksplash_07_gp,        // OK+    // magenta, lavender, and almost white
//     gr65_hult_gp,               // OK+    // bright blue, light purple, white
//     ib15_gp,                    // OK+    // soft gurl Desaturated pink and blue
//     Fuschia_7_gp,               // OK+    // bright purple blue pink
//     BlacK_Magenta_Red_gp,       // OK+    // magenta purple and black
//     Magenta_Evening_gp,         // OK+    // magenta and purple (no white)
//     bhw1_28_gp,                 // OK       // light blue, light purple
//     es_ocean_breeze_036_gp,     // OK       // Sky blue, and white
//     es_emerald_dragon_08_gp,    // OK    // Alien lime green
//     lava_gp,                    // OK    // (test to see if it's the same as our other one)
//     Colorfull_gp,               // OK    // desaturated green, purple blue white
//     Pink_Purple_gp,             // OK    // soothing purple, blue, white
//     BlacK_Blue_Magenta_White_gp,// OK    // like a desaturated american flag - not pleasing to cache
//     es_pinksplash_08_gp,        // OK      // pink, purple, white (dreamsicle) similar to below
//     es_landscape_33_gp,         // OK    // blue and gold (I think piss)
//     fire_gp,                    // OK-ish    // Candy corn colors
//     gr64_hult_gp,               // MEH    // similar to above
//     es_rivendell_15_gp,         // MEH      // grey green, and white
//     es_landscape_64_gp,         // MEH    // green, blue, white
//     // departure_gp,               // EW    // green with white and weird color
//     //GMT_drywet_gp,              // MEH    // blue, yellowish
//     // es_vintage_57_gp,           // NOPE    // Unhealthy piss (bloody piss)
//     //es_ocean_breeze_068_gp,     // OK       // same as above but with white
//     //retro2_16_gp,               // NOPE     // piss colors
//     //es_vintage_01_gp,           // EWEWEW  // piss colors (chaplin)
// };
// *************** ALL OPTIONS NOTES ***************************





/*--------------------------------------------------------------------------------------------------*
 *                          TURNER'S PALETTES                                                       *
 * These are palettes that I created, adapted, or renamed to better fit with my own needs           *
 *  I give credit where credit is due though :)                                                     *
 *                                                                                                  *
 *--------------------------------------------------------------------------------------------------*/
// **********************************************************
//      BUILT-IN PALETTES (converted to gradient palettes)
// **********************************************************
DEFINE_GRADIENT_PALETTE( tk_Rainbow_gp ) {
      0,  255,    0,    0, // Red
     32,  171,   85,    0, // Orange
     64,  171,  171,    0, // Yellow
     96,    0,  255,    0, // Green
    128,    0,  171,   85, // Aqua
    160,    0,    0,  255, // Blue
    192,   85,    0,  171, // Purple
    224,  171,    0,   85, // Pink
    255,  255,    0,    0  // and back to Red
};



DEFINE_GRADIENT_PALETTE( tk_Forest_gp ) {
      0,    0,  100,    0, // DarkGreen       -- 0x006400
     16,    0,  100,    0, // DarkGreen       -- 0x006400
     32,   85,  107,   47, // DarkOliveGreen  -- 0x556B2F
     48,    0,  100,    0, // DarkGreen       -- 0x006400

     64,    0,  128,    0, // Green           -- 0x008000
     80,   34,  139,   34, // ForestGreen     -- 0x228B22
     96,  107,  142,   35, // OliveDrab       -- 0x6B8E23
    112,    0,  128,    0, // Green           -- 0x008000
    
    128,   46,  139,   87, // SeaGreen        -- 0x2E8B57
    144,  102,  205,  170, // MediumAquamarine-- 0x66CDAA
    160,   50,  205,   50, // LimeGreen       -- 0x32CD32
    176,  154,  205,   50, // YellowGreen     -- 0x9ACD32
    
    192,  144,  238,  144, // LightGreen      -- 0x90EE90
    208,  124,  252,    0, // LawnGreen       -- 0x7CFC00
    224,  102,  205,  170, // MediumAquamarine-- 0x66CDAA
    240,   34,  139,   34, // ForestGreen    -- 0x228B22
    255,    0,  100,    0, // and back to the beginning
};



DEFINE_GRADIENT_PALETTE( tk_Party_gp ) {
      0,     85,    0,  171, // -- 0x 5500AB
     16,    132,    0,  124, // -- 0x 84007C
     32,    181,    0,   75, //  -- 0x B5004B
     48,    229,    0,   27, // -- 0x E5001B

     64,    232,   23,    0, // -- 0x E81700
     80,    184,   71,    0, // -- 0x B84700
     96,    171,  119,    0, // -- 0x AB7700
    112,    171,  171,    0, // -- 0x ABAB00
    
    128,    171,   85,    0, // -- 0x AB5500
    144,    221,   34,    0, // -- 0x DD2200
    160,    242,   14,    0, // -- 0x F2000E
    176,    194,    0,   62, // -- 0x C2003E
    
    192,    143,    0,  113, // -- 0x 8F0071
    208,     95,    0,  161, // -- 0x 5F00A1
    224,     47,    0,  208, // -- 0x 2F00D0
    240,      0,    7,  249, // -- 0x 0007F9
    255,     85,    0,  171  // and back to the beginning
};





// **********************************************************
//      TKS ORIGINAL GRADIENT PALETTES
// **********************************************************
DEFINE_GRADIENT_PALETTE( tk_Peacock_Colors_gp ) {
    0,  146,    0,  110,
//   16,  125,    0,  131,
//   32,  103,    0,  153,
//   48,   83,    0,  172,
//   64,   61,    0,  194,
   80,   40,    0,  215,
//   96,   18,    0,  237,
  112,    0,    6,  250,
//  128,    0,   49,  207,
//  144,    0,   91,  165,
  160,    0,  134,  122,
//  176,    0,  172,   83,
//  192,    0,  194,   61,
  208,    0,  215,   40,
//  224,    0,  237,   18,
  240,    0,  255,    0,
  255,  146,    0,  110
};


DEFINE_GRADIENT_PALETTE( tk_Watermellon_Colors_gp ) {
    0,  146,    0,  110,
   64,  146,    0,  110,
   96,   83,    0,  237,
  128,    0,  194,   165,
  144,    0,  255,    0,
  240,    0,  255,    0,
  255,  146,    0,  110
};


DEFINE_GRADIENT_PALETTE( tricias_Fairy_Wings_gp ) {
  0,  247, 37, 133,
  24,  247, 37, 133,
  25,  181, 23, 158,
  50,  181, 23, 158,
  51,  114,  9, 183,
  75,  114,  9, 183,
  76,  86,  11, 173,
  101,  86,  11, 173,
  102,  72,  12, 168,
  127,  72,  12, 168,
  128,  58,  12, 163,
  152,  58,  12, 163,
  153,  63,  55, 201,
  178,  63,  55, 201,  
  179,  67,  97, 238,
  203,  67,  97, 238,  
  204,  72, 149, 239,
  229,  72, 149, 239,  
  230,  76, 201, 240,
  255,  247, 37, 133 // wrapping around
  // 255,  76, 201, 240  // NOT wrapping around
};



// **********************************************************
//      TKS SPECIALTY PALETTES
// **********************************************************

// RENAME OF Gradient palette "fire_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/neota/elem/tn/fire.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 28 bytes of program space.

DEFINE_GRADIENT_PALETTE( tk_Fire_Candle_gp ) {
    0,   1,  1,  0,
   76,  32,  5,  0,
  146, 192, 24,  0,
  197, 220,105,  5,
  240, 252,255, 31,
  250, 252,255,111,
  255, 255,255,255
};

DEFINE_GRADIENT_PALETTE( tricias_Fairy_Fire_gp ) {
  
    0,    0,   0,   0,   // black  
   64,  197,   7,  93,
   90,  181,  23, 158,
  127,  114,   9, 183,
  153,   63,  55, 201,
  210,   67,  97, 238,
  230,   76, 201, 240,
  255,  255, 255, 255
};






DEFINE_GRADIENT_PALETTE( tk_Fire_Red_gp ) {
    0,   0,     0,   0,   // black
   64,  204,    0,   0,   // red
   80,  255,    51,   0,  // red + little green
  144, 255,  255,    0,   // yellow
  255, 255,  255,  255    // white
};


DEFINE_GRADIENT_PALETTE( tk_Fire_Blue_gp ) {
    0,   0,    0,    0,   // black
   64,   0,    0,  204,   // blue
   80,   0,    51,  255,   // blue
  144,   0,  255,   255,   // Aqua
  255, 255,  255,  255    // white
};   

DEFINE_GRADIENT_PALETTE( tk_Fire_Green_gp ) {
    0,   0,    0,    0,   // black
   80,   0,  204,    0,   // green
   96,   51,  255,   0,   // green
  160,   255,  255,  0,   // yellow
  255, 255,  255,  255    // white
};  


DEFINE_GRADIENT_PALETTE( tk_Fire_Pink_gp ) {
    0,    0,    0,    0,
   16,   24,    0,    4,
   32,   48,    0,    9,
   48,   72,    0,   13,
   64,   96,    0,   18,
   80,  121,    0,   23,
   96,  130,   12,   35,
  112,  140,   25,   47,
  128,  150,   37,   59,
  144,  160,   50,   71,
  160,  170,   63,   84,
  176,  187,  101,  118,
  192,  204,  139,  152,
  208,  221,  178,  186,
  224,  238,  216,  220,
  240,  255,  254,  254,
  255,    0,    0,    0
};


// RENAME OF Gradient palette "BlacK_Red_Magenta_Yellow_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/nd/basic/tn/BlacK_Red_Magenta_Yellow.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 28 bytes of program space.

DEFINE_GRADIENT_PALETTE( tk_Fire_Multi_Pink_gp ) {
    0,   0,  0,  0,
   42,  42,  0,  0,
   84, 255,  0,  0,
  127, 255,  0, 45,
  170, 255,  0,255,
  212, 255, 55, 45,
  255, 255,255,  0};








// **********************************************************
//      OTHER GRADIENT PALETTE ATTEMPTS
// **********************************************************
// DEFINE_GRADIENT_PALETTE( cache_01_gp ) {
//    0,   63, 255,  236,
//   51,   58,  72,  116,
//   102, 103, 101,  162,
//   153, 157, 113,  166,
//   204, 255, 154,  103,
//   255, 255, 227,  183};

// DEFINE_GRADIENT_PALETTE( tk_Fire_og_gp ) {
//     0,   0,     0,    0,   // black
//    64,  255,    0,    0,   // red
//   128,  171,  171,    0,   // yellow
//   255,  255,  255,  255};   // white


// DEFINE_GRADIENT_PALETTE( tk_Fire_Blue_og_gp ) {
//     0,   0,    0,    0,   // black
//    64,   0,    0,  255,   // blue
//   128,   0,  171,   85,   // Aqua
//   255, 255,  255,  255    // white
// };   







#endif
