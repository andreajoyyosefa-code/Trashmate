#include "trashmate.cpp"
#include <emscripten/emscripten.h>

extern "C" {
EMSCRIPTEN_KEEPALIVE int jumlahData() { return JUMLAH_DATA; }
EMSCRIPTEN_KEEPALIVE const char* getNama(int i) { return database[i].nama.c_str(); }
EMSCRIPTEN_KEEPALIVE const char* getKategori(int i) { return database[i].kategori.c_str(); }
EMSCRIPTEN_KEEPALIVE const char* getPengelolaan(int i) { return database[i].pengelolaan.c_str(); }
EMSCRIPTEN_KEEPALIVE int cariSampahWasm(const char* in) { return cariSampah(in); }
}
