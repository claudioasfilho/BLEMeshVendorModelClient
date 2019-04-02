/*************************************************************************
    > File Name: vm_def.h
    > Author: Kevin
    > Created Time: 2018-09-16
    >Description: 
 ************************************************************************/

#ifndef VM_DEF_H
#define VM_DEF_H

#define VENDOR_ID				0x1111
#define SERVER_MODEL_ID			0x1111
#define CLIENT_MODEL_ID			0x2222

#define NUM_OPCODES				4

typedef enum {
	pub_addr_get = 0x1,
	pub_addr_st,
	user_name,
	congrat
}opcodes_t;


#endif
