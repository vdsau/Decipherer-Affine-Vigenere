#include"classes.h"
#include<stdexcept>
#include<clocale>

extern _LOCAL_ERRORS_ l_err;
extern Algorithms cipher_algorithms;

int simple_numbers_check(long int a, long int b)
{
  return b == 0 ? a : simple_numbers_check(b, (a % b) );
}

bool simple_numbers(void* args)
{
  bool res = true;
  Affine_Keys* keys = (Affine_Keys*)args;
  if(keys->a < 0 || keys->b < 0)
   res = false;
  else if(simple_numbers_check(keys->a,keys->b) != 1 ) 
    res = false;
  return res;
}

void Prev_Check(int argc, char* argv[])
{
// 5 args for Vigenere cipher
// 6 args for Affine cipher, cause this cipher should have 2 keys ( a and b )
 if(argc < 5 || argc > 6) 
    throw invalid_argument(l_err.wrong_cmd_format);
 if(argc == 5)  // Vigenere with 1 key
    if(!Decipher::Check_Key(argv[4]) || argv[4] == NULL ) 
      throw invalid_argument(l_err.wrong_key_format);
 if(argc == 6) // Affine with 2 key
 {
   Affine_Keys keys = { atoi(argv[4]), atoi(argv[5]) };
   if(!Decipher::Check_Key_With_Predicate(simple_numbers,(void*)&keys))
      throw invalid_argument(l_err.wrong_key_format);
 }
  if(!Check_File(argv[1])) 
      throw invalid_argument(l_err.wrong_file_format);
}

void create_threads(Decipherer*& dc)
{
    Data_Chunk dt,dt1;

     dt.base = 0; //start position in file for 1st thread
     dt1.base = _BUFFER_SIZE_ - 1; //start position in file for 2nd thread

    dt.decipher = dt1.decipher = dc;

    Handler hd = { Handle_File, (void*)&dt };
    Handler hd1 = { Handle_File, (void*)&dt1 };

    pthread_t th1,th2;

    cout<<"Start deciphering.\nPlease,wait."<<endl;

    int err = pthread_create(&th1,NULL,hd.handler,hd.arg);
    if(err!=0) 
      throw runtime_error(l_err.new_thread_create);
      err = pthread_create(&th2,NULL,hd1.handler,hd1.arg);
     if(err!=0) 
       throw runtime_error(l_err.new_thread_create);

      pthread_join(th1,NULL);
      pthread_join(th2,NULL);
}

int main(int argc, char* argv[]){
    try{
      setlocale(LC_ALL,".1252"); //set ANSI code page
    
      Prev_Check(argc,argv);

      Decipherer* dc;

      if(strcmp(argv[3],cipher_algorithms.Vigenere)  == 0)
          dc = new Decipherer(new VDecipher(argv[4]));
       if(strcmp(argv[3],cipher_algorithms.Affine)  == 0)
          dc = new Decipherer(new ADecipher(argv[4],argv[5])); 
          
          setOutputFile(argv[2],ios::trunc | ios::out | ios::binary);
          setInputFile(argv[1], ios::binary | ios::in);
          
          create_threads(dc);

      callback(NULL);

      cout<<"Complete.File decripted."<<endl;
      cin.get();
    }
    catch(invalid_argument e)
    {
      cout<<e.what()<<endl;
      get_help();
    }
    catch(runtime_error e)
    {
      cout<<e.what()<<endl;
    }
    catch(...){
        cout<<"Unhandeled error. Exiting program."<<endl;
        exit(0);
    }
}