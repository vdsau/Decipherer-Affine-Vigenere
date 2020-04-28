#include"classes.h"

 pthread_mutex_t que_mutex = PTHREAD_MUTEX_INITIALIZER; //sync for queue
 pthread_mutex_t file_mutex = PTHREAD_MUTEX_INITIALIZER; //sync file access

void setOutputFile(const char* filename,ios::openmode mode){
    output = ofstream(filename,mode);
}
void setInputFile(const char* filename,ios::openmode mode){
    input = ifstream(filename,mode);
}

void get_help()
{
    ifstream in("help.txt", ios::in | ios::binary);
      if(!in) throw runtime_error(l_err.read_file);
      char c;
      while(in.get(c)) 
        cout<<c;
      in.close(); 
}

size_t get_file_size(const char* filename)
{
   ifstream in(filename,ios::binary | ios::in | ios::ate);
   if(!in)  throw invalid_argument(l_err.read_file);
   return (size_t)in.tellg();
}
void Fill_output()
{
  while(!global_buffer.empty())
  {
      output<<global_buffer.front();
      global_buffer.pop();
  }
}

void callback(void* data){ 
    Fill_output();
    input.close();
    output.close();
  }

void Write_To_Queue(char* text)
{
  pthread_mutex_lock(&que_mutex);
  global_buffer.push(text);
  pthread_mutex_unlock(&que_mutex);
}

void* Handle_File(void* data)
{
  pthread_t id = pthread_self();
  Data_Chunk* fp = (Data_Chunk*)data;
  size_t temp = fp->base;
  int mtx = 0;
   while(!input.eof()){
     pthread_mutex_lock(&file_mutex);
     input.seekg(temp,ios::beg);
     input.read(fp->buffer,_BUFFER_SIZE_ - 1); //read 2048 bytes from file
     pthread_mutex_unlock(&file_mutex);
     sleep(1);
     temp = fp->base +(_BUFFER_SIZE_-1); 
     fp->base = temp * 2;
     strcpy(fp->buffer, fp->decipher->Decrypt(fp->buffer));
    Write_To_Queue(fp->buffer);
    sleep(1);
  }
  pthread_exit((void*)0);
}

bool Check_File(const char* filename)
{
  ifstream in(filename,ios::binary | ios::in);  
  if(!in) throw runtime_error(l_err.read_file);
  if(!in.is_open()) throw runtime_error(l_err.closed_file);
  bool res = true;
  char c;
  while(in.get(c)) 
  {
    if( !isalpha(c) || !islower(c) )
    {
      res = false;
      break;
    }
  }
  return res;
}