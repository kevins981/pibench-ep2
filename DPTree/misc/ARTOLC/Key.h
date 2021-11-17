#ifndef ART_KEY_H
#define ART_KEY_H

#include <stdint.h>
#include <cstring>
#include <memory>
#include <assert.h>

extern std::atomic<uint64_t> baseTree_mp;

using KeyLen = uint32_t;

class Key {
public:

    static constexpr uint32_t stackLen = 128;
    uint32_t len = 0;

    uint8_t *data = nullptr;

    uint8_t stackKey[stackLen];

    Key(uint64_t k) { setInt(k); }

    void setInt(uint64_t k) { data = stackKey; len = 8; *reinterpret_cast<uint64_t*>(stackKey) = __builtin_bswap64(k); }

    uint64_t getInt() { return __builtin_bswap64(*reinterpret_cast<uint64_t*>(stackKey)); }

    Key() {}

    ~Key();

    //Key(const Key &key);

    Key(Key &&key);

    void set(const char bytes[], const std::size_t length);

    void operator=(const char key[]);
    //Key& operator=(const Key &key);
    bool operator==(const Key &k) const {
        if (k.getKeyLen() != getKeyLen()) {
            return false;
        }
        return std::memcmp(&k[0], data, getKeyLen()) == 0;
    }

    uint8_t &operator[](std::size_t i);

    const uint8_t &operator[](std::size_t i) const;

    KeyLen getKeyLen() const;

    void setKeyLen(KeyLen len);

};


inline uint8_t &Key::operator[](std::size_t i) {
    assert(i < len);
    return data[i];
}

inline const uint8_t &Key::operator[](std::size_t i) const {
    assert(i < len);
    return data[i];
}

inline KeyLen Key::getKeyLen() const { return len; }

inline Key::~Key() {
    if (len > stackLen) {
        delete[] data;
        data = nullptr;
    }
}

inline Key::Key(Key &&key) {
    len = key.len;
    if (len > stackLen) {
        data = key.data;
        key.data = nullptr;
    } else {
        memcpy(stackKey, key.stackKey, key.len);
        data = stackKey;
    }
}
//
//inline Key::Key(const Key &key) {
//    len = key.len;
//    if (len > stackLen) {
//        data = new uint8_t[len];
//        memcpy(data, key.data, len);
//    } else {
//        memcpy(stackKey, key.stackKey, key.len);
//        data = stackKey;
//    }
//}

inline void Key::set(const char bytes[], const std::size_t length) {
    if (len > stackLen) {
        delete[] data;
    }
    if (length <= stackLen) {
        memcpy(stackKey, bytes, length);
        data = stackKey;
    } else {
        data = new uint8_t[length];
        #ifdef MEMORY_FOOTPRINT
            baseTree_mp += sizeof(uint8_t);
        #endif
        memcpy(data, bytes, length);
    }
    len = length;
}
//
//inline Key& Key::operator=(const Key &key) {
//    if (this == &key)
//        return *this;
//    if (len > stackLen) {
//        delete[] data;
//    }
//
//    data = nullptr;
//    len = key.len;
//
//    if (len > stackLen) {
//        data = new uint8_t[len];
//        memcpy(data, key.data, len);
//    } else {
//        memcpy(stackKey, key.stackKey, key.len);
//        data = stackKey;
//    }
//    return *this;
//}


inline void Key::operator=(const char key[]) {
    if (len > stackLen) {
        delete[] data;
    }
    len = strlen(key);
    if (len <= stackLen) {
        memcpy(stackKey, key, len);
        data = stackKey;
    } else {
        data = new uint8_t[len];
        #ifdef MEMORY_FOOTPRINT
            baseTree_mp += sizeof(uint8_t);
        #endif
        memcpy(data, key, len);
    }
}

inline void Key::setKeyLen(KeyLen newLen) {
    if (len == newLen) return;
    if (len > stackLen) {
        delete[] data;
    }
    len = newLen;
    if (len > stackLen) {
        data = new uint8_t[len];
        #ifdef MEMORY_FOOTPRINT
            baseTree_mp += sizeof(uint8_t);
        #endif
    } else {
        data = stackKey;
    }
}

#endif // ART_KEY_H
