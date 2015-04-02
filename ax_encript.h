//
//  ax_encript.h
//  SFBox
//
//  Created by 彭运筹 on 15/3/31.
//  Copyright (c) 2015年 彭运筹. All rights reserved.
//

#ifndef __SFBox__ax_encript__
#define __SFBox__ax_encript__

#include <stdio.h>
#include <stdint.h>
typedef enum{
    ax_encript_type_enc,
    ax_encript_type_dec
} ax_encript_type_t;
typedef enum{
    ax_encript_func_xor=0x0001,
	ax_encript_func_tea=0x0002,
	ax_encript_func_xtea=0x0003,
	ax_encript_func_xxtea=0x0004,
	ax_encript_func_rc4=0x0005,
} ax_encript_func_t;
typedef int64_t ax_encript_block_t;
typedef ax_encript_block_t* ax_encript_block_p;
void ax_encript_do(ax_encript_block_p in, ax_encript_block_p pwd, ax_encript_block_p out, ax_encript_type_t type,ax_encript_func_t func);
#endif /* defined(__SFBox__ax_encript__) */
