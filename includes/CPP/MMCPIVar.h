/*
 * MMCPIVar.h
 *
 *  Created on: Mar 3, 2014
 *      Author: ZivB
 */

#ifndef MMCPIVAR_H_
#define MMCPIVAR_H_

#include "mmc_definitions.h"
#include "MMCPPGlobal.h"
#include "MMCPIBulk.h"

typedef void (*CopyBool)(int index, bool &bValue);

class CMMCPIBulk;

// bit operations macros
#define PI_BITS_TO_BYTES(uiBitSize)						(((uiBitSize - 1) >> 3) + 1)
#define PI_BYTE_NUM_WITH_OFF(uiBitSize,ucBitStart)		(((uiBitSize + ucBitStart - 1) >> 3) + 1)
#define PI_MOD8_ASSIGN(x)								 x &= 0x07
#define PI_MOD8(x)										(x) & 0x07
#define PI_ALIGNMENT_CHECK(x)							(x) & PI_ALIGNMENT_BYTES

class DLLMMCPP_API CMMCPIVar {

	friend class CMMCPIBulk; //new 9.3.14

public:

	/*! \fn default constructor
	*/
	CMMCPIVar():m_uiConnHndl(0),m_usAxisRef(-1),m_ePIDirection(ePI_NONE),m_usPIVarOffset(0),m_ucVarType(0),m_uiBitOffset(0),m_uiBitSize(0),m_ucByteLength(0),m_pBulkRelated(NULL),
	m_iIsPIVARRelatedToBulkFlag(0)
	{

	}

	/*! \fn constructor()
	*	\brief constructor that receive PI VAR offset and direction.
	*/
	CMMCPIVar(MMC_CONNECT_HNDL uHandle, MMC_AXIS_REF_HNDL hAxisRef, unsigned short usPIVarOffset, PI_DIRECTIONS eDirection ) throw (CMMCException);

	/*! \fn constructor()
	*	\brief constructor that receive PI VAR alias.
	*/
	CMMCPIVar(MMC_CONNECT_HNDL uHandle, MMC_AXIS_REF_HNDL hAxisRef, char alias[PI_ALIASING_LENGTH]) throw (CMMCException);

	/*! \fn destructor
	*/
	virtual ~CMMCPIVar();

	/*! \fn Init()
	*	\brief set inital value for class variable according to offset.
	*/
	void Init(MMC_CONNECT_HNDL uHandle, MMC_AXIS_REF_HNDL hAxisRef, unsigned short usPIVarOffset, PI_DIRECTIONS eDirection ) throw (CMMCException);

	/*! \fn Init()
	*	\brief set inital value for class variable according to alias.
	*/
	void Init(MMC_CONNECT_HNDL uHandle, MMC_AXIS_REF_HNDL hAxisRef, char alias[PI_ALIASING_LENGTH]) throw (CMMCException);

	/*! \fn UnbindFromBulkRead()
	*	\brief remove the option of reading from bulkRead.
	*/
	void UnbindFromBulkRead();

	/*! \fn IsBindtoBulkRead()
	*	\brief return 1 if bind to bulk read or 0 if it is not bind to bulk read.
	*/
	int IsBoundToBulkRead();

	/*! \WritePI(bool bValue)
	*	\write the input argument value to PI var.
	*/
	void WritePI(bool bValue) throw (CMMCException);

	void WritePI(char cValue) throw (CMMCException);

	void WritePI(unsigned char ucValue) throw (CMMCException);

	void WritePI(unsigned short usValue) throw (CMMCException);

	void WritePI(short sValue) throw (CMMCException);

	void WritePI(unsigned int uiValue) throw (CMMCException);

	void WritePI(int iValue) throw (CMMCException);

	void WritePI(float fValue) throw (CMMCException);

	void WritePI(unsigned char *ucValue,int iSize) throw (CMMCException);

#ifdef WIN32

	void WritePI(unsigned __int64 ullValue) throw (CMMCException);

	void WritePI(__int64 llValue) throw (CMMCException);

#else
	void WritePI(unsigned long long ullValue) throw (CMMCException);

	void WritePI(long long llValue) throw (CMMCException);
#endif

	void WritePI(double dValue) throw (CMMCException);


	/*! \ReadPI(bool &bValue)
	*	\Read the value of PI variable.
	*	\The value will return in the bValue
	*/
	void ReadPI(bool &bValue) throw (CMMCException);

	void ReadPI(char &cValue) throw (CMMCException);

	void ReadPI(unsigned char &ucValue) throw (CMMCException);

	void ReadPI(short &sValue) throw (CMMCException);

	void ReadPI(unsigned short &usValue) throw (CMMCException);

	void ReadPI(int &iValue) throw (CMMCException);

	void ReadPI(unsigned int &uiValue) throw (CMMCException);

	void ReadPI(float &fValue) throw (CMMCException);

	void ReadPI(unsigned char *ucValue,int iSize) throw (CMMCException);

#ifdef WIN32
	void ReadPI(__int64 &llValue) throw (CMMCException);

	void ReadPI(unsigned __int64 &ullValue) throw (CMMCException);
#else
	void ReadPI(long long &llValue) throw (CMMCException);

	void ReadPI(unsigned long long &ullValue) throw (CMMCException);
#endif

	void ReadPI(double &dValue) throw (CMMCException);

	/*! \fn GetPIVarInfoByAlias()
	*	\brief gets the PI info according to the PI alaia.
	*	\char alias : the name of the PI
	*	\MMC_GETPIVARINFOBYALIAS_OUT &pOutParam - retrive the info data of the PI
	*/
	void GetPIVarInfoByAlias(char alias[PI_ALIASING_LENGTH],MMC_GETPIVARINFOBYALIAS_OUT &pOutParam) throw (CMMCException);

	/*! \fn GetPIVarsRangeInfo()
	*	\brief gets the PI info of range of PI.
	*	\param MMC_GETPIVARSRANGEINFO_IN  pInParam
	*	\param  MMC_GETPIVARSRANGEINFO_OUT &pOutParam - retrive the info data of the PI
	*/
	void GetPIVarsRangeInfo(MMC_GETPIVARSRANGEINFO_IN  pInParam,MMC_GETPIVARSRANGEINFO_OUT &pOutParam) throw (CMMCException);

private:

	MMC_CONNECT_HNDL 		m_uiConnHndl;
	MMC_AXIS_REF_HNDL		m_usAxisRef;
	PI_DIRECTIONS 			m_ePIDirection;
	unsigned short 			m_usPIVarOffset;
	unsigned char   		m_ucVarType;
	unsigned int    		m_uiBitOffset;
	unsigned int    		m_uiBitSize;
	unsigned char  			m_ucByteLength;

	//BulkRead related parameters
	int 					m_iIndexInDataBuffer;
	CMMCPIBulk 				*m_pBulkRelated;
	int 					m_iIsPIVARRelatedToBulkFlag;
	//CopyBool				m_pfCopyBool ;
};
#endif /* MMCPIVAR_H_ */
