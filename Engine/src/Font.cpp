#include <GalaEngine/Font.hpp>

void GalaEngine::Font::ClearCache() {
    // Unload fonts.
    for(const auto &fi : fontCacheList)
        ::UnloadFont(fi.font);

    // Clear cache list.
    fontCacheList.clear();
}

bool GalaEngine::Font::LoadFontData(const std::vector<uint8_t> &data, const std::vector<int> &chars) {
    if(data.empty()) return false;

    ClearCache();
    _fontData = data;
    _fontChars = chars;

    return true;
}

std::vector<uint8_t> GalaEngine::Font::GetFontData() {
    return _fontData;
}

BitmapFont GalaEngine::Font::GenerateBitmapFont(const int size) {
    int *fontChars = _fontChars.empty() ? NULL : _fontChars.data();

    return ::LoadFontFromMemory(
        ".ttf",
        _fontData.data(), _fontData.size(),
        size,
        fontChars, _fontChars.size()
    );
}

BitmapFont GalaEngine::Font::GetAtSize(const int size) {
    // FIXME: Memory leak when unloading fonts.

    // Search for cached bitmap font at size.
    const auto it = std::find_if(
        fontCacheList.begin(), fontCacheList.end(),
        [size](const auto &item) { return item.size == size; }
    );
    
    // If the cached bitmap font is found...
    if(it != fontCacheList.end()) {
        // Move it to the front.
        FontCacheItem item = *it;
        
        if(!fontCacheList.empty())
            fontCacheList.erase(it);

        fontCacheList.push_front(item);
            
    }else { // Otherwise...
        // Clear last (least recently used) item if reached max cache size.
        if(fontCacheList.size() >= GALAENGINE_FONT_CACHE_SIZE) {
            ::UnloadFont(fontCacheList.back().font);
            fontCacheList.pop_back();
        }
       
        // Load new font into cache item.
        const FontCacheItem newFont = { size, GenerateBitmapFont(size) };

        // Push it to the front.
        fontCacheList.push_front(newFont);
    }

    // Return resource.
    return fontCacheList.front().font;
}

GalaEngine::Font::Font() {

}