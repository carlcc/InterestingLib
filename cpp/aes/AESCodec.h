/**
 * Copyright (c) 2018 Chen.Chen All rights reserved.
 *
 * Author: Chen Chen (carlchenmarx@gmail.com)
 * 
 * Date: 2019-3-13
 *
 * About this file: This file holds the declaration/implementation of class AESCodec
 */

#pragma once


#include <cstdint>
#include <cstddef>

/**
 * AESCodec
 */
class AESCodec {
public:
    AESCodec(const uint8_t* key, size_t keyLenInBytes);

    AESCodec(const AESCodec&) = delete;

    AESCodec(AESCodec&& aes) noexcept
    {
        mImpl = aes.mImpl;
        aes.mImpl = nullptr;
    }

    ~AESCodec();

    AESCodec& operator=(const AESCodec&) = delete;

    AESCodec& operator=(AESCodec&& aes) noexcept
    {
        mImpl = aes.mImpl;
        aes.mImpl = nullptr;
    }

    // This method assumes: cipher is (plainLen + 15)/16 bytes length
    void encrypt(void* cipher, const void* plain, size_t plainLen);

    // This method assumes: cipher and plain are both 16 bytes length
    void encryptBlock(void* cipher, const void* plain);

    // This method assumes: plain is (cipherLen + 15)/16 bytes length
    void decrypt(void* plain, const void* cipher, size_t cipherLen);

    // This method assumes: cipher and plain are both 16 bytes length
    void decryptBlock(void* plain, const void* cipher);

private:
    class AESCodecInternal;
    AESCodecInternal* mImpl;
};



