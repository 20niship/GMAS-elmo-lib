/*
 * MMCDS406Axis.h
 *
 *  Created on: 27/03/2011
 *      Author: yuvall
 */

#ifndef MMCDS406_H_
#define MMCDS406_H_

#include <MMCNode.h>

class DLLMMCPP_API CMMCDS406 : public CMMCNode {
public:
	CMMCDS406();
	~CMMCDS406();

	double GetActualPosition() throw (CMMCException);

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

private:

	void PDOGeneralWrite(unsigned char ucParam,MMCPPULL_T ulliVal)throw (CMMCException){return;}
	void GetPDOInfo(unsigned char uiPDONumber,int &iPDOEventMode, unsigned char &ucPDOCommType, unsigned char &ucTPDOCommEventGroup, unsigned char &ucRPDOCommEventGroup)throw (CMMCException){return;}

};

#endif /* MMCDS406_H_ */
