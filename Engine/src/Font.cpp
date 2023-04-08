#include <GalaEngine/Font.hpp>

BitmapFont GalaEngine::Font::GetAtSize(const int size) {
    // Search for cached bitmap font at size.
    const auto &it = std::find_if(
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
        if(_fontCacheList.size() >= GALAENGINE_FONT_CACHE_SIZE)
            _fontCacheList.pop_back();
       
        // TODO: Load new font.
        const _FontCacheItem newFont = {
            size,
            GetFontDefault()
        };

        // Push it to the front.
        _fontCacheList.push_front(newFont);
    }

    // Return resource.
    return _fontCacheList.front().font;
}

GalaEngine::Font::Font() {

}