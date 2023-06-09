/*
============================================================================
 Name : MbusMasterAsyncServices.h
 Author : Haim Hillel
 Version : 23Dec2013

 Description : GMAS C/C++ project header file
	This Class provide Mbus Asynchronous services.
	The services base on Focus FieldTalk Modbus Master C++ Library, ver 2.4.1.
	This Class is wrapper above Focus services provide asynchronous call.
	In this header file is the service functioin section of the header file.

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

							/* Function-Command ID		*/

#if   (SELECT_TEMPLATE_OR_REAL == TEMPLATE_SELECTED)

	#define prinfFUNID						0x1001
	#define powFUNID						0x1002
	#define longTimeFuncFUNID				0x1003
	
#elif (SELECT_TEMPLATE_OR_REAL == REAL_SELECTED)

	#define readCoilsFUNID              	0x1004
	#define readInputDiscretesFUNID     	0x1005
	#define writeCoilFUNID              	0x1006
	#define forceMultipleCoilsFUNID     	0x1007
	#define readMultipleRegistersFUNID  	0x1008
	#define readInputRegistersFUNID     	0x1009
	#define writeSingleRegisterFUNID    	0x1010
	#define writeMultipleRegistersFUNID 	0x1011
	#define maskWriteRegisterFUNID      	0x1012
	#define readWriteRegistersFUNID     	0x1013
	#define readMultipleLongIntsFUNID   	0x1014
	#define readInputLongIntsFUNID      	0x1015
	#define writeMultipleLongIntsFUNID  	0x1016
	#define readMultipleFloatsFUNID     	0x1017
	#define readInputFloatsFUNID        	0x1018
	#define writeMultipleFloatsFUNID    	0x1019
	#define readMultipleMod10000FUNID   	0x1020
	#define readInputMod10000FUNID       	0x1021
	#define writeMultipleMod10000FUNID  	0x1022
	#define readExceptionStatusFUNID    	0x1023
	#define returnQueryDataFUNID        	0x1024
	#define setTimeoutFUNID             	0x1025
	#define getTimeoutFUNID             	0x1026
	#define setPollDelayFUNID           	0x1027
	#define getPollDelayFUNID           	0x1028
	#define setRetryCntFUNID            	0x1029
	#define getRetryCntFUNID            	0x1030
	#define getTotalCounterFUNID        	0x1031
	#define resetTotalCounterFUNID      	0x1032
	#define getSuccessCounterFUNID      	0x1033
	#define resetSuccessCounterFUNID    	0x1034
	#define configureBigEndianIntsFUNID 	0x1035
	#define configureSwappedFloatsFUNID 	0x1036
	#define configureLittleEndianIntsFUNID	0x1037
	#define configureIeeeFloatsFUNID		0x1038
	#define getPackageVersionFUNID      	0x1039
	
	#define openProtocolFUNID				0x1040
	#define closeProtocolFUNID				0x1041
	#define isOpenFUNID						0x1042
	#define setPortFUNID					0x1043
	#define adamSendReceiveAsciiCmdFUNID    0x1044
	
#else
#error "***(MbusMasterAsyncServices.h) 'SELECT_TEMPLATE_OR_REAL' shuld be define as: 'TEMPLATE_SELECTED' or 'REAL_SELECTED'"
#endif
#define 	exitReqFUNID					0x1999



#if   (SELECT_TEMPLATE_OR_REAL == TEMPLATE_SELECTED)

	typedef struct MbusPrintfStructT   		// 0x1001 
	{
		char			* format;
		int			    printVal;
	} MbusPrintfT;
	
	typedef struct MbusPowStructT      		// 0x1002 
	{
		float			*powRsult;
		float			powBase;
		float			powExp;
	} MbusPowT;
	
	
	typedef struct MbuslongTimeStructT      // 0x1003 
	{
		int				exeSec;
	} MbusLongTimeT;

#elif (SELECT_TEMPLATE_OR_REAL == REAL_SELECTED)

	typedef struct MbusReadCoilsStructT     // 0x1004 
	{
		int slaveAddr;
		int startRef;
		int *bitArr;
		int refCnt;
	}MbusReadCoilsT;

	typedef struct MbusReadInputDiscretesStructT  // 0x1005 
	{
		int slaveAddr;
		int startRef;
		int *bitArr;
		int refCnt;
	}MbusReadInputDiscretesT;

	typedef struct MbusWriteCoilStructT     // 0x1006 
	{
		int slaveAddr;
		int bitAddr;
		int bitVal;
	}MbusWriteCoilT;

	typedef struct MbusForceMultipleCoilsStructT	// 0x1007 
	{
		int slaveAddr;
		int startRef;
		const int * bitArr;
		int refCnt;
	}MbusForceMultipleCoilsT;

	typedef struct MbusReadMultipleRegistersStructT // 0x1008 
	{
		int slaveAddr;
		int startRef;
		short *regArr;
		int refCnt;
	}MbusReadMultipleRegistersT;

	typedef struct MbusReadInputRegistersStructT    // 0x1009 
	{
		int slaveAddr;
		int startRef;
		short *regArr;
		int refCnt;
	}MbusReadInputRegistersT;

	typedef struct MbusWriteSingleRegisterStructT   // 0x1010 
	{
		int slaveAddr;
		int regAddr;
		short regVal;
	}MbusWriteSingleRegisterT;

	typedef struct MbusWriteMultipleRegistersStructT	// 0x1011 
	{
		int slaveAddr;
		int startRef;
		const short *regArr;
		int refCnt;
	}MbusWriteMultipleRegistersT;

	typedef struct MbusMaskWriteRegisterStructT	// 0x1012 
	{ 
		int slaveAddr;
		int regAddr;
		short andMask;
		short orMask;
	}MbusMaskWriteRegisterT;

	typedef struct MbusReadWriteRegistersStructT // 0x1013 
	{     
		int slaveAddr;
		int readRef;
		short *readArr;
		int readCnt;
		int writeRef;
		const short *writeArr;
		int writeCnt;
	}MbusReadWriteRegistersT;

	typedef struct MbusReadMultipleLongIntsStructT	// 0x1014 
	{
		int slaveAddr;
		int startRef;
		long *int32Arr;
		int refCnt;
	}MbusReadMultipleLongIntsT;

	typedef struct MbusReadInputLongIntsStructT // 0x1015 
	{
		int slaveAddr;
		int startRef;
		long *int32Arr;
		int refCnt;
	}MbusReadInputLongIntsT;

	typedef struct MbusWriteMultipleLongIntsStructT // 0x1016 
	{
		int slaveAddr;
		int startRef;
		const long  *int32Arr;
		int refCnt;
	}MbusWriteMultipleLongIntsT;

	typedef struct MbusReadMultipleFloatsStructT // 0x1017 
	{
		int slaveAddr;
		int startRef;
		float *float32Arr;
		int refCnt;
	}MbusReadMultipleFloatsT;

	typedef struct MbusReadInputFloatsStructT // 0x1018 
	{
		int slaveAddr;
		int startRef;
		float *float32Arr;
		int refCnt;
	}MbusReadInputFloatsT;

	typedef struct MbusWriteMultipleFloatsStructT // 0x1019 
	{
		int slaveAddr;
		int startRef;
		const float *float32Arr;
		int refCnt;
	}MbusWriteMultipleFloatsT;

	typedef struct MbusReadMultipleMod10000StructT // 0x1020 
	{
		int slaveAddr;
		int startRef;
		long *int32Arr;
		int refCnt;
	}MbusReadMultipleMod10000T;

	typedef struct MbusReadInputMod10000StructT // 0x1021
	{
		int slaveAddr;
		int startRef;
		long *int32Arr;
		int refCnt;
	}MbusReadInputMod10000T;

	typedef struct MbusWriteMultipleMod10000StructT // 0x1022 
	{
		int slaveAddr;
		int startRef;
		const long  *int32Arr;
		int refCnt;
	}MbusWriteMultipleMod10000T;

	typedef struct MbusReadExceptionStatusStructT // 0x1023 
	{
		int slaveAddr;
		unsigned char *statusBytePtr;
	}MbusReadExceptionStatusT;

	typedef struct MbusReturnQueryDataStructT // 0x1024 
	{
		int slaveAddr;
		const unsigned char *queryArr;
		unsigned char *echoArr;
		int len;
	}MbusReturnQueryDataT;

	typedef struct MbusSetTimeoutStructT    // 0x1025 
	{
		int timeOut;
	}MbusSetTimeoutT;

	typedef struct MbusGetTimeoutStructT	// 0x1026
	{
	}MbusGetTimeoutT;

	typedef struct MbusSetPollDelayStructT  // 0x1027 
	{
		int pollDelay;
	}MbusSetPollDelayT;

	typedef struct MbusGetPollDelayStructT  // 0x1028 
	{
	}MbusGetPollDelayT;

	typedef struct MbusSetRetryCntStructT   // 0x1029 
	{
		int retryCnt;
	}MbusSetRetryCntT;

	typedef struct MbusGetRetryCntStructT   // 0x1030 
	{
	}MbusGetRetryCntT;

	typedef struct MbusGetTotalCounterStructT // 0x1031 
	{
	}MbusGetTotalCounterT;

	typedef struct MbusResetTotalCounterStructT // 0x1032 
	{
	}MbusResetTotalCounterT;

	typedef struct MbusGetSuccessCounterStructT // 0x1033
	{
	}MbusGetSuccessCounterT;

	typedef struct MbusResetSuccessCounterStructT // 0x1034
	{
	}MbusResetSuccessCounterT;

	typedef struct MbusConfigureBigEndianIntsStructT // 0x1035 
	{
	}MbusConfigureBigEndianIntsT;

	typedef struct MbusConfigureSwappedFloatsStructT // 0x1036
	{
	}MbusConfigureSwappedFloatsT;

	typedef struct MbusConfigureLittleEndianIntsStructT // 0x1037
	{
	}MbusConfigureLittleEndianIntsT;

	typedef struct MbusConfigureIeeeFloatsStructT // 0x1038 
	{
	}MbusConfigureIeeeFloatsT;

	typedef struct MbusGetPackageVersionStructT   // 0x1039 
	{
	}MbusGetPackageVersionT;


	typedef struct MbusOpenProtocolStructT		  // 0x1040
	{
// ???  const TCHAR * hostName;
        const char * hostName;
	}MbusOpenProtocolT;

	typedef struct MbusCloseProtocolStructT		  // 0x1041
	{
	}MbusCloseProtocolT;

	typedef struct MbusIsOpenStructT			  // 0x1042
	{
	}MbusIsOpenT;

	typedef struct MbusSetPortStructT			  // 0x1043
	{
        unsigned short portNo;
	}MbusSetPortT;

	typedef struct MbusAdamSendReceiveAsciiCmdStructT // 0x1044
	{
        const char * commandSz;
		char *responseSz;
	}MbusAdamSendReceiveAsciiCmdT;

#else
#error "***(MbusMasterAsyncServices.h) 'SELECT_TEMPLATE_OR_REAL' shuld be define as: 'TEMPLATE_SELECTED' or 'REAL_SELECTED'"
#endif


typedef union MbusAsyncT
{

#if   (SELECT_TEMPLATE_OR_REAL == TEMPLATE_SELECTED)

	MbusPrintfT   				   MbusPrintf;							// 0x1001
	MbusPowT					   MbusPow;              				// 0x1002
	MbusLongTimeT				   MbusLongTime;         				// 0x1003

#elif (SELECT_TEMPLATE_OR_REAL == REAL_SELECTED)

	MbusReadCoilsT                 MbusReadCoils;                       // 0x1004
	MbusReadInputDiscretesT        MbusReadInputDiscretes;              // 0x1005
	MbusWriteCoilT                 MbusWriteCoil;                       // 0x1006
	MbusForceMultipleCoilsT        MbusForceMultipleCoils;              // 0x1007
	MbusReadMultipleRegistersT     MbusReadMultipleRegisters;           // 0x1008
	MbusReadInputRegistersT        MbusReadInputRegisters;              // 0x1009
	MbusWriteSingleRegisterT       MbusWriteSingleRegister;             // 0x1010
	MbusWriteMultipleRegistersT    MbusWriteMultipleRegisters;          // 0x1011
	MbusMaskWriteRegisterT         MbusMaskWriteRegister;               // 0x1012
	MbusReadWriteRegistersT        MbusReadWriteRegisters;              // 0x1013
	MbusReadMultipleLongIntsT      MbusReadMultipleLongInts;            // 0x1014
	MbusReadInputLongIntsT         MbusReadInputLongInts;               // 0x1015
	MbusWriteMultipleLongIntsT     MbusWriteMultipleLongInts;           // 0x1016
	MbusReadMultipleFloatsT        MbusReadMultipleFloats;              // 0x1017
	MbusReadInputFloatsT           MbusReadInputFloats;                 // 0x1018
	MbusWriteMultipleFloatsT       MbusWriteMultipleFloats;             // 0x1019
	MbusReadMultipleMod10000T      MbusReadMultipleMod10000;            // 0x1020
	MbusReadInputMod10000T         MbusReadInputMod10000;               // 0x1021
	MbusWriteMultipleMod10000T     MbusWriteMultipleMod10000;           // 0x1022
	MbusReadExceptionStatusT       MbusReadExceptionStatus;             // 0x1023
	MbusReturnQueryDataT           MbusReturnQueryData;                 // 0x1024
	MbusSetTimeoutT                MbusSetTimeout;                      // 0x1025
	MbusGetTimeoutT                MbusGetTimeout;                      // 0x1026
	MbusSetPollDelayT              MbusSetPollDelay;                    // 0x1027
	MbusGetPollDelayT              MbusGetPollDelay;                    // 0x1028
	MbusSetRetryCntT               MbusSetRetryCnt;                     // 0x1029
	MbusGetRetryCntT               MbusGetRetryCnt;                     // 0x1030
	MbusGetTotalCounterT           MbusGetTotalCounter;                 // 0x1031
	MbusResetTotalCounterT         MbusResetTotalCounter;               // 0x1032
	MbusGetSuccessCounterT         MbusGetSuccessCounter;               // 0x1033
	MbusResetSuccessCounterT       MbusResetSuccessCounter;             // 0x1034
	MbusConfigureBigEndianIntsT    MbusConfigureBigEndianInts;          // 0x1035
	MbusConfigureSwappedFloatsT    MbusConfigureSwappedFloats;          // 0x1036
	MbusConfigureLittleEndianIntsT MbusConfigureLittleEndianInts;		// 0x1037
	MbusConfigureIeeeFloatsT       MbusConfigureIeeeFloats;             // 0x1038
	MbusGetPackageVersionT         MbusGetPackageVersion;               // 0x1039

	MbusOpenProtocolT              MbusOpenProtocol;                    // 0x1040
	MbusCloseProtocolT			   MbusCloseProtocol;                   // 0x1041
	MbusIsOpenT					   MbusIsOpen;                          // 0x1042
	MbusSetPortT                   MbusSetPort;                         // 0x1043
	MbusAdamSendReceiveAsciiCmdT   MbusAdamSendReceiveAsciiCmd;			// 0x1044

#else
#error "***(MbusMasterAsyncServices.h) 'SELECT_TEMPLATE_OR_REAL' shuld be define as: 'TEMPLATE_SELECTED' or 'REAL_SELECTED'"
#endif
} MbusAsyncSrvParam;

