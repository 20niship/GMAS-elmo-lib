/*
 * CEmblHomeOnIndex.h
 *
 *  Created on: 13/04/2015
 *      Author: ilia
 */

#ifndef CEMBLHOMEONINDEX_H_
#define CEMBLHOMEONINDEX_H_
#include "EMBLHome.h"
#ifdef __cplusplus

class CEmblHomeOnIndex : public CEmblHome {
public:
	CEmblHomeOnIndex();
	CEmblHomeOnIndex(unsigned int uiConn, unsigned short usAxisRef);
	virtual ~CEmblHomeOnIndex();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	 name:				Init
	 description:	    Initialize values for connection handle,axis reference and other class members.
						overloading function to prevent dynamic allocation.
	 input:             unsigned int uiConn - connection handle.
						usAxisRef - axis reference.
						homeOnIndexInParam -  pointer to the relevant data that should be use the Initialize class members
	 output:
	 return:			0 if completed successfully, otherwise error
	 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	virtual int Init(unsigned int uiConn, unsigned short usAxisRef, EMBL_HOME_ON_INDEX_IN* homeOnIndexInParam);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	 name:				Init
	 description:	    get specific data, convert to void* and send to Init(void *pData) function to initialize class members.
	 input:             homeOnIndexInParam - pointer to the relevant data that should be used the Initialize class members
	 output:
	 return:			0 if completed successfully, otherwise error
	 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	virtual int Init(EMBL_HOME_ON_INDEX_IN* homeOnIndexInParam);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	 name:				PostPerform
	 description:       Execution of methods after the perform ended.
						Overloaded function to let the user call by specific value and prevent him send by casting to (void*)
	 input:             homeOutParam - structure of data relevant for PostPerform function.
	 output:
	 return:			0 if completed successfully, otherwise error
	 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	virtual int PostPerform(MMC_HOME_OUT* homeOutParam);

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
	 * \brife: Execution of methods after the perform ended.
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

unsigned int  HoIndexCreateObj(unsigned int uiConn, unsigned short usAxisRef);
void  HoIndexRmObj(unsigned int uiHoIndexObj);
int HoIndexInit(unsigned int uiHoIndexObj, EMBL_HOME_ON_INDEX_IN* data);
int  HoIndexPost(unsigned int uiHoIndexObj, void *pData );

#ifdef __cplusplus
}
#endif
#endif /* CEMBLHOMEONINDEX_H_ */
