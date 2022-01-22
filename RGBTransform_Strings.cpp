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
	StrID_Description,					"���[�邶�[�с[�����Ă����",
	SCALD_BUTTON_NAME,					"Scald",
	SCALD_LAYER_NAME,					"���C���[",
	SCALD_POPUP_SRC_NAME,				"�\�[�X�F�f",
	SCALD_POPUP_LAYER_NAME,				"�ϊ��F�f",
	SCALD_TRANSFORM_TOPIC_START_NAME,	"�g�����X�t�H�[��",
	SCALD_TRANSFORM_POINT_NAME,			"�ʒu",
	SCALD_TRANSFORM_SCALE_RATIO_NAME,	"�c������Œ�",
	SCALD_TRANSFORM_SCALE_NAME,			"�X�P�[��",
	SCALD_TRANSFORM_SCALEH_NAME,		"�X�P�[���̍���",
	SCALD_TRANSFORM_SCALEW_NAME,		"�X�P�[���̕�",
	SCALD_TRANSFORM_ROTATE_NAME,		"��]",
	SCALD_TRANSFORM_ALPHA_NAME,			"�s�����x",
};

char	*GetStringPtr(int strNum)
{
	return g_strs[strNum].str;
}
	