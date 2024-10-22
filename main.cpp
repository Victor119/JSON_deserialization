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

int v1[256], v2 [256];
char vector_chey[256][256]; // Vector pentru a stoca cheile

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

    // falag reprezinta ca suntem pe caracterul '{' cel mai din stanga
    int flag = 0;

    // reprezinta ca suntem  inside { {} }
    int flag2 = 0;

    //reset k and l for iteration matrix
    k=0;
    l=0;

    // j = 0 reprezinta indexul din v1 in care stim pozitia primul caracter '{' si folosim si faptul ca v2[j] stocheaza cel mai din dreapta caracter '}'
    j = 0;

    char sir_creat1[256] = ""; // Pentru a construi cheile sau valorile

    for (i = 0; i < strlen(s); i++) {
        // Verificăm dacă suntem în interiorul unei secțiuni JSON
        if (flag == 1 && s[i] != '}' && i < v2[j] && v1[j] == -1 && v2[j] != -1) {
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
            v1[j] = -1; // Pornim procesul
        }
    }

    // Afișăm vectorul de chei
    cout << "Chei identificate:" << endl;
    for (int m = 0; m < k; m++) {
        cout << vector_chey[m] << endl;
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
