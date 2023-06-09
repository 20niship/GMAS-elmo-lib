////////////////////////////////////////////////////////////////////////////////
/// \file MMC_ErrorCorr_API.h
/// Name        : MMC_ErrorCorr_API.h
/// Author      : Benjamin Spitzer
/// Created on	: June, 2011
/// Version     : 0.0.1
/// Copyright   : Your copyright notice
/// Description : This file contain definitions for ...
////////////////////////////////////////////////////////////////////////////////

#ifndef MMC_ERRORCORR_API_H
#define MMC_ERRORCORR_API_H
//
//moving to g++ @YL 4-10-2010
#ifdef __cplusplus
 extern "C" {
#endif
#include <sys/types.h>
#ifndef WIN32
#include <unistd.h>
#endif

///////////////////////////////////////////////////////////////////////////////
/// \enum NC_ERROR_TABLE_NUMBER
/// \brief Communication connection type.
///////////////////////////////////////////////////////////////////////////////
typedef enum _NC_ERROR_TABLE_NUMBER
{
	NC_ERROR_TABLE_A,
	NC_ERROR_TABLE_B,
	NC_ERROR_TABLE_C,
	NC_ERROR_TABLE_D,
	NC_ERROR_TABLE_E,
	NC_ERROR_TABLE_F,
	NC_ERROR_TABLE_MAX
} NC_ERROR_TABLE_NUMBER;

///////////////////////////////////////////////////////////////////////////////
/// \enum NC_ERROR_TABLE_DIMENSION
/// \brief Communication connection type.
///////////////////////////////////////////////////////////////////////////////
typedef enum _NC_ERROR_TABLE_DIMENSION
{
	NC_ERROR_TABLE_DIMENSION_NONE = 0,
	NC_ERROR_TABLE_DIMENSION_1D	  = 1,
	NC_ERROR_TABLE_DIMENSION_2D	  = 2,
	NC_ERROR_TABLE_DIMENSION_3D	  = 3,
	NC_ERROR_TABLE_DIMENSION_MAX  = 4
} NC_ERROR_TABLE_DIMENSION;

/*
 * Alex 16/06/2011 - Error correction user API
 */
#define NC_MAX_ET_FILE_PATH_LENGTH 100

typedef struct
{
	double dMaxCorrectionDelta;
	NC_ERROR_TABLE_NUMBER eETNumber;
	char pPathToETFile[NC_MAX_ET_FILE_PATH_LENGTH];
	char sSpare[24];
} MMC_LOADERRORTABLE_IN;

typedef struct
{
	int iProblematicLine;
	unsigned short usStatus;
	short usErrorID;
} MMC_LOADERRORTABLE_OUT;

typedef struct
{
	NC_ERROR_TABLE_NUMBER eTableNumber;
} MMC_UNLOADERRORTABLE_IN;

typedef struct
{
	unsigned short usStatus;
	short usErrorID;
} MMC_UNLOADERRORTABLE_OUT;

typedef struct
{
	NC_ERROR_TABLE_NUMBER eTableNumber;
} MMC_ENABLEERRORTABLE_IN;

typedef struct
{
	unsigned short usStatus;
	short usErrorID;
} MMC_ENABLEERRORTABLE_OUT;


typedef struct
{
	NC_ERROR_TABLE_NUMBER eTableNumber;
} MMC_DISABLEERRORTABLE_IN;

typedef struct
{
	unsigned short usStatus;
	short usErrorID;
} MMC_DISABLEERRORTABLE_OUT;


typedef struct
{
	NC_ERROR_TABLE_NUMBER eTableNumber;
} MMC_GETERRORTABLESTATUS_IN;

typedef struct
{
	NC_NODE_HNDL_T hReferenceAxesRef[NC_ERROR_TABLE_DIMENSION_3D];
	NC_NODE_HNDL_T hTargetAxisRef;
	unsigned short usStatus;
	short usErrorID;
	char cFileName[NC_MAX_ET_FILE_PATH_LENGTH];
	unsigned char ucIsTableEnabled;
	unsigned char ucIsTableLoaded;
	char sSpare[20];
} MMC_GETERRORTABLESTATUS_OUT;

////////////////////////////////////////////////////////////////////////////////
/// \fn int  MMC_LoadErrorCorrTableCmd(
///								   IN MMC_CONNECT_HNDL hConn,
/// 							   IN MMC_LOADERRRORTABLE_IN* pInParam
///								   OUT MMC_LOADERRORTABLE_OUT* pOutParam)
/// \brief
/// \param  hConn - [IN] Connection handle
///	\param	pInParam - Pointer to MMC_LOADERRORTABLE_IN input structure
///	\param	pOutParam - Pointer to MMC_LOADERRORTABLE_OUT output structure
/// \return	return - 0 if success
/// 				 error_id in case of error
////////////////////////////////////////////////////////////////////////////////
MMC_LIB_API int MMC_LoadErrorCorrTableCmd(IN MMC_CONNECT_HNDL hConn,
									  IN MMC_LOADERRORTABLE_IN* pInParam,
									  OUT MMC_LOADERRORTABLE_OUT* pOutParam);

////////////////////////////////////////////////////////////////////////////////
/// \fn int  MMC_UnloadErrorCorrTableCmd(
///								   IN MMC_CONNECT_HNDL hConn,
/// 							   IN MMC_UNLOADERRRORTABLE_IN* pInParam
///								   OUT MMC_UNLOADERRORTABLE_OUT* pOutParam)
/// \brief
/// \param  hConn - [IN] Connection handle
///	\param	pInParam - Pointer to MMC_UNLOADERRORTABLE_IN input structure
///	\param	pOutParam - Pointer to MMC_UNLOADERRORTABLE_OUT output structure
/// \return	return - 0 if success
/// 				 error_id in case of error
////////////////////////////////////////////////////////////////////////////////
MMC_LIB_API int MMC_UnloadErrorCorrTableCmd(IN MMC_CONNECT_HNDL hConn,
									    IN MMC_UNLOADERRORTABLE_IN* pInParam,
									    OUT MMC_UNLOADERRORTABLE_OUT* pOutParam);

////////////////////////////////////////////////////////////////////////////////
/// \fn int  MMC_EnableErrorCorrTableCmd(
///								   IN MMC_CONNECT_HNDL hConn,
/// 							   IN MMC_ENABLEERRRORTABLE_IN* pInParam
///								   OUT MMC_ENABLEERRORTABLE_OUT* pOutParam)
/// \brief
/// \param  hConn - [IN] Connection handle
///	\param	pInParam - Pointer to MMC_ENABLEERRORTABLE_IN input structure
///	\param	pOutParam - Pointer to MMC_ENABLEERRORTABLE_OUT output structure
/// \return	return - 0 if success
/// 				 error_id in case of error
////////////////////////////////////////////////////////////////////////////////
MMC_LIB_API int MMC_EnableErrorCorrTableCmd(IN MMC_CONNECT_HNDL hConn,
									    IN MMC_ENABLEERRORTABLE_IN* pInParam,
									    OUT MMC_ENABLEERRORTABLE_OUT* pOutParam);


////////////////////////////////////////////////////////////////////////////////
/// \fn int  MMC_DisableErrorTableCmd(
///								   IN MMC_CONNECT_HNDL hConn,
/// 							   IN MMC_DISABLEERRRORTABLE_IN* pInParam
///								   OUT MMC_DISABLEERRORTABLE_OUT* pOutParam)
/// \brief
/// \param  hConn - [IN] Connection handle
///	\param	pInParam - Pointer to MMC_DISABLEERRORTABLE_IN input structure
///	\param	pOutParam - Pointer to MMC_DISABLEERRORTABLE_OUT output structure
/// \return	return - 0 if success
/// 				 error_id in case of error
////////////////////////////////////////////////////////////////////////////////
MMC_LIB_API int MMC_DisableErrorCorrTableCmd(IN MMC_CONNECT_HNDL hConn,
									    IN MMC_DISABLEERRORTABLE_IN* pInParam,
									    OUT MMC_DISABLEERRORTABLE_OUT* pOutParam);


////////////////////////////////////////////////////////////////////////////////
/// \fn int  MMC_GetErrorTableStatusCmd(
///									    IN MMC_CONNECT_HNDL hConn,
/// 							   		IN MMC_GETERRORTABLESTATUS_IN* pInParam
///								   		OUT MMC_GETERRORTABLESTATUS_OUT* pOutParam)
/// \brief
/// \param  hConn - [IN] Connection handle
///	\param	pInParam - Pointer to MMC_GETERRORTABLESTATUS_IN input structure
///	\param	pOutParam - Pointer to MMC_GETERRORTABLESTATUS_OUT output structure
/// \return	return - 0 if success
////////////////////////////////////////////////////////////////////////////////
MMC_LIB_API int MMC_GetErrorTableStatusCmd(IN MMC_CONNECT_HNDL hConn,
									       IN MMC_GETERRORTABLESTATUS_IN* pInParam,
									       OUT MMC_GETERRORTABLESTATUS_OUT* pOutParam);


//moving to g++ @YL 4-10-2010
#ifdef __cplusplus
}
#endif

#endif /* MMC_ERRORCORR_API_H */
