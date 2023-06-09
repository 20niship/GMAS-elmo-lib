/*
============================================================================
 Name : AdsAmsUdpProtocol.h
 Author : Haim H.
 Version : 09Jul2015
 Description :  Implement ADS / AMS Beckhoof protocol above UDP.
                GMAS implementation for be Server responce to ADS client.
============================================================================
*/

#ifndef __AdsAmsUdpProtocol_h__
#define __AdsAmsUdpProtocol_h__

#ifndef WIN32

                    /* From MMCUDP ???? */
                    /* From MMCUDP ???? */
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/types.h>
#include <pthread.h>
#include <sys/ioctl.h>

#include "MMCPPGlobal.h"
#include "MMCSocket.h"
                    /* From MMCUDP ???? */



    #define DEF_UDP_MSG_MAX_SIZE            512
    #define UDP_SND_BUF_SIZE                DEF_UDP_MSG_MAX_SIZE

                    /* ADS/AMS Structure OFFSETS (interesting item offset within AMS stream) */
    #define AMS_HDR_NETID_TRG                0
    #define AMS_HDR_NETID_SRC                8
    #define AMS_HDR_PORT_TRG                 6
    #define AMS_HDR_PORT_SRC                14
    #define AMS_HDR_CMD                     16
    #define AMS_HDR_STATE                   18
    #define AMS_HDR_LEN                     20
    #define AMS_HDR_ERR_CODE                24
    #define AMS_HDR_INVOKE_ID               28
    
    #define AMSDATA_STR                     32
    #define AMSDATA_IDX_GRP                 (AMSDATA_STR+0)
    #define AMSDATA_IDX_OFST                (AMSDATA_STR+4)
    #define AMSDATA_REQ_LEN                 (AMSDATA_STR+8)
    
    #define AMSDATA_RESP_READ_LEN           (AMSDATA_STR+4)
    #define AMSDATA_RESP_READ_PURE_DATA     (AMSDATA_STR+8)
    
    #define AMSWRITE_DATA_STR               (AMSDATA_STR+12)

                    /* Define dump line length. Number of chars in one dump line (line length is more then  */
                    /* twice as: Space from begin of line, Hex, Space (betweens Hex to ascci) Asscii...     */
    #define ADS_AMS_BYTES_IN_DUMP_LINE      16
    


                    /* AMS ADS Command ID. Other commands are not defined or are used Beckhoff internally.  */
                    /* Therefore the Command Id  is only allowed to contain the above enumerated values!    */
                    /* Commad Id, type appearing both (exchange between) 'unsigned short'   */
                    /* and 'eCMDId' be carfull because enumerated type is 'int',            */
                    /* in ADS/AMS header the command appear in size of 'short'              */
    typedef enum CMDId_TAg
    {
        eCMDIdInvalid                    =0x0000,
        eCMDIdReadDeviceInfo             =0x0001,
        eCMDIdRead                       =0x0002,
        eCMDIdWrite                      =0x0003,
        eCMDIdReadState                  =0x0004,
        eCMDIdWriteControl               =0x0005,
        eCMDIdAddDeviceNotification      =0x0006,
        eCMDIdDeleteDeviceNotification   =0x0007,
        eCMDIdDeviceNotification         =0x0008,
        eCMDIdReadWrite                  =0x0009
    } eCMDId;


                    /* First data received by 'udp.Receive' */
    typedef struct ADS_AMS_HEADER_UDP_TAG
       {
           unsigned    char    cpAMSNetIdTarget[6];    	/* AMSNetId of the station, for which the packet is intended.   */
           unsigned    short   usAMSPortTarget;        	/* AMSPort of the station, for which the packet is intended.    */
           unsigned    char    cpAMSNetIdSource[6];    	/* AMSNetId of the station, from which the packet was sent.     */
           unsigned    short   usAMSPortSource;        	/* AMSPort of the station, from which the packet was sent.      */
       
           unsigned    short   usCommandId;                
           unsigned    short   usStateFlags;
           unsigned    int     uiHdrLen;				/* Size of the data range. The unit is byte.                    */
           unsigned    int     uiErrorCode;            	/* AMS error number                                             */
           unsigned    int     uiInvokeId;             	/* Free usable 32 bit array. Usually this array serves to send  */
														/* an Id. This Id makes is possible to assign a received        */
														/* response to a request, which was sent before                 */
       } ADS_AMS_HEADER_UDP;

    

                    /* Type of function the class calls for get user data as*/
                    /* response to Client requst Read data from Server      */
    typedef int (* ADSAMS_CLBK_REQ_READ)(unsigned char      ucDataToClient[],
                                         unsigned int       uiDataToClientSize,
                                         unsigned int       uiIndexGroup,
                                         unsigned int       uiIndexOffset,
                                         unsigned int*      puiResult,
                                         ADS_AMS_HEADER_UDP*    ptAmsHdrFromClient,     /* Copy of the org.         */
                                         ADS_AMS_HEADER_UDP**   pptAmsHdrToClient);     /* If Null take from Rcv    */

                    /* Type of function the class calls for serve client    */
                    /* requsted Write data to server (client sends data)    */
    typedef int (* ADSAMS_CLBK_REQ_WRITE)(unsigned char     ucDataFromClient[],
                                         unsigned int       uiDataFromClientSize,
                                         unsigned int       uiIndexGroup,
                                         unsigned int       uiIndexOffset,
                                         unsigned int*      puiResult,
                                         ADS_AMS_HEADER_UDP*    ptAmsHdrFromClient,     /* Copy of the org.         */
                                         ADS_AMS_HEADER_UDP**   pptAmsHdrToClient);     /* If Null take from Rcv    */ 


                    /* Macros for GET/PUT data from/into stream.        */
                    /* Also change from Little-Endian to Big-Endian.    */
                                                        /* See: GNU "Statement Expressions" */
    #define GET_USHORT(ucStream, offSetOnStream)                            \
            ({                                                              \
                unsigned short       us1;                                   \
                unsigned short       us0;                                   \
                us1 = (unsigned short)ucStream[offSetOnStream + 1] << 8;    \
                us0 = (unsigned short)ucStream[offSetOnStream + 0] << 0;    \
                                    /* Macro return value */                \
                us0 + us1;                                                  \
            })                                                              \

                                                        /* See: GNU "Statement Expressions" */
    #define GET_USINT(ucStream, offSetOnStream)                             \
            ({                                                              \
                unsigned int         ui3;                                   \
                unsigned int         ui2;                                   \
                unsigned int         ui1;                                   \
                unsigned int         ui0;                                   \
                ui3 = (unsigned short)ucStream[offSetOnStream + 3] << 24;   \
                ui2 = (unsigned short)ucStream[offSetOnStream + 2] << 16;   \
                ui1 = (unsigned short)ucStream[offSetOnStream + 1] <<  8;   \
                ui0 = (unsigned short)ucStream[offSetOnStream + 0] <<  0;   \
                                    /* Macro return value */                \
                ui0 + ui1 + ui2 + ui3;                                      \
            })                                                              \


    #define PUT_USHORT(ucStream, offSetOnStream, usVal)                     \
            ({                                                              \
                unsigned char        uc1;                                   \
                unsigned char        uc0;                                   \
                uc1 = (unsigned char)((usVal >> 8) & 0xff);                 \
                uc0 = (unsigned char)((usVal >> 0) & 0xff);                 \
                ucStream[offSetOnStream + 1] = uc1;                         \
                ucStream[offSetOnStream + 0] = uc0;                         \
            })                                                              \


    #define PUT_USINT(ucStream, offSetOnStream, uiVal)                      \
            ({                                                              \
                unsigned char        uc3;                                   \
                unsigned char        uc2;                                   \
                unsigned char        uc1;                                   \
                unsigned char        uc0;                                   \
                uc3 = (unsigned char)((uiVal >> 24) & 0xff);                \
                uc2 = (unsigned char)((uiVal >> 16) & 0xff);                \
                uc1 = (unsigned char)((uiVal >>  8) & 0xff);                \
                uc0 = (unsigned char)((uiVal >>  0) & 0xff);                \
                ucStream[offSetOnStream + 3] = uc3;                         \
                ucStream[offSetOnStream + 2] = uc2;                         \
                ucStream[offSetOnStream + 1] = uc1;                         \
                ucStream[offSetOnStream + 0] = uc0;                         \
            })                                                              \




                            /* Implement ADS/AMS READ,WRITE protocol    */
    class DLLMMCPP_API CMMCAdsAmsUdpProtocol
    {
    public:
        CMMCAdsAmsUdpProtocol()
        {
            _giDbgLclFlag = 0;
            _giDbgCommuFlag = 0;

            /* From MMCUDP ???? */
            _iSock=-1;
            /* From MMCUDP ???? */
        };

        ~ CMMCAdsAmsUdpProtocol()
        {
            /* From MMCUDP ???? */
            if (_iSock!=-1)
                close(_iSock);
            _bClbkThreadAlive = false;
            /* From MMCUDP ???? */
        };


                            /* Application Initialize (connection to ADS/AMS) supplay:  */
                            /*  port number,                                            */
                            /*  ClientReqRead - call back function, response to Client  */
                            /*          requst Read Data from server.                   */
                            /*  ClientReqWrite - Call back function, response to Client */
                            /*          requst Write Data to server.                    */
        int     CMMCAdsAmsUdpProtocolInit(unsigned short usPort,
                                          ADSAMS_CLBK_REQ_READ  fnClbkRespClientReqRead,
                                          ADSAMS_CLBK_REQ_WRITE fnClbkClientReqWrite);

                            /* Dbg Service, when iDbgCommuFlag != 0 print communication */
        void    AdsAmsSetDbg        (int iDbgLclFlag, int iDbgCommuFlag);
                           /* Dbg service, print string in Hex & Ascii format           */
        void    DumpStreamBuffer    (unsigned char pucStrStream[], unsigned int uiNumCharForPrint);


        /* Orginal takes From MMCUDP ???? */
        /* Orginal takes From MMCUDP ???? */
                            /* Udp services for ADS/AMS                                 */
                            /* This services takes with very little change from MMCUDP  */
#include "AdsAmsUdpProtocolUdp.h"
        /* Orginal takes From MMCUDP ???? */
        /* Orginal takes From MMCUDP ???? */

    private:
        int     DecodeAmsHeader     (unsigned char ucStrStream[]);
        int     DecodeGrpOffsetLen  (unsigned char ucStrStream[]);
        int     ResponseClientReq     (eCMDId    CmdId, unsigned char ucRcvBuf[], unsigned int uiRcvBufSize, unsigned char ucSndBuf[], unsigned short* pusRespSize);
                                            /* Call from thread while soket receive data */
        int     SocketfnClbk        (int iSock, short sSockEvent, unsigned char pucReadBuf[], int iReadBufSize, ...);

                                            /* Buffers for UDP Send communication to client */
        unsigned char   _gucUdpSndBuf[UDP_SND_BUF_SIZE];
                                            /* Commad Id, type appear both (exchange between) 'unsigned short'  */
                                            /* and 'eCMDId' be carfull because enumerated type is 'int'.        */
        unsigned short  _gusRcvCommandId;
                        /* From Client point of view                    */
                        /* Rcv => GMAS got the command (read/write...)  */
        unsigned short  _gusRcvPortTarget;  /* Target port  */
        unsigned short  _gusRcvPortSource;  /* Source port  */ 
        unsigned short  _gusRcvStateFlags;  /* State Flags  */
        unsigned int    _guiRcvHdrLen;      /* Whole range of 'DATA AREA', E.g.: Including: IndexGroup, InexOffset, Length and "Pure Data" */
        unsigned int    _guiRcvErrorCode;   /* Error Code   */
        unsigned int    _guiRcvInvokeId;    /* Invoke Id.   */
        
                        /* From Last relevant Rcv Command */
        unsigned int    _guiIndexGroup;     /* Index Group of the data which should be written.     */
        unsigned int    _guiIndexOffset;    /* Index Offset, in which the data should be written.   */
        
                                            /* Length of the data (in bytes) which are written.     */ 
                                            /*   "pure data within data area" Not Including         */
                                            /*   IndexGroup, InexOffset, Length.... E.g. when pure  */
                                            /*   data is 'a' this field be 1.                       */
        unsigned int    _guiPureDataLen;


        int             _giSizeRcv;
        int             _giSizeForSnd;

                                            /* Pointer to user function call in responce to Client  */
                                            /* requst Read (return roud data from server to client).*/
        ADSAMS_CLBK_REQ_READ   _fnClbkRespClientReqRead;
                                            /* Pointer to user function call while Client requst    */
                                            /* Write (return client data to server).                */
        ADSAMS_CLBK_REQ_WRITE  _fnClbkClientReqWrite;
                                            /* Trace & debug flags                                  */
        int                     _giDbgLclFlag;
        int                     _giDbgCommuFlag;
    };
#endif  /* #ifndef WIN32 */

#endif  /* #define __AdsAmsUdpProtocol_h__ */

