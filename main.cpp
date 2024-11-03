#include <iostream>
#include <fstream>
#include <cstring>
#include <stack>
#include <sstream>
#include <cstdio>
#include <cstdlib>

using namespace std;

void stergeCaracterPePozitie(char *sir, int pozitie)
{
    // Mutăm caracterele spre stânga
    for (int i = pozitie; i < strlen(sir); i++)
    {
        sir[i] = sir[i + 1];
    }

    // Terminăm șirul cu '\0'
    sir[strlen(sir) - 1] = '\0';
}

void stergeSirPePozitie(char **vector, int pozitie, int &dimensiune)
{
    for (int i = pozitie; i < dimensiune - 1; i++)
    {
        strcpy(vector[i], vector[i + 1]);
    }
    dimensiune--;
}

// eliminate Spaces ' '
char *eliminareSpatii(char *s)
{
    char *p;

    // copy the original string to break down with strtok
    char *c = new char[strlen(s) + 1];
    strcpy(c, s);

    char *rezultat = new char[strlen(s) + 1];
    rezultat[0] = '\0'; // initialize string for concatenation

    p = strtok(c, " ");
    while (p != NULL)
    {
        strcat(rezultat, p);
        p = strtok(NULL, " ");
    }

    delete[] c;
    return rezultat;
}

void insertCharAtPosition(char *p, int i, char ch, int &current_size)
{
    // Verificăm dacă poziția de inserare este validă
    if (i < 0 || i > current_size)
    {
        std::cerr << "Poziție invalidă!" << std::endl;
        return;
    }

    // Mărim dimensiunea bufferului cu 1 pentru a face loc pentru noul caracter
    p[current_size + 1] = '\0'; // Asigurăm terminarea string-ului

    // Mutam caracterele la dreapta
    for (int j = current_size; j >= i; j--)
    {
        p[j + 1] = p[j];
    }

    p[i] = ch;

    current_size++;
}

// put charcters '{ }' on left and right of the word {word}
// use the fact that every key can have only one object with a number/string
void modifyJSON(char *p)
{
    int ok = 0, ok2 = 0, ok3 = 0, ok4 = 0, ok5 = 0, flag3 = 0;
    int current_size = strlen(p);

    for (int i = 0; i < current_size; i++)
    {
        if (p[i] == '"')
        {
            flag3++;
            if (p[i - 1] == '\\')
            {
                flag3--;
            }
        }

        if (ok == 1 && ok2 == 0 && ok3 == 0 && ok4 == 0 && ok5 == 0)
        {
            if (p[i] == '"' && flag3 % 2 == 0)
            {
                insertCharAtPosition(p, i + 1, '}', current_size);
                ok = 0;
            }
        }

        if (ok2 == 1 && ok == 0 && ok3 == 0 && ok4 == 0 && ok5 == 0)
        {
            if (p[i] >= '0' && p[i] <= '9' && (p[i + 1] == '{' || p[i + 1] == '}' || p[i + 1] == '[' || p[i + 1] == ']' || p[i + 1] == ','))
            {
                insertCharAtPosition(p, i + 1, '}', current_size);
                ok2 = 0;
            }
        }

        if (ok3 == 1 && ok == 0 && ok2 == 0 && ok4 == 0 && ok5 == 0)
        {
            if (p[i] == 'l' && (p[i + 1] == '{' || p[i + 1] == '}' || p[i + 1] == '[' || p[i + 1] == ']' || p[i + 1] == ','))
            {
                insertCharAtPosition(p, i + 1, '}', current_size);
                ok3 = 0;
            }
        }

        if (ok4 == 1 && ok == 0 && ok2 == 0 && ok3 == 0 && ok5 == 0)
        {
            if (p[i] == 'e' && (p[i + 1] == '{' || p[i + 1] == '}' || p[i + 1] == '[' || p[i + 1] == ']' || p[i + 1] == ','))
            {
                insertCharAtPosition(p, i + 1, '}', current_size);
                ok4 = 0;
            }
        }

        if (ok5 == 1 && ok == 0 && ok2 == 0 && ok3 == 0 && ok4 == 0)
        {
            if (p[i] == 'e' && (p[i + 1] == '{' || p[i + 1] == '}' || p[i + 1] == '[' || p[i + 1] == ']' || p[i + 1] == ','))
            {
                insertCharAtPosition(p, i + 1, '}', current_size);
                ok5 = 0;
            }
        }

        if (p[i] == ':' && ok == 0 && ok2 == 0 && ok3 == 0 && ok4 == 0 && ok5 == 0 && flag3 % 2 == 0)
        {

            if (p[i + 1] == '-' && p[i + 2] >= '0' && p[i + 2] <= '9')
            {
                ok2++;
                insertCharAtPosition(p, i + 1, '{', current_size);
                i++;
            }
            if ((p[i + 1] >= '0' && p[i + 1] <= '9'))
            {
                ok2++;
                insertCharAtPosition(p, i + 1, '{', current_size);
                i++;
            }
            if (p[i + 1] == 'n' && p[i + 2] == 'u' && p[i + 3] == 'l' && p[i + 4] == 'l')
            {
                ok3++;
                insertCharAtPosition(p, i + 1, '{', current_size);
                i++;
            }
            if ((p[i + 1] == 't' && p[i + 2] == 'r' && p[i + 3] == 'u' && p[i + 4] == 'e'))
            {
                ok4++;
                insertCharAtPosition(p, i + 1, '{', current_size);
                i++;
            }
            if (p[i + 1] == 'f' && p[i + 2] == 'a' && p[i + 3] == 'l' && p[i + 4] == 's' && p[i + 5] == 'e')
            {
                ok5++;
                insertCharAtPosition(p, i + 1, '{', current_size);
                i++;
            }
            if (p[i + 1] == '"')
            {
                ok++;
                insertCharAtPosition(p, i + 1, '{', current_size);
                i++; // suntem pe caracter '{'
                i++; // suntem pe caracter '"'
                if (p[i] == '"')
                {
                    flag3++;
                }
            }
        }
    }
}

// Se dă un șir de paranteze rotunde care se închid corect (corect parantezat). Să se determine adâncimea parantezării.
int calculateMaxDepth(char *p)
{
    int ok = 1;
    int height = 0;
    int height_max = 0;
    int flag3 = 0;
    for (int i = 0; p[i] && ok; i++)
    {
        if (p[i] == '"')
        {
            flag3++;
            if (p[i - 1] == '\\')
            {
                flag3--;
            }
        }
        if (p[i] == '{' && flag3 % 2 == 0)
        {
            height++;
            if (height > height_max)
                height_max = height;
        }
        if (p[i] == '}' && flag3 % 2 == 0)
            if (height > 0)
                height--;
            else
                ok = 0;
    }
    if (height > 0)
        ok = 0;
    if (!ok)
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
    for (int i = 0; p[i] && ok; i++)
    {
        if (p[i] == '"')
        {
            flag3++;
            if (p[i - 1] == '\\')
            {
                flag3--;
            }
        }
        if (p[i] == '[' && flag3 % 2 == 0)
        {
            height++;
            if (height > height_max)
                height_max = height;
        }
        if (p[i] == ']' && flag3 % 2 == 0)
            if (height > 0)
                height--;
            else
                ok = 0;
    }
    if (height > 0)
        ok = 0;
    if (!ok)
        return -1; // -1 is for inccorect
    else
        return height_max;
}

void stergeCaracterPePozitie2(char *sir, int pozitie)
{
    int length = strlen(sir);
    if (pozitie < 0 || pozitie >= length)
        return;

    // Mutam caracterele spre stanga
    for (int i = pozitie; i < length - 1; i++)
    {
        sir[i] = sir[i + 1];
    }

    // Terminam sirul cu '\0'
    sir[strlen(sir) - 1] = '\0';
}

char *oglindit(char *s)
{
    int len = strlen(s);
    char *rezultat = new char[len + 1]; // string saving the reverse string

    for (int i = 0; i < len; i++)
    {
        rezultat[i] = s[len - 1 - i];
    }

    rezultat[len] = '\0'; // Terminăm șirul oglindit cu '\0'
    return rezultat;
}

char *removeSubstring(char *s, char *t)
{
    char *copy1_s = new char[strlen(s) + 1]();
    char *copy2_s = new char[strlen(s) + 1]();
    char *copy3_s = new char[strlen(s) + 1]();

    int i = 0, j = 0;

    char *result2 = new char[strlen(s) + 1];

    char *intermediate_new_s = nullptr;

    strcpy(copy1_s, s);

    char *new_s = strstr(copy1_s, t);

    if (new_s != nullptr)
    {
        *(new_s + strlen(t)) = '\0';

        // Calculăm lungimea părții pe care vrem să o copiem
        int length_to_copy = new_s - copy1_s + strlen(t);

        // Creăm un nou șir pentru a păstra rezultatul
        char *result = new char[length_to_copy + 1]; // +1 pentru '\0'

        // Copiem în noul șir
        strncpy(result, copy1_s, length_to_copy);
        result[length_to_copy] = '\0'; // Asigurăm terminarea șirului

        new_s = result;

        intermediate_new_s = new_s = result;
    }

    // cout << new_s << endl;
    // cout << strlen(new_s) << endl;

    for (i = strlen(new_s); i < strlen(s); i++)
    {
        copy2_s[j] = s[i];
        j++;
    }

    copy2_s[j] = '\0';

    for (i = 0; i < strlen(new_s); i++)
    {
        strcpy(copy3_s, new_s + i);
        if (strcmp(copy3_s, t) == 0)
        {
            strncpy(new_s + i, new_s + i + strlen(t), strlen(new_s) - i - strlen(t) + 1);
            break;
        }
    }

    int new_length = strlen(new_s) + strlen(copy2_s) + 1; // +1 pentru '\0'
    char *adjusted_new_s = new char[new_length];

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

bool isValidJson(const std::string &json)
{
    std::stack<char> brackets; // Stivă pentru acolade și paranteze
    bool inString = false;     // Flag pentru a detecta șirurile de caractere
    bool expectValue = true;   // Indică dacă urmează o valoare
    bool allowComma = false;   // Flag pentru a permite o virgulă după o valoare

    size_t i = 0;
    while (i < json.size())
    {
        char c = json[i];

        // Ignorăm spațiile
        if (c == ' ' || c == '\n' || c == '\t')
        {
            i++;
            continue;
        }

        // Dacă suntem într-un string
        if (inString)
        {
            if (c == '\\')
            {
                i++; // Sărim peste caracterul următor dacă e escapare
            }
            else if (c == '"')
            {
                inString = false;  // Ieșim din string
                allowComma = true; // După string, se permite virgulă
            }
            i++;
            continue;
        }

        switch (c)
        {
        case '{':
            if (!expectValue)
                return false; // Structură invalidă dacă nu așteptăm valoare
            brackets.push(c);
            expectValue = true; // Așteptăm o cheie în obiect
            allowComma = false;
            break;

        case '}':
            if (brackets.empty() || brackets.top() != '{')
                return false; // Acoladă închisă necorespunzător
            brackets.pop();
            expectValue = false; // Închidem un obiect, nu mai așteptăm valoare
            allowComma = true;
            break;

        case '[':
            if (!expectValue)
                return false; // Structură invalidă dacă nu așteptăm valoare
            brackets.push(c);
            expectValue = true; // Așteptăm o valoare în array
            allowComma = false;
            break;

        case ']':
            if (brackets.empty() || brackets.top() != '[')
                return false;
            brackets.pop();
            expectValue = false; // Închidem un array
            allowComma = true;
            break;

        case '"':
            inString = true;     // Intrăm într-un string
            expectValue = false; // String-ul satisface așteptarea de valoare
            break;

        case ':':
            if (expectValue || brackets.empty() || brackets.top() != '{')
                return false;   // Invalid dacă `:` nu urmează după o cheie
            expectValue = true; // După `:` urmează o valoare
            allowComma = false;
            break;

        case ',':
            if (!allowComma)
                return false;   // Invalid dacă virgula nu e permisă
            expectValue = true; // După `,` ne așteptăm la o nouă valoare sau cheie
            allowComma = false;
            break;

        case 't':
        case 'f':
        case 'n': // Valori: true, false, null
            if (expectValue)
            {
                std::string val;
                if (json.substr(i, 4) == "true")
                    val = "true";
                else if (json.substr(i, 5) == "false")
                    val = "false";
                else if (json.substr(i, 4) == "null")
                    val = "null";
                else
                    return false;

                i += val.size() - 1; // Avansăm indexul
                expectValue = false;
                allowComma = true;
            }
            else
                return false;
            break;

        default: // Valori numerice
            if (isdigit(c) || c == '-')
            {
                if (!expectValue)
                    return false;
                while (i < json.size() && (isdigit(json[i]) || json[i] == '.' || json[i] == 'e' || json[i] == 'E' || json[i] == '+' || json[i] == '-'))
                    i++;
                i--; // Ajustăm indexul pentru a procesa corect
                expectValue = false;
                allowComma = true;
            }
            else
                return false; // Caracter invalid
            break;
        }
        i++;
    }

    // JSON valid dacă toate structurile sunt închise corect și nu mai așteptăm valori
    return brackets.empty() && !inString && !expectValue;
}

bool become_empty(char *p)
{
    while (strchr(p, '{') != NULL || strchr(p, '}') != NULL || strchr(p, '[') != NULL || strchr(p, ']') != NULL || strchr(p, ',') != NULL)
    {
        if (strchr(p, '{') != NULL)
        {
            char *modifiedString3 = removeSubstring(p, (char *)"{");
            strcpy(p, modifiedString3);
            delete[] modifiedString3;
        }
        if (strchr(p, '}') != NULL)
        {
            char *modifiedString3 = removeSubstring(p, (char *)"}");
            strcpy(p, modifiedString3);
            delete[] modifiedString3;
        }
        if (strchr(p, '[') != NULL)
        {
            char *modifiedString3 = removeSubstring(p, (char *)"[");
            strcpy(p, modifiedString3);
            delete[] modifiedString3;
        }
        if (strchr(p, ']') != NULL)
        {
            char *modifiedString3 = removeSubstring(p, (char *)"]");
            strcpy(p, modifiedString3);
            delete[] modifiedString3;
        }
        if (strchr(p, ',') != NULL)
        {
            char *modifiedString3 = removeSubstring(p, (char *)",");
            strcpy(p, modifiedString3);
            delete[] modifiedString3;
        }
    }
    if (strlen(p) == 0)
        return true;
    else
        return false;
}

void replaceSubstring(char *&str, const char *oldSubstr, const char *newSubstr)
{
    size_t oldLen = strlen(oldSubstr);
    size_t newLen = strlen(newSubstr);

    // Calculăm dimensiunea necesară pentru noul șir
    size_t strLen = strlen(str);
    size_t count = 0;

    // Numărăm de câte ori apare oldSubstr în str
    for (char *pos = strstr(str, oldSubstr); pos; pos = strstr(pos + oldLen, oldSubstr))
    {
        count++;
    }

    // Alocăm spațiu doar pentru noul șir exact
    size_t newStrLen = strLen + count * (newLen - oldLen);
    char *buffer = new char[newStrLen + 1];
    buffer[0] = '\0'; // Inițializăm buffer-ul ca șir gol

    char *lastPos = str;
    char *pos = strstr(str, oldSubstr);

    // Parcurgem șirul inițial și construim noul șir
    while (pos)
    {
        // Copiem partea dinaintea oldSubstr în buffer
        strncat(buffer, lastPos, pos - lastPos);

        // Adăugăm newSubstr în buffer
        strcat(buffer, newSubstr);

        // Avansăm lastPos după oldSubstr
        lastPos = pos + oldLen;

        // Căutăm următoarea apariție a oldSubstr
        pos = strstr(lastPos, oldSubstr);
    }

    // Copiem restul șirului după ultima apariție a oldSubstr
    strcat(buffer, lastPos);

    delete[] str; // Eliberăm vechiul șir
    str = buffer; // Actualizăm str la noul șir rezultat
}

int number_of_commas(char *str)
{
    int i = 0;

    int length = strlen(str);
    if (length <= 2)
    {
        cout << "0";
    }

    char *trimmed_str = new char[length - 1];
    strncpy(trimmed_str, str + 1, length - 2);
    trimmed_str[length - 2] = '\0';

    strcpy(str, trimmed_str);
    delete[] trimmed_str;

    // cout << "am intrat1= " << str << endl;

    // eliminam caracterele { } [ ] daca se afla in ghilimele
    int flag3 = 0;
    for (i = 0; i < strlen(str); i++)
    {
        if (str[i] == '"')
        {
            flag3++;
            if (str[i - 1] == '\\')
            {
                flag3--;
            }
        }
        if ((str[i] == '{' || str[i] == '}' || str[i] == '[' || str[i] == ']') && flag3 % 2 == 1)
        {
            stergeCaracterPePozitie2(str, i);
            i--;
        }
    }

    // cout << "am intrat2= " << str << endl;

    while (strchr(str, '{') != NULL || strchr(str, '}') != NULL || strchr(str, '[') != NULL || strchr(str, '{') != NULL)
    {
        char sir_creat1[strlen(str) + 1];
        int l = 0;
        flag3 = 0;
        int flag2 = 0;
        int flag4 = 1;
        for (i = 0; i < strlen(str) && flag4 > 0; i++)
        {
            if (str[i] == '"')
            {
                flag3++;
                if (str[i - 1] == '\\')
                {
                    flag3--;
                }
            }
            if (str[i] == '{' && flag2 == 1 && flag3 % 2 == 0)
            {
                flag4++;
            }
            if (str[i] == '[' && flag2 == 1 && flag3 % 2 == 0)
            {
                flag4++;
            }
            if (str[i] == '{' && flag2 == 0 && flag4 == 1 && flag3 % 2 == 0)
            {
                flag2++;
            }
            if (str[i] == '[' && flag2 == 0 && flag4 == 1 && flag3 % 2 == 0)
            {
                flag2++;
            }
            if (str[i] == '}' && flag3 % 2 == 0)
            {
                flag4--;
            }
            if (str[i] == ']' && flag3 % 2 == 0)
            {
                flag4--;
            }
            if (flag2 == 1)
            {
                sir_creat1[l] = str[i];
                l++;
            }
        }

        sir_creat1[l] = '\0';

        // cout << sir_creat1 << endl;

        char *modifiedString = removeSubstring(str, sir_creat1);
        strcpy(str, modifiedString);
        delete[] modifiedString;
    }

    int comma_count = 0;

    flag3 = 0;
    for (i = 0; i < strlen(str); i++)
    {
        if (str[i] == '"')
        {
            flag3++;
            if (str[i - 1] == '\\')
            {
                flag3--;
            }
        }
        if (str[i] == ',' && flag3 % 2 == 0)
        {
            comma_count++;
        }
    }

    return comma_count;
}

char *modifiedConcatToLeft(const char *sir1, const char *sir2)
{
    // Calculăm lungimea totală necesară pentru noul șir (plus 1 pentru terminatorul '\0')
    int totalLength = strlen(sir1) + strlen(sir2) + 1;

    // Alocăm spațiu pentru noul șir
    char *result = new char[totalLength];

    // Concatenăm sir2 în stânga și apoi sir1
    strcpy(result, sir2);
    strcat(result, ".");
    strcat(result, sir1);

    return result;
}

char *concatToLeft(const char *sir1, const char *sir2)
{
    // Calculăm lungimea totală necesară pentru noul șir (plus 1 pentru terminatorul '\0')
    int totalLength = strlen(sir1) + strlen(sir2) + 1;

    // Alocăm spațiu pentru noul șir
    char *result = new char[totalLength];

    // Concatenăm sir2 în stânga și apoi sir1
    strcpy(result, sir2);
    strcat(result, sir1);

    return result;
}

char *addCharToFront(const char *original, char newChar)
{
    // Creăm un nou șir cu o lungime mai mare cu 1 pentru caracterul nou
    int originalLength = strlen(original);
    char *newString = new char[originalLength + 2]; // +1 pentru '\0' +1 pentru caracter

    // Adăugăm caracterul nou la început
    newString[0] = newChar;

    // Copiem șirul original în noul șir
    strcpy(newString + 1, original);

    return newString; // Returnăm noul șir
}

char *addCharToEnd(const char *original, char newChar)
{
    int originalLength = strlen(original);
    char *newString = new char[originalLength + 2]; // +1 pentru '\0'

    // Copiem șirul original
    strcpy(newString, original);

    // Adăugăm noul caracter la sfârșit
    newString[originalLength] = newChar;
    newString[originalLength + 1] = '\0'; // Asigurăm terminarea șirului

    return newString; // Returnăm noul șir
}

char *eliminaDupaGhilimele(char *sir)
{
    int length = strlen(sir);
    stergeCaracterPePozitie(sir, length);
    length = strlen(sir);

    int vec[length];

    int j = 0, j2 = 0, j3 = 0, j4 = 0;
    int flag3 = 0;

    char *aux = new char[length];

    strcpy(aux, "");

    for (int j = 0; j < length; j++)
    {
        if (sir[j] == '"')
        {
            if (sir[j - 1] != '\\')
            {
                flag3++;
            }
        }

        if (sir[j] == ':' && (flag3 % 2 == 0))
        {
            sir[j] = '.';

            vec[j2] = j - 1;
            j2++;

            vec[j2] = j + 1;
            j2++;
        }
    }

    for (j = 0; j < strlen(sir); j++)
    {
        if (j != vec[j3])
        {
            aux[j4] = sir[j];
            j4++;
        }
        else
        {
            j3++;
        }
    }

    for (j = 0; j < j2; j++)
    {
        vec[j] = 0;
    }

    aux[j4] = '\0';

    return aux;
}

char *stergePrimaUltimaPozitie(const char *sir)
{
    int length = strlen(sir);

    // Dacă șirul are mai puțin de 2 caractere, returnăm un șir gol
    if (length <= 2)
    {
        char *emptyString = new char[1];
        emptyString[0] = '\0';
        return emptyString;
    }

    char *result = new char[length - 1];
    strncpy(result, sir + 1, length - 2);
    result[length - 2] = '\0';
    return result;
}

/*
int v1[1024], v2[1024], v3[1024], v4[1024];
int copyV1[1024], copyV2[1024];

char vector_chey[1024][1024], vector_chey2[1024][1024], vector_chey3[1024][1024], vector_chey4[1024][1024], vector_chey5[1024][1024];
char vector_words[1024][1024], vector_words2[1024][1024], vector_words3[1024][1024], vector_words4[1024][1024], vector_words5[1024][1024];

char copy1_s[9999], copy2_s[9999];
char aux[9999], aux2[9999], aux3[9999];
char sir_creat1[9999], sir_creat2[9999];
*/

char *copy1_s = nullptr;
char *copy2_s = nullptr;
char *aux = nullptr;
char *aux2 = nullptr;
char *aux3 = nullptr;

char *sir_creat1 = nullptr;
char *sir_creat2 = nullptr;

// path C:/Users/victor/Documents/jetbarain_task_1/input.txt

int main(int argc, char *argv[])
{

    int i=0, size_of_s = 0;
    char ch;

    int n = 9999;
    char *s = new char[n];
    char *s2 = new char[n];

    if (argc > 2)
    {
        string filePath = argv[1];
        string inputString = argv[2];

        ifstream inputFile(filePath);
        if (!inputFile.is_open())
        {
            cerr << "Eroare la deschiderea fisierului!" << std::endl;
            return 1;
        }

        while (inputFile.get(ch))
        {
            if (ch != '\n')
            {
                size_of_s++;
            }
        }

        // Resetează poziția la începutul fișierului
        inputFile.clear();
        inputFile.seekg(0, ios::beg);

        char *s2 = new char[size_of_s + 1];

        while (inputFile.get(ch))
        {
            if (ch != '\n')
            {
                s2[i] = ch;
                i++;
            }
        }

        s2[i] = '\0';
        inputFile.close();

        strcpy(s, s2);
    }
    else
    {
        cerr << "Utilizare: ./main /cale/catre/fisier \"input.string\"" << endl;
        return 1;
    }

    int n2 = 0, j = 0, j2 = 0, j3 = 0, j4 = 0, k = 0, l = 0, k2 = 0, l2 = 0, k3 = 0, l3 = 0;

    // flag3%2==1 means we are inside a string
    int flag3 = 0;

    int flag4 = 0;
    int flag5 = 0;

    // cin.getline(s, 256);

    if (isValidJson(s))
    {
        cout << "JSON-ul este valid." << endl;
    }
    else
    {
        cout << "JSON-ul nu este valid." << endl;
    }

    // eliminate spaces
    char *new_s = eliminareSpatii(s);

    strcpy(s, new_s);

    // modify JSON
    modifyJSON(s);

    // char *s2 = new char[n];
    // n = strlen(s) + 1;

    
    n2 = n;
    char *copy3_s = new char[n];

    strcpy(copy3_s, s);

    int *v1 = new int[n]();
    int *v2 = new int[n]();
    int *v3 = new int[n]();
    int *v4 = new int[n]();
    int *copyV1 = new int[n]();
    int *copyV2 = new int[n]();

    int *vec = new int[n];

    char *copy1_s = new char[n];

    char *copy2_s = new char[n];

    char *aux = new char[n];

    char *aux2 = new char[n];

    char *aux3 = new char[n];

    char **vector_chey = new char *[n];
    char **vector_chey2 = new char *[n];
    char **vector_chey3 = new char *[n];
    char **vector_chey4 = new char *[n];
    char **vector_chey5 = new char *[n];
    char **vector_chey6 = new char *[n];
    char **vector_chey7 = new char *[n];
    char **vector_chey8 = new char *[n];
    char **vector_chey9 = new char *[n];
    char **vector_words = new char *[n];
    char **vector_words2 = new char *[n];
    char **vector_words3 = new char *[n];
    char **vector_words4 = new char *[n];
    char **vector_words5 = new char *[n];

    // Inițializare matrice și vectori
    for (j = 0; j < n; j++)
    {
        vector_chey[j] = new char[n]();
        vector_chey2[j] = new char[n]();
        vector_chey3[j] = new char[n]();
        vector_chey4[j] = new char[n]();
        vector_chey5[j] = new char[n]();
        vector_chey6[j] = new char[n]();
        vector_chey7[j] = new char[n]();
        vector_chey8[j] = new char[n]();
        vector_chey9[j] = new char[n]();
        vector_words[j] = new char[n]();
        vector_words2[j] = new char[n]();
        vector_words3[j] = new char[n]();
        vector_words4[j] = new char[n]();
        vector_words5[j] = new char[n]();
    }
    strcpy(s, copy3_s);

    j = 0;
    k = 0;

    // avem 4 vectori
    // v1 - in care indexul din vector adica i reprezinta numarul de ordine pentru caracterul '{' iar valoarea efectiva v1[i] reprezinta indexul din sir
    // v2 - in care indexul din vector adica i reprezinta numarul de ordine pentru caracterul '}' iar valoarea efectiva v2[i] reprezinta indexul din sir
    // v3 - in care indexul din vector adica i reprezinta numarul de ordine pentru caracterul '[' iar valoarea efectiva v3[i] reprezinta indexul din sir
    // v4 - in care indexul din vector adica i reprezinta numarul de ordine pentru caracterul ']' iar valoarea efectiva v4[i] reprezinta indexul din sir

    strcpy(copy1_s, s);

    int maxDepth = calculateMaxDepth(s);

    int flag = 0;

    flag3 = 0;

    while (calculateMaxDepth(copy1_s) > 0)
    {
        int counterAscii123 = 0;
        // check for {
        flag = 0;
        for (int i = 0; i < strlen(copy1_s) && flag < 2; i++)
        {
            if (copy1_s[i] == '"')
            {
                flag3++;
                if (copy1_s[i - 1] == '\\')
                {
                    flag3--;
                }
            }
            if (flag == 1 && flag3 % 2 == 0)
            {
                if (copy1_s[i] == '}')
                {
                    v2[l] = i;
                    l++;
                    copy1_s[i] = ']';
                    flag++;
                }
            }
            if (flag == 0 && flag3 % 2 == 0)
            {
                if (copy1_s[i] == '{')
                {
                    counterAscii123++;
                }
                if (copy1_s[i] == '}')
                {
                    counterAscii123--;
                }
                if (counterAscii123 == maxDepth)
                {
                    v1[k] = i;
                    k++;
                    copy1_s[i] = '[';
                    flag++;
                }
            }
        }
        maxDepth = calculateMaxDepth(copy1_s);
    }

    strcpy(copy1_s, s);
    maxDepth = calculateMaxDepth2(s);

    flag = 0;

    flag3 = 0;

    while (calculateMaxDepth2(copy1_s) != 0)
    {
        int counterAscii123 = 0;
        // check for {
        flag = 0;

        for (int i = 0; i < strlen(copy1_s) && flag < 2; i++)
        {
            if (copy1_s[i] == '"')
            {
                flag3++;
                if (copy1_s[i - 1] == '\\')
                {
                    flag3--;
                }
            }
            if (flag == 1 && flag3 % 2 == 0)
            {
                if (copy1_s[i] == ']')
                {
                    v4[l2] = i;
                    l2++;
                    copy1_s[i] = '}';
                    flag++;
                }
            }
            if (flag == 0 && flag3 % 2 == 0)
            {
                if (copy1_s[i] == '[')
                {
                    counterAscii123++;
                }
                if (copy1_s[i] == ']')
                {
                    counterAscii123--;
                }
                if (counterAscii123 == maxDepth)
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

    int v5[k + k2] = {0};
    int v6[l + l2] = {0};

    flag3 = 0;

    for (i = 0; i < strlen(s); i++)
    {
        if (s[i] == '"')
        {
            flag3++;
            if (s[i - 1] == '\\')
            {
                flag3--;
            }
        }

        if (s[i] == '{' && flag3 % 2 == 0)
        {
            flag = 0;
            for (j = 0; j < k && flag == 0; j++)
            {
                if (i == v1[j])
                {
                    v5[k3] = v1[j];
                    v6[k3] = v2[j];
                    k3++;
                    flag++;
                }
            }
        }
        if (s[i] == '[' && flag3 % 2 == 0)
        {
            flag = 0;
            for (j = 0; j < k2 && flag == 0; j++)
            {
                if (i == v3[j])
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
    for (int m = 0; m < k3; m++)
    {
        copyV1[m] = v5[m];
    }

    for (int n = 0; n < k3; n++)
    {
        copyV2[n] = v6[n];

        // cout << v5[n] << " " << v6[n] << endl;
    }

    n = k3;

    // falag reprezinta ca suntem pe caracterul '{' cel mai din stanga
    flag = 0;

    // utilizat ca atunci cand dam peste : sa parcurgem backwards de la prima " la a doua "
    int flag2 = 0;

    flag3 = 0;

    // reset k and l for iteration
    k = 0;

    // index for sir_creat1
    l = 0;

    // index for sir_creat2
    int t = 0;

    // index pentru a oglindi sir_creat2 si pune in sir_creat1
    int t2 = 0;

    sir_creat1 = new char[n2](); // Pentru a construi cheile

    sir_creat2 = new char[n2](); // Pentru a constui cheile

    for (i = 0; i < strlen(s); i++)
    {
        if (s[i] == '"')
        {
            flag3++;
            if (s[i - 1] == '\\')
            {
                flag3--;
            }
        }
        // extract key
        if (flag == 1 && flag2 < 2)
        {
            while (flag2 < 2)
            {
                if (flag2 > 0)
                {
                    if (s[i - 1 - t] != '"')
                    {
                        sir_creat2[t] = s[i - 1 - t];
                        t++;
                    }
                    if (s[i - 1 - t] == '"')
                    {
                        sir_creat2[t] = s[i - 1 - t];
                        t++;
                        flag2++;
                        flag3++;
                        if (s[i - 1 - t] == '\\')
                        {
                            flag2--;
                            flag3--;
                        }
                    }
                }
                if (s[i - 1] == ':' && flag2 == 0)
                {
                    sir_creat2[t] = s[i - 1 - t];
                    t++;

                    if (s[i - 1 - t] == '"')
                    {
                        sir_creat2[t] = s[i - 1 - t];
                        t++;
                        flag2++;
                        flag3++;
                    }
                }
            }

            // cout << sir_creat2 << endl;

            // oglindim sir_creat2 in sir_creat1
            for (t2 = strlen(sir_creat2) - 1; t2 >= 0; t2--)
            {
                sir_creat1[l] = sir_creat2[t2];
                l++;
            }

            // golim sir_creat2
            while (t > -1)
            {
                stergeCaracterPePozitie(sir_creat2, t);
                t--;
            }
            // pentru a ajunge cu t la 0
            t++;

            // Save key
            strcpy(vector_chey[k], sir_creat1);

            // pregatim indexul urmatoarei key
            k++;

            // golim sir_creat1
            while (l > -1)
            {
                stergeCaracterPePozitie(sir_creat1, l);
                l--;
            }
            // pentru a ajunge cu l la 0
            l++;

            // reset flags
            flag2 = 0;
            flag = 0;
        }

        // if flag3%2==1 means we are inside a string
        if (s[i] == ':' && flag3 % 2 == 0 && flag == 0)
        {
            flag++;
        }
    }

    int size_of_vector_chey = k;

    // for(int m=0; m < size_of_vector_chey; m++)
    //     cout << vector_chey[m] << endl;

    // flag reprezinta ca suntem pe caracterul '{' cel mai din stanga
    flag = 0;

    // reprezinta ca am actualizat start_index
    flag2 = 0;

    // if flag3%2==1 means we are inside a string
    flag3 = 0;

    // reprezinta ca suntem  la prima perece {} sau [] inside { {} } initial dupa se mareste la fiecare pereche {} sau []
    int index_v1 = 0;

    // reset k and l for iteration
    k = 0;
    l = 0;

    // j = 0 reprezinta indexul din v1 in care stim pozitia primul caracter '{' sau '[' si folosim si faptul ca v2[j] stocheaza cel mai din dreapta caracter '}' sau ']'
    j = 0;

    int start_index = 0;
    int end_index = 0;

    // for(j=0; j<n; j++){
    //     cout << copyV1[j] << endl;
    // }

    // spargem o expresie care incepe cu caracter '{' si se termina cu caracter '}' ex: {{},[],{}}
    // index_v1 contorizam perechile din interiorul {} sau [] peste care dam atunci cand facem extractia {} sau []
    for (i = 0; i < strlen(s); i++)
    {
        if (s[i] == '"')
        {
            flag3++;
            if (s[i - 1] == '\\')
            {
                flag3--;
            }
        }

        // Verificăm dacă suntem în interiorul unei secțiuni JSON
        if (flag == 1 && i < copyV2[j])
        {
            if (flag2 == 1)
            {
                if (i >= start_index && i < end_index && flag2 > 0)
                {
                    sir_creat1[l] = s[i];
                    l++;

                    if ((s[i] == '{' || s[i] == '[') && flag3 % 2 == 0)
                    {
                        index_v1++;
                    }
                }
                // cout << start_index << " " << end_index << endl;

                if (i == end_index && flag2 > 0)
                {
                    sir_creat1[l] = s[i];
                    l++;
                    sir_creat1[l] = '\0'; // Terminăm sirul
                    // l++;

                    strcpy(vector_words[k], sir_creat1); // Salvăm cuventul {}

                    while (l > -1)
                    {
                        stergeCaracterPePozitie(sir_creat1, l);
                        l--;
                    }
                    // pentru a ajunge cu l la 0
                    l++;
                    k++;
                    flag2--;
                }
            }
            if (s[i] == ':' && flag2 == 0 && flag3 % 2 == 0)
            {
                i++;
                if ((s[i] == '{' || s[i] == '[') && index_v1 < n && flag2 == 0)
                {
                    start_index = v5[index_v1];
                    end_index = v6[index_v1];

                    // cout << start_index << " " << end_index << endl;
                    flag2++;
                    index_v1++;
                }
                if (i >= start_index && i <= end_index && flag2 > 0)
                {
                    sir_creat1[l] = s[i];
                    l++;
                }
            }
        }

        // Dacă întâlnim '{', setăm flag-ul
        if (s[i] == '{' && flag == 0)
        {
            flag++;
            copyV1[j] = -1; // Pornim procesul
            index_v1++;
        }
    }

    int size_of_vector_words = k;

    // Afisam vectorul chei si words
    /*
    for (int m = 0; m < size_of_vector_chey; m++)
    {
        cout << vector_chey[m];
        if (m <= size_of_vector_words)
            cout << " " << vector_words[m];
        cout << endl;
    }
    */

    // pana aici merge
    int size_of_vector_chey2 = 0;
    int size_of_vector_words2 = 0;

    flag3 = 0;
    l2 = 0;
    l3 = 0;
    i = 0;

    // cout << "am intrat " << s << endl;
    strcpy(copy1_s, s);

    // while(size_of_vector_words != 0)
    while (size_of_vector_words > 0)
    {
        strcpy(copy2_s, copy1_s);
        l = 0;
        strcpy(sir_creat1, "");

        t = 0;
        strcpy(sir_creat2, "");

        new_s = strstr(copy2_s, vector_words[i]);

        if (new_s != nullptr)
        {
            *(new_s + strlen(vector_words[i])) = '\0'; // trunchiem dupa aparitia sirului

            // Calculăm lungimea părții pe care vrem să o copiem
            int length_to_copy = new_s - copy2_s + strlen(vector_words[i]);

            // Creăm un nou șir pentru a păstra rezultatul
            char result[length_to_copy + 1]; // +1 pentru '\0'

            // Copiem în noul șir
            strncpy(result, copy2_s, length_to_copy);
            result[length_to_copy] = '\0'; // Asigurăm terminarea șirului

            new_s = result;

            // cout << new_s << endl;

            flag = 0;
            flag2 = 0;

            // starts with value 1 beacause we don`t count the first appeareance of { or [
            flag4 = 1;
            flag5 = 1;

            // if flag3%2==1 means we are inside a string
            flag3 = 0;

            for (j = strlen(new_s) - 1; j >= 0 && (flag4 > 0 && flag5 > 0); j--)
            {
                if (flag == 1 && flag2 == 0)
                {
                    if (new_s[j] == '}')
                    {
                        flag4++;
                    }
                    if (new_s[j] == '{')
                    {
                        flag4--;
                    }
                }
                if (flag == 0 && flag2 == 1)
                {
                    if (new_s[j] == ']')
                    {
                        flag5++;
                    }
                    if (new_s[j] == '[')
                    {
                        flag5--;
                    }
                }
                if (new_s[j] == '}' && flag == 0 && flag2 == 0)
                {
                    flag++;
                }

                if (new_s[j] == ']' && flag2 == 0 && flag == 0)
                {
                    flag2++;
                }
            }

            flag = 0;

            // now the caracter in new_s[j] is :
            while (j >= 0 && flag < 2)
            {

                if (new_s[j] == '"')
                {
                    flag++;
                    if (new_s[j - 1] == '\\')
                    {
                        flag--;
                    }
                }
                sir_creat2[t] = new_s[j];
                t++;
                j--;
            }

            sir_creat2[t] = '\0';

            // oglindim sir_creat2 in sir_creat1
            for (t2 = strlen(sir_creat2) - 1; t2 >= 0; t2--)
            {
                sir_creat1[l] = sir_creat2[t2];
                l++;
            }

            // golim sir_creat2
            while (t > -1)
            {
                stergeCaracterPePozitie(sir_creat2, t);
                t--;
            }
            // pentru a ajunge cu t la 0
            t++;

            // cout << new_s << endl;

            strcpy(vector_chey2[l2], sir_creat1);
            l2++;
            size_of_vector_chey2++;

            // golim sir_creat1
            while (l > -1)
            {
                stergeCaracterPePozitie(sir_creat1, l);
                l--;
            }
            // pentru a ajunge cu l la 0
            l++;

            new_s = strstr(copy2_s, vector_words[i]);

            strcpy(vector_words2[l3], new_s);
            l3++;
            size_of_vector_words2++;

            // cout << vector_chey2[0] << " " << vector_words2[0] << endl;

            char *result2 = new char[strlen(vector_chey2[l2 - 1]) + strlen(vector_words2[l3 - 1]) + 1];

            strcpy(result2, "");

            flag5 = 0;
            // eliminate first appeareance of vector_words2[l2-1] from vector_words
            for (j3 = 0; j3 < size_of_vector_words && flag5 == 0; j3++)
            {
                if (strcmp(vector_words[j3], vector_words2[l2 - 1]) == 0)
                {
                    for (j4 = j3; j4 < size_of_vector_words; j4++)
                        strcpy(vector_words[j4], vector_words[j4 + 1]);
                    size_of_vector_words--;
                    flag5++;
                }
            }

            strcat(result2, vector_chey2[l2 - 1]);
            strcat(result2, vector_words2[l3 - 1]);

            char *modifiedString = removeSubstring(copy1_s, result2);

            // cout << "am intrat= " << modifiedString << endl;

            strcpy(copy1_s, modifiedString);
            delete[] modifiedString;

            // copy1_s now has the old cop1_s with result2 removed
            // cout << copy1_s << endl;
        }
    }

    t = 0;

    // Afisam vector_chei2 si vector_words2
    for (int m = 0; m < size_of_vector_chey; m++)
    {
        if (strcmp(vector_chey[m], vector_chey2[t]) == 0)
        {
            strcpy(vector_chey3[m], vector_chey2[t]);
            strcpy(vector_words3[m], vector_words2[t]);
            t++;
        }
        else
        {
            strcpy(vector_chey3[m], vector_chey[m]);
        }
        // cout << vector_chey[m] << " " << vector_words3[m] << endl;
    }

    // inainte de a prelucra words3 il salvam in words4
    // copiem cuvintele in vector_words4 inainte de a face extractiile

    for (int m = 0; m < size_of_vector_chey; m++)
    {
        strcpy(vector_words4[m], vector_words3[m]);
        // cout << vector_words4[m] << endl;
    }

    int size_of_vector_chey3 = size_of_vector_chey;
    int size_of_vector_words3 = size_of_vector_chey;

    i = 0, j = 0, j2 = 0, j3 = 0, j4 = 0, k = 0, k2 = 0, k3 = 0, l = 0, l2 = 0, l3 = 0, t = 0, t2 = 0;
    flag = 0, flag2 = 0, flag3 = 0, flag4 = 0, flag5 = 0;

    for (i = 0; i < size_of_vector_chey3; i++)
    {
        if (strlen(vector_words3[i]) == 0)
        {
            flag = 0;
            for (j = i - 1; j >= 0 && flag == 0; j--)
            {
                // if(vector_chey3[i] is in vector_words3[j])
                if (strstr(vector_words3[j], vector_chey3[i]) != nullptr)
                {

                    // extract the string starting with the vector_chey3[i] from vector_words3[j]
                    char *new_s2 = strstr(vector_words3[j], vector_chey3[i]);

                    // increment this vlag when encounter the first character { or [
                    flag2 = 0;

                    flag3 = 0;

                    // we assune that we have already encountered the character { or [
                    flag4 = 1;

                    // cout << "am intrat=" << new_s2 << endl;
                    l = 0;

                    // cout << "am intrat= " << new_s2 << endl;

                    // aici sir_creat1 este gol
                    // start with j2 with the position after the first character that is either { or [
                    for (j2 = 0; j2 < strlen(new_s2) && flag4 > 0; j2++)
                    {
                        if (new_s2[j2] == '"')
                        {
                            flag3++;
                            if (new_s2[j2 - 1] == '\\')
                            {
                                flag3--;
                            }
                        }
                        if (new_s2[j2] == '{' && flag2 == 1 && flag3 % 2 == 0)
                        {
                            flag4++;
                        }
                        if (new_s2[j2] == '[' && flag2 == 1 && flag3 % 2 == 0)
                        {
                            flag4++;
                        }
                        if (new_s2[j2] == '{' && flag2 == 0 && flag4 == 1 && flag3 % 2 == 0)
                        {
                            flag2++;
                        }
                        if (new_s2[j2] == '[' && flag2 == 0 && flag4 == 1 && flag3 % 2 == 0)
                        {
                            flag2++;
                        }
                        if (new_s2[j2] == '}' && flag3 % 2 == 0)
                        {
                            flag4--;
                        }
                        if (new_s2[j2] == ']' && flag3 % 2 == 0)
                        {
                            flag4--;
                        }
                        if (flag2 == 1)
                        {
                            sir_creat1[l] = new_s2[j2];
                            l++;
                        }
                    }
                    if (flag4 == 0)
                    {
                        delete[] new_s2;
                        sir_creat1[l] = '\0';

                        // salvam sircreat1 in vector_words4, sircreat1 reprezinta wordul fara sa se fi aplicat extractia
                        strcpy(vector_words4[i], sir_creat1);

                        // cout << "am intrat2= " << sir_creat1 << endl;

                        strcpy(vector_words3[i], sir_creat1);

                        char *result3 = new char[strlen(vector_chey3[i]) + strlen(sir_creat1) + 1];

                        strcpy(result3, "");

                        // facem ca in result3 sa avem key + word
                        strcat(result3, vector_chey3[i]);
                        strcat(result3, sir_creat1);

                        // stergem result3 din words3[j]
                        char *modifiedString2 = removeSubstring(vector_words3[j], result3);

                        strcpy(vector_words3[j], modifiedString2);
                        delete[] modifiedString2;

                        // cout << "am intrat= " << vector_words3[j] << endl;

                        // golim sir_creat1
                        while (l > -1)
                        {
                            stergeCaracterPePozitie(sir_creat1, l);
                            l--;
                        }
                        // pentru a ajunge cu l la 0
                        l++;

                        flag++;

                        // cout << "am intrat= " << vector_words3[j] << endl;

                        strcpy(aux, vector_words3[j]);
                        // if vector_words3[j] has become [{,},{,},{,}] then restore to the initial string before extraction
                        if (become_empty(aux) == true)
                        {
                            strcpy(vector_words3[j], vector_words4[j]);
                        }
                    }
                }
            }
        }
    }

    // acum in vector_words4 avem extragerea completa a cuvintelor
    /*
    for (int m = 0; m < size_of_vector_chey; m++)
    {
        cout << vector_chey3[m] << " " << vector_words4[m] << endl;
    }
    */

    /*
    Transform from this:
    "x": {789}
    "a": {"b":[1,2,{"c":{false}},[11,12]]}
    "b": [1,2,{"c":{false}},[11,12]]
    "c": {false}
    "y": {999}

    To this:
    "x": 789
    "a": {"b":[1,2,{"c":false},[11,12]]}
    "b": [1,2,{"c":false},[11,12]]
    "c": false
    "y": 999
    */

    // Modificare vector_words4 pentru a avea valorile corespunzătoare
    // Parcurgere vector_words4 de jos in sus
    for (int m = size_of_vector_chey - 1; m >= 0; m--)
    {
        string value = vector_words4[m];
        if (value[0] == '{' && value[value.size() - 1] == '}')
        {
            // Verifică max depth
            int maxDepth = calculateMaxDepth(vector_words4[m]);
            if (maxDepth == 1)
            {
                // Elimină acoladele
                value = value.substr(1, value.size() - 2);
            }

            for (k = m - 1; k >= 0; k--)
            {
                replaceSubstring(vector_words4[k], vector_words4[m], value.c_str());
            }
            strcpy(vector_words4[m], value.c_str());
        }
    }

    i = 0, j = 0, j2 = 0, j3 = 0, j4 = 0, l = 0, k = 0;
    flag = 0, flag2 = 0, flag3 = 0, flag4 = 0, flag5 = 0;
    cout << endl;
    // Afișare rezultat
    for (int m = 0; m < size_of_vector_chey; m++)
    {
        cout << vector_chey3[m] << " " << vector_words4[m] << endl;
    }

    /*
    Transform from this:
    "x": 789
    "a": {"b":[1,2,{"c":false},[11,12]]}
    "b": [1,2,{"c":false},[11,12]]
    "c": false
    "y": 999

    To this:
    x -789
    a {"b":[1,2,{"c":"test"},[11,12]]}
    b [1,2,{"c":"test"},[11,12]]
    b 1
    b 2
    b {"c":"test"}
    b [11,12]
    c "test"
    y -999
    */

    cout << endl;
    for (i = 0; i < size_of_vector_chey; i++)
    {
        j2 = 0;
        flag = 0;
        if (vector_words4[i][0] == '[' && vector_words4[i][strlen(vector_words4[i]) == ']'] && flag == 0)
        {
            flag++;
        }

        if (flag == 1)
        {

            // before break_down vector_words4[i] save
            j2 = 0;
            for (k = 1; k < strlen(vector_chey3[i]) - 2; k++)
            {
                vector_chey4[j4][j2] = vector_chey3[i][k];
                j2++;
            }
            vector_chey4[j4][j2] = '\0';
            j4++;

            strcpy(vector_words5[j3], vector_words4[i]);
            j3++;

            flag3 = 0;
            // before counting the character , eliminate the first index and last index from copy_vector_words4[i]
            // count the number of character , in a string
            strcpy(aux, vector_words4[i]);
            int numberOfCommas = number_of_commas(aux);
            int countCommas = 0;

            for (j = 1; j < strlen(vector_words4[i]) - 1; j++)
            {
                if (vector_words4[i][j] == '"')
                {
                    flag3++;
                    if (vector_words4[i][j - 1] == '\\')
                    {
                        flag3--;
                    }
                }
                flag5 = 0;
                if ((vector_words4[i][j] == '{' || vector_words4[i][j] == '[') && flag3 % 2 == 0)
                {
                    flag2 = 0;
                    flag4 = 1;
                    while (j < strlen(vector_words4[i]) - 1 && flag4 > 0)
                    {
                        if (vector_words4[i][j] == '{' && flag2 == 1 && flag3 % 2 == 0)
                        {
                            flag4++;
                        }
                        if (vector_words4[i][j] == '[' && flag2 == 1 && flag3 % 2 == 0)
                        {
                            flag4++;
                        }
                        if (vector_words4[i][j] == '{' && flag2 == 0 && flag4 == 1 && flag3 % 2 == 0)
                        {
                            flag2++;
                        }
                        if (vector_words4[i][j] == '[' && flag2 == 0 && flag4 == 1 && flag3 % 2 == 0)
                        {
                            flag2++;
                        }
                        if (vector_words4[i][j] == '}' && flag3 % 2 == 0)
                        {
                            flag4--;
                        }
                        if (vector_words4[i][j] == ']' && flag3 % 2 == 0)
                        {
                            flag4--;
                        }
                        if (flag2 == 1)
                        {
                            sir_creat1[l] = vector_words4[i][j];
                            l++;
                        }
                        j++;
                    }
                    flag5++;
                }
                if (flag5 == 0 && vector_words4[i][j] != ',' && countCommas < numberOfCommas && flag3 % 2 == 0)
                {
                    sir_creat1[l] = vector_words4[i][j];
                    l++;
                }
                if (countCommas >= numberOfCommas)
                {
                    if (j < strlen(vector_words4[i]) - 1)
                    {
                        sir_creat1[l] = vector_words4[i][j];
                        l++;
                    }

                    if (j == strlen(vector_words4[i]) - 1)
                    {
                        sir_creat1[l] = '\0';

                        j2 = 0;
                        for (k = 1; k < strlen(vector_chey3[i]) - 2; k++)
                        {
                            vector_chey4[j4][j2] = vector_chey3[i][k];
                            j2++;
                        }
                        vector_chey4[j4][j2] = '\0';
                        j4++;

                        strcpy(vector_words5[j3], sir_creat1);
                        j3++;
                        // golim sir_creat1
                        while (l > -1)
                        {
                            stergeCaracterPePozitie(sir_creat1, l);
                            l--;
                        }
                        // pentru a ajunge cu l la 0
                        l++;
                    }
                }
                if (vector_words4[i][j] == ',' && countCommas < numberOfCommas && flag3 % 2 == 0)
                {
                    sir_creat1[l] = '\0';

                    j2 = 0;
                    for (k = 1; k < strlen(vector_chey3[i]) - 2; k++)
                    {
                        vector_chey4[j4][j2] = vector_chey3[i][k];
                        j2++;
                    }
                    vector_chey4[j4][j2] = '\0';
                    j4++;

                    strcpy(vector_words5[j3], sir_creat1);
                    j3++;
                    // golim sir_creat1
                    while (l > -1)
                    {
                        stergeCaracterPePozitie(sir_creat1, l);
                        l--;
                    }
                    // pentru a ajunge cu l la 0
                    l++;
                    countCommas++;
                }
            }
        }
        else
        {

            // copy without " ":
            for (j = 1; j < strlen(vector_chey3[i]) - 2; j++)
            {
                vector_chey4[j4][j2] = vector_chey3[i][j];
                j2++;
            }
            vector_chey4[j4][j2] = '\0';
            j4++;

            strcpy(vector_words5[j3], vector_words4[i]);
            j3++;
        }
    }

    int size_of_vector_chey4 = j4;

    for (i = 0; i < size_of_vector_chey4; i++)
    {
        cout << vector_chey4[i] << " " << vector_words5[i] << endl;
    }

    /*
    Transform from this:
    x -789
    a {"b":[1,2,{"c":"test"},[11,12]]}
    b [1,2,{"c":"test"},[11,12]]
    b 1
    b 2
    b {"c":"test"}
    b [11,12]
    c "test"
    y -99

    To this:
    x     -789
    a     {"b":[1,2,{"c":"test"},[11,12]]}
    b     [1,2,{"c":"test"},[11,12]]
    b[0]  1
    b[1]  2
    b[2]  {"c":"test"}
    b[3]  [11,12]
    c     "test"
    y     -99
    */

    int i2 = 0, counter = 0;
    i = 0, j = 0, j2 = 0, j3 = 0, j4 = 0, l = 0, k = 0;
    flag = 0, flag2 = 0, flag3 = 0, flag4 = 0, flag5 = 0;

    string counterAsString = to_string(counter);

    // cout << "am intrat2 = " << size_of_vector_chey4-1 << endl;

    for (i = 0; i < size_of_vector_chey4 - 1; i++)
    {
        if (strcmp(vector_chey4[i], vector_chey4[i + 1]) != 0)
        {
            if (flag == 1)
            {
                if ((strcmp(vector_chey4[i], vector_chey4[i - 1]) == 0) && i > 0)
                {
                    strcpy(aux, vector_chey4[i]);
                    strcat(aux, "[");
                    counterAsString = to_string(counter);
                    strcat(aux, counterAsString.c_str());
                    strcat(aux, "]");

                    strcpy(vector_chey5[j4], aux);
                    j4++;
                    counter++;
                }
            }
            if (flag == 0)
            {
                strcpy(vector_chey5[j4], vector_chey4[i]);
                j4++;

                if (i == size_of_vector_chey4 - 2)
                {
                    strcpy(vector_chey5[j4], vector_chey4[i + 1]);
                    j4++;
                }
            }
            flag = 0;
            counter = 0;
        }

        if ((strcmp(vector_chey4[i], vector_chey4[i + 1]) == 0))
        {
            if (flag == 1)
            {

                strcpy(aux, vector_chey4[i]);
                strcat(aux, "[");
                counterAsString = to_string(counter);
                strcat(aux, counterAsString.c_str());
                strcat(aux, "]");

                strcpy(vector_chey5[j4], aux);
                j4++;
                counter++;

                strcpy(aux, vector_chey4[i + 1]);
                strcat(aux, "[");
                counterAsString = to_string(counter);
                strcat(aux, counterAsString.c_str());
                strcat(aux, "]");

                strcpy(vector_chey5[j4], aux);
                j4++;
                counter++;

                i++;
                k = i;
                k++;
                if (k == size_of_vector_chey4 - 1)
                {

                    // primul caz era tot b pe ultima pozitie
                    if ((strcmp(vector_chey4[k], vector_chey4[k - 1])) == 0)
                    {
                        strcpy(aux, vector_chey4[k]);
                        strcat(aux, "[");
                        counterAsString = to_string(counter);
                        strcat(aux, counterAsString.c_str());
                        strcat(aux, "]");

                        strcpy(vector_chey5[j4], aux);
                        j4++;
                        counter++;
                    }
                    // difera pe ultima pozitie de ce era inainte
                    if ((strcmp(vector_chey4[k], vector_chey4[k - 1])) != 0)
                    {
                        strcpy(vector_chey5[j4], vector_chey4[k]);
                        j4++;
                    }
                }
            }
            if (flag == 0)
            {
                strcpy(vector_chey5[j4], vector_chey4[i]);
                j4++;

                strcpy(aux, vector_chey4[i + 1]);
                strcat(aux, "[");
                counterAsString = to_string(counter);
                strcat(aux, counterAsString.c_str());
                strcat(aux, "]");

                strcpy(vector_chey5[j4], aux);
                j4++;

                i++;
                counter++;
                flag++;
            }
        }
    }

    // cout << "am intrat= " << j4 << endl;
    int size_of_vector_chey5 = j4;

    cout << endl;
    // vector_chey7 = "chey5":
    for (i = 0; i < size_of_vector_chey5; i++)
    {
        char *modifiedString = addCharToFront(vector_chey5[i], '"');

        // Adăugăm '"' la sfârșit
        modifiedString = addCharToEnd(modifiedString, '"');

        // Adăugăm ":" la sfârșit
        modifiedString = addCharToEnd(modifiedString, ':');
        strcpy(vector_chey7[i], modifiedString);
        strcpy(vector_chey8[i], modifiedString);
    }

    for (i = 0; i < size_of_vector_chey5; i++)
    {
        cout << vector_chey5[i] << " " << vector_words5[i] << endl;
    }

    /*
    Transform from this:
    x     -789
    a     {"b":[1,2,{"c":"test"},[11,12]]}
    b     [1,2,{"c":"test"},[11,12]]
    b[0]  1
    b[1]  2
    b[2]  {"c":"test"}
    b[3]  [11,12]
    c     "test"
    y     -999

    To this:
    "x": -789
    "a": {"b":[1,2,{"c":"test"},[11,12]]}
    "a":"b": [1,2,{"c":"test"},[11,12]]
    "a":"b[0]": 1
    "a":"b[1]": 2
    "a":"b[2]": {"c":"test"}
    "a":"b[3]": [11,12]
    "a":"b[2]":"c": "test"
    "y": -999
    */

    i = 0, i2 = 0, j = 0, j2 = 0, j3 = 0, j4 = 0, l = 0, k = 0;
    flag = 0, flag2 = 0, flag3 = 0, flag4 = 0, flag5 = 0;

    // extract de key from words for the current key and stock them in vector_chey5
    for (i2 = 0; i2 < size_of_vector_chey5; i2++)
    {
        strcpy(sir_creat1, "");
        strcpy(sir_creat2, "");

        // temporary place to store keys

        for (i = 0; i < size_of_vector_chey4 + 1; i++)
        {
            strcpy(vector_chey6[i], "");
        }

        k = 0, l = 0, t = 0;
        flag = 0, flag2 = 0, flag3 = 0;

        for (i = 0; i < strlen(vector_words5[i2]); i++)
        {
            if (vector_words5[i2][i] == '"')
            {
                flag3++;
                if (vector_words5[i2][i - 1] == '\\')
                {
                    flag3--;
                }
            }
            // extract key
            if (flag == 1 && flag2 < 2)
            {
                while (flag2 < 2)
                {
                    if (flag2 > 0)
                    {
                        if (vector_words5[i2][i - 1 - t] != '"')
                        {
                            sir_creat2[t] = vector_words5[i2][i - 1 - t];
                            t++;
                        }
                        if (vector_words5[i2][i - 1 - t] == '"')
                        {
                            sir_creat2[t] = vector_words5[i2][i - 1 - t];
                            t++;
                            flag2++;
                            flag3++;
                            if (vector_words5[i2][i - 1 - t] == '\\')
                            {
                                flag2--;
                                flag3--;
                            }
                        }
                    }
                    if (vector_words5[i2][i - 1] == ':' && flag2 == 0)
                    {
                        sir_creat2[t] = vector_words5[i2][i - 1 - t];
                        t++;

                        if (vector_words5[i2][i - 1 - t] == '"')
                        {
                            sir_creat2[t] = vector_words5[i2][i - 1 - t];
                            t++;
                            flag2++;
                            flag3++;
                        }
                    }
                }

                // cout << sir_creat2 << endl;

                // oglindim sir_creat2 in sir_creat1
                for (t2 = strlen(sir_creat2) - 1; t2 >= 0; t2--)
                {
                    sir_creat1[l] = sir_creat2[t2];
                    l++;
                }

                // golim sir_creat2
                while (t > -1)
                {
                    stergeCaracterPePozitie(sir_creat2, t);
                    t--;
                }
                // pentru a ajunge cu t la 0
                t++;

                // Save key
                strcpy(vector_chey6[k], sir_creat1);

                // pregatim indexul urmatoarei key
                k++;

                // golim sir_creat1
                while (l > -1)
                {
                    stergeCaracterPePozitie(sir_creat1, l);
                    l--;
                }
                // pentru a ajunge cu l la 0
                l++;

                // reset flags
                flag2 = 0;
                flag = 0;
            }

            // if flag3%2==1 means we are inside a string
            if (vector_words5[i2][i] == ':' && flag3 % 2 == 0 && flag == 0)
            {
                flag++;
            }
        }
        if (k > 0)
        {
            int counter = 0;

            // cout << k << endl;
            for (j2 = i2 + 1; j2 < size_of_vector_chey4 && counter < k; j2++)
            {
                flag4 = 0;
                for (j4 = 0; j4 < k && flag4 == 0; j4++)
                {
                    char modified_chey6[strlen(vector_chey6[j4] + 1)];
                    strncpy(modified_chey6, vector_chey6[j4] + 1, strlen(vector_chey6[j4]) - 3);
                    modified_chey6[strlen(vector_chey6[j4]) - 3] = '\0';

                    if (strcmp(vector_chey4[j2], modified_chey6) == 0)
                    {
                        flag4++;
                    }
                }
                if (flag4 == 1)
                {
                    char *rezultat = concatToLeft(vector_chey7[j2], vector_chey8[i2]);
                    strcpy(vector_chey7[j2], rezultat);
                }
                if (strcmp(vector_chey4[j2], vector_chey4[j2 - 1]) != 0)
                {
                    counter++;
                }
            }
        }
    }

    /*
    Transform from this:
    "x": -789
    "a": {"b":[1,2,{"c":"test"},[11,12]]}
    "a":"b": [1,2,{"c":"test"},[11,12]]
    "a":"b[0]": 1
    "a":"b[1]": 2
    "a":"b[2]": {"c":"test"}
    "a":"b[3]": [11,12]
    "a":"b[2]":"c": "test"
    "y": -999

    To this:
    x          -789
    a          {"b":[1,2,{"c":"test"},[11,12]]}
    a.b        [1,2,{"c":"test"},[11,12]]
    a.b[0]     1
    a.b[1]     2
    a.b[2]     {"c":"test"}
    a.b[3]     [11,12]
    a.b[2].c   "test"
    y          -999
    */

    i = 0, i2 = 0, j = 0, j2 = 0, j3 = 0, j4 = 0, l = 0, k = 0;
    flag = 0, flag2 = 0, flag3 = 0, flag4 = 0, flag5 = 0;

    cout << endl;
    for (i = 0; i < size_of_vector_chey5; i++)
    {
        strcpy(sir_creat1, vector_chey7[i]);
        strcpy(aux, "");
        strcpy(aux2, "");
        strcpy(aux3, "");
        flag = 0, flag3 = 0;
        j = 0, j2 = 0;

        for (j = 0; j < strlen(sir_creat1); j++)
        {
            if (sir_creat1[j] == '"')
            {
                flag3++;
                if (sir_creat1[j] == '\\')
                {
                    flag3--;
                }
            }
            if (sir_creat1[j] == ':' && flag3 % 2 == 0)
            {
                char temp[2] = {sir_creat1[j], '\0'};
                strcat(aux, temp);
                strcpy(vector_chey9[j2], aux);
                j2++;
                strcpy(aux, "");
            }
            else
            {
                char temp[2] = {sir_creat1[j], '\0'};
                strcat(aux, temp);
            }
        }
        for (j = 0; j < (j2 - 1 - 1); j++)
        {
            strncpy(aux, vector_chey9[j] + 1, strlen(vector_chey9[j]) - 3);
            aux[strlen(vector_chey9[j]) - 3] = '\0';

            strncpy(aux2, vector_chey9[j + 1] + 1, strlen(vector_chey9[j + 1]) - 3);
            aux2[strlen(vector_chey9[j + 1]) - 3] = '\0';

            char *modifiedString2 = removeSubstring(aux, aux2);
            strcpy(aux3, modifiedString2);

            if (aux3[0] == '[' && aux3[strlen(aux3) - 1] == ']')
            {
                stergeSirPePozitie(vector_chey9, j + 1, j2);
            }
        }
        strcpy(aux, "");
        for (j = j2 - 2; j >= 0; j--)
        {
            strcat(aux, vector_chey9[j]);
        }
        strcat(aux, vector_chey9[j2 - 1]);

        strcpy(vector_chey7[i], aux);

        strcpy(aux, "");

        // cout << vector_chey7[i] << endl;

        char *modifiedString = eliminaDupaGhilimele(vector_chey7[i]);

        char *modifiedString2 = stergePrimaUltimaPozitie(modifiedString);

        strcpy(vector_chey7[i], modifiedString2);
    }

    cout << endl;
    for (i = 0; i < size_of_vector_chey5; i++)
    {
        cout << vector_chey7[i] << " " << vector_words5[i] << endl;
    }

    // char s2[256];
    // cout << "Input expression= " << endl;
    // cin.getline(s2,256);

    // cout << s2 << endl;

    // in max(max(a.b[0]))
    // mai intai facem toate inlocuirile dupa cand ajungem mereu la max depth facem calculul efectiv

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
