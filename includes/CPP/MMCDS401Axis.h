/*
 * CMMCDS401Axis.h
 *
 *  Created on: 27/03/2011
 *      Author: yuvall
 */

#ifndef CMMCDS401AXIS_H_
#define CMMCDS401AXIS_H_

#include <MMCAxis.h>
#include <MMCNode.h>
#include <MMCPPGlobal.h>

class DLLMMCPP_API CMMCDS401Axis : public CMMCNode {
public:
	CMMCDS401Axis();
	~CMMCDS401Axis();

	void EnableDS401DIChangedEvent() throw (CMMCException);
	void DisableDS401DIChangedEvent() throw (CMMCException);
	MMCPPULL_T ReadDS401DInput() throw (CMMCException);
	void WriteDS401DOutput(MMCPPULL_T) throw (CMMCException);
	//
	//
	/*! \fn void ConfigGeneralRPDO3()
	*	\brief This function configure to receive general PDO3 message.
	*	\return	- void.
	*/
	void ConfigGeneralRPDO3(unsigned char ucEventType,unsigned char ucPDOCommParam, unsigned char ucPDOLength) throw(CMMCException);

	//
	/*! \fn void ConfigGeneralRPDO4()
	*	\brief This function configure to receive general PDO4 message.
	*	\return	- void.
	*/
	void ConfigGeneralRPDO4(unsigned char ucEventType,unsigned char ucPDOCommParam, unsigned char ucPDOLength) throw(CMMCException);

	//
	/*! \fn void CancelGeneralRPDO3()
	*	\brief This function cancel the configuration of receiving general PDO3 message.
	*	\return	- void.
	*/
	void CancelGeneralRPDO3() throw(CMMCException);

	//
	/*! \fn void CancelGeneralRPDO4()
	*	\brief This function cancle the configuration of receiving general PDO4 message.
	*	\return	- void.
	*/
	void CancelGeneralRPDO4() throw(CMMCException);

	//
	/*! \fn void ConfigGeneralTPDO3()
	*	\brief This function configure to transmit general PDO3 message.
	*	\return	- void.
	*/
	void ConfigGeneralTPDO3(unsigned char ucEventType) throw(CMMCException);

	//
	/*! \fn void ConfigGeneralTPDO4()
	*	\brief This function configure to transmit general PDO4 message.
	*	\return	- void.
	*/
	void ConfigGeneralTPDO4(unsigned char ucEventType) throw(CMMCException);

	//
	/*! \fn void CancelGeneralTPDO3()
	*	\brief This function cancle the configuration of transmitting general PDO3 message.
	*	\return	- void.
	*/
	void CancelGeneralTPDO3() throw(CMMCException);

	//
	/*! \fn void CancelGeneralTPDO4()
	*	\brief This function cancle the configuration of transmitting general PDO3 message.
	*	\return	- void.
	*/
	void CancelGeneralTPDO4() throw(CMMCException);

};

#endif /* CMMCDS401AXIS_H_ */
