#ifndef INC_912_DSA_EXERCISE_BITMAP_BITMAP_H_
#define INC_912_DSA_EXERCISE_BITMAP_BITMAP_H_

#include <cstdio>
#include <cstdlib>
#include <cstring>

namespace dsa {
class Bitmap {
 private:
  int bytes_num;
  unsigned char* bitmap;

 protected:
  void Init(int n);

 public:
  explicit Bitmap(int n = 8) { Init(n); }

  explicit Bitmap(char* file, int n = 8) {
    Init(n);
    FILE* fp = fopen(file, "r");
    fread(bitmap, sizeof(unsigned char), bytes_num, fp);
    fclose(fp);
  }

  ~Bitmap() {
    delete[] bitmap;
    bitmap = nullptr;
  }

  bool Test(int k);

  void Set(int k);

  void Clear(int k);

  void Dump(char* file);

  char* Bits2String(int n);

  void Expand(int k);

  void Print(int n);
};
}  // namespace dsa

#endif