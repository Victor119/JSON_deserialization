#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

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

void insertCharAtPosition(char* p, int i, char ch) {
    char t[256]; 
    strcpy(t, p + i);
    strcpy(p + i + 1, t);
    p[i] = ch;
}

//put charcters '{ }' on left and right of the word {word} 
//use the fact that every key can have only one object with a number/string
char* modifyJSON(char *p) {
    int ok = 0, ok2 = 0, ok3=0, flag3 = 0;
    for (int i = 0; i < strlen(p); i++) {
        if (p[i] == '"') {
            flag3++;
            if(p[i-1] == '\\')
            {
                flag3--;
            }
        }

        if (ok == 1 && ok2 == 0 && ok3==0) {
            if (p[i] == '"' && flag3%2 == 0) {
                insertCharAtPosition(p, i + 1, '}');
                ok = 0;
            }
        }

        if (ok2 == 1 && ok == 0 && ok3==0) {
            if (p[i] >= '0' && p[i] <= '9' && (p[i + 1] < '0' || p[i + 1] > '9')) {
                insertCharAtPosition(p, i + 1, '}');
                ok2 = 0;
            }
        }

        if (ok3 == 1 && ok == 0 && ok2==0) {
            if (p[i] == 'l' && p[i + 1] != 'l') {
                insertCharAtPosition(p, i + 1, '}');
                ok3 = 0;
            }
        }

        if (p[i] == ':' && ok == 0 && ok2 == 0 && flag3 % 2 == 0) {
            if (p[i + 1] == '"') {
                ok++;
                insertCharAtPosition(p, i + 1, '{');
                i++; //suntem pe caracter '{'
                i++; //suntem pe caracter '"'
                if(p[i] == '"'){
                    flag3++;
                }
            } 
            if (p[i + 1] >= '0' && p[i + 1] <= '9') {
                ok2++;
                insertCharAtPosition(p, i + 1, '{'); 
                i++;
            }
            if(p[i+1] == 'n' && p[i+2] == 'u' && p[i+3] == 'l' && p[i+4] == 'l'){
                ok3++;
                insertCharAtPosition(p, i + 1, '{'); 
                i++;
            }
        }
    }
    return p;
}



//Se dă un șir de paranteze rotunde care se închid corect (corect parantezat). Să se determine adâncimea parantezării.
int calculateMaxDepth(char *p)
{
    int ok = 1;
    int height = 0;
    int height_max = 0;
    int flag3 = 0;
    for(int i = 0 ; p[i] && ok ; i ++)
    {
        if(p[i] == '"')
        {
            flag3++;
            if(p[i-1] == '\\')
            {
                flag3--;
            }
        }
        if(p[i] == '{' && flag3%2==0)
        {
            height ++;
            if(height > height_max)
                height_max = height;
        }
        if(p[i] == '}' && flag3%2==0)
            if(height > 0)
                height --;
            else
                ok = 0;
    }
    if(height > 0)
        ok = 0;
    if(!ok)
        return -1; // -1 is for inccorect
    else
        return height_max;
}

int calculateMaxDepth2(char *p)
{
    int ok = 1;
    int height = 0;
    int height_max = 0;
    int flag3 = 0;
    for(int i = 0 ; p[i] && ok ; i ++)
    {
        if(p[i] == '"')
        {
            flag3++;
            if(p[i-1] == '\\')
            {
                flag3--;
            }
        }
        if(p[i] == '[' && flag3%2==0)
        {
            height ++;
            if(height > height_max)
                height_max = height;
        }
        if(p[i] == ']' && flag3%2==0)
            if(height > 0)
                height --;
            else
                ok = 0;
    }
    if(height > 0)
        ok = 0;
    if(!ok)
        return -1; // -1 is for inccorect
    else
        return height_max;
}

void stergeCaracterPePozitie(char* sir, int pozitie) {
    // Mutăm caracterele spre stânga
    for (int i = pozitie; i < strlen(sir); i++) {
        sir[i] = sir[i + 1];
    }

    // Terminăm șirul cu '\0'
    sir[strlen(sir) - 1] = '\0';
}

char* oglindit(char* s) {
    int len = strlen(s);
    char* rezultat = new char[len + 1];  //string saving the reverse string
    
    for (int i = 0; i < len; i++) {
        rezultat[i] = s[len - 1 - i];
    }
    
    rezultat[len] = '\0';  // Terminăm șirul oglindit cu '\0'
    return rezultat;
}

char* removeSubstring(char* s,char* t)
{
    char copy1_s[256] = "", copy2_s[256] = "", copy3_s[256] = "";
    int i = 0, j=0;
    
    char* result2 = new char[strlen(s) + 1];
    
    char* intermediate_new_s = nullptr;

    strcpy(copy1_s, s);
    
    char* new_s = strstr(copy1_s, t);
    
    if(new_s != nullptr)
    {
        *(new_s + strlen(t)) = '\0';
        
        // Calculăm lungimea părții pe care vrem să o copiem
        int length_to_copy = new_s - copy1_s + strlen(t);

        // Creăm un nou șir pentru a păstra rezultatul
        char* result = new char[length_to_copy + 1]; // +1 pentru '\0'
            
        // Copiem în noul șir
        strncpy(result, copy1_s, length_to_copy);
        result[length_to_copy] = '\0'; // Asigurăm terminarea șirului

        new_s = result;
        
        intermediate_new_s = new_s = result;
    }
    
    //cout << new_s << endl;
    //cout << strlen(new_s) << endl;
    
    for(i=strlen(new_s); i<strlen(s); i++)
    {
        copy2_s[j] = s[i];
        j++;
    }
    
    copy2_s[j] = '\0';
    
    for(i=0; i<strlen(new_s); i++)
    {
        strcpy(copy3_s, new_s + i);
        if(strcmp(copy3_s, t)==0)
        {
            strncpy(new_s + i, new_s + i + strlen(t), strlen(new_s) - i - strlen(t) + 1);
            break;
        }
    }
    
    int new_length = strlen(new_s) + strlen(copy2_s) + 1; // +1 pentru '\0'
    char* adjusted_new_s = new char[new_length];

    // Copiem new_s în adjusted_new_s
    strcpy(adjusted_new_s, new_s);

    // Concatenăm copy2_s la adjusted_new_s
    strcat(adjusted_new_s, copy2_s);

    // Mutăm conținutul lui adjusted_new_s în result2
    strcpy(result2, adjusted_new_s);
    
    delete[] intermediate_new_s;
    delete[] adjusted_new_s;
    
    return result2;
}


int v1[256], v2 [256], v3[256], v4[256], copyV1[256], copyV2[256];
char s[256], copy1_s[256], copy2_s[256];
char vector_chey[256][256], vector_chey2[256][256], vector_chey3[256][256];// Vector pentru a stoca cheile
char vector_words[256][256], vector_words2[256][256], vector_words3[256][256];

int main()
{
    int n, i, j=0, j2=0, j3=0, j4=0, k=0, l=0, k2=0, l2=0, k3=0, l3=0;

    // flag3%2==1 means we are inside a string
    int flag3 = 0;

    int flag4 = 0;
    int flag5 = 0;

    cin.getline(s, 256);

    //eliminate spaces
    char *new_s = eliminareSpatii(s);

    

    strcpy(s, new_s);
    delete[] new_s;
    cout << s << endl;

    //modify JSON
    new_s = modifyJSON(s);

    strcpy(s, new_s);
    delete[] new_s;
    cout << s << endl;

    //avem 4 vectori
    //v1 - in care indexul din vector adica i reprezinta numarul de ordine pentru caracterul '{' iar valoarea efectiva v1[i] reprezinta indexul din sir
    //v2 - in care indexul din vector adica i reprezinta numarul de ordine pentru caracterul '}' iar valoarea efectiva v2[i] reprezinta indexul din sir
    //v3 - in care indexul din vector adica i reprezinta numarul de ordine pentru caracterul '[' iar valoarea efectiva v3[i] reprezinta indexul din sir
    //v4 - in care indexul din vector adica i reprezinta numarul de ordine pentru caracterul ']' iar valoarea efectiva v4[i] reprezinta indexul din sir

    strcpy(copy1_s, s);

    int maxDepth = calculateMaxDepth(s);

    int flag = 0;

    flag3 = 0;

    while(calculateMaxDepth(copy1_s) != 0)
    {
        int counterAscii123 = 0;
        //check for {
        flag = 0;
        for(int i = 0; i < strlen(copy1_s) && flag < 2; i++)
        {
            if(copy1_s[i] == '"')
            {
                flag3++;
                if(copy1_s[i-1] == '\\')
                {
                    flag3--;
                }
            }
            if(flag == 1 && flag3%2==0){
                if(copy1_s[i] == '}')
                {
                    v2[l] = i;
                    l++;
                    copy1_s[i] = ']';
                    flag++;
                }
            }
            if(flag == 0 && flag3%2==0){
                if(copy1_s[i] == '{')
                {
                    counterAscii123++;
                }
                if(copy1_s[i] == '}')
                {
                    counterAscii123--;
                }
                if(counterAscii123 == maxDepth)
                {
                    v1[k] = i;
                    k++;
                    copy1_s[i] = '[';
                    flag++;
                }
            }
        }
        // calculate the new max Depth
        maxDepth = calculateMaxDepth(copy1_s);
    }

    strcpy(copy1_s, s);
    maxDepth = calculateMaxDepth2(s);

    flag = 0;

    flag3 = 0;

    while(calculateMaxDepth2(copy1_s) != 0)
    {
        int counterAscii123 = 0;
        //check for {
        flag = 0;

        for(int i = 0; i < strlen(copy1_s) && flag < 2; i++)
        {
            if(copy1_s[i] == '"')
            {
                flag3++;
                if(copy1_s[i-1] == '\\')
                {
                    flag3--;
                }
            }
            if(flag == 1 && flag3%2==0){
                if(copy1_s[i] == ']')
                {
                    v4[l2] = i;
                    l2++;
                    copy1_s[i] = '}';
                    flag++;
                }
            }
            if(flag == 0 && flag3%2==0){
                if(copy1_s[i] == '[')
                {
                    counterAscii123++;
                }
                if(copy1_s[i] == ']')
                {
                    counterAscii123--;
                }
                if(counterAscii123 == maxDepth)
                {
                    v3[k2] = i;
                    k2++;
                    copy1_s[i] = '{';
                    flag++;
                }
            }
        }

        // calculate the new max Depth
        maxDepth = calculateMaxDepth2(copy1_s);
    }

    flag = 0;

    int v5[k+k2] = {0};
    int v6[l+l2] = {0};

    flag3 = 0;

    for(i=0; i<strlen(s); i++)
    {
        if(s[i] == '"')
        {
            flag3++;
            if(s[i-1] == '\\')
            {
                flag3--;
            }
        }

        if(s[i] == '{' && flag3%2==0)
        {
            flag = 0;
            for(j=0; j<k && flag==0; j++)
            {
                if(i == v1[j])
                {
                    v5[k3] = v1[j];
                    v6[k3] = v2[j];
                    k3++;
                    flag++;
                }
            }
        }
        if(s[i] == '[' && flag3%2==0)
        {
            flag = 0;
            for(j=0; j<k2 && flag==0; j++)
            {
                if( i == v3[j])
                {
                    v5[k3] = v3[j];
                    v6[k3] = v4[j];
                    k3++;
                    flag++;
                }
            }
        }
    }

    // Copierea vectorilor v1 și v2 în copyV1 și copyV2
    for (int m = 0; m < k3; m++) {
        copyV1[m] = v5[m];
    }

    for (int n = 0; n < k3; n++) {
        copyV2[n] = v6[n];

        //cout << v5[n] << " " << v6[n] << endl;
    }

    n=k3;

    // falag reprezinta ca suntem pe caracterul '{' cel mai din stanga
    flag = 0;

    // utilizat ca atunci cand dam peste : sa parcurgem backwards de la prima " la a doua "
    int flag2 = 0;

    flag3 = 0;

    //reset k and l for iteration
    k=0;

    //index for sir_creat1
    l=0;

    //index for sir_creat2
    int t = 0;

    //index pentru a oglindi sir_creat2 si pune in sir_creat1
    int t2 = 0;

    char sir_creat1[256] = ""; // Pentru a construi cheile

    char sir_creat2[256] = ""; // Pentru a constui cheile

    for (i = 0; i < strlen(s); i++) {
        if(s[i] == '"')
        {
            flag3++;
            if(s[i-1] == '\\')
            {
                flag3--;
            }
        }
        //extract key
        if(flag == 1 && flag2 < 2)
        {
            while(flag2 < 2)
            {
                if(flag2 > 0)
                {
                    if(s[i-1-t] != '"')
                    {
                        sir_creat2[t] = s[i - 1 - t];
                        t++;
                    }
                    if(s[i - 1 - t] == '"')
                    {
                        sir_creat2[t] = s[i - 1 - t];
                        t++;
                        flag2++;
                        flag3++;
                        if(s[i-1-t] == '\\')
                        {
                            flag2--;
                            flag3--;
                        }
                    }
                }
                if(s[i - 1] == ':' && flag2 == 0)
                {
                    sir_creat2[t] = s[i - 1 - t];
                    t++;
                    
                    if(s[i - 1 - t] == '"')
                    {
                        sir_creat2[t] = s[i - 1 - t];
                        t++;
                        flag2++;
                        flag3++;
                    }
                }
                
            }

            //cout << sir_creat2 << endl;

            //oglindim sir_creat2 in sir_creat1
            for(t2 = strlen(sir_creat2) - 1; t2 >=0; t2--)
            {
                    sir_creat1[l] = sir_creat2[t2];
                    l++;
            }

            //golim sir_creat2
            while(t > -1)
            {
                stergeCaracterPePozitie(sir_creat2, t);
                t--;
            }
            //pentru a ajunge cu t la 0
            t++;

            //Save key
            strcpy(vector_chey[k], sir_creat1);

            //pregatim indexul urmatoarei key
            k++;

            //golim sir_creat1
            while(l > -1)
            {
                stergeCaracterPePozitie(sir_creat1, l);
                l--;
            }
            //pentru a ajunge cu l la 0
            l++;

            //reset flags
            flag2= 0;
            flag= 0;
        }
        
        //if flag3%2==1 means we are inside a string
        if(s[i] == ':' && flag3%2 == 0 && flag==0)
        {
            flag++;
        }
    }

    int size_of_vector_chey = k;

    /*
    for(int m=0; m < size_of_vector_chey; m++)
        cout << vector_chey[m] << endl;
    */

    // flag reprezinta ca suntem pe caracterul '{' cel mai din stanga
    flag = 0;

    //reprezinta ca am actualizat start_index
    flag2 = 0;

    // if flag3%2==1 means we are inside a string
    flag3 = 0;

    // reprezinta ca suntem  la prima perece {} sau [] inside { {} } initial dupa se mareste la fiecare pereche {} sau []
    int index_v1 = 0;    

    //reset k and l for iteration
    k=0;
    l=0;

    // j = 0 reprezinta indexul din v1 in care stim pozitia primul caracter '{' sau '[' si folosim si faptul ca v2[j] stocheaza cel mai din dreapta caracter '}' sau ']'
    j = 0;

    int start_index = 0;
    int end_index = 0;

    //spargem o expresie care incepe cu caracter '{' si se termina cu caracter '}' ex: {{},[],{}}
    //index_v1 contorizam perechile din interiorul {} sau [] peste care dam atunci cand facem extractia {} sau []
    for (i = 0; i < strlen(s); i++) {
        if(s[i] == '"')
        {
            flag3++;
            if(s[i-1] == '\\')
            {
                flag3--;
            }
        }

        // Verificăm dacă suntem în interiorul unei secțiuni JSON
        if (flag == 1 && i < copyV2[j]) 
        {
            if(flag2 == 1)
            {
                if(i >= start_index && i < end_index && flag2 > 0)
                {
                    sir_creat1[l] = s[i];
                    l++;

                    if((s[i] == '{' || s[i] == '[') && flag3%2==0 )
                    {
                        index_v1++;
                    }
                }
                //cout << start_index << " " << end_index << endl;

                if(i == end_index && flag2 > 0)
                {
                    sir_creat1[l] = s[i];
                    l++;
                    sir_creat1[l] = '\0'; // Terminăm sirul
                    //l++;

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
                }
            }
            if(s[i] == ':' && flag2 == 0 && flag3%2==0)
            {
                i++;
                if((s[i] == '{' || s[i] == '[') && index_v1 < n && flag2==0)
                {
                    start_index = v5[index_v1];
                    end_index = v6[index_v1];

                    //cout << start_index << " " << end_index << endl; 
                    flag2++;
                    index_v1++;
                }
                if(i >= start_index && i <= end_index && flag2 > 0)
                {
                    sir_creat1[l] = s[i];
                    l++;
                }
            }
        }

        // Dacă întâlnim '{', setăm flag-ul
        if (s[i] == '{' && flag == 0) {
            flag++;
            copyV1[j] = -1; // Pornim procesul
            index_v1++;
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


    int size_of_vector_chey2 = 0;
    int size_of_vector_words2 = 0;

    flag3 = 0;
    l2 = 0;
    l3 = 0;
    i = 0;
    strcpy(copy1_s, s);
    //while(size_of_vector_words != 0)
    while(size_of_vector_words > 0)
    {
        strcpy(copy2_s, copy1_s);
        l=0;
        strcpy(sir_creat1, "");

        t=0;
        strcpy(sir_creat2, "");

        new_s = strstr(copy2_s, vector_words[i]);

        if(new_s != nullptr)
        {
            *(new_s + strlen(vector_words[i])) = '\0'; //trunchiem dupa aparitia sirului

            // Calculăm lungimea părții pe care vrem să o copiem
            int length_to_copy = new_s - copy2_s + strlen(vector_words[i]);

            // Creăm un nou șir pentru a păstra rezultatul
            char* result = new char[length_to_copy + 1]; // +1 pentru '\0'
            
            // Copiem în noul șir
            strncpy(result, copy2_s, length_to_copy);
            result[length_to_copy] = '\0'; // Asigurăm terminarea șirului

            new_s = result;
        }

        flag = 0;
        flag2 = 0;

        //starts with value 1 beacause we don`t count the first appeareance of { or [
        flag4 = 1;
        flag5 = 1;

        // if flag3%2==1 means we are inside a string
        flag3 = 0;

        

        for(j=strlen(new_s)-1; j>=0 && (flag4>0 && flag5>0); j--)
        {
            if(flag == 1 && flag2 == 0)
            {
                if(new_s[j] == '}')
                {
                    flag4++;
                }
                if(new_s[j] == '{')
                {
                    flag4--;
                }
            }
            if(flag == 0 && flag2 == 1)
            {
                if(new_s[j] == ']')
                {
                    flag5++;
                }
                if(new_s[j] == '[')
                {
                    flag5--;
                }
            }
            if(new_s[j] == '}' && flag == 0 && flag2 ==0)
            {
                flag++;
            }

            if(new_s[j] == ']' && flag2 == 0 && flag ==0)
            {
                flag2++;
            }
        }

        flag = 0;


        //now the caracter in new_s[j] is :
        while(j>=0 && flag < 2)
        {
            
            if(new_s[j] == '"')
            {
                flag++;
                if(new_s[j-1] == '\\' )
                {
                    flag--;
                }
            }
            sir_creat2[t] = new_s[j];
            t++;
            j--;
        }

        sir_creat2[t] = '\0';

        //oglindim sir_creat2 in sir_creat1
        for(t2 = strlen(sir_creat2) - 1; t2 >=0; t2--)
        {   
                sir_creat1[l] = sir_creat2[t2];
                l++;
        }

        //golim sir_creat2
        while(t > -1)
        {
            stergeCaracterPePozitie(sir_creat2, t);
            t--;
        }
        //pentru a ajunge cu t la 0
        t++;

        new_s = strstr(copy2_s, vector_words[i]);

        //cout << new_s << endl;

        strcpy(vector_chey2[l2], sir_creat1);
        l2++;
        size_of_vector_chey2++;


        //golim sir_creat1
        while(l > -1)
        {
            stergeCaracterPePozitie(sir_creat1, l);
            l--;
        }
        //pentru a ajunge cu l la 0
        l++;

        strcpy(vector_words2[l3], new_s);
        l3++;
        size_of_vector_words2++;

        //cout << vector_chey2[0] << " " << vector_words2[0] << endl;

        char* result2 = new char[strlen(vector_chey2[l2-1])+ strlen(vector_words2[l3-1]) + 1]; 

        strcpy(result2, "");

        flag5=0;
        //eliminate first appeareance of vector_words2[l2-1] from vector_words
        for(j3=0; j3<size_of_vector_words && flag5==0; j3++)
        {
            if(strcmp(vector_words[j3],vector_words2[l2-1])==0)
            {
                for(j4=j3; j4<size_of_vector_words; j4++)
                    strcpy(vector_words[j4], vector_words[j4+1]);
                size_of_vector_words--;
                flag5++;
            }
        }
        

        strcat(result2, vector_chey2[l2-1]);
        strcat(result2, vector_words2[l3-1]);

        char* modifiedString = removeSubstring(copy1_s, result2);
        strcpy(copy1_s, modifiedString);
        delete[] modifiedString;


        //copy1_s now has the old cop1_s with result2 removed
        cout << copy1_s << endl;

    }

    t=0;

    // Afisam vector_chei2 si vector_words2
    for (int m = 0; m < size_of_vector_chey; m++) {
        if(strcmp(vector_chey[m], vector_chey2[t]) == 0){
            strcpy(vector_chey3[m],vector_chey2[t]);
            strcpy(vector_words3[m], vector_words2[t]);
            t++;
        }
        else{
            strcpy(vector_chey3[m],vector_chey[m]);
        }
    }

    //for(int m = 0; m < size_of_vector_chey; m++)
    //{
    //    cout << vector_chey3[m] << " "  << vector_words3[m] << endl;  
    //}

    int size_of_vector_chey3 = size_of_vector_chey;
    int size_of_vector_words3 = size_of_vector_chey;

    i=0, j=0, j2=0, j3=0, j4=0, k=0, k2=0, k3=0, l=0, l2=0, l3=0, t=0, t2=0;
    flag=0, flag2=0, flag3=0;

    for(i=0; i<size_of_vector_chey3; i++)
    {
        if(strlen(vector_words3[i]) == 0)
        {
            flag=0;
            for(j=i-1; j>=0 && flag==0; j--)
            {
                //if(vector_chey3[i] is in vector_words3[j])
                if(strstr(vector_words3[j],vector_chey3[i]) != nullptr)
                {
                    //extract the string starting with the vector_chey3[i] from vector_words3[j]
                    char *new_s = strstr(vector_words3[j],vector_chey3[i]);

                    //increment this vlag when encounter the first character { or [
                    flag2=0;

                    flag3=0;

                    //we assune that we have already encountered the character { or [
                    flag4=1;

                    //aici sir_creat1 este gol
                    //start with j2 with the position after the first character that is either { or [
                    for(j2=0; j2<strlen(new_s) && flag4>0; j2++)
                    {
                        if(new_s[j2] == '"')
                        {
                            flag3++;
                            if(new_s[j2-1] == '\\')
                            {
                                flag3--;
                            }
                        }
                        if(new_s[j2] == '{' && flag2==1 && flag3%2==0)
                        {
                            flag4++;
                        }
                        if(new_s[j2] == '[' && flag2==1 && flag3%2==0)
                        {
                            flag4++;
                        }
                        if(new_s[j2] == '{' && flag2==0 && flag4==1 && flag3%2==0)
                        {
                            flag2++;
                        }
                        if(new_s[j2] == '[' && flag2==0 && flag4==1 && flag3%2==0)
                        {
                            flag2++;
                        }
                        if(new_s[j2] == '}' && flag3%2==0)
                        {
                            flag4--;
                        }
                        if(new_s[j2] == ']' && flag3%2==0)
                        {
                            flag4--;
                        }
                        if(flag2 == 1)
                        {
                            sir_creat1[l] = new_s[j2];
                            l++;
                        }
                    }
                    if(flag4==0)
                    {
                        sir_creat1[l] = '\0';
                        strcpy(vector_words3[i], sir_creat1);

                        //golim sir_creat1
                        while(l > -1)
                        {
                            stergeCaracterPePozitie(sir_creat1, l);
                            l--;
                        }
                        //pentru a ajunge cu l la 0
                        l++;

                        flag++;
                    }
                }
            }
        }
    }

    for(int m = 0; m < size_of_vector_chey; m++)
    {
        cout << vector_chey3[m] << " "  << vector_words3[m] << endl;  
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




