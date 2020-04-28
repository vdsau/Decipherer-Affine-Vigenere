#include"decipher.h"

bool Decipher::Check_Key(char* text,bool only_numbers)
 {
     bool res = true;
     size_t len = strlen(text);
     if(len > 0){
         for(int i = 0; i < len; i++)
         {
             if(!isdigit(text[i]))
             {
                 if(only_numbers)
                 {
                    res = false;
                    break;
                 }
                 else if(!isalpha(text[i]))
                 {
                     res = false;
                     break;
                 }
             }
        }
     }
     return res;
 }

bool Decipher::Check_Key_With_Predicate (bool (*predicate)(void* args),void* args)
{
    return predicate(args);
}

char* VDecipher::Decrypt(char* text)
{
    size_t cipher_length = strlen(text);
    if(cipher_length > 0 ){
       cipher_length++;
       char* res = new char[cipher_length];
       size_t key_len = strlen(key);
       int other_char_count = 0;
       for(int i = 0; i < cipher_length-1; i++)
       {
           if(isalpha(text[i]) || isdigit(text[i]))
           {
               bool upper_char = isupper(text[i]);
               char offset = (upper_char) ? 'A' : 'a';
               int key_index = ( i - other_char_count ) % key_len;
               int k = ((upper_char ? toupper(key[key_index]) : tolower(key[key_index])) - offset);
               res[i] = (char)((Mod((text[i]-k),alphabet_length))+offset);
           } 
           else
           {
               res[i] = text[i];
               ++other_char_count;
           } 
       }
       return res;
    } else return _EMPTY_STR_;
}

void ADecipher::FIll_Table()
{
    for(int i = 0; i < alphabet_length; i++)
    {
        int temp = (a_key.b+a_key.a*i); 
        if( temp > 25 )
        {
            int f = temp / alphabet_length;
            table[i+1] = alphabet[temp + 1 - 26 * f];
        } else 
            table[i+1] = alphabet[temp+1];  
    }
}

int ADecipher::mod_Inverse(int a, int b)
{
    int b0 = b,t,q;
    int x0=0,x1=1;
    if(b==1) return 1;
    while(a>1)
    {
        q = a/b;
        t = b, b = a% b, a=t;
        t = x0, x0= x1 -q *x0, x1 =t;
    }
    if(x1 < 0) x1 += b0;
    return x1;
}

char* ADecipher::Decrypt(char* text)
{
    size_t cipher_length = strlen(text);
    if(cipher_length>0){
       cipher_length++;
       char* res = new char[cipher_length];
       for(int i =0; i < cipher_length; i++)
       {
           if(isalpha(text[i]))
             res[i] = (char)(mod_Inverse(a_key.a,alphabet_length) * (alphabet_length + text[i]) - 'a' - a_key.b) % 26 +'a';
            else res[i] = text[i];
       }
        return res;
    }else return _EMPTY_STR_;
}