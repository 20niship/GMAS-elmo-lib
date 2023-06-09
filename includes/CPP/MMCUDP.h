/*
 * CMMCUDP.h
 *
 *  Created on: 28/06/2011
 *      Author: yuvall
 */

#ifndef CMMCUDP_H_
#define CMMCUDP_H_

#ifndef WIN32

#include <fcntl.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>

#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>

#else

#include <winsock2.h>
#include <iostream>
#include <fstream>

#endif //WIN32


#include "MMCSocket.h"
/*
 *
 */
#define	MMCUDP_MaxSize	512
class DLLMMCPP_API CMMCUDP {
public:
	CMMCUDP();
	virtual ~CMMCUDP();

	inline void SetMessageMaxSize(int iSize) {_iMsgMaxSize = iSize;}

	/*! \fn int Create (char * cIP, int iPort) throw (CMMCException)
	* \brief this function creates the socket.
	* \param cIP - IP address of driver.
	* \param iPort - port for socket connection.
	* \return	return - 0 on success, otherwise throws CMMCException or non zero.
	*/
	int Create (char * cIP, int iPort, int iGMASPort = 0, int iMaxSize = 512) throw (CMMCException) ;

	/*! \fn int SendTo(char* msg, short sLength) throw (CMMCException)
	* \brief this function sends data via socket.
	* \param msg - message buffer to send..
	* \param sLength - length (bytes) of data to send. must not be more then buffer length.
	* \return result>=0 on success, otherwise throws CMMCException or -1.
	*/
	int SendTo(char* msg, short sLength, bool clrRcvBuf=true) ;//throw (CMMCException);

	/*! \fn int RecvFrom(char* msg, short sLength, short sTimeoutMS) throw (CMMCException)
	* \brief this function receives data from socket.
	* \param msg - message buffer to receive data..
	* \param sLength - length to read. must not be more then buffer length.
	* \param sTimeoutMS - milliseconds to wait on receive.
	* \return	return - result>=0 on success, otherwise throws CMMCException or result<0.
	*/
	int ReceiveFrom(char* msg, short sLength, short sTimeout) throw (CMMCException);


	/*! \fn int GetIP(char* msg, short sLength) throw (CMMCException)
	* \brief This function returns the ip of the connection
	* \return the IP address as character array.
	*/
	in_addr GetIP() ;//throw (CMMCException);

//	int GetPort() throw (CMMCException) ;

	/*! \fn int Close ()
	* \brief this function closes the socket.
	* \return	return - 0 on success, otherwise throws CMMCException or -1 is returned.
	*/
	int Close();
	
/*-------------------------------------------------------------------------
* new API for UDP class basically to comply with TCP API
*/

/**\!fn int Create (unsigned short usPort, SOCK_CLBK fnClbk=NULL, int iMsgMaxSize=512)
 * \brief creates UDP none blocking server (listener)
 * \param usPort port number to listen on (or to bind with)
 * \param fnClbk user call-back function. relevant only for call-back mode of operation.
 * \param iSock reference to socket file (descriptor)
 * \param iMsgMaxSize largest possible message (in bytes). relevant only for call-back mode of operation.
 * \return 0 on success, -1 otherwise. socket number (iSock) is update on success, otherwise -1;
 */
int Create (unsigned short usPort, SOCK_CLBK fnClbk=NULL, int iMsgMaxSize=512) throw (CMMCException);

/**\!fn int Receive (void * pData, unsigned short usSize, long lDelay, sockaddr_in* pSockaddr)
 * \brief receives UDP message pointed by pData.
 * \param pData (IN) pointer to buffer, which will store the received data.
 * \param usSize message size to read.
 * \param lDelay delay time. default is 0 (no delay)
 * \param pSockaddr pointer to socket address. default is NULL.
 * 		  On call-back mode it shell be delivered to Send by call-back function for synchronous matters.
 * \return number of read bytes, -1 otherwise.
 */
int Receive (void * pData, unsigned short usSize, long lDelay=0L, sockaddr_in* pSockaddr=NULL) throw (CMMCException);
/**\!fn int Send (void * pData, unsigned short usSize, sockaddr_in* pSockaddr)
 * \brief sends udp message pointed by pData.
 * \param pData (IN) pointer to data to send
 * \param usSize message size.
 * \param pSockaddr pointer to socket address. default is NULL.
 * 		  On call-back mode it may be pointed to the socket address with data from last receive.
 * \return number of bytes actually sent, -1 otherwise.
 */
int Send (void * pData, unsigned short usSize, sockaddr_in* pSockaddr=NULL) throw (CMMCException);
//int inline Connect(char * cIP, int iPort) {return Create(cIP, iPort);}
int Connect(char* szAddr, unsigned short usPort, bool& bWait, int iMsgMaxSize=512) throw (CMMCException);

/**! \fn int IsReady();
 * \brief checks for errors and whether or not UDP connection is ready for read operation.
 * return true if ready for read operation, otherwise false.
 */
int IsReady();

/**! \fn void SetMaxSize(int iSize);
* \brief overwrite default (512)  message size.
* \param iSize new message size.
* return none.
*/
void SetMaxSize(int iSize) {_iMsgMaxSize = (iSize>512 || iSize < 0)?512:iSize;}

/**! \fn bool IsWritable();
* \brief checks for errors and whether or not connection is ready for write operation.
* \param iSock client socket connection to check.
* return true if writable, otherwise false.
*/
bool IsWritable();

/**! \fn bool IsReadable(int iTimeOut=0);
 * \brief checks for errors and whether or not UDP connection is ready for read operation.
 * \param iTimeOut waiting time for checking. default behavior is not to wait.
 * return true if readable, otherwise false.
 */
bool IsReadable(int iTimeOut=0);

private:
	/**! \fn int IsPending(int iSock, bool& bFail)
	* \brief check pending connection on a non blocking socket
	*  actuall checks for errors and whether or not connection is ready for write operation.
	* \param iSock client socket connection to check.
	* \param bFail true if error(socket must be closed then), false otherwise.
	* \return: OK if connection complete / ERROR if fail or still pending
	*/
	int IsPending(int iSock) throw (CMMCException);

	/*! \fn int SetSocketTimeout(int  iMilliseconds)
	* \brief this function set socket to block only for iMilliseconds on receive operation.
	* \param iMilliseconds - timeout in ms to wait on receive.
	* \return	return - 0 on success, otherwise throws CMMCException or none zero error..
	*/
	int SetSocketTimeout(int iMilliseconds);
#ifndef WIN32
	friend void* _fnUDPClbkThread(void *);	//call-back argument for pthread_create within RunClbkThread.
#else
	friend DWORD WINAPI _fnUDPClbkThread( LPVOID lpParam );
#endif
	int RunClbkThread();					//launches the call-back thread for call-back mode of operation.
	void ClbkThread();						//the actual implementation of call-back mode of operation.

private:
	typedef void (CMMCUDP::*PCLBKTHREAD)(void *);
	PCLBKTHREAD _pThreadClbk;
	int _iSock;
	unsigned _usPort;
//	struct sockaddr_in m_sockAddrIn;	//old client convention
	struct sockaddr_in m_sockAddrOut;	//new client/server convention
	SOCK_CLBK _fnClbk;
    int _iMsgMaxSize;
    bool _bClbkThreadAlive;
#ifdef WIN32
	WSADATA m_wsaData;
	HANDLE  _thread;
#else
	pthread_t _thread;
#endif
};
#endif /* CMMCUDP_H_ */
