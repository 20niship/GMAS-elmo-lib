////////////////////////////////////////////////////////////////////////////////
/// \file MMC_DS401_API.h
/// Name        : MMC_DS401_API.h
/// Author      : Barak R
/// Created on	: April 19, 20010
/// Version     : 0.0.1
/// Copyright   : Your copyright notice
/// Description : This file contain definitions for ...
////////////////////////////////////////////////////////////////////////////////

#ifndef MMC_DS401_API_H
#define MMC_DS401_API_H
//
//moving to g++ @YL 4-10-2010
#ifdef __cplusplus
 extern "C" {
#endif
#include <sys/types.h>
#ifndef WIN32
#include <unistd.h>
#endif

typedef struct
{
	unsigned char ucGroupIndex;
}MMC_READDIGROUP_IN;

typedef struct
{
	unsigned short usStatus;
	short usErrorID;
}MMC_READDIGROUP_OUT;

typedef struct
{
	unsigned char ucGroupIndex;
	unsigned char ucVal;
}MMC_WRITEDOGROUP_IN;

typedef struct
{
	unsigned short usStatus;
	short usErrorID;
}MMC_WRITEDOGROUP_OUT;

typedef struct
{
	unsigned char ucDummy;
}MMC_ENABLEDICHANGEDEVENT_IN;

typedef struct
{
	unsigned short usStatus;
	short usErrorID;
}MMC_ENABLEDICHANGEDEVENT_OUT;

typedef struct
{
	unsigned char ucDummy;
}MMC_DISABLEDICHANGEDEVENT_IN;

typedef struct
{
	unsigned short usStatus;
	short usErrorID;
}MMC_DISABLEDICHANGEDEVENT_OUT;

typedef struct
{
	unsigned char dummy;
}MMC_READDI_IN;

typedef struct
{
#ifdef WIN32
	unsigned __int64	ulliDI;
#else
	unsigned long long int			ulliDI;
#endif
	unsigned short usStatus;
	short usErrorID;
}MMC_READDI_OUT;

typedef struct
{
#ifdef WIN32
	unsigned __int64	ulliDO;
#else
	unsigned long long int			ulliDO;
#endif
}MMC_WRITEDO_IN;

typedef struct
{
	unsigned short usStatus;
	short usErrorID;
}MMC_WRITEDO_OUT;

typedef struct
{
	unsigned char ucEventType;
	unsigned char ucPDOCommParam;
	unsigned char ucPDOLength;
}MMC_CONFIGGENERALRPDO3_IN;

typedef struct
{
	unsigned short usStatus;
	short usErrorID;
}MMC_CONFIGGENERALRPDO3_OUT;

typedef struct
{
    unsigned char ucEventType;
    unsigned char ucPDOCommParam;
	unsigned char ucPDOLength;
}MMC_CONFIGGENERALRPDO4_IN;

typedef struct
{
    unsigned short usStatus;
    short usErrorID;
}MMC_CONFIGGENERALRPDO4_OUT;

typedef struct
{
    unsigned char ucDummy;
}MMC_CANCELGENERALRPDO3_IN;

typedef struct
{
    unsigned short usStatus;
    short usErrorID;
}MMC_CANCELGENERALRPDO3_OUT;

typedef struct
{
    unsigned char ucDummy;
}MMC_CANCELGENERALRPDO4_IN;

typedef struct
{
    unsigned short usStatus;
    short usErrorID;
}MMC_CANCELGENERALRPDO4_OUT;

typedef struct
{
    unsigned char ucEventType;
}MMC_CONFIGGENERALTPDO3_IN;

typedef struct
{
    unsigned short usStatus;
    short usErrorID;
}MMC_CONFIGGENERALTPDO3_OUT;

typedef struct
{
    unsigned char ucEventType;
}MMC_CONFIGGENERALTPDO4_IN;

typedef struct
{
    unsigned short usStatus;
    short usErrorID;
}MMC_CONFIGGENERALTPDO4_OUT;

typedef struct
{
    unsigned char ucDummy;
}MMC_CANCELGENERALTPDO3_IN;

typedef struct
{
    unsigned short usStatus;
    short usErrorID;
}MMC_CANCELGENERALTPDO3_OUT;

typedef struct
{
    unsigned char ucDummy;
}MMC_CANCELGENERALTPDO4_IN;

typedef struct
{
    unsigned short usStatus;
    short usErrorID;
}MMC_CANCELGENERALTPDO4_OUT;

////////////////////////////////////////////////////////////////////////////////
/// \fn int MMC_ReadDIGroup(
///				IN MMC_CONNECT_HNDL hConn,
///				IN MMC_AXIS_REF_HNDL hAxisRef,
///				IN MMC_READDIGROUP_IN* pInParam,
///				OUT MMC_READDIGROUP_OUT* pOutParam)
////////////////////////////////////////////////////////////////////////////////
MMC_LIB_API int MMC_ReadDS401DIGroup(
		IN MMC_CONNECT_HNDL hConn,
		IN MMC_AXIS_REF_HNDL hAxisRef,
		IN MMC_READDIGROUP_IN* pInParam,
		OUT MMC_READDIGROUP_OUT* pOutParam);

////////////////////////////////////////////////////////////////////////////////
/// \fn int MMC_WriteDOGroup(
///				IN MMC_CONNECT_HNDL hConn,
///				IN MMC_AXIS_REF_HNDL hAxisRef,
///				IN MMC_WRITEDOGROUP_IN* pInParam,
///				OUT MMC_WRITEDOGROUP_OUT* pOutParam)
////////////////////////////////////////////////////////////////////////////////
MMC_LIB_API int MMC_WriteDS401DOGroup(
		IN MMC_CONNECT_HNDL hConn,
		IN MMC_AXIS_REF_HNDL hAxisRef,
		IN MMC_WRITEDOGROUP_IN* pInParam,
		OUT MMC_WRITEDOGROUP_OUT* pOutParam);

////////////////////////////////////////////////////////////////////////////////
/// \fn int MMC_EnableDIChangedEvent(
///				IN MMC_CONNECT_HNDL hConn,
///				IN MMC_AXIS_REF_HNDL hAxisRef,
///				IN MMC_CONFIGREGULARPARAMEVENTPDO3_IN* pInParam,
///				OUT MMC_CONFIGREGULARPARAMEVENTPDO3_OUT* pOutParam)
////////////////////////////////////////////////////////////////////////////////
MMC_LIB_API int MMC_EnableDS401DIChangedEvent(
		IN MMC_CONNECT_HNDL hConn,
		IN MMC_AXIS_REF_HNDL hAxisRef,
		IN MMC_ENABLEDICHANGEDEVENT_IN* pInParam,
		OUT MMC_ENABLEDICHANGEDEVENT_OUT* pOutParam);

////////////////////////////////////////////////////////////////////////////////
/// \fn int MMC_DisableDIChangedEvent(
///				IN MMC_CONNECT_HNDL hConn,
///				IN MMC_AXIS_REF_HNDL hAxisRef,
///				IN MMC_CONFIGREGULARPARAMEVENTPDO3_IN* pInParam,
///				OUT MMC_CONFIGREGULARPARAMEVENTPDO3_OUT* pOutParam)
////////////////////////////////////////////////////////////////////////////////
MMC_LIB_API int MMC_DisableDS401DIChangedEvent(
		IN MMC_CONNECT_HNDL hConn,
		IN MMC_AXIS_REF_HNDL hAxisRef,
		IN MMC_DISABLEDICHANGEDEVENT_IN* pInParam,
		OUT MMC_DISABLEDICHANGEDEVENT_OUT* pOutParam);

////////////////////////////////////////////////////////////////////////////////
/// \fn int MMC_ReadDS401DInput(
///				IN MMC_CONNECT_HNDL hConn,
///				IN MMC_AXIS_REF_HNDL hAxisRef,
///				IN MMC_READDIGROUP_IN* pInParam,
///				OUT MMC_READDIGROUP_OUT* pOutParam)
////////////////////////////////////////////////////////////////////////////////
MMC_LIB_API int MMC_ReadDS401DInput(
		IN MMC_CONNECT_HNDL hConn,
		IN MMC_AXIS_REF_HNDL hAxisRef,
		IN MMC_READDI_IN* pInParam,
		OUT MMC_READDI_OUT* pOutParam) ;

////////////////////////////////////////////////////////////////////////////////
/// \fn int MMC_WriteDS401DOutput(
///				IN MMC_CONNECT_HNDL hConn,
///				IN MMC_AXIS_REF_HNDL hAxisRef,
///				IN MMC_WRITEDOGROUP_IN* pInParam,
///				OUT MMC_WRITEDOGROUP_OUT* pOutParam)
////////////////////////////////////////////////////////////////////////////////
MMC_LIB_API int MMC_WriteDS401DOutput(
		IN MMC_CONNECT_HNDL hConn,
		IN MMC_AXIS_REF_HNDL hAxisRef,
		IN MMC_WRITEDO_IN* pInParam,
		OUT MMC_WRITEDO_OUT* pOutParam) ;

////////////////////////////////////////////////////////////////////////////////
/// \fn int MMC_ConfigGeneralRPDO3(
///				IN MMC_CONNECT_HNDL hConn,
///				IN MMC_AXIS_REF_HNDL hAxisRef,
///				IN MMC_CONFIGGENERALRPDO3_IN* pInParam,
///				OUT MMC_CONFIGGENERALRPDO3_OUT* pOutParam)
////////////////////////////////////////////////////////////////////////////////
MMC_LIB_API int MMC_ConfigGeneralRPDO3(
		IN MMC_CONNECT_HNDL hConn,
		IN MMC_AXIS_REF_HNDL hAxisRef,
		IN MMC_CONFIGGENERALRPDO3_IN* pInParam,
		OUT MMC_CONFIGGENERALRPDO3_OUT* pOutParam);

////////////////////////////////////////////////////////////////////////////////
/// \fn int MMC_ConfigGeneralRPDO4(
///				IN MMC_CONNECT_HNDL hConn,
///				IN MMC_AXIS_REF_HNDL hAxisRef,
///				IN MMC_CONFIGGENERALRPDO4_IN* pInParam,
///				OUT MMC_CONFIGGENERALRPDO4_OUT* pOutParam)
////////////////////////////////////////////////////////////////////////////////
MMC_LIB_API int MMC_ConfigGeneralRPDO4(
		IN MMC_CONNECT_HNDL hConn,
		IN MMC_AXIS_REF_HNDL hAxisRef,
		IN MMC_CONFIGGENERALRPDO4_IN* pInParam,
		OUT MMC_CONFIGGENERALRPDO4_OUT* pOutParam);

////////////////////////////////////////////////////////////////////////////////
/// \fn int MMC_CancelGeneralRPDO3(
///				IN MMC_CONNECT_HNDL hConn,
///				IN MMC_AXIS_REF_HNDL hAxisRef,
///				IN MMC_CANCELGENERALRPDO3_IN* pInParam,
///				OUT MMC_CANCELGENERALRPDO3_OUT* pOutParam)
////////////////////////////////////////////////////////////////////////////////
MMC_LIB_API int MMC_CancelGeneralRPDO3(
		IN MMC_CONNECT_HNDL hConn,
		IN MMC_AXIS_REF_HNDL hAxisRef,
		IN MMC_CANCELGENERALRPDO3_IN* pInParam,
		OUT MMC_CANCELGENERALRPDO3_OUT* pOutParam);

////////////////////////////////////////////////////////////////////////////////
/// \fn int MMC_CancelGeneralRPDO4(
///				IN MMC_CONNECT_HNDL hConn,
///				IN MMC_AXIS_REF_HNDL hAxisRef,
///				IN MMC_CANCELGENERALRPDO4_IN* pInParam,
///				OUT MMC_CANCELGENERALRPDO4_OUT* pOutParam)
////////////////////////////////////////////////////////////////////////////////
MMC_LIB_API int MMC_CancelGeneralRPDO4(
		IN MMC_CONNECT_HNDL hConn,
		IN MMC_AXIS_REF_HNDL hAxisRef,
		IN MMC_CANCELGENERALRPDO4_IN* pInParam,
		OUT MMC_CANCELGENERALRPDO4_OUT* pOutParam);

////////////////////////////////////////////////////////////////////////////////
/// \fn int MMC_ConfigGeneralTPDO3(
///				IN MMC_CONNECT_HNDL hConn,
///				IN MMC_AXIS_REF_HNDL hAxisRef,
///				IN MMC_CONFIGGENERALTPDO3_IN* pInParam,
///				OUT MMC_CONFIGGENERALTPDO3_OUT* pOutParam)
////////////////////////////////////////////////////////////////////////////////
MMC_LIB_API int MMC_ConfigGeneralTPDO3(
		IN MMC_CONNECT_HNDL hConn,
		IN MMC_AXIS_REF_HNDL hAxisRef,
		IN MMC_CONFIGGENERALTPDO3_IN* pInParam,
		OUT MMC_CONFIGGENERALTPDO3_OUT* pOutParam);

////////////////////////////////////////////////////////////////////////////////
/// \fn int MMC_ConfigGeneralTPDO4(
///				IN MMC_CONNECT_HNDL hConn,
///				IN MMC_AXIS_REF_HNDL hAxisRef,
///				IN MMC_CONFIGGENERALTPDO4_IN* pInParam,
///				OUT MMC_CONFIGGENERALTPDO4_OUT* pOutParam)
////////////////////////////////////////////////////////////////////////////////
MMC_LIB_API int MMC_ConfigGeneralTPDO4(
		IN MMC_CONNECT_HNDL hConn,
		IN MMC_AXIS_REF_HNDL hAxisRef,
		IN MMC_CONFIGGENERALTPDO4_IN* pInParam,
		OUT MMC_CONFIGGENERALTPDO4_OUT* pOutParam);

////////////////////////////////////////////////////////////////////////////////
/// \fn int MMC_CancelGeneralTPDO3(
///				IN MMC_CONNECT_HNDL hConn,
///				IN MMC_AXIS_REF_HNDL hAxisRef,
///				IN MMC_CANCELGENERALTPDO3_IN* pInParam,
///				OUT MMC_CANCELGENERALTPDO3_OUT* pOutParam)
////////////////////////////////////////////////////////////////////////////////
MMC_LIB_API int MMC_CancelGeneralTPDO3(
		IN MMC_CONNECT_HNDL hConn,
		IN MMC_AXIS_REF_HNDL hAxisRef,
		IN MMC_CANCELGENERALTPDO3_IN* pInParam,
		OUT MMC_CANCELGENERALTPDO3_OUT* pOutParam);

////////////////////////////////////////////////////////////////////////////////
/// \fn int MMC_CancelGeneralTPDO4(
///				IN MMC_CONNECT_HNDL hConn,
///				IN MMC_AXIS_REF_HNDL hAxisRef,
///				IN MMC_CANCELGENERALTPDO4_IN* pInParam,
///				OUT MMC_CANCELGENERALTPDO4_OUT* pOutParam)
////////////////////////////////////////////////////////////////////////////////
MMC_LIB_API int MMC_CancelGeneralTPDO4(
		IN MMC_CONNECT_HNDL hConn,
		IN MMC_AXIS_REF_HNDL hAxisRef,
		IN MMC_CANCELGENERALTPDO4_IN* pInParam,
		OUT MMC_CANCELGENERALTPDO4_OUT* pOutParam);



//moving to g++ @YL 4-10-2010
#ifdef __cplusplus
}
#endif

#endif /* MMC_DS401_API_H */
