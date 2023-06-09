/*
 * MMCPIBulk.h
 *
 *  Created on: Mar 9, 2014
 *      Author: ZivB
 */

#ifndef MMCPIBULK_H_
#define MMCPIBULK_H_

#include "MMC_definitions.h"
#include "MMCPPGlobal.h"
#include "MMCPIVar.h"


class CMMCPIVar;

class DLLMMCPP_API CMMCPIBulk {

	friend class CMMCPIVar;

public:

	/*! \fn default constructor
	*/
	CMMCPIBulk();

	/*! \fn constructor()
	*	\brief constructor that connection handle and size of array.
	*/
	CMMCPIBulk(MMC_CONNECT_HNDL ConnHndl, int iSize, NC_BULKREAD_CONFIG_PI_ENUM  eConfiguration, CMMCPIVar *PIVARArr = NULL) throw (CMMCException);

	/*! \fn destructor
	*/
	virtual ~CMMCPIBulk();

	/*! \fn Init()
	*	\brief set inital value for class
	*/
	void Init(MMC_CONNECT_HNDL ConnHndl, int iSize, NC_BULKREAD_CONFIG_PI_ENUM  eConfiguration, CMMCPIVar *PIVARArr = NULL) throw (CMMCException);

	/*! \fn Append()
	*	\Add new CMMCCPIVar to the array of PIVAR
	*/
	void Append(CMMCPIVar &PIVar) throw (CMMCException);

	/*! \fn Clear()
	*	\Clear the instance of the PIBULKREAD
	*/
	void Clear() throw (CMMCException);

	/*! \fn Config()
	*	\Perform config bulk read according to the setting
	*/
	void Config() throw (CMMCException);

	/*! \fn Upload()
	*	\Perform upload of the data
	*/
	void Upload() throw (CMMCException);


private:

	/*! \fn Copy()
	*	\Perform copy of the requested data
	*/
	void Copy(int index, bool &bValue);

	void Copy(int index, char &cValue);

	void Copy(int index, unsigned char &ucValue);

	void Copy(int index, short &sValue);

	void Copy(int index, unsigned short &usValue);

	void Copy(int index, int &iValue);

	void Copy(int index, unsigned int &uiValue);

	void Copy(int index, float &fValue);

#ifdef WIN32
	void Copy(int index, __int64 &ullValue);

	void Copy(int index, unsigned __int64 &ullValue);
#else
	void Copy(int index, long long &ullValue);

	void Copy(int index, unsigned long long &ullValue);
#endif

	void Copy(int index, double &dValue);


	MMC_CONNECT_HNDL 				m_uiConnHndl;
	MMC_CONFIGBULKREADPI_IN 		m_ConfigBulkReadPIInParam;
	NC_BULKREAD_CONFIG_PI_ENUM    	m_eConfiguration;
	MMC_PERFORMBULKREADPI_OUT 		m_pOut_performBulkread;
	int 							m_iIndexInDataBuffer;
	int 							m_iIndexInInputBuffer;
	int								m_iIsBulkReadInitializedFlag;
};


#endif /* MMCPIBULK_H_ */
