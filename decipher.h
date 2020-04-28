#ifndef _DECIPHER_H
#define _DECIPHER_H

#include<stdio.h>
#include<stdlib.h>
#include<cctype>
#include<string.h>

#include<iostream>

using namespace std;

#define _EMPTY_STR_ (char*)""
#define _BUFFER_SIZE_ 2049

struct Algorithms
{
    const char* Vigenere = "vig";
    const char* Affine = "aff";
};

static Algorithms cipher_algorithms;

struct Affine_Keys
    {
      long int a;
      long int b;
    };

class Decipher  //base class of decipher algorithms
{
    protected:
    const char* alphabet = "abcdefghijklmnopqrstuvwxyz"; 
    size_t alphabet_length;
    char* key;
    public:
    Decipher(const Decipher& dc):key(dc.key),alphabet_length(strlen(alphabet)){}
    Decipher& operator=(const Decipher& dc)
    {
        key = dc.key;
        alphabet_length = strlen(alphabet);
        
    }
    Decipher():alphabet_length(strlen(alphabet)){}
    Decipher(char *key):key(key),alphabet_length(strlen(alphabet)) {}
    static bool Check_Key(char*, bool only_numbers = false); // check text for nondigit or nonalpha characters
    static bool Check_Key_With_Predicate (bool (*predicate)(void* args) = NULL,void* args = NULL);
    virtual char* Decrypt(char*) = 0;
    virtual ~Decipher(){
        delete alphabet;
        delete key;
    };
};

class Decipherer
{
    Decipher* dc;
    public:
    Decipherer(Decipher* algorithm):dc(algorithm){ }
   char* Decrypt(char* text)
   {
        return dc->Decrypt(text);
    }
    ~Decipherer()
    {
        delete dc;
    }
};

class VDecipher : public Decipher
{
    //  Vigenere cipher
    static int Mod(int a,int b)
    {
        return (a%b+b)%b;
    }
    public:
    VDecipher(char* key) : Decipher(key){}
    char* Decrypt(char* text);
    char* c(){
      return (char*)"LOL";
    }
    ~VDecipher() {}
};

class ADecipher : public Decipher
{
    // Affine cipher
    Affine_Keys a_key;
    char table[27];
    int mod_Inverse(int a, int b);
    protected:
    void FIll_Table();
    public:
    ADecipher(char* a, char* b){
            a_key.a = atoi(a);
            a_key.b = atoi(b);
    }
    char* Decrypt(char* text);
     ~ADecipher(){}
};

#endif