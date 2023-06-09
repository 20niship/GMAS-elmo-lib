/*
 * CMMCAxis.h
 *
 *  Created on: 10/03/2011
 *      Author: yuvall
 */

#ifndef CMMCAXIS_H_
#define CMMCAXIS_H_

#include "string.h"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include "MMCPPGlobal.h"

//using namespace std;

#define MAX_RETRIES 1000


class DLLMMCPP_API CMMCAxis {
public:
	/*! \fn default constructor
	*	\brief This function retrieves axis name.
	*/
	CMMCAxis():
		m_uiConnHndl(0),
		m_usAxisRef(-1)
		{}

	CMMCAxis(CMMCAxis&  axis);
	/*! \fn destructor
	*	\brief This function retrieves axis name.
	*/
	virtual ~CMMCAxis(){}

	/*! \fn char* GetName()
	*	\brief This function retrieves axis name.
	*/
	const char* GetName() const {return m_strName;}
	/*! \fn unsigned int GetConnHndl()
	*	\brief This function retrieves conneciton handler.
	*/
	MMC_CONNECT_HNDL GetConnHndl() const {return m_uiConnHndl;}

	/*! \fn unsigned short GetRef()
	*	\brief This function retrieves axis reference .
	*/
	unsigned short GetRef() const {return m_usAxisRef;}

	/*! \fn void InitAxisData(const char* cName, MMC_CONNECT_HNDL uHandle)
	*	\brief This function initiates axis name and retrieves a session handler.
	*/
	virtual void InitAxisData(const char* cName, MMC_CONNECT_HNDL uHandle) throw (CMMCException)
	{
		SetName(cName);
		SetConnHndl(uHandle);
		GetAxisByName(cName);
	}

	/*! \fn int GetAxisByName(const char* cName)
	 * \brief This function return axis index reference by his name.
	 * \param  cName name of the axis.
	 * \return	return - 0 on success, otherwise throws CMMCException.
	 */
	int GetAxisByName(const char* cName) throw (CMMCException);


	/*! \fn unsigned int SetDefaultManufacturerParameters()
	* \brief This function restore the axis\group parameters
	* \param
	* \return
	*/

	void SetDefaultManufacturerParameters() throw (CMMCException);

	/*! \fn unsigned int GetStatusRegister()
	* \brief This function returns the motion status word
	* \return	return - 0 on success, otherwise throws CMMCException.
	*/
	virtual unsigned int GetStatusRegister() throw (CMMCException)
	{
		CMMCPPGlobal::Instance()->MMCPPThrow("MMC_GetStatusRegister:", m_uiConnHndl, m_usAxisRef, -1, NC_WRONG_NODE_TYPE, 0);
		return 0;
	}


	unsigned int GetSystemCounter() throw (CMMCException);



protected:
	/*! \fn void SetName()
	*	\brief This function sets axis name.
	*/
	void SetName(const char* cName) {strcpy(m_strName, cName);}
	/*! \fn void SetConnHndl()
	*	\brief This function sets axis's connection handler.
	*/
	void SetConnHndl(MMC_CONNECT_HNDL uiConnHndl){m_uiConnHndl=uiConnHndl;}
	/*! \fn void SetRef()
	*	\brief This function sets axis ref.
	*/
	void SetRef(unsigned short usAxisRef){m_usAxisRef = usAxisRef;}
protected:
	//
	char m_strName[128];							/*!< axis name.						*/
	MMC_CONNECT_HNDL m_uiConnHndl;					/*!< communication session handler;	*/
	unsigned short m_usAxisRef;						/*!< set by GetAxisByName 			*/
};

#endif /* CMMCAXIS_H_ */
