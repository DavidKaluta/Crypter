//
//  main.c
//  Crypter
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
#include <time.h>
#include <string.h>
#include "Header.h"

int main(int argc, const char * argv[]) {
    char * s;
    if(argc == 4) {
        if(strcmp(argv[1], "-e") == 0 || strcmp(argv[1], "-E") == 0) {
            s = Encrypt(argv[2], argv[3]);
            if(s != NULL) {
                printf("%s\n", s);
                free(s);
            } 
            else {
                printf("ERROR! - Invalid key. Letters only.\n");
                return 1;
            }
        } 
        else if(strcmp(argv[1], "-d") == 0 || strcmp(argv[1], "-D") == 0) {
            s = Decrypt(argv[2], argv[3]);
            if(s != NULL) {
                printf("%s\n", s);
                free(s);
            } 
            else {
                printf("ERROR! - Invalid key. Letters only.\n");
                return 1;
            }
        } 
        else {
            printf("USAGE: crypter [[-e]/[-d] \"Text\" \"Key\"]\n");
            return 2;
        }
    } 
    else if(argc == 3) {
        if(strcmp(argv[1],"-e") == 0 || strcmp(argv[1],"-E") == 0) {
            srand((unsigned int) time(NULL));
            int i = 0;
            char * key = malloc(sizeof(key));
            if(key == NULL) {
            	printf("ERROR! - Out of memory. \n");
            	return 3;
            }
            do {
                if(argv[2][i] == 0)
                    key[i] = 0;
                else
                    key[i++] = rand()%26 + 'a';
            } while (argv[2][i] != 0);
            s = Encrypt(argv[2], key);
            if(s != NULL) {
                printf("%s\n", s);
                free(s);
                printf("The key is %s\n", key);
            } 
            else {
                printf("ERROR! - Invalid key. Letters only.\n");
                return 1;
            }
            free(key);
        } 
        else {
            printf("ERROR! - Invalid key. Letters only.\n");
            return 1;
        }
    } 
    else {
        printf("USAGE: crypter [[-e]/[-d] \"Text\" \"Key\"]\n");
        return 2;
    }
    return 0;
}

char * Encrypt(const char * s,const char * key) {
    char * newS = malloc(sizeof(newS));
    if(newS == NULL)
    	return "ERROR! - Out of memory. \n";
    char ch;
    int chAsInt;
    int i = 0;
    do {
        ch = s[i];
        if(s[i] != 0) {
            if(ch >= 'A' && ch <= 'Z'){
                ch -= 'A';
                chAsInt = (int) ch;
                if(key[i] >= 'A' && key[i] <= 'Z')
                    chAsInt += key[i] - 64;
                else if(key[i] >= 'a' && key[i] <= 'z')
                    chAsInt += key[i] - 96;
                else {
                    free(newS);
                    return NULL;
                }
                chAsInt%=26;
                ch = (char) chAsInt;
                ch += 'A';
            } 
            else if(ch >= 'a' && ch <= 'z') {
                ch -= 'a';
                chAsInt = (int) ch;
                if(key[i] >= 'A' && key[i] <= 'Z')
                    chAsInt += key[i] - 64;
                else if(key[i] >= 'a' && key[i] <= 'z')
                    chAsInt += key[i] - 96;
                else {
                    free(newS);
                    return NULL;
                }
                chAsInt%=26;
                ch = (char) chAsInt;
                ch += 'a';
            } 
            else if(ch >= '0' && ch <= '9') {
                ch -= '0';
                chAsInt = (int) ch;
                if(key[i] >= 'A' && key[i] <= 'Z')
                    chAsInt += key[i] - 64;
                else if(key[i] >= 'a' && key[i] <= 'z')
                    chAsInt += key[i] - 96;
                else {
                    free(newS);
                    return NULL;
                }
                chAsInt%=10;
                ch = (char) chAsInt;
                ch += 'a';
            }
        }
        newS[i++] = ch;
    } while (s[i] != 0);
    return newS;
}

char * Decrypt(const char * s, const char * key) {
    char * newS = malloc(sizeof(newS));
    if(newS == NULL)
    	return "ERROR! - Out of memory. \n";
    char ch;
    int chAsInt;
    int i = 0;
    do {
        ch = s[i];
        if(s[i] != 0) {
            if(ch >= 'A' && ch <= 'Z'){
                ch -= 'A';
                chAsInt = (int) ch;
                if(key[i] >= 'A' && key[i] <= 'Z')
                    chAsInt -= key[i] - 64;
                else if(key[i] >= 'a' && key[i] <= 'z')
                    chAsInt -= key[i] - 96;
                else {
                    free(newS);
                    return NULL;
                }
                if(chAsInt < 0)
                    chAsInt += 26;
                chAsInt%=26;
                ch = (char) chAsInt;
                ch += 'A';
            } 
            else if(ch >= 'a' && ch <= 'z') {
                ch -= 'a';
                chAsInt = (int) ch;
                if(key[i] >= 'A' && key[i] <= 'Z')
                    chAsInt -= key[i] - 64;
                else if(key[i] >= 'a' && key[i] <= 'z')
                    chAsInt -= key[i] - 96;
                else {
                    free(newS);
                    return NULL;
                }
                if(chAsInt < 0)
                    chAsInt+=26;
                chAsInt%=26;
                ch = (char) chAsInt;
                ch += 'a';
            } 
            else if(ch >= '0' && ch <= '9') {
                ch -= '0';
                chAsInt = (int) ch;
                if(key[i] >= 'A' && key[i] <= 'Z')
                    chAsInt -= key[i] - 64;
                else if(key[i] >= 'a' && key[i] <= 'z')
                    chAsInt -= key[i] - 96;
                else {
                    free(newS);
                    return NULL;
                }
                if(chAsInt < 0)
                    chAsInt += 10;
                chAsInt%=10;
                ch = (char) chAsInt;
                ch += 'a';
            }
        }
        newS[i++] = ch;
    } while (s[i] != 0);
    return newS;
}
