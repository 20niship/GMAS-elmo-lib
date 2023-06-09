////////////////////////////////////////////////////////////////////////////////
/// \file MMC_network_API.h
/// Name        : MMC_network_API.h
/// Author      : Barak R
/// Created on	: April 19, 20010
/// Version     : 0.0.1
/// Copyright   : Your copyright notice
/// Description : This file contain definitions for ...
////////////////////////////////////////////////////////////////////////////////

#ifndef MMC_NETWORK_API_H_
#define MMC_NETWORK_API_H_

//moving to g++ @YL 4-10-2010
#ifdef __cplusplus
 extern "C" {
#endif

#define CAN_ID_MAX							128		///< Maximal number CAN ID's
///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_SET_SERVERIP_IN
/// \brief Set Server IP address input data structure.
///////////////////////////////////////////////////////////////////////////////
typedef struct {
	unsigned char cFirst; ///< First number of IP address
	unsigned char cSecond; ///< Second number of IP address
	unsigned char cThird; ///< Third number of IP address
	unsigned char cFourth; ///< Fourth number of IP address
} MMC_SET_SERVERIP_IN;

///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_SET_SERVERIP_OUT
/// \brief Set Server IP address output data structure.
///////////////////////////////////////////////////////////////////////////////
typedef struct {
	unsigned short usStatus; ///< Returned command status.
	short usErrorID; ///< Returned command error ID.
} MMC_SET_SERVERIP_OUT;

///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_GET_SERVERIP_IN
/// \brief Get Server IP address input data structure.
///////////////////////////////////////////////////////////////////////////////
typedef struct {
	unsigned char dummy;
} MMC_GET_SERVERIP_IN;

///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_GET_SERVERIP_OUT
/// \brief Get Server IP address output data structure.
///////////////////////////////////////////////////////////////////////////////
typedef struct {
	int iPort ;
	unsigned short usStatus; ///< Returned command status.
	short usErrorID; ///< Returned command error ID.
	char cFirst; ///< First number of IP address
	char cSecond; ///< Second number of IP address
	char cThird; ///< Third number of IP address
	char cFourth; ///< Fourth number of IP address
} MMC_GET_SERVERIP_OUT;

///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_OPENUDPCHANNEL_IN
/// \brief
///////////////////////////////////////////////////////////////////////////////
typedef struct {
	int iEventsMask;
	int iPort;
	char cFirst;
	char cSecond;
	char cThird;
	char cFourth;
} MMC_OPENUDPCHANNEL_IN;

///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_OPENUDPCHANNEL_OUT
/// \brief
///////////////////////////////////////////////////////////////////////////////
typedef struct {
	unsigned short usStatus;
	short usErrorID;
} MMC_OPENUDPCHANNEL_OUT;

///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_CLOSEUDPCHANNEL_IN
/// \brief
///////////////////////////////////////////////////////////////////////////////
typedef struct {
	unsigned char dummy;
} MMC_CLOSEUDPCHANNEL_IN;

///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_CLOSEUDPCHANNEL_OUT
/// \brief
///////////////////////////////////////////////////////////////////////////////
typedef struct {
	unsigned short usStatus;
	short usErrorID;
} MMC_CLOSEUDPCHANNEL_OUT;

///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_NETWORKSCAN_IN
/// \brief
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
	unsigned char dummy;
}MMC_NETWORKSCAN_IN;

///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_NETWORKSCAN_OUT
/// \brief
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
	unsigned short usStatus;
	short usErrorID;
}MMC_NETWORKSCAN_OUT;

///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_NODESINFO
/// \brief
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
	unsigned int uiNodeType;
	unsigned char ucNodeID;
	unsigned char ucCommType;	
	unsigned char ucNodeState;
	unsigned char dummy;
}MMC_NODESINFO;

///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_SET_DHCP_IN
/// \brief Set DHCP input data structure.
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
	unsigned char ucMode;
}MMC_SET_DHCP_IN;

///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_SET_DHCP_OUT
/// \brief Set DHCP output data structure.
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
	unsigned short usStatus;	///< Returned command status.
	short usErrorID;	///< Returned command error ID.
}MMC_SET_DHCP_OUT;

///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_GET_DHCP_IN
/// \brief Get DHCP input data structure.
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
	unsigned char dummy;
}MMC_GET_DHCP_IN;

///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_GET_DHCP_OUT
/// \brief Get DHCP output data structure.
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
	unsigned short usStatus;	///< Returned command status.
	short usErrorID;	///< Returned command error ID.
	unsigned char ucMode;
}MMC_GET_DHCP_OUT;

///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_SET_IP_ADDRESS_IN
/// \brief Set IP address input data structure.
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
	char cFirst;	///< First number of IP address
	char cSecond;	///< Second number of IP address
	char cThird;	///< Third number of IP address
	char cFourth;	///< Fourth number of IP address
}MMC_SET_IP_ADDRESS_IN;

///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_SET_IP_ADDRESS_OUT
/// \brief Set IP address output data structure.
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
	unsigned short usStatus;	///< Returned command status.
	short usErrorID;	///< Returned command error ID.
}MMC_SET_IP_ADDRESS_OUT;


///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_GET_IP_ADDRESS_IN
/// \brief Get IP address input data structure.
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
	unsigned char dummy;
}MMC_GET_IP_ADDRESS_IN;

///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_GET_IP_ADDRESS_OUT
/// \brief Get IP address output data structure.
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
	unsigned short usStatus;	///< Returned command status.
	short usErrorID;	///< Returned command error ID.
	char cFirst;				///< First number of IP address
	char cSecond;				///< Second number of IP address
	char cThird;				///< Third number of IP address
	char cFourth;				///< Fourth number of IP address
}MMC_GET_IP_ADDRESS_OUT;


///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_SET_IP_MASK_IN
/// \brief Set IP mask input data structure.
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
	char cFirst;	///< First number of IP mask
	char cSecond;	///< Second number of IP mask
	char cThird;	///< Third number of IP mask
	char cFourth;	///< Fourth number of IP mask
}MMC_SET_IP_MASK_IN;

///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_SET_IP_MASK_OUT
/// \brief Set IP mask output data structure.
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
	unsigned short usStatus;	///< Returned command status.
	short usErrorID;	///< Returned command error ID.
}MMC_SET_IP_MASK_OUT;


///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_GET_IP_MASK_OUT
/// \brief Get IP mask input data structure.
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
	unsigned char dummy;
}MMC_GET_IP_MASK_IN;

///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_GET_IP_MASK_OUT
/// \brief Get IP mask output data structure.
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
	unsigned short usStatus;	///< Returned command status.
	short usErrorID;	///< Returned command error ID.
	char cFirst;				///< First number of IP mask
	char cSecond;				///< Second number of IP mask
	char cThird;				///< Third number of IP mask
	char cFourth;				///< Fourth number of IP mask
}MMC_GET_IP_MASK_OUT;


///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_SET_DEFGATEWAY_IN
/// \brief Set Default Gateway IP address input data structure.
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
	char cFirst;				///< First number of IP address
	char cSecond;				///< Second number of IP address
	char cThird;				///< Third number of IP address
	char cFourth;				///< Fourth number of IP address
}MMC_SET_DEFGATEWAY_IN;

///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_SET_DEFGATEWAY_OUT
/// \brief Set Default Gateway IP address output data structure.
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
	unsigned short usStatus;	///< Returned command status.
	short usErrorID;	///< Returned command error ID.
}MMC_SET_DEFGATEWAY_OUT;


///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_GET_DEFGATEWAY_IN
/// \brief Get Gateway IP address input data structure.
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
	unsigned char dummy;
}MMC_GET_DEFGATEWAY_IN;

///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_GET_DEFGATEWAY_OUT
/// \brief Get Gateway IP address output data structure.
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
	unsigned short usStatus;	///< Returned command status.
	short usErrorID;	///< Returned command error ID.
	unsigned char cFirst;				///< First number of IP address
	unsigned char cSecond;				///< Second number of IP address
	unsigned char cThird;				///< Third number of IP address
	unsigned char cFourth;				///< Fourth number of IP address
}MMC_GET_DEFGATEWAY_OUT;

///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_NETWORKINFO_IN
/// \brief
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
	unsigned char dummy;
}MMC_NETWORKINFO_IN;

///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_NETWORKINFO_OUT
/// \brief
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
	int iBusType;
	int iBusBaud;
	int iNumOfActiveNodes;
	int iNumOfResFileNodes;
	unsigned short usStatus;
	short usErrorID;
	MMC_NODESINFO stNodesInfo[CAN_ID_MAX - 1];
}MMC_NETWORKINFO_OUT;


/// Node - Types:
/// -------------
enum
{
    eMMC_NODE_TYPE_NONE = 0,
    eMMC_NODE_TYPE_BASOON,
    eMMC_NODE_TYPE_LAST
};

/// Node - States:
/// --------------
enum
{
	eMMC_NODE_STATE_ENABLED = 0,
	eMMC_NODE_STATE_DISABLED,
    eMMC_NODE_STATE_UNKNOWN,
    eMMC_NODE_STATE_LAST
};

/// functions


////////////////////////////////////////////////////////////////////////////////
/// \fn int  MMC_GetServerIpCmd(
///				IN MMC_CONNECT_HNDL hConn,
///				IN MMC_GET_SERVERIP_IN* pInParam,
///				OUT MMC_GET_SERVERIP_OUT* pOutParam)
/// \brief This function read server IP address.
/// \param  hConn - [IN] Connection handle
/// \param  pInParam - [IN] Pointer to Get Server IP Address input parameters
/// \param  pOutParam - [OUT] Pointer to Get Server IP Address output parameters
/// \return	return - 0 if success
/// 				 error_id in case of error
////////////////////////////////////////////////////////////////////////////////
MMC_LIB_API int MMC_GetServerIpCmd(
		IN MMC_CONNECT_HNDL hConn,
		IN MMC_GET_SERVERIP_IN* pInParam,
		OUT MMC_GET_SERVERIP_OUT* pOutParam);

////////////////////////////////////////////////////////////////////////////////
/// \fn int MMC_OpenUdpChannelCmd(
///				IN MMC_CONNECT_HNDL hConn,
///				IN MMC_OPENUDPCHANNEL_IN* pInParam,
///				OUT MMC_OPENUDPCHANNEL_OUT* pOutParam)
/// \brief The function opens UDP connection per RPC/IPC connection.
/// Please note - the UDP port is already assigned in the InitConnection Function
/// \param  hConn - [IN] Connection handle
/// \param  pInParam - [IN] Pointer to Open UDP Channel input parameters
/// \param  pOutParam - [OUT] Pointer to Open UDP Channel output parameters
/// \return	return - 0 if success
/// 				 error_id in case of error
////////////////////////////////////////////////////////////////////////////////
MMC_LIB_API int MMC_OpenUdpChannelCmd(
		IN MMC_CONNECT_HNDL hConn,
		IN MMC_OPENUDPCHANNEL_IN* pInParam,
		OUT MMC_OPENUDPCHANNEL_OUT* pOutParam);


////////////////////////////////////////////////////////////////////////////////
/// \fn int MMC_OpenUdpChannelCmdEx(
///				IN MMC_CONNECT_HNDL hConn,
///				IN MMC_OPENUDPCHANNEL_IN* pInParam,
///				OUT MMC_OPENUDPCHANNEL_OUT* pOutParam)
/// \brief The function opens UDP connection per RPC/IPC connection.
/// Please note - the UDP port is already assigned in the InitConnection Function
/// \param  hConn - [IN] Connection handle
/// \param  pInParam - [IN] Pointer to Open UDP Channel input parameters
/// \param  pOutParam - [OUT] Pointer to Open UDP Channel output parameters
/// \return	return - 0 if success
/// 				 error_id in case of error
////////////////////////////////////////////////////////////////////////////////
MMC_LIB_API int MMC_OpenUdpChannelCmdEx(
	IN MMC_CONNECT_HNDL hConn,
	IN MMC_OPENUDPCHANNEL_IN* pInParam,
	OUT MMC_OPENUDPCHANNEL_OUT* pOutParam);

////////////////////////////////////////////////////////////////////////////////
/// \fn int MMC_CloseUdpChannelCmd(
///				IN MMC_CONNECT_HNDL hConn,
///				IN MMC_CLOSEUDPCHANNEL_IN* pInParam,
///				OUT MMC_CLOSEUDPCHANNEL_OUT* pOutParam)
/// \brief The function closes UDP connection per RPC/IPC connection.
/// \param  hConn - [IN] Connection handle
/// \param  pInParam - [IN] Pointer to Close UDP Channel input parameters
/// \param  pOutParam - [OUT] Pointer to Close UDP Channel output parameters
/// \return	return - 0 if success
/// 				 error_id in case of error
////////////////////////////////////////////////////////////////////////////////
MMC_LIB_API int MMC_CloseUdpChannelCmd(
		IN MMC_CONNECT_HNDL hConn,
		IN MMC_CLOSEUDPCHANNEL_IN* pInParam,
		OUT MMC_CLOSEUDPCHANNEL_OUT* pOutParam);


////////////////////////////////////////////////////////////////////////////////
/// \fn int  MMC_SetDhcpCmd(
///				IN MMC_CONNECT_HNDL hConn,
///				IN MMC_SET_DHCP_IN* pInParam,
///				OUT MMC_SET_DHCP_OUT* pOutParam)
/// \brief This function set DHCP Mode.
/// \param  hConn - [IN] Connection handle
/// \param  pInParam - [IN] Pointer to Set DHCP input parameters
/// \param  pOutParam - [OUT] Pointer to Set DHCP output parameters
/// \return	return - 0 if success
/// 				 error_id in case of error
////////////////////////////////////////////////////////////////////////////////
int MMC_SetDhcpCmd(
		IN MMC_CONNECT_HNDL hConn,
		IN MMC_SET_DHCP_IN* pInParam,
		OUT MMC_SET_DHCP_OUT* pOutParam);

////////////////////////////////////////////////////////////////////////////////
/// \fn int  MMC_GetDhcpCmd(
///				IN MMC_CONNECT_HNDL hConn,
///				IN MMC_GET_DHCP_IN* pInParam,
///				OUT MMC_GET_DHCP_OUT* pOutParam)
/// \brief This function read DHCP Mode.
/// \param  hConn - [IN] Connection handle
/// \param  pInParam - [IN] Pointer to Get DHCP input parameters
/// \param  pOutParam - [OUT] Pointer to Get DHCP output parameters
/// \return	return - 0 if success
/// 				 error_id in case of error
////////////////////////////////////////////////////////////////////////////////
MMC_LIB_API int MMC_GetDhcpCmd(
		IN MMC_CONNECT_HNDL hConn,
		IN MMC_GET_DHCP_IN* pInParam,
		OUT MMC_GET_DHCP_OUT* pOutParam);

////////////////////////////////////////////////////////////////////////////////
/// \fn int  MMC_SetIpAddrCmd(
///				IN MMC_CONNECT_HNDL hConn,
///				IN MMC_SET_IP_ADDRESS_IN* pInParam,
///				OUT MMC_SET_IP_ADDRESS_OUT* pOutParam)
/// \brief This function set IP address.
/// \param  hConn - [IN] Connection handle
/// \param  pInParam - [IN] Pointer to Set IP Address input parameters
/// \param  pOutParam - [OUT] Pointer to Set IP Address output parameters
/// \return	return - 0 if success
/// 				 error_id in case of error
////////////////////////////////////////////////////////////////////////////////
int MMC_SetIpAddrCmd(
		IN MMC_CONNECT_HNDL hConn,
		IN MMC_SET_IP_ADDRESS_IN* pInParam,
		OUT MMC_SET_IP_ADDRESS_OUT* pOutParam);

////////////////////////////////////////////////////////////////////////////////
/// \fn int  MMC_GetIpAddrCmd(
///				IN MMC_CONNECT_HNDL hConn,
///				IN MMC_GET_IP_ADDRESS_IN* pInParam,
///				OUT MMC_GET_IP_ADDRESS_OUT* pOutParam)
/// \brief This function read IP address.
/// \param  hConn - [IN] Connection handle
/// \param  pInParam - [IN] Pointer to Get IP Address input parameters
/// \param  pOutParam - [OUT] Pointer to Get IP Address output parameters
/// \return	return - 0 if success
/// 				 error_id in case of error
////////////////////////////////////////////////////////////////////////////////
MMC_LIB_API int MMC_GetIpAddrCmd(
		IN MMC_CONNECT_HNDL hConn,
		IN MMC_GET_IP_ADDRESS_IN* pInParam,
		OUT MMC_GET_IP_ADDRESS_OUT* pOutParam);

////////////////////////////////////////////////////////////////////////////////
/// \fn int  MMC_SetIpMaskCmd(
///				IN MMC_CONNECT_HNDL hConn,
///				IN MMC_SET_IP_MASK_IN* pInParam,
///				OUT MMC_SET_IP_MASK_OUT* pOutParam)
/// \brief This function set IP mask.
/// \param  hConn - [IN] Connection handle
/// \param  pInParam - [IN] Pointer to Set IP Mask input parameters
/// \param  pOutParam - [OUT] Pointer to Set IP Mask output parameters
/// \return	return - 0 if success
/// 				 error_id in case of error
////////////////////////////////////////////////////////////////////////////////
int MMC_SetIpMaskCmd(
		IN MMC_CONNECT_HNDL hConn,
		IN MMC_SET_IP_MASK_IN* pInParam,
		OUT MMC_SET_IP_MASK_OUT* pOutParam);

////////////////////////////////////////////////////////////////////////////////
/// \fn int  MMC_GetIpMaskCmd(
///				IN MMC_CONNECT_HNDL hConn,
///				IN MMC_GET_IP_MASK_IN* pInParam,
///				OUT MMC_GET_IP_MASK_OUT* pOutParam)
/// \brief This function read IP mask.
/// \param  hConn - [IN] Connection handle
/// \param  pInParam - [IN] Pointer to Get IP Mask input parameters
/// \param  pOutParam - [OUT] Pointer to Get IP Mask output parameters
/// \return	return - 0 if success
/// 				 error_id in case of error
////////////////////////////////////////////////////////////////////////////////
MMC_LIB_API int MMC_GetIpMaskCmd(
		IN MMC_CONNECT_HNDL hConn,
		IN MMC_GET_IP_MASK_IN* pInParam,
		OUT MMC_GET_IP_MASK_OUT* pOutParam);

////////////////////////////////////////////////////////////////////////////////
/// \fn int  MMC_SetDefGatewayCmd(
///				IN MMC_CONNECT_HNDL hConn,
///				IN MMC_SET_DEFGATEWAY_IN* pInParam,
///				OUT MMC_SET_DEFGATEWAY_OUT* pOutParam)
/// \brief This function set default gateway IP address.
/// \param  hConn - [IN] Connection handle
/// \param  pInParam - [IN] Pointer to Set Default Gateway IP Address input parameters
/// \param  pOutParam - [OUT] Pointer to Set Default gateway IP Address output parameters
/// \return	return - 0 if success
/// 				 error_id in case of error
////////////////////////////////////////////////////////////////////////////////
int MMC_SetDefGatewayCmd(
		IN MMC_CONNECT_HNDL hConn,
		IN MMC_SET_DEFGATEWAY_IN* pInParam,
		OUT MMC_SET_DEFGATEWAY_OUT* pOutParam);

////////////////////////////////////////////////////////////////////////////////
/// \fn int  MMC_GetDefGatewayCmd(
///				IN MMC_CONNECT_HNDL hConn,
///				IN MMC_GET_DEFGATEWAY_IN* pInParam,
///				OUT MMC_GET_DEFGATEWAY_OUT* pOutParam)
/// \brief This function read default gateway IP address.
/// \param  hConn - [IN] Connection handle
/// \param  pInParam - [IN] Pointer to Get Default Gateway IP Address input parameters
/// \param  pOutParam - [OUT] Pointer to Get Default Gateway IP Address output parameters
/// \return	return - 0 if success
/// 				 error_id in case of error
////////////////////////////////////////////////////////////////////////////////
MMC_LIB_API int MMC_GetDefGatewayCmd(
		IN MMC_CONNECT_HNDL hConn,
		IN MMC_GET_DEFGATEWAY_IN* pInParam,
		OUT MMC_GET_DEFGATEWAY_OUT* pOutParam);

////////////////////////////////////////////////////////////////////////////////
/// \fn int  MMC_SetServerIpCmd(
///				IN MMC_CONNECT_HNDL hConn,
///				IN MMC_SET_SERVERIP_IN* pInParam,
///				OUT MMC_SET_SERVERIP_OUT* pOutParam)
/// \brief This function set server IP address.
/// \param  hConn - [IN] Connection handle
/// \param  pInParam - [IN] Pointer to Set Server IP Address input parameters
/// \param  pOutParam - [OUT] Pointer to Set Server IP Address output parameters
/// \return	return - 0 if success
/// 				 error_id in case of error
////////////////////////////////////////////////////////////////////////////////
MMC_LIB_API int MMC_SetServerIpCmd(
		IN MMC_CONNECT_HNDL hConn,
		IN MMC_SET_SERVERIP_IN* pInParam,
		OUT MMC_SET_SERVERIP_OUT* pOutParam);

////////////////////////////////////////////////////////////////////////////////
/// \fn int MMC_NetworkScanCmd(
///				IN MMC_CONNECT_HNDL hConn,
///				IN MMC_NETWORKSCAN_IN* pInParam,
///				OUT MMC_NETWORKSCAN_OUT* pOutParam)
/// \brief The function scans the network, to see which nodes are on the network.
/// \param  hConn - [IN] Connection handle
/// \param  pInParam - [IN] Pointer to Network Scan input parameters
/// \param  pOutParam - [OUT] Pointer to Network Scan output parameters
/// \return	return - 0 if success
/// 				 error_id in case of error
////////////////////////////////////////////////////////////////////////////////
MMC_LIB_API int MMC_NetworkScanCmd(
		IN MMC_CONNECT_HNDL hConn,
		IN MMC_NETWORKSCAN_IN* pInParam,
		OUT MMC_NETWORKSCAN_OUT* pOutParam);

////////////////////////////////////////////////////////////////////////////////
/// \fn int MMC_NetworkInfoCmd(
///				IN MMC_CONNECT_HNDL hConn,
///				IN MMC_NETWORKINFO_IN* pInParam,
///				OUT MMC_NETWORKINFO_OUT* pOutParam)
/// \brief The function returns network information. who is connected / defined  in resources.
/// \param  hConn - [IN] Connection handle
/// \param  pInParam - [IN] Pointer to Network Scan input parameters
/// \param  pOutParam - [OUT] Pointer to Network Scan output parameters
/// \return	return - 0 if success
/// 				 error_id in case of error
////////////////////////////////////////////////////////////////////////////////
MMC_LIB_API int MMC_NetworkInfoCmd(
		IN MMC_CONNECT_HNDL hConn,
		IN MMC_NETWORKINFO_IN* pInParam,
		OUT MMC_NETWORKINFO_OUT* pOutParam);

//moving to g++ @YL 4-10-2010
#ifdef __cplusplus
}
#endif

#endif /* MMC_NETWORK_API_H_ */
