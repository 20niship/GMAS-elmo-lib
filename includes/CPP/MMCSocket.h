/*
 * MMCSocket.h
 *
 *  Created on: 25/12/2012
 *      Author: yuvall
 */

#ifndef MMCSOCKET_H_
#define MMCSOCKET_H_

#include "MMCPPGlobal.h"


#define MMCPP_RETERROR	1
#define MMCPP_RETOK	0
#define MMCPP_INVSOCKET -1
#define MMCPP_SOCKERROR	-1

#define MMCPP_SOCK_INFINIT_BLOCK -1
#define MMCPP_SOCK_EOE_RETRIES	3
#define MMCPP_SOCK_NEW_EVENT 10
#define MMCPP_SOCK_READY_EVENT 11
#define MMCPP_SOCK_CLOSED_EVENT 12
#define MMCPP_SOCK_ABORT_EVENT 13
#define MMCPP_SOCK_MAXLIM_EVENT 14

#ifdef __cplusplus
extern "C" {
#endif
typedef int (*SOCK_CLBK)(int, short, unsigned char*, int, ...);
#ifdef __cplusplus
}
#endif

#endif /* MMCSOCKET_H_ */
