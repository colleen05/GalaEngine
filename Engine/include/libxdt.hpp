/**
 * @file libxdt.hpp
 * @brief LibXDT's single header file.
 * @details Contains all declarations for using LibXDT.
 */

#pragma once

#include <string>
#include <sstream>
#include <iomanip>
#include <vector>
#include <unordered_map>
#include <chrono>
#include <iostream>
#include <fstream>
#include <iterator>
#include <algorithm>

#define XDT_MAGIC 0x00584454 //!< 4-byte sequence used at the beginning of a file to declare it is XDT-formatted.

#define XDT_GET_ITEM_COMPRESION(flags) (flags.low & 0b11000000) //!< Returns the 2-bit compression bitfield within an ItemFlags struct.

namespace xdt {
    /*! @brief Bitfield for header flags
     *  @details Contains information about how provided XDT-formatted data
     *  may be encoded. The high-byte may be used for non-standard encodings.
     */
    struct HeaderFlags {
        uint8_t low = 0x00; //!< Unused flags
        uint8_t high = 0x00; //!< Unused flags
    };

    /*! @brief Container for header information
     *  @details Contains header information as provided in the XDT
     *  specification, such as encoding version and flags.
     *  @note
     *  - Does not contain the **magic** field as defined in the
     *  specification, as it is a static value, and will automatically be
     *  prepended to serialised data by the Table class.
     * 
     *  - Does not contain the **item count** field as declared in the
     *  specification, as it can be obtained from the directory member in the
     *  Table class, and will automatically be written to serialised data.
     */
    struct HeaderInfo {
        uint16_t version = 0x0000;   //!< Version field which states what standard, or non-standard encoding version the XDT-formatted data uses.
        HeaderFlags flags;  //!< Bitfield for flags stored in the header.
    };

    /*! @brief Item type enumeration, values from specification.
     *  @details IDs for various types of data which an item can contain,
     *  identical to those which are defined in the XDT specification. It is
     *  used by LibXDT for decerning how to serialise / deserialise data
     *  within XDT files / the Table class.
     */
    enum class ItemType {
        Byte            = 0x00, //!< `0x00`: Byte (unsigned char)
        Bool            = 0x01, //!< `0x01`: Boolean (bool)
        Int16           = 0x02, //!< `0x02`: Signed 16-bit integer (int16_t)
        Uint16          = 0x03, //!< `0x03`: Unsigned 16-bit integer (uint16_t)
        Int32           = 0x04, //!< `0x04`: Signed 32-bit integer (int16_t)
        Uint32          = 0x05, //!< `0x05`: Unsigned 32-bit integer (uint16_t)
        Int64           = 0x06, //!< `0x06`: Signed 64-bit integer (int16_t)
        Uint64          = 0x07, //!< `0x07`: Unsigned 64-bit integer (uint16-t)
        Float           = 0x08, //!< `0x08`: Floating-point number (float)
        Double          = 0x09, //!< `0x09`: Double-precision floating-point number (double)
        Timestamp       = 0x0A, //!< `0x0A`: 32-bit UNIX timestamp (int32_t / std::chrono::seconds)
        LongTimestamp   = 0x0B, //!< `0x0B`: 64-bit UNIX timestamp (int64_t / std::chrono::seconds)
        ASCIIString     = 0x0C, //!< `0x0C`: ASCII-encoded string (char[] / std::string)
        UTF8String      = 0x0D, //!< `0x0D`: UTF8-encoded string (std::string)
        File            = 0x0E, //!< `0x0E`: File data (uint8_t[] / std::vector<uint8_t>)
        Raw             = 0x0F  //!< `0x0F`: Raw binary data (uint8_t[] / std::vector<uint8_t>)
    };

    /*! @brief Vector of types which are BLOBs
     *  @note Any type needing more than 4 bytes of data is always a BLOB.
     */
    const std::vector<ItemType> BLOBTypes = { ItemType::Int64, ItemType::Uint64, ItemType::LongTimestamp, ItemType::Double, ItemType::ASCIIString, ItemType::UTF8String, ItemType::File, ItemType::Raw};

    /*! @brief Get name of standard type
     *  @details Attempts to get the name of a given type.
     *  @note If the supplied type is non-standard, will return the numeric
     *  value as a string.
     */
    std::string GetTypeString(ItemType type);

    /*! @brief Per-item bitfield for directory entries
     *  @details Contains information about how an individual item is encoded,
     *  regardless of what type of data is stored (such as compression). The
     *  high-byte may be used for non-standard encodigns.
     */
    struct ItemFlags {
        //! Information about which compression scheme to use, as defined in the specification.
        /*!
         * Compression schemes are as followed, ordered by effeciency/time:
         * Code     | Compression Scheme
         * ---------|-------------------
         * ``0b00`` | No compression
         * ``0b01`` | Run-length encoding (RLE)
         * ``0b10`` | LZ77
         * ``0b11`` | DEFLATE
         */
        uint8_t low = 0x00;
        uint8_t high = 0x00; //!< Unused
    };

    /*! @brief Per-item container for item information
     *  @details Contains information about an individual item within the
     *  directory of XDT-formatted data, such as the item's data type,
     *  its flags, and a vector to the data itself.
     *  @note Does not contain the **size/value** field as declared in the
     *  specification, but instead contains a **data** member which will
     *  automatically be correctly serialised by the Table class.
     */
    struct Item {
        ItemType    type;           //!< What data-type the individual item contains.
        ItemFlags   flags;          //!< Flags containing additional information.
        std::vector<uint8_t> data;  //!< Data as bytes.

        // Getters
        uint8_t     GetByte();      //!< Returns value casted to a byte, **0x00** if types are incompatible.
        bool        GetBool();      //!< Returns value casted to a boolean, **false** if types are incompatible.
        int16_t     GetInt16();     //!< Returns value casted to a signed 16-bit integer, **0** if types are incompatible.
        uint16_t    GetUint16();    //!< Returns value casted to an unsigned 16-bit integer, **0** if types are incompatible.
        int32_t     GetInt32();     //!< Returns value casted to a signed 32-bit integer, **0** if types are incompatible.
        uint32_t    GetUint32();    //!< Returns value casted to an unsigned 32-bit integer, **0** if types are incompatible.
        int64_t     GetInt64();     //!< Returns value casted to a signed 64-bit integer, **0** if types are incompatible.
        uint64_t    GetUint64();    //!< Returns value casted to an unsigned 64-bit integer, **0** if types are incompatible.
        float       GetFloat();     //!< Returns value casted to a floating-point number, **0.0f** if types are incompatible.
        double      GetDouble();    //!< Returns value casted to a double-precision floating-point number, **0.0** if types are incompatible.
        std::chrono::seconds GetTimestamp();  //!< Returns value casted to seconds since January 1st, 1970, **0s** if types are incompatible.
        std::string          GetString(bool asHex = false); //!< Returns value casted to a string, empty if types are incompatible.
        std::vector<uint8_t> GetBytes();      //!< Returns raw bytes of value.

        // Setters
        void SetByte      (uint8_t  value, bool overwriteType = false); //!< Attempts to set the value to the supplied value.
        void SetBool      (bool     value, bool overwriteType = false); //!< Attempts to set the value to the supplied value.
        void SetInt16     (int16_t  value, bool overwriteType = false); //!< Attempts to set the value to the supplied value.
        void SetUint16    (uint16_t value, bool overwriteType = false); //!< Attempts to set the value to the supplied value.
        void SetInt32     (int32_t  value, bool overwriteType = false); //!< Attempts to set the value to the supplied value.
        void SetUint32    (uint32_t value, bool overwriteType = false); //!< Attempts to set the value to the supplied value.
        void SetInt64     (int64_t  value, bool overwriteType = false); //!< Attempts to set the value to the supplied value.
        void SetUint64    (uint64_t value, bool overwriteType = false); //!< Attempts to set the value to the supplied value.
        void SetFloat     (float    value, bool overwriteType = false); //!< Attempts to set the value to the supplied value.
        void SetDouble    (double   value, bool overwriteType = false); //!< Attempts to set the value to the supplied value.
        void SetTimestamp (std::chrono::seconds value,  bool isLong = false, bool overwriteType = false); //!< Attempts to set the value to the supplied value.
        void SetString    (const std::string    &value, bool isUTF8 = false, bool overwriteType = false); //!< Attempts to set the value to the supplied value.
        void SetBytes     (const std::vector<uint8_t> &value, bool isFileData = false, bool overwriteType = false); //!< Attempts to set the value to the supplied value.
    };

    /*! @brief Class for managing XDT data.
     *  @details Provides functionality for encoding/decoding to and from
     *  XDT-formatted data. All table data is stored such that they can be
     *  read and modified with C++.
     */
    class Table {
        public:
            std::string errorStatus = ""; //!< Current error status

            HeaderInfo headerInfo; //!< Header information such as version, flags, and the number of table items.
            std::vector<std::pair<std::string, Item>> directory; //!< The container for all items, indexed by name.

            // General item stuff
            xdt::Item       *GetItem    (const std::string &itemName); //!< Returns pointer to item if found.
            bool            ItemExists  (const std::string &itemName); //!< Returns **true** if item is found.
            xdt::ItemType   GetItemType (const std::string &itemName); //!< Returns type of item if found.
            void            DeleteItem  (const std::string &itemName); //!< Delete item by name.

            // Getters
            uint8_t     GetByte     (const std::string &itemName); //!< Returns value casted to a byte, **0x00** if types are incompatible.
            bool        GetBool     (const std::string &itemName); //!< Returns value casted to a boolean, **false** if types are incompatible.
            int16_t     GetInt16    (const std::string &itemName); //!< Returns value casted to a signed 16-bit integer, **0** if types are incompatible.
            uint16_t    GetUint16   (const std::string &itemName); //!< Returns value casted to an unsigned 16-bit integer, **0** if types are incompatible.
            int32_t     GetInt32    (const std::string &itemName); //!< Returns value casted to a signed 32-bit integer, **0** if types are incompatible.
            uint32_t    GetUint32   (const std::string &itemName); //!< Returns value casted to an unsigned 32-bit integer, **0** if types are incompatible.
            int64_t     GetInt64    (const std::string &itemName); //!< Returns value casted to a signed 64-bit integer, **0** if types are incompatible.
            uint64_t    GetUint64   (const std::string &itemName); //!< Returns value casted to an unsigned 64-bit integer, **0** if types are incompatible.
            float       GetFloat    (const std::string &itemName); //!< Returns value casted to a floating-point number, **0.0f** if types are incompatible.
            double      GetDouble   (const std::string &itemName); //!< Returns value casted to a double-precision floating-point number, **0.0** if types are incompatible.
            std::chrono::seconds GetTimestamp(const std::string &itemName);  //!< Returns value casted to seconds since January 1st, 1970, **0s** if types are incompatible.
            std::string          GetString(const std::string &itemName, bool asHex = false); //!< Returns value casted to a string, empty if types are incompatible.
            std::vector<uint8_t> GetBytes(const std::string &itemName);      //!< Returns raw bytes of value.

            // Setters
            void SetByte      (const std::string &itemName, uint8_t  value, bool overwriteType = false); //!< Attempts to set the value to the supplied value.
            void SetBool      (const std::string &itemName, bool     value, bool overwriteType = false); //!< Attempts to set the value to the supplied value.
            void SetInt16     (const std::string &itemName, int16_t  value, bool overwriteType = false); //!< Attempts to set the value to the supplied value.
            void SetUint16    (const std::string &itemName, uint16_t value, bool overwriteType = false); //!< Attempts to set the value to the supplied value.
            void SetInt32     (const std::string &itemName, int32_t  value, bool overwriteType = false); //!< Attempts to set the value to the supplied value.
            void SetUint32    (const std::string &itemName, uint32_t value, bool overwriteType = false); //!< Attempts to set the value to the supplied value.
            void SetInt64     (const std::string &itemName, int64_t  value, bool overwriteType = false); //!< Attempts to set the value to the supplied value.
            void SetUint64    (const std::string &itemName, uint64_t value, bool overwriteType = false); //!< Attempts to set the value to the supplied value.
            void SetFloat     (const std::string &itemName, float    value, bool overwriteType = false); //!< Attempts to set the value to the supplied value.
            void SetDouble    (const std::string &itemName, double   value, bool overwriteType = false); //!< Attempts to set the value to the supplied value.
            void SetTimestamp (const std::string &itemName, std::chrono::seconds value,  bool isLong = false, bool overwriteType = false); //!< Attempts to set the value to the supplied value.
            void SetString    (const std::string &itemName, const std::string    &value, bool isUTF8 = false, bool overwriteType = false); //!< Attempts to set the value to the supplied value.
            void SetBytes     (const std::string &itemName, const std::vector<uint8_t> &value, bool isFileData = false, bool overwriteType = false); //!< Attempts to set the value to the supplied value.

            // Serialisation
            std::vector<uint8_t> Serialise(); //!< Returns an XDT-formatted byte array of the table.
            bool Deserialise(const std::vector<uint8_t> &data); //!< Loads data from an XDT-formatted byte array.

            // File IO
            void Save(const std::string &filename); //!< Save serialised data.
            bool Load(const std::string &filename); //!< Load XDT file.

            // Constructors
            Table(const std::vector<uint8_t> &data);   //!< Construct and load from XDT-formatted data.
            Table(const std::string &filename);        //!< Construct and load from a file.
            Table(HeaderInfo header);           //!< Construct with given header configuration.
            Table();                            //!< Construct with default header configuration.
    };

    /*! @brief Compress bytes using run-length encoding (RLE).
     *  @param bytes The bytes to be compressed.
     *  @returns Compressed bytes.
     */
    std::vector<uint8_t> CompressRLE(std::vector<uint8_t> &bytes);

    /*! @brief Decompress bytes from RLE-compressed bytes.
     *  @param bytes The bytes to be decompressed.
     *  @returns Decompressed bytes.
     */
    std::vector<uint8_t> DecompressRLE(std::vector<uint8_t> &bytes);
}