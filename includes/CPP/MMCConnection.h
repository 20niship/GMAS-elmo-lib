/*
 * CMMCConnection.h
 *
 *  Created on: 22/03/2011
 *      Author: yuvall
 */

#ifndef MMCPPCONNECTION_H_
#define MMCPPCONNECTION_H_

#include "mmc_definitions.h"
#include "MMCPPGlobal.h"


#define USR_VAR_1   0
#define USR_VAR_2   1
#define USR_VAR_3   2
#define USR_VAR_4   3
#define EMERGENCY_MANUFACTURER_SPECIFIC_BLOCK_SIZE   5

#define EVENT_ID_INDX  0
#define POLICYERROR_ID_INDX  10
#define AXIS_REF_INDX  12
#define ASYNC_EVENT_LEN_INDX  16
#define PDO_GROUP_INDX  14
#define PDO_DATA_INDX   15
#define MSG_DATA_INDX 8
#define EMGCY_LEN_INDX 4
#define EMGCY_DATA_INDX		14
#define TOUCHP_POS_INDX		14
#define EVENT_CODE_INDX		14

typedef union {unsigned short usVal; float fVal; long lVal;} UNPDODAT;
typedef void (*PdoRcvEventCallback)(unsigned short usAxisRef, unsigned short usGrpID, UNPDODAT unDat1, UNPDODAT unDat2);
typedef void (*HBeateEventCallback)(unsigned short usAxisRef);
typedef void (*MotionEndEventCallback)(unsigned short usAxisRef, bool bResult);
typedef void (*EmergencyEventCallback)(unsigned short usAxisRef, short sEmcyCode, char cErrReg, char cManSpec[EMERGENCY_MANUFACTURER_SPECIFIC_BLOCK_SIZE]);
typedef void (*HomeEndedEventCallback)(unsigned short usAxisRef, short sErrCode,...);
typedef void (*ModbusWriteEventCallback)(unsigned short usSubType);
typedef void (*SysErrorEventCallback)();
typedef void (*AsyncReplyEventCallback)(unsigned short usAxisRef,unsigned short usStatus, unsigned short usError,
										unsigned short usCobID, unsigned short usLength, unsigned char* ucBuffer,
										unsigned char ucAsyncEventType, unsigned int uiAbortCode, unsigned short usIndex,
										unsigned char ucHeader,	unsigned char ucSubIndex);
typedef void (*TouchProbeEndCallback)(unsigned short usAxisRef, long  lPosition);
typedef void (*NodeErrorEventCallback)(unsigned short usAxisRef,unsigned short sErrorID,unsigned short usEmergencyCode);
typedef void (*StopOnLimitEventCallback)(unsigned short usAxisRef, unsigned short usError, unsigned int uiStatusRegister, unsigned int uiMcsLimitRegister);
typedef void (*TableUnderflowEventCallback)(unsigned short usAxisRef);
typedef void (*NodeConnectedEventCallback)(unsigned short usAxisRef);
typedef void (*GlobalAsyncReplyEventCallback)(unsigned short usStatus, unsigned short usError, unsigned char ucMessageID);
typedef void (*NodeInitEventCallback)(unsigned short usError, unsigned short usAxisRef);
typedef void (*FBNotifyEventCallback)(unsigned short usAxisRef, int  iEventCode);
typedef void (*PolicyEndedEventCallback)(unsigned short usAxisRef, short sError, unsigned char ucPolType, unsigned char ucPolState, unsigned char ucErrorType);

typedef enum {MMCPP_PDORCV, MMCPP_HBEAT,  MMCPP_MOTIONENDED,  MMCPP_EMCY,
	MMCPP_ASYNC_REPLY, MMCPP_HOME_ENDED, MMCPP_MODBUS_WRITE, MMCPP_TOUCH_PROBE_ENDED,
	MMCPP_NODE_ERROR, MMCPP_STOP_ON_LIMIT, MMCPP_TABLE_UNDERFLOW, MMCPP_NODE_CONNECTED,
	MMCPP_GLOBAL_ASYNC_REPLY, MMCPP_NODE_INIT, MMCPP_FB_NOTIFICATION, MMCPP_POLICY_ENDED
	} MMC_EVENT_ENUM;


class DLLMMCPP_API CMMCConnection {
public:
	CMMCConnection();
	virtual ~CMMCConnection();
	
	#ifndef WIN32
	unsigned int ConnectIPC(int iEventMask, MMC_CB_FUNC fpClbk);
	unsigned int ConnectIPCEx(int iEventMask, MMC_MB_CLBK fpClbk);
	#endif

	unsigned int ConnectRPC(char* cHostIP, char* cDestIP, int iEventMask, MMC_CB_FUNC fpClbk);
	unsigned int ConnectRPCEx(char* cHostIP, char* cDestIP, int iEventMask, MMC_MB_CLBK fpClbk);
	void CloseConnection();

	MMC_CONNECT_HNDL GetConnHndl() {return m_uiConnHndl;}
	void GetVersion() throw (CMMCException);
	void GetVersion_Ex()  throw (CMMCException);
	void GetLibVersion();
	void GetVersionEx(std::string& strVersion) throw (CMMCException);
	void GetVersion(int& iVer) throw (CMMCException);


	/*! \fn void MMC_GlobalWriteBoolParameterSetGlobalBoolParameter(unsigned long ulValue, MMC_PARAMETER_LIST_ENUM eNumber, int iIndex, unsigned char ucEnable = 1)
	* \brief This function write boolean global parameter.
	* \return	return - 0 if success, otherwise throws CMMCException.
	*/
	void SetGlobalBoolParameter(long lValue, MMC_PARAMETER_LIST_ENUM eNumber, int iIndex) throw (CMMCException);
	void SetGlobalParameter(double dbValue, MMC_PARAMETER_LIST_ENUM eNumber, int iIndex) throw (CMMCException);
	long GetGlobalBoolParameter(MMC_PARAMETER_LIST_ENUM eNumber, int iIndex) throw (CMMCException);
	double GetGlobalParameter(MMC_PARAMETER_LIST_ENUM eNumber, int iIndex) throw (CMMCException);
	//
	void SaveParameters() throw (CMMCException);
	void LoadParameters() throw (CMMCException);
	void SetDefaultManufacturerParameters() throw (CMMCException);
	void SetIsToLoadGlobalParams(unsigned char ucVal) throw (CMMCException);
	void SetHeartBeatConsumer(unsigned int uiHeartbeatTimeFactor) throw (CMMCException);
	int CallbackFunc(unsigned char*, short,void*);
	void RegisterEventCallback(MMC_EVENT_ENUM eClbType, void * pfClbk);//register event callbacks
	void RegisterSyncTimerFunction(MMC_SYNC_TIMER_CB_FUNC func,unsigned short usSYNCTimerTime);
	void GetMaestroTime(unsigned short &year, unsigned short &month, unsigned short &day, unsigned short &hour,
			unsigned short &minute, unsigned short &second, unsigned short &milliSecond) throw (CMMCException);
	void SetMaestroTime(unsigned short year, unsigned short month, unsigned short day, unsigned short hour,
			unsigned short minute, unsigned short second, unsigned short milliSecond) throw (CMMCException);

	// Connection related functions that deal with UDP event mask
	void SetEventsMask(unsigned int uiEventMask) throw (CMMCException);
	void ClearEventsMask(unsigned int uiEventMask) throw (CMMCException);
	unsigned int GetEventsMask() throw (CMMCException);

private:
	MMC_MB_CLBK m_fpClbk;
	MMC_CONNECT_HNDL m_uiConnHndl;	/*!< communication session handler;					*/
	char m_cHost[16];
	char m_cDest[16];
	int m_iConnID;
	unsigned char m_ucDeviceType;

	PdoRcvEventCallback			m_pfPdoRcvEventClbk;
	HBeateEventCallback			m_pfHBeateEventClbk;
	MotionEndEventCallback		m_pfMotionEndEventClbk;
	EmergencyEventCallback		m_pfEmergencyEventClbk;
	HomeEndedEventCallback		m_pfHomeEndEventClbk;
	ModbusWriteEventCallback	m_pfModbusWriteEventClbk;
	//SysErrorEventCallback		m_pfSysErrorEventClbk;
	AsyncReplyEventCallback		m_pfAsyncReplyEventClbk;
	TouchProbeEndCallback	   m_pfTouchProbeEndCallback;
	NodeErrorEventCallback		m_pfNodeErrorEventClbk;
	StopOnLimitEventCallback	m_pfStopOnLimitEventClbk;
	TableUnderflowEventCallback m_pfTableUnderflowEventClbk;
	NodeConnectedEventCallback	m_pfNodeConnectedEventClbk;
	GlobalAsyncReplyEventCallback	m_pfGlobalAsyncReplyEventClbk;
	NodeInitEventCallback			m_pfNodeInitEventClbk;
	FBNotifyEventCallback  			m_pfFBNotifyEventClbk;
	PolicyEndedEventCallback  		m_pfPolicyEndedEventClbk;

};

#endif /* MMCPPCONNECTION_H_ */
