#include <iostream>
#include <fstream>
#include <cstring>
#include <stack>

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
    int ok = 0, ok2 = 0, ok3=0, ok4=0, ok5=0, flag3 = 0;
    for (int i = 0; i < strlen(p); i++) {
        if (p[i] == '"') {
            flag3++;
            if(p[i-1] == '\\')
            {
                flag3--;
            }
        }

        if (ok == 1 && ok2 == 0 && ok3==0 && ok4==0 && ok5==0) {
            if (p[i] == '"' && flag3%2 == 0) {
                insertCharAtPosition(p, i + 1, '}');
                ok = 0;
            }
        }

        if (ok2 == 1 && ok == 0 && ok3==0 && ok4==0 && ok5==0) {
            if (p[i] >= '0' && p[i] <= '9' && (p[i + 1]=='{' || p[i+1]=='}' || p[i+1]=='[' || p[i+1]==']' || p[i+1]==',')) {
                insertCharAtPosition(p, i + 1, '}');
                ok2 = 0;
            }
        }

        if (ok3 == 1 && ok == 0 && ok2==0 && ok4==0 && ok5==0) {
            if (p[i] == 'l' && (p[i + 1]=='{' || p[i+1]=='}' || p[i+1]=='[' || p[i+1]==']' || p[i+1]==',')) {
                insertCharAtPosition(p, i + 1, '}');
                ok3 = 0;
            }
        }

        if (ok4 == 1 && ok == 0 && ok2==0 && ok3==0 && ok5==0) {
            if (p[i] == 'e' && (p[i + 1]=='{' || p[i+1]=='}' || p[i+1]=='[' || p[i+1]==']' || p[i+1]==',')) {
                insertCharAtPosition(p, i + 1, '}');
                ok4 = 0;
            }
        }

        if (ok5 == 1 && ok == 0 && ok2==0 && ok3==0 && ok4==0) {
            if (p[i] == 'e' && (p[i + 1]=='{' || p[i+1]=='}' || p[i+1]=='[' || p[i+1]==']' || p[i+1]==',')) {
                insertCharAtPosition(p, i + 1, '}');
                ok5 = 0;
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
            if(p[i+1] == '-' && p[i + 2] >= '0' && p[i + 2] <= '9'){
                ok2++;
                insertCharAtPosition(p, i + 1, '{'); 
                i++;
            }
            if ((p[i + 1] >= '0' && p[i + 1] <= '9')) {
                ok2++;
                insertCharAtPosition(p, i + 1, '{'); 
                i++;
            }
            if(p[i+1] == 'n' && p[i+2] == 'u' && p[i+3] == 'l' && p[i+4] == 'l'){
                ok3++;
                insertCharAtPosition(p, i + 1, '{'); 
                i++;
            }
            if((p[i+1] == 't' && p[i+2] == 'r' && p[i+3] == 'u' && p[i+4] == 'e') ){
                ok4++;
                insertCharAtPosition(p, i + 1, '{'); 
                i++;
            }
            if(p[i+1] == 'f' && p[i+2] == 'a' && p[i+3] == 'l' && p[i+4] == 's' && p[i+5] == 'e'){
                ok5++;
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

bool isValidJson(const std::string& json) {
    std::stack<char> brackets;  // Stivă pentru acolade și paranteze
    bool inString = false;      // Flag pentru a fi într-un string
    bool expectValue = true;    // Așteptăm o valoare inițial
    
    size_t i = 0;
    while (i < json.size()) {
        char c = json[i];

        // Ignorăm spațiile
        if (c == ' ' || c == '\n' || c == '\t') {
            i++;
            continue;
        }

        // Dacă suntem într-un string
        if (inString) {
            if (c == '\\') {
                i++; // Sărim peste caracterul următor dacă e escapare
            } else if (c == '"') {
                inString = false; // Ieșim din string
            }
            i++;
            continue;
        }

        switch (c) {
            case '{':
                if (!expectValue) return false; // Structură nepermisă
                brackets.push(c);
                expectValue = true; // Așteptăm o cheie într-un obiect
                break;

            case '}':
                if (brackets.empty() || brackets.top() != '{') return false;
                brackets.pop();
                expectValue = false; // Încheiem obiectul
                break;

            case '[':
                if (!expectValue) return false;
                brackets.push(c);
                expectValue = true; // Așteptăm o valoare în array
                break;

            case ']':
                if (brackets.empty() || brackets.top() != '[') return false;
                brackets.pop();
                expectValue = false;
                break;

            case '"':
                inString = true;
                expectValue = false; // String-ul satisface așteptarea de valoare
                break;

            case ':':
                if (expectValue || brackets.empty() || brackets.top() != '{') return false;
                expectValue = true; // După `:` urmează o valoare
                break;

            case ',':
                if (expectValue || brackets.empty()) return false;
                expectValue = true; // După `,` ne așteptăm la o nouă valoare
                break;

            case 't':
                if (json.substr(i, 4) == "true" && expectValue) {
                    i += 3; // Sărim peste "true"
                    expectValue = false;
                } else return false;
                break;

            case 'f':
                if (json.substr(i, 5) == "false" && expectValue) {
                    i += 4; // Sărim peste "false"
                    expectValue = false;
                } else return false;
                break;

            case 'n':
                if (json.substr(i, 4) == "null" && expectValue) {
                    i += 3; // Sărim peste "null"
                    expectValue = false;
                } else return false;
                break;

            default:
                if (isdigit(c) || c == '-') { // Valoare numerică
                    if (!expectValue) return false;
                    while (i < json.size() && (isdigit(json[i]) || json[i] == '.' || json[i] == 'e' || json[i] == 'E' || json[i] == '+' || json[i] == '-')) i++;
                    i--; // Ajustăm indexul pentru a procesa corect
                    expectValue = false;
                } else {
                    return false; // Caracter invalid
                }
                break;
        }
        i++;
    }

    return brackets.empty() && !inString && !expectValue; // Structură JSON corect închisă
}


//daca exemplul este prea mare atunci nu va functiona


int main()
{
    int n=0, j=0, j2=0, j3=0, j4=0, k=0, l=0, k2=0, l2=0, k3=0, l3=0;

    // flag3%2==1 means we are inside a string
    int flag3 = 0;

    int flag4 = 0;
    int flag5 = 0;

    //cin.getline(s, 256);

    int i=0;
    int size_of_s=0;
    char ch;

    ifstream inputFile("input.txt");
    if (!inputFile.is_open()) {
        cerr << "Eroare la deschiderea fișierului!" << std::endl;
        return 1;
    }
    
    while (inputFile.get(ch)) {
        size_of_s++;
    }

    // Resetează poziția la începutul fișierului
    inputFile.clear();
    inputFile.seekg(0, ios::beg);

    char* s = new char[size_of_s + 1];

    while (inputFile.get(ch)) {
        s[i] = ch;
        i++;
    }

    s[i] = '\0';

    inputFile.close();

    n = size_of_s+1;

    int v1[n] = {0}, v2[n] = {0}, v3[n] = {0}, v4[n] = {0};
    int copyV1[n] = {0}, copyV2[n] = {0};

    char copy1_s[n], copy2_s[n];

    char vector_chey[n][n], vector_chey2[n][n], vector_chey3[n][n];
    char vector_words[n][n], vector_words2[n][n], vector_words3[n][n];

    for (j = 0; j < n; j++) {
        for (k = 0; k < n; k++){
            vector_chey[j][k] = '\0';
            vector_chey2[j][k] = '\0';
            vector_chey3[j][k] = '\0';
            vector_words[j][k] = '\0';
            vector_words2[j][k] = '\0';
            vector_words3[j][k] = '\0';
        }
    }

    j = 0;
    k = 0;
    
    //std::string s = R"([{"_id":"671fb093de4cf33f051b4c23","index":0,"guid":"7efa4069-6b1d-4d41-9dbc-f50cd8161f34","isActive":true,"balance":"$2,099.99","picture":"http://placehold.it/32x32","age":31,"eyeColor":"blue","name":"Diane Sharp","gender":"female","company":"INEAR","email":"dianesharp@inear.com","phone":"+1 (809) 544-3049","address":"406 Morton Street, Leyner, Ohio, 544","about":"Excepteur irure fugiat ea Lorem sunt. Nisi magna minim velit non est duis nisi sint anim. Sint consequat fugiat adipisicing commodo. Ad duis incididunt velit commodo occaecat ad ipsum in magna minim dolore. Cupidatat do in quis in ipsum proident fugiat elit sunt consectetur. Proident occaecat qui mollit adipisicing adipisicing eu sunt esse ad deserunt adipisicing est dolor aliquip. Velit anim eiusmod aliqua elit veniam anim enim laborum minim ipsum laborum ullamco deserunt veniam.\r\n","registered":"2024-09-04T02:38:29 -03:00","latitude":57.111994,"longitude":102.906227,"tags":["sit","et","dolor","mollit","id","velit","nulla"],"friends":[{"id":0,"name":"Madge Farrell"},{"id":1,"name":"Yvonne Anderson"},{"id":2,"name":"Greene Rosario"}],"greeting":"Hello, Diane Sharp! You have 4 unread messages.","favoriteFruit":"apple"},{"_id":"671fb0937fefd364beae7528","index":1,"guid":"21378a53-e395-4f87-beda-825260ef7520","isActive":false,"balance":"$1,722.93","picture":"http://placehold.it/32x32","age":26,"eyeColor":"green","name":"Richards Manning","gender":"male","company":"SCHOOLIO","email":"richardsmanning@schoolio.com","phone":"+1 (999) 527-3911","address":"609 Division Place, Warsaw, Louisiana, 8117","about":"Cupidatat cupidatat aute qui duis mollit qui velit dolore. Excepteur veniam esse labore aute occaecat enim enim nulla culpa est dolor aute quis. Ut quis aute dolor voluptate labore irure qui culpa excepteur id laboris fugiat non. Consequat aliquip qui ullamco est tempor sint laboris dolor elit cillum irure. Ut non irure id exercitation ex labore reprehenderit pariatur consectetur non. Nisi incididunt quis irure aute commodo in ut labore nulla in anim aliqua id. Proident tempor labore exercitation id do nostrud in culpa exercitation nisi qui.\r\n","registered":"2020-02-05T08:23:32 -02:00","latitude":-86.100386,"longitude":-175.653081,"tags":["pariatur","consequat","qui","minim","deserunt","minim","do"],"friends":[{"id":0,"name":"Gutierrez Nichols"},{"id":1,"name":"Boyle Ryan"},{"id":2,"name":"Brigitte Pratt"}],"greeting":"Hello, Richards Manning! You have 9 unread messages.","favoriteFruit":"banana"},{"_id":"671fb093822920f2caa4caf3","index":2,"guid":"6e06c4bc-326d-4e25-8dfe-ccd8a84be10c","isActive":true,"balance":"$2,914.15","picture":"http://placehold.it/32x32","age":38,"eyeColor":"green","name":"Johanna Cain","gender":"female","company":"IMAGEFLOW","email":"johannacain@imageflow.com","phone":"+1 (983) 592-3256","address":"216 Montana Place, Townsend, Hawaii, 8155","about":"Mollit dolor aliqua consequat labore deserunt dolor sint duis culpa. Quis veniam velit consequat et. Dolore aute exercitation nostrud laborum pariatur irure id elit. Excepteur Lorem ex culpa ullamco veniam reprehenderit tempor est consequat velit velit commodo cillum.\r\n","registered":"2024-10-21T03:24:44 -03:00","latitude":-48.75001,"longitude":165.155763,"tags":["officia","deserunt","labore","ex","exercitation","quis","pariatur"],"friends":[{"id":0,"name":"Todd Carpenter"},{"id":1,"name":"Lilia Haley"},{"id":2,"name":"Anne Quinn"}],"greeting":"Hello, Johanna Cain! You have 4 unread messages.","favoriteFruit":"strawberry"},{"_id":"671fb093c6e9c94b53c0a55d","index":3,"guid":"724d6205-04ce-4f9c-9b24-5351306e8d12","isActive":false,"balance":"$3,202.08","picture":"http://placehold.it/32x32","age":28,"eyeColor":"brown","name":"Kristy England","gender":"female","company":"ZOMBOID","email":"kristyengland@zomboid.com","phone":"+1 (888) 448-3117","address":"739 Beekman Place, Woodlands, Maine, 6304","about":"Laboris deserunt adipisicing veniam nostrud duis sint exercitation. Sit duis nostrud commodo culpa anim enim et. Irure voluptate occaecat nostrud nulla consequat consequat. Aliquip duis id cillum aliquip et fugiat minim adipisicing sunt. Eiusmod Lorem sit est ipsum in nostrud Lorem non consequat voluptate dolor irure consectetur. Id labore dolore anim esse culpa incididunt deserunt.\r\n","registered":"2015-07-12T07:36:56 -03:00","latitude":-53.241525,"longitude":131.457158,"tags":["sint","proident","magna","consequat","qui","veniam","amet"],"friends":[{"id":0,"name":"Chang Perez"},{"id":1,"name":"Leblanc Reyes"},{"id":2,"name":"Warren Knapp"}],"greeting":"Hello, Kristy England! You have 9 unread messages.","favoriteFruit":"strawberry"},{"_id":"671fb09320d096eead8e80e4","index":4,"guid":"db1f9e7c-5052-4cc3-b414-61d70855afc2","isActive":false,"balance":"$3,924.30","picture":"http://placehold.it/32x32","age":26,"eyeColor":"brown","name":"Levy Horton","gender":"male","company":"INSECTUS","email":"levyhorton@insectus.com","phone":"+1 (884) 442-2564","address":"188 Lott Place, Bawcomville, Idaho, 5792","about":"Deserunt elit amet irure dolore et eiusmod veniam do minim sunt exercitation officia. Id pariatur dolore ullamco proident excepteur adipisicing ea deserunt minim. Laborum enim est ipsum velit in nostrud sint proident ipsum do. Sint enim et cillum consectetur enim mollit occaecat esse consectetur.\r\n","registered":"2017-02-11T02:04:39 -02:00","latitude":-51.088951,"longitude":-164.34146,"tags":["est","cupidatat","veniam","aliquip","laboris","ea","irure"],"friends":[{"id":0,"name":"Nguyen Patterson"},{"id":1,"name":"Lourdes Malone"},{"id":2,"name":"Sara Lyons"}],"greeting":"Hello, Levy Horton! You have 1 unread messages.","favoriteFruit":"banana"}])";


    if (isValidJson(s)) {
        cout << "JSON-ul este valid." << endl;
    } else {
        cout << "JSON-ul nu este valid." << endl;
    }

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

    n = k3;

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

    
    //for(int m=0; m < size_of_vector_chey; m++)
    //    cout << vector_chey[m] << endl;
    

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




