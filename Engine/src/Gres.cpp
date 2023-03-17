#include <GalaEngine/Gres.hpp>

// Textures
Texture GalaEngine::Gres::LoadTextureData(const std::vector<uint8_t> &data) {
    // Load table
    xdt::Table gresTable;
    gresTable.Deserialise(data);

    // Checking
    if(gresTable.GetString("type") != "texture")                return {0};
    if(gresTable.GetItemType("texture") != xdt::ItemType::Raw)  return {0};

    // Decode texture
    const auto textureBytes = gresTable.GetBytes("texture");

    Image img = LoadImageFromMemory(".qoi", textureBytes.data(), textureBytes.size() * sizeof(textureBytes[0]));
    if( (img.data == NULL) ||
        (img.width == 0) ||
        (img.height == 0)
    ) return {0};

    Texture tex = LoadTextureFromImage(img);

    // Set texture filter
    if(gresTable.ItemExists("texture_filter")) {
        std::string filterStr = gresTable.GetString("texture_filter");
        TextureFilter filter = TEXTURE_FILTER_POINT;

        if      (filterStr == "bilinear")   filter = TEXTURE_FILTER_BILINEAR;
        else if (filterStr == "trilinear")  filter = TEXTURE_FILTER_TRILINEAR;

        SetTextureFilter(tex, filter);
    }

    // Unload image & return
    UnloadImage(img);
    
    return tex;
}

Texture GalaEngine::Gres::LoadTexture(const std::string &filePath) {
    std::ifstream f(filePath);

    if(!f.good()) return {0};

    return LoadTextureData(std::vector<uint8_t>(
        std::istreambuf_iterator<char>(f),
        std::istreambuf_iterator<char>()
    ));
}


// Sprites
GalaEngine::Sprite GalaEngine::Gres::LoadSpriteData(const std::vector<uint8_t> &data) {
    // Load table
    xdt::Table gresTable;
    gresTable.Deserialise(data);

    // Checking
    if(gresTable.GetString("type")          != "sprite")             return {{0}, {0}, {{0}}};
    if(gresTable.GetItemType("texture")     != xdt::ItemType::Raw)   return {{0}, {0}, {{0}}};
    if(gresTable.GetItemType("frame_count") != xdt::ItemType::Int16) return {{0}, {0}, {{0}}};


    /// Decoding ///
    GalaEngine::Sprite spr;

    // Decode texture
    const auto textureBytes = gresTable.GetBytes("texture");

    Image img = LoadImageFromMemory(".qoi", textureBytes.data(), textureBytes.size() * sizeof(textureBytes[0]));
    if( (img.data == NULL) ||
        (img.width == 0) ||
        (img.height == 0)
    ) return {{0}, {0}, {{0}}};

    spr.texture = LoadTextureFromImage(img);

    // Set texture filter
    if(gresTable.ItemExists("texture_filter")) {
        std::string filterStr = gresTable.GetString("texture_filter");
        TextureFilter filter = TEXTURE_FILTER_POINT;

        if      (filterStr == "bilinear")   filter = TEXTURE_FILTER_BILINEAR;
        else if (filterStr == "trilinear")  filter = TEXTURE_FILTER_TRILINEAR;

        SetTextureFilter(spr.texture, filter);
    }

    // Unload image
    UnloadImage(img);

    // Decode origin data
    spr.origin = (Vector2) {
        (float) gresTable.GetInt16("origin_x"),
        (float) gresTable.GetInt16("origin_y")
    };

    // Decode frames
    const size_t frameCount = gresTable.GetInt16("frame_count");
    
    if(frameCount <= 0)
        spr.frameRects.push_back((Rectangle) {0.0f, 0.0f, (float)spr.texture.width, (float)spr.texture.height});

    for(auto i = 0; i < frameCount; i++) {
        const std::string frameStr = "frame[" + std::to_string(i) + "]";

        spr.frameRects.push_back((Rectangle) {
            (float) gresTable.GetInt16(frameStr + ".x"),
            (float) gresTable.GetInt16(frameStr + ".y"),
            (float) gresTable.GetInt16(frameStr + ".w"),
            (float) gresTable.GetInt16(frameStr + ".h")
        });
    }

    return spr;
}

GalaEngine::Sprite GalaEngine::Gres::LoadSprite(const std::string &filePath) {
    std::ifstream f(filePath);

    if(!f.good()) return {{0}, {0}, {{0}}};

    return LoadSpriteData(std::vector<uint8_t>(
        std::istreambuf_iterator<char>(f),
        std::istreambuf_iterator<char>()
    ));
}


// 9-Slices
GalaEngine::NSlice GalaEngine::Gres::LoadNSliceData(const std::vector<uint8_t> &data) {
    // Load table
    xdt::Table gresTable;
    gresTable.Deserialise(data);

    // Checking
    if(gresTable.GetString("type")          != "nslice")             return {{0}, {0}, {0}};
    if(gresTable.GetItemType("texture")     != xdt::ItemType::Raw)   return {{0}, {0}, {0}};
    
    if(gresTable.GetItemType("centre_slice.x") != xdt::ItemType::Int16) return {{0}, {0}, {0}};
    if(gresTable.GetItemType("centre_slice.y") != xdt::ItemType::Int16) return {{0}, {0}, {0}};
    if(gresTable.GetItemType("centre_slice.w") != xdt::ItemType::Int16) return {{0}, {0}, {0}};
    if(gresTable.GetItemType("centre_slice.h") != xdt::ItemType::Int16) return {{0}, {0}, {0}};

    if(!gresTable.ItemExists("stretch_slices.up"))      return {{0}, {0}, {0}};
    if(!gresTable.ItemExists("stretch_slices.right"))   return {{0}, {0}, {0}};
    if(!gresTable.ItemExists("stretch_slices.down"))    return {{0}, {0}, {0}};
    if(!gresTable.ItemExists("stretch_slices.left"))    return {{0}, {0}, {0}};
    if(!gresTable.ItemExists("stretch_slices.centre"))  return {{0}, {0}, {0}};


    /// Decoding ///
    GalaEngine::NSlice nslice;

    // Decode texture
    const auto textureBytes = gresTable.GetBytes("texture");

    Image img = LoadImageFromMemory(".qoi", textureBytes.data(), textureBytes.size() * sizeof(textureBytes[0]));
    if( (img.data == NULL) ||
        (img.width == 0) ||
        (img.height == 0)
    ) return {{0}, {0}, {0}};

    nslice.texture = LoadTextureFromImage(img);

    // Set texture filter
    if(gresTable.ItemExists("texture_filter")) {
        std::string filterStr = gresTable.GetString("texture_filter");
        TextureFilter filter = TEXTURE_FILTER_POINT;

        if      (filterStr == "bilinear")   filter = TEXTURE_FILTER_BILINEAR;
        else if (filterStr == "trilinear")  filter = TEXTURE_FILTER_TRILINEAR;

        SetTextureFilter(nslice.texture, filter);
    }

    // Unload image
    UnloadImage(img);

    // Decode centre slice
    nslice.centreSlice = (Rectangle) {
        gresTable.GetFloat("centre_slice.x"),
        gresTable.GetFloat("centre_slice.y"),
        gresTable.GetFloat("centre_slice.w"),
        gresTable.GetFloat("centre_slice.h")
    };

    // Decode stretched slice
    nslice.stretchSlices[0] = gresTable.GetBool("stretch_slices.up");
    nslice.stretchSlices[1] = gresTable.GetBool("stretch_slices.right");
    nslice.stretchSlices[2] = gresTable.GetBool("stretch_slices.down");
    nslice.stretchSlices[3] = gresTable.GetBool("stretch_slices.left");
    nslice.stretchSlices[4] = gresTable.GetBool("stretch_slices.centre");


    return nslice;
}

GalaEngine::NSlice GalaEngine::Gres::LoadNSlice(const std::string &filePath) {
    std::ifstream f(filePath);

    if(!f.good()) return {{0}, {0}, {0}};

    return LoadNSliceData(std::vector<uint8_t>(
        std::istreambuf_iterator<char>(f),
        std::istreambuf_iterator<char>()
    ));
}


// Tilesets
GalaEngine::Tileset GalaEngine::Gres::LoadTilesetData(const std::vector<uint8_t> &data) {
    // Load table
    xdt::Table gresTable;
    gresTable.Deserialise(data);

    // Checking
    if(gresTable.GetString("type")          != "tileset")            return Tileset();
    if(gresTable.GetItemType("texture")     != xdt::ItemType::Raw)   return Tileset();
    if(gresTable.GetItemType("tile_size")   != xdt::ItemType::Int16) return Tileset();


    /// Decoding ///
    GalaEngine::Tileset ts;

    // Decode texture
    const auto textureBytes = gresTable.GetBytes("texture");

    Image img = LoadImageFromMemory(".qoi", textureBytes.data(), textureBytes.size() * sizeof(textureBytes[0]));
    if( (img.data == NULL) ||
        (img.width == 0) ||
        (img.height == 0)
    ) return Tileset();

    Texture tex = LoadTextureFromImage(img);
    UnloadImage(img);

    // Construct tileset
    const auto flagBytes = gresTable.GetBytes("flags");

    auto flagsVec = std::vector<uint16_t>(flagBytes.size() / 2, 0x00);
    for(size_t i = 0; i < flagBytes.size() / 2; i++) {
        flagsVec[i] = (flagBytes[i*2+1] << 8) + (flagBytes[i*2]);
    }

    ts = Tileset(
        tex,
        gresTable.GetInt16("tile_size"),
        flagsVec
    );

    return ts;
}

GalaEngine::Tileset GalaEngine::Gres::LoadTileset(const std::string &filePath) {
    std::ifstream f(filePath);

    if(!f.good()) return Tileset();

    return LoadTilesetData(std::vector<uint8_t>(
        std::istreambuf_iterator<char>(f),
        std::istreambuf_iterator<char>()
    ));
}


// Sounds
Sound GalaEngine::Gres::LoadSoundData(const std::vector<uint8_t> &data) {
    // Load table
    xdt::Table gresTable;
    gresTable.Deserialise(data);

    // Checking
    if(gresTable.GetString("type")      != "sound")             return {0};
    if(gresTable.GetItemType("audio")   != xdt::ItemType::Raw)  return {0};

    // Decode audio
    const auto audioBytes = gresTable.GetBytes("audio");
    std::string fileType = (gresTable.GetString("encoding") == "vorbis") ? ".ogg" : ".wav";

    Wave wav = LoadWaveFromMemory(
        fileType.c_str(),
        audioBytes.data(),
        audioBytes.size() * sizeof(audioBytes[0])
    );

    return LoadSoundFromWave(wav);
}

Sound GalaEngine::Gres::LoadSound(const std::string &filePath) {
    std::ifstream f(filePath);

    if(!f.good()) return {0};

    return LoadSoundData(std::vector<uint8_t>(
        std::istreambuf_iterator<char>(f),
        std::istreambuf_iterator<char>()
    ));
}


// Fonts
Font GalaEngine::Gres::LoadFontData(const std::vector<uint8_t> &data) {
    return {0};
}

Font GalaEngine::Gres::LoadFont(const std::string &filePath) {
    std::ifstream f(filePath);

    if(!f.good()) return {0};

    return LoadFontData(std::vector<uint8_t>(
        std::istreambuf_iterator<char>(f),
        std::istreambuf_iterator<char>()
    ));
}