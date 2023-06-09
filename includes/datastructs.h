////////////////////////////////////////////////////////////////////////////////
/// \file datastructs.h
/// Name        : datastructs.h
/// Author      : Arcady Chechik
/// Created on	: Jun 9, 2008
/// Version     : 0.0.1
/// Copyright   : Your copyright notice
/// Description : This file contain basic RPC/IPC communication structures
////////////////////////////////////////////////////////////////////////////////

#ifndef	_DATASTRUCTS_
#define _DATASTRUCTS_


#ifndef WIN32
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <errno.h>
#include <signal.h>
#include <unistd.h>
#include <syscall.h>
#include <sys/socket.h>
#include <sys/sem.h>
#include <time.h>
#include <sys/time.h>
#include <pthread.h>
#include <semaphore.h>
#endif

#include "MMC_definitions.h"


#ifdef NULL
#undef NULL
	#define NULL 0
#endif



#define LINUX_ALIGNMENT
#define IPC_MSG_MAX_LENGTH					260
#ifdef _PLATINUM
#define IPC_MSG_IN_OUT_ARGS_MAX_SIZE 		1500//1000
#else
#define IPC_MSG_IN_OUT_ARGS_MAX_SIZE 		1000
#endif

#define	IPC_SOCKET_PATH						"/var/MMC/socket/fae-motion-srv"
#define	IPC_UDP_SOCKET_PATH					"/var/MMC/socket/fae-motion-udp-srv"
#define SHM_NAME1 							"/ipc_shm1_name"
#define IPC_MSG_S_SEM_NAME_LENGTH_SIZE		1
#define	IPC_SEM_NAME_MAX_LENGTH				80
#define	IPC_SEM_NAME_MIN_LENGTH				2
#define IPC_MSG_CONN_NUM_LENGTH				sizeof(int)
#define IPC_MIRR_PARAM_ADDR_LENGTH 			sizeof(unsigned int)
//
#define IPC_MSG_S_SEM_NAME_LENGTH_OFFSET 	0
#define IPC_MSG_S_SEM_NAME_OFFSET 			(IPC_MSG_S_SEM_NAME_LENGTH_OFFSET + IPC_MSG_S_SEM_NAME_LENGTH_SIZE)
#define IPC_MSG_C_SEM_NAME_LENGTH_OFFSET 	(IPC_MSG_S_SEM_NAME_OFFSET + IPC_SEM_NAME_MAX_LENGTH)
#define IPC_MSG_C_SEM_NAME_OFFSET 			(IPC_MSG_C_SEM_NAME_LENGTH_OFFSET + IPC_MSG_S_SEM_NAME_LENGTH_SIZE)
#define IPC_MSG_CONN_NUM_OFFSET				(IPC_MSG_C_SEM_NAME_OFFSET + IPC_SEM_NAME_MAX_LENGTH)
#define IPC_MSG_MIRR_PARAM_ADDR_OFFSET		(IPC_REG_AXES_NUM_OFFSET + IPC_REG_AXES_NUM_LENGTH)

#define	MMC_REMOTE_FUNC_MOTION_FUNC_MAX_INDEX 				20

#define IPC_MSG_FUNC_CODE_ID_OPEN_UDP_RESPONSE_CHANNEL		102
#define IPC_MSG_FUNC_CODE_ID_CLOSE_UDP_RESPONSE_CHANNEL		103
#define IPC_MSG_FUNC_CODE_ID_CLOSE_IPC_CHANNEL				104

#define MMC_MAX_CONNECTION_NUMBER 							20

#define SEND_GET_SYNC_TIMEOUTms								3000

#define MMC_MAX_NUM_AXIS									127

///////////////////////////////////////////////////////////////////////////////
// NC driver - IOCTLs
///////////////////////////////////////////////////////////////////////////////

// Use 'k' as magic number
#define NC_DRV_IOC_MAGIC  'k'

#define NC_IOCBEGINRECORDING    			_IO(NC_DRV_IOC_MAGIC, 	0)
#define NC_IOCSTOPRECORDING    				_IO(NC_DRV_IOC_MAGIC, 	1)
#define NC_IOCDEBUG             			_IO(NC_DRV_IOC_MAGIC, 	2)
#define NC_IOCSTARTHRTIMER      			_IOW(NC_DRV_IOC_MAGIC, 	3, unsigned int)
#define NC_IOCSTOPHRTIMER      				_IO(NC_DRV_IOC_MAGIC, 	4)
#define NC_IOCREGNCTASK						_IOW(NC_DRV_IOC_MAGIC, 	5, unsigned char)
#define NC_IOCUNREGNCTASK					_IO(NC_DRV_IOC_MAGIC, 	6)
#define NC_IOCPOWERENABLE       			_IOW(NC_DRV_IOC_MAGIC, 	7, unsigned int)
#define NC_IOCPOWERENABLEDBG				_IOW(NC_DRV_IOC_MAGIC, 	8, unsigned int)
#define NC_IOCSINTABLEINIT					_IOW(NC_DRV_IOC_MAGIC, 	9, unsigned int)
#define NC_IOCMMINIT						_IOW(NC_DRV_IOC_MAGIC, 	10, unsigned int)
#define NC_IOCGETTRFUNC						_IOWR(NC_DRV_IOC_MAGIC, 11, unsigned int)
#define NC_IOCGETCANCOMMEVENTS				_IOW(NC_DRV_IOC_MAGIC, 	12, unsigned int)
#define NC_IOCSETSYNCTIME					_IOW(NC_DRV_IOC_MAGIC, 	13, unsigned short)
#define NC_IOCSETHEARTBEATTIMEFACTOR		_IOW(NC_DRV_IOC_MAGIC, 	14, unsigned int)
#ifdef _PRM_SNAPSHOT_
#define NC_IOCGETPARAMMIRRORADDR			_IOW(NC_DRV_IOC_MAGIC, 	15, unsigned int)
#endif
#define NC_IOCSETGPIO						_IOW(NC_DRV_IOC_MAGIC, 	16, unsigned char)
#define NC_IOCCLEARGPIO						_IOW(NC_DRV_IOC_MAGIC, 	17, unsigned char)
#define NC_IOCSYNCTIMER						_IOW(NC_DRV_IOC_MAGIC, 	18, unsigned short)
#define NC_IOCSYNCTIMERSTARTSTOP			_IOW(NC_DRV_IOC_MAGIC, 	19, unsigned char)
#define NC_IOCCOMMCONFIGMODEENABLE			_IO(NC_DRV_IOC_MAGIC, 	20)
#define NC_IOCCOMMCONFIGMODEDISABLE			_IO(NC_DRV_IOC_MAGIC, 	21)

///////////////////////////////////////////////////////////////////////////////
/// \struct MOTION_FUNCS_INNER_ARGS
/// \brief Command common data
///////////////////////////////////////////////////////////////////////////////
typedef struct motion_funcs_inner_args
{
	unsigned int uiConnIndex;			///< Connection index
	void *pAxisRef;						///< Pointer to Axis data structure
	unsigned short usNumerator;			///< Command enumerator
	unsigned short usOutputDataSize;	///< Size of output data
	unsigned short usFuncID;			///< Command function ID
	unsigned char ucConnType;			///< Connection type (IPC/RPC)
	unsigned char dummy; 				///< added for whole 16-byte size
}MOTION_FUNCS_INNER_ARGS;

///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_IPC_BASIC_IN_STRUCT
/// \brief Basic common IPC/RPC command header
///////////////////////////////////////////////////////////////////////////////
typedef struct basic_input
{
	unsigned short func_code_id;	///< Function ID code
	unsigned short numerator_id;	///< Command enumerator
	unsigned short data_size;		///< Command data size
	unsigned short axis_ref;		///< Handle of command related axis.
}LINUX_ALIGNMENT MMC_IPC_BASIC_IN_STRUCT;



///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_IPC_SHM_IN_STRUCT
/// \brief IPC host to target transaction data structure
///
///	This structure defines host to target shared memory transaction	for IPC.
///////////////////////////////////////////////////////////////////////////////
typedef struct shared_memory_region1
{
	MMC_IPC_BASIC_IN_STRUCT	basic_in ;
#ifndef WIN32
	MOTION_FUNCS_INNER_ARGS inner_args;
	unsigned char  in_param[IPC_MSG_IN_OUT_ARGS_MAX_SIZE];
#else
	unsigned char  in_param[IPC_MSG_IN_OUT_ARGS_MAX_SIZE];
	MOTION_FUNCS_INNER_ARGS inner_args;
#endif
}LINUX_ALIGNMENT MMC_IPC_SHM_IN_STRUCT;

///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_IPC_SHM_OUT_STRUCT
/// \brief IPC target to host transaction data structure
///////////////////////////////////////////////////////////////////////////////
typedef struct shared_memory_out_region1
{
	unsigned short numerator_id;
	unsigned short data_size;
	unsigned short dummy[2];
#ifndef WIN32
	MOTION_FUNCS_INNER_ARGS inner_args;							// why is this here ? Benji !!!!
	unsigned char  out_param[IPC_MSG_IN_OUT_ARGS_MAX_SIZE];
#else
	unsigned char  out_param[IPC_MSG_IN_OUT_ARGS_MAX_SIZE];
	MOTION_FUNCS_INNER_ARGS inner_args;
#endif
}LINUX_ALIGNMENT MMC_IPC_SHM_OUT_STRUCT;

///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_RESP_HEADER_STRUCT
/// \brief Common responce data structure
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
	unsigned short usStatus;		///< Returned command status.
	short usErrorID;		///< Returned command error ID.
}LINUX_ALIGNMENT MMC_RESP_HEADER_STRUCT;

#define MAX_UDP_FIFO_SIZE	16
#define MX_UDP_FIFO_MSG_SIZE sizeof(MMC_CAN_REPLY_DATA_OUT)

typedef struct {
	int	iUDPFIFOSize ;
	int iLen;
	unsigned char ucData[MX_UDP_FIFO_MSG_SIZE];
	unsigned short usCanId;
#ifndef WIN32
	sem_t synchronised_communication_event;
#else
	void *synchronised_communication_event ;
#endif
} LINUX_ALIGNMENT MMC_UDP_DATA_FIFO_STRUCT;

///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_IF_STRUCT
/// \brief Connection interface data structure
///////////////////////////////////////////////////////////////////////////////

#ifndef WIN32

typedef struct
	{
		unsigned int magic;
		MMC_CONNECTION_TYPE conn_type;
		MMC_CONNECTION_PARAM_STRUCT conn_param;
		int	sock;
		int shm_fd;
		unsigned char * ipc_shm_addr;
		int ipc_server_semid;
		int ipc_client_semid;
		int ipc_conn_num;
		unsigned int msg_numerator;
		void* snd_msg;
		pthread_mutex_t snd_msg_mutex;
		pthread_mutexattr_t snd_msg_mutex_attr;
		unsigned int sockListen ;
		//MMC_CB_FUNC pCbFunc ;MB support to MMCPP library. @YL 27-06-2011
		MMC_MB_CLBK pCbFunc ;
		MMC_MB_CLBK pCbFuncSecondary ; // @ZB
		int hTerminateEvent ;
		pthread_attr_t hConnectThreadAttr;
		pthread_t hConnectThread;
		int		udpport ;
		int iActiveAxesNum;
		MMC_UDP_DATA_FIFO_STRUCT* stUDPDataFIFO[MMC_MAX_NUM_AXIS] ;
		char cLastError[512] ;
		pthread_mutex_t lpCriticalSectionUDP;
		pthread_mutexattr_t lpCriticalSectionUDPAttr;
		int db_shm_fd;
		unsigned char * ipc_db_shm_addr;
		unsigned char* shm_ptr;
		unsigned char ucIsSYNCTimerActive;
		unsigned char ucSYNCTimerExit;
		int nc_drv_fd;
		unsigned char ucSendAsyncEventFlag ;
		unsigned char ucDeviceType;
	} LINUX_ALIGNMENT MMC_IF_STRUCT;
#else

typedef struct mmc_if_struct
	{
		unsigned int magic;
		MMC_CONNECTION_TYPE conn_type;
		MMC_CONNECTION_PARAM_STRUCT conn_param;
		int	sock;
		int shm_fd;
		double dData[190] ;
		// unsigned char * ipc_shm_addr;
		unsigned int blocksock ;
		unsigned int sockListen ;
		unsigned long tID ;
		int		udpport ;
		void *hConnectThread ;
		void *hTerminateEvent ;
		//void *synchronised_communication_event ;
		int iActiveAxesNum;
		MMC_UDP_DATA_FIFO_STRUCT* stUDPDataFIFO[MMC_MAX_NUM_AXIS] ;
		CRITICAL_SECTION lpCriticalSectionUDP ;
		CRITICAL_SECTION lpCriticalSectionSendRcv ;
		MMC_CB_FUNC pCbFunc ;
		int ipc_conn_num;
		unsigned int msg_numerator;
		void* snd_msg;
		char cLastError[512] ;
		unsigned char ucSendAsyncEventFlag ;
		unsigned char ucDeviceType;
	} LINUX_ALIGNMENT MMC_IF_STRUCT;

#endif


///////////////////////////////////////////////////////////////////////////////
/// \typedef MMC_SND_MSG_FUNC
/// \brief 	IPC/RPC send function prototype.
///////////////////////////////////////////////////////////////////////////////
typedef int (*MMC_SND_MSG_FUNC)(
						IN MMC_IF_STRUCT* pMmcIf,
						IN MMC_AXIS_REF_HNDL hAxisRef,
						IN int iFuncId,
						IN void* pInParam,
						IN short iInSize,
						IN short iOutSize,
						OUT void* pOutParam);



#endif
