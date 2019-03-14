#include <iostream>
#include "AESCodec.h"

long getFileSize(FILE* f)
{
    fseek(f, 0, SEEK_END);
    auto s = ftell(f);
    fseek(f, 0, SEEK_SET);
    return s;
}

int main()
{
    FILE* fin = fopen("1.txt", "rb");
    FILE* fout = fopen("2.txt", "wb");
    uint8_t key[] = {
            0x00, 0x01, 0x02, 0x03,
            0x04, 0x05, 0x06, 0x07,
            0x08, 0x09, 0x0a, 0x0b,
            0x0c, 0x0d, 0x0e, 0x0f,
            0x10, 0x11, 0x12, 0x13,
            0x14, 0x15, 0x16, 0x17,
            0x18, 0x19, 0x1a, 0x1b,
            0x1c, 0x1d, 0x1e, 0x1f};

    bool enc = 1;
    char buf[4096];
    char out[4096];
    long finSize = getFileSize(fin);
    uint8_t finalBlockSize = static_cast<uint8_t>(finSize & 0x0f);

    if (enc) {
        fwrite(&finalBlockSize, 1, 1, fout);
    } else {
        fread(&finalBlockSize, 1, 1, fin);
        finSize--;
    }
    AESCodec aes(key, sizeof(key));
    for (;;) {
        auto count = fread(buf, 1, sizeof(buf), fin);

        if (count == 0) {
            break;
        }

        finSize -= count;

        if (enc) {
            aes.encrypt(out, buf, count);
            fwrite(out, 1, (count + 15) / 16 * 16, fout);
        } else {
            aes.decrypt(out, buf, count);
            if (finSize == 0) {
                if (finalBlockSize == 0) {
                    fwrite(out, 1, count, fout);
                } else {
                    fwrite(out, 1, count - 16 + finalBlockSize, fout);
                }
            } else {
                fwrite(out, 1, count, fout);
            }
        }
    }

    fclose(fout);
    fclose(fin);
    return 0;
}