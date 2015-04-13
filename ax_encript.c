//
//  ax_encript.c
//  SFBox
//
//  Created by 彭运筹 on 15/3/31.
//  Copyright (c) 2015年 彭运筹. All rights reserved.
//

#include "ax_encript.h"
#include <string.h>
#define ax_encript_min(a,b) (a)>(b)?(b):(a)
ax_encript_func_t ax_enc_func_name_to_value(char *name){
    if (strcasecmp(name, "xor")==0) {
        return ax_encript_func_xor;
    }
    return ax_encript_func_xor;
}
void ax_enc_func_to_name(ax_encript_func_t func,char *name,int namelen){
    char *funcname="";
    switch (func) {
        case ax_encript_func_xor:
            funcname="xor";
            break;
            
        default:
            funcname="unknow";
            break;
    }
    memcpy(name, funcname,ax_encript_min(strlen(funcname),namelen));
}
void ax_encript_xor_enc_dec(ax_encript_block_p in, ax_encript_block_p pwd, ax_encript_block_p out){
	*out = *in^*pwd;
}
void ax_encript_tea_enc(ax_encript_block_p in, ax_encript_block_p pwd, ax_encript_block_p out){

}
void ax_encript_tea_dec(ax_encript_block_p in, ax_encript_block_p pwd, ax_encript_block_p out){

}
void ax_encript_do(ax_encript_block_p in, ax_encript_block_p pwd, ax_encript_block_p out, ax_encript_type_t type,ax_encript_func_t func){
	switch(func){
		case ax_encript_func_xor:{
			ax_encript_xor_enc_dec(in,pwd,out);
		}break;
		case ax_encript_func_tea:{
			if(ax_encript_type_enc==type){
				ax_encript_tea_enc(in,pwd,out);
			}else{
				ax_encript_tea_dec(in,pwd,out);
			}
		}break;
		case ax_encript_func_xtea:{

		}break;
		case ax_encript_func_xxtea:{

		}break;
		case ax_encript_func_rc4:{

		}break;
	}
}
