#include <string>
#include <cctype>
#include <emscripten/emscripten.h>

using namespace std;

struct Sampah {
    string nama, kategori, kode, pengelolaan;
};

#define OR(n,p) {n,"Sampah Organik","organik",p}
#define AN(n,p) {n,"Sampah Anorganik","anorganik",p}
#define B3(n,p) {n,"Sampah B3 (Bahan Berbahaya & Beracun)","b3",p}
#define RS(n,p) {n,"Sampah Residu","residu",p}

Sampah database[] = {
    // ORGANIK
    OR("sisa makanan","Olah menjadi kompos atau pakan maggot."),
    OR("kulit buah","Olah menjadi kompos atau eco-enzyme."),
    OR("daun kering","Kumpulkan untuk dijadikan pupuk kompos."),
    OR("sayuran","Olah menjadi pupuk organik cair atau kompos."),
    OR("tulang ayam","Dapat diolah menjadi kompos dengan pencacahan khusus atau pakan hewan."),
    OR("kulit telur","Haluskan untuk dijadikan pupuk tanaman sumber kalsium."),
    OR("ampas teh","Campurkan langsung ke media tanam atau komposer."),
    OR("ampas kopi","Sangat baik untuk kompos dan media tanam tanaman hias."),
    OR("bonggol sayur","Olah menjadi kompos bersama sisa sayuran lainnya."),
    // ANORGANIK
    AN("botol plastik","Remukkan botol, pisahkan tutupnya, lalu setor ke bank sampah/daur ulang."),
    AN("kaleng","Bersihkan sisa isi, pipihkan, dan salurkan ke pengepul logam/daur ulang."),
    AN("kertas","Pastikan tidak basah/berminyak, lalu kumpulkan untuk didaur ulang."),
    AN("kaca","Bungkus rapat agar tidak melukai petugas, lalu serahkan ke pusat daur ulang."),
    AN("kardus","Lipat rapi dan simpan di tempat kering untuk didaur ulang."),
    AN("ember plastik","Salurkan ke bank sampah jika masih utuh atau daur ulang plastik."),
    AN("sikat gigi","Bersihkan sebelum disetor atau didaur ulang."),
    AN("kabel listrik","Pisahkan tembaga di dalamnya untuk disetor ke pengepul rongsokan."),
    // B3
    B3("baterai bekas","Jangan dibuang sembarangan! Serahkan ke dropbox limbah elektronik/B3."),
    B3("lampu bekas","Bungkus dengan kardus agar tidak pecah dan serahkan ke fasilitas limbah B3."),
    B3("kaleng cat","Simpan tertutup rapat dan serahkan ke pengelola limbah B3."),
    B3("obat kadaluarsa","Hancurkan kemasan dan serahkan ke apotek atau fasilitas kesehatan."),
    B3("termometer merkuri","Jangan dipecahkan! Serahkan khusus ke pengelola limbah medis/B3."),
    // RESIDU
    RS("popok bayi","Bersihkan kotorannya ke kloset, gulung rapat, lalu buang ke tempat sampah residu."),
    RS("popok dewasa","Gulung rapat dan bungkus plastik sebelum dibuang ke tempat sampah residu."),
    RS("pembalut wanita","Bungkus dengan kertas atau plastik rapat, lalu buang ke tempat sampah residu."),
    RS("tisu wajah","Buang ke tempat sampah residu karena serat kertas sudah kotor dan tidak bisa didaur ulang."),
    RS("tisu basah","Buang ke tempat sampah residu."),
    RS("masker medis","Gunting tali pengikatnya agar tidak menjerat hewan, bungkus rapat, lalu buang ke residu."),
    RS("puntung rokok","Pastikan api sudah mati total, lalu buang ke tempat sampah residu."),
    RS("kemasan sachet","Buang ke tempat sampah residu karena berlapis plastik dan aluminium foil."),
    RS("styrofoam","Buang ke tempat sampah residu karena sangat sulit diurai dan didaur ulang."),
    RS("kertas nasi","Buang ke tempat sampah residu karena mengandung lapisan plastik/minyak."),
    RS("sedotan plastik","Buang ke tempat sampah residu jika tipis, kotor, atau rusak."),
    RS("pecahan keramik","Bungkus tebal agar aman bagi petugas, lalu buang ke tempat sampah residu."),
    RS("lakban","Buang ke tempat sampah residu."),
    RS("struk belanja","Kertas termal struk tidak bisa didaur ulang karena bahan kimia, buang ke residu."),
    RS("tipe-x","Buang ke tempat sampah residu."),
    RS("pulpen rusak","Buang ke tempat sampah residu."),
    RS("balon karet","Buang ke tempat sampah residu.")
};

const int JUMLAH_DATA = sizeof(database) / sizeof(database[0]);

string hurufKecil(string teks) {
    for (size_t i = 0; i < teks.length(); i++) teks[i] = tolower((unsigned char)teks[i]);
    return teks;
}

int cariSampah(const string& input) {
    string kataKunci = hurufKecil(input);
    for (int i = 0; i < JUMLAH_DATA; i++)
        if (hurufKecil(database[i].nama).find(kataKunci) != string::npos) return i;
    return -1;
}

// ===== Fungsi yang dipanggil dari JavaScript =====
extern "C" {
    EMSCRIPTEN_KEEPALIVE int jumlah() { return JUMLAH_DATA; }
    EMSCRIPTEN_KEEPALIVE const char* nama(int i)        { return database[i].nama.c_str(); }
    EMSCRIPTEN_KEEPALIVE const char* kategori(int i)    { return database[i].kategori.c_str(); }
    EMSCRIPTEN_KEEPALIVE const char* kode(int i)        { return database[i].kode.c_str(); }
    EMSCRIPTEN_KEEPALIVE const char* pengelolaan(int i) { return database[i].pengelolaan.c_str(); }
    EMSCRIPTEN_KEEPALIVE int cari(const char* teks)     { return cariSampah(teks); }
}

