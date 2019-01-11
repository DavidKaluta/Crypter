//
//  main.c
//  idk20190111
//
//  Created by David Kaluta on 11/01/2019.
//  Copyright © 2019 David Kaluta.
//  Permission is hereby granted, free of charge, to any person obtaining a copy
//  of this software and associated documentation files (the "Software"), to deal
//  in the Software without restriction, including without limitation the rights
//  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//  copies of the Software, and to permit persons to whom the Software is
//  furnished to do so, subject to the following conditions:
//
//  The above copyright notice and this permission notice shall be included in all
//  copies or substantial portions of the Software.
//
//
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
//  SOFTWARE.

#include <stdio.h>
#include <stdlib.h>
#include "Header.h"

int main(int argc, const char * argv[]) {
    // insert code here...
    printf("Do you want to *E*ncrypt or *D*ecrypt? ");
    char action = getchar();
    char * s = malloc(sizeof(s));
    char * newS;
    int keyNumber = -1;
    int * knptr = &keyNumber;
    int * key = malloc(sizeof(key));
    int i = 0;
    switch (action) {
        case 'e':
        case 'E':
            printf("Input a string: ");
            scanf("%s", s);
            while (s[i] != 0) {
                printf("Input a number: ");
                scanf("%d", knptr);
                key[i++] = keyNumber;
            }
            newS = Encrypt(s, key);
            printf("%s\n", newS);
            free(newS);
            break;
        case 'd':
        case 'D':
            printf("Input a string: ");
            scanf("%s", s);
            while (s[i] != 0) {
                printf("Input a number: ");
                scanf("%d", knptr);
                key[i++] = keyNumber;
            }
            newS = Decrypt(s, key);
            printf("%s\n", newS);
            free(newS);
            break;
        default:
            printf("Invalid choice.\n");
            break;
    }
    free(s);
    free(key);
    return 0;
}

char * Encrypt(char * s, int * key) {
    char * newS = malloc(sizeof(newS));
    char ch;
    int chAsInt;
    int i = 0;
    do {
        ch = s[i];
        if(s[i] != 0) {
            if(ch >= 'A' && ch <= 'Z'){
                ch -= 'A';
                chAsInt = (int) ch;
                chAsInt += key[i];
                chAsInt%=26;
                ch = (char) chAsInt;
                ch += 'A';
            } else if(ch >= 'a' && ch <= 'z') {
                ch -= 'a';
                chAsInt = (int) ch;
                chAsInt += key[i];
                chAsInt%=26;
                ch = (char) chAsInt;
                ch += 'a';
            } else if(ch >= '0' && ch <= '9') {
                ch -= '0';
                chAsInt = (int) ch;
                chAsInt += key[i];
                chAsInt%=10;
                ch = (char) chAsInt;
                ch += 'a';
            }
        }
        newS[i++] = ch;
    } while (s[i] != 0);
    return newS;
}

char * Decrypt(char * s, int * key) {
    char * newS = malloc(sizeof(newS));
    char ch;
    int chAsInt;
    int i = 0;
    do {
        ch = s[i];
        if(s[i] != 0) {
            if(ch >= 'A' && ch <= 'Z'){
                ch -= 'A';
                chAsInt = (int) ch;
                chAsInt -= key[i];
                chAsInt%=26;
                ch = (char) chAsInt;
                ch += 'A';
            } else if(ch >= 'a' && ch <= 'z') {
                ch -= 'a';
                chAsInt = (int) ch;
                chAsInt -= key[i];
                chAsInt%=26;
                ch = (char) chAsInt;
                ch += 'a';
            } else if(ch >= '0' && ch <= '9') {
                ch -= '0';
                chAsInt = (int) ch;
                chAsInt -= key[i];
                chAsInt%=10;
                ch = (char) chAsInt;
                ch += 'a';
            }
        }
        newS[i++] = ch;
    } while (s[i] != 0);
    return newS;
}
