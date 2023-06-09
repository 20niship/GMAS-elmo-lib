/*
 * CMMCPPGlobal.h
 *
 *  Created on: 15/03/2011
 *      Author: yuvall
 */
/*
 * -------------------------------------------------------------------------------------------------------------
 * history list of modification
 * -------------------------------------------------------------------------------------------------------------
 *		 #				description																version release	name			date
 *	__________________________________________________________________________________
 *		001	 		add version release definition										v1.0.0.1			YL				30/10/2013
 *		002	 		add message size restriction to TCP/UDP messages	v1.0.0.1			YL				30/10/2013
 *		003	 		bypass Linux socket select bug
 *						in CMMCPP::IsWriable & ::IsReadable						v1.0.0.1			YL				30/10/2013
 *		004			reset #003. getpeername system call is not					v1.0.0.2			YL/HH		23/01/2014
 *						a suitable solution.
 *		005			add ECAM API															v1.0.0.4			YL				30/11/2014
 * 	006			add CurveType input parameter to MC_CamIn			v1.0.1.0			YL				04/03/2015
 * 					within InitPVT Table, PVT dynamic is on unless Cyclic
 * 					if on. underflow threshold is 0 if Cyclic is on.
 * 					Cyclic is meaningless on PVT dynamic mode.  			v1.0.1.0			YL				04/03/2015
 */

#ifndef MMCPPGLOBAL_H_
#define MMCPPGLOBAL_H_
//
//
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <fstream>
#include "MMC_definitions.h"
//
//
//using std::cout;
//using std::endl;
//using std::fstream;
//using std::string;
using namespace std;
//
#ifdef _WIN32
	typedef unsigned __int64 MMCPPULL_T;
	#pragma warning( disable : 4290 )
#else
	typedef unsigned long long int MMCPPULL_T;
#endif
//
//
#ifndef DLLMMCPP_API
#ifdef WIN32
#include "windows.h"
#ifdef LIBMMCPPLIB_EXPORTS
#define DLLMMCPP_API __declspec(dllexport)
#else
#define DLLMMCPP_API __declspec(dllimport)
#endif
#else
#define DLLMMCPP_API
#ifdef _PLATINUM
#pragma GCC diagnostic ignored "-Wwrite-strings"
#pragma GCC diagnostic ignored "-Wunused-but-set-variable"
#pragma GCC diagnostic ignored "-Wconversion-null"
#endif
#endif
#endif
//
//
#include "MMCMessage.h"

#define _MMCPP_VERSION_RELEASE "v1.0.1.8"
//
//
#ifdef _WIN32
#include <winsock2.h>
#include <sys/utime.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>



struct timespec
{
  time_t tv_sec;
  long int tv_nsec;
};

static void nanosleep (const struct timespec *requested_delay)
{
  if (requested_delay->tv_sec > 0)
    /* at least one second. Millisecond resolution is sufficient. */
    Sleep ((DWORD)requested_delay->tv_sec * 1000 + requested_delay->tv_nsec / 1000000);
  else {
      /* Use Sleep for the largest part, and busy-loop for the rest. */
      static double frequency;
      if (frequency == 0)
        {
          LARGE_INTEGER freq;
          if (!QueryPerformanceFrequency (&freq))
            {
              /* Cannot use QueryPerformanceCounter. */
              Sleep (requested_delay->tv_nsec / 1000000);
              return;
            }
          frequency = (double) freq.QuadPart / 1000000000.0;
        }
      double expected_counter_difference = requested_delay->tv_nsec * frequency;
      int sleep_part = (int) requested_delay->tv_nsec / 1000000 - 10;
      LARGE_INTEGER before;
      QueryPerformanceCounter (&before);
      double expected_counter = before.QuadPart + expected_counter_difference;
      if (sleep_part > 0)
        Sleep (sleep_part);
      for (;;) {
          LARGE_INTEGER after;
          QueryPerformanceCounter (&after);
          if (after.QuadPart >= expected_counter)
            break;
      }
    }
}

#endif


#ifdef MMCPP_DEBUG
#define MMCPP_TRACE(FORMAT,FUNC,RC,NAME,REF,ERRID,STATUS) \
	printf(FORMAT,FUNC,RC,NAME,REF,ERRID,STATUS);
#define _MMCPP_TRACE(FORMAT,RC,NAME,REF,ERRID,STATUS) \
	printf(FORMAT,RC,NAME,REF,ERRID,STATUS);
#define _MMCPP_TRACE_INFO(INFOSTR) \
	cout << INFOSTR << endl;
#else
#define MMCPP_TRACE(FORMAT,FUNC,RC,NAME,REF,ERRID,STATUS)
#define _MMCPP_TRACE(FORMAT,RC,NAME,REF,ERRID,STATUS)
#define _MMCPP_TRACE_INFO(INFOSTR)
#endif
//
//
#define MMCPP_MAX_CONNECTIONS_NUM	20
//
typedef struct
{
	unsigned int m_uiConnHndl;
	void* m_pConn;
} MMCPP_CONN_REG;


template <class T>
class TMMCPPSingleton
{
public:
	static T * Instance()	{
		static T obj;
		return &obj;
	}

private:
	TMMCPPSingleton() {}
	~TMMCPPSingleton() {}
};

#define SINGLETON(T) protected:friend class TMMCPPSingleton< T >;T(){};
#define SINGLETONINSTANCE(T) TMMCPPSingleton< T >::Instance()

// ----------------------------------------------------------------------------




typedef int (*RTE_CLBKP)(const char* cErrMsg, unsigned int uiConnHndl, unsigned short usAxisRef, short sErrorID, unsigned short usStatus);
typedef int (*WARNING_CLBKP)(const char* cFunctionName, unsigned int uiConnHndl, unsigned short usAxisRef, int iRetCode, short sErrorID, unsigned short usStatus);

class DLLMMCPP_API CMMCException
{
public:
	CMMCException(const char* msg, const char* cAxisName, unsigned short usAxisRef, int errid, unsigned short status): m_usErrorID(errid), m_usStatus(status), m_usAxisRef(usAxisRef)
	{
		strcpy(m_cAxisName, cAxisName);
		strcpy(m_cMessage, msg);
	}

	const char* what() const {return m_cMessage;}
	const char* axisName() const {return m_cAxisName;}
	const short error() const	{return m_usErrorID;}
	unsigned short status() const {return m_usStatus;}
	unsigned short  axisRef() const {return m_usAxisRef;}

private:
	char m_cMessage[1024];
	char m_cAxisName[128];
	unsigned short m_usErrorID;
	unsigned short m_usStatus;
	unsigned short m_usAxisRef;		/*!< set by GetAxisByName							*/
};
//



//
class DLLMMCPP_API CMMCPPGlobal {
//	SINGLETON( CMMCPPGlobal )
public:
	static CMMCPPGlobal * Instance()
	{
		static CMMCPPGlobal g_Instance;		
		return &g_Instance;
	}

public:
	//
	void RegisterRTE(RTE_CLBKP pRTEClbk, bool bIsToCloseOnRTE = true) {m_pRTEClbk = pRTEClbk;m_bIsToCloseOnRTE = bIsToCloseOnRTE;}
	void RegisterWarningClbk(WARNING_CLBKP pWarningClbk) {m_pWarningClbk =  pWarningClbk;}
	void SetThrowFlag(bool bThrow, bool bIsToCloseOnThrow = true) {m_bThrowException_OnError =  bThrow;m_bIsToCloseOnThrow = bIsToCloseOnThrow;}
	void SetThrowWarningFlag(bool bThrowWarining) {m_bThrowException_OnWarning =  bThrowWarining;}
	void SetPrintErrorFlag(bool bPrintError) {m_bPrintError =  bPrintError;}
	void SetPrintWarningFlag(bool bPrintWarining) {m_bPrintWarning =  bPrintWarining;}
	bool IsToThrowError() { return m_bThrowException_OnError;}
	bool IsToThrowWarning() {return m_bThrowException_OnWarning;}
	bool IsToCallWarningClbk() { return (m_pWarningClbk != NULL);}
	bool IsToCallRTEClbk() {return (m_pRTEClbk != NULL);}
    void  MMCPPThrow(const char* cFunctionName, unsigned int uiConnHndl, unsigned short usAxisRef, int iRetCode, short sErrorID, unsigned short usStatus);
	/*! \fn unsigned short GetSyncTime()
	* \brief The function returns the SYNC time, in case of CAN communication.
	* \return	return - sync time on success, otherwise throws CMMCException.
	*/
	unsigned short GetSyncTime(unsigned int uiConnHndl) throw (CMMCException);
	/*! \fn int SetSyncTime(
	* \brief The function sets the SYNC time in the communication module.
	* \param  usSync - sync time.
	* \return	return - 0 if success, otherwise throws CMMCException.
	*/
	int SetSyncTime(unsigned int uiConnHndl, unsigned short usSync) throw (CMMCException);
	void CreateSYNCTimer(unsigned int uiConnHndl, MMC_SYNC_TIMER_CB_FUNC pfClbk, unsigned short usSYNCTimerTime)  throw (CMMCException);
	void DestroySYNCTimer(unsigned int uiConnHndl) throw (CMMCException);
	//
	int RegisterConnection(unsigned int uiConnHndl, void * pConn);
	void* GetConnectionReg(unsigned int uiConnHndl);
	void ClearConnectionReg(unsigned int uiConnHndl);
	//
	void			ThrowMessage(int iRetval,int iErrorID,const char* cFunctionName);
	MMCPP_CONN_TYPE GetConnectionType(){return m_eConnectionType;}
	void			SetConnectionType(MMCPP_CONN_TYPE eConnectionType_IN){m_eConnectionType = eConnectionType_IN;}
	
	#ifndef WIN32
	string			GetMessageFileName(){return m_cMessage.GetMessageFileName();}
	void			SetMessageFileName(string sMessageFileName_IN){m_cMessage.SetMessageFileName(sMessageFileName_IN);}
	void			SetMessageFileName(char* cMessageFileName_IN){m_cMessage.SetMessageFileName(cMessageFileName_IN);}
	#endif

	void			ConfigBulkRead(MMC_CONNECT_HNDL hConnHndl,
								   NC_BULKREAD_CONFIG_ENUM eConfig,
								   NC_BULKREAD_PRESET_ENUM ePreset,
								   unsigned short usAxisRefArray[],
								   unsigned short usNumberOfAxes,
								   float* fFactorsArray) throw (CMMCException);
	void			ConfigBulkRead(MMC_CONNECT_HNDL hConnHndl,
								   NC_BULKREAD_CONFIG_ENUM eConfig,
								   unsigned long ulParameters[],
								   unsigned short usAxisRefArray[],
								   unsigned short usNumberOfAxes,
								   float* fFactorsArray) throw (CMMCException);
	void			PerformBulkRead(MMC_CONNECT_HNDL hConnHndl,
									unsigned short usNumberOfAxes,
									NC_BULKREAD_CONFIG_ENUM eConfiguration,
									NC_BULKREAD_PRESET_ENUM& eChosenPreset,
									NC_BULKREAD_PRESET_1 stOutputData[]);
	void 			PerformBulkRead(MMC_CONNECT_HNDL hConnHndl,
									unsigned short usNumberOfAxes,
									NC_BULKREAD_CONFIG_ENUM eConfiguration,
									NC_BULKREAD_PRESET_ENUM& eChosenPreset,
									NC_BULKREAD_PRESET_2 stOutputData[]);
	void 			PerformBulkRead(MMC_CONNECT_HNDL hConnHndl,
									unsigned short usNumberOfAxes,
									NC_BULKREAD_CONFIG_ENUM eConfiguration,
									NC_BULKREAD_PRESET_ENUM& eChosenPreset,
									NC_BULKREAD_PRESET_3 stOutputData[]);

	void 			PerformBulkRead(MMC_CONNECT_HNDL hConnHndl,
									unsigned short usNumberOfAxes,
									NC_BULKREAD_CONFIG_ENUM eConfiguration,
									NC_BULKREAD_PRESET_ENUM& eChosenPreset,
									NC_BULKREAD_PRESET_4 stOutputData[]);

	void 			PerformBulkRead(MMC_CONNECT_HNDL hConnHndl,
									unsigned short usNumberOfAxes,
									NC_BULKREAD_CONFIG_ENUM eConfiguration,
									NC_BULKREAD_PRESET_ENUM& eChosenPreset,
									NC_BULKREAD_PRESET_5 stOutputData[]);

	void 			PerformBulkRead(MMC_CONNECT_HNDL hConnHndl,
									unsigned short usNumberOfAxes,
									NC_BULKREAD_CONFIG_ENUM eConfiguration,
									NC_BULKREAD_PRESET_ENUM& eChosenPreset,
									unsigned long* ulOutputData);
	//
	void 			UserCommandControlExe(MMC_CONNECT_HNDL hConnHndl,
										  char cUserCommandIn[128],
										  MC_COMMAND_OPERATION eUsrCommandOpIn,
										  int &iStatus,
										  char cExecutableFileName[64] = NULL);

	void RegErrPolicy(MMC_CONNECT_HNDL hConnHndl,MMC_REGERRPOLICY_IN stInParams) throw (CMMCException);
	void GetErrPolicy(MMC_CONNECT_HNDL hConnHndl,MMC_GETERRPOLICY_IN stInParams,MMC_GETERRPOLICY_OUT &stOutParams) throw (CMMCException);
	void ResetSystem(MMC_CONNECT_HNDL hConnHndl) throw (CMMCException);

#ifndef WIN32
	std::string GetLibVersion(); __attribute__ ((deprecated));
#else
	/*
	* too risky. user project's settings must comply exactly to library 
	* use GetLibVersion(std::string& str) (see below)
	*/
	__declspec(deprecated) std::string GetLibVersion(); 
#endif
	/**
	* \fn void GetLibVersion(std::string& str)
	* \brief		retrieves this library version release
	* \param str	string reference from user program to retrieve the version.
	* \return none. version in str.
	*/
	inline void GetLibVersion(std::string& str) {str = std::string(_MMCPP_VERSION_RELEASE);}

private:

CMMCPPGlobal():m_pRTEClbk(NULL),m_pWarningClbk(NULL)
{
	for(int i=0;i<MMCPP_MAX_CONNECTIONS_NUM;i++)
	{
		m_ConnRegTable[i].m_uiConnHndl=0;
	}
	m_bThrowException_OnError = false;
	m_bThrowException_OnWarning = false;
	m_bPrintWarning = false;
	m_bPrintError = true;
	m_bIsToCloseOnRTE = true;
	m_eConnectionType = CT_UNKNOWN;
}

	~CMMCPPGlobal()
	{
	}

	CMMCPPGlobal(CMMCPPGlobal const&);   // Don't Implement
    void operator=(CMMCPPGlobal const&); // Don't implement
	//
	bool 					m_bThrowException_OnError;
	bool 					m_bThrowException_OnWarning;
	bool					m_bPrintWarning;
	bool					m_bPrintError;
	bool					m_bIsToCloseOnRTE;
	bool					m_bIsToCloseOnThrow;
	MMCPP_CONN_TYPE			m_eConnectionType;
	RTE_CLBKP 				m_pRTEClbk;
	WARNING_CLBKP			m_pWarningClbk;
	MMCPP_CONN_REG 			m_ConnRegTable[MMCPP_MAX_CONNECTIONS_NUM];		
	#ifndef WIN32
	CMMCMessage				m_cMessage;
	#endif
};


namespace MMCPPUtils
{
	inline void endian_swap16(unsigned short* x)
	{
		*x = (*x>>8) | (*x<<8);
	}
	inline void endian_swap32(unsigned int* x)
	{
		*x = (*x>>24) | ((*x<<8) & 0x00FF0000) |((*x>>8) & 0x0000FF00) | (*x<<24);
	}

	inline void NetToLocal(void* NetBuff, unsigned short *usVal)
	{
		memcpy((unsigned char*)usVal,(unsigned char*)NetBuff, 2);
		#ifdef WIN32
			endian_swap16((unsigned short *)usVal);
		#endif
	}
	inline void NetToLocal(void* NetBuff, void *iVal)
	{
		memcpy((unsigned char*)iVal,(unsigned char*)NetBuff,4);
		#ifdef WIN32
			endian_swap32((unsigned int *)iVal);
		#endif
	}
}

#endif /* MMCPPGLOBAL_H_ */
