/*
============================================================================
 Name : AdsAmsUdpProtocolUdp.h
 Author : Haim H.
 Version : 15Jul2015
 Description :  Implement ADS / AMS Beckhoof protocol above UDP.
                GMAS implementation for be Server responce to ADS client.
				Udp services for ADS/AMS
				This services takes with very little change from MMCUDP
============================================================================
*/

#ifndef __AdsAmsUdpProtocolUdp_H__
#define __AdsAmsUdpProtocolUdp_H__


#define MMCUDP_MaxSize  512



      inline void SetMessageMaxSize(int iSize) {_iMsgMaxSize = iSize;}

  //  int GetPort() throw (CMMCException) ;

      /*! \fn int Close ()
      * \brief this function closes the socket.
      * \return   return - 0 on success, otherwise throws CMMCException or -1 is returned.
      */
      int Close();

  /**\!fn int CreateClbk (unsigned short usPort, int iMsgMaxSize=512)
   * \brief creates UDP none blocking server (listener)
   * \param usPort port number to listen on (or to bind with)
   * \param iMsgMaxSize largest possible message (in bytes). relevant only for call-back mode of operation.
   * \return 0 on success, -1 otherwise. socket number (iSock) is update on success, otherwise -1;
   */
  int CreateSocketfnClbk (unsigned short usPort, int iMsgMaxSize=512) throw (CMMCException);

  /**\!fn int Receive (void * pData, unsigned short usSize, long lDelay, sockaddr_in* pSockaddr)
   * \brief receives UDP message pointed by pData.
   * \param pData (IN) pointer to buffer, which will store the received data.
   * \param usSize message size to read.
   * \param lDelay delay time. default is 0 (no delay)
   * \param pSockaddr pointer to socket address. default is NULL.
   *        On call-back mode it shell be delivered to Send by call-back function for synchronous matters.
   * \return number of read bytes, -1 otherwise.
   */
  int Receive (void * pData, unsigned short usSize, long lDelay=0L, sockaddr_in* pSockaddr=NULL) throw (CMMCException);
  /**\!fn int Send (void * pData, unsigned short usSize, sockaddr_in* pSockaddr)
   * \brief sends udp message pointed by pData.
   * \param pData (IN) pointer to data to send
   * \param usSize message size.
   * \param pSockaddr pointer to socket address. default is NULL.
   *        On call-back mode it may be pointed to the socket address with data from last receive.
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
      * \return   return - 0 on success, otherwise throws CMMCException or none zero error..
      */
      int SetSocketTimeout(int iMilliseconds);
      friend void* fnUDPClbkThread(void *);   //call-back argument for pthread_create within RunClbkThread.
      int RunClbkThread();                    //launches the call-back thread for call-back mode of operation.
      void ClbkThread();                      //the actual implementation of call-back mode of operation.

  private:
//??      typedef void (CMMCUDP::*PCLBKTHREAD)(void *);
      typedef void (CMMCAdsAmsUdpProtocol::*PCLBKTHREAD)(void *);
      PCLBKTHREAD _pThreadClbk;
      int _iSock;
      unsigned _usPort;
  //  struct sockaddr_in m_sockAddrIn;    //old client convention
      struct sockaddr_in m_sockAddrOut;   //new client/server convention
      int _iMsgMaxSize;
      bool _bClbkThreadAlive;
      pthread_t _thread;

#endif	/* #ifndef __AdsAmsUdpProtocolUdp_H__ */

