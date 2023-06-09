/*
 * CMMCNode.h
 *
 *  Created on: 27/03/2011
 *      Author: yuvall
 *		Update: HH Add func ResetAsync
 */
#include <MMCAxis.h>

#ifndef CMMCNODE_H_
#define CMMCNODE_H_


typedef enum {PDO_NUM_3	= 3, PDO_NUM_4 = 4} PDO_NUMBER_ENUM;
typedef enum {PDO_PARAM_REG	= 1, PDO_PARAM_USE	= 2 } PDO_PARAM_TYPE_ENUM;

class DLLMMCPP_API CMMCNode : public CMMCAxis {
public:

	/*! \fn default constructor
	*/
	CMMCNode();

	/*! \fn copy constructor
	 */
	CMMCNode(CMMCNode& axis):CMMCAxis(axis){}

	/*! \fn destructor
	*/
	~CMMCNode();

	virtual void Reset() throw(CMMCException);
    virtual void ResetAsync() throw(CMMCException);
	/*! \fn int ReadStatus()
	*	\brief This function gets axis status for specific axis.
	*	\return	return - status on success, otherwise throws CMMCException.
	*/
	virtual unsigned long ReadStatus() throw (CMMCException);
	virtual unsigned long ReadStatus(unsigned short& usAxisErrorID, unsigned short& usStatusWord) throw (CMMCException);
	//
	/*! \fn int  MMC_SendSdoCmd(
	* \brief This function send SDO message command.*/
	virtual void SendSdoCmd(long lData,
			unsigned char ucService,
			unsigned char ucSubIndex,
			unsigned long ulDataLength,
			unsigned short usIndex,
			unsigned short usSlaveID) throw (CMMCException);

	//
	/*! \fn int  unsigned(
	* \brief This function send SDO message command.*/
	virtual void SendSdoDownload(long lData,
			unsigned char ucSubIndex,
			unsigned long ulDataLength,
			unsigned short usIndex,
			unsigned short usSlaveID) throw (CMMCException);


	//
	/*! \fn int  SendSdoUpload(
	* \brief This function send SDO message command.*/
	virtual long SendSdoUpload(unsigned char ucSubIndex,
			unsigned long ulDataLength,
			unsigned short usIndex,
			unsigned short usSlaveID) throw (CMMCException);

	//
	/*! \fn int  SendSdoUpload(
	* \brief This function send SDO message command.*/
	virtual void SendSdoUploadAsync(unsigned char ucSubIndex,
			unsigned long ulDataLength,
			unsigned short usIndex,
			unsigned short usSlaveID) throw (CMMCException);

	//
	/*! \fn int  SendSdoUpload(
	* \brief This function send SDO message command.*/
	virtual void RetreiveSdoUploadAsync(long& lData) throw (CMMCException);

	//
	/*! \fn void PDOGeneralRead()
	*	\brief This function gets General PDO from the axis (this PDO defined by the user).
	*	\return - Return the actual value of the PDO, ulliVal variable inserted by reference.
	*/
	virtual MMCPPULL_T PDOGeneralRead(unsigned char ucParam) throw(CMMCException);
	//
	//
	/*! \fn void PDOGeneralWrite()
	*	\brief This function sets General PDO from the axis (this PDO defined by the user).
	*	\return	- void.
	*/
	virtual void PDOGeneralWrite(unsigned char ucParam,MMCPPULL_T ulliVal) throw(CMMCException);
	virtual void PDOGeneralWrite(unsigned char ucParam,unGeneralPDOWriteData DataUnion) throw(CMMCException);

	//
	/*! \fn void GetPDOInfo()
	*	\brief This function get information about PDO 3\4.
	*	IN uiPDONumber			- PDO number (3\4)
	*	OUT iPDOEventMode		- PDO event mode (NO\CYCLE\IMMEDIATE)
	*	OUT ucPDOCommType		- Communication parameter (SYNC\ASYNC\NO_EVENT)
	*	OUT ucPDOCommEventGroup	- PDO Current group (1 .... 17)
	*	\return	- void.
	*/
	virtual void GetPDOInfo(unsigned char uiPDONumber,int &iPDOEventMode, unsigned int &uiCommParamEventPDO,unsigned short &usEventTimerPDO, unsigned char &ucRPDOCommType,unsigned char &ucTPDOCommType, unsigned char &ucTPDOCommEventGroup, unsigned char &ucRPDOCommEventGroup, unsigned char &ucSubIndexTPDO, unsigned char &ucSubindexRPDO) throw(CMMCException);

	virtual void SetBoolParameter(long lValue, MMC_PARAMETER_LIST_ENUM eNumber, int iIndex) throw (CMMCException);
	virtual void SetParameter(double dbValue, MMC_PARAMETER_LIST_ENUM eNumber, int iIndex) throw (CMMCException);
	virtual long GetBoolParameter(MMC_PARAMETER_LIST_ENUM eNumber, int iIndex) throw (CMMCException);
	virtual double GetParameter(MMC_PARAMETER_LIST_ENUM eNumber, int iIndex) throw (CMMCException);
	virtual void ConfigPDOEventMode(unsigned char ucPDOEventMode, PDO_NUMBER_ENUM ePDONum = PDO_NUM_3) throw (CMMCException);
	virtual void ConfigPDOEventMode(MC_PDO_EVENT_NOTIF_MODE_ENUM ePDOEventMode, PDO_NUMBER_ENUM ePDONum = PDO_NUM_3) throw (CMMCException);

	virtual unsigned short GetAxisError(unsigned short* usLastEmergencyErrCode) throw (CMMCException);


	virtual void EthercatWriteMemoryRange(unsigned short usRegAddr, unsigned char ucLength, unsigned char pData[ETHERCAT_MEMORY_WRITE_MAX_SIZE]) throw (CMMCException);

	virtual void EthercatWritePIVar(unsigned short usIndex, unsigned char ucByteLength,	unsigned char pRawData[PI_REG_VAR_SIZE]) throw (CMMCException);
	virtual void EthercatWritePIVar(unsigned short usIndex,	unsigned short usByteLength, unsigned char pRawData[PI_LARGE_VAR_SIZE]) throw (CMMCException);
	virtual void EthercatWritePIVar(unsigned short usIndex, bool bData) throw (CMMCException);
	virtual void EthercatWritePIVar(unsigned short usIndex,	signed char cData) throw (CMMCException);
	virtual void EthercatWritePIVar(unsigned short usIndex, unsigned char ucData) throw (CMMCException);
	virtual void EthercatWritePIVar(unsigned short usIndex, unsigned short usData) throw (CMMCException);
	virtual void EthercatWritePIVar(unsigned short usIndex, short sData) throw (CMMCException);
	virtual void EthercatWritePIVar(unsigned short usIndex, unsigned int uiData) throw (CMMCException);
	virtual void EthercatWritePIVar(unsigned short usIndex, int iData) throw (CMMCException);
	virtual void EthercatWritePIVar(unsigned short usIndex, float fData) throw (CMMCException);
	virtual void EthercatWritePIVar(unsigned short usIndex, double dbData) throw (CMMCException);
	
#ifdef WIN32
	virtual void EthercatWritePIVar(unsigned short usIndex, unsigned __int64 ullData) throw (CMMCException);
	virtual void EthercatWritePIVar(unsigned short usIndex, __int64 llData) throw (CMMCException);
#else
	virtual void EthercatWritePIVar(unsigned short usIndex, unsigned long long ullData) throw (CMMCException);
	virtual void EthercatWritePIVar(unsigned short usIndex, long long llData) throw (CMMCException);
#endif


	virtual void EthercatReadMemoryRange(unsigned short usRegAddr,	unsigned char ucLength, unsigned char pData[ETHERCAT_MEMORY_READ_MAX_SIZE]) throw (CMMCException);

	virtual void EthercatReadPIVar(unsigned short usIndex, unsigned char ucDirection, unsigned char ucByteLength, unsigned char pRawData[PI_REG_VAR_SIZE]) throw (CMMCException);
	virtual void EthercatReadPIVar(unsigned short usIndex, unsigned char ucDirection, unsigned short usByteLength, unsigned char pRawData[PI_LARGE_VAR_SIZE]) throw (CMMCException);
	virtual void EthercatReadPIVar(unsigned short usIndex, unsigned char ucDirection, bool &bData) throw (CMMCException);
	virtual void EthercatReadPIVar(unsigned short usIndex, unsigned char ucDirection, signed char &cData) throw (CMMCException);
	virtual void EthercatReadPIVar(unsigned short usIndex, unsigned char ucDirection, unsigned char &ucData) throw (CMMCException);
	virtual void EthercatReadPIVar(unsigned short usIndex, unsigned char ucDirection, unsigned short &usData) throw (CMMCException);
	virtual void EthercatReadPIVar(unsigned short usIndex, unsigned char ucDirection, short &sData) throw (CMMCException);
	virtual void EthercatReadPIVar(unsigned short usIndex, unsigned char ucDirection, unsigned int &uiData) throw (CMMCException);
	virtual void EthercatReadPIVar(unsigned short usIndex, unsigned char ucDirection, int &iData) throw (CMMCException);
	virtual void EthercatReadPIVar(unsigned short usIndex, unsigned char ucDirection, float &fData) throw (CMMCException);
	virtual void EthercatReadPIVar(unsigned short usIndex, unsigned char ucDirection, double &dbData) throw (CMMCException);
	
#ifdef WIN32
	virtual void EthercatReadPIVar(unsigned short usIndex, unsigned char ucDirection, unsigned __int64 &ullData) throw (CMMCException);
	virtual void EthercatReadPIVar(unsigned short usIndex, unsigned char ucDirection, __int64 &llData) throw (CMMCException);
#else
	virtual void EthercatReadPIVar(unsigned short usIndex, unsigned char ucDirection, unsigned long long &ullData) throw (CMMCException);
	virtual void EthercatReadPIVar(unsigned short usIndex, unsigned char ucDirection, long long &llData) throw (CMMCException);
#endif
	
	virtual void EthercatPIVarInfo(unsigned short usPIVarIndex, unsigned char ucDirection, NC_PI_ENTRY &VarInfo) throw (CMMCException);

};

#endif /* CMMCNODE_H_ */
