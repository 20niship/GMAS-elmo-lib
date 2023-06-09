/*
 * EmblOCPosTabActivate.h
 *
 *  Created on: 22/06/2015
 *      Author: ilia
 */

#ifndef EMBLOCPOSTABACTIVATE_H_
#define EMBLOCPOSTABACTIVATE_H_

#ifdef __cplusplus
#include "EMBLOutputCompare.h"

class CEmblOCPosTabActivate: public CEMBLOutputCompare {
public:
	CEmblOCPosTabActivate() {}
	CEmblOCPosTabActivate(unsigned int uiConn, unsigned short usAxisRef);
	virtual ~CEmblOCPosTabActivate();

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	 name:				Init
	 description:	    Initialize values for connection handle,axis reference and other class members.
						overloading function to prevent dynamic allocation.
	 input:             unsigned int uiConn - connection handle.
						usAxisRef - axis reference.
						ocPosTabActivateInParam -  pointer to the relevant data that should be use the Initialize class members
	 output:
	 return:			0 if completed successfully, otherwise error
	 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	virtual int Init(unsigned int uiConn, unsigned short usAxisRef, EMBL_OC_POS_TAB_ACTIVE_IN* ocPosTabActivateInParam);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	 name:				Init
	 description:	    get specific data, convert to void* and send to Init(void *pData) function to initialize class members.
	 input:             ocPosTabActivateInParam - pointer to the relevant data that should be used the Initialize class members
	 output:
	 return:			0 if completed successfully, otherwise error
	 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	virtual int Init(EMBL_OC_POS_TAB_ACTIVE_IN* ocPosTabActivateInParam);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	 name:				PostPerform
	 description:       Execution of methods after the perform ended.
						Overloaded function to let the user call by specific value and prevent him send by casting to (void*)
	 input:             outParam - structure of data relevant for PostPerform function.
	 output:
	 return:			0 if completed successfully, otherwise error
	 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	virtual int PostPerform(EMBL_OUT* outParam);

	void  Echo(void);
protected:

	/**
		 * \fn Init()
		 * \brife: Initialize values for the class members
		 * \In param:
		 * \void *pData - void pointer to the relevant data that should be use the Initialize class members
		 */
		virtual int Init(void *);
		/**
		 * \fn PostPerform()
		 * \brife: Execution of methods after the preform ended.
		 * \return none.
		 */
		virtual int PostPerform(void *);
};
#endif
/*-------------------------------------------------------------------------
 * accessor functions are a way to convert that reference we passed
 *  to C (the void pointer) back into something usable by C++ .
 */
#ifdef __cplusplus
extern "C" {
#endif
unsigned int  OCPosTabActivateCreateObj(unsigned int uiConn, unsigned short usAxisRef);
void  OCPosTabActivateRmObj(unsigned int uiOCPosTabActivateObj);
int OCPosTabActivateInit(unsigned int uiOCPosTabActivateObj, EMBL_OC_POS_TAB_ACTIVE_IN* data);
int  OCPosTabActivatePost(unsigned int uiOCPosTabActivateObj, void *pData );

#ifdef __cplusplus
}
#endif
#endif /* EMBLOCPOSTABACTIVATE_H_ */
