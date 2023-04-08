#include <GalaEngine/Font.hpp>

void GalaEngine::Font::ClearCache() {
    // Unload fonts.
    for(const auto &fi : _fontCacheList)
        ::UnloadFont(fi.font);

    // Clear cache list.
    _fontCacheList.clear();
}

bool GalaEngine::Font::LoadFontData(const std::vector<uint8_t> &data, const std::vector<int> &chars) {
    if(data.empty() || chars.empty()) return false;

    ClearCache();
    _fontData = data;
    _fontChars = chars;

    return true;
}

BitmapFont GalaEngine::Font::GenerateBitmapFont(const int size) {
    return ::LoadFontFromMemory(
        ".ttf",
        _fontData.data(), _fontData.size(),
        size,
        _fontChars.data(), _fontChars.size()
    );
}

BitmapFont GalaEngine::Font::GetAtSize(const int size) {
    // Search for cached bitmap font at size.
    const auto it = std::find_if(
        _fontCacheList.begin(), _fontCacheList.end(),
        [size](const auto &item) { return item.size == size; }
    );
    
    // If the cached bitmap font is found...
    if(it != _fontCacheList.end()) {
        // Move it to the front.
        _fontCacheList.push_front(*it);
        
        if(_fontCacheList.size() > 1)
            _fontCacheList.erase(it);
    }else { // Otherwise...
        // Clear last (least recently used) item if reached max cache size.
        if(_fontCacheList.size() >= GALAENGINE_FONT_CACHE_SIZE) {
            ::UnloadFont(_fontCacheList.back().font);
            _fontCacheList.pop_back();
        }
       
        // Load new font into cache item.
        const _FontCacheItem newFont = { size, GenerateBitmapFont(size) };

        // Push it to the front.
        _fontCacheList.push_front(newFont);
    }

    // Return resource.
    return _fontCacheList.front().font;
}

GalaEngine::Font::Font() {

}