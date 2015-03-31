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

typedef struct{
    char head;
    char data[128];
} ax_encript_block_t;
typedef ax_encript_block_t* ax_encript_block_p;
typedef enum{
    ax_encript_type_enc,
    ax_encript_type_dec
} ax_encript_type_t;

typedef void ax_encript_exec(ax_encript_block_p inblock,ax_encript_block_p outblock,ax_encript_type_t type);

typedef enum{
    ax_encript_func_xor
} ax_encript_func_t;

void ax_encript(ax_encript_block_p inblock,ax_encript_block_p outbock,ax_encript_type_t type,ax_encript_func_t func);
#endif /* defined(__SFBox__ax_encript__) */
