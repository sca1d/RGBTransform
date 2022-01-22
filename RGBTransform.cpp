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

/*	Skeleton.cpp	

	This is a compiling husk of a project. Fill it in with interesting
	pixel processing code.
	
	Revision History

	Version		Change													Engineer	Date
	=======		======													========	======
	1.0			(seemed like a good idea at the time)					bbb			6/1/2002

	1.0			Okay, I'm leaving the version at 1.0,					bbb			2/15/2006
				for obvious reasons; you're going to 
				copy these files directly! This is the
				first XCode version, though.

	1.0			Let's simplify this barebones sample					zal			11/11/2010

	1.0			Added new entry point									zal			9/18/2017

*/

#define WINDOWS_IGNORE_PACKING_MISMATCH

#include <stdio.h>
#include <stdlib.h>

#include <thread>
#include <atomic>
#include <map>
#include <mutex>
#include <assert.h>

#include "RGBTransform.h"

//#include "..\FsLibrary\Fs.h"

const char* color_items[] = { "全て", "赤", "緑", "青" };

static PF_Err 
About (	
	PF_InData		*in_data,
	PF_OutData		*out_data,
	PF_ParamDef		*params[],
	PF_LayerDef		*output )
{
	AEGP_SuiteHandler suites(in_data->pica_basicP);
	
	suites.ANSICallbacksSuite1()->sprintf(	out_data->return_msg,
											"%s v%d.%d\r%s",
											STR(StrID_Name), 
											MAJOR_VERSION, 
											MINOR_VERSION, 
											STR(StrID_Description));
	return PF_Err_NONE;
}

static PF_Err 
GlobalSetup (	
	PF_InData		*in_data,
	PF_OutData		*out_data,
	PF_ParamDef		*params[],
	PF_LayerDef		*output )
{
	out_data->my_version = PF_VERSION(	MAJOR_VERSION, 
										MINOR_VERSION,
										BUG_VERSION, 
										STAGE_VERSION, 
										BUILD_VERSION);
	/*
	out_data->out_flags =	PF_OutFlag_PIX_INDEPENDENT |
							PF_OutFlag_DEEP_COLOR_AWARE |
							PF_OutFlag_NON_PARAM_VARY;

	out_data->out_flags2 =	PF_OutFlag2_FLOAT_COLOR_AWARE |
							PF_OutFlag2_SUPPORTS_SMART_RENDER |
							PF_OutFlag2_SUPPORTS_THREADED_RENDERING;
	*/
	out_data->out_flags = PF_OutFlag_DEEP_COLOR_AWARE;
	return PF_Err_NONE;
}

static PF_Err 
ParamsSetup (	
	PF_InData		*in_data,
	PF_OutData		*out_data,
	PF_ParamDef		*params[],
	PF_LayerDef		*output )
{
	PF_Err		err		= PF_Err_NONE;
	PF_ParamDef	def;

	UI_ADD_BUTTON(SCALD_BUTTON_ID, SCALD_BUTTON_NAME, "info");

	UI_ADD_LAYER(SCALD_LAYER_ID, SCALD_LAYER_NAME, 0);

	UI_ADD_POPUP(SCALD_POPUP_SRC_ID, SCALD_POPUP_SRC_NAME, color_items, 0);

	UI_ADD_POPUP(SCALD_POPUP_LAYER_ID, SCALD_POPUP_LAYER_NAME, color_items, 0);

	UI_TOPIC_START(SCALD_TRANSFORM_TOPIC_START_ID, SCALD_TRANSFORM_TOPIC_START_NAME);

		UI_ADD_POINT(SCALD_TRANSFORM_POINT_ID, SCALD_TRANSFORM_POINT_NAME, 50, 50, FALSE);

		UI_INIT;
		PF_ADD_CHECKBOX("", STR(SCALD_TRANSFORM_SCALE_RATIO_NAME), TRUE, 0, SCALD_TRANSFORM_SCALE_RATIO_ID);
		//UI_ADD_CHECKBOX(SCALD_TRANSFORM_SCALE_RATIO_ID, SCALD_TRANSFORM_SCALE_RATIO_NAME, TRUE);

		UI_INIT;
		PF_ADD_FIXED(STR(SCALD_TRANSFORM_SCALEH_NAME), -15000, 15000, -200, 200, 100, 1, 0, 0, SCALD_TRANSFORM_SCALEH_ID);
		
		UI_INIT;
		PF_ADD_FIXED(STR(SCALD_TRANSFORM_SCALEW_NAME), -15000, 15000, -200, 200, 100, 1, 0, 0, SCALD_TRANSFORM_SCALEW_ID);

		UI_ADD_ANGLE(SCALD_TRANSFORM_ROTATE_ID, SCALD_TRANSFORM_ROTATE_NAME, 0);

		UI_ADD_FIXED(SCALD_TRANSFORM_ALPHA_ID, SCALD_TRANSFORM_ALPHA_NAME, 0, 100, 100, 1);

	UI_TOPIC_END(SCALD_TRANSFORM_TOPIC_END_ID);

	UI_INIT;
	
	out_data->num_params = SCALD_NUM_PARAMS;

	return err;
}

static PF_Err
MakeParamCopy(
	PF_ParamDef* actual[],	/* >> */
	PF_ParamDef copy[])		/* << */
{
	for (A_short iS = 0; iS < SCALD_NUM_PARAMS; ++iS) {
		AEFX_CLR_STRUCT(copy[iS]);	// clean params are important!
	}

	for (int i = 0; i < SCALD_NUM_PARAMS; i++)
	{
		copy[i] = *actual[i];
	}

	return PF_Err_NONE;

}

static PF_Err ParamChanged(
	PF_InData* in_data,
	PF_OutData* out_data,
	PF_SmartRenderExtra* extra
)
{
	PF_Err err = PF_Err_NONE;

	//DEBUG_LOGGER("path:%s\n", INFO_APP_PATH);
	Run(INFO_APP_PATH);

	return err;
}

static PF_Err UpdateParameterUI(
	PF_InData* in_data,
	PF_OutData* out_data,
	PF_ParamDef* params[],
	PF_LayerDef* output
)
{
	PF_Err err = PF_Err_NONE, err2 = PF_Err_NONE;
	AEGP_SuiteHandler		suites(in_data->pica_basicP);

	PF_ParamDef		param_copy[SCALD_NUM_PARAMS];
	ERR(MakeParamCopy(params, param_copy));

	if (!err && GetCheckBoxVal(params, output, SCALD_TRANSFORM_SCALE_RATIO))
	{
		param_copy[SCALD_TRANSFORM_SCALEW].param_type = PF_Param_FIX_SLIDER;
		param_copy[SCALD_TRANSFORM_SCALEW].ui_flags |= PF_PUI_DISABLED;
		strcpy(param_copy[SCALD_TRANSFORM_SCALEH].name, STR(SCALD_TRANSFORM_SCALE_NAME));
		strcpy(param_copy[SCALD_TRANSFORM_SCALEW].name, "");

		ERR(suites.ParamUtilsSuite3()->PF_UpdateParamUI(
			in_data->effect_ref,
			SCALD_TRANSFORM_SCALEW,
			&param_copy[SCALD_TRANSFORM_SCALEW]));
		ERR(suites.ParamUtilsSuite3()->PF_UpdateParamUI(
			in_data->effect_ref,
			SCALD_TRANSFORM_SCALEH,
			&param_copy[SCALD_TRANSFORM_SCALEH]));
	}
	else if (!err && !GetCheckBoxVal(params, output, SCALD_TRANSFORM_SCALE_RATIO) &&
		(!(param_copy[SCALD_TRANSFORM_SCALE_RATIO].ui_flags & PF_PUI_DISABLED)))
	{
		param_copy[SCALD_TRANSFORM_SCALEW].param_type = PF_Param_FIX_SLIDER;
		param_copy[SCALD_TRANSFORM_SCALEW].ui_flags &= ~PF_PUI_DISABLED;
		strcpy(param_copy[SCALD_TRANSFORM_SCALEH].name, STR(SCALD_TRANSFORM_SCALEH_NAME));
		strcpy(param_copy[SCALD_TRANSFORM_SCALEW].name, STR(SCALD_TRANSFORM_SCALEW_NAME));

		ERR(suites.ParamUtilsSuite3()->PF_UpdateParamUI(
			in_data->effect_ref,
			SCALD_TRANSFORM_SCALEW,
			&param_copy[SCALD_TRANSFORM_SCALEW]));
		ERR(suites.ParamUtilsSuite3()->PF_UpdateParamUI(
			in_data->effect_ref,
			SCALD_TRANSFORM_SCALEH,
			&param_copy[SCALD_TRANSFORM_SCALEH]));
	}

	out_data->out_flags |= PF_OutFlag_REFRESH_UI | PF_OutFlag_FORCE_RERENDER;

	return err;

}

void LayerSwitch(
	cv::Mat* src,
	cv::Mat* layer_src,
	A_long popup_src,
	A_long popup_layer,
	int lx,
	int ly,
	int sx,
	int sy
)
{
	if (0 <= sx && 0 <= sy &&
		sx < src->cols && sy < src->rows) {
		switch (popup_src) {
		case AllChannels:
			switch (popup_layer) {
			case AllChannels:
				for (int c = 0; c < 3; c++) {
					src->ptr<Vec3b>(sy, sx)[c] = layer_src->ptr<Vec3b>(ly, lx)[c];
				}
				break;
			case Red:
				for (int c = 0; c < 3; c++) {
					src->ptr<Vec3b>(sy, sx)[c] = layer_src->ptr<Vec3b>(ly, lx)[2];
				}
				break;
			case Green:
				for (int c = 0; c < 3; c++) {
					src->ptr<Vec3b>(sy, sx)[c] = layer_src->ptr<Vec3b>(ly, lx)[1];
				}
				break;
			case Blue:
				for (int c = 0; c < 3; c++) {
					src->ptr<Vec3b>(sy, sx)[c] = layer_src->ptr<Vec3b>(ly, lx)[0];
				}
				break;
			}
			break;
		case Red:
			switch (popup_layer) {
			case AllChannels:
				for (int c = 0; c < 3; c++) {
					src->ptr<Vec3b>(sy, sx)[0] = layer_src->ptr<Vec3b>(ly, lx)[c];
				}
				break;
			case Red:
				src->ptr<Vec3b>(sy, sx)[0] = layer_src->ptr<Vec3b>(ly, lx)[0];
				break;
			case Green:
				src->ptr<Vec3b>(sy, sx)[0] = layer_src->ptr<Vec3b>(ly, lx)[1];
				break;
			case Blue:
				src->ptr<Vec3b>(sy, sx)[0] = layer_src->ptr<Vec3b>(ly, lx)[2];
				break;
			}
			break;
		case Green:
			switch (popup_layer) {
			case AllChannels:
				for (int c = 0; c < 3; c++) {
					src->ptr<Vec3b>(sy, sx)[1] = layer_src->ptr<Vec3b>(ly, lx)[c];
				}
				break;
			case Red:
				src->ptr<Vec3b>(sy, sx)[1] = layer_src->ptr<Vec3b>(ly, lx)[0];
				break;
			case Green:
				src->ptr<Vec3b>(sy, sx)[1] = layer_src->ptr<Vec3b>(ly, lx)[1];
				break;
			case Blue:
				src->ptr<Vec3b>(sy, sx)[1] = layer_src->ptr<Vec3b>(ly, lx)[2];
				break;
			}
			break;
		case Blue:
			switch (popup_layer) {
			case AllChannels:
				for (int c = 0; c < 3; c++) {
					src->ptr<Vec3b>(sy, sx)[2] = layer_src->ptr<Vec3b>(ly, lx)[c];
				}
				break;
			case Red:
				src->ptr<Vec3b>(sy, sx)[2] = layer_src->ptr<Vec3b>(ly, lx)[0];
				break;
			case Green:
				src->ptr<Vec3b>(sy, sx)[2] = layer_src->ptr<Vec3b>(ly, lx)[1];
				break;
			case Blue:
				src->ptr<Vec3b>(sy, sx)[2] = layer_src->ptr<Vec3b>(ly, lx)[2];
				break;
			}
			break;
		}
	}
}

void RGBTransform(cv::Mat* src, cv::Mat* layer_src, DataParams_t* params)
{
	A_long popup_src = GetPopupVal(params->params, params->output, SCALD_POPUP_SRC_ID);
	A_long popup_layer = GetPopupVal(params->params, params->output, SCALD_POPUP_LAYER_ID);

	A_long loc_x = GetPointXVal(params->params, params->output, SCALD_TRANSFORM_POINT_ID);
	A_long loc_y = GetPointYVal(params->params, params->output, SCALD_TRANSFORM_POINT_ID);

	PF_Boolean ratio = GetCheckBoxVal(params->params, params->output, SCALD_TRANSFORM_SCALE_RATIO_ID);
	A_long scaleh = GetFixedVal(params->params, params->output, SCALD_TRANSFORM_SCALEH_ID);
	A_long scalew = GetFixedVal(params->params, params->output, SCALD_TRANSFORM_SCALEW_ID);

	A_long rotate = GetAngleVal(params->params, params->output, SCALD_TRANSFORM_ROTATE_ID);

	A_long alpha = GetFixedVal(params->params, params->output, SCALD_TRANSFORM_ALPHA_ID);

	DEBUG_LOGGER("src layer:%s\n", color_items[popup_src - 1]);
	DEBUG_LOGGER("change color:%s\n", color_items[popup_layer - 1]);
	DEBUG_LOGGER("x:%d y:%d\n", loc_x, loc_y);
	DEBUG_LOGGER("scale ratio:%d\n", ratio);
	DEBUG_LOGGER("scale h:%d scale w:%d\n", scaleh, scalew);
	DEBUG_LOGGER("rotate:%d\n", rotate);
	DEBUG_LOGGER("alpha:%d\n", alpha);

	if (ratio) scalew = scaleh;

	double sizew = (double)scalew / 100.0;
	double sizeh = (double)scaleh / 100.0;

	if (sizew < 0) {
		flip(*layer_src, *layer_src, 1);
		sizew *= -1;
	}
	if (sizeh < 0) {
		flip(*layer_src, *layer_src, 0);
		sizeh *= -1;
	}

	Point2f center = Point2f(
		static_cast<float>(layer_src->cols / 2),
		static_cast<float>(layer_src->rows / 2)
	);

	/*
	Mat affine;
	getRotationMatrix2D(center, -(double)trans->rotate, 1.0).copyTo(affine);
	warpAffine(*layer_src, *layer_src, affine, layer_src->size(), cv::INTER_CUBIC);
	*/

	resize(*layer_src, *layer_src, cv::Size(), sizew, sizeh);

	int sx, sy, lx, ly;

	for (int y = 0; y < layer_src->rows; y++) {
		for (int x = 0; x < layer_src->cols; x++) {
			sx = x + loc_x - layer_src->cols / 2;
			sy = y + loc_y - layer_src->rows / 2;

			lx = x;
			ly = y;

			/*
			for (int c = 0; c < 3; c++) {
				layer_src->ptr<Vec3b>(ly, lx)[c]
					-= layer_src->ptr<Vec3b>(ly, lx)[c] - layer_src->ptr<Vec3b>(ly, lx)[3];
			}
			*/

			LayerSwitch(src, layer_src, popup_src, popup_layer, lx, ly, sx, sy);
		}
	}
}

void FxFunc8(DataParams_t* params)
{
	cv::Mat layer = D2M8(params->layers[SCALD_LAYER_ID]);
	cv::Mat src = D2M8(params->output);

	RGBTransform(&src, &layer, params);

	*params->err = M2D8(src, params->output);
}

void FxFunc16(DataParams_t* params)
{
	DEBUG_LOGGER("プレビュー解像度:1/%d\n", params->sdata->ViewPort);
	DEBUG_LOGGER("フレーム:%d\n", params->sdata->FrameNumber);

	A_long width = *params->sdata->srcWidth / params->sdata->ViewPort;//in_data
	A_long height = *params->sdata->srcHeight / params->sdata->ViewPort;//in_data

	DEBUG_LOGGER("width:%d height:%d\n", width, height);

	cv::Mat layer = D2M16(params->layers[SCALD_LAYER_ID]);
	cv::Mat src = D2M16(params->output);

	RGBTransform(&src, &layer, params);
	/*
	double w2 = (double)src.cols / 2.0;
	double h2 = (double)src.rows / 2.0;

	int x1 = static_cast<int>(w2 - (double)layer.cols / 2.0 + 0.5);
	int y1 = static_cast<int>(h2 - (double)layer.rows / 2.0 + 0.5);

	for (int y = 0; y < layer.rows; y++)
	{
		for (int x = 0; x < layer.cols; x++)
		{
			PF_Pixel16* outData = (PF_Pixel16*)params->output->data;
			A_long outWidth = params->output->rowbytes / sizeof(PF_Pixel16);
			PF_Pixel16* l_outData = (PF_Pixel16*)params->layers[SCALD_LAYER_ID]->data;
			A_long l_outWidth = params->layers[SCALD_LAYER_ID]->rowbytes / sizeof(PF_Pixel16);
			int alpha = l_outData[x + y * l_outWidth].alpha;
			if (alpha == 0xFF)
			{
				for (int c = 0; c < 3; c++)
				{
					src.ptr<Vec3b>(y + y1, x + x1)[c] = layer.ptr<Vec3b>(y, x)[c];
				}
			}
			else if (alpha < 0xFF)
			{
				src.ptr<Vec3b>(y + y1, x + x1)[0] = outData[(y + y1) + (x + x1) * outWidth].blue + (l_outData[x + y * l_outWidth].blue - (PF_MAX_CHAN16 - alpha));
				src.ptr<Vec3b>(y + y1, x + x1)[1] = outData[(y + y1) + (x + x1) * outWidth].green + (l_outData[x + y * l_outWidth].green - (PF_MAX_CHAN16 - alpha));
				src.ptr<Vec3b>(y + y1, x + x1)[2] = outData[(y + y1) + (x + x1) * outWidth].red + (l_outData[x + y * l_outWidth].red - (PF_MAX_CHAN16 - alpha));
			}
		}
	}
	*/

	*params->err = M2D16(src, params->output);
}

void FxFunc32(DataParams_t* params)
{
	PF_Pixel32* outData = (PF_Pixel32*)params->output->data;
}

static PF_Err Render(
	PF_InData		*in_data,
	PF_OutData		*out_data,
	PF_ParamDef		*params[],
	PF_LayerDef		*output
	)
{
	PF_Err				err		= PF_Err_NONE;
	PF_Err				err2	= PF_Err_NONE;

	PF_EffectWorld* input = &params[0]->u.ld;

	ERR(PF_COPY(input, output, NULL, NULL));

	PF_ParamDef param;
	AEFX_CLR_STRUCT(param);

	err = in_data->inter.checkout_param(
		(in_data)->effect_ref,
		SCALD_LAYER,
		in_data->current_time,
		in_data->time_step,
		in_data->time_scale,
		&param
	);

	if (param.u.ld.data != nullptr) {
		PF_LayerDef* layers[SCALD_NUM_PARAMS];
		layers[SCALD_LAYER_ID] = &param.u.ld;
		//DEBUG_LOGGER("[Layer] w:%d h:%d\n", param.u.ld.width, param.u.ld.height);

		SourceData_t sdata = {
			&input->width,
			&input->height,
			&output->width,
			&output->height,
			in_data->current_time / in_data->local_time_step,
			static_cast<int>((double)in_data->width / (double)input->width + 0.5)
		};

		DataParams_t d_params = {
			in_data,
			out_data,
			params,
			output,
			input,
			&err,
			layers,
			&sdata
		};

		//DEBUG_LOGGER("world deep:%d\n", PF_WORLD_IS_DEEP(output));

		if (PF_WORLD_IS_DEEP(output)) {
			try {
				FxFunc16(&d_params);
			}
			catch (...) {
				FxFunc8(&d_params);
			}
		}
		else {

		}
	}

	ERR2(PF_CHECKIN_PARAM(in_data, &param));

	return err;
}

static PF_Err SmartRender(
	PF_InData* in_data,
	PF_OutData* out_data,
	PF_SmartRenderExtra* extraP
)
{
	PF_Err err = PF_Err_NONE;

	PF_EffectWorld* input = NULL, *output = NULL;

	ERR((extraP->cb->checkout_layer_pixels(in_data->effect_ref, SCALD_INPUT, &input)));
	ERR(extraP->cb->checkout_output(in_data->effect_ref, &output));

	//DataParams_t d_params = { in_data, out_data, params, output, input, &err };

	return err;
}

extern "C" DllExport
PF_Err PluginDataEntryFunction(
	PF_PluginDataPtr inPtr,
	PF_PluginDataCB inPluginDataCallBackPtr,
	SPBasicSuite* inSPBasicSuitePtr,
	const char* inHostName,
	const char* inHostVersion)
{
	PF_Err result = PF_Err_INVALID_CALLBACK;

	result = PF_REGISTER_EFFECT(
		inPtr,
		inPluginDataCallBackPtr,
		"Scald_RGBTransform", // Name
		"Scald RGBTransform", // Match Name
		"Scald", // Category
		AE_RESERVED_INFO); // Reserved Info

	return result;
}


PF_Err
EffectMain(
	PF_Cmd			cmd,
	PF_InData		*in_data,
	PF_OutData		*out_data,
	PF_ParamDef		*params[],
	PF_LayerDef		*output,
	void			*extra)
{
	PF_Err		err = PF_Err_NONE;

	#ifdef _DEBUG

	AllocConsole();
	FILE* fp = NULL;
	freopen_s(&fp, "CONOUT$", "w", stdout);
	freopen_s(&fp, "CONIN$", "r", stdin);

	#endif

	DEBUG_LOGGER("---------------------------------------------------\n");
	
	try {
		switch (cmd) {
			case PF_Cmd_ABOUT:
				err = About(in_data, out_data, params, output);
				break;
			case PF_Cmd_GLOBAL_SETUP:
				err = GlobalSetup(in_data, out_data, params, output);
				break;
			case PF_Cmd_PARAMS_SETUP:
				err = ParamsSetup(in_data, out_data, params, output);
				break;
			case PF_Cmd_RENDER:
				err = Render(in_data, out_data, params,	output);
				break;
			case PF_Cmd_SMART_RENDER:
				err = SmartRender(in_data, out_data, (PF_SmartRenderExtra*)extra);
				break;
			case PF_Cmd_USER_CHANGED_PARAM:
				err = ParamChanged(in_data, out_data, (PF_SmartRenderExtra*)extra);
				break;
			case PF_Cmd_UPDATE_PARAMS_UI:
				err = UpdateParameterUI(in_data, out_data, params, output);
		}
	}
	catch(PF_Err &thrown_err){
		err = thrown_err;
	}
	return err;
}


