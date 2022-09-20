// Project: GalaEngine
// File: Colour.hpp
// Description: Colour struct and predefined colours.
// Authors: Colleen (@colleen05)
// https://github.com/colleen05/GalaEngine
// Distributed under the zlib license.

#pragma once

#include <raylib.h>
#include <string>

// Grey tones & clear
#define C_CLEAR		(GalaEngine::Colour) {0x00, 0x00, 0x00, 0x00}
#define C_WHITE		(GalaEngine::Colour) {0xFF, 0xFF, 0xFF, 0xFF}
#define C_LTGREY	(GalaEngine::Colour) {0xBB, 0xBB, 0xBB, 0xFF}
#define C_GREY		(GalaEngine::Colour) {0x7F, 0x7F, 0x7F, 0xFF}
#define C_DKGREY	(GalaEngine::Colour) {0x33, 0x33, 0x33, 0xFF}
#define C_BLACK		(GalaEngine::Colour) {0x00, 0x00, 0x00, 0xFF}

// Reds
#define C_LTRED     (GalaEngine::Colour) {0xFF, 0x7F, 0x7F, 0xFF}
#define C_RED       (GalaEngine::Colour) {0xFF, 0x00, 0x00, 0xFF}
#define C_DKRED     (GalaEngine::Colour) {0x7F, 0x00, 0x00, 0xFF}

// Greens
#define C_LTGREEN   (GalaEngine::Colour) {0x7F, 0xFF, 0x7F, 0xFF}
#define C_GREEN		(GalaEngine::Colour) {0x00, 0xFF, 0x00, 0xFF}
#define C_DKGREEN	(GalaEngine::Colour) {0x00, 0x7F, 0x00, 0xFF}

// Blues
#define C_LTBLUE    (GalaEngine::Colour) {0x7F, 0x7F, 0xFF, 0xFF}
#define C_BLUE      (GalaEngine::Colour) {0x00, 0x00, 0xFF, 0xFF}
#define C_DKBLUE    (GalaEngine::Colour) {0x00, 0x00, 0x7F, 0xFF}

// Cyans
#define C_LTCYAN	(GalaEngine::Colour) {0x7F, 0xFF, 0xFF, 0xFF}
#define C_CYAN		(GalaEngine::Colour) {0x00, 0xFF, 0xFF, 0xFF}
#define C_DKCYAN	(GalaEngine::Colour) {0x00, 0x7F, 0x7F, 0xFF}

// Magentas
#define C_LTMAGENTA	(GalaEngine::Colour) {0xFF, 0x7F, 0xFF, 0xFF}
#define C_MAGENTA	(GalaEngine::Colour) {0xFF, 0x00, 0xFF, 0xFF}
#define C_DKMAGENTA	(GalaEngine::Colour) {0x7F, 0x00, 0x7F, 0xFF}
#define C_FUCHSIA	(GalaEngine::Colour) {0xFF, 0x00, 0x7F, 0xFF}

// Yellows
#define C_YELLOW    (GalaEngine::Colour) {0xFF, 0xFF, 0x00, 0xFF}
#define C_DKYELLOW  (GalaEngine::Colour) {0x7F, 0x7F, 0x00, 0xFF}
#define C_ORANGE	(GalaEngine::Colour) {0xFF, 0x7F, 0x00, 0xFF}
#define C_BROWN		(GalaEngine::Colour) {0x7F, 0x33, 0x00, 0xFF}

// Purples
#define C_LTPURPLE	(GalaEngine::Colour) {0xBB, 0x7F, 0xFF, 0xFF}
#define C_PURPLE	(GalaEngine::Colour) {0x7F, 0x00, 0xFF, 0xFF}
#define C_DKPURPLE	(GalaEngine::Colour) {0x55, 0x00, 0x7F, 0xFF}

// Special
#define C_GALARED	(GalaEngine::Colour) {0xDD, 0x00, 0x33, 0xFF}
#define C_GALAWHITE	(GalaEngine::Colour) {0xFF, 0xF8, 0xF8, 0xFF}
#define C_GALABLACK	(GalaEngine::Colour) {0x08, 0x08, 0x10, 0xFF}

namespace GalaEngine {
	struct Colour {
		uint8_t r, g, b, a;

		Colour Lerp(Colour colour, float t);
		static Colour Lerp(Colour c1, Colour c2, float t);

		Vector4 Normalised();
		static Vector4 Normalise(Colour colour);

		constexpr operator Color() {
			return Color{r, g, b, a};
		}
	};
}

namespace Colours {
	// Special
	const GalaEngine::Colour GalaRed				= C_GALARED;
	const GalaEngine::Colour GalaWhite				= C_GALAWHITE;
	const GalaEngine::Colour GalaBlack				= C_GALABLACK;
	const GalaEngine::Colour Clear					= C_CLEAR;

	// X11 Colours
	const GalaEngine::Colour AliceBlue				= {240,248,255,255};
	const GalaEngine::Colour AntiqueWhite			= {250,235,215,255};
	const GalaEngine::Colour Aqua	 				= {0,255,255,255};
	const GalaEngine::Colour Aquamarine	 			= {127,255,212,255};
	const GalaEngine::Colour Azure	 				= {240,255,255,255};
	const GalaEngine::Colour Beige	 				= {245,245,220,255};
	const GalaEngine::Colour Bisque	 				= {255,228,196,255};
	const GalaEngine::Colour Black	 				= {0,0,0,255};
	const GalaEngine::Colour BlanchedAlmond	 		= {255,235,205,255};
	const GalaEngine::Colour Blue	 				= {0,0,255,255};
	const GalaEngine::Colour BlueViolet	 			= {138,43,226,255};
	const GalaEngine::Colour Brown	 				= {165,42,42,255};
	const GalaEngine::Colour BurlyWood	 			= {222,184,135,255};
	const GalaEngine::Colour CadetBlue	 			= {95,158,160,255};
	const GalaEngine::Colour Chartreuse	 			= {127,255,0,255};
	const GalaEngine::Colour Chocolate	 			= {210,105,30,255};
	const GalaEngine::Colour Coral	 				= {255,127,80,255};
	const GalaEngine::Colour CornflowerBlue	 		= {100,149,237,255};
	const GalaEngine::Colour Cornsilk	 			= {255,248,220,255};
	const GalaEngine::Colour Crimson	 			= {220,20,60,255};
	const GalaEngine::Colour Cyan	 				= {0,255,255,255};
	const GalaEngine::Colour DarkBlue	 			= {0,0,139,255};
	const GalaEngine::Colour DarkCyan	 			= {0,139,139,255};
	const GalaEngine::Colour DarkGoldenrod	 		= {184,134,11,255};
	const GalaEngine::Colour DarkGray	 			= {169,169,169,255};
	const GalaEngine::Colour DarkGreen	 			= {0,100,0,255};
	const GalaEngine::Colour DarkKhaki	 			= {189,183,107,255};
	const GalaEngine::Colour DarkMagenta	 		= {139,0,139,255};
	const GalaEngine::Colour DarkOliveGreen	 		= {85,107,47,255};
	const GalaEngine::Colour DarkOrange	 			= {255,140,0,255};
	const GalaEngine::Colour DarkOrchid	 			= {153,50,204,255};
	const GalaEngine::Colour DarkRed	 			= {139,0,0,255};
	const GalaEngine::Colour DarkSalmon	 			= {233,150,122,255};
	const GalaEngine::Colour DarkSeaGreen	 		= {143,188,143,255};
	const GalaEngine::Colour DarkSlateBlue	 		= {72,61,139,255};
	const GalaEngine::Colour DarkSlateGray	 		= {47,79,79,255};
	const GalaEngine::Colour DarkTurquoise	 		= {0,206,209,255};
	const GalaEngine::Colour DarkViolet	 			= {148,0,211,255};
	const GalaEngine::Colour DeepPink	 			= {255,20,147,255};
	const GalaEngine::Colour DeepSkyBlue	 		= {0,191,255,255};
	const GalaEngine::Colour DimGray	 			= {105,105,105,255};
	const GalaEngine::Colour DodgerBlue	 			= {30,144,255,255};
	const GalaEngine::Colour FireBrick	 			= {178,34,34,255};
	const GalaEngine::Colour FloralWhite	 		= {255,250,240,255};
	const GalaEngine::Colour ForestGreen	 		= {34,139,34,255};
	const GalaEngine::Colour Fuchsia	 			= {255,0,255,255};
	const GalaEngine::Colour Gainsboro	 			= {220,220,220,255};
	const GalaEngine::Colour GhostWhite	 			= {248,248,255,255};
	const GalaEngine::Colour Gold	 				= {255,215,0,255};
	const GalaEngine::Colour Goldenrod	 			= {218,165,32,255};
	const GalaEngine::Colour Gray	 				= {128,128,128,255};
	const GalaEngine::Colour Green	 				= {0,128,0,255};
	const GalaEngine::Colour GreenYellow	 		= {173,255,47,255};
	const GalaEngine::Colour Honeydew	 			= {240,255,240,255};
	const GalaEngine::Colour HotPink	 			= {255,105,180,255};
	const GalaEngine::Colour IndianRed	 			= {205,92,92,255};
	const GalaEngine::Colour Indigo	 				= {75,0,130,255};
	const GalaEngine::Colour Ivory	 				= {255,255,240,255};
	const GalaEngine::Colour Khaki	 				= {240,230,140,255};
	const GalaEngine::Colour Lavender	 			= {230,230,250,255};
	const GalaEngine::Colour LavenderBlush	 		= {255,240,245,255};
	const GalaEngine::Colour LawnGreen	 			= {124,252,0,255};
	const GalaEngine::Colour LemonChiffon	 		= {255,250,205,255};
	const GalaEngine::Colour LightBlue	 			= {173,216,230,255};
	const GalaEngine::Colour LightCoral	 			= {240,128,128,255};
	const GalaEngine::Colour LightCyan	 			= {224,255,255,255};
	const GalaEngine::Colour LightGoldenrodYellow	= {250,250,210,255};
	const GalaEngine::Colour LightGreen	 	 		= {144,238,144,255};
	const GalaEngine::Colour LightGrey	 	 		= {211,211,211,255};
	const GalaEngine::Colour LightPink	 	 		= {255,182,193,255};
	const GalaEngine::Colour LightSalmon	 		= {255,160,122,255};
	const GalaEngine::Colour LightSeaGreen	 		= {32,178,170,255};
	const GalaEngine::Colour LightSkyBlue	 		= {135,206,250,255};
	const GalaEngine::Colour LightSlateGray	 		= {119,136,153,255};
	const GalaEngine::Colour LightSteelBlue	 		= {176,196,222,255};
	const GalaEngine::Colour LightYellow	 		= {255,255,224,255};
	const GalaEngine::Colour Lime	 				= {0,255,0,255};
	const GalaEngine::Colour LimeGreen	 			= {50,205,50,255};
	const GalaEngine::Colour Linen	 				= {250,240,230,255};
	const GalaEngine::Colour Magenta				= {255,0,255,255};
	const GalaEngine::Colour Maroon	 				= {128,0,0,255};
	const GalaEngine::Colour MediumAquamarine	 	= {102,205,170,255};
	const GalaEngine::Colour MediumBlue	 	 	 	= {0,0,205,255};
	const GalaEngine::Colour MediumOrchid	 	 	= {186,85,211,255};
	const GalaEngine::Colour MediumPurple	 	 	= {147,112,219,255};
	const GalaEngine::Colour MediumSeaGreen	 	 	= {60,179,113,255};
	const GalaEngine::Colour MediumSlateBlue	 	= {123,104,238,255};
	const GalaEngine::Colour MediumSpringGreen	 	= {0,250,154,255};
	const GalaEngine::Colour MediumTurquoise	 	= {72,209,204,255};
	const GalaEngine::Colour MediumVioletRed	 	= {199,21,133,255};
	const GalaEngine::Colour MidnightBlue	 		= {25,25,112,255};
	const GalaEngine::Colour MintCream	 	 		= {245,255,250,255};
	const GalaEngine::Colour MistyRose	 	 		= {255,228,225,255};
	const GalaEngine::Colour Moccasin	 	 		= {255,228,181,255};
	const GalaEngine::Colour NavajoWhite	 		= {255,222,173,255};
	const GalaEngine::Colour Navy	 	 			= {0,0,128,255};
	const GalaEngine::Colour OldLace	 			= {253,245,230,255};
	const GalaEngine::Colour Olive	 				= {128,128,0,255};
	const GalaEngine::Colour OliveDrab	 			= {107,142,35,255};
	const GalaEngine::Colour Orange	 	 			= {255,165,0,255};
	const GalaEngine::Colour OrangeRed	 			= {255,69,0,255};
	const GalaEngine::Colour Orchid	 		 		= {218,112,214,255};
	const GalaEngine::Colour PaleGoldenrod	 		= {238,232,170,255};
	const GalaEngine::Colour PaleGreen	 	 		= {152,251,152,255};
	const GalaEngine::Colour PaleTurquoise	 		= {175,238,238,255};
	const GalaEngine::Colour PaleVioletRed	 		= {219,112,147,255};
	const GalaEngine::Colour PapayaWhip	 			= {255,239,213,255};
	const GalaEngine::Colour PeachPuff	 			= {255,218,185,255};
	const GalaEngine::Colour Peru	 	 			= {205,133,63,255};
	const GalaEngine::Colour Pink	 	 			= {255,192,203,255};
	const GalaEngine::Colour Plum	 	 			= {221,160,221,255};
	const GalaEngine::Colour PowderBlue	 			= {176,224,230,255};
	const GalaEngine::Colour Purple	 	 			= {128,0,128,255};
	const GalaEngine::Colour Red	 	 			= {255,0,0,255};
	const GalaEngine::Colour RosyBrown	 			= {188,143,143,255};
	const GalaEngine::Colour RoyalBlue	 			= {65,105,225,255};
	const GalaEngine::Colour SaddleBrown	 		= {139,69,19,255};
	const GalaEngine::Colour Salmon	 	 			= {250,128,114,255};
	const GalaEngine::Colour SandyBrown	 			= {244,164,96,255};
	const GalaEngine::Colour SeaGreen	 			= {46,139,87,255};
	const GalaEngine::Colour Seashell	 			= {255,245,238,255};
	const GalaEngine::Colour Sienna	 	 			= {160,82,45,255};
	const GalaEngine::Colour Silver	 	 			= {192,192,192,255};
	const GalaEngine::Colour SkyBlue	 			= {135,206,235,255};
	const GalaEngine::Colour SlateBlue	 			= {106,90,205,255};
	const GalaEngine::Colour SlateGray	 			= {112,128,144,255};
	const GalaEngine::Colour Snow	 		 		= {255,250,250,255};
	const GalaEngine::Colour SpringGreen	 		= {0,255,127,255};
	const GalaEngine::Colour SteelBlue	 			= {70,130,180,255};
	const GalaEngine::Colour Tan	 	 			= {210,180,140,255};
	const GalaEngine::Colour Teal	 	 			= {0,128,128,255};
	const GalaEngine::Colour Thistle	 			= {216,191,216,255};
	const GalaEngine::Colour Tomato	 	 			= {255,99,71,255};
	const GalaEngine::Colour Turquoise	 			= {64,224,208,255};
	const GalaEngine::Colour Violet	 	 			= {238,130,238,255};
	const GalaEngine::Colour Wheat	 	 			= {245,222,179,255};
	const GalaEngine::Colour White	 	 			= {255,255,255,255};
	const GalaEngine::Colour WhiteSmoke	 			= {245,245,245,255};
	const GalaEngine::Colour Yellow	 				= {255,255,0,255};
	const GalaEngine::Colour YellowGreen	 		= {154,205,50,255};
}