#ifndef _CLASSES_H_
#define _CLASSES_H_

#include<iostream>
#include<pthread.h>
#include<unistd.h>
#include<fstream>
#include"decipher.h"
#include<queue>

using namespace std;

struct Data_Chunk
{
    size_t base;
    char buffer[_BUFFER_SIZE_];
    Decipherer* decipher;
    pthread_mutex_t* file_mutex;
    pthread_mutex_t* que_mutex;
};

static queue<char*> global_buffer;

static ofstream output;
static ifstream input;

void setOutputFile(const char* ,ios::openmode );
void setInputFile(const char* ,ios::openmode);
void get_help();
bool Check_File(const char*);
void* Handle_File(void* data);
void Fill_output();
void callback(void*);

struct _LOCAL_ERRORS_
{
   const char* read_file = "Error reading file";
   const char* write_file = "Error writing to the file";
   const char* wrong_key_format = "Wrong key format";
   const char* wrong_cmd_format = "Wrong command syntax";
   const char* wrong_file_format = "Wrong file format";
   const char* closed_file = "File is closed";
   const char* new_thread_create = "Cannot create new thread";
   const char* thread_join = "Cannot join thread";
};

static _LOCAL_ERRORS_ l_err;

 template<class T>struct _Handler
    {
         T (*handler)(void*);
         void* arg;
    };
    typedef _Handler<void*> Handler;
#endif