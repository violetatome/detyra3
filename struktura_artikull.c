#include <stdio.h>
#define GJAT_EMER 25
#define MAX_ARTIKULL 100

struct artikull {
    int numri;
    char emri[GJAT_EMER + 1];
    int gjendja;
} inventari[MAX_ARTIKULL];

//int inventari[MAX_ARTIKULL];

int nr_artikull = 0;

int gjej_artikull(int numer);
void shto(void);
void kerko(void);
void update(void);
void printo(void);
int gjendjeZero(struct artikull inventari[]);
int lexo_rresht(char str[], int n);
/* main: i kerkon perdoruesit te jape nje kod veprimi, dhe pastaj
therret funksionin perkates te kryeje veprimin e kerkuar.
Kjo gje perseritet deri sa perdoruesi te jape 'q'. Nese
perdoruesi jep nje kod te gabuar printohet nje mesazh gabimi*/
int main() {
    char kodi;

    for (;;) {

            printf("\nMenu:\n");
            printf("Shtyp 's' per te shtuar nje artikull te ri\n");
            printf("Shtyp 'k' per te kerkuar nese artikulli i deshiruar ekziston\n");
            printf("Shtyp 'u' per te perditesuar gjendjen e nje artikull\n");
            printf("Shtyp 'p' per te printuar te dhenat e nje artikulli\n");
            printf("Shtyp '0' per te gjetur numrin e artikujve, gjendja e te cileve eshte 0\n");
            printf("Shtyp '1' per te pare artikujt me numer(kod) njeshifror\n");
            printf("Shtyp 'q' per te dale\n");
            printf("Fut kodin e veprimit: ");
            scanf(" %c", &kodi);

        while (getchar() != '\n'); /* kalon deri te fundi i rreshtit */

        switch (kodi) {
            case 's': shto();
                break;
            case 'k': kerko();
                break;
            case 'u': update();
                break;
            case 'p': printo();
                break;
            case '0':
            printf("Numri i artikujve me gjendje 0: %d\n", gjendjeZero(inventari));
                break;
            case '1': nrNjeShifror(inventari);
                break;
            case 'q': return 0; // exit
            default: printf("Kod i gabuar\n");
        }
        printf("\n");
    }

    return 0;
}
/* Funksioni gjej_artikull kerkon ne matricen inventari artikull me
variablin numri sa vlera qe merr si argument. Kthen indeksin e
matrices nese gjen nje artikull me nje numer te tille, ne te
kundert kthen -1*/
int gjej_artikull(int numri) {
    int i;
    for (i = 0; i < nr_artikull; i++)
        if (inventari[i].numri == numri)
            return i;
    return -1;
}
/* Funksioni shto, i kerkon perdoruesit informacion per nje artikull te
ri dhe me pas e shton artikullin ne databaze. Kthen nje mesazh gabimi
nese artikulli egzistonte qe me pare ose nese databaza eshte plot */
void shto(void) {
    int artikull_nr;
    if (nr_artikull == MAX_ARTIKULL) {
        printf("Databaza eshte plot; nuk mund te shtohet artikull.\n");
        return;
    }
    printf("Fut numrin e artikullit: ");
    scanf("%d", &artikull_nr);
    if (gjej_artikull(artikull_nr) >= 0) {
        printf("Artikulli egziston.\n");
        return;
    }

    inventari[nr_artikull].numri = artikull_nr;
    printf("Jep emrin e artikullit: ");
    getchar();
    fgets(inventari[nr_artikull].emri, sizeof(inventari[nr_artikull].emri), stdin);
    inventari[nr_artikull].emri[strcspn(inventari[nr_artikull].emri, "\n")] = 0;
    printf("Jep gjendjen e artikullit: ");
    scanf("%d", &inventari[nr_artikull].gjendja);
    nr_artikull++;
}
/* Funksioni kerko i kerkon perdoruesit te jap nje numer artikulli,
pastaj kerkon ne databaze, nese artikulli me kete numer egziston kthen
emrin dhe gjendjen e artikullit, ne te kundert printon nje mesazh
gabimi. */
void kerko(void) {
    int i, numer;
    printf("Jep numrin e artikullit: ");
    scanf("%d", &numer);
    i = gjej_artikull(numer);
    if (i >= 0) {
        printf("Emri i artikullit: %s\n", inventari[i].emri);
        printf("Gjendja e artikullit: %d\n", inventari[i].gjendja);
    } else
        printf("Artikulli nuk u gjet.\n");
}
/* Funksioni update i kerkon perdoruesit te jape nje numer artikulli.
Kthen nje mesazh gabimi nese artikulli nuk egziston; ne te kundert
i kerkon perdoruesit te jape ndryshimin ne gjendje te artikullit
dhe i ben update. */
void update(void) {
    int i, numer, ndryshimi;
    printf("Jep numrin e artikullit: ");
    scanf("%d", &numer);
    i = gjej_artikull(numer);
    if (i >= 0) {
        printf("Jep ndryshimin ne gjendje te artikullit: ");
        scanf("%d", &ndryshimi);
        inventari[i].gjendja += ndryshimi;
    } else
        printf("Artikulli nuk u gjet.\n");
}
/* Funksioni printo, printon gjithe artikujt ne databaze, duke dhene
numrin, emrin dhe gjendjen e artikullit. Artikujt printohen me ate
renditje qe jane futur ne databaze. */
void printo(void) {
    int i;
    printf("Numri i Artikullit Emri i Artikullit Gjendja e Artikullit\n");
    for (i = 0; i < nr_artikull; i++)
        printf("%7d %25s %25d\n", inventari[i].numri, inventari[i].emri, inventari[i].gjendja);
}
/* Funksioni gjendjeZero kontrollon cdo artikull ne databaze dhe kur gjen nje
artikull, gjendja e se cilit eshte 0, variabla 'count' qe tregon numrin
e artikujve me gjendje 0 rritet me nje. Ne fund ai kthen vleren perfundimtare
te variablit 'count', pra numrin total te artikujve me gjendje zero. */
int gjendjeZero(struct artikull inventari[]) {
    int i;
    int count=0;
    for (i=0; i<nr_artikull; i++) {
       if (inventari[i].gjendja == 0){
           count++;
    }
    }
    if (count == 0){
        printf("Nuk u gjend asnje artikull me gjendje 0.\n");
    }
    return count;
}
/*Funksioni nrNjeShifor kerkon cdo artikull dhe gjen ne databaze
artikujt qe kane numer njeshifror, pra mes 0 dhe 10 dhe printon emrat
e ketyre artikujve. */
void nrNjeShifror(struct artikull inventari[]){
    int i,gjendet;
    printf("Artikujt me numer(kod) nje shifror: \n");
    for (i=0; i<nr_artikull; i++){
        if (inventari[i].numri < 10 && inventari[i].numri>0){
                printf("%s\n", inventari[i].emri);
                gjendet = 1;
        }
        if(!gjendet) {
        printf("Nuk u gjend asnje artikull me numer(kod) nje shifror.\n");
        }
    }
}

/* Funksioni lexo_rresht lexon karakteret e rreshtit nje nga nje dhe
i ruan tek str. Ndalon leximin e karaktereve nese numri i tyre ka
tejkaluar vleren e argumentit n. Kthen numrin e karaktereve te
ruajtura tek stringa str */
int lexo_rresht(char str[], int n) {
    int ch, i = 0;
    while ((ch = getchar()) == ' ')
        ;
    while ((ch != '\n') && (ch != EOF)) {
        if (i < n)
            str[i++] = ch;
        ch = getchar();
    }
    str[i] = '\0';
    return i;
}

