#pragma once

#include <cstdio>
#include <cstdlib>
#include <cstring>

namespace dsa {
    class Bitmap {
    private:
        int            N;
        unsigned char *map;

    protected:
        void init(int n) {
            N = (n + 7) / 8;
            map = new unsigned char[N];
            memset(map, 0, N);
        }

    public:
        Bitmap(int n = 8) {
            init(n);
        }

        Bitmap(char *file, int n = 8) {
            init(n);
            FILE *fp = fopen(file, "r");
            fread(map, sizeof(unsigned char), N, fp);
            fclose(fp);
        }

        ~Bitmap() {
            delete[] map;
            map = nullptr;
        }

        bool test(int k) {
            int           q = k >> 3;             // k / 8
            unsigned char offset = k & 0x07;      // k % 8
            unsigned char mask = 0x80 >> offset;  // the k-th bit

            return map[q] & (mask);
        }

        void set(int k) {
            expand(k);
            map[k >> 3] |= (0x80 >> (k & 0x07));
        }

        void clear(int k) {
            expand(k);
            map[k >> 3] &= ~(0x80 >> (k & 0x07));
        }

        void dump(char *file) {
            FILE *fp = fopen(file, "w");
            fwrite(map, sizeof(unsigned char), N, fp);
            fclose(fp);
        }

        char *bits2string(int n) {
            expand(n - 1);

            char *s = new char[n - 1];
            for (int i = 0; i < n; ++i) {
                s[i] = test(i) ? '1' : '0';
            }
            s[n] = '\0';

            return s;
        }

        void expand(int k) {
            if (k < N * 8) {
                return;
            }
            int            oldN = N;
            unsigned char *oldMap = map;

            init(2 * k);
            memcpy(map, oldMap, oldN);

            delete[] oldMap;
        }

        void print(int n) {
            expand(n);
            for (int i = 0; i < n; ++i) {
                printf(test(i) ? "1" : "0");
            }
        }
    };
}
