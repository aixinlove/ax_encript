//
//  ax_encript.c
//  SFBox
//
//  Created by 彭运筹 on 15/3/31.
//  Copyright (c) 2015年 彭运筹. All rights reserved.
//

#include "ax_encript.h"
typedef struct{
    char data[64];
} ax_encript_block_t;
typedef ax_encript_block_t* ax_encript_block_p;

typedef void ax_encript_block_exec(ax_encript_block_p inblock,ax_encript_block_p outblock,ax_encript_type_t type);

void ax_encript_block_xor(ax_encript_block_p inblock,ax_encript_block_p outblock,ax_encript_type_t type){
    if (type==ax_encript_type_enc) {
        
    }else{
        
    }
}
void ax_encript_block_tea(ax_encript_block_p inblock,ax_encript_block_p outblock,ax_encript_type_t type){
    if (type==ax_encript_type_enc) {
        
    }else{
        
    }
}
void ax_encript_block_xtea(ax_encript_block_p inblock,ax_encript_block_p outblock,ax_encript_type_t type){
    if (type==ax_encript_type_enc) {
        
    }else{
        
    }
}
void ax_encript_block_xxtea(ax_encript_block_p inblock,ax_encript_block_p outblock,ax_encript_type_t type){
    if (type==ax_encript_type_enc) {
        
    }else{
        
    }
}
void ax_encript_block_rc4(ax_encript_block_p inblock,ax_encript_block_p outblock,ax_encript_type_t type){
    if (type==ax_encript_type_enc) {
        
    }else{
        
    }
}
void ax_encript_block(ax_encript_block_p inblock,ax_encript_block_p outbock,ax_encript_type_t type,ax_encript_func_t func){
    
}
void ax_encript_stream(char *indata,int inlen,char *outdata,int outlen,ax_encript_type_t type,ax_encript_func_t func, void* ud){
	
}