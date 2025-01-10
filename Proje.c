#include <stdio.h>
#include <stdbool.h>

#define MAX_BOYUT 23

char tahta[MAX_BOYUT][MAX_BOYUT];
int i, j, boyut;
int kirmizi_sayisi = 0;
int sari_sayisi = 0; 
int mavi_sayisi = 0;

void tahtaSifirla() {
  for (i =0; i< boyut; i++) {
      for (j = 0; j < boyut; j++) 
          tahta[i][j] = '.'; 
  }
}

void tahtaYazdir() {
    printf("   ");
    for (j=0; j <boyut; j++) {
        printf("%d ", j + 1);
    }
    printf("\n");

    for (i = 0; i < boyut; i++) {
        printf("%d  ", i + 1);
        for (j= 0; j < boyut; j++) {
            printf("%c ", tahta[i][j]);
        }
        printf("\n");
    }
}

bool gecerliKoordinat(int x, int y) {
 return x >= 0 && x < boyut && y >= 0 && y < boyut && tahta[x][y] == '.';
}

void tasSayilariGuncelle() {
    kirmizi_sayisi = sari_sayisi = mavi_sayisi = 0;
    for (i = 0; i< boyut; i++) {
      for (j = 0; j < boyut; j++) {
        if (tahta[i][j] == 'K')
          kirmizi_sayisi++;
        else if (tahta[i][j] == 'S') sari_sayisi++;
        else if (tahta[i][j] == 'M') {
            mavi_sayisi++;
        }
      }
    }
}

void tasCevir(int x, int y, char renk) {
    int yonler[8][2] = { 
        {-1, 0}, {1, 0}, {0, -1}, {0, 1},
        {-1, -1}, {-1, 1}, {1, -1}, {1, 1} 
    };
    for (i = 0; i < 8; i++) {
      int dx = yonler[i][0], dy = yonler[i][1];
      int nx = x + dx, ny = y + dy;
      bool degisim = false;

      while (nx >= 0 && nx < boyut && ny >= 0 && ny < boyut && 
             tahta[nx][ny] != '.' && tahta[nx][ny] != renk) {
          nx += dx;
          ny += dy;
          degisim = true;
      }

      if (degisim && nx >= 0 && nx < boyut && ny >= 0 && ny < boyut && tahta[nx][ny] == renk) {
          nx -= dx;
          ny -= dy;
          while (nx != x || ny != y) {
              tahta[nx][ny] = renk;
              nx -= dx; ny -= dy;
          }
      }
    }
}

void tasKoy(int x, int y, char renk) {
  tahta[x][y] = renk;
  tasCevir(x, y, renk);
}

void oyuncuKoy() {
    int x = boyut / 2, y = boyut / 2;

    while (!gecerliKoordinat(x, y)) {
        if (x>0) x--;
        else if (y > 0) y--;
    }

    tahta[x][y] = 'K';
}

int main() {
    printf("Oyun tahtasinin boyutunu girin (1-%d): ", MAX_BOYUT);
    if (scanf("%d", &boyut) != 1 || boyut < 1 || boyut > MAX_BOYUT) {
        printf("Gecersiz boyut! Program sonlandiriliyor.\n");
        return 1;
    }

    tahtaSifirla();
    oyuncuKoy();
    int oyuncu = 1;
    char renkler[3] = {'K', 'S', 'M'};
    bool oyun_devam_ediyor = true;

    while (oyun_devam_ediyor) {
        tahtaYazdir();
        printf("Oyuncu %d (%c) tas koymak icin koordinat girin (satir sutun, veya -1 cikis): ", oyuncu + 1, renkler[oyuncu]);
        int x, y;

        if (scanf("%d", &x) != 1) {
            printf("Gecersiz giris! Lutfen bir sayi giriniz.\n");
        } else if (x == -1) {
            printf("Oyun sonlandirildi.\n");
            oyun_devam_ediyor = false;
        } else if (scanf("%d", &y) != 1) {
            printf("Gecersiz giris! Lutfen bir sayi giriniz.\n");
        } else {
            x -= 1; y -= 1;

            if (gecerliKoordinat(x, y)) {
                tasKoy(x, y, renkler[oyuncu]);
                tasSayilariGuncelle();

                bool bos_var = false;
                for (i = 0; i < boyut && !bos_var; i++) {
                    for (j = 0; j < boyut && !bos_var; j++) {
                        if (tahta[i][j] == '.') {
                            bos_var = true;
                        }
                    }
                }

                if (!bos_var) {
                    printf("Oyun bitti!\n");
                    tahtaYazdir();
                    printf("Kirmizi: %d, Sari: %d, Mavi: %d\n", kirmizi_sayisi, sari_sayisi, mavi_sayisi);
                    if (kirmizi_sayisi > sari_sayisi && kirmizi_sayisi > mavi_sayisi)
                        printf("Kazanan: Kirmizi\n");
                    else if (sari_sayisi > kirmizi_sayisi && sari_sayisi > mavi_sayisi)
                        printf("Kazanan: Sari\n");
                    else if (mavi_sayisi > kirmizi_sayisi && mavi_sayisi > sari_sayisi)
                        printf("Kazanan: Mavi\n");
                    else printf("Beraberlik!\n");
                    
                    oyun_devam_ediyor = false;
                } else {
                    oyuncu = (oyuncu +1) % 3;
                }
            } else {
                printf("Gecersiz hamle! Tekrar deneyin.\n");
            }
        }
    }

    return 0;
}

