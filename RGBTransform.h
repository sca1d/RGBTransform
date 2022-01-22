/*******************************************************************/
/*                                                                 */
/*                      ADOBE CONFIDENTIAL                         */
/*                   _ _ _ _ _ _ _ _ _ _ _ _ _                     */
/*                                                                 */
/* Copyright 2007 Adobe Systems Incorporated                       */
/* All Rights Reserved.                                            */
/*                                                                 */
/* NOTICE:  All information contained herein is, and remains the   */
/* property of Adobe Systems Incorporated and its suppliers, if    */
/* any.  The intellectual and technical concepts contained         */
/* herein are proprietary to Adobe Systems Incorporated and its    */
/* suppliers and may be covered by U.S. and Foreign Patents,       */
/* patents in process, and are protected by trade secret or        */
/* copyright law.  Dissemination of this information or            */
/* reproduction of this material is strictly forbidden unless      */
/* prior written permission is obtained from Adobe Systems         */
/* Incorporated.                                                   */
/*                                                                 */
/*******************************************************************/

/*
	Skeleton.h
*/

#pragma once

#ifndef SKELETON_H
#define SKELETON_H

typedef unsigned char		u_char;
typedef unsigned short		u_short;
typedef unsigned short		u_int16;
typedef unsigned long		u_long;
typedef short int			int16;
#define PF_TABLE_BITS	12
#define PF_TABLE_SZ_16	4096

#define PF_DEEP_COLOR_AWARE 1	// make sure we get 16bpc pixels; 
// AE_Effect.h checks for this.

#include "AEConfig.h"

#ifdef AE_OS_WIN
typedef unsigned short PixelType;
#include <Windows.h>
#endif

#define _USE_MATH_DEFINES
#include <math.h>

#include <vector>

#include "entry.h"
#include "AE_Effect.h"
#include "AE_EffectCB.h"
#include "AE_Macros.h"
#include "Param_Utils.h"
#include "AE_EffectCBSuites.h"
#include "String_Utils.h"
#include "AE_GeneralPlug.h"
#include "AEFX_ChannelDepthTpl.h"
#include "AEGP_SuiteHandler.h"
#include "AEFX_SuiteHelper.h"

#include "RGBTransform_Strings.h"

/* Versioning information */

#define	MAJOR_VERSION	1
#define	MINOR_VERSION	0
#define	BUG_VERSION		0
#define	STAGE_VERSION	PF_Stage_DEVELOP
#define	BUILD_VERSION	1


/* Parameter defaults */

#define	SKELETON_GAIN_MIN		0
#define	SKELETON_GAIN_MAX		100
#define	SKELETON_GAIN_DFLT		10

#include "libaeplscl/libaeplscl.h"

enum {
	SCALD_INPUT = 0,
	SCALD_BUTTON,
	SCALD_LAYER,
	SCALD_POPUP_SRC,
	SCALD_POPUP_LAYER,
	SCALD_TRANSFORM_TOPIC_START,
	SCALD_TRANSFORM_POINT,
	SCALD_TRANSFORM_SCALE_RATIO,
	SCALD_TRANSFORM_SCALEH,
	SCALD_TRANSFORM_SCALEW,
	SCALD_TRANSFORM_ROTATE,
	SCALD_TRANSFORM_ALPHA,
	SCALD_TRANSFORM_TOPIC_END,
	SCALD_NUM_PARAMS,
};

enum {
	SCALD_BUTTON_ID = 1,
	SCALD_LAYER_ID,
	SCALD_POPUP_SRC_ID,
	SCALD_POPUP_LAYER_ID,
	SCALD_TRANSFORM_TOPIC_START_ID,
	SCALD_TRANSFORM_POINT_ID,
	SCALD_TRANSFORM_SCALE_RATIO_ID,
	SCALD_TRANSFORM_SCALEH_ID,
	SCALD_TRANSFORM_SCALEW_ID,
	SCALD_TRANSFORM_ROTATE_ID,
	SCALD_TRANSFORM_ALPHA_ID,
	SCALD_TRANSFORM_TOPIC_END_ID,
};

enum {
	AllChannels = 1,
	Red,
	Green,
	Blue,
};

typedef struct GainInfo{
	PF_FpLong	gainF;
} GainInfo, *GainInfoP, **GainInfoH;

#define ERFLAG_RESET(erflag) erflag.Nulled=false;erflag.ValueError=false;erflag.CantAccess=false;erflag.Others=false;
#define ERFLAG_RESET_PTR(erflag) erflag->Nulled=false;erflag->ValueError=false;erflag->CantAccess=false;erflag->Others=false;
typedef struct {
	bool Nulled;
	bool ValueError;
	bool CantAccess;
	bool Others;
}ErLogs;

typedef struct {
	int* x;
	int* y;
}DotPoints, *DotPointsP;

typedef float doubler_scl;
typedef bool BitFlag;

extern "C" {

	DllExport
	PF_Err
	EffectMain(
		PF_Cmd			cmd,
		PF_InData		*in_data,
		PF_OutData		*out_data,
		PF_ParamDef		*params[],
		PF_LayerDef		*output,
		void			*extra);

}

#endif // SKELETON_H