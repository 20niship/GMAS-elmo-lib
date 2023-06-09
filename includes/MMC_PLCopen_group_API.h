////////////////////////////////////////////////////////////////////////////////
/// \file MMC_PLCopen_group_API.h
/// Name        : MMC_PLCopen_group_API.h
/// Author      : Barak R
/// Created on	: April 19, 20010
/// Version     : 0.0.1
/// Copyright   : Your copyright notice
/// Description : This file contain definitions for ...
////////////////////////////////////////////////////////////////////////////////

#ifndef MMC_PLCOPEN_GROUP_API_H
#define MMC_PLCOPEN_GROUP_API_H


//moving to g++ @YL 4-10-2010
#ifdef __cplusplus
 extern "C" {
#endif

//
///////////////////////////////////////////////////////////////////////////////
/// Group Status Bit Mask
///////////////////////////////////////////////////////////////////////////////
#define NC_GROUP_STANDBY_MASK				0x00020000	///< Group Standby State Bit Mask.
#define NC_GROUP_DISABLED_MASK				0x00010000	///< Group Disabled State Bit Mask.
#define NC_GROUP_HOMING_MASK				0x00008000	///< Group Homing State Bit Mask.
#define NC_GROUP_ERROR_STOP_MASK			0x00004000	///< Group Error State Bit Mask.
#define NC_GROUP_MOVING_MASK				0x00002000	///< Group Moving State Bit Mask.
#define NC_GROUP_STOPPING_MASK				0x00001000	///< Group Stopping State Bit Mask.

#define NC_MAX_SPLINES_FILE_PATH_LENGTH		100
///////////////////////////////////////////////////////////////////////////////
/// \enum NC_PATH_CHOICE_ENUM
/// This type define kinds of supported arc length
///////////////////////////////////////////////////////////////////////////////
typedef enum
{
	MC_NONE_ARC_CHOICE		= 0,
	MC_SHORT		    	= 1,
	MC_LONG	            	= 2,
}NC_ARC_SHORT_LONG_ENUM;

///////////////////////////////////////////////////////////////////////////////
/// \enum NC_CIRC_MODE
/// This type define kinds of supported circular modes
///////////////////////////////////////////////////////////////////////////////
typedef enum
{
	MC_NONE_CIRC_MODE	= 0,
	MC_BORDER_CIRC_MODE	= 1,
	MC_CENTER_CIRC_MODE	= 2,
	MC_RADIUS_CIRC_MODE	= 3,
	MC_ANGLE_CIRC_MODE	= 4,
}NC_CIRC_MODE_ENUM;

///////////////////////////////////////////////////////////////////////////////
/// \enum NC_DIRECTION_ENUM
/// This type define kinds of supported directions
///////////////////////////////////////////////////////////////////////////////
typedef enum
{
	MC_NONE_DIRECTION		= 0,
	MC_POSITIVE_DIRECTION	= 1,
	MC_SHORTEST_WAY			= 2,
	MC_NEGATIVE_DIRECTION	= 3,
	MC_CURRENT_DIRECTION	= 4,
}MC_DIRECTION_ENUM;

///////////////////////////////////////////////////////////////////////////////
/// \enum NC_PATH_CHOICE_ENUM
/// This type define kinds of supported path choice
///////////////////////////////////////////////////////////////////////////////
typedef enum
{
	MC_NONE_PATH_CHOICE		= 0,
	MC_CLOCKWISE			= 1,
	MC_COUNTERCLOCKWISE		= 2,
}NC_PATH_CHOICE_ENUM;

///////////////////////////////////////////////////////////////////////////////
/// \enum MC_COORD_SYSTEM_ENUM
/// This type define kinds of supported coordinate systems
///////////////////////////////////////////////////////////////////////////////
typedef enum
{
	MC_NONE_COORD	= 0,
	MC_ACS_COORD	= 1,
	MC_MCS_COORD	= 2,
	MC_PCS_COORD	= 3,
}MC_COORD_SYSTEM_ENUM;

///////////////////////////////////////////////////////////////////////////////
/// \enum PCS_REF_AXIS_SRC_ENUM
/// This reference type for dynamic PCS/MCS transformation
///////////////////////////////////////////////////////////////////////////////
typedef enum {
	NC_PCS_TARGET_POS = 0,
	NC_PCS_ACTUAL_POS,
	NC_PCS_AUX_POS,
} PCS_REF_AXIS_SRC_ENUM;

///////////////////////////////////////////////////////////////////////////////
/// \enum NC_PCS_MCS_TRANSFORM_TYPE
/// This type define kinds of supported PCS-MCS transformation types
///////////////////////////////////////////////////////////////////////////////
typedef enum
{
	NC_PCS_MCS_TRANSFORM_NONE = 0,
	NC_PCS_MCS_TRANSFORM_STATIC = 1,
	NC_PCS_MCS_CONVEYOR_BELT = 2,
	NC_PCS_MCS_ROTARY_TABLE = 3
}NC_PCS_MCS_TRANSFORM_TYPE;

///////////////////////////////////////////////////////////////////////////////
/// \enum PCS_ROTATION_ANGLE_UNITS_ENUM
/// This type define angle units used in PCS to MCS transformation
///////////////////////////////////////////////////////////////////////////////
typedef enum
{
	PCS_DEGREE	= 0,
	PCS_RADIAN	= 1,
}PCS_ROTATION_ANGLE_UNITS_ENUM;

///////////////////////////////////////////////////////////////////////////////
/// \enum NC_TRANSITION_MODE_ENUM
/// This type define supported transition modes
///////////////////////////////////////////////////////////////////////////////
typedef enum
{
	MC_TM_NONE_MODE					= 0,
	MC_TM_MAX_VELOCITY_MODE			= 1,
	MC_TM_DEFINED_VELOCITY_MODE		= 2,
	MC_TM_CORNER_DISTANCE_MODE		= 3,
	MC_TM_MAX_CORNER_DEVIATION_MODE	= 4,
	MC_TM_SWITCH_RADIUS_MODE        = 5,
    MC_TM_CORNER_DIST_TC_POLYNOM    = 6,
	MC_TM_CORNER_DIST_CV_POLYNOM3   = 7,
	MC_TM_CORNER_DIST_CV_POLYNOM5   = 8,
	MC_TM_CORNER_DEVIATION_MODE_PLN6 = 9,
	MC_TM_CORNER_DIST_CV_POLYNOM5_NAXES = 10,
	MC_TM_CORNER_DIST_CV_POLYNOM7 = 11,
	MC_TM_CORNER_DEVIATION_MODE_PLN8 = 12,
	MC_TM_DIST1_DIST2_DEVIATION_PLN6 = 13,
	MC_TM_DIST1_DIST2_DEVIATION_PLN8 = 14,
	MC_TM_LAST_MODE
}NC_TRANSITION_MODE_ENUM;

///////////////////////////////////////////////////////////////////////////////
/// \enum NC_AXIS_IN_GROUP_TYPE_ENUM_EX
/// This type define kinds of supported axis in group
///////////////////////////////////////////////////////////////////////////////
typedef enum
{
	NC_PROFILER_X_AXIS_TYPE = 0,
	NC_PROFILER_Y_AXIS_TYPE,
	NC_PROFILER_Z_AXIS_TYPE,
	NC_PROFILER_U_AXIS_TYPE,
	NC_PROFILER_V_AXIS_TYPE,
	NC_PROFILER_W_AXIS_TYPE,
	NC_PROFILER_N1_AXIS_TYPE,
	NC_PROFILER_N2_AXIS_TYPE,
	NC_PROFILER_N3_AXIS_TYPE,
	NC_PROFILER_N4_AXIS_TYPE,
	NC_PROFILER_N5_AXIS_TYPE,
	NC_PROFILER_N6_AXIS_TYPE,
	NC_PROFILER_N7_AXIS_TYPE,
	NC_PROFILER_N8_AXIS_TYPE,
	NC_PROFILER_N9_AXIS_TYPE,
	NC_PROFILER_S_AXIS_TYPE,
	NC_MCS_X_AXIS_TYPE,
	NC_MCS_Y_AXIS_TYPE,
	NC_MCS_Z_AXIS_TYPE,
	NC_MCS_U_AXIS_TYPE,
	NC_MCS_V_AXIS_TYPE,
	NC_MCS_W_AXIS_TYPE,
	NC_ACS_A1_AXIS_TYPE,
	NC_ACS_A2_AXIS_TYPE,
	NC_ACS_A3_AXIS_TYPE,
	NC_ACS_A4_AXIS_TYPE,
	NC_ACS_A5_AXIS_TYPE,
	NC_ACS_A6_AXIS_TYPE,
	NC_LAST_AXIS_TYPE_EX
}NC_AXIS_IN_GROUP_TYPE_ENUM_EX;


///////////////////////////////////////////////////////////////////////////////
/// \enum NC_AXIS_IN_GROUP_TYPE_ENUM
/// This type define kinds of supported axis in group
///////////////////////////////////////////////////////////////////////////////
typedef enum
{
	NC_X_AXIS_TYPE = 0,
	NC_Y_AXIS_TYPE,
	NC_Z_AXIS_TYPE,
	NC_U_AXIS_TYPE,
	NC_V_AXIS_TYPE,
	NC_W_AXIS_TYPE,
	NC_N1_AXIS_TYPE,
	NC_N2_AXIS_TYPE,
	NC_N3_AXIS_TYPE,
	NC_N4_AXIS_TYPE,
	NC_N5_AXIS_TYPE,
	NC_N6_AXIS_TYPE,
	NC_N7_AXIS_TYPE,
	NC_N8_AXIS_TYPE,
	NC_N9_AXIS_TYPE,
	NC_S_AXIS_TYPE,
	NC_LAST_AXIS_TYPE
}NC_AXIS_IN_GROUP_TYPE_ENUM;

///////////////////////////////////////////////////////////////////////////////
/// \enum NC_BUFFERED_MODE_ENUM
/// This type define all supported buffered mode options
///////////////////////////////////////////////////////////////////////////////
typedef enum
{
	MC_ABORTING_MODE			= 1,
	MC_BUFFERED_MODE			= 2,
	MC_BLENDING_LOW_MODE		= 3,
	MC_BLENDING_PREVIOUS_MODE	= 4,
	MC_BLENDING_NEXT_MODE		= 5,
	MC_BLENDING_HIGH_MODE		= 6,
}MC_BUFFERED_MODE_ENUM;


///////////////////////////////////////////////////////////////////////////////
/// \enum NC_TR_COEF_TYPE_ENUM
/// This type define kinds of supported MCS transform coefficients
///////////////////////////////////////////////////////////////////////////////
typedef enum
{
	NC_BACK_TR_RATIO_COEF = 0,
	NC_FRWD_TR_RATIO_COEF = 1,
	NC_BACK_SHIFT_COEF = 2,
	NC_MAX_NUM_COEF
}NC_TR_COEF_TYPE_ENUM;

///////////////////////////////////////////////////////////////////////////////
/// \enum NC_AXIS_IN_GROUP_TYPE_ENUM
/// This type define kinds of supported axis in group
///////////////////////////////////////////////////////////////////////////////
typedef enum
{
	NC_TR_NONE_FUNC = 0,
	NC_TR_SHIFT_FUNC,
	NC_TR_LAST_FUNC
}NC_TR_FUNC_ID_ENUM;

typedef enum {
	NC_NODE_1_ID = 0,
	NC_NODE_2_ID = 1,
	NC_NODE_3_ID = 2,
	NC_NODE_4_ID = 3,
	NC_NODE_5_ID = 4,
	NC_NODE_6_ID = 5,
	NC_NODE_7_ID = 6,
	NC_NODE_8_ID = 7,
	NC_NODE_9_ID = 8,
	NC_NODE_10_ID = 9,
	NC_NODE_11_ID = 10,
	NC_NODE_12_ID = 11,
	NC_NODE_13_ID = 12,
	NC_NODE_14_ID = 13,
	NC_NODE_15_ID = 14,
	NC_NODE_16_ID = 15
}NC_IDENT_IN_GROUP_ENUM;

//// structs



///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_SETKINTRANSFORM_IN
/// \brief
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
	double  ulTrCoef[NC_MAX_NUM_AXES_IN_NODE][NC_MAX_NUM_COEF];
	int iNumAxes;
	MC_BUFFERED_MODE_ENUM eBufferMode;
	NC_TR_FUNC_ID_ENUM iMcsToAcsFuncID[NC_MAX_NUM_AXES_IN_NODE];
	NC_NODE_HNDL_T hNode[NC_MAX_NUM_AXES_IN_NODE];
	NC_AXIS_IN_GROUP_TYPE_ENUM eType[NC_MAX_NUM_AXES_IN_NODE];
	unsigned char ucExecute;
}MMC_SETKINTRANSFORM_IN;

///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_SETKINTRANSFORM_OUT
/// \brief
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
	unsigned short usStatus;
	short usErrorID;
}MMC_SETKINTRANSFORM_OUT;



///////////////////////////////////////////////////////////////////////////////
/// \enum NC_AXIS_IN_GROUP_TYPE_ENUM
/// This type define kinds of supported axis in group
///////////////////////////////////////////////////////////////////////////////
typedef enum
{
	NC_CARTESIAN_TYPE = 0,
	NC_DELTA_ROBOT_TYPE,
	NC_SCARA_ROBOT_TYPE,
	NC_THREE_LINK_ROBOT_TYPE,
	NC_LAST_KIN_TYPE
}NC_KIN_TYPE;

///////////////////////////////////////////////////////////////////////////////
/// \struct MC_KIN_NODE_DEF
/// \brief
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
	double  ulTrCoef[NC_MAX_NUM_COEF];
	NC_TR_FUNC_ID_ENUM iMcsToAcsFuncID;
	NC_NODE_HNDL_T hNode;
	NC_AXIS_IN_GROUP_TYPE_ENUM_EX eType;
}MC_KIN_NODE_DEF;

///////////////////////////////////////////////////////////////////////////////
/// \struct MC_KIN_REF_CARTESIAN
/// \brief
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
	MC_KIN_NODE_DEF sNode[NC_MAX_NUM_AXES_IN_NODE];
	int iNumAxes;
}MC_KIN_REF_CARTESIAN;


///////////////////////////////////////////////////////////////////////////////
/// \struct MC_KIN_REF_DELTA
/// \brief
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
	double  dbArm;
	double  dbForeArm;
	double  dbBaseRadius;
	double  dbEndEffectorRadius;
	MC_KIN_NODE_DEF sNode[NC_MAX_NUM_AXES_IN_NODE];
	int iNumAxes;
}MC_KIN_REF_DELTA;

/// \struct MC_KIN_REF_SCARA
/// \brief
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
	double  dInnerLinkLength;
	double  dOuterLinkLength;
	double  dShoulderOffset;
	double  dWristOffset;
	double  dWristTheta2OffsetCoef;
	MC_KIN_NODE_DEF sNode[NC_MAX_NUM_AXES_IN_NODE];
	int iNumAxes;
	char 	cElbowSign;
	char	cPadding1 ;
	char	cPadding2 ;
	char	cPadding3 ;
}MC_KIN_REF_SCARA;

typedef struct
{
	double dInnerLinkLength ;
	double dMediumLinkLength;
	double dOuterLinkLength;
	double dShoulderOffset;
	double dWristOffset;
	double  dWristTheta2OffsetCoef;
	MC_KIN_NODE_DEF sNode[NC_MAX_NUM_AXES_IN_NODE];
	int iNumAxes;
	char cElbowSign ;
	char cPadding1 ;
	char cPadding2 ;
	char cPadding3 ;
}MC_KIN_REF_THREE_LINK;


///////////////////////////////////////////////////////////////////////////////
/// \struct MC_KIN_REF
/// \brief
///////////////////////////////////////////////////////////////////////////////
typedef union
{
	MC_KIN_REF_DELTA		stDelta;
	MC_KIN_REF_CARTESIAN	stCart;
	MC_KIN_REF_SCARA		stScara ;
	MC_KIN_REF_THREE_LINK	stThreeLink ;
	unsigned char ucMaxSize[1300];
}MC_KIN_REF;


///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_SETKINTRANSFORMEX_IN
/// \brief
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
	MC_KIN_REF stInput;
	NC_KIN_TYPE eKinType;
	MC_BUFFERED_MODE_ENUM eBufferMode;
	unsigned char ucExecute;
}MMC_SETKINTRANSFORMEX_IN;

///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_SETKINTRANSFORMEX_OUT
/// \brief
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
	unsigned short usStatus;
	short usErrorID;
}MMC_SETKINTRANSFORMEX_OUT;


///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_SETCARTESIANTRANSFORM_IN
/// \brief
///////////////////////////////////////////////////////////////////////////////
typedef struct 
{
	double dOffset[3];		// X,Y,Z translation components
	double dRotAngle[3];	// U,V,W rotation angles
	double dPadding[5] ;
	PCS_ROTATION_ANGLE_UNITS_ENUM eRotAngleUnits;
	MC_BUFFERED_MODE_ENUM eBufferMode;
	MC_EXECUTION_MODE eExecutionMode;
	unsigned char ucExecute;
}MMC_SETCARTESIANTRANSFORM_IN;


///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_SETCARTESIANTRANSFORM_OUT
/// \brief
///////////////////////////////////////////////////////////////////////////////
typedef struct 
{
	unsigned short usStatus;
	short sErrorID;
}MMC_SETCARTESIANTRANSFORM_OUT;

///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_TRACKCONVEYORBELT_IN
/// \brief
///////////////////////////////////////////////////////////////////////////////
typedef struct mmc_trackconveyorbelt_in
{
	double dConveyorBeltOrigin[6];		// X,Y,Z,U,V,W
	double dInitialObjectPosition[6];	// X,Y,Z,U,V,W
	double dInitialRefAxisPosition;
  	double dRefAxisScaling;
	double dPadding[5] ;
	unsigned short usRefAxis;
	PCS_REF_AXIS_SRC_ENUM eRefAxisSourceType;		//defines the reference axis source: dTargetPosUU or dActualPosUU
	PCS_ROTATION_ANGLE_UNITS_ENUM eRotAngleUnits;
	MC_BUFFERED_MODE_ENUM eBufferMode;
	MC_COORD_SYSTEM_ENUM eCoordSystem;
	MC_EXECUTION_MODE eExecutionMode;
	unsigned char ucExecute;
}MMC_TRACKCONVEYORBELT_IN;

///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_TRACKCONVEYORBELT_OUT
/// \brief
///////////////////////////////////////////////////////////////////////////////
typedef struct mmc_trackconveyorbelt_out
{
	unsigned short usStatus;
	short sErrorID;
}MMC_TRACKCONVEYORBELT_OUT;

///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_TRACKROTARYTABLE_IN
/// \brief
///////////////////////////////////////////////////////////////////////////////
typedef struct mmc_trackrotarytable_in
{
	double dRotaryTableOrigin[6];		// X,Y,Z,U,V,W
	double dInitialObjectPosition[6];	// X,Y,Z,U,V,W
	double dInitialRefAxisPosition;
  	double dRefAxisScaling;
	double dPadding[5] ;
	PCS_REF_AXIS_SRC_ENUM eRefAxisSourceType;		//defines the reference axis source: dTargetPosUU or dActualPosUU
	PCS_ROTATION_ANGLE_UNITS_ENUM eRotAngleUnits;
	MC_BUFFERED_MODE_ENUM eBufferMode;
	MC_COORD_SYSTEM_ENUM eCoordSystem;
	MC_EXECUTION_MODE eExecutionMode;
	unsigned short usRefAxis;
	unsigned char ucExecute;
}MMC_TRACKROTARYTABLE_IN;

///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_TRACKROTARYTABLE_OUT
/// \brief
///////////////////////////////////////////////////////////////////////////////
typedef struct mmc_trackrotarytable_out
{
	unsigned short usStatus;
	short sErrorID;
}MMC_TRACKROTARYTABLE_OUT;

///////////////////////////////////////////////////////////////////////////////
/// \struct NC_MCS_INFO_STRUCT
/// \brief
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
	double  ulTrCoef[NC_MAX_NUM_COEF];
	unsigned int hNode;
	NC_AXIS_IN_GROUP_TYPE_ENUM eType;
	NC_TR_FUNC_ID_ENUM eMcsToAcsFuncID;
}NC_MCS_INFO_STRUCT;

///////////////////////////////////////////////////////////////////////////////
/// \struct NC_MCS_KIN_REF_STRUCT
/// \brief
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
	int iNumAxes;
	NC_MCS_INFO_STRUCT sMcsInfo[NC_MAX_NUM_AXES_IN_NODE];
}NC_MCS_KIN_REF_STRUCT;


///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_READKINTRANSFORM_IN
/// \brief
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
	unsigned char ucEnable;
}MMC_READKINTRANSFORM_IN;

///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_READKINTRANSFORM_OUT
/// \brief
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
	double  ulTrCoef[NC_MAX_NUM_AXES_IN_NODE][NC_MAX_NUM_COEF];
	int iNumAxes;
	int iMcsToAcsFuncID[NC_MAX_NUM_AXES_IN_NODE];
	NC_NODE_HNDL_T hNode[NC_MAX_NUM_AXES_IN_NODE];
	NC_AXIS_IN_GROUP_TYPE_ENUM eType[NC_MAX_NUM_AXES_IN_NODE];
	unsigned short usStatus;
	short usErrorID;
}MMC_READKINTRANSFORM_OUT;

///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_GROUPREADACTUALPOSITION_IN
/// \brief
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
	MC_COORD_SYSTEM_ENUM eCoordSystem;
	unsigned char ucEnable;
}MMC_GROUPREADACTUALPOSITION_IN;

///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_GROUPREADACTUALPOSITION_OUT
/// \brief
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
	double dbPosition[NC_MAX_NUM_AXES_IN_NODE];
	unsigned short usStatus;
	short usErrorID;
}MMC_GROUPREADACTUALPOSITION_OUT;

///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_GROUPREADACTUALVELOCITY_IN
/// \brief
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
	MC_COORD_SYSTEM_ENUM eCoordSystem;
	unsigned char ucEnable;
}MMC_GROUPREADACTUALVELOCITY_IN;

///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_GROUPREADACTUALVELOCITY_OUT
/// \brief
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
	double dVelocity[NC_MAX_NUM_AXES_IN_NODE];
	double dPathVelocity;
	unsigned short usStatus;
	short usErrorID;
}MMC_GROUPREADACTUALVELOCITY_OUT;

///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_GROUPREADERROR_IN
/// \brief
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
	unsigned char ucEnable;
}MMC_GROUPREADERROR_IN;

///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_GROUPREADERROR_OUT
/// \brief
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
	unsigned short usStatus;
	short usErrorID;
	unsigned short usGroupErrorID;
}MMC_GROUPREADERROR_OUT;

///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_MOVECIRCULARABSOLUTE_IN
/// \brief Move Circular Absolute Command input data structure.
///
/// (See : " Technical Paper
///		PLCopen Technical Committee 2 – Task Force
///		Function Blocks for motion control:
///		Part 4 –Coordinated Motion")
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
	double dAuxPoint[NC_MAX_NUM_AXES_IN_NODE];
	double dEndPoint[NC_MAX_NUM_AXES_IN_NODE];
	float fVelocity;
	float fAcceleration;
	float fDeceleration;
	float fJerk;
	float fTransitionParameter[NC_MAX_NUM_AXES_IN_NODE];
	NC_PATH_CHOICE_ENUM ePathChoice;
	NC_ARC_SHORT_LONG_ENUM eArcShortLong;
	NC_CIRC_MODE_ENUM eCircleMode;
	MC_COORD_SYSTEM_ENUM eCoordSystem;
	NC_TRANSITION_MODE_ENUM eTransitionMode;
	MC_BUFFERED_MODE_ENUM eBufferMode;
	unsigned char ucSuperimposed;
	unsigned char ucExecute;
}MMC_MOVECIRCULARABSOLUTE_IN;

///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_MOVECIRCULARABSOLUTEEX_IN
/// \brief Move Circular Absolute Extended Command input data structure.
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
	double dAuxPoint[NC_MAX_NUM_AXES_IN_NODE];
	double dEndPoint[NC_MAX_NUM_AXES_IN_NODE];
	double dVelocity;
	double dAcceleration;
	double dDeceleration;
	double dJerk;
	double dTransitionParameter[NC_MAX_NUM_AXES_IN_NODE];
	NC_PATH_CHOICE_ENUM ePathChoice;
	NC_ARC_SHORT_LONG_ENUM eArcShortLong;
	NC_CIRC_MODE_ENUM eCircleMode;
	MC_COORD_SYSTEM_ENUM eCoordSystem;
	NC_TRANSITION_MODE_ENUM eTransitionMode;
	MC_BUFFERED_MODE_ENUM eBufferMode;
	unsigned char ucSuperimposed;
	unsigned char ucExecute;
}MMC_MOVECIRCULARABSOLUTEEX_IN;

///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_MOVECIRCULARABSOLUTECENTER_IN
/// \brief Move Circular Absolute Center Command input data structure.
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
	double dCenterPoint[NC_MAX_NUM_AXES_IN_NODE];
	double dEndPoint[NC_MAX_NUM_AXES_IN_NODE];
	float fVelocity;
	float fAcceleration;
	float fDeceleration;
	float fJerk;
	float fTransitionParameter[NC_MAX_NUM_AXES_IN_NODE];
	NC_ARC_SHORT_LONG_ENUM eArcShortLong;
	MC_COORD_SYSTEM_ENUM eCoordSystem;
	NC_TRANSITION_MODE_ENUM eTransitionMode;
	MC_BUFFERED_MODE_ENUM eBufferMode;
	unsigned char ucSuperimposed;
	unsigned char ucExecute;
}MMC_MOVECIRCULARABSOLUTECENTER_IN;

///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_MOVECIRCULARABSOLUTECENTEREX_IN
/// \brief Move Circular Absolute Center Extended Command input data structure.
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
	double dCenterPoint[NC_MAX_NUM_AXES_IN_NODE];
	double dEndPoint[NC_MAX_NUM_AXES_IN_NODE];
	double dVelocity;
	double dAcceleration;
	double dDeceleration;
	double dJerk;
	double dTransitionParameter[NC_MAX_NUM_AXES_IN_NODE];
	NC_ARC_SHORT_LONG_ENUM eArcShortLong;
	MC_COORD_SYSTEM_ENUM eCoordSystem;
	NC_TRANSITION_MODE_ENUM eTransitionMode;
	MC_BUFFERED_MODE_ENUM eBufferMode;
	unsigned char ucSuperimposed;
	unsigned char ucExecute;
}MMC_MOVECIRCULARABSOLUTECENTEREX_IN;

///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_MOVECIRCULARABSOLUTEBORDER_IN
/// \brief Move Circular Absolute Border Command input data structure.
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
	double dBorderPoint[NC_MAX_NUM_AXES_IN_NODE];
	double dEndPoint[NC_MAX_NUM_AXES_IN_NODE];
	float fVelocity;
	float fAcceleration;
	float fDeceleration;
	float fJerk;
	float fTransitionParameter[NC_MAX_NUM_AXES_IN_NODE];
	MC_COORD_SYSTEM_ENUM eCoordSystem;
	NC_TRANSITION_MODE_ENUM eTransitionMode;
	MC_BUFFERED_MODE_ENUM eBufferMode;
	unsigned char ucSuperimposed;
	unsigned char ucExecute;
}MMC_MOVECIRCULARABSOLUTEBORDER_IN;

///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_MOVECIRCULARABSOLUTEBORDEREX_IN
/// \brief Move Circular Absolute Border Extended Command input data structure.
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
	double dBorderPoint[NC_MAX_NUM_AXES_IN_NODE];
	double dEndPoint[NC_MAX_NUM_AXES_IN_NODE];
	double dVelocity;
	double dAcceleration;
	double dDeceleration;
	double dJerk;
	double dTransitionParameter[NC_MAX_NUM_AXES_IN_NODE];
	MC_COORD_SYSTEM_ENUM eCoordSystem;
	NC_TRANSITION_MODE_ENUM eTransitionMode;
	MC_BUFFERED_MODE_ENUM eBufferMode;
	unsigned char ucSuperimposed;
	unsigned char ucExecute;
}MMC_MOVECIRCULARABSOLUTEBORDEREX_IN;

///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_MOVECIRCULARABSOLUTERADIUS_IN
/// \brief Move Circular Absolute Radius Command for input data structure.
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
	double dSpearHeadPoint[NC_MAX_NUM_AXES_IN_NODE];
	double dEndPoint[NC_MAX_NUM_AXES_IN_NODE];
	float fVelocity;
	float fAcceleration;
	float fDeceleration;
	float fJerk;
	float fTransitionParameter[NC_MAX_NUM_AXES_IN_NODE];
	NC_PATH_CHOICE_ENUM ePathChoice;
	NC_ARC_SHORT_LONG_ENUM eArcShortLong;
	MC_COORD_SYSTEM_ENUM eCoordSystem;
	NC_TRANSITION_MODE_ENUM eTransitionMode;
	MC_BUFFERED_MODE_ENUM eBufferMode;
	unsigned char ucSuperimposed;
	unsigned char ucExecute;
}MMC_MOVECIRCULARABSOLUTERADIUS_IN;

///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_MOVECIRCULARABSOLUTERADIUSEX_IN
/// \brief Move Circular Absolute Radius Extended Command for input data structure.
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
	double dSpearHeadPoint[NC_MAX_NUM_AXES_IN_NODE];
	double dEndPoint[NC_MAX_NUM_AXES_IN_NODE];
	double dVelocity;
	double dAcceleration;
	double dDeceleration;
	double dJerk;
	double dTransitionParameter[NC_MAX_NUM_AXES_IN_NODE];
	NC_PATH_CHOICE_ENUM ePathChoice;
	NC_ARC_SHORT_LONG_ENUM eArcShortLong;
	MC_COORD_SYSTEM_ENUM eCoordSystem;
	NC_TRANSITION_MODE_ENUM eTransitionMode;
	MC_BUFFERED_MODE_ENUM eBufferMode;
	unsigned char ucSuperimposed;
	unsigned char ucExecute;
}MMC_MOVECIRCULARABSOLUTERADIUSEX_IN;

///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_MOVECIRCULARABSOLUTEANGLE_IN
/// \brief Move Circular Absolute Radius Command for input data structure.
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
	double dCenterPoint[NC_MAX_NUM_AXES_IN_NODE];
	double dAngle;
	float fVelocity;
	float fAcceleration;
	float fDeceleration;
	float fJerk;
	float fTransitionParameter[NC_MAX_NUM_AXES_IN_NODE];
	MC_COORD_SYSTEM_ENUM eCoordSystem;
	NC_TRANSITION_MODE_ENUM eTransitionMode;
	MC_BUFFERED_MODE_ENUM eBufferMode;
	unsigned char ucSuperimposed;
	unsigned char ucExecute;
}MMC_MOVECIRCULARABSOLUTEANGLE_IN;

///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_MOVECIRCULARABSOLUTEANGLEEX_IN
/// \brief Move Circular Absolute Radius Extended Command for input data structure.
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
	double dCenterPoint[NC_MAX_NUM_AXES_IN_NODE];
	double dAngle;
	double dVelocity;
	double dAcceleration;
	double dDeceleration;
	double dJerk;
	double dTransitionParameter[NC_MAX_NUM_AXES_IN_NODE];
	MC_COORD_SYSTEM_ENUM eCoordSystem;
	NC_TRANSITION_MODE_ENUM eTransitionMode;
	MC_BUFFERED_MODE_ENUM eBufferMode;
	unsigned char ucSuperimposed;
	unsigned char ucExecute;
}MMC_MOVECIRCULARABSOLUTEANGLEEX_IN;

///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_MOVECIRCULARABSOLUTE_OUT
/// \brief Move Circular Absolute Command output data structure.
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
	unsigned int   uiHndl;			///< Function Block Handle.
	unsigned short usStatus;		///< Returned command status.
	short usErrorID;		///< Returned command error ID.
}MMC_MOVECIRCULARABSOLUTE_OUT;

///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_MOVECIRCULARABSOLUTEEX_OUT
/// \brief Move Circular Absolute Extended Command output data structure.
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
	unsigned int   uiHndl;			///< Function Block Handle.
	unsigned short usStatus;		///< Returned command status.
	short usErrorID;		///< Returned command error ID.
}MMC_MOVECIRCULARABSOLUTEEX_OUT;

///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_GROUPENABLE_IN
/// \brief Group Enable Command input data structure.
///
/// (See : " Technical Paper
///		PLCopen Technical Committee 2 – Task Force
///		Function Blocks for motion control:
///		Part 4 –Coordinated Motion")
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
	unsigned char ucExecute;
}MMC_GROUPENABLE_IN;

///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_GROUPENABLE_OUT
/// \brief Group Enable Command output data structure.
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
	unsigned short usStatus;		///< Returned command status.
	short usErrorID;		///< Returned command error ID.
}MMC_GROUPENABLE_OUT;

///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_GROUPDISABLE_IN
/// \brief Group Disable Command input data structure.
///
/// (See : " Technical Paper
///		PLCopen Technical Committee 2 – Task Force
///		Function Blocks for motion control:
///		Part 4 –Coordinated Motion")
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
	unsigned char ucExecute;
}MMC_GROUPDISABLE_IN;

///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_GROUPDISABLE_OUT
/// \brief Group Disable Command output data structure.
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
	unsigned short usStatus;		///< Returned command status.
	short usErrorID;		///< Returned command error ID.
}MMC_GROUPDISABLE_OUT;

///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_GROUPRESET_IN
/// \brief Group Reset Command input data structure.
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
	unsigned char ucExecute;
}MMC_GROUPRESET_IN;

///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_GROUPRESET_OUT
/// \brief Group Reset Command output data structure.
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
	unsigned short usStatus;
	short usErrorID;
}MMC_GROUPRESET_OUT;


///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_ADDAXISTOGROUP_IN
/// \brief Add Axis to Group input data structure.
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
	NC_NODE_HNDL_T hNode;
	NC_IDENT_IN_GROUP_ENUM eIdentInGroup;
}MMC_ADDAXISTOGROUP_IN;

///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_ADDAXISTOGROUP_OUT
/// \brief Add Axis to Group output data structure.
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
	unsigned short usStatus;
	short usErrorID;
}MMC_ADDAXISTOGROUP_OUT;

///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_REMOVEAXISFROMGROUP_IN
/// \brief Remove Axis from Group input data structure.
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
	NC_IDENT_IN_GROUP_ENUM eIdentInGroup;
}MMC_REMOVEAXISFROMGROUP_IN;

///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_REMOVEAXISFROMGROUP_OUT
/// \brief Remove Axis from Group output data structure.
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
	unsigned short usStatus;
	short usErrorID;
}MMC_REMOVEAXISFROMGROUP_OUT;

///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_GROUPSETPOSITION_IN
/// \brief Group Set Position Command input data structure.
///
/// (See : " Technical Paper
///		PLCopen Technical Committee 2 – Task Force
///		Function Blocks for motion control:
///		Part 4 –Coordinated Motion")
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
	double dbPosition[NC_MAX_NUM_AXES_IN_NODE];
	MC_COORD_SYSTEM_ENUM eCordSystem;
	MC_BUFFERED_MODE_ENUM eBufferMode;
	MC_EXECUTION_MODE eExecutionMode;
	unsigned char ucExecute;
	unsigned char ucMode;
} MMC_GROUPSETPOSITION_IN;

///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_GROUPSETPOSITION_OUT
/// \brief Group Set Position Command output data structure.
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
	unsigned short usStatus;		///< Returned command status.
	short usErrorID;		///< Returned command error ID.
} MMC_GROUPSETPOSITION_OUT;

///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_GROUPREADSTATUS_IN
/// \brief Group Read Status Command input data structure.
///
/// (See : " Technical Paper
///		PLCopen Technical Committee 2 – Task Force
///		Function Blocks for motion control:
///		Part 4 –Coordinated Motion")
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
	unsigned int  uiHndlr;	///< Group Handle.
	unsigned char ucEnable;	///< Enable read status flag.
} MMC_GROUPREADSTATUS_IN;

///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_GROUPREADSTATUS_OUT
/// \brief Group Read Status Command output data structure.
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
	unsigned long ulState;			///< Group current state.
	unsigned short usStatus;		///< Returned command status.
	short usErrorID;		///< Returned command error ID.
	unsigned short usGroupErrorID;	///< Group error ID.
} MMC_GROUPREADSTATUS_OUT;

///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_SETOVERRIDE_IN
/// \brief Set Override Command input data structure.
///
/// (See : "Technical Paper
///		PLCopen Technical Committee
///		Function Blocks for motion control:
///		Part 2 - Extensions")
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
	float fVelFactor;						///< New override factor for the velocity
	float fAccFactor;						///< New override factor for the acceleration/deceleration
	float fJerkFactor;						///< New override factor for the jerk
	unsigned short usUpdateVelFactorIdx;	///< Index of changed velocity factor. Vendor defined. (range from 1 till 3)
	unsigned char ucEnable;					///< If SET, it writes the value of the override factor continuously. If RESET it should keep the last value.
}MMC_SETOVERRIDE_IN;

///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_SETOVERRIDE_OUT
/// \brief Set Override Command output data structure.
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
	unsigned short usStatus;	///< Returned command status.
	short usErrorID;	///< Returned command error ID.
}MMC_SETOVERRIDE_OUT;

///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_MOVELINEARRELATIVE_IN
/// \brief Move Linear Relative Command input data structure.
///
/// (See : " Technical Paper
///		PLCopen Technical Committee 2 – Task Force
///		Function Blocks for motion control:
///		Part 4 –Coordinated Motion")
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
	double dbDistance[NC_MAX_NUM_AXES_IN_NODE]; 			///<Array [1..n] of relative distances for each dimension in the specified coordinate system. The value of n is supplier specific.
	float fVelocity;										///< Maximum Velocity [u/s] for the path for the coordinate system in which the path is defined. Always positive. Not necessarily reached
	float fAcceleration;									///< Maximum acceleration. Always positive. Not necessarily reached
	float fDeceleration;									///< Maximum deceleration. Always positive. Not necessarily reached
	float fJerk;											///< Maximum jerk. Always positive. Not necessarily reached
	float fTransitionParameter[NC_MAX_NUM_AXES_IN_NODE];	///< Additional parameter for the transition mode (n = supplier specific)
	MC_COORD_SYSTEM_ENUM eCoordSystem;						///< Reference to the applicable coordinate system: ACS, MCS, PCS
	NC_TRANSITION_MODE_ENUM eTransitionMode;				///< See 2.4.3 Overview of Transition Mode
	MC_BUFFERED_MODE_ENUM eBufferMode;						///< Defines the chronological sequence of the FB relative to the previous block. Refer to Chapter 7.3 Buffer Modes
	unsigned char ucSuperimposed;							///< Selection if the motion functionality is superimposed to the existingc movement. Default value = 0, meaning not superimposed (normal operation)
	unsigned char ucExecute;								///< Start the motion at rising edge
}MMC_MOVELINEARRELATIVE_IN;

///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_MOVELINEARRELATIVE_OUT
/// \brief Move Linear Relative Command output data structure.
///////////////////////////////////////////////////////////////////////////////
typedef struct mmc_movealinearrelative_out
{
	unsigned int   uiHndl;			///< Returned Function Block Handle.
	unsigned short usStatus;		///< Returned command status.
	short usErrorID;		///< Returned command error ID.
}MMC_MOVELINEARRELATIVE_OUT;

///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_MOVELINEARRELATIVEEX_IN
/// \brief Move Linear Relative Extended Command input data structure.
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
	double dbDistance[NC_MAX_NUM_AXES_IN_NODE]; 			///<Array [1..n] of relative distances for each dimension in the specified coordinate system. The value of n is supplier specific.
	double dVelocity;										///< Maximum Velocity [u/s] for the path for the coordinate system in which the path is defined. Always positive. Not necessarily reached
	double dAcceleration;									///< Maximum acceleration. Always positive. Not necessarily reached
	double dDeceleration;									///< Maximum deceleration. Always positive. Not necessarily reached
	double dJerk;											///< Maximum jerk. Always positive. Not necessarily reached
	double dTransitionParameter[NC_MAX_NUM_AXES_IN_NODE];	///< Additional parameter for the transition mode (n = supplier specific)
	MC_COORD_SYSTEM_ENUM eCoordSystem;						///< Reference to the applicable coordinate system: ACS, MCS, PCS
	NC_TRANSITION_MODE_ENUM eTransitionMode;				///< See 2.4.3 Overview of Transition Mode
	MC_BUFFERED_MODE_ENUM eBufferMode;						///< Defines the chronological sequence of the FB relative to the previous block. Refer to Chapter 7.3 Buffer Modes
	unsigned char ucSuperimposed;							///< Selection if the motion functionality is superimposed to the existingc movement. Default value = 0, meaning not superimposed (normal operation)
	unsigned char ucExecute;								///< Start the motion at rising edge
}MMC_MOVELINEARRELATIVEEX_IN;

///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_MOVELINEARRELATIVEEX_OUT
/// \brief Move Linear Relative Extended Command output data structure.
///////////////////////////////////////////////////////////////////////////////
typedef struct mmc_movealinearrelativeex_out
{
	unsigned int   uiHndl;			///< Returned Function Block Handle.
	unsigned short usStatus;		///< Returned command status.
	short usErrorID;		///< Returned command error ID.
}MMC_MOVELINEARRELATIVEEX_OUT;

///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_MOVELINEARABSOLUTE_IN
/// \brief Move Linear Absolute Command input data structure.
///
/// (See : " Technical Paper
///		PLCopen Technical Committee 2 – Task Force
///		Function Blocks for motion control:
///		Part 4 –Coordinated Motion")
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
	double dbPosition[NC_MAX_NUM_AXES_IN_NODE];				///< Array [1..N] of absolute end positions for each dimension in the specified coordinate system. The value of n is supplier specific. See 1.4 Glossary
	float fVelocity;										///< Maximum Velocity [u/s] for the path for the coordinate system in which the path is defined. Always positive. Not necessarily reached
	float fAcceleration;									///< Maximum acceleration. Always positive. Not necessarily reached
	float fDeceleration;									///< Maximum deceleration. Always positive. Not necessarily reached
	float fJerk;											///< Maximum jerk. Always positive. Not necessarily reached
	float fTransitionParameter[NC_MAX_NUM_AXES_IN_NODE];	///< Additional parameter for the transition mode (n = supplier specific)
	MC_COORD_SYSTEM_ENUM eCoordSystem;						///< Reference to the applicable coordinate system: ACS, MCS, PCS
	NC_TRANSITION_MODE_ENUM eTransitionMode;				///< See 2.4.3 Overview of Transition Mode
	MC_BUFFERED_MODE_ENUM eBufferMode;						///< Defines the chronological sequence of the FB relative to the previous block. Refer to Chapter 7.3 Buffer Modes
	unsigned char ucSuperimposed;							///< Selection if the motion functionality is superimposed to the existingc movement. Default value = 0, meaning not superimposed (normal operation)
	unsigned char ucExecute;								///< Start the motion at rising edge
}MMC_MOVELINEARABSOLUTE_IN;

///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_MOVELINEARABSOLUTE_OUT
/// \brief Move Linear Absolute Command output data structure.
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
	unsigned int   uiHndl;			///< Returned Function Block Handle.
	unsigned short usStatus;		///< Returned command status.
	short usErrorID;		///< Returned command error ID.
}MMC_MOVELINEARABSOLUTE_OUT;

///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_MOVELINEARABSOLUTEEX_IN
/// \brief Move Linear Absolute Extended Command input data structure.
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
	double dbPosition[NC_MAX_NUM_AXES_IN_NODE];				///< Array [1..N] of absolute end positions for each dimension in the specified coordinate system. The value of n is supplier specific. See 1.4 Glossary
	double dVelocity;										///< Maximum Velocity [u/s] for the path for the coordinate system in which the path is defined. Always positive. Not necessarily reached
	double dAcceleration;									///< Maximum acceleration. Always positive. Not necessarily reached
	double dDeceleration;									///< Maximum deceleration. Always positive. Not necessarily reached
	double dJerk;											///< Maximum jerk. Always positive. Not necessarily reached
	double dTransitionParameter[NC_MAX_NUM_AXES_IN_NODE];	///< Additional parameter for the transition mode (n = supplier specific)
	MC_COORD_SYSTEM_ENUM eCoordSystem;						///< Reference to the applicable coordinate system: ACS, MCS, PCS
	NC_TRANSITION_MODE_ENUM eTransitionMode;				///< See 2.4.3 Overview of Transition Mode
	MC_BUFFERED_MODE_ENUM eBufferMode;						///< Defines the chronological sequence of the FB relative to the previous block. Refer to Chapter 7.3 Buffer Modes
	unsigned char ucSuperimposed;							///< Selection if the motion functionality is superimposed to the existingc movement. Default value = 0, meaning not superimposed (normal operation)
	unsigned char ucExecute;								///< Start the motion at rising edge
}MMC_MOVELINEARABSOLUTEEX_IN;

///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_MOVELINEARABSOLUTEEX_OUT
/// \brief Move Linear Absolute Extended Command output data structure.
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
	unsigned int   uiHndl;			///< Returned Function Block Handle.
	unsigned short usStatus;		///< Returned command status.
	short usErrorID;		///< Returned command error ID.
}MMC_MOVELINEARABSOLUTEEX_OUT;

///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_MOVELINEARADDOTIVE_IN
/// \brief Move Linear Additive Command input data structure.
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
	double dbDistance[NC_MAX_NUM_AXES_IN_NODE]; 			///<Array [1..n] of additive distances for each dimension in the specified coordinate system. The value of n is supplier specific.
	float fVelocity;										///< Maximum Velocity [u/s] for the path for the coordinate system in which the path is defined. Always positive. Not necessarily reached
	float fAcceleration;									///< Maximum acceleration. Always positive. Not necessarily reached
	float fDeceleration;									///< Maximum deceleration. Always positive. Not necessarily reached
	float fJerk;											///< Maximum jerk. Always positive. Not necessarily reached
	float fTransitionParameter[NC_MAX_NUM_AXES_IN_NODE];	///< Additional parameter for the transition mode (n = supplier specific)
	MC_COORD_SYSTEM_ENUM eCoordSystem;						///< Reference to the applicable coordinate system: ACS, MCS, PCS
	NC_TRANSITION_MODE_ENUM eTransitionMode;				///< See 2.4.3 Overview of Transition Mode
	MC_BUFFERED_MODE_ENUM eBufferMode;						///< Defines the chronological sequence of the FB relative to the previous block. Refer to Chapter 7.3 Buffer Modes
	unsigned char ucSuperimposed;							///< Selection if the motion functionality is superimposed to the existingc movement. Default value = 0, meaning not superimposed (normal operation)
	unsigned char ucExecute;								///< Start the motion at rising edge
}MMC_MOVELINEARADDITIVE_IN;

///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_MOVELINEARADDITIVE_OUT
/// \brief Move Linear Additive Command output data structure.
///////////////////////////////////////////////////////////////////////////////
typedef struct mmc_movealinearadditive_out
{
	unsigned int   uiHndl;			///< Returned Function Block Handle.
	unsigned short usStatus;		///< Returned command status.
	short usErrorID;		///< Returned command error ID.
}MMC_MOVELINEARADDITIVE_OUT;

///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_MOVELINEARADDITIVEEX_IN
/// \brief Move Linear Additive Extended Command input data structure.
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
	double dbDistance[NC_MAX_NUM_AXES_IN_NODE]; 			///<Array [1..n] of relative distances for each dimension in the specified coordinate system. The value of n is supplier specific.
	double dVelocity;										///< Maximum Velocity [u/s] for the path for the coordinate system in which the path is defined. Always positive. Not necessarily reached
	double dAcceleration;									///< Maximum acceleration. Always positive. Not necessarily reached
	double dDeceleration;									///< Maximum deceleration. Always positive. Not necessarily reached
	double dJerk;											///< Maximum jerk. Always positive. Not necessarily reached
	double dTransitionParameter[NC_MAX_NUM_AXES_IN_NODE];	///< Additional parameter for the transition mode (n = supplier specific)
	MC_COORD_SYSTEM_ENUM eCoordSystem;						///< Reference to the applicable coordinate system: ACS, MCS, PCS
	NC_TRANSITION_MODE_ENUM eTransitionMode;				///< See 2.4.3 Overview of Transition Mode
	MC_BUFFERED_MODE_ENUM eBufferMode;						///< Defines the chronological sequence of the FB relative to the previous block. Refer to Chapter 7.3 Buffer Modes
	unsigned char ucSuperimposed;							///< Selection if the motion functionality is superimposed to the existingc movement. Default value = 0, meaning not superimposed (normal operation)
	unsigned char ucExecute;								///< Start the motion at rising edge
}MMC_MOVELINEARADDITIVEEX_IN;

///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_MOVELINEARADDITIVEEX_OUT
/// \brief Move Linear Additive Extended Command output data structure.
///////////////////////////////////////////////////////////////////////////////
typedef struct mmc_movealinearadditiveex_out
{
	unsigned int   uiHndl;			///< Returned Function Block Handle.
	unsigned short usStatus;		///< Returned command status.
	short usErrorID;		///< Returned command error ID.
}MMC_MOVELINEARADDITIVEEX_OUT;


///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_MOVEPOLYNOMABSOLUTE_IN
/// \brief Move Polynom Absolute Extended Command input data structure.
///////////////////////////////////////////////////////////////////////////////
typedef struct 
{
	double dbAuxPoint[NC_MAX_NUM_AXES_IN_NODE]; 			///<Array [1..n] of absolute positions to define the auxiliary point, in the specified coordinate system. The value of n is supplier specific.
	double dbEndPoint[NC_MAX_NUM_AXES_IN_NODE]; 			///<Array [1..n] of absolute target positions for each dimension in the specified coordinate system. The value of n is supplier specific.
	double dVelocity;										///< Maximum Velocity [u/s] for the path for the coordinate system in which the path is defined. Always positive. Not necessarily reached
	double dAcceleration;									///< Maximum acceleration. Always positive. Not necessarily reached
	double dDeceleration;									///< Maximum deceleration. Always positive. Not necessarily reached
	double dJerk;											///< Maximum jerk. Always positive. Not necessarily reached
	MC_COORD_SYSTEM_ENUM eCoordSystem;						///< Reference to the applicable coordinate system: ACS, MCS, PCS
	MC_BUFFERED_MODE_ENUM eBufferMode;						///< Defines the chronological sequence of the FB relative to the previous block. Refer to Chapter 7.3 Buffer Modes
	unsigned char ucSuperimposed;							///< Selection if the motion functionality is superimposed to the existingc movement. Default value = 0, meaning not superimposed (normal operation)
	unsigned char ucExecute;								///< Start the motion at rising edge
}MMC_MOVEPOLYNOMABSOLUTE_IN;

///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_MOVEPOLYNOMABSOLUTE_OUT
/// \brief Move Polynom Absolute Extended Command output data structure.
///////////////////////////////////////////////////////////////////////////////
typedef struct 
{
	unsigned int   uiHndl;			///< Returned Function Block Handle.
	unsigned short usStatus;		///< Returned command status.
	short usErrorID;		///< Returned command error ID.
}MMC_MOVEPOLYNOMABSOLUTE_OUT;


typedef struct mmc_group_stop_in
{
	float fDeceleration;
	float fJerk;
	MC_BUFFERED_MODE_ENUM eBufferMode;
	unsigned char ucExecute;
}MMC_GROUPSTOP_IN;

typedef struct mmc_group_stop_out
{
	unsigned int   uiHndl;
	unsigned short usStatus;
	short usErrorID;
}MMC_GROUPSTOP_OUT;

typedef struct mmc_group_halt_in
{
	float fDeceleration;
	float fJerk;
	MC_BUFFERED_MODE_ENUM eBufferMode;
	unsigned char ucExecute;
}MMC_GROUPHALT_IN;

typedef struct mmc_group_halt_out
{
	unsigned int   uiHndl;
	unsigned short usStatus;
	short usErrorID;
}MMC_GROUPHALT_OUT;

typedef struct {
	unsigned long ulStatus;
	double aPos[NC_MAX_NUM_AXES_IN_NODE];
	double aVel[NC_MAX_NUM_AXES_IN_NODE];
	double aACDC[NC_MAX_NUM_AXES_IN_NODE];
}NC_VECT_MIRROR_DATA_STRUCT;

/* Alex: Integration of MoveRepetitive functions */
///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_MOVELINEARABSOLUTEREPETITIVE_IN
/// \brief Move Linear Absolute Repetitive Command input data structure.
///////////////////////////////////////////////////////////////////////////////
typedef struct mmc_movelinearabsoluterepetitive_in
{
	double dbPosition[NC_MAX_NUM_AXES_IN_NODE];
	float fVelocity;
	float fAcceleration;
	float fDeceleration;
	float fJerk;
	MC_COORD_SYSTEM_ENUM eCoordSystem;
	MC_BUFFERED_MODE_ENUM eBufferMode;
	unsigned int uiExecDelayMs;
	unsigned char ucSuperImposed;
	unsigned char ucExecute;
//	NC_TRANSITION_MODE_ENUM eTransitionMode;
//	float fTransitionParameter[NC_MAX_NUM_AXES_IN_NODE];
} MMC_MOVELINEARABSOLUTEREPETITIVE_IN;

///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_MOVELINEARABSOLUTEREPETITIVE_OUT
/// \brief Move Linear Absolute Repetitive Command output data structure.
///////////////////////////////////////////////////////////////////////////////
typedef struct mmc_movelinearabsoluterepetitive_out
{
	unsigned int uiHndl;
	unsigned short usStatus;
	short usErrorID;
} MMC_MOVELINEARABSOLUTEREPETITIVE_OUT;

///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_MOVELINEARABSOLUTEREPETITIVE_IN
/// \brief Move Linear Absolute Repetitive Command input data structure.
///////////////////////////////////////////////////////////////////////////////
typedef struct mmc_movelinearabsoluterepetitiveex_in
{
	double dbPosition[NC_MAX_NUM_AXES_IN_NODE];
	double dVelocity;
	double dAcceleration;
	double dDeceleration;
	double dJerk;
	MC_COORD_SYSTEM_ENUM eCoordSystem;
	MC_BUFFERED_MODE_ENUM eBufferMode;
	unsigned int uiExecDelayMs;
	unsigned char ucSuperImposed;
	unsigned char ucExecute;
} MMC_MOVELINEARABSOLUTEREPETITIVEEX_IN;

///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_MOVELINEARABSOLUTEREPETITIVE_OUT
/// \brief Move Linear Absolute Repetitive Command output data structure.
///////////////////////////////////////////////////////////////////////////////
typedef struct mmc_movelinearabsoluterepetitiveex_out
{
	unsigned int uiHndl;
	unsigned short usStatus;
	short usErrorID;
} MMC_MOVELINEARABSOLUTEREPETITIVEEX_OUT;

///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_MOVELINEARRELATIVEREPETITIVE_IN
/// \brief Move Linear Relative Repetitive Command input data structure.
///////////////////////////////////////////////////////////////////////////////
typedef struct mmc_movelinearrelativerepetitive_in
{
	double dbPosition[NC_MAX_NUM_AXES_IN_NODE];
	float fVelocity;
	float fAcceleration;
	float fDeceleration;
	float fJerk;
	MC_COORD_SYSTEM_ENUM eCoordSystem;
	MC_BUFFERED_MODE_ENUM eBufferMode;
	unsigned int uiExecDelayMs;
	unsigned char ucSuperImposed;
	unsigned char ucExecute;
} MMC_MOVELINEARRELATIVEREPETITIVE_IN;

///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_MOVELINEARRELATIVEREPETITIVE_OUT
/// \brief Move Linear Relative Repetitive Command output data structure.
///////////////////////////////////////////////////////////////////////////////
typedef struct mmc_movelinearrelativerepetitive_out
{
	unsigned int uiHndl;
	unsigned short usStatus;
	short usErrorID;
} MMC_MOVELINEARRELATIVEREPETITIVE_OUT;


///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_MOVELINEARRELATIVEREPETITIVEEX_IN
/// \brief Move Linear Relative Repetitive Ex Command input data structure.
///////////////////////////////////////////////////////////////////////////////
typedef struct mmc_movelinearrelativerepetitiveex_in
{
	double dbPosition[NC_MAX_NUM_AXES_IN_NODE];
	double dVelocity;
	double dAcceleration;
	double dDeceleration;
	double dJerk;
	MC_COORD_SYSTEM_ENUM eCoordSystem;
	MC_BUFFERED_MODE_ENUM eBufferMode;
	unsigned int uiExecDelayMs;
	unsigned char ucSuperImposed;
	unsigned char ucExecute;
} MMC_MOVELINEARRELATIVEREPETITIVEEX_IN;

///////////////////////////////////////////////////////////////////////////////
/// \struct MMC_MOVELINEARRELATIVEREPETITIVE_OUT
/// \brief Move Linear Relative Repetitive Command output data structure.
///////////////////////////////////////////////////////////////////////////////
typedef struct mmc_movelinearrelativerepetitiveex_out
{
	unsigned int uiHndl;
	unsigned short usStatus;
	short usErrorID;
} MMC_MOVELINEARRELATIVEREPETITIVEEX_OUT;




/* Alex 13/03/2011: Splines user interface structures */

typedef char MC_PATH_DATA_REF[NC_MAX_SPLINES_FILE_PATH_LENGTH];
typedef unsigned int MC_PATH_REF;
///////////////////////////////////////////////////////////
/// \struct MMC_PATHSELECT_IN
/// \brief Path Select Command input data structure.
///////////////////////////////////////////////////////////
typedef struct mmc_pathselect_in
{
	MC_COORD_SYSTEM_ENUM 	eCoordSystem;
	MC_PATH_DATA_REF 		pPathToSplineFile;
	unsigned char 			ucExecute;
} MMC_PATHSELECT_IN;

////////////////////////////////////////////////////////
/// \struct MMC_PATHSELECT_OUT
/// \brief Path Select Command output data structure.
////////////////////////////////////////////////////////
typedef struct mmc_pathselect_out
{
	MC_PATH_REF 	hMemHandle;
	unsigned short usStatus;
	short usErrorID;
} MMC_PATHSELECT_OUT;

typedef struct mmc_pathgetlengths_in
{
	MC_PATH_REF hMemHandle;
	unsigned int uiStartSeg;
	unsigned int uiSegmentsNum;
	unsigned char ucExecute;
	unsigned char spare[32];
} MMC_PATHGETLENGTHS_IN;

#define RPC_PATH_MAX_LENGTHS 								170 //TCP MTU 1400 -> sizeof(double) * 170 and save some for data structure

typedef struct mmc_pathgetlengths_out
{
	double dbLengths[RPC_PATH_MAX_LENGTHS];	//store returned length values
	int iRetValues;									//number of returned values
	unsigned short usStatus;						//device status
	unsigned short usErrorID;						//error id in case of error, otherwise 0.
	unsigned char spare[32];
} MMC_PATHGETLENGTHS_OUT;

////////////////////////////////////////////////////////
/// \struct MMC_MOVEPATH_IN
/// \brief Move Path Command input data structure.
////////////////////////////////////////////////////////
typedef struct mmc_movepath_in
{
	float fTransitionParameter[NC_MAX_NUM_AXES_IN_NODE];
	MC_COORD_SYSTEM_ENUM eCoordSystem;
	NC_TRANSITION_MODE_ENUM eTransitionMode;
	MC_BUFFERED_MODE_ENUM eBufferMode;
	MC_PATH_REF hMemHandle;
	unsigned char ucSuperImposed;
	unsigned char ucExecute;
} MMC_MOVEPATH_IN;

////////////////////////////////////////////////////////
/// \struct MMC_MOVEPATH_OUT
/// \brief Move Path Command output data structure.
////////////////////////////////////////////////////////
typedef struct mmc_movepath_out
{
	unsigned int uiHandle;
	unsigned short usStatus;
	short usErrorID;
} MMC_MOVEPATH_OUT;

/////////////////////////////////////////////////////////
/// \struct MMC_PATHUNSELECT_IN
/// \brief Path Unselect Command input data structure.
/////////////////////////////////////////////////////////
typedef struct mmc_pathunselect_in
{
	MC_PATH_REF hMemHandle;
	unsigned char ucExecute;
} MMC_PATHUNSELECT_IN;

///////////////////////////////////////////////////////////
/// \struct MMC_PATHUNSELECT_OUT
/// \brief Path Unselect Command input data structure.
///////////////////////////////////////////////////////////
typedef struct mmc_pathunselect_out
{
	unsigned short usStatus;
	short usErrorID;
} MMC_PATHUNSELECT_OUT;



/////////////////////////////////////////////////////////
/// \struct MMC_GETGROUPMEMBERSINFO_IN
/// \brief Get Group members info Command input data structure.
/////////////////////////////////////////////////////////
typedef struct mmc_getgroupmembersinfo_in
{
	unsigned char ucDummy;
} MMC_GETGROUPMEMBERSINFO_IN;


///////////////////////////////////////////////////////////
/// \struct MMC_GETGROUPMEMBERSINFO_OUT
/// \brief Get Group members info Command input data structure.
///////////////////////////////////////////////////////////
typedef struct mmc_getgroupmembersinfo_out
{
	unsigned short pAxesReferences[NC_MAX_NUM_AXES_IN_NODE];
	unsigned short pDeviceID[NC_MAX_NUM_AXES_IN_NODE];
	unsigned short usStatus;
	short usErrorID;
	char pAxesNames[NC_MAX_NUM_AXES_IN_NODE][NODE_NAME_MAX_LENGTH];
	unsigned char ucNumOfAxes;
} MMC_GETGROUPMEMBERSINFO_OUT;



/////// functions



////////////////////////////////////////////////////////////////////////////////
/// \fn int   MMC_ReadParameter(
///					IN MMC_CONNECT_HNDL hConn,
///					IN MMC_AXIS_REF_HNDL hAxisRef,
///					IN MMC_READPARAMETER_IN* pInParam,
///					OUT MMC_READPARAMETER_OUT* pOutParam)
/// \brief This function read specific axis parameter.
/// \param  hConn - [IN] Connection handle
/// \param  hAxisRef - [IN] Axis Reference handle
/// \param  pInParam - [IN] Pointer to Read Parameter input parameters
/// \param  pOutParam - [OUT] Pointer to Read Parameter output parameters
/// \return	return - 0 if success
/// 				 error_id in case of error
////////////////////////////////////////////////////////////////////////////////
MMC_LIB_API int MMC_GroupReadParameter(
		IN MMC_CONNECT_HNDL hConn,
		IN MMC_AXIS_REF_HNDL hAxisRef,
		IN MMC_READPARAMETER_IN* pInParam,
		OUT MMC_READPARAMETER_OUT* pOutParam);

////////////////////////////////////////////////////////////////////////////////
/// \fn int   MMC_ReadBoolParameter(
///					IN MMC_CONNECT_HNDL hConn,
///					IN MMC_AXIS_REF_HNDL hAxisRef,
///					IN MMC_READBOOLPARAMETER_IN* pInParam,
///					OUT MMC_READBOOLPARAMETER_OUT* pOutParam)
/// \brief This function read boolean specific axis parameter.
/// \param  hConn - [IN] Connection handle
/// \param  hAxisRef - [IN] Axis Reference handle
/// \param  pInParam - [IN] Pointer to Read Boolean Parameter input parameters
/// \param  pOutParam - [OUT] Pointer to Read Boolean Parameter output parameters
/// \return	return - 0 if success
/// 				 error_id in case of error
////////////////////////////////////////////////////////////////////////////////
MMC_LIB_API int MMC_GroupReadBoolParameter(
		IN MMC_CONNECT_HNDL hConn,
		IN MMC_AXIS_REF_HNDL hAxisRef,
		IN MMC_READBOOLPARAMETER_IN* pInParam,
		OUT MMC_READBOOLPARAMETER_OUT* pOutParam);

////////////////////////////////////////////////////////////////////////////////
/// \fn int   MMC_WriteParameter(
///					IN MMC_CONNECT_HNDL hConn,
///					IN MMC_AXIS_REF_HNDL hAxisRef,
///					IN MMC_WRITEPARAMETER_IN* pInParam,
///					OUT MMC_WRITEPARAMETER_OUT* pOutParam)
/// \brief This function write specific axis parameter.
/// \param  hConn - [IN] Connection handle
/// \param  hAxisRef - [IN] Axis Reference handle
/// \param  pInParam - [IN] Pointer to Write Parameter input parameters
/// \param  pOutParam - [OUT] Pointer to Write Parameter output parameters
/// \return	return - 0 if success
/// 				 error_id in case of error
////////////////////////////////////////////////////////////////////////////////
MMC_LIB_API int MMC_GroupWriteParameter(
		IN MMC_CONNECT_HNDL hConn,
		IN MMC_AXIS_REF_HNDL hAxisRef,
		IN MMC_WRITEPARAMETER_IN* pInParam,
		OUT MMC_WRITEPARAMETER_OUT* pOutParam);

////////////////////////////////////////////////////////////////////////////////
/// \fn int   MMC_WriteBoolParameter(
///					IN MMC_CONNECT_HNDL hConn,
///					IN MMC_AXIS_REF_HNDL hAxisRef,
///					IN MMC_WRITEBOOLPARAMETER_IN* pInParam,
///					OUT MMC_WRITEBOOLPARAMETER_OUT* pOutParam)
/// \brief This function write boolean specific axis parameter.
/// \param  hConn - [IN] Connection handle
/// \param  hAxisRef - [IN] Axis Reference handle
/// \param  pInParam - [IN] Pointer to Write Boolean Parameter input parameters
/// \param  pOutParam - [OUT] Pointer to Write Boolean Parameter output parameters
/// \return	return - 0 if success
/// 				 error_id in case of error
////////////////////////////////////////////////////////////////////////////////
MMC_LIB_API int MMC_GroupWriteBoolParameter(
		IN MMC_CONNECT_HNDL hConn,
		IN MMC_AXIS_REF_HNDL hAxisRef,
		IN MMC_WRITEBOOLPARAMETER_IN* pInParam,
		OUT MMC_WRITEBOOLPARAMETER_OUT* pOutParam);



////////////////////////////////////////////////////////////////////////////////
/// \fn int MMC_SetKinTransform(
///				IN MMC_CONNECT_HNDL hConn,
///				IN MMC_AXIS_REF_HNDL hAxisRef,
///				IN MMC_SETKINTRANSFORM_IN* pInParam,
///				OUT MMC_SETKINTRANSFORM_OUT* pOutParam)
/// \brief This function set group's kinematic transformation parameter.
/// \param  hConn - [IN] Connection handle
/// \param  hAxisRef - [IN] Axis Reference handle
/// \param  pInParam - [IN] Pointer to Set Kinematic Transform input parameters
/// \param  pOutParam - [OUT] Pointer to Set Kinematic Transform output parameters
/// \return	return - 0 if success
/// 				 error_id in case of error
////////////////////////////////////////////////////////////////////////////////
MMC_LIB_API int MMC_SetKinTransform(
		IN MMC_CONNECT_HNDL hConn,
		IN MMC_AXIS_REF_HNDL hAxisRef,
		IN MMC_SETKINTRANSFORM_IN* pInParam,
		OUT MMC_SETKINTRANSFORM_OUT* pOutParam);

////////////////////////////////////////////////////////////////////////////////
/// \fn int MMC_SetKinTransformEx(
///				IN MMC_CONNECT_HNDL hConn,
///				IN MMC_AXIS_REF_HNDL hAxisRef,
///				IN MMC_SETKINTRANSFORM_IN* pInParam,
///				OUT MMC_SETKINTRANSFORM_OUT* pOutParam)
/// \brief This function set group's kinematic transformation parameter.
/// \param  hConn - [IN] Connection handle
/// \param  hAxisRef - [IN] Axis Reference handle
/// \param  pInParam - [IN] Pointer to Set Kinematic Transform input parameters
/// \param  pOutParam - [OUT] Pointer to Set Kinematic Transform output parameters
/// \return	return - 0 if success
/// 				 error_id in case of error
////////////////////////////////////////////////////////////////////////////////
MMC_LIB_API int MMC_SetKinTransformEx(
		IN MMC_CONNECT_HNDL hConn,
		IN MMC_AXIS_REF_HNDL hAxisRef,
		IN MMC_SETKINTRANSFORMEX_IN* pInParam,
		OUT MMC_SETKINTRANSFORMEX_OUT* pOutParam);

////////////////////////////////////////////////////////////////////////////////
/// \fn int MMC_SetCartesianTransform(
///				IN MMC_CONNECT_HNDL hConn,
///				IN MMC_AXIS_REF_HNDL hAxisRef,
///				IN MMC_SETKINTRANSFORM_IN* pInParam,
///				OUT MMC_SETKINTRANSFORM_OUT* pOutParam)
/// \brief This function set group's cartesian MCS<->PCS transformation parameters.
/// \param  hConn - [IN] Connection handle
/// \param  hAxisRef - [IN] Axis Reference handle
/// \param  pInParam - [IN] Pointer to Set Cartesian Transform input parameters
/// \param  pOutParam - [OUT] Pointer to Set Cartesian Transform output parameters
/// \return	return - 0 if success
/// 				 error_id in case of error
////////////////////////////////////////////////////////////////////////////////
MMC_LIB_API int MMC_SetCartesianTransform(
		IN MMC_CONNECT_HNDL hConn,
		IN MMC_AXIS_REF_HNDL hAxisRef,
		IN MMC_SETCARTESIANTRANSFORM_IN* pInParam,
		OUT MMC_SETCARTESIANTRANSFORM_OUT* pOutParam);

////////////////////////////////////////////////////////////////////////////////
/// \fn int MMC_TrackConveyorBelt(
///				IN MMC_CONNECT_HNDL hConn,
///				IN MMC_AXIS_REF_HNDL hAxisRef,
///				IN MMC_TRACKCONVEYORBELT_IN* pInParam,
///				OUT MMC_TRACKCONVEYORBELT_OUT* pOutParam)
/// \brief This function set group's cartesian MCS<->PCS transformation parameters.
/// \param  hConn - [IN] Connection handle
/// \param  hAxisRef - [IN] Axis Reference handle
/// \param  pInParam - [IN] Pointer to Set Cartesian Transform input parameters
/// \param  pOutParam - [OUT] Pointer to Set Cartesian Transform output parameters
/// \return	return - 0 if success
/// 				 error_id in case of error
////////////////////////////////////////////////////////////////////////////////
MMC_LIB_API int MMC_TrackConveyorBelt(
		IN MMC_CONNECT_HNDL hConn,
		IN MMC_AXIS_REF_HNDL hAxisRef,
		IN MMC_TRACKCONVEYORBELT_IN* pInParam,
		OUT MMC_TRACKCONVEYORBELT_OUT* pOutParam);

////////////////////////////////////////////////////////////////////////////////
/// \fn int MMC_TrackRotaryTable(
///				IN MMC_CONNECT_HNDL hConn,
///				IN MMC_AXIS_REF_HNDL hAxisRef,
///				IN MMC_TRACKROTARYTABLE_IN* pInParam,
///				OUT MMC_TRACKROTARYTABLE_OUT* pOutParam)
/// \brief This function set group's cartesian MCS<->PCS transformation parameters.
/// \param  hConn - [IN] Connection handle
/// \param  hAxisRef - [IN] Axis Reference handle
/// \param  pInParam - [IN] Pointer to Set Cartesian Transform input parameters
/// \param  pOutParam - [OUT] Pointer to Set Cartesian Transform output parameters
/// \return	return - 0 if success
/// 				 error_id in case of error
////////////////////////////////////////////////////////////////////////////////
MMC_LIB_API int MMC_TrackRotaryTable(
		IN MMC_CONNECT_HNDL hConn,
		IN MMC_AXIS_REF_HNDL hAxisRef,
		IN MMC_TRACKROTARYTABLE_IN* pInParam,
		OUT MMC_TRACKROTARYTABLE_OUT* pOutParam);

////////////////////////////////////////////////////////////////////////////////
/// \fn int MMC_RemoveAxisFromGroup(
///				IN MMC_CONNECT_HNDL hConn,
///				IN MMC_AXIS_REF_HNDL hAxisRef,
///				IN MMC_REMOVEAXISFROMGROUP_IN* pInParam,
///				OUT MMC_REMOVEAXISFROMGROUP_OUT* pOutParam)
/// \brief This function remove axis from axis group.
/// \param  hConn - [IN] Connection handle
/// \param  hAxisRef - [IN] Axis Reference handle
/// \param  pInParam - [IN] Pointer to Remove Axis From Group input parameters
/// \param  pOutParam - [OUT] Pointer to Remove Axis From Group output parameters
/// \return	return - 0 if success
/// 				 error_id in case of error
////////////////////////////////////////////////////////////////////////////////
MMC_LIB_API int MMC_RemoveAxisFromGroup(
		IN MMC_CONNECT_HNDL hConn,
		IN MMC_AXIS_REF_HNDL hAxisRef,
		IN MMC_REMOVEAXISFROMGROUP_IN* pInParam,
		OUT MMC_REMOVEAXISFROMGROUP_OUT* pOutParam);

////////////////////////////////////////////////////////////////////////////////
/// \fn int MMC_MoveCircularAbsoluteCmd(
///				IN MMC_CONNECT_HNDL hConn,
///				IN MMC_AXIS_REF_HNDL hAxisRef,
///				IN MMC_MOVECIRCULARABSOLUTE_IN* pInParam,
///				OUT MMC_MOVECIRCULARABSOLUTE_OUT* pOutParam)
/// \brief This function This function  send Move Circular Absolute command to MMC server for specific Group.
/// \param  hConn - [IN] Connection handle
/// \param  hAxisRef - [IN] Axis Reference handle
/// \param  pInParam - [IN] Pointer to Move Circular Absolute input parameters
/// \param  pOutParam - [OUT] Pointer to Move Circular Absolute output parameters
/// \return	return - 0 if success
/// 				 error_id in case of error
////////////////////////////////////////////////////////////////////////////////
MMC_LIB_API int MMC_MoveCircularAbsoluteCmd(
		IN MMC_CONNECT_HNDL hConn,
		IN MMC_AXIS_REF_HNDL hAxisRef,
		IN MMC_MOVECIRCULARABSOLUTE_IN* pInParam,
		OUT MMC_MOVECIRCULARABSOLUTE_OUT* pOutParam);

/// \fn int MMC_MoveCircularAbsoluteExCmd(IN MMC_CONNECT_HNDL hConn,
///										  IN MMC_AXIS_REF_HNDL hAxisRef,
///										  IN MMC_MOVECIRCULARABSOLUTEEX_IN* pInParam,
///										  OUT MMC_MOVECIRCULARABSOLUTEEX_OUT* pOutParam)
/// \brief This function This function  is similar to MMC_MoveCircularAbsoluteCmd, except the fact that all float
///		   input parameters were converted to double
/// \param  hConn - [IN] Connection handle
/// \param  hAxisRef - [IN] Axis Reference handle
/// \param  pInParam - [IN] Pointer to Move Circular Absolute Extended input parameters
/// \param  pOutParam - [OUT] Pointer to Move Circular Absolute Extended output parameters
/// \return	return - 0 if success
/// 				 error_id in case of error
////////////////////////////////////////////////////////////////////////////////
MMC_LIB_API int MMC_MoveCircularAbsoluteExCmd(IN MMC_CONNECT_HNDL hConn,
											IN MMC_AXIS_REF_HNDL hAxisRef,
											IN MMC_MOVECIRCULARABSOLUTEEX_IN* pInParam,
											OUT MMC_MOVECIRCULARABSOLUTEEX_OUT* pOutParam);
////////////////////////////////////////////////////////////////////////////////
/// \fn int MMC_MoveCircularAbsoluteCenterCmd(
///				IN MMC_CONNECT_HNDL hConn,
///				IN MMC_AXIS_REF_HNDL hAxisRef,
///				IN MMC_MOVECIRCULARABSOLUTECENTER_IN* pInParam,
///				OUT MMC_MOVECIRCULARABSOLUTE_OUT* pOutParam)
/// \brief This function This function  send Move Circular Absolute Center command to MMC server for specific Group.
/// \param  hConn - [IN] Connection handle
/// \param  hAxisRef - [IN] Axis Reference handle
/// \param  pInParam - [IN] Pointer to Move Circular Absolute Center input parameters
/// \param  pOutParam - [OUT] Pointer to Move Circular Absolute output parameters
/// \return	return - 0 if success
/// 				 error_id in case of error
////////////////////////////////////////////////////////////////////////////////
MMC_LIB_API int MMC_MoveCircularAbsoluteCenterCmd(
		IN MMC_CONNECT_HNDL hConn,
		IN MMC_AXIS_REF_HNDL hAxisRef,
		IN MMC_MOVECIRCULARABSOLUTECENTER_IN* pInParam,
		OUT MMC_MOVECIRCULARABSOLUTE_OUT* pOutParam);
////////////////////////////////////////////////////////////////////////////////
/// \fn int MMC_MoveCircularAbsoluteCenterCmd(IN MMC_CONNECT_HNDL hConn,
///											  IN MMC_AXIS_REF_HNDL hAxisRef,
///											  IN MMC_MOVECIRCULARABSOLUTECENTEREX_IN* pInParam,
///											  OUT MMC_MOVECIRCULARABSOLUTEEX_OUT* pOutParam)
/// \brief This function This function  is similar to MMC_MoveCircularAbsoluteCenterCmd, except the fact that all float
///		   input parameters were converted to double
/// \param  hConn - [IN] Connection handle
/// \param  hAxisRef - [IN] Axis Reference handle
/// \param  pInParam - [IN] Pointer to Move Circular Absolute Center Extended input parameters
/// \param  pOutParam - [OUT] Pointer to Move Circular Absolute Extended output parameters
/// \return	return - 0 if success
/// 				 error_id in case of error
////////////////////////////////////////////////////////////////////////////////
MMC_LIB_API int MMC_MoveCircularAbsoluteCenterExCmd(IN MMC_CONNECT_HNDL hConn,
													IN MMC_AXIS_REF_HNDL hAxisRef,
													IN MMC_MOVECIRCULARABSOLUTECENTEREX_IN* pInParam,
													OUT MMC_MOVECIRCULARABSOLUTEEX_OUT* pOutParam);

////////////////////////////////////////////////////////////////////////////////
/// \fn int MMC_MoveCircularAbsoluteBorderCmd(
///				IN MMC_CONNECT_HNDL hConn,
///				IN MMC_AXIS_REF_HNDL hAxisRef,
///				IN MMC_MOVECIRCULARABSOLUTEBORDER_IN* pInParam,
///				OUT MMC_MOVECIRCULARABSOLUTE_OUT* pOutParam)
/// \brief This function This function  send Move Circular Absolute Border command to MMC server for specific Group.
/// \param  hConn - [IN] Connection handle
/// \param  hAxisRef - [IN] Axis Reference handle
/// \param  pInParam - [IN] Pointer to Move Circular Absolute Border input parameters
/// \param  pOutParam - [OUT] Pointer to Move Circular Absolute output parameters
/// \return	return - 0 if success
/// 				 error_id in case of error
////////////////////////////////////////////////////////////////////////////////
MMC_LIB_API int MMC_MoveCircularAbsoluteBorderCmd(
		IN MMC_CONNECT_HNDL hConn,
		IN MMC_AXIS_REF_HNDL hAxisRef,
		IN MMC_MOVECIRCULARABSOLUTEBORDER_IN* pInParam,
		OUT MMC_MOVECIRCULARABSOLUTE_OUT* pOutParam);

////////////////////////////////////////////////////////////////////////////////
/// \fn int MMC_MoveCircularAbsoluteBorderExCmd(IN MMC_CONNECT_HNDL hConn,
///												IN MMC_AXIS_REF_HNDL hAxisRef,
///												IN MMC_MOVECIRCULARABSOLUTEBORDEREX_IN* pInParam,
///												OUT MMC_MOVECIRCULARABSOLUTEEX_OUT* pOutParam)
/// \brief This function This function  is similar to MMC_MoveCircularAbsoluteBorderCmd, except the fact that all float
///		   input parameters were converted to double
/// \param  hConn - [IN] Connection handle
/// \param  hAxisRef - [IN] Axis Reference handle
/// \param  pInParam - [IN] Pointer to Move Circular Absolute Border Extended input parameters
/// \param  pOutParam - [OUT] Pointer to Move Circular Absolute Extended output parameters
/// \return	return - 0 if success
/// 				 error_id in case of error
////////////////////////////////////////////////////////////////////////////////
MMC_LIB_API int MMC_MoveCircularAbsoluteBorderExCmd(IN MMC_CONNECT_HNDL hConn,
													IN MMC_AXIS_REF_HNDL hAxisRef,
													IN MMC_MOVECIRCULARABSOLUTEBORDEREX_IN* pInParam,
													OUT MMC_MOVECIRCULARABSOLUTEEX_OUT* pOutParam);

////////////////////////////////////////////////////////////////////////////////
/// \fn int MMC_MoveCircularAbsoluteRadiusCmd(
///				IN MMC_CONNECT_HNDL hConn,
///				IN MMC_AXIS_REF_HNDL hAxisRef,
///				IN MMC_MOVECIRCULARABSOLUTERADIUS_IN* pInParam,
///				OUT MMC_MOVECIRCULARABSOLUTE_OUT* pOutParam)
/// \brief This function This function  is similar to MMC_MoveCircularAbsoluteBorderCmd, except the fact that all float
///		   input parameters were converted to double
/// \param  hConn - [IN] Connection handle
/// \param  hAxisRef - [IN] Axis Reference handle
/// \param  pInParam - [IN] Pointer to Move Circular Absolute Radius input parameters
/// \param  pOutParam - [OUT] Pointer to Move Circular Absolute output parameters
/// \return	return - 0 if success
/// 				 error_id in case of error
////////////////////////////////////////////////////////////////////////////////
MMC_LIB_API int MMC_MoveCircularAbsoluteRadiusCmd(
		IN MMC_CONNECT_HNDL hConn,
		IN MMC_AXIS_REF_HNDL hAxisRef,
		IN MMC_MOVECIRCULARABSOLUTERADIUS_IN* pInParam,
		OUT MMC_MOVECIRCULARABSOLUTE_OUT* pOutParam);

////////////////////////////////////////////////////////////////////////////////
/// \fn int MMC_MoveCircularAbsoluteRadiusExCmd(IN MMC_CONNECT_HNDL hConn,
///												IN MMC_AXIS_REF_HNDL hAxisRef,
///												IN MMC_MOVECIRCULARABSOLUTERADIUSEX_IN* pInParam,
///												OUT MMC_MOVECIRCULARABSOLUTE_OUT* pOutParam)
/// \brief This function This function  is similar to MMC_MoveCircularAbsoluteRadiusCmd, except the fact that all float
///		   input parameters were converted to double
/// \param  hConn - [IN] Connection handle
/// \param  hAxisRef - [IN] Axis Reference handle
/// \param  pInParam - [IN] Pointer to Move Circular Absolute Radius Extended input parameters
/// \param  pOutParam - [OUT] Pointer to Move Circular Absolute Extended output parameters
/// \return	return - 0 if success
/// 				 error_id in case of error
////////////////////////////////////////////////////////////////////////////////
MMC_LIB_API int MMC_MoveCircularAbsoluteRadiusExCmd(IN MMC_CONNECT_HNDL hConn,
													IN MMC_AXIS_REF_HNDL hAxisRef,
													IN MMC_MOVECIRCULARABSOLUTERADIUSEX_IN* pInParam,
													OUT MMC_MOVECIRCULARABSOLUTEEX_OUT* pOutParam);

////////////////////////////////////////////////////////////////////////////////
/// \fn int MMC_MoveCircularAbsoluteAngleCmd(IN MMC_CONNECT_HNDL hConn,
///											 IN MMC_AXIS_REF_HNDL hAxisRef,
///											 IN MMC_MOVECIRCULARABSOLUTEANGLE_IN* pInParam,
///											 OUT MMC_MOVECIRCULARABSOLUTE_OUT* pOutParam)
/// \brief This function This function  send Move Circular Absolute Angle command to MMC server for specific Group.
/// \param  hConn - [IN] Connection handle
/// \param  hAxisRef - [IN] Axis Reference handle
/// \param  pInParam - [IN] Pointer to Move Circular Absolute Angle input parameters
/// \param  pOutParam - [OUT] Pointer to Move Circular Absolute output parameters
/// \return	return - 0 if success
/// 				 error_id in case of error
////////////////////////////////////////////////////////////////////////////////
MMC_LIB_API int MMC_MoveCircularAbsoluteAngleCmd(IN MMC_CONNECT_HNDL hConn,
												   IN MMC_AXIS_REF_HNDL hAxisRef,
												   IN MMC_MOVECIRCULARABSOLUTEANGLE_IN* pInParam,
												   OUT MMC_MOVECIRCULARABSOLUTE_OUT* pOutParam);

////////////////////////////////////////////////////////////////////////////////
/// \fn int MMC_MoveCircularAbsoluteAngleExCmd(IN MMC_CONNECT_HNDL hConn,
///											   IN MMC_AXIS_REF_HNDL hAxisRef,
///											   IN MMC_MOVECIRCULARABSOLUTEANGLE_IN* pInParam,
///											   OUT MMC_MOVECIRCULARABSOLUTE_OUT* pOutParam)
/// \brief This function This function  is similar to MMC_MoveCircularAbsoluteAngleCmd, except the fact that all float
///		   input parameters were converted to double
/// \param  hConn - [IN] Connection handle
/// \param  hAxisRef - [IN] Axis Reference handle
/// \param  pInParam - [IN] Pointer to Move Circular Absolute Angle Extended input parameters
/// \param  pOutParam - [OUT] Pointer to Move Circular Absolute Extended output parameters
/// \return	return - 0 if success
/// 				 error_id in case of error
////////////////////////////////////////////////////////////////////////////////
MMC_LIB_API int MMC_MoveCircularAbsoluteAngleExCmd(IN MMC_CONNECT_HNDL hConn,
												   IN MMC_AXIS_REF_HNDL hAxisRef,
												   IN MMC_MOVECIRCULARABSOLUTEANGLEEX_IN* pInParam,
												   OUT MMC_MOVECIRCULARABSOLUTEEX_OUT* pOutParam);

////////////////////////////////////////////////////////////////////////////////
/// \fn int MMC_GroupSetOverrideCmd(
///				IN MMC_CONNECT_HNDL hConn,
///				IN MMC_AXIS_REF_HNDL hAxisRef,
///				IN MMC_SETOVERRIDE_IN* pInParam,
///				OUT MMC_SETOVERRIDE_OUT* pOutParam)
/// \brief This function  send Group Set Override command to MMC server for specific Group.
/// \param  hConn - [IN] Connection handle
/// \param  hAxisRef - [IN] Group Reference handle
/// \param  pInParam - [IN] Pointer to Set Override input parameters
/// \param  pOutParam - [OUT] Pointer to Set Override output parameters
/// \return	return - 0 if success
/// 				 error_id in case of error
////////////////////////////////////////////////////////////////////////////////
MMC_LIB_API int MMC_GroupSetOverrideCmd(
		IN MMC_CONNECT_HNDL hConn,
		IN MMC_AXIS_REF_HNDL hAxisRef,
		IN MMC_SETOVERRIDE_IN* pInParam,
		OUT MMC_SETOVERRIDE_OUT* pOutParam);

////////////////////////////////////////////////////////////////////////////////
/// \fn int MMC_MoveLinearAbsoluteCmd(
///				IN MMC_CONNECT_HNDL hConn,
///				IN MMC_AXIS_REF_HNDL hAxisRef,
///				IN MMC_MOVELINEARABSOLUTE_IN* pInParam,
///				OUT MMC_MOVELINEARABSOLUTE_OUT* pOutParam)
/// \brief This function  send Move Linear Absolute command to MMC server for specific Group.
/// \param  hConn - [IN] Connection handle
/// \param  hAxisRef - [IN] Axis Reference handle
/// \param  pInParam - [IN] Pointer to Move Linear Absolute input parameters
/// \param  pOutParam - [OUT] Pointer to Move Linear Absolute output parameters
/// \return	return - 0 if success
/// 				 error_id in case of error
////////////////////////////////////////////////////////////////////////////////
MMC_LIB_API int MMC_MoveLinearAbsoluteCmd(
		IN MMC_CONNECT_HNDL hConn,
		IN MMC_AXIS_REF_HNDL hAxisRef,
		IN MMC_MOVELINEARABSOLUTE_IN* pInParam,
		OUT MMC_MOVELINEARABSOLUTE_OUT* pOutParam);

/// \fn int MMC_MoveLinearAbsoluteExCmd(IN MMC_CONNECT_HNDL hConn,
///										IN MMC_AXIS_REF_HNDL hAxisRef,
///										IN MMC_MOVELINEARABSOLUTEEX_IN* pInParam,
///										OUT MMC_MOVELINEARABSOLUTEEX_OUT* pOutParam)
/// \brief This function  is similar to MMC_MoveLinearAbsoluteCmd, except the fact that all float input parameters
///		   were converted to double
/// \param  hConn - [IN] Connection handle
/// \param  hAxisRef - [IN] Axis Reference handle
/// \param  pInParam - [IN] Pointer to Move Linear Absolute Extended input parameters
/// \param  pOutParam - [OUT] Pointer to Move Linear Absolute Extended output parameters
/// \return	return - 0 if success
/// 				 error_id in case of error
////////////////////////////////////////////////////////////////////////////////
MMC_LIB_API int MMC_MoveLinearAbsoluteExCmd(IN MMC_CONNECT_HNDL hConn,
											IN MMC_AXIS_REF_HNDL hAxisRef,
											IN MMC_MOVELINEARABSOLUTEEX_IN* pInParam,
											OUT MMC_MOVELINEARABSOLUTEEX_OUT* pOutParam);

////////////////////////////////////////////////////////////////////////////////
/// \fn int MMC_MoveLinearRelativeCmd(
///				IN MMC_CONNECT_HNDL hConn,
///				IN MMC_AXIS_REF_HNDL hAxisRef,
///				IN MMC_MOVELINEARRELATIVE_IN* pInParam,
///				OUT MMC_MOVELINEARRELATIVE_OUT* pOutParam)
/// \brief This function  send Move Linear Relative command to MMC server for specific Group.
/// \param  hConn - [IN] Connection handle
/// \param  hAxisRef - [IN] Axis Reference handle
/// \param  pInParam - [IN] Pointer to Move Linear Relative input parameters
/// \param  pOutParam - [OUT] Pointer to Move Linear Relative output parameters
/// \return	return - 0 if success
/// 				 error_id in case of error
////////////////////////////////////////////////////////////////////////////////
MMC_LIB_API int MMC_MoveLinearRelativeCmd(
		IN MMC_CONNECT_HNDL hConn,
		IN MMC_AXIS_REF_HNDL hAxisRef,
		IN MMC_MOVELINEARRELATIVE_IN* pInParam,
		OUT MMC_MOVELINEARRELATIVE_OUT* pOutParam);

////////////////////////////////////////////////////////////////////////////////
/// \fn int MMC_MoveLinearRelativeExCmd(IN MMC_CONNECT_HNDL hConn,
///										IN MMC_AXIS_REF_HNDL hAxisRef,
///										IN MMC_MOVELINEARRELATIVEEX_IN* pInParam,
///										OUT MMC_MOVELINEARRELATIVEEX_OUT* pOutParam)
/// \brief This function  is similar to MMC_MoveLinearRelativeCmd, except the fact that all float input parameters
///		   were converted to double
/// \param  hConn - [IN] Connection handle
/// \param  hAxisRef - [IN] Axis Reference handle
/// \param  pInParam - [IN] Pointer to Move Linear Relative Extended input parameters
/// \param  pOutParam - [OUT] Pointer to Move Linear Relative Extended output parameters
/// \return	return - 0 if success
/// 				 error_id in case of error
////////////////////////////////////////////////////////////////////////////////
MMC_LIB_API int MMC_MoveLinearRelativeExCmd(IN MMC_CONNECT_HNDL hConn,
											IN MMC_AXIS_REF_HNDL hAxisRef,
											IN MMC_MOVELINEARRELATIVEEX_IN* pInParam,
											OUT MMC_MOVELINEARRELATIVEEX_OUT* pOutParam);

////////////////////////////////////////////////////////////////////////////////
/// \fn int MMC_MovePolynomAbsoluteCmd(
///				IN MMC_CONNECT_HNDL hConn,
///				IN MMC_AXIS_REF_HNDL hAxisRef,
///				IN MMC_MOVEPOLYNOMABSOLUTE_IN* pInParam,
///				OUT MMC_MOVEPOLYNOMABSOLUTE_OUT* pOutParam)
/// \brief This function  send Move Polynom Absolute command to MMC server for specific Group.
/// \param  hConn - [IN] Connection handle
/// \param  hAxisRef - [IN] Axis Reference handle
/// \param  pInParam - [IN] Pointer to Move Polynom Absolute input parameters
/// \param  pOutParam - [OUT] Pointer to Move Polynom Absolute output parameters
/// \return	return - 0 if success
/// 				 error_id in case of error
////////////////////////////////////////////////////////////////////////////////
MMC_LIB_API int MMC_MovePolynomAbsoluteCmd(
		IN MMC_CONNECT_HNDL hConn,
		IN MMC_AXIS_REF_HNDL hAxisRef,
		IN MMC_MOVEPOLYNOMABSOLUTE_IN* pInParam,
		OUT MMC_MOVEPOLYNOMABSOLUTE_OUT* pOutParam);


////////////////////////////////////////////////////////////////////////////////
/// \fn int MMC_GroupSetPositionCmd(
///				IN MMC_CONNECT_HNDL hConn,
///				IN MMC_AXIS_REF_HNDL hAxisRef,
///				IN MMC_GROUPSETPOSITION_IN* pInParam,
///				OUT MMC_GROUPSETPOSITION_OUT* pOutParam)
/// \brief This function  send Set Position command to MMC server for specific Group.
/// \param  hConn - [IN] Connection handle
/// \param  hAxisRef - [IN] Axis Reference handle
/// \param  pInParam - [IN] Pointer to Set Position input parameters
/// \param  pOutParam - [OUT] Pointer to Set POsition output parameters
/// \return	return - 0 if success
/// 				 error_id in case of error
////////////////////////////////////////////////////////////////////////////////
MMC_LIB_API int MMC_GroupSetPositionCmd(
		IN MMC_CONNECT_HNDL hConn,
		IN MMC_AXIS_REF_HNDL hAxisRef,
		IN MMC_GROUPSETPOSITION_IN* pInParam,
		OUT MMC_GROUPSETPOSITION_OUT* pOutParam);

////////////////////////////////////////////////////////////////////////////////
/// \fn int MMC_GroupReadStatusCmd(
///				IN MMC_CONNECT_HNDL hConn,
///				IN MMC_AXIS_REF_HNDL hAxisRef,
///				IN MMC_GROUPREADSTATUS_IN* pInParam,
///				OUT MMC_GROUPREADSTATUS_OUT* pOutParam)
/// \brief This function  send Read Group Status command to MMC server for specific Group.
/// \param  hConn - [IN] Connection handle
/// \param  hAxisRef - [IN] Axis Reference handle
/// \param  pInParam - [IN] Pointer to Axis Status input parameters structure
/// \param  pOutParam - [OUT] Axis Status output parameters structure
/// \return	return - 0 if success
/// 				 error_id in case of error
////////////////////////////////////////////////////////////////////////////////
MMC_LIB_API int MMC_GroupReadStatusCmd(
		IN MMC_CONNECT_HNDL hConn,
		IN MMC_AXIS_REF_HNDL hAxisRef,
		IN MMC_GROUPREADSTATUS_IN* pInParam,
		OUT MMC_GROUPREADSTATUS_OUT* pOutParam);

////////////////////////////////////////////////////////////////////////////////
/// \fn int MMC_GroupEnableCmd(
///				IN MMC_CONNECT_HNDL hConn,
///				IN MMC_AXIS_REF_HNDL hAxisRef,
///				IN MMC_GROUPENABLE_IN* pInParam,
///				OUT MMC_GROUPENABLE_OUT* pOutParam)
/// \brief This function  send Group Enable command to MMC server for specific Group.
/// \param  hConn - [IN] Connection handle
/// \param  hAxisRef - [IN] Axis Reference handle
/// \param  pInParam - [IN] Pointer to....
/// \param  pOutParam - [OUT] Axis ..
/// \return	return - 0 if success
/// 				 error_id in case of error
////////////////////////////////////////////////////////////////////////////////
MMC_LIB_API int MMC_GroupEnableCmd(
		IN MMC_CONNECT_HNDL hConn,
		IN MMC_AXIS_REF_HNDL hAxisRef,
		IN MMC_GROUPENABLE_IN* pInParam,
		OUT MMC_GROUPENABLE_OUT* pOutParam);

////////////////////////////////////////////////////////////////////////////////
/// \fn int MMC_GroupDisableCmd(
///				IN MMC_CONNECT_HNDL hConn,
///				IN MMC_AXIS_REF_HNDL hAxisRef,
///				IN MMC_GROUPDISABLE_IN* pInParam,
///				OUT MMC_GROUPDISABLE_OUT* pOutParam)
/// \brief This function This function  send Group Disable command to MMC server for specific Group.
/// \param  hConn - [IN] Connection handle
/// \param  hAxisRef - [IN] Axis Reference handle
/// \param  pInParam - [IN] Pointer to....
/// \param  pOutParam - [OUT] Axis ..
/// \return	return - 0 if success
/// 				 error_id in case of error
////////////////////////////////////////////////////////////////////////////////
MMC_LIB_API int MMC_GroupDisableCmd(
		IN MMC_CONNECT_HNDL hConn,
		IN MMC_AXIS_REF_HNDL hAxisRef,
		IN MMC_GROUPDISABLE_IN* pInParam,
		OUT MMC_GROUPDISABLE_OUT* pOutParam);

////////////////////////////////////////////////////////////////////////////////
/// \fn int MMC_GroupResetCmd(
///				IN MMC_CONNECT_HNDL hConn,
///				IN MMC_AXIS_REF_HNDL hAxisRef,
///				IN MMC_GROUPRESET_IN* pInParam,
///				OUT MMC_GROUPRESET_OUT* pOutParam)
/// \brief This function  send Group Reset command to MMC server for specific Group.
/// \param  hConn - [IN] Connection handle
/// \param  hAxisRef - [IN] Axis Reference handle
/// \param  pInParam - [IN] Pointer to....
/// \param  pOutParam - [OUT] Pointer to....
/// \return	return - 0 if success
/// 				 error_id in case of error
////////////////////////////////////////////////////////////////////////////////
MMC_LIB_API int MMC_GroupResetCmd(
		IN MMC_CONNECT_HNDL hConn,
		IN MMC_AXIS_REF_HNDL hAxisRef,
		IN MMC_GROUPRESET_IN* pInParam,
		OUT MMC_GROUPRESET_OUT* pOutParam);

////////////////////////////////////////////////////////////////////////////////
/// \fn int MMC_GroupReadActualVelocity(
///				IN MMC_CONNECT_HNDL hConn,
///				IN MMC_AXIS_REF_HNDL hAxisRef,
///				IN MMC_GROUPREADACTUALVELOCITY_IN* pInParam,
///				OUT MMC_GROUPREADACTUALVELOCITY_OUT* pOutParam)
/// \brief This function read group actual velocity.
/// \param  hConn - [IN] Connection handle
/// \param  hAxisRef - [IN] Axis Reference handle
/// \param  pInParam - [IN] Pointer to Group Read Actual Velocity input parameters
/// \param  pOutParam - [OUT] Pointer to Group Read Actual Velocity output parameters
/// \return	return - 0 if success
/// 				 error_id in case of error
////////////////////////////////////////////////////////////////////////////////
MMC_LIB_API int MMC_GroupReadActualVelocity(
		IN MMC_CONNECT_HNDL hConn,
		IN MMC_AXIS_REF_HNDL hAxisRef,
		IN MMC_GROUPREADACTUALVELOCITY_IN* pInParam,
		OUT MMC_GROUPREADACTUALVELOCITY_OUT* pOutParam);

////////////////////////////////////////////////////////////////////////////////
/// \fn int MMC_GroupReadError(
///				IN MMC_CONNECT_HNDL hConn,
///				IN MMC_AXIS_REF_HNDL hAxisRef,
///				IN MMC_GROUPREADERROR_IN* pInParam,
///				OUT MMC_GROUPREADERROR_OUT* pOutParam)
/// \brief This function read group error.
/// \param  hConn - [IN] Connection handle
/// \param  hAxisRef - [IN] Axis Reference handle
/// \param  pInParam - [IN] Pointer to Group Read Error input parameters
/// \param  pOutParam - [OUT] Pointer to Group Read Error output parameters
/// \return	return - 0 if success
/// 				 error_id in case of error
////////////////////////////////////////////////////////////////////////////////
MMC_LIB_API int MMC_GroupReadError(
		IN MMC_CONNECT_HNDL hConn,
		IN MMC_AXIS_REF_HNDL hAxisRef,
		IN MMC_GROUPREADERROR_IN* pInParam,
		OUT MMC_GROUPREADERROR_OUT* pOutParam);

////////////////////////////////////////////////////////////////////////////////
/// \fn int MMC_AddAxisToGroup(
///				IN MMC_CONNECT_HNDL hConn,
///				IN MMC_AXIS_REF_HNDL hAxisRef,
///				IN MMC_ADDAXISTOGROUP_IN* pInParam,
///				OUT MMC_ADDAXISTOGROUP_OUT* pOutParam)
/// \brief This function add axis to axis group.
/// \param  hConn - [IN] Connection handle
/// \param  hAxisRef - [IN] Axis Reference handle
/// \param  pInParam - [IN] Pointer to Add Axis To Group input parameters
/// \param  pOutParam - [OUT] Pointer to Add Axis To Group output parameters
/// \return	return - 0 if success
/// 				 error_id in case of error
////////////////////////////////////////////////////////////////////////////////
MMC_LIB_API int MMC_AddAxisToGroup(
		IN MMC_CONNECT_HNDL hConn,
		IN MMC_AXIS_REF_HNDL hAxisRef,
		IN MMC_ADDAXISTOGROUP_IN* pInParam,
		OUT MMC_ADDAXISTOGROUP_OUT* pOutParam);

////////////////////////////////////////////////////////////////////////////////
/// \fn int MMC_GroupReadActualPosition(
///				IN MMC_CONNECT_HNDL hConn,
///				IN MMC_AXIS_REF_HNDL hAxisRef,
///				IN MMC_GROUPREADACTUALPOSITION_IN* pInParam,
///				OUT MMC_GROUPREADACTUALPOSITION_OUT* pOutParam)
/// \brief This function read group actual position.
/// \param  hConn - [IN] Connection handle
/// \param  hAxisRef - [IN] Axis Reference handle
/// \param  pInParam - [IN] Pointer to Group Read Actual Position input parameters
/// \param  pOutParam - [OUT] Pointer to Group Read Actual Position output parameters
/// \return	return - 0 if success
/// 				 error_id in case of error
////////////////////////////////////////////////////////////////////////////////
MMC_LIB_API int MMC_GroupReadActualPosition(
		IN MMC_CONNECT_HNDL hConn,
		IN MMC_AXIS_REF_HNDL hAxisRef,
		IN MMC_GROUPREADACTUALPOSITION_IN* pInParam,
		OUT MMC_GROUPREADACTUALPOSITION_OUT* pOutParam);

////////////////////////////////////////////////////////////////////////////////
/// \fn int MMC_GroupStopCmd(
///				IN MMC_CONNECT_HNDL hConn,
///				IN MMC_AXIS_REF_HNDL hAxisRef,
///				IN MMC_GROUPSTOP_IN* pInParam,
///				OUT MMC_GROUPSTOP_OUT* pOutParam)
/// \brief This function ....
/// \param hConn - [IN] Connection handle
/// \param hAxisRef - [IN] Axis Reference handle
/// \param pInParam - [IN] Pointer to Group Stop input parameters
/// \param pOutParam - [OUT] Pointer to Group Stop output parameters
/// \return	return - 0 if success
/// 				 error_id in case of error
////////////////////////////////////////////////////////////////////////////////
MMC_LIB_API int MMC_GroupStopCmd(
		IN MMC_CONNECT_HNDL hConn,
		IN MMC_AXIS_REF_HNDL hAxisRef,
		IN MMC_GROUPSTOP_IN* pInParam,
		OUT MMC_GROUPSTOP_OUT* pOutParam);

////////////////////////////////////////////////////////////////////////////////
/// \fn int MMC_GroupHaltCmd(
///				IN MMC_CONNECT_HNDL hConn,
///				IN MMC_AXIS_REF_HNDL hAxisRef,
///				IN MMC_GROUPHALT_IN* pInParam,
///				OUT MMC_GROUPHALT_OUT* pOutParam)
/// \brief This function ....
/// \param hConn - [IN] Connection handle
/// \param hAxisRef - [IN] Axis Reference handle
/// \param pInParam - [IN] Pointer to Group Halt input parameters
/// \param pOutParam - [OUT] Pointer to Group Halt output parameters
/// \return	return - 0 if success
/// 				 error_id in case of error
////////////////////////////////////////////////////////////////////////////////
MMC_LIB_API int MMC_GroupHaltCmd(
		IN MMC_CONNECT_HNDL hConn,
		IN MMC_AXIS_REF_HNDL hAxisRef,
		IN MMC_GROUPHALT_IN* pInParam,
		OUT MMC_GROUPHALT_OUT* pOutParam);


/* Alex: Integration of MoveRepetitive functions */
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn int MMC_MoveLinearAbsoluteRepetitiveCmd(IN MMC_CONNECT_HNDL hConn,
///												IN MMC_AXIS_REF_HNDL hAxisRef,
///												IN MMC_MOVELINEARABSOLUTEREPETITIVE_IN* pInParam,
///												OUT MMC_MOVELINEARABSOLUTEREPETITIVE_OUT* pOutParam)
/// \brief This function moves the vector back and forth from the current position to absolute target position
/// \param  hConn - [IN] Connection handle
/// \param  hAxisRef - [IN] Axis Reference handle
/// \param  pInParam - [IN] Pointer to Move Linear Absolute Repetitive input parameters
/// \param  pOutParam - [OUT] Pointer to Move Linear Absolute Repetitive output parameters
/// \return	return - 0 if success
/// 				 error_id in case of error
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
MMC_LIB_API int MMC_MoveLinearAbsoluteRepetitiveCmd(
		IN MMC_CONNECT_HNDL hConn,
		IN MMC_AXIS_REF_HNDL hAxisRef,
		IN MMC_MOVELINEARABSOLUTEREPETITIVE_IN* pInParam,
		OUT MMC_MOVELINEARABSOLUTEREPETITIVE_OUT* pOutParam);


////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn int MMC_MoveLinearAbsoluteRepetitiveExCmd(IN MMC_CONNECT_HNDL hConn,
///												  IN MMC_AXIS_REF_HNDL hAxisRef,
///												  IN MMC_MOVELINEARABSOLUTEREPETITIVEEX_IN* pInParam,
///												  OUT MMC_MOVELINEARABSOLUTEREPETITIVEEX_OUT* pOutParam)
/// \brief This function moves the vector back and forth from the current position to absolute target position
/// \param  hConn - [IN] Connection handle
/// \param  hAxisRef - [IN] Axis Reference handle
/// \param  pInParam - [IN] Pointer to Move Linear Absolute Repetitive Ex input parameters
/// \param  pOutParam - [OUT] Pointer to Move Linear Absolute Repetitive Ex output parameters
/// \return	return - 0 if success
/// 				 error_id in case of error
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
MMC_LIB_API int MMC_MoveLinearAbsoluteRepetitiveExCmd(
		IN MMC_CONNECT_HNDL hConn,
		IN MMC_AXIS_REF_HNDL hAxisRef,
		IN MMC_MOVELINEARABSOLUTEREPETITIVEEX_IN* pInParam,
		OUT MMC_MOVELINEARABSOLUTEREPETITIVEEX_OUT* pOutParam);

/////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn int MMC_MoveLinearRelativeRepetitiveCmd(IN MMC_CONNECT_HNDL hConn,
///												IN MMC_AXIS_REF_HNDL hAxisRef,
///												IN MMC_MOVELINEARRELATIVEREPETITIVE_IN* pInParam,
///												OUT MMC_MOVELINEARRELATIVEREPETITIVE_OUT* pOutParam)
/// \brief This function moves the vector back and forth from the current position to a given distance
/// \param  hConn - [IN] Connection handle
/// \param  hAxisRef - [IN] Axis Reference handle
/// \param  pInParam - [IN] Pointer to Move Linear Relative Repetitive input parameters
/// \param  pOutParam - [OUT] Pointer to Move Linear Relative Repetitive output parameters
/// \return	return - 0 if success
/// 				 error_id in case of error
//////////////////////////////////////////////////////////////////////////////////////////////////////////
MMC_LIB_API int MMC_MoveLinearRelativeRepetitiveCmd(IN MMC_CONNECT_HNDL hConn,
													IN MMC_AXIS_REF_HNDL hAxisRef,
													IN MMC_MOVELINEARRELATIVEREPETITIVE_IN* pInParam,
													OUT MMC_MOVELINEARRELATIVEREPETITIVE_OUT* pOutParam);

/////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn int MMC_MoveLinearRelativeRepetitiveExCmd(IN MMC_CONNECT_HNDL hConn,
///												  IN MMC_AXIS_REF_HNDL hAxisRef,
///												  IN MMC_MOVELINEARRELATIVEREPETITIVEEX_IN* pInParam,
///												  OUT MMC_MOVELINEARRELATIVEREPETITIVEEX_OUT* pOutParam)
/// \brief This function moves the vector back and forth from the current position to a given distance
/// \param  hConn - [IN] Connection handle
/// \param  hAxisRef - [IN] Axis Reference handle
/// \param  pInParam - [IN] Pointer to Move Linear Relative Repetitive Ex input parameters
/// \param  pOutParam - [OUT] Pointer to Move Linear Relative Repetitive Ex output parameters
/// \return	return - 0 if success
/// 				 error_id in case of error
//////////////////////////////////////////////////////////////////////////////////////////////////////////
MMC_LIB_API int MMC_MoveLinearRelativeRepetitiveExCmd(IN MMC_CONNECT_HNDL hConn,
													  IN MMC_AXIS_REF_HNDL hAxisRef,
													  IN MMC_MOVELINEARRELATIVEREPETITIVEEX_IN* pInParam,
													  OUT MMC_MOVELINEARRELATIVEREPETITIVEEX_OUT* pOutParam);

/* Alex 13/03/2011: Splines user interface */
////////////////////////////////////////////////////////////////////////////////////////
/// \fn int MMC_PathSelectCmd(IN MMC_CONNECT_HNDL hConn,
///							  IN MMC_AXIS_REF_HNDL hAxisRef,
///							  IN MMC_PATHSELECT_IN* pInParam,
///							  OUT MMC_PATHSELECT_OUT* pOutParam)
/// \brief This function reads splines data from file and calculates the optimal path
/// \param  hConn - [IN] Connection handle
/// \param  hAxisRef - [IN] Axis Reference handle
/// \param  pInParam - [IN] Pointer to Path Select input parameters
/// \param  pOutParam - [OUT] Pointer to Path Select output parameters
/// \return	return - 0 if success
/// 				 error_id in case of error
/////////////////////////////////////////////////////////////////////////////////////////
MMC_LIB_API int MMC_PathSelectCmd(IN MMC_CONNECT_HNDL hConn,
								  IN MMC_AXIS_REF_HNDL hAxisRef,
								  IN MMC_PATHSELECT_IN* pInParam,
								  OUT MMC_PATHSELECT_OUT* pOutParam);
								  
MMC_LIB_API int MMC_PathGetLengthsCmd(IN MMC_CONNECT_HNDL hConn,
								IN MMC_AXIS_REF_HNDL hAxisRef,
								IN MMC_PATHGETLENGTHS_IN* pInParam,
								OUT MMC_PATHGETLENGTHS_OUT* pOutParam);

////////////////////////////////////////////////////////////////////////////////////////
/// \fn int MMC_MovePathCmd(IN MMC_CONNECT_HNDL hConn,
///						 	IN MMC_AXIS_REF_HNDL hAxisRef,
///							IN MMC_PATHSELECT_IN* pInParam,
///							OUT MMC_PATHSELECT_OUT* pOutParam)
/// \brief This function moves the vector according to previously selected path
/// \param  hConn - [IN] Connection handle
/// \param  hAxisRef - [IN] Axis Reference handle
/// \param  pInParam - [IN] Pointer to Move Path input parameters
/// \param  pOutParam - [OUT] Pointer to Move Path output parameters
/// \return	return - 0 if success
/// 				 error_id in case of error
/////////////////////////////////////////////////////////////////////////////////////////
MMC_LIB_API int MMC_MovePathCmd(IN MMC_CONNECT_HNDL hConn,
								IN MMC_AXIS_REF_HNDL hAxisRef,
								IN MMC_MOVEPATH_IN* pInParam,
								OUT MMC_MOVEPATH_OUT* pOutParam);
/**
 * \fn	void mmc_pathgetlengths(void args)
 * \brief	this method retrieves a list of lengths for a range of spline segments.
 * \param  hConn - [IN] Connection handle
 * \param  hAxisRef - [IN] Axis Reference handle
 * \param  pInParam - [IN] Pointer to Move Path input parameters
 * \param  pOutParam - [OUT] Pointer to Move Path output parameters
 * \return 0 on successful completion, otherwise error.
 */								
MMC_LIB_API int MMC_PathGetLengthsCmd(IN MMC_CONNECT_HNDL hConn,
								IN MMC_AXIS_REF_HNDL hAxisRef,
								IN MMC_PATHGETLENGTHS_IN* pInParam,
								OUT MMC_PATHGETLENGTHS_OUT* pOutParam);

////////////////////////////////////////////////////////////////////////////////////////
/// \fn int MMC_PathUnselectCmd(IN MMC_CONNECT_HNDL hConn,
///						 		IN MMC_AXIS_REF_HNDL hAxisRef,
///								IN MMC_PATHSELECT_IN* pInParam,
///								OUT MMC_PATHSELECT_OUT* pOutParam)
/// \brief This function moves the vector according to previously selected path
/// \param  hConn - [IN] Connection handle
/// \param  hAxisRef - [IN] Axis Reference handle
/// \param  pInParam - [IN] Pointer to Move Path input parameters
/// \param  pOutParam - [OUT] Pointer to Move Path output parameters
/// \return	return - 0 if success
/// 				 error_id in case of error
/////////////////////////////////////////////////////////////////////////////////////////
MMC_LIB_API int MMC_PathUnselectCmd(IN MMC_CONNECT_HNDL hConn,
								    IN MMC_AXIS_REF_HNDL hAxisRef,
								    IN MMC_PATHUNSELECT_IN* pInParam,
								    OUT MMC_PATHUNSELECT_OUT* pOutParam);

/////////////////////////////////////////////////////////////////////////////////////////
MMC_LIB_API int MMC_MoveLinearAdditiveCmd(IN MMC_CONNECT_HNDL hConn,
								    	  IN MMC_AXIS_REF_HNDL hAxisRef,
								    	  IN MMC_MOVELINEARADDITIVE_IN* pInParam,
								    	  OUT MMC_MOVELINEARADDITIVE_OUT* pOutParam);


MMC_LIB_API int MMC_MoveLinearAdditiveExCmd(IN MMC_CONNECT_HNDL hConn,
								    	    IN MMC_AXIS_REF_HNDL hAxisRef,
								    	    IN MMC_MOVELINEARADDITIVEEX_IN* pInParam,
								    	    OUT MMC_MOVELINEARADDITIVEEX_OUT* pOutParam);
////////////////////////////////////////////////////////////////////////////////
/// \fn int  MMC_GetGroupMembersInfo(
///				IN MMC_CONNECT_HNDL hConn,
///				IN MMC_AXIS_REF_HNDL hAxisRef,
///				IN MMC_GETGROUPMEMBERSINFO_IN* pInParam,
///				OUT MMC_GETGROUPMEMBERSINFO_OUT* pOutParam)
/// \brief	This function receives group reference and return the
///			information regarding his members
/// \param  hConn - [IN] Connection handle
/// \param  hAxisRef - [IN] group reference
/// \param  pOutParam - [OUT] the output returns two strings, status and error id.
///								1. Number of axes in group (members)
///								2. Array of axes names.
///								3. Array of axes references.
/// \return	return - 0 if success
/// 				 error_id in case of error
////////////////////////////////////////////////////////////////////////////////
MMC_LIB_API int MMC_GetGroupMembersInfo(
		IN MMC_CONNECT_HNDL hConn,
		IN MMC_AXIS_REF_HNDL hAxisRef,
		IN MMC_GETGROUPMEMBERSINFO_IN* pInParam,
		OUT MMC_GETGROUPMEMBERSINFO_OUT* pOutParam);

/**
 * wrappers for kinematics's transformation API
 * eventually using MMC_SETKINTRANSFORMEX_IN
 */
typedef struct _mc_kintransform_delta {
	MC_KIN_REF_DELTA		stParams;
	MC_BUFFERED_MODE_ENUM eBufferMode;
	unsigned char ucExecute;
} MMC_KINTRANSFORM_DELTA_IN;
typedef MMC_SETKINTRANSFORMEX_OUT MMC_KINTRANSFORM_DELTA_OUT;
typedef struct _mc_kintransform_cartesian {
	MC_KIN_REF_CARTESIAN	stParams;
	MC_BUFFERED_MODE_ENUM eBufferMode;
	unsigned char ucExecute;
} MMC_KINTRANSFORM_CARTESIAN_IN;
typedef MMC_SETKINTRANSFORMEX_OUT MMC_KINTRANSFORM_CARTESIAN_OUT;
typedef struct _mc_kintransform_scara {
	MC_KIN_REF_SCARA		stParams;
	MC_BUFFERED_MODE_ENUM eBufferMode;
	unsigned char ucExecute;
} MMC_KINTRANSFORM_SCARA_IN;
typedef MMC_SETKINTRANSFORMEX_OUT MMC_KINTRANSFORM_SCARA_OUT;
typedef struct _mc_kintransform_threelink {
	MC_KIN_REF_THREE_LINK	stParams;
	MC_BUFFERED_MODE_ENUM eBufferMode;
	unsigned char ucExecute;
} MMC_KINTRANSFORM_THREELINK_IN;
typedef MMC_SETKINTRANSFORMEX_OUT MMC_KINTRANSFORM_THREELINK_OUT;


/*! \fn void SetKinTransformDelta(MMC_KINTRANSFORM_DELTA_IN& stInParam)
*	\brief sets parameters kinematic transformation (MSC to ACS) for DELTA robot.
*	\param stInParam reference of structure with kinematic parameters.
*	\return 0 if completed successfully, otherwise error or throws CMMCException.
*/
MMC_LIB_API int MMC_SetKinTransformDelta(
		IN MMC_CONNECT_HNDL hConn,
		IN MMC_AXIS_REF_HNDL hAxisRef,
		IN MMC_KINTRANSFORM_DELTA_IN* pInParam,
		OUT MMC_KINTRANSFORM_DELTA_OUT* pOutParam);
/*! \fn void SetKinTransformCartesian(MMC_KINTRANSFORM_CARTESIAN_IN& stInParam)
*	\brief sets parameters kinematic transformation (MSC to ACS) for Cartesian system.
*	\param stInParam reference of structure with kinematic parameters.
*	\return 0 if completed successfully, otherwise error or throws CMMCException.
*/
MMC_LIB_API int MMC_SetKinTransformCartesian(
		IN MMC_CONNECT_HNDL hConn,
		IN MMC_AXIS_REF_HNDL hAxisRef,
		IN MMC_KINTRANSFORM_CARTESIAN_IN* pInParam,
		OUT MMC_KINTRANSFORM_CARTESIAN_OUT* pOutParam);
/*! \fn void SetKinTransformScara(MMC_KINTRANSFORM_SCARA_IN& stInParam)
*	\brief sets parameters kinematic transformation (MSC to ACS) for SCARA robot.
*	\param stInParam reference of structure with kinematic parameters.
*	\return 0 if completed successfully, otherwise error or throws CMMCException.
*/
MMC_LIB_API int MMC_SetKinTransformScara(
		IN MMC_CONNECT_HNDL hConn,
		IN MMC_AXIS_REF_HNDL hAxisRef,
		IN MMC_KINTRANSFORM_SCARA_IN* pInParam,
		OUT MMC_KINTRANSFORM_SCARA_OUT* pOutParam);
/*! \fn void SetKinTransformThreeLink(MMC_KINTRANSFORM_THREELINK_IN& stInParam)
*	\brief sets parameters kinematic transformation (MSC to ACS) for THREELINK robot.
*	\param stInParam reference of structure with kinematic parameters.
*	\return 0 if completed successfully, otherwise error or throws CMMCException.
*/
MMC_LIB_API int MMC_SetKinTransformThreeLink(
		IN MMC_CONNECT_HNDL hConn,
		IN MMC_AXIS_REF_HNDL hAxisRef,
		IN MMC_KINTRANSFORM_THREELINK_IN* pInParam,
		OUT MMC_KINTRANSFORM_THREELINK_OUT* pOutParam);

//moving to g++ @YL 4-10-2010
#ifdef __cplusplus
}
#endif

#endif /* MMC_PLCOPEN_GROUP_API_H */
