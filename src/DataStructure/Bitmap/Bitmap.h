#pragma once

#include <cstdio>
#include <cstdlib>
#include <cstring>

namespace dsa {
  class Bitmap {
private:
    int            bytes_num;
    unsigned char *bitmap;

protected:
    void init(int n);

public:
    explicit Bitmap(int n = 8) {
      init(n);
    }

    explicit Bitmap(char *file, int n = 8) {
      init(n);
      FILE *fp = fopen(file, "r");
      fread(bitmap, sizeof(unsigned char), bytes_num, fp);
      fclose(fp);
    }

    ~Bitmap() {
      delete[] bitmap;
      bitmap = nullptr;
    }

    bool test(int k);

    void set(int k);

    void clear(int k);

    void dump(char *file);

    char *bits2string(int n);

    void expand(int k);

    void print(int n);
  };
}
