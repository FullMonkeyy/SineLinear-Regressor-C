
#include <iostream>
#include <math.h>


#define DIM 30
#define NREL 1000
#define MAX 100
#define MIN -100
#define FRQMAX 5
#define FRQMIN -5
#define AMPMAX 15
#define AMPMIN -15
#define PIG 3.14159265

#pragma warning(disable : 4996)

typedef struct {

    double x;
    double y;

}PUNTO;
typedef struct {

    double m;
    double q;
    PUNTO a;
    PUNTO b;

}FUNZIONE;
typedef struct {

    double q;
    double m;
    double amplitudine;
    double frequenza;
    double spostamento;
    double periodo;
    double errore;
    int ntentativo;
    int precisione;

}OSCILLANTE;

FUNZIONE genera(PUNTO a, PUNTO b);
void OrdinaPunti(PUNTO punti[], int np);
int CaricaFunzioni(FUNZIONE* caso, PUNTO analisi[], int np);
int GeneraPuntiACaso(PUNTO punti[]);
int CalcolaNfunzioni(int np);
FUNZIONE predizione(FUNZIONE* caso, int nfunzioni);
double mediaQ(FUNZIONE caso[], int nfunzioni);
double mediaM(FUNZIONE caso[], int nfunzioni);
void InserisciPunti(PUNTO x[], int* np);
void Menu(FUNZIONE lavoro[], FUNZIONE* finale, PUNTO punti[], OSCILLANTE *magnitudo);
void Opzioni(int np);
void StampaRelazioni(PUNTO punti[], int np);
void Allena(FUNZIONE lavoro[], FUNZIONE* finale, PUNTO punti[], int np, OSCILLANTE* magnitudo);
double Media(double Distanza[], int np);
FUNZIONE FunDisPun(FUNZIONE finale, PUNTO a);
FUNZIONE NuovoFunDisPun(FUNZIONE finale, PUNTO a);
double Distanza(FUNZIONE finale, PUNTO a);
void PREDIZIONE(FUNZIONE finale, OSCILLANTE magnitudo);
void PredizioneTotale(FUNZIONE finale);
double ImprecisioneMedia(OSCILLANTE definitiva, FUNZIONE finale, PUNTO punti[], int np);
double DistanzaOsciPUNTO(FUNZIONE finale, PUNTO a, OSCILLANTE prova);
OSCILLANTE Magnitudo(FUNZIONE finale, PUNTO a[], int np, int perc);
double DistanzaMedia(FUNZIONE finale, PUNTO a[], OSCILLANTE prova, int np);
double FunzioneFinale(OSCILLANTE definitiva, double x);
double grad2rad(double x);
void  CancellaUNARelazione(PUNTO a[], int indice,int* np);
void CancellaDetRelazione(PUNTO a[], int* np);
void CancellaDataSet(int* np);
void PredizioneTotale(OSCILLANTE definitiva);
void StampaInformazioniModello(FUNZIONE finale, OSCILLANTE definitivo, int np);
int CaricaElenco(char elenco[][DIM], FILE* file);
bool ChekFile(PUNTO x[], int* np, char elenco[][DIM]);
void SpartisciXeY(PUNTO x[], int* np, char elenco[][DIM]);
int ncifreINT(int x);
double AMPMASSIMA(FUNZIONE finale, PUNTO a[], int np);
int RintracciaDecimale(char spartizione[]);
int main()
{

    FUNZIONE lavoro[NREL*20];
    FUNZIONE finale;
    PUNTO punti[NREL];
    OSCILLANTE magnitudo;
    

    Menu(lavoro, &finale, punti,&magnitudo);

}
bool ChekFile(PUNTO x[], int* np, char elenco[][DIM]) {

    FILE* DATI = fopen("dati.txt", "r");

    if (DATI == NULL) {

        printf("File dati non rilevato\n");;

        return false;

    }
    else {

        printf("\n\nFILE DATI RILEVATO.");

        *np = CaricaElenco(elenco, DATI);
        fclose(DATI);

        SpartisciXeY(x, np, elenco);

        return true;

    }


}
void SpartisciXeY(PUNTO x[], int* np, char elenco[][DIM]) {

    char strX[DIM];
    char strY[DIM];
    bool decimale;
    int j,c;
    int ncif;
    int k;
    double prima;
    for (int i = 0; i < *np; i++) {

        decimale = false;

        j = 0;
        k = 0;

        while (elenco[i][j] != '\t') {

            strX[k] = elenco[i][j];

            j++;
            k++;
        }

        strX[j] = '\0';

        j++;
        k = 0;
        while (elenco[i][j] != '\0') {

            strY[k] = elenco[i][j];

            j++;
            k++;
        }

        strY[k] = '\0';

        if (strY[0] == '0') {
            decimale = true;

            for (int ns = 0; ns < 2; ns++) {

                for (int p = 0; p < strlen(strY); p++) {

                    strY[p] = strY[p + 1];

                }

            }

            x[i].y = atoi(strY);

            ncif = ncifreINT(x[i].y);

            x[i].y = x[i].y / pow(10, ncif);

        }
        else if (RintracciaDecimale(strY) != -1) {

            prima = atoi(strY);
            c = RintracciaDecimale(strY);

            for (int ns = 0; ns <= c; ns++) {

                for (int p = 0; p < strlen(strY); p++) {

                    strY[p] = strY[p + 1];

                }

            }

            x[i].y = atoi(strY);

            ncif = ncifreINT(x[i].y);

            x[i].y = x[i].y / pow(10, ncif);

            x[i].y = x[i].y + prima;

        }
        else {

            x[i].y = atoi(strY);

        }



        if (strX[0] == '0') {
            decimale = true;

            for (int ns = 0; ns < 2; ns++) {

                for (int p = 0; p < strlen(strX); p++) {

                    strX[p] = strX[p + 1];

                }

            }

            x[i].x = atoi(strX  );

            ncif = ncifreINT(x[i].x);

            x[i].x = x[i].x / pow(10, ncif);

        }
        else if(RintracciaDecimale(strX) != -1) {

            prima = atoi(strX);
            c = RintracciaDecimale(strX);

            for (int ns = 0; ns <= c; ns++) {

                for (int p = 0; p < strlen(strX); p++) {

                    strX[p] = strX[p + 1];

                }

            }

            x[i].x = atoi(strX);

            ncif = ncifreINT(x[i].x);

            x[i].x = x[i].x / pow(10, ncif);

            x[i].x = x[i].x + prima;

        }
        else{

            x[i].x = atoi(strX);

        }


    }


}
void Menu(FUNZIONE lavoro[], FUNZIONE* finale, PUNTO punti[], OSCILLANTE* magnitudo) {

    int np = 0;
    int opz;
    bool uscita = false;
    bool allenato = false;
    char elenco[NREL][DIM];

    if (ChekFile(punti, &np, elenco)) {

        printf("DATASET CARICATO\n");

    }

    
    do {

        printf("\nDeveloper: Scapellato Davide\n");

        Opzioni(np);
        scanf_s("%d", &opz);

        system("cls");

        printf("\n\nDeveloper: Scapellato Davide\n");

        switch (opz) {

        case 1:

            printf("\n<<CREA NUOVA RELAZIONE>>\n");

            InserisciPunti(punti, &np);

            OrdinaPunti(punti, np);


            break;
        case 2:

            printf("\n<<RELAZIONI REGISTRATE>>\n");

            StampaRelazioni(punti, np);

            break;
        case 5:

            if (np < 2)
                printf("\nPer allenare il modello matematico di predizione, bisogna inserire ALMENO 2 relazioni\n");

            else {

                Allena(lavoro, finale, punti, np,magnitudo);
                allenato = true;
                printf("\nMODELLO ALLENATO CORRETTAMENTE\n");

            }

            break;

        case 7:

            if (allenato) {

                printf("\n<<PREDIZIONE>>\n");

                PREDIZIONE(*finale,*magnitudo);

            }
            else
                printf("\nMODELLO NON ANCORA ALLENATO\n");

            break;
        case 6:
                     
            if (allenato) {

                printf("\n<<IMPRECISIONE>>\n");

                ImprecisioneMedia(*magnitudo,*finale, punti, np);

            }
            else
                printf("\nMODELLO NON ANCORA ALLENATO\n");

            break;

        case 3:

            CancellaDetRelazione(punti, &np);

            break;
        case 4:

            CancellaDataSet(&np);

            break;

        case 8:

            if (allenato) {

                printf("\n<<PREDIZIONE TOTALE>>\n");

                PredizioneTotale(*magnitudo);

            }
            else
                printf("\nMODELLO NON ANCORA ALLENATO\n");


            break;
        case 9:

            if (allenato) {

                printf("\n<<INFORMAZIONI SUL MODELLO>>\n");

                StampaInformazioniModello(*finale, *magnitudo, np);

            }
            else
                printf("\nMODELLO NON ANCORA ALLENATO\n");


            break;
        case 10:

            uscita = true;

            break;
        default:

            printf("\nOpzione non prevista");

            break;

        }

        printf("\n\n");
        system("pause");
        system("cls");

    } while (!uscita);

}
void Opzioni(int np) {

    printf("\nNUMERO RELAZIONI REGISTRATE: %d\n", np);
    printf("\n1)Registra una nuova relazione ");
    printf("\n2)Visualizza relazioni");
    printf("\n3)Cancella una relazione precisa");
    printf("\n4)Resetta Dataset");
    printf("\n5)Allena modello");
    printf("\n6)Imprecisione lineare");
    printf("\n7)PREDIZIONE");
    printf("\n8)ANDAMENTO LOGICO FUNZIONALE");
    printf("\n9)Informazioni sul modello");
    printf("\n10)Chiudi");
    printf("\nScelta (numero opzione): ");

}
FUNZIONE genera(PUNTO a, PUNTO b) {

    FUNZIONE lavoro;
    lavoro.a = a;
    lavoro.b = b;

    lavoro.m = (lavoro.b.y - lavoro.a.y) / (lavoro.b.x - lavoro.a.x);
    lavoro.q = a.y - lavoro.m * a.x;

    return lavoro;

}
void OrdinaPunti(PUNTO punti[], int np) {

    PUNTO temp;

    for (int i = 0; i < np - 1; i++) {

        for (int j = i; j < np; j++) {

            if (punti[j].x < punti[i].x) {

                temp = punti[i];
                punti[i] = punti[j];
                punti[j] = temp;

            }

        }

    }

}
int CaricaFunzioni(FUNZIONE* caso, PUNTO analisi[], int np) {

    int i, j, k;

    k = 0;

    for (i = 0; i < np; i++) {

        for (j = i - 1; j >= 0; j--) {

            if (!(analisi[i].x == analisi[j].x && analisi[j].y != analisi[i].y)) {

                caso[k] = genera(analisi[i], analisi[j]);
                k++;

            }

        }

    }

    return k;

}
int GeneraPuntiACaso(PUNTO punti[]) {

    PUNTO x;

    punti[0].x = rand() % (MAX - MIN + 1) + MIN;
    punti[0].y = rand() % (MAX - MIN + 1) + MIN;

    for (int i = 1; i < DIM; i++) {

        punti[i].x = rand() % (MAX - MIN + 1) + MIN;
        punti[i].y = rand() % (MAX - MIN + 1) + MIN;



    }

    OrdinaPunti(punti, DIM);

    return DIM;
}
int CalcolaNfunzioni(int np) {

    int i;
    int somma = 0;
    int k;

    for (i = 0; i < np; i++) {

        somma = somma + i - 1;

    }

    return somma;



}
FUNZIONE predizione(FUNZIONE* caso, int nfunzioni) {

    FUNZIONE finale;
    double m;
    double q;
    finale.m = mediaM(caso, nfunzioni);
    finale.q = mediaQ(caso, nfunzioni);
    finale.a.x = 0;
    finale.b.y = 0;

    finale.a.y = finale.m * finale.a.x + finale.q;
    finale.b.x = (finale.b.y - finale.q) / finale.m;

    return finale;

}
double mediaQ(FUNZIONE caso[], int nfunzioni) {

    double somma = 0;

    for (int i = 0; i < nfunzioni; i++) {

        somma = somma + caso[i].q;

    }


    return somma / nfunzioni;

}
double mediaM(FUNZIONE caso[], int nfunzioni) {

    double somma = 0;

    for (int i = 0; i < nfunzioni; i++) {

        somma = somma + caso[i].m;

    }


    return somma / nfunzioni;


}
void InserisciPunti(PUNTO x[], int* np) {

    printf("\nInserisci valore di X %d: ", (*np) + 1);
    scanf_s("%lf", &x[*np].x);

    printf("\nInserisci valore di Y %d: ", (*np) + 1);
    scanf_s("%lf", &x[*np].y);

    printf("\nPunto registrato in data base correttamente. \n");

    (*np)++;

}
void StampaRelazioni(PUNTO punti[], int np) {

    for (int i = 0; i < np; i++) {

        printf("\n| X%d = %lf | Y%d = %lf |", i + 1, punti[i].x, i + 1, punti[i].y);

    }

}
void Allena(FUNZIONE lavoro[], FUNZIONE* finale, PUNTO punti[], int np, OSCILLANTE *magnitudo) {

    int pre;

    int NF=CaricaFunzioni(lavoro, punti, np);

    *finale = predizione(lavoro, NF);

    do {
        printf("\nLIVELLO ALLENAMENTO:\n");
        printf("\n1)PRECISO (circa 20 secondi)");
        printf("\n2)SUPER PRECISO (tra i 2 minuti ei 5)");

        printf("\n\nScelta: ");
        scanf_s("%d", &pre);

    } while (pre != 1 && pre != 2);

    *magnitudo = Magnitudo(*finale, punti, np, pre);

}
void PREDIZIONE(FUNZIONE finale, OSCILLANTE magnitudo) {

    double x;
    double mainx;
    double mainy;
    double angolo = atan(finale.m);
    double y, frq, amp, q, m, s;
    frq = magnitudo.frequenza;
    amp = magnitudo.amplitudine;
    q = magnitudo.q;
    m = magnitudo.m;
    s = magnitudo.spostamento;

   
    printf("\nInserisci il valore di X: ");
    scanf_s("%lf", &x);
    
    mainy = amp * sin(frq * x + s) + m * x + q;
    y = m * x + q;

    printf("\nConsiderando l'oscillazione d'imprecisione (%2.3lf ) il valore potrebbe valere: %2.3lf", magnitudo.errore,mainy);
    printf("\nValore teorico (efficente se il margine d'errore e' minimo): %2.3lf", y);
}
void PredizioneTotale(FUNZIONE finale) {

    int npre;
    int intervallo;
    int x=0;
    double y;

    printf("\nQuante predizioni si vogliono effettuare?: ");
    scanf_s("%d", &npre);

    printf("\nOgni quanto n intervallo si vuole calcolare la predizione?: ");
    scanf_s("%d", &intervallo);

    for (int i = 0; i < npre; i++) {


        y = finale.m * x + finale.q;

        printf("\n| X = %d | Y = %lf |", x,y);
        x++;

    }




}
double Distanza(FUNZIONE finale, PUNTO a) {

    FUNZIONE VersoRetta = NuovoFunDisPun(finale, a);
    PUNTO incontro;
    double distanza;
    double y,m,q;
    m = finale.m;
    q = finale.q;
    y = m * a.x + q;

    distanza = y - a.y;

    if (y < a.y)
        distanza = distanza*(-1);
    
    return distanza;

}
double AMPMASSIMA(FUNZIONE finale, PUNTO a[], int np) {

    double distmax = 0;
    double distlavoro;

    for (int i = 0; i < np; i++) {

        distlavoro = Distanza(finale, a[i]);

        if (distlavoro > distmax) {

            distmax = distlavoro;

        }

    }

    return distmax;

}
double grad2rad(double x)
{
    double ris;

    ris = 3.14 * x / 180;

    return ris;
}
FUNZIONE FunDisPun(FUNZIONE finale, PUNTO a) {

    PUNTO retta;
    double m;
    double perpendicolareX;
    double Angolo = atan(finale.m);
    double base;
    double altezza;
    double Angprimario = grad2rad(180) - grad2rad(90) - Angolo;//espresso in radiante periodico
    double AngSecondario;
    FUNZIONE PuntoARetta;
    retta.y = (finale.m * a.x + finale.q);
    perpendicolareX = a.y - retta.y;
    base = perpendicolareX * cos(Angprimario);
    AngSecondario = grad2rad(90) - Angprimario;
    altezza = base * cos(AngSecondario);
    retta.x = altezza + (((finale.m * a.x + finale.q) - finale.q) / finale.m);
    retta.y = finale.m * retta.x + finale.q;

    if (retta.x < a.x)
        PuntoARetta = genera(retta, a);
    else
        PuntoARetta = genera(a, retta);

    return PuntoARetta;

}
FUNZIONE NuovoFunDisPun(FUNZIONE finale, PUNTO a) {

    FUNZIONE lavoro;

    lavoro.m = (-1) * (1 / finale.m);
    lavoro.q = a.y - lavoro.m * a.x;


    return lavoro; //(sta roba mi sta facendo piangere e non poco)

}
double ImprecisioneMedia(OSCILLANTE definitiva, FUNZIONE finale, PUNTO punti[], int np) {

    int i;
    double somma = 0;
    double imprecisione;

    for(i=0; i<np; i++){
    
        imprecisione = DistanzaOsciPUNTO(finale, punti[i], definitiva);
        somma = somma + imprecisione;
        printf("\nLa relazione numero %d dista dal filo logico di %lf unita'", i + 1, imprecisione);
    
    }

    printf("\nLa media di imprecisione e' di %lf", somma / np);

    return 0;

}
double DistanzaOsciPUNTO(FUNZIONE finale, PUNTO a, OSCILLANTE prova) {
    
    //algoritmo funzionante ma trasceso da quello successivo

    FUNZIONE VersoRetta = NuovoFunDisPun(finale, a);
    PUNTO incontro;
    PUNTO oscillante;
    double distanza;
    double rettaproiettatax;
    double angolo = atan(finale.m);
    double y, frq, amp,q,m,s;

    frq = prova.frequenza;
    amp = prova.amplitudine;
    q = prova.q;
    m = prova.m;
    s = prova.spostamento;
    y = amp * sin(frq * a.x+s) + m * a.x + q;

    distanza = y - a.y;


    if (y < a.y)
        distanza = distanza*(-1);
  

    return distanza;
}
OSCILLANTE Magnitudo(FUNZIONE finale, PUNTO a[], int np, int perc) {

    OSCILLANTE migliore;
    OSCILLANTE lavoro;
    double intervallo = 0.1;
   float i, j, p,n,z,T,d;
    int t,pre;
    int l;
    int k;
    float c;
    double ampmax= AMPMASSIMA(finale,a,np);

    double ampmin = 0 - ampmax;
    lavoro.q = finale.q;
    lavoro.m = finale.m;
    migliore.errore = 999999999999;
    n = 0;
    t = 0;

    if (ampmax == 0) {

        p = 1;

    }
    else
        p = ampmax;

    system("cls");
    printf("\n\n<<ALLENAMENTO>>\n");

    switch (perc) {

        case 1:

            intervallo = 0.1;

            n = (FRQMAX * 2 * p * 2) /intervallo/intervallo;
            break;

        case 2:

            intervallo = 0.01;
            n = (FRQMAX * 2 * p * 2) / intervallo / intervallo / intervallo;
            break;

    }

    

    l = 0;

    i = FRQMIN;

        while (i <= FRQMAX) {

            lavoro.frequenza = i;

            j = ampmin;

            z = 0;
      
            d = i;

            if (i == 0)
                d = 1;

            T = (2 * PIG) / (sqrt(pow(d, 2)));

            while (z < T) {

                lavoro.spostamento = z;

                j = 0;

                do {
                   

                    lavoro.amplitudine = j;

                    lavoro.errore = DistanzaMedia(finale, a, lavoro, np) + pow(sqrt(pow((j  *  i) /np, 2 )),2);

                    if (lavoro.errore < migliore.errore) {
                        migliore = lavoro;
                        migliore.ntentativo = l;
                    }


                    j = j + intervallo;

                   

                } while (j <= ampmax);

                z = z + intervallo;

            }

            p = l * 100 / (10/intervallo);
 
                
                printf("\nSTATO ALLENAMENTO: %3.2lf%%", p);
 

                if (i >= -0.15 && i < 0)
                    i = 0;
                else
                    i = i + intervallo;

            l++;

        }

    migliore.m = finale.m;
    migliore.q = finale.q;
    migliore.precisione = perc;

    return migliore;

}
double DistanzaMedia(FUNZIONE finale, PUNTO a[], OSCILLANTE prova, int np) {


    double sommpunteggio = 0;
    double punteggiolavoro;
    int k;
    for (k = 0; k < np; k++) {

        punteggiolavoro = DistanzaOsciPUNTO(finale, a[k], prova);
        sommpunteggio = sommpunteggio + punteggiolavoro;

    }

    return sommpunteggio / np;

}
double FunzioneFinale(OSCILLANTE definitiva, double x) {

    double y,ygame;
    double mainx;
    double mainy;
    double angolo = atan(definitiva.m);
    double amp = definitiva.amplitudine;
    double frq = definitiva.frequenza;
    double m = definitiva.m;
    double q = definitiva.q;
    double s = definitiva.spostamento;

    mainy = amp * sin(frq * x+s) + m * x + q;

    return mainy;

}
void  CancellaUNARelazione(PUNTO a[], int indice, int* np) {

    for (int i = indice; i < *np; i++) {

        a[i] = a[i + 1];

    }

    (*np)--;

}
void CancellaDetRelazione(PUNTO a[], int* np) {

    int n;

    printf("\n<<DIGITARE IL NUMERO DELLA RELAZIONE DA ELIMINARE>>");

    StampaRelazioni(a, *np);

    printf("\nScelta (-1 per annullare): ");
    scanf_s("%d", &n);


    if (n != -1) {

        n--;
        CancellaUNARelazione(a, n, np);
        system("cls");
        printf("\nCancellato correttamente");

    }
    else
        printf("\nAnnullamento confermato");

}
void CancellaDataSet(int* np) {

    char c;
    bool richiedi = false;

    do {

        system("cls");
        richiedi = false;

        printf("\n\n<<ELIMINAZIONE DATASET>>");
        printf("\n\nCancellare dataset(S/N)?: ");
        scanf_s(" %c", &c);

        switch (c) {

        case 'n':
        case 'N':

            printf("\n\nDataset invariato");

            break;
        case 's':
        case 'S':

            *np = 0;
            printf("\n\nDATASET RESETTATO");

            break;
        default:

            printf("\nOpzione non prevista\n");
            richiedi = true;
            break;
        }
    } while (richiedi);
}
void PredizioneTotale(OSCILLANTE definitiva) {

    int npre;
    int intervallo;
    int x = 0;
    double y;

    printf("\nQuante predizioni si vogliono effettuare?: ");
    scanf_s("%d", &npre);

    printf("\nOgni quanto n intervallo si vuole calcolare la predizione?: ");
    scanf_s("%d", &intervallo);

    for (int i = 0; i < npre; i++) {


        y = FunzioneFinale(definitiva, x);

        printf("\n| X = %d | Y = %lf |", x, y);
        x=x+intervallo;

    }


}
void StampaInformazioniModello(FUNZIONE finale,  OSCILLANTE definitivo, int np) {

    printf("\nMODELLO LINEARE DI TIPO ""COMPLESSO""");
    printf("\nPRECISIONE DI LIVELLO %d ", definitivo.precisione);
    printf("\nQUESTO MODELLO E' STATO GENERATO AL TEST N %d", definitivo.ntentativo+1);
    printf("\nAmpiezza logica: %2.3lf", definitivo.amplitudine);
    printf("\nFrequenza logica: %2.3lf",definitivo.frequenza);
    printf("\nSpostamento logico: %2.3f", definitivo.spostamento);
    printf("\nPendenza analitica: %2.3lf", definitivo.m);
    printf("\nIntersezione analitica: %2.3lf", definitivo.q);
    printf("\nPunteggio errore: %2.3lf", definitivo.errore);
    printf("\n\nDeveloper: Scapellato Davide");

}
int CaricaElenco(char elenco[][DIM], FILE* file) {

    int i = 0;

    while (!feof(file) && i<NREL) {

        fgets(elenco[i], DIM, file);

        for (int j = 0; j < DIM; j++) {

            if (elenco[i][j] == '\n') {

                elenco[i][j] = 0;
                break;

            }

        }

        i++;

    }

    elenco[i - 1][0] = 0;

    return i - 1;

}
int ncifreINT(int x) {

    int i = 0;
    bool indiv=false;


    while (!indiv) {

        if (x - pow(10, i) < 0) {

            indiv=true;

        }

        i++;


    }

    return i - 1;

}
int RintracciaDecimale(char spartizione[]) {

    int i = 0; 

    while (spartizione[i] != '\n') {

        if (spartizione[i] == '.') {

            return i;

        }

        i++;
        
    }

    return -1;

}