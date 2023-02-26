// Project: GalaEngine
// File: Colour.hpp
// Description: Colour struct and predefined colours.
// Authors: Colleen (@colleen05)
// https://github.com/colleen05/GalaEngine
// Distributed under the zlib license.

#pragma once

#include <raylib.h>
#include <rlgl.h>
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
#define C_GALARED	(GalaEngine::Colour) {0xDD, 0x00, 0x22, 0xFF}
#define C_GALAWHITE	(GalaEngine::Colour) {0xFF, 0xF8, 0xF8, 0xFF}
#define C_GALABLACK	(GalaEngine::Colour) {0x08, 0x08, 0x10, 0xFF}

namespace GalaEngine {
	/*! @brief Colour struct
	 *  @details Contains colour information, as well as functions that allow
	 *  for colour manipulation.
	 */
	struct Colour {
		uint8_t r;	//!< Red value
		uint8_t g;	//!< Green value
		uint8_t b;	//!< Blue value
		uint8_t a;	//!< Alpha value (opacity)

		/*! @brief Get blending result with another colour.
		 *  @details Get linear interpolation with another colour.
		 *  @param colour Other colour
		 *  @param t Ratio of **colour** to self.
		 *  @returns Blended colour.
		 */
		constexpr inline
		Colour Lerp(const Colour colour, const float t) {
			return Colour {
				static_cast<uint8_t>(static_cast<float>(r) + t * static_cast<float>(colour.r - r)),
				static_cast<uint8_t>(static_cast<float>(g) + t * static_cast<float>(colour.g - g)),
				static_cast<uint8_t>(static_cast<float>(b) + t * static_cast<float>(colour.b - b)),
				static_cast<uint8_t>(static_cast<float>(a) + t * static_cast<float>(colour.a - a))
			};
		}

		/*! @brief Blend two colours.
		 *  @details Linearly interpolate two colours.
		 *  @param c1 Colour from
		 *  @param c2 Colour to
		 *  @param t Ratio of c1 to c2.
		 */
		static Colour Lerp(Colour c1, Colour c2, const float t);

		/*! @brief Get normalised colour values
		 *  @details Get colour values normalised between 0.0f and 1.0f
		 *  @returns Normalised vector
		 */
		constexpr inline
		Vector4 Normalised() {
			return Vector4 {
				static_cast<float>(r) / 255.0f,
				static_cast<float>(g) / 255.0f,
				static_cast<float>(b) / 255.0f,
				static_cast<float>(a) / 255.0f
			};
		}

		/*! @brief Get normalised values from colour
		 *  @details Get normalised values of colour between 0.0f and 1.0f
		 *  @param colour The colour to normalise
		 *  @returns Normalised vector
		 */
		static Vector4 Normalise(Colour colour);

		/*! @brief Get basic struct from Colour
		 *  @details Constructs a Color struct from a Colour.
		 *  @note This is supplied for compatibility with raylib.
		 */
		constexpr operator Color() {
			return Color{r, g, b, a};
		}
	};

	/*! @brief Blend mode struct
	 *  @details Contains a source and destination factor for blend modes,
	 *  which are used to dictate how colours should be blended together when
	 *  drawn.
	 * 
	 *  Blend modes are calculated as such, where **E** is a given equation:<br>
	 *  finalColour = E((srcColour * srcFactor), (destColour * destFactor))
	 *  @note For common blend mode types, see the BlendModes namespace.
	 */
	struct BlendMode {
		/*! @brief Blend mode factors
		 *  @details Factors used when blending colours.
		 */
		enum class Factor {
			Zero					= 0x0000,	//!< (0, 0, 0, 0)
			One						= 0x0001,	//!< (1, 1, 1, 1)
			SourceColour			= 0x0300,	//!< (Rs, Gs, Bs, As)
			SourceColourInverted	= 0x0301,	//!< (1-Rs, 1-Gs, 1-Bs, 1-As)
			SourceAlpha				= 0x0302,	//!< (As, As, As, As)
			SourceAlphaInverted		= 0x0303,	//!< (1-As, 1-As, 1-As, 1-As)
			DestAlpha				= 0x0304,	//!< (Ad, Ad, Ad, Ad)
			DestAlphaInverted		= 0x0305,	//!< (1-Ad, 1-Ad, 1-Ad, 1-Ad)
			DestColour				= 0x0306,	//!< (Rd, Gd, Bd, Ad)
			DestColourInverted		= 0x0307,	//!< (1-Rd, 1-Gd, 1-Bd, 1-Ad)
			SourceAlphaSaturate		= 0x0308 	//!< (f, f, f, f); f = min(As, 1-Ad)
		};

		/*! @brief Blend mode functions/equations
		 *  @details How colours should be combined after applying factors.
		 */
		enum class Equation {
			Add					= 0x8006,	//!< finalColour = (srcProduct)  + (destProduct)
			Subtract			= 0x800A,	//!< finalColour = (srcProduct)  - (destProduct)
			SubtractReversed	= 0x800B,	//!< finalColour = (destProduct) - (srcProduct)
			Min					= 0x8007,	//!< finalColour = min(srcColour, destColour)
			Max					= 0x8008	//!< finalColour = max(srcColour, destColour)
		};

		Factor	 sourceFactor;	//!< The factor of which to multiply the source colour.
		Factor	 destFactor;	//!< The factor of which to multiply the destination colour.
		Equation equation;		//!< How to combine the two products into the final colour.
	};
}

/*! @brief Blend modes namespace
 *  @details Contains common blend modes, such as modes used in visual effects,
 *  and image-editing programs.
 */
namespace BlendModes {
    const GalaEngine::BlendMode Normal = {
        GalaEngine::BlendMode::Factor::One,
        GalaEngine::BlendMode::Factor::SourceAlphaInverted,
        GalaEngine::BlendMode::Equation::Add
    };
};

/*! @brief Colours namespace
 *  @details Contains colour presets from the X11 palette.
 */
namespace Colours {
	/*! @name Special colours
	 *  @details These colours are not in the X11 palette, but might be nice
	 *  to have anyway.
	 */
	///@{
	const GalaEngine::Colour GalaRed				= C_GALARED;    //!< `(GalaEngine::Colour) {0xdd, 0x00, 0x22, 0xff}`: Red colour used in the GalaEngine logo and website.
	const GalaEngine::Colour GalaWhite				= C_GALAWHITE;  //!< `(GalaEngine::Colour) {0xff, 0xf8, 0xf8, 0xff}`: Slightly off-white.
	const GalaEngine::Colour GalaBlack				= C_GALABLACK;  //!< `(GalaEngine::Colour) {0x08, 0x08, 0x10, 0xff}`: Very dark navy.
	const GalaEngine::Colour Clear					= C_CLEAR;      //!< `(GalaEngine::Colour) {0x00, 0x00, 0x00, 0x00}` Transparent.
	///@}

	/*! @name X11 colours
	 *  @details These colours are the default X11 / web colours.
     *  @see https://en.wikipedia.org/wiki/Web_colors#X11_color_names
	 */
	///@{
	const GalaEngine::Colour AliceBlue				= {0xf0, 0xf8, 0xff, 0xff}; //!< AliceBlue				
	const GalaEngine::Colour AntiqueWhite			= {0xfa, 0xeb, 0xd7, 0xff}; //!< AntiqueWhite			
	const GalaEngine::Colour Aqua	 				= {0x00, 0xff, 0xff, 0xff}; //!< Aqua	 				
	const GalaEngine::Colour Aquamarine	 			= {0x7f, 0xff, 0xd4, 0xff}; //!< Aquamarine	 			
	const GalaEngine::Colour Azure	 				= {0xf0, 0xff, 0xff, 0xff}; //!< Azure	 				
	const GalaEngine::Colour Beige	 				= {0xf5, 0xf5, 0xdc, 0xff}; //!< Beige	 				
	const GalaEngine::Colour Bisque	 				= {0xff, 0xe4, 0xc4, 0xff}; //!< Bisque	 				
	const GalaEngine::Colour Black	 				= {0x00, 0x00, 0x00, 0xff}; //!< Black	 				
	const GalaEngine::Colour BlanchedAlmond	 		= {0xff, 0xeb, 0xcd, 0xff}; //!< BlanchedAlmond	 		
	const GalaEngine::Colour Blue	 				= {0x00, 0x00, 0xff, 0xff}; //!< Blue	 				
	const GalaEngine::Colour BlueViolet	 			= {0x8a, 0x2b, 0xe2, 0xff}; //!< BlueViolet	 			
	const GalaEngine::Colour Brown	 				= {0xa5, 0x2a, 0x2a, 0xff}; //!< Brown	 				
	const GalaEngine::Colour BurlyWood	 			= {0xde, 0xb8, 0x87, 0xff}; //!< BurlyWood	 			
	const GalaEngine::Colour CadetBlue	 			= {0x5f, 0x9e, 0xa0, 0xff}; //!< CadetBlue	 			
	const GalaEngine::Colour Chartreuse	 			= {0x7f, 0xff, 0x00, 0xff}; //!< Chartreuse	 			
	const GalaEngine::Colour Chocolate	 			= {0xd2, 0x69, 0x1e, 0xff}; //!< Chocolate	 			
	const GalaEngine::Colour Coral	 				= {0xff, 0x7f, 0x50, 0xff}; //!< Coral	 				
	const GalaEngine::Colour CornflowerBlue	 		= {0x64, 0x95, 0xed, 0xff}; //!< CornflowerBlue	 		
	const GalaEngine::Colour Cornsilk	 			= {0xff, 0xf8, 0xdc, 0xff}; //!< Cornsilk	 			
	const GalaEngine::Colour Crimson	 			= {0xdc, 0x14, 0x3c, 0xff}; //!< Crimson	 			
	const GalaEngine::Colour Cyan	 				= {0x00, 0xff, 0xff, 0xff}; //!< Cyan	 				
	const GalaEngine::Colour DarkBlue	 			= {0x00, 0x00, 0x8b, 0xff}; //!< DarkBlue	 			
	const GalaEngine::Colour DarkCyan	 			= {0x00, 0x8b, 0x8b, 0xff}; //!< DarkCyan	 			
	const GalaEngine::Colour DarkGoldenrod	 		= {0xb8, 0x86, 0x0b, 0xff}; //!< DarkGoldenrod	 		
	const GalaEngine::Colour DarkGray	 			= {0xa9, 0xa9, 0xa9, 0xff}; //!< DarkGray	 			
	const GalaEngine::Colour DarkGreen	 			= {0x00, 0x64, 0x00, 0xff}; //!< DarkGreen	 			
	const GalaEngine::Colour DarkKhaki	 			= {0xbd, 0xb7, 0x6b, 0xff}; //!< DarkKhaki	 			
	const GalaEngine::Colour DarkMagenta	 		= {0x8b, 0x00, 0x8b, 0xff}; //!< DarkMagenta	 		
	const GalaEngine::Colour DarkOliveGreen	 		= {0x55, 0x6b, 0x2f, 0xff}; //!< DarkOliveGreen	 		
	const GalaEngine::Colour DarkOrange	 			= {0xff, 0x8c, 0x00, 0xff}; //!< DarkOrange	 			
	const GalaEngine::Colour DarkOrchid	 			= {0x99, 0x32, 0xcc, 0xff}; //!< DarkOrchid	 			
	const GalaEngine::Colour DarkRed	 			= {0x8b, 0x00, 0x00, 0xff}; //!< DarkRed	 			
	const GalaEngine::Colour DarkSalmon	 			= {0xe9, 0x96, 0x7a, 0xff}; //!< DarkSalmon	 			
	const GalaEngine::Colour DarkSeaGreen	 		= {0x8f, 0xbc, 0x8f, 0xff}; //!< DarkSeaGreen	 		
	const GalaEngine::Colour DarkSlateBlue	 		= {0x48, 0x3d, 0x8b, 0xff}; //!< DarkSlateBlue	 		
	const GalaEngine::Colour DarkSlateGray	 		= {0x2f, 0x4f, 0x4f, 0xff}; //!< DarkSlateGray	 		
	const GalaEngine::Colour DarkTurquoise	 		= {0x00, 0xce, 0xd1, 0xff}; //!< DarkTurquoise	 		
	const GalaEngine::Colour DarkViolet	 			= {0x94, 0x00, 0xd3, 0xff}; //!< DarkViolet	 			
	const GalaEngine::Colour DeepPink	 			= {0xff, 0x14, 0x93, 0xff}; //!< DeepPink	 			
	const GalaEngine::Colour DeepSkyBlue	 		= {0x00, 0xbf, 0xff, 0xff}; //!< DeepSkyBlue	 		
	const GalaEngine::Colour DimGray	 			= {0x69, 0x69, 0x69, 0xff}; //!< DimGray	 			
	const GalaEngine::Colour DodgerBlue	 			= {0x1e, 0x90, 0xff, 0xff}; //!< DodgerBlue	 			
	const GalaEngine::Colour FireBrick	 			= {0xb2, 0x22, 0x22, 0xff}; //!< FireBrick	 			
	const GalaEngine::Colour FloralWhite	 		= {0xff, 0xfa, 0xf0, 0xff}; //!< FloralWhite	 		
	const GalaEngine::Colour ForestGreen	 		= {0x22, 0x8b, 0x22, 0xff}; //!< ForestGreen	 		
	const GalaEngine::Colour Fuchsia	 			= {0xff, 0x00, 0xff, 0xff}; //!< Fuchsia	 			
	const GalaEngine::Colour Gainsboro	 			= {0xdc, 0xdc, 0xdc, 0xff}; //!< Gainsboro	 			
	const GalaEngine::Colour GhostWhite	 			= {0xf8, 0xf8, 0xff, 0xff}; //!< GhostWhite	 			
	const GalaEngine::Colour Gold	 				= {0xff, 0xd7, 0x00, 0xff}; //!< Gold	 				
	const GalaEngine::Colour Goldenrod	 			= {0xda, 0xa5, 0x20, 0xff}; //!< Goldenrod	 			
	const GalaEngine::Colour Gray	 				= {0x80, 0x80, 0x80, 0xff}; //!< Gray	 				
	const GalaEngine::Colour Green	 				= {0x00, 0x80, 0x00, 0xff}; //!< Green	 				
	const GalaEngine::Colour GreenYellow	 		= {0xad, 0xff, 0x2f, 0xff}; //!< GreenYellow	 		
	const GalaEngine::Colour Honeydew	 			= {0xf0, 0xff, 0xf0, 0xff}; //!< Honeydew	 			
	const GalaEngine::Colour HotPink	 			= {0xff, 0x69, 0xb4, 0xff}; //!< HotPink	 			
	const GalaEngine::Colour IndianRed	 			= {0xcd, 0x5c, 0x5c, 0xff}; //!< IndianRed	 			
	const GalaEngine::Colour Indigo	 				= {0x4b, 0x00, 0x82, 0xff}; //!< Indigo	 				
	const GalaEngine::Colour Ivory	 				= {0xff, 0xff, 0xf0, 0xff}; //!< Ivory	 				
	const GalaEngine::Colour Khaki	 				= {0xf0, 0xe6, 0x8c, 0xff}; //!< Khaki	 				
	const GalaEngine::Colour Lavender	 			= {0xe6, 0xe6, 0xfa, 0xff}; //!< Lavender	 			
	const GalaEngine::Colour LavenderBlush	 		= {0xff, 0xf0, 0xf5, 0xff}; //!< LavenderBlush	 		
	const GalaEngine::Colour LawnGreen	 			= {0x7c, 0xfc, 0x00, 0xff}; //!< LawnGreen	 			
	const GalaEngine::Colour LemonChiffon	 		= {0xff, 0xfa, 0xcd, 0xff}; //!< LemonChiffon	 		
	const GalaEngine::Colour LightBlue	 			= {0xad, 0xd8, 0xe6, 0xff}; //!< LightBlue	 			
	const GalaEngine::Colour LightCoral	 			= {0xf0, 0x80, 0x80, 0xff}; //!< LightCoral	 			
	const GalaEngine::Colour LightCyan	 			= {0xe0, 0xff, 0xff, 0xff}; //!< LightCyan	 			
	const GalaEngine::Colour LightGoldenrodYellow	= {0xfa, 0xfa, 0xd2, 0xff}; //!< LightGoldenrodYellow	
	const GalaEngine::Colour LightGreen	 	 		= {0x90, 0xee, 0x90, 0xff}; //!< LightGreen	 	 		
	const GalaEngine::Colour LightGrey	 	 		= {0xd3, 0xd3, 0xd3, 0xff}; //!< LightGrey	 	 		
	const GalaEngine::Colour LightPink	 	 		= {0xff, 0xb6, 0xc1, 0xff}; //!< LightPink	 	 		
	const GalaEngine::Colour LightSalmon	 		= {0xff, 0xa0, 0x7a, 0xff}; //!< LightSalmon	 		
	const GalaEngine::Colour LightSeaGreen	 		= {0x20, 0xb2, 0xaa, 0xff}; //!< LightSeaGreen	 		
	const GalaEngine::Colour LightSkyBlue	 		= {0x87, 0xce, 0xfa, 0xff}; //!< LightSkyBlue	 		
	const GalaEngine::Colour LightSlateGray	 		= {0x77, 0x88, 0x99, 0xff}; //!< LightSlateGray	 		
	const GalaEngine::Colour LightSteelBlue	 		= {0xb0, 0xc4, 0xde, 0xff}; //!< LightSteelBlue	 		
	const GalaEngine::Colour LightYellow	 		= {0xff, 0xff, 0xe0, 0xff}; //!< LightYellow	 		
	const GalaEngine::Colour Lime	 				= {0x00, 0xff, 0x00, 0xff}; //!< Lime	 				
	const GalaEngine::Colour LimeGreen	 			= {0x32, 0xcd, 0x32, 0xff}; //!< LimeGreen	 			
	const GalaEngine::Colour Linen	 				= {0xfa, 0xf0, 0xe6, 0xff}; //!< Linen	 				
	const GalaEngine::Colour Magenta				= {0xff, 0x00, 0xff, 0xff}; //!< Magenta				
	const GalaEngine::Colour Maroon	 				= {0x80, 0x00, 0x00, 0xff}; //!< Maroon	 				
	const GalaEngine::Colour MediumAquamarine	 	= {0x66, 0xcd, 0xaa, 0xff}; //!< MediumAquamarine	 	
	const GalaEngine::Colour MediumBlue	 	 	 	= {0x00, 0x00, 0xcd, 0xff}; //!< MediumBlue	 	 	 	
	const GalaEngine::Colour MediumOrchid	 	 	= {0xba, 0x55, 0xd3, 0xff}; //!< MediumOrchid	 	 	
	const GalaEngine::Colour MediumPurple	 	 	= {0x93, 0x70, 0xdb, 0xff}; //!< MediumPurple	 	 	
	const GalaEngine::Colour MediumSeaGreen	 	 	= {0x3c, 0xb3, 0x71, 0xff}; //!< MediumSeaGreen	 	 	
	const GalaEngine::Colour MediumSlateBlue	 	= {0x7b, 0x68, 0xee, 0xff}; //!< MediumSlateBlue	 	
	const GalaEngine::Colour MediumSpringGreen	 	= {0x00, 0xfa, 0x9a, 0xff}; //!< MediumSpringGreen	 	
	const GalaEngine::Colour MediumTurquoise	 	= {0x48, 0xd1, 0xcc, 0xff}; //!< MediumTurquoise	 	
	const GalaEngine::Colour MediumVioletRed	 	= {0xc7, 0x15, 0x85, 0xff}; //!< MediumVioletRed	 	
	const GalaEngine::Colour MidnightBlue	 		= {0x19, 0x19, 0x70, 0xff}; //!< MidnightBlue	 		
	const GalaEngine::Colour MintCream	 	 		= {0xf5, 0xff, 0xfa, 0xff}; //!< MintCream	 	 		
	const GalaEngine::Colour MistyRose	 	 		= {0xff, 0xe4, 0xe1, 0xff}; //!< MistyRose	 	 		
	const GalaEngine::Colour Moccasin	 	 		= {0xff, 0xe4, 0xb5, 0xff}; //!< Moccasin	 	 		
	const GalaEngine::Colour NavajoWhite	 		= {0xff, 0xde, 0xad, 0xff}; //!< NavajoWhite	 		
	const GalaEngine::Colour Navy	 	 			= {0x00, 0x00, 0x80, 0xff}; //!< Navy	 	 			
	const GalaEngine::Colour OldLace	 			= {0xfd, 0xf5, 0xe6, 0xff}; //!< OldLace	 			
	const GalaEngine::Colour Olive	 				= {0x80, 0x80, 0x00, 0xff}; //!< Olive	 				
	const GalaEngine::Colour OliveDrab	 			= {0x6b, 0x8e, 0x23, 0xff}; //!< OliveDrab	 			
	const GalaEngine::Colour Orange	 	 			= {0xff, 0xa5, 0x00, 0xff}; //!< Orange	 	 			
	const GalaEngine::Colour OrangeRed	 			= {0xff, 0x45, 0x00, 0xff}; //!< OrangeRed	 			
	const GalaEngine::Colour Orchid	 		 		= {0xda, 0x70, 0xd6, 0xff}; //!< Orchid	 		 		
	const GalaEngine::Colour PaleGoldenrod	 		= {0xee, 0xe8, 0xaa, 0xff}; //!< PaleGoldenrod	 		
	const GalaEngine::Colour PaleGreen	 	 		= {0x98, 0xfb, 0x98, 0xff}; //!< PaleGreen	 	 		
	const GalaEngine::Colour PaleTurquoise	 		= {0xaf, 0xee, 0xee, 0xff}; //!< PaleTurquoise	 		
	const GalaEngine::Colour PaleVioletRed	 		= {0xdb, 0x70, 0x93, 0xff}; //!< PaleVioletRed	 		
	const GalaEngine::Colour PapayaWhip	 			= {0xff, 0xef, 0xd5, 0xff}; //!< PapayaWhip	 			
	const GalaEngine::Colour PeachPuff	 			= {0xff, 0xda, 0xb9, 0xff}; //!< PeachPuff	 			
	const GalaEngine::Colour Peru	 	 			= {0xcd, 0x85, 0x3f, 0xff}; //!< Peru	 	 			
	const GalaEngine::Colour Pink	 	 			= {0xff, 0xc0, 0xcb, 0xff}; //!< Pink	 	 			
	const GalaEngine::Colour Plum	 	 			= {0xdd, 0xa0, 0xdd, 0xff}; //!< Plum	 	 			
	const GalaEngine::Colour PowderBlue	 			= {0xb0, 0xe0, 0xe6, 0xff}; //!< PowderBlue	 			
	const GalaEngine::Colour Purple	 	 			= {0x80, 0x00, 0x80, 0xff}; //!< Purple	 	 			
	const GalaEngine::Colour Red	 	 			= {0xff, 0x00, 0x00, 0xff}; //!< Red	 	 			
	const GalaEngine::Colour RosyBrown	 			= {0xbc, 0x8f, 0x8f, 0xff}; //!< RosyBrown	 			
	const GalaEngine::Colour RoyalBlue	 			= {0x41, 0x69, 0xe1, 0xff}; //!< RoyalBlue	 			
	const GalaEngine::Colour SaddleBrown	 		= {0x8b, 0x45, 0x13, 0xff}; //!< SaddleBrown	 		
	const GalaEngine::Colour Salmon	 	 			= {0xfa, 0x80, 0x72, 0xff}; //!< Salmon	 	 			
	const GalaEngine::Colour SandyBrown	 			= {0xf4, 0xa4, 0x60, 0xff}; //!< SandyBrown	 			
	const GalaEngine::Colour SeaGreen	 			= {0x2e, 0x8b, 0x57, 0xff}; //!< SeaGreen	 			
	const GalaEngine::Colour Seashell	 			= {0xff, 0xf5, 0xee, 0xff}; //!< Seashell	 			
	const GalaEngine::Colour Sienna	 	 			= {0xa0, 0x52, 0x2d, 0xff}; //!< Sienna	 	 			
	const GalaEngine::Colour Silver	 	 			= {0xc0, 0xc0, 0xc0, 0xff}; //!< Silver	 	 			
	const GalaEngine::Colour SkyBlue	 			= {0x87, 0xce, 0xeb, 0xff}; //!< SkyBlue	 			
	const GalaEngine::Colour SlateBlue	 			= {0x6a, 0x5a, 0xcd, 0xff}; //!< SlateBlue	 			
	const GalaEngine::Colour SlateGray	 			= {0x70, 0x80, 0x90, 0xff}; //!< SlateGray	 			
	const GalaEngine::Colour Snow	 		 		= {0xff, 0xfa, 0xfa, 0xff}; //!< Snow	 		 		
	const GalaEngine::Colour SpringGreen	 		= {0x00, 0xff, 0x7f, 0xff}; //!< SpringGreen	 		
	const GalaEngine::Colour SteelBlue	 			= {0x46, 0x82, 0xb4, 0xff}; //!< SteelBlue	 			
	const GalaEngine::Colour Tan	 	 			= {0xd2, 0xb4, 0x8c, 0xff}; //!< Tan	 	 			
	const GalaEngine::Colour Teal	 	 			= {0x00, 0x80, 0x80, 0xff}; //!< Teal	 	 			
	const GalaEngine::Colour Thistle	 			= {0xd8, 0xbf, 0xd8, 0xff}; //!< Thistle	 			
	const GalaEngine::Colour Tomato	 	 			= {0xff, 0x63, 0x47, 0xff}; //!< Tomato	 	 			
	const GalaEngine::Colour Turquoise	 			= {0x40, 0xe0, 0xd0, 0xff}; //!< Turquoise	 			
	const GalaEngine::Colour Violet	 	 			= {0xee, 0x82, 0xee, 0xff}; //!< Violet	 	 			
	const GalaEngine::Colour Wheat	 	 			= {0xf5, 0xde, 0xb3, 0xff}; //!< Wheat	 	 			
	const GalaEngine::Colour White	 	 			= {0xff, 0xff, 0xff, 0xff}; //!< White	 	 			
	const GalaEngine::Colour WhiteSmoke	 			= {0xf5, 0xf5, 0xf5, 0xff}; //!< WhiteSmoke	 			
	const GalaEngine::Colour Yellow	 				= {0xff, 0xff, 0x00, 0xff}; //!< Yellow	 				
	const GalaEngine::Colour YellowGreen	 		= {0x9a, 0xcd, 0x32, 0xff}; //!< YellowGreen	 		
	///@}
}