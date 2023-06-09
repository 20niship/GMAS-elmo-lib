/*
 * CEmblHomeOnBlock.h
 *
 *  Created on: Jan 27, 2015
 *      Author: yuvall
 */

#ifndef EMCHOB_H_
#define EMCHOB_H_
#include "EMBLHome.h"
/*
 *
 */
#ifdef __cplusplus
class CEmblHomeOnBlock: public CEmblHome {
public:
	CEmblHomeOnBlock() {}
	CEmblHomeOnBlock(unsigned int uiConn, unsigned short usAxisRef);
	virtual ~CEmblHomeOnBlock();

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	 name:				Init
	 description:	    Initialize values for connection handle,axis reference and other class members.
						overloading function to prevent dynamic allocation.
	 input:             unsigned int uiConn - connection handle.
						usAxisRef - axis reference.
						homeOnBlockParam -  pointer to the relevant data that should be use the Initialize class members
	 output:
	 return:			0 if completed successfully, otherwise error
	 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	virtual int Init(unsigned int uiConn, unsigned short usAxisRef, EMBL_HOME_ON_BLOCK* homeOnBlockParam);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	 name:				Init
	 description:	    get specific data, convert to void* and send to Init(void *pData) function to initialize class members.
	 input:             homeOnBlockParam - pointer to the relevant data that should be used the Initialize class members
	 output:
	 return:			0 if completed successfully, otherwise error
	 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	virtual int Init(EMBL_HOME_ON_BLOCK* homeOnBlockParam);

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

unsigned int  HobCreateObj(unsigned int uiConn, unsigned short usAxisRef);
void  HobRmObj(unsigned int uiHobObj);
int  HobPost(unsigned int uiHobObj, void *pData );
int HobInit(unsigned int uiHobObj, EMBL_HOME_ON_BLOCK* data);

#ifdef __cplusplus
}
#endif
#endif /* EMCHOB_H_ */
