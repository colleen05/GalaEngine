#include <GalaEngine/Font.hpp>

BitmapFont GalaEngine::Font::GetAtSize(const int size) {
    // Search for cached bitmap font at size.
    const auto &it = std::find_if(
        _fontCacheList.begin(), _fontCacheList.end(),
        [size](const auto &item) { return item.size == size; }
    );
    
    // If the cached bitmap font is found...
    if(it != _fontCacheList.end()) {
        // Move it to the back.
        _fontCacheList.push_back(*it);
        
        if(_fontCacheList.size() > 1)
            _fontCacheList.erase(it);
    }else { // Otherwise...
        // Clear first (least recently used) item if reached max cache size.
        if(_fontCacheList.size() >= GALAENGINE_FONT_CACHE_SIZE)
            _fontCacheList.erase(_fontCacheList.begin());
       
        // TODO: Load new font.
        const _FontCacheItem newFont = {
            size,
            GetFontDefault()
        };

        // Push it to the back.
        _fontCacheList.push_back(newFont);
    }

    // Return resource.
    return _fontCacheList.back().font;
}

GalaEngine::Font::Font() {

}