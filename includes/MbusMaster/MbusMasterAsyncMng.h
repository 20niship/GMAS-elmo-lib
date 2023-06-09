/*
============================================================================
 Name : MbusMasterAsyncMng.h
 Author : Haim Hillel
 Version : 23Dec2013

 Description : GMAS C/C++ project header file
	This Class provide Mbus Asynchronous services.
	The services base on Focus FieldTalk Modbus Master C++ Library, ver 2.4.1.
	This Class is wrapper above Focus services provide asynchronous call.
	In this header file is the manage (Mng) section of the header file.
	
			ALL API HAVE SYNC/ASYNC PARAM AT END OF PARM LIST
			THIS PARAM CAN BE MISSING IN CALLING, THE DEFAULT
			(IN CASE IS MISSING) IS ASYNC.

	Algorithm:
		Export Set of Api services, each asynchronous service write the
		service call parameters into queue (1 deep level) and return to the call
		(not blocking), release thread which read the parameters and call
		FieldTalk function with this parameters.
		
	Check list steps for add new service Function-Command:
		1. Build service parameter structure
			Example:
				MbusPrintfT, MbusPowT, MbusLongTimeT
			1.1 Add this structure to Union MbusAsyncSrvParam.
		2. Define new constant symbol for functionId
			Example:
				prinfFUNID,	powFUNID,	longTimeFuncFUNID
			2.1 Add the new service call to thread switch
			Example:
				MbusMasterGetFunExe()
		3. Add new Local service call (class method *.h & *.cpp):
			Example:
				Lprintf(), Lpow(), LlongTimeFunc()
============================================================================
*/
						/* Select code for Template/example/test or Mbus (real) */
#define TEMPLATE_SELECTED			100
#define REAL_SELECTED				200
						/* FOR EFFECTIVE SETTING OF 'TEMPLATE_SELECTED'	THE LINK*/
						/* SHOULD SET FRO BUILD EXE (AND NOT SHARE LIB), E.G: 	*/
						/* COPY THE SOURCE TO NEW PROJECT WHICH BUILD .gexe.	*/
//#define	SELECT_TEMPLATE_OR_REAL     TEMPLATE_SELECTED
#define	SELECT_TEMPLATE_OR_REAL REAL_SELECTED

							/* Ver: DDMMYY 24-12-2013 	*/
#define	MBUS_MASTER_ASYNC_VER				0x00241213


#if   (SELECT_TEMPLATE_OR_REAL == TEMPLATE_SELECTED)
#elif (SELECT_TEMPLATE_OR_REAL == REAL_SELECTED)
#else
#error "***(MbusMasterAsyncServices.h) 'SELECT_TEMPLATE_OR_REAL' shuld be define as: 'TEMPLATE_SELECTED' or 'REAL_SELECTED'"
#endif


#include "MbusMasterAsyncServicesDatTypes.h"


							/* Error codes:				*/
#define	MBUS_MASTER_CREATING_THREAD			0x1234
#define	MBUS_MASTER_JOINING_THREAD			0x1235
#define	MBUS_MASTER_PARAM_ERROR				0x1236
#define	MBUS_MASTER_NO_SUCH_FUNTHREAD		0x1237



typedef enum MbusMasterSyncAsyncT
{
	MbusMasterAsync=9,
	MbusMasterSync
} MbusMasterSyncAsync;


			/* MbusMasterFunPtr is type of: pointer to function return		*/
			/* pointer to void and have parameter of type pointer to void.	*/
typedef void* (*MbusMasterFunPtr) (void *);
typedef void* (*MbusMasterFunPtrV)();



			/* Communication area between "put Api" to thread Consumer the putted data */
typedef struct MbusAsyncCommAreaT
{
  unsigned int			MbusMasterAsyncVer;	/* First, Enable read conditional the follow (meaning)	*/
  int					funcId;
  MbusAsyncSrvParam		SrvParam;		/* Union hold fun and its parameters */
} MbusAsyncCommArea;


/* Focuse Class herarcy
 *
 * class MbusTcpMasterProtocol: 		public MbusMasterFunctions
 * class MbusSerialMasterProtocol: 		public MbusMasterFunctions
 * 
 * class MbusAsciiMasterProtocol: 		public MbusSerialMasterProtocol
 * class MbusRtuMasterProtocol: 		public MbusSerialMasterProtocol
 * 
 * class MbusRtuOverTcpMasterProtocol: 	public MbusTcpMasterProtocol
 */


class DLLMMCPP_API MbusMasterAsyncServices: public MbusTcpMasterProtocol
{
public:
	MbusMasterAsyncServices()
	{
		SMbusAsyncCommArea.MbusMasterAsyncVer = MBUS_MASTER_ASYNC_VER;
		sem_init(&empty_sem_mutex,0, 1);
		sem_init(&full_sem_mutex, 0, 0);

		pCallBackFun 		= NULL;
		pCallBackFunPrmPtr	= NULL;

		if(pthread_create(&ctid, NULL, MbusMasterGetFunThreadWarper, this))
		  {
						/* Error creating thread */
			exit(MBUS_MASTER_CREATING_THREAD);
		  }
	}

	~MbusMasterAsyncServices()
	{
		if(pthread_join(ctid, NULL)) /* wait for consumer (MbusMasterGetFunThreadWarper) to finish */
		{
		    exit(MBUS_MASTER_JOINING_THREAD);
		}

		sem_destroy(&empty_sem_mutex);
		sem_destroy(&full_sem_mutex);
	}
						/* Implementation version */
	unsigned int MbusMasterAsyncVer();
						/* Return into 'ReadyForNewCommand' True/False 		*/
						/* according to service thread status.				*/
						/* When it ready for new service command return True*/
						/* There is no queue for request commands if call is*/
						/* made while the service thread is busy, the issue */
						/* process is block automatically and release after */
						/* the thread take the command.	Instead the issue   */
						/* process can check 'IsReady()' and issue commands */
						/* only when True.									*/
						/* Use Case: when calling process has enough work	*/
						/*          it issue Async service, check if ready  */
						/*          if not, do its work and again...		*/
	int IsReady(volatile bool *ReadyForNewCommand);
						/* This function block the calling process and 		*/
						/* release it when the service thread is "ready"	*/
						/* => finish it previous command (ready for new).	*/
						/* If ipRtStatus is not NULL the function return	*/
						/* there the last operation status.					*/
						/* Use Case: The calling process call for Async 	*/
						/*          service (background). Continue its  	*/
						/*			work and block itself on point			*/
						/*          it needs the background command finished*/
	int WaitForReady(int * ipRtStatus=NULL);
						/* Return the last FINISHED service return code.	*/
						/* Attention: be aware to which service the return  */
						/* code actually belonging...						*/
						/* When no new service was called, if IsReady() Yes	*/
						/* GetLastServiceRtStatus is from the last service	*/
	int	GetLastServiceRtStatus(int * iRtStatus);

						/* Call back function, call when Service fun return */
						/* CallBackFunPrmPtr - Value pass to CallBackFun 	*/
						/* when it call, if set to NULL the function call 	*/
						/* with no Param									*/
						/* new call replace the previous. Call to this func */
						/* couse block the process till current 			*/
						/* Service-Command if exist	finish, set the new		*/
						/* function and return to process. The new func		*/
						/* execute when next service-Command finish.		*/
						/* For Unregister CallBack function call as:		*/
						/* 		RegisterCallBackFunc(NULL, NULL);			*/
						/* Callback func not calling in SYNC execution mode */
	int RegisterCallBackFunc(MbusMasterFunPtr		CallBackFun,
							void					* CallBackFunPrmPtr);


#if   (SELECT_TEMPLATE_OR_REAL == TEMPLATE_SELECTED)

						/* Example - Implementation for printf() */
	int	Lprintf					(	 			// 0x1001
								char *format,
								int intVal,
								MbusMasterSyncAsync AsyncSync=MbusMasterAsync
								);
						/* Example - Implementation for pow() */
	int Lpow   					(               // 0x1002
								float *fnun1,
								float fnum2,
								float fnum3,
								MbusMasterSyncAsync AsyncSync=MbusMasterAsync
								);
						/* Example - long time excute function */
	int LlongTimeFunc 			(				// 0x1003
								int consumeTimeSec,
								MbusMasterSyncAsync AsyncSync=MbusMasterAsync 
								);


#elif (SELECT_TEMPLATE_OR_REAL == REAL_SELECTED)


	int	LreadCoils				(				// 0x1004
								int slaveAddr,
								int startRef,
								int *bitArr,
								int refCnt,
								MbusMasterSyncAsync AsyncSync=MbusMasterAsync 
								);
	int	LreadInputDiscretes		(				// 0x1005
								int slaveAddr,
								int startRef,
								int *bitArr,
								int refCnt,
								MbusMasterSyncAsync AsyncSync=MbusMasterAsync 
								);
	int LwriteCoil				(				// 0x1006
								int slaveAddr,
								int bitAddr,
								int bitVal,
								MbusMasterSyncAsync AsyncSync=MbusMasterAsync 
								);
	int LforceMultipleCoils 	(               // 0x1007
								int slaveAddr,
								int startRef,
								const int *bitArr,
								int refCnt,
								MbusMasterSyncAsync AsyncSync=MbusMasterAsync 
								);
	int LreadMultipleRegisters	(               // 0x1008
								int slaveAddr,
								int startRef,
								short *regArr,
								int refCnt,
								MbusMasterSyncAsync AsyncSync=MbusMasterAsync 
								);
	int LreadInputRegisters 	(			    // 0x1009
								int slaveAddr,
								int startRef,
								short *regArr,
								int refCnt,
								MbusMasterSyncAsync AsyncSync=MbusMasterAsync 
								);
	int LwriteSingleRegister	(				// 0x1010
								int slaveAddr,
								int regAddr,
								short regVal,
								MbusMasterSyncAsync AsyncSync=MbusMasterAsync 
								);
	int LwriteMultipleRegisters (				// 0x1011
								int slaveAddr,
								int startRef,
								const short *regArr,
								int refCnt,
								MbusMasterSyncAsync AsyncSync=MbusMasterAsync 
								);
	int LmaskWriteRegister 		(				// 0x1012
								int slaveAddr,
								int regAddr,
								short andMask,
								short orMask,
								MbusMasterSyncAsync AsyncSync=MbusMasterAsync 
								);
	int LreadWriteRegisters 	(				// 0x1013
								int slaveAddr,
								int readRef,
								short *readArr,
								int readCnt,
								int writeRef,
								const short *writeArr,
								int writeCnt,
								MbusMasterSyncAsync AsyncSync=MbusMasterAsync 
								);
	int LreadMultipleLongInts	(				// 0x1014
								int slaveAddr,
								int startRef,
								long *int32Arr,
								int refCnt,
								MbusMasterSyncAsync AsyncSync=MbusMasterAsync 
								);
	int LreadInputLongInts 		(				// 0x1015
								int slaveAddr,
								int startRef,
								long *int32Arr,
								int refCnt,
								MbusMasterSyncAsync AsyncSync=MbusMasterAsync 
								);
	int LwriteMultipleLongInts 	(				// 0x1016
								int slaveAddr,
								int startRef,
								const long 	*int32Arr,
								int refCnt,
								MbusMasterSyncAsync AsyncSync=MbusMasterAsync 
								);
	int LreadMultipleFloats 	(				// 0x1017
								int slaveAddr,
								int startRef,
								float *float32Arr,
								int refCnt,
								MbusMasterSyncAsync AsyncSync=MbusMasterAsync 
								);
	int LreadInputFloats 		(				// 0x1018
								int slaveAddr,
								int startRef,
								float *float32Arr,
								int refCnt,
								MbusMasterSyncAsync AsyncSync=MbusMasterAsync 
								);
	int LwriteMultipleFloats 	(				// 0x1019
								int slaveAddr,
								int startRef,
								const float *float32Arr,
								int refCnt,
								MbusMasterSyncAsync AsyncSync=MbusMasterAsync 
								);
	int LreadMultipleMod10000 	(				// 0x1020
								int slaveAddr,
								int startRef,
								long *int32Arr,
								int refCnt,
								MbusMasterSyncAsync AsyncSync=MbusMasterAsync 
								);
	int LreadInputMod10000 		(				// 0x1021
								int slaveAddr,
								int startRef,
								long *int32Arr,
								int refCnt,
								MbusMasterSyncAsync AsyncSync=MbusMasterAsync 
								);
	int LwriteMultipleMod10000 	(				// 0x1022
								int slaveAddr,
								int startRef,
								const long 	*int32Arr,
								int refCnt,
								MbusMasterSyncAsync AsyncSync=MbusMasterAsync 
								);
	int LreadExceptionStatus 	(			    // 0x1023
								int slaveAddr,
								unsigned char *statusBytePtr,
								MbusMasterSyncAsync AsyncSync=MbusMasterAsync 
								);
	int LreturnQueryData 		(				// 0x1024
								int slaveAddr,
								const unsigned char *queryArr,
								unsigned char *echoArr,
								int len,
								MbusMasterSyncAsync AsyncSync=MbusMasterAsync 
								);
	int LsetTimeout 			(
								int timeOut,	// 0x1025
								MbusMasterSyncAsync AsyncSync=MbusMasterAsync 
								);
	int LgetTimeout 			(				// 0x1026
								MbusMasterSyncAsync AsyncSync=MbusMasterAsync 
								);
	int LsetPollDelay 			(				// 0x1027
								int pollDelay,
								MbusMasterSyncAsync AsyncSync=MbusMasterAsync 
								);
	int LgetPollDelay 			(				// 0x1028
								MbusMasterSyncAsync AsyncSync=MbusMasterAsync 
								);
	int LsetRetryCnt 			(				// 0x1029
								int retryCnt,
								MbusMasterSyncAsync AsyncSync=MbusMasterAsync 
								);
	int LgetRetryCnt 			(				// 0x1030
								MbusMasterSyncAsync AsyncSync=MbusMasterAsync
								);
	long LgetTotalCounter 		(               // 0x1031
								MbusMasterSyncAsync AsyncSync=MbusMasterAsync
								);
	void LresetTotalCounter 	(				// 0x1032
								MbusMasterSyncAsync AsyncSync=MbusMasterAsync
								);
	long LgetSuccessCounter 	(				// 0x1033
								MbusMasterSyncAsync AsyncSync=MbusMasterAsync
								);
	void LresetSuccessCounter 	(				// 0x1034
								MbusMasterSyncAsync AsyncSync=MbusMasterAsync
								);
	void LconfigureBigEndianInts(				// 0x1035
								MbusMasterSyncAsync AsyncSync=MbusMasterAsync
								);
	void LconfigureSwappedFloats(				// 0x1036
								MbusMasterSyncAsync AsyncSync=MbusMasterAsync
								);
void LconfigureLittleEndianInts (				// 0x1037
								MbusMasterSyncAsync AsyncSync=MbusMasterAsync
								);
	void LconfigureIeeeFloats 	(				// 0x1038
								MbusMasterSyncAsync AsyncSync=MbusMasterAsync
								);
//???	TCHAR  LgetPackageVersion 	(				// 0x1039
	char  LgetPackageVersion 	(				// 0x1039
								MbusMasterSyncAsync AsyncSync=MbusMasterAsync
								);
	int	LopenProtocol   		(				// 0x1040
//???										const TCHAR * hostName,
										const char * hostName,
								MbusMasterSyncAsync AsyncSync=MbusMasterAsync
								);
	void LcloseProtocol     	(				// 0x1041
								MbusMasterSyncAsync AsyncSync=MbusMasterAsync
								);
	int	LisOpen     			(				// 0x1042
								MbusMasterSyncAsync AsyncSync=MbusMasterAsync
								);
	int	LsetPort    			(				// 0x1043
								unsigned short portNo,
								MbusMasterSyncAsync AsyncSync=MbusMasterAsync
								);

	int LadamSendReceiveAsciiCmd(               // 0x1044
								const char * commandSz,
								char *responseSz,
								MbusMasterSyncAsync AsyncSync=MbusMasterAsync
								);

#else
#error "***(MbusMasterAsyncServices.h) 'SELECT_TEMPLATE_OR_REAL' shuld be define as: 'TEMPLATE_SELECTED' or 'REAL_SELECTED'"
#endif
						/* Exit and close the service thread 	*/
						/* ONLY for ASYNC call 					*/
	int	LexitReq();

private:
					/* General function for fill communiation area with Application MBuf function 	*/
					/* later consume by thread and excute async to the Application.				  	*/
	int			MbusMasterPutFun(MbusAsyncCommArea *funcItem);

					/* Nothing but warper above MbusMasterGetFunThread() (Cpp behavior...) 	  		*/
	static void* MbusMasterGetFunThreadWarper(void *context);
					/* Actual Body of the Mbus consumer thread, call in loop for get Mbus functions	*/
	int 		MbusMasterGetFunThread(void);
					/* Thread side, Get one Mbus function from comunication area and exequte it	  	*/
	int			MbusMasterGetFun(void);
					/* Exequte one Mbus function from comunication area	*/
	int			MbusMasterGetFunExe(MbusAsyncCommArea* SMbusAsyncCommArea);

#if   (SELECT_TEMPLATE_OR_REAL == TEMPLATE_SELECTED)
					/* Example, long time exec function. 	*/
	int 		longTimeFunc (int consumeTimeSec);
#elif (SELECT_TEMPLATE_OR_REAL == REAL_SELECTED)
#else
#error "***(MbusMasterAsyncServices.h) 'SELECT_TEMPLATE_OR_REAL' shuld be define as: 'TEMPLATE_SELECTED' or 'REAL_SELECTED'"
#endif


					/* see above in RegisterCallBackFunc	*/
	MbusMasterFunPtr	pCallBackFun;
	void				* pCallBackFunPrmPtr;

	MbusAsyncCommArea   SMbusAsyncCommArea;
	sem_t 				empty_sem_mutex; 	/* producer semaphore - protect the data area  		*/
	sem_t 				full_sem_mutex; 	/* consumer (MbusMasterGetFunThread) semaphore 		*/
	int					iLastRtStatus;

	pthread_t 			ctid;
};

