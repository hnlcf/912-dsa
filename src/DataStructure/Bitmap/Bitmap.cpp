#include <Bitmap.h>

void
dsa::Bitmap::init(int n) {
  bytes_num = (n + 7) / 8;
  bitmap = new unsigned char[bytes_num];
  memset(bitmap, 0, bytes_num);
}

bool
dsa::Bitmap::test(int k) {
  int           q = k >> 3;             // k / 8
  unsigned char offset = k & 0x07;      // k % 8
  unsigned char mask = 0x80 >> offset;  // the k-th bit

  return bitmap[q] & (mask);
}

void
dsa::Bitmap::set(int k) {
  expand(k);
  bitmap[k >> 3] |= (0x80 >> (k & 0x07));
}

void
dsa::Bitmap::clear(int k) {
  expand(k);
  bitmap[k >> 3] &= ~(0x80 >> (k & 0x07));
}

void
dsa::Bitmap::dump(char *file) {
  FILE *fp = fopen(file, "w");
  fwrite(bitmap, sizeof(unsigned char), bytes_num, fp);
  fclose(fp);
}

char *
dsa::Bitmap::bits2string(int n) {
  expand(n - 1);

  char *s = new char[n - 1];
  for (int i = 0; i < n; ++i) {
    s[i] = test(i) ? '1' : '0';
  }
  s[n] = '\0';

  return s;
}

void
dsa::Bitmap::expand(int k) {
  if (k < bytes_num * 8) {
    return;
  }
  int            oldN = bytes_num;
  unsigned char *oldMap = bitmap;

  init(2 * k);
  memcpy(bitmap, oldMap, oldN);

  delete[] oldMap;
}

void
dsa::Bitmap::print(int n) {
  expand(n);
  for (int i = 0; i < n; ++i) {
    printf(test(i) ? "1" : "0");
  }
}
