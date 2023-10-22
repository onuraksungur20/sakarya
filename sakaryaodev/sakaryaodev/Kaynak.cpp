#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <iomanip>
#include <algorithm>
#include <cmath>

using namespace std;

// Harf notu hesaplama fonksiyonu
string harfNotuHesapla(double puan) {
    if (puan >= 90) return "AA";
    else if (puan >= 85) return "BA";
    else if (puan >= 80) return "BB";
    else if (puan >= 75) return "CB";
    else if (puan >= 70) return "CC";
    else if (puan >= 65) return "DC";
    else if (puan >= 60) return "DD";
    else return "FF";
}

// Ogrenci struct
struct Ogrenci {
    string isim;
    string soyIsim;
    double vize;
    double odev1;
    double odev2;
    double kisaSinav1;
    double kisaSinav2;
    double yilIciNot;

    // Yýl içi notunu hesapla
    void hesaplaYilIciNot(double vizeAgirligi, double odevAgirligi, double kisaSinavAgirligi) {
        yilIciNot = vize * vizeAgirligi + (odev1 + odev2) * odevAgirligi + (kisaSinav1 + kisaSinav2) * kisaSinavAgirligi;
    }
};

int main() {
    int ogrenciSayisi;
    cout << "Sinifin ogrenci sayisini girin: ";
    cin >> ogrenciSayisi;

    double vizeAgirligi, odevAgirligi, kisaSinavAgirligi, yilIciEtkisi;
    cout << "Vize Agirligi (örnek: 0.2): ";
    cin >> vizeAgirligi;
    cout << "Odev Agirligi (örnek: 0.3): ";
    cin >> odevAgirligi;
    cout << "Kisa Sinav Agirligi (örnek: 0.2): ";
    cin >> kisaSinavAgirligi;
    cout << "Yil Ici Puaninin Gecme Notuna Etkisi (örnek: 0.4): ";
    cin >> yilIciEtkisi;

    double gecmeNotu;
    cout << "Gecme Notunu girin: ";
    cin >> gecmeNotu;

    vector<Ogrenci> sinif;

    // Ogrenci listesi olustur
    for (int i = 0; i < ogrenciSayisi; i++) {
        Ogrenci ogrenci;
        static string isimler[] = { "Ali", "Mehmet", "Ayþe", "Fatma", "Mustafa", "Eren" };
        static string soyisimler[] = { "Yýlmaz", "Demir", "Kaya", "Þahin", "Arslan", "Çelik" };

        random_device rd;
        mt19937 gen(rd());

        ogrenci.isim = isimler[gen() % 6];
        ogrenci.soyIsim = soyisimler[gen() % 6];

        uniform_real_distribution<double> dist1(0.0, 100.0); // %20 için 0-100
        ogrenci.vize = dist1(gen);

        uniform_real_distribution<double> dist2(0.0, 100.0); // %50 için 0-100
        ogrenci.odev1 = dist2(gen);

        uniform_real_distribution<double> dist3(0.0, 100.0); // %50 için 0-100
        ogrenci.odev2 = dist3(gen);

        uniform_real_distribution<double> dist4(0.0, 100.0); // %30 için 0-100
        ogrenci.kisaSinav1 = dist4(gen);

        uniform_real_distribution<double> dist5(0.0, 100.0); // %30 için 0-100
        ogrenci.kisaSinav2 = dist5(gen);

        ogrenci.hesaplaYilIciNot(vizeAgirligi, odevAgirligi, kisaSinavAgirligi);
        sinif.push_back(ogrenci);
    }

    vector<double> notlar;
    double toplamNot = 0.0;

    // Notlarý hesapla
    for (int i = 0; i < ogrenciSayisi; i++) {
        Ogrenci& ogrenci = sinif[i];
        notlar.push_back(ogrenci.yilIciNot);
        toplamNot += ogrenci.yilIciNot;
    }

    // En yüksek ve en düþük notlarý tespit et
    double enYuksekNot = *max_element(notlar.begin(), notlar.end());
    double enDusukNot = *min_element(notlar.begin(), notlar.end());

    // En yüksek ve en düþük notlarý alan öðrencilerin isimlerini bul
    string enYuksekNotAlanIsim;
    string enDusukNotAlanIsim;

    for (const Ogrenci& ogrenci : sinif) {
        if (ogrenci.yilIciNot == enYuksekNot) {
            enYuksekNotAlanIsim = ogrenci.isim + " " + ogrenci.soyIsim;
        }
        if (ogrenci.yilIciNot == enDusukNot) {
            enDusukNotAlanIsim = ogrenci.isim + " " + ogrenci.soyIsim;
        }
    }

    // Sinif istatistiklerini hesapla
    double sinifOrtalamasi = toplamNot / ogrenciSayisi;
    double sinifStandartSapma = 0.0;

    for (int i = 0; i < ogrenciSayisi; i++) {
        sinifStandartSapma += pow(notlar[i] - sinifOrtalamasi, 2);
    }
    sinifStandartSapma = sqrt(sinifStandartSapma / ogrenciSayisi);

    int harfNotlari[8] = { 0 }; // AA, BA, BB, CB, CC, DC, DD, FF
    for (int i = 0; i < ogrenciSayisi; i++) {
        string harfNot = harfNotuHesapla(notlar[i]);
        if (harfNot == "AA") harfNotlari[0]++;
        else if (harfNot == "BA") harfNotlari[1]++;
        else if (harfNot == "BB") harfNotlari[2]++;
        else if (harfNot == "CB") harfNotlari[3]++;
        else if (harfNot == "CC") harfNotlari[4]++;
        else if (harfNot == "DC") harfNotlari[5]++;
        else if (harfNot == "DD") harfNotlari[6]++;
        else harfNotlari[7]++;
    }

    double gecmeNotu = sinifOrtalamasi * yilIciEtkisi;
    cout << fixed << setprecision(2);
    cout << "Sinif Ortalamasi: " << sinifOrtalamasi << endl;
    cout << "Standart Sapma: " << sinifStandartSapma << endl;
    cout << "En Yuksek Not: " << enYuksekNot << " - Alan Ogrenci: " << enYuksekNotAlanIsim << endl;
    cout << "En Dusuk Not: " << enDusukNot << " - Alan Ogrenci: " << enDusukNotAlanIsim << endl;
    cout << "AA: " << harfNotlari[0] << " ogrenci" << endl;
    cout << "BA: " << harfNotlari[1] << " ogrenci" << endl;
    cout << "BB: " << harfNotlari[2] << " ogrenci" << endl;
    cout << "CB: " << harfNotlari[3] << " ogrenci" << endl;
    cout << "CC: " << harfNotlari[4] << " ogrenci" << endl;
    cout << "DC: " << harfNotlari[5] << " ogrenci" << endl;
    cout << "DD: " << harfNotlari[6] << " ogrenci" << endl;
    cout << "FF: " << harfNotlari[7] << " ogrenci" << endl;
    cout << "Gecme Notu: " << gecmeNotu << endl;

    return 0;
}
