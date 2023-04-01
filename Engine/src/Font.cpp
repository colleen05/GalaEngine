#include <GalaEngine/Font.hpp>

BitmapFont GalaEngine::Font::GetAtSize(int size) {
    /* TODO: Implement O(n) caching algorithm:
     * 1. If cache slots are not full, use first free cache slot for new font,
     *    and increment the "get count" of that slot. Otherwise, ...
     * 2. Search for font in cache. If found, incremenet get-count and return.
     *    Otherwise, ...
     * 3. Find font slot with lowest "get count".
     * 4. Unload font in that slot.
     * 5. Use that slot to store new font. Set "get count" to 1.
     */

    // Search cache.
    for(const auto &[fSize, font] : _cachedFonts) {
        // Return if font cached at size.
        if(fSize == size) return font;
    }

    // If font has not been cached at size...
    BitmapFont font = ::GetFontDefault(); // TODO: Generate font from data.

    /* Load into "rolling cache"; The font slot which has had the longest time
       since use will be replaced with new font. */
    const size_t cachedFontIndex = _cachedFontCount % GALAENGINE_FONT_CACHE_SIZE;

    if(_cachedFontCount >= GALAENGINE_FONT_CACHE_SIZE)      // If going to overwrite a loaded font slot...
        ::UnloadFont(_cachedFonts[cachedFontIndex].second); // Unload the font first.

    _cachedFonts[cachedFontIndex] = std::make_pair(size, font);
    _cachedFontCount++;

    return font;
}

GalaEngine::Font::Font() {

}