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

#define WINDOWS_IGNORE_PACKING_MISMATCH

#include "RGBTransform.h"

typedef struct {
	A_u_long	index;
	A_char		str[256];
} TableString;



TableString		g_strs[StrID_NUMTYPES] = {
	StrID_NONE,							"",
	StrID_Name,							"Scald_RGBTransform",
	StrID_Description,					"あーるじーびーいじてもろて",
	SCALD_BUTTON_NAME,					"Scald",
	SCALD_LAYER_NAME,					"レイヤー",
	SCALD_POPUP_SRC_NAME,				"ソース色素",
	SCALD_POPUP_LAYER_NAME,				"変換色素",
	SCALD_TRANSFORM_TOPIC_START_NAME,	"トランスフォーム",
	SCALD_TRANSFORM_POINT_NAME,			"位置",
	SCALD_TRANSFORM_SCALE_RATIO_NAME,	"縦横比を固定",
	SCALD_TRANSFORM_SCALE_NAME,			"スケール",
	SCALD_TRANSFORM_SCALEH_NAME,		"スケールの高さ",
	SCALD_TRANSFORM_SCALEW_NAME,		"スケールの幅",
	SCALD_TRANSFORM_ROTATE_NAME,		"回転",
	SCALD_TRANSFORM_ALPHA_NAME,			"不透明度",
};

char	*GetStringPtr(int strNum)
{
	return g_strs[strNum].str;
}
	