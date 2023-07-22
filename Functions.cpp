#include "Functions.h"


char* mygets(char*& str, size_t& LMax, FILE* in) {

    int begin = 0;
    if (!str)
        str = new char[LMax];
    while (fgets(str + begin, LMax - begin, in)) { //  terminates reading if a newline
        begin = LMax - 1;
        if (strchr(str, '\n'))
            break;
        LMax *= 2;
        char* buf = new char[LMax];
        strcpy(buf, str);
        delete[] str;
        str = buf;
    }
    if (begin == 0) {
        delete[] str;
        return NULL;
    }
    return str;
}


int get_int(char* s, int& x) {

    int position;
    if (sscanf(s, "%d%n", &x, &position) == 1)
        return position;
    if (sscanf(s, "%s", s) == 1)
        return -1;

    return 0;
}


int get_word(char* s, char*& str) {

    int pos;
    if (sscanf(s, "%s%n", str, &pos) == 1)
        return pos;
    if (sscanf(s, "%s", s) == 1)
        return -1;

    return 0;
}