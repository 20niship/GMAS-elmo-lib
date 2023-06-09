/*
 * MMCEIPSession.h
 *
 *  Created on: 03/06/2012
 *      Author: yuvall
 */

#ifndef MMCEIPSession_H_
#define MMCEIPSession_H_

//#include "MMCPPGlobal.h"
#include <EIP_API.h>

#ifdef __cplusplus
 extern "C" {
#endif
int EipLibCallback (unsigned char* cBuffer, short sEvent,void* ptr);
void EIPP_Init();
void EIPP_Close();
#ifdef __cplusplus
}
#endif

/**
* \class CMMCEIPSession
*
* \brief This is a singleton class, which manages EthernetIP session.
*
* @author YL 5/6/2012
*
* $Header $
*/

/*
 *
 */
class CMMCEIPSession {
public:
	static CMMCEIPSession* Instance()
	{
		static CMMCEIPSession obj;
		return &obj;
	}
private:
	CMMCEIPSession() {}
	~CMMCEIPSession(){}

public:

	/*! \fn int EipOpenSession(unsigned short& usStatus)
	*	\brief initialize  and starts EIP session
	*	\param pClbkFunc user call back function to invoke on EADK (EIP stack) event call back.
	*	\param bEventNotification event notification flag. EIP ignores  user call back if this flag is false.
	*	\return 0 on success, error id otherwise.
	*/
	int EipOpenSession( EIP_CALLBACK_FUNC	pClbkFunc, bool bEventNotification = true);

	/*! \fn int EIPCloseSession(unsigned short& usStatus)
	*	\brief close EtherntIP session and frees allocated memoey before terminating program
	*	\return 0 on success, error id otherwise.
	*/
	int EIPCloseSession();

	/*! \fn int EipCreate(char 	* strPath, unsigned short& usStatus)
	*	\brief creates internal DB according to given XML file.
	*	\details allocate memory, parse XML tags files and initializes mutexes and semaphores.
	*	\param strPath full path to XML tags file as null terminated string.
	*	\return 0 on success, error id otherwise.
	*/
	int EipCreate(char 	* strPath);

	/*! \fn int EipDestroy(unsigned short& usStatus)
	*	\brief release all resources (allocated memory, mutexes, semaphores, etc...)
	*	\return 0 on success, error id otherwise.
	*/
	int EipDestroy();
};

#endif /* MMCEIPSession_H_ */
