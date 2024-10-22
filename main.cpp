#include <iostream>
#include <fstream>
#include <cstring>
#include <cctype>
#include <vector>

using namespace std;

char s[256];


//eliminate Spaces ' '
char* eliminareSpatii(char *s)
{
    char *p;

    //copy the original string to break down with strtok
    char *c = new char[strlen(s) + 1];
    strcpy(c, s);

    char *rezultat = new char[strlen(s) + 1];
    rezultat[0] = '\0';  // initialize string for concatenation

    p = strtok(c, " ");
    while (p != NULL)
    {
        strcat(rezultat, p);
        p = strtok(NULL, " ");
    }

    delete[] c;  
    return rezultat;
}

int countDecimalNintyOne(char *s)
{
    int Stiva[1000] = {0}; 
    int nrS = 0;
    int cnt = 0;
    int maxi = 0;
    for(int i = 0 ; s[i] ; i ++)
        if(s[i] == '{')
        {
            Stiva[++nrS] = ++cnt;
            if(maxi < cnt)
                maxi = cnt;
        }
        else
        {
            
            nrS --;
        }
    return maxi;
}

void stergeCaracterPePozitie(char* sir, int pozitie) {
    // Mutăm caracterele spre stânga
    for (int i = pozitie; i < strlen(sir); i++) {
        sir[i] = sir[i + 1];
    }

    // Terminăm șirul cu '\0'
    sir[strlen(sir) - 1] = '\0';
}

int v1[256], v2 [256], copyV1[256], copyV2[256];
char vector_chey[256][256]; // Vector pentru a stoca cheile
char vector_words[256][256];

int main()
{
    int n,i, j=0, k=0, l=0;
    cin.getline(s, 256);

    //eliminate spaces
    char *new_s = eliminareSpatii(s);

    strcpy(s, new_s);
    delete[] new_s;

    cout << s << endl;

    //avem 2 vectori
    //v1 - in care indexul din vector adica i reprezinta numarul de ordine pentru caracterul '{' iar valoarea efectiva v1[i] reprezinta indexul din sir
    //v2 - in care indexul din vector adica i reprezinta numarul de ordine pentru caracterul '}' iar valoarea efectiva v2[i] reprezinta indexul din sir

    j = strlen(s) - 1; 
    for(i=0; i < strlen(s); i++)
    {
        if(s[i] == '{')
        {
            v1[k] = i;
            k++;
        }
        if(s[j] == '}')
        {
            v2[l] = j;
            l++;
        }
        j--;
    }

    // Copierea vectorilor v1 și v2 în copyV1 și copyV2
    for (int m = 0; m < k; m++) {
        copyV1[m] = v1[m];
    }

    for (int n = 0; n < l; n++) {
        copyV2[n] = v2[n];
    }

    n=l;

    // falag reprezinta ca suntem pe caracterul '{' cel mai din stanga
    int flag = 0;

    // reprezinta ca suntem  inside { {} }
    int flag2 = 0;

    //reset k and l for iteration
    k=0;
    l=0;

    // j = 0 reprezinta indexul din v1 in care stim pozitia primul caracter '{' si folosim si faptul ca v2[j] stocheaza cel mai din dreapta caracter '}'
    j = 0;

    char sir_creat1[256] = ""; // Pentru a construi cheile sau valorile

    for (i = 0; i < strlen(s); i++) {
        // Verificăm dacă suntem în interiorul unei secțiuni JSON
        if (flag == 1 && s[i] != '}' && i < copyV2[j] && copyV1[j] == -1 && copyV2[j] != -1) {
            if (s[i] != ':') 
            {
                sir_creat1[l] = s[i];
                l++;
            } 
            else 
            {
                // La întâlnirea caracterului ':', salvăm cheia
                sir_creat1[l] = s[i];
                l++;
                sir_creat1[strlen(sir_creat1)] = '\0'; // Terminăm sirul
                l++;

                strcpy(vector_chey[k], sir_creat1); // Salvăm cheia

                while(l > -1)
                {
                    stergeCaracterPePozitie(sir_creat1, l);
                    l--;
                }
                //pentru a ajunge cu l la 0
                l++;
                
                k++;
                flag = 0; // Resetăm flag-ul
            }
        }

        // Dacă întâlnim '{', setăm flag-ul
        if (s[i] == '{' && flag == 0) {
            flag++;
            copyV1[j] = -1; // Pornim procesul
        }
    }

    int size_of_vector_chey = k;

    // Copierea vectorilor v1 și v2 în copyV1 și copyV2
    //n has stored the number of indexes in v1 and v2
    for (int m = 0; m < n; m++) {
        copyV1[m] = v1[m];
    }

    for (int m = 0; m < n; m++) {
        copyV2[n] = v2[n];
    }

    // falag reprezinta ca suntem pe caracterul '{' cel mai din stanga
    flag = 0;

    // reprezinta ca suntem  la prima perece {} inside { {} } initial dupa se mareste la fiecare pereche {}
    int index_v1 = 0;

    //reprezinta ca am actualizat start_index
    flag2 = 0;

    //reset k and l for iteration
    k=0;
    l=0;

    // j = 0 reprezinta indexul din v1 in care stim pozitia primul caracter '{' si folosim si faptul ca v2[j] stocheaza cel mai din dreapta caracter '}'
    j = 0;

    // t = j+1 pentru a reprezenta pozitia de v1[t], v2[t] si mergem pana la streln(v1) adica mergem prin toate perechile dinautru {{},{}}
    int t = 0;

    int start_index = 0;
    int end_index = 0;
    for (i = 0; i < strlen(s); i++) {
        // Verificăm dacă suntem în interiorul unei secțiuni JSON
        if (flag == 1 && i < copyV2[j] && copyV1[j] == -1 && copyV2[j] != -1) 
        {
            if(s[i] == ':' && flag2 == 0)
            {
                i++;
                if(s[i] == '{' && index_v1 < n && flag2==0)
                {
                    start_index = v1[index_v1];
                    end_index = v2[index_v1];
                    flag2++;
                }
                if(i >= start_index && i <= end_index && flag2 > 0)
                {
                    sir_creat1[l] = s[i];
                    l++;
                }
            }
            else
            {
                if(s[i] != '}' && i >= start_index && i <= end_index && flag2 > 0)
                {
                    sir_creat1[l] = s[i];
                    l++;
                }
                if(s[i] == '}' && i == end_index && flag2 > 0)
                {
                    sir_creat1[l] = s[i];
                    l++;
                    sir_creat1[strlen(sir_creat1)] = '\0'; // Terminăm sirul
                    l++;

                    strcpy(vector_words[k], sir_creat1); // Salvăm cuventul {}

                    while(l > -1)
                    {
                        stergeCaracterPePozitie(sir_creat1, l);
                        l--;
                    }
                    //pentru a ajunge cu l la 0
                    l++;
                    k++;
                    flag2--;
                    index_v1++;
                }
            }
        }

        // Dacă întâlnim '{', setăm flag-ul
        if (s[i] == '{' && flag == 0) {
            flag++;
            copyV1[j] = -1; // Pornim procesul
            index_v1 = j+1;
        }
    }

    int size_of_vector_words = k;

    // Afisam vectorul chei si words
    for (int m = 0; m < size_of_vector_chey; m++) {
        cout << vector_chey[m];
        if (m <= size_of_vector_words)
            cout << " " << vector_words[m];
        cout << endl;
    }
    return 0;
}

/*
void eliminare(char *s, int poz)
{
    char t[256];
    strcpy(t, s + poz + 1);
    strcpy(s + poz, t);
}
*/

/*
char* eliminareGhilimeleKeys(char *s)
{
    int flag = 0;
    int i = 0, j = 0;

    char *rezultat = new char[strlen(s) + 1];
    rezultat[0] = '\0';

    while(s[i] != '\0')
    {
        if(s[i] != '{' && flag == 0)
        {
            rezultat[j++] = s[i];
        }
        if(s[i] != '"' && flag ==1)
        {
            rezultat[j++] = s[i];
        }
        if (s[i] == '{')
        {
            rezultat[j++] = s[i];
            flag++;
        }
        if (s[i] == ':')
        {
            flag--;
        }
        i++;
    }

    rezultat[j] = '\0';
    return rezultat;
}
*/


//eliminate " 
    //new_s = eliminareGhilimeleKeys(s);

    //strcpy(s, new_s);

    //cout << s << endl;

    //create matrix with "key" : {}

    //calculate max depth
    //n = calculateMaxDepth(s);
    //if(n < 0){
    //    cout << "Incorrect";
    //}
    //else{
    //    cout << "maxDepth:" << n << endl;
    //}

    //count the number of character {, the count reprezents the number of rows of the matrix used for declaration

    //int nrRows = countDecimalNintyOne(s);

    //cout << "Total number of { :" << nrRows << endl;

    //char matrix[nrRows+1][256];



//Se dă un șir de paranteze rotunde care se închid corect (corect parantezat). Să se determine adâncimea parantezării.
//int calculateMaxDepth(char *p)
//{
//    int ok = 1;
//    int height = 0;
//    int height_max = 0;
//    for(int i = 0 ; s[i] && ok ; i ++)
//    {
//        if(s[i] == '{')
//        {
//            height ++;
//            if(height > height_max)
//                height_max = height;
//        }
//        if(s[i] == '}')
//            if(height > 0)
//                height --;
//            else
//                ok = 0;
//    }
//    if(height > 0)
//           ok = 0;
//    if(!ok)
//        return -1; // -1 is for inccorect
//    else
//        return height_max;
//}
