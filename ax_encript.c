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
    ax_encript_func_t func=ax_encript_func_tea;
    if (strcasecmp(name, "xor")==0) {
        func= ax_encript_func_xor;
    }else if(strcasecmp(name, "tea")==0){
        func= ax_encript_func_tea;
    }else if(strcasecmp(name, "xtea")==0){
        func= ax_encript_func_xtea;
    }else if(strcasecmp(name, "xxtea")==0){
        func= ax_encript_func_xxtea;
    }
    return func;
}
void ax_enc_func_to_name(ax_encript_func_t func,char *name,int namelen){
    char *funcname="";
    switch (func) {
        case ax_encript_func_xor:
            funcname="xor";
            break;
        case ax_encript_func_tea:
            funcname="tea";
            break;
        case ax_encript_func_xtea:
            funcname="xtea";
            break;
        case ax_encript_func_xxtea:
            funcname="xxtea";
            break;
        default:
            funcname="tea";
            break;
    }
    memcpy(name, funcname,ax_encript_min(strlen(funcname),namelen));
}
void ax_encript_xor_enc_dec(ax_encript_block_p in, ax_encript_block_p pwd, ax_encript_block_p out){
	*out = *in^*pwd;
}
void ax_encript_tea_enc(ax_encript_block_p in, ax_encript_block_p pwd, ax_encript_block_p out){
    uint32_t v[2];
    uint32_t k[4];
    memcpy(v, in, sizeof(*in));
    memcpy(k, pwd, sizeof(*pwd));
    memcpy(k+2, pwd, sizeof(*pwd));
    uint32_t v0=v[0], v1=v[1], sum=0, i;           /* set up */
    uint32_t delta=0x9e3779b9;                     /* a key schedule constant */
    uint32_t k0=k[0], k1=k[1], k2=k[2], k3=k[3];   /* cache key */
    for (i=0; i < 32; i++) {                       /* basic cycle start */
        sum += delta;
        v0 += ((v1<<4) + k0) ^ (v1 + sum) ^ ((v1>>5) + k1);
        v1 += ((v0<<4) + k2) ^ (v0 + sum) ^ ((v0>>5) + k3);
    }                                              /* end cycle */
    v[0]=v0; v[1]=v1;
    memcpy(out, v, sizeof(*out));
}
void ax_encript_tea_dec(ax_encript_block_p in, ax_encript_block_p pwd, ax_encript_block_p out){
    uint32_t v[2];
    uint32_t k[4];
    memcpy(v, in, sizeof(*in));
    memcpy(k, pwd, sizeof(*pwd));
    memcpy(k+2, pwd, sizeof(*pwd));
    uint32_t v0=v[0], v1=v[1], sum=0xC6EF3720, i;  /* set up */
    uint32_t delta=0x9e3779b9;                     /* a key schedule constant */
    uint32_t k0=k[0], k1=k[1], k2=k[2], k3=k[3];   /* cache key */
    for (i=0; i<32; i++) {                         /* basic cycle start */
        v1 -= ((v0<<4) + k2) ^ (v0 + sum) ^ ((v0>>5) + k3);
        v0 -= ((v1<<4) + k0) ^ (v1 + sum) ^ ((v1>>5) + k1);
        sum -= delta;
    }                                              /* end cycle */
    v[0]=v0; v[1]=v1;
    memcpy(out, v, sizeof(*out));
}

void ax_encript_xtea_enc(ax_encript_block_p in, ax_encript_block_p pwd, ax_encript_block_p out){
    uint32_t v[2];
    uint32_t key[4];
    memcpy(v, in, sizeof(*in));
    memcpy(key, pwd, sizeof(*pwd));
    memcpy(key+2, pwd, sizeof(*pwd));
    unsigned int num_rounds=7;
    unsigned int i;
    uint32_t v0=v[0], v1=v[1], sum=0, delta=0x9E3779B9;
    for (i=0; i < num_rounds; i++) {
        v0 += (((v1 << 4) ^ (v1 >> 5)) + v1) ^ (sum + key[sum & 3]);
        sum += delta;
        v1 += (((v0 << 4) ^ (v0 >> 5)) + v0) ^ (sum + key[(sum>>11) & 3]);
    }
    v[0]=v0; v[1]=v1;
    memcpy(out, v, sizeof(*out));
}
void ax_encript_xtea_dec(ax_encript_block_p in, ax_encript_block_p pwd, ax_encript_block_p out){
    uint32_t v[2];
    uint32_t key[4];
    memcpy(v, in, sizeof(*in));
    memcpy(key, pwd, sizeof(*pwd));
    memcpy(key+2, pwd, sizeof(*pwd));
    unsigned int num_rounds=7;
    unsigned int i;
    uint32_t v0=v[0], v1=v[1], delta=0x9E3779B9, sum=delta*num_rounds;
    for (i=0; i < num_rounds; i++) {
        v1 -= (((v0 << 4) ^ (v0 >> 5)) + v0) ^ (sum + key[(sum>>11) & 3]);
        sum -= delta;
        v0 -= (((v1 << 4) ^ (v1 >> 5)) + v1) ^ (sum + key[sum & 3]);
    }
    v[0]=v0; v[1]=v1;
    memcpy(out, v, sizeof(*out));
}

#define DELTA 0x9e3779b9
#define MX (((z>>5^y<<2) + (y>>3^z<<4)) ^ ((sum^y) + (key[(p&3)^e] ^ z)))
void ax_encript_xxtea_enc(ax_encript_block_p in, ax_encript_block_p pwd, ax_encript_block_p out){
    int n=2;
    uint32_t v[n];
    uint32_t key[4];
    memcpy(v, in, sizeof(*in));
    memcpy(key, pwd, sizeof(*pwd));
    memcpy(key+2, pwd, sizeof(*pwd));
    uint32_t y, z, sum;
    unsigned p, rounds, e;
    rounds = 6 + 52/n;
    sum = 0;
    z = v[n-1];
    do {
        sum += DELTA;
        e = (sum >> 2) & 3;
        for (p=0; p<n-1; p++) {
            y = v[p+1];
            z = v[p] += MX;
        }
        y = v[0];
        z = v[n-1] += MX;
    } while (--rounds);
    memcpy(out, v, sizeof(*out));
}
void ax_encript_xxtea_dec(ax_encript_block_p in, ax_encript_block_p pwd, ax_encript_block_p out){
    int n=2;
    uint32_t v[n];
    uint32_t key[4];
    memcpy(v, in, sizeof(*in));
    memcpy(key, pwd, sizeof(*pwd));
    memcpy(key+2, pwd, sizeof(*pwd));
    uint32_t y, z, sum;
    unsigned p, rounds, e;
    rounds = 6 + 52/n;
    sum = rounds*DELTA;
    y = v[0];
    do {
        e = (sum >> 2) & 3;
        for (p=n-1; p>0; p--) {
            z = v[p-1];
            y = v[p] -= MX;
        }
        z = v[n-1];
        y = v[0] -= MX;
    } while ((sum -= DELTA) != 0);
    memcpy(out, v, sizeof(*out));
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
            if(ax_encript_type_enc==type){
                ax_encript_xtea_enc(in,pwd,out);
            }else{
                ax_encript_xtea_dec(in,pwd,out);
            }
		}break;
		case ax_encript_func_xxtea:{
            if(ax_encript_type_enc==type){
                ax_encript_xxtea_enc(in,pwd,out);
            }else{
                ax_encript_xxtea_dec(in,pwd,out);
            }
		}break;
		case ax_encript_func_rc4:{

		}break;
	}
}
