//
//  ax_encript.c
//  SFBox
//
//  Created by 彭运筹 on 15/3/31.
//  Copyright (c) 2015年 彭运筹. All rights reserved.
//

#include "ax_encript.h"

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
