/* ----------------------------------------------------------------------------
 *   Includes
 * ---------------------------------------------------------------------------- */
#include "tee_internal_api.h"
#include "tee_ext_api.h"
#include "tee_log.h"
#include "securec.h"


#define TA_TEMPLATE_VERSION        "V1_20160111"             //an version number(integer) + last modified time

/*
   typedef struct{
   char *packagename;
   char *modulus;
   char *public_exponent;
   } Login_struct;

   static Login_struct login_demo[] =
   {
   {"com.ctd.wasmappstore".
   "E02C5AB97A2B3A8A5996223CDE06B82B2D4FF5B15CAF65B860D5C7A3D68995AB08620BB75A22FE7673A8A1ABA03E17B651D1FC4D5CBDBAE9E73EEEAF5A1D4D2FB73E7000231E0DB2166D0FC5DD97E705FD66546C9DA38ED4EFA2CCCDD238AD32E39821242B0195DF01D9B97242DBF209EDA8E446E043244B84E6BFCA79D7BB3C1924CDD248EDBD600EFF8F73001A89A4C663DB8970E3288B9431524C361E853B8FA29E04E61EBE6FBDBD87CDBD3EEB47B027B5851BDEAA13A23F43967A030E747EA432652CBB34FDDE61049BF5060C813FB0E93F6BAD9D36F4D4551195EA3BB49E9201AA6DF975AE169E214905DE2579D7CC3C3EAC4594B14AC19D7E39C5C267",
   "65537"},
   };
   */
enum
{
	CMD_GET_TA_VERSION = 1,
};

static TEE_Result get_TA_version(char* buffer, uint32_t max_buf_len, uint32_t *buf_len)
{
	TEE_Result ret;
	ret = (TEE_Result)strncpy_s(buffer, max_buf_len, (char*)TA_TEMPLATE_VERSION, strlen((char*)TA_TEMPLATE_VERSION));
	if (ret) {
		SLogError("get_TA_version strncpy_s error, ret = %d.\n", ret);
		return ret;
	}

	*buf_len = strlen(buffer);

	return TEE_SUCCESS;
}


/* ----------------------------------------------------------------------------
 *   Trusted Application Entry Points
 * ---------------------------------------------------------------------------- */

/**
 *  Function TA_CreateEntryPoint
 *  Description:
 *    The function TA_CreateEntryPoint is the Trusted Application's constructor,
 *    which the Framework calls when it creates a new instance of the Trusted Application.
 */
TEE_Result TA_CreateEntryPoint(void)
{
	SLogTrace("----- TA_CreateEntryPoint ----- ");
	SLogTrace("TA version: %s ", TA_TEMPLATE_VERSION);


	/*
	 * Add the info of the CA/TA which is allowed to call this TA.
	 * 鍦ㄦ澧炲姞鍏佽璁块棶鏈琓A鐨凜A鎴朤A鐨勪俊鎭�.
	 *
	 * use the following functions:
	 *
	 *    // if caller is a CA and it's an Executable file.
	 *
	 *    TEE_Result AddCaller_CA_exec(char* ca_name, uint32_t ca_uid);
	 *
	 *    // if caller is a CA and it's an APK.
	 *    // (modulus here is a string, and it's length must be the integral multiple of 256)
	 *
	 *    TEE_Result AddCaller_CA_apk(char* ca_name, char *modulus, char *pub_exponent);
	 *
	 *    // if caller is a TA
	 *    // (isAll = 0   only allow the TA has 'ta_uuid' to call this TA.)
	 *    // (isAll = 1   allow all the TA to call this TA.)
	 *
	 *    TEE_Result AddCaller_TA(TEE_UUID* ta_uuid, uint32_t isAll);
	 */
	// example for AddCaller_CA_exec
	{
		char *packageName = "/system/bin/tee_test_ut";
		uint32_t uid = 0;

		if (TEE_SUCCESS == AddCaller_CA_exec(packageName, uid)) {
			SLogTrace("TA_CreateEntryPoint: AddCaller_CA_exec ok.");
		} else {
			SLogError("TA_CreateEntryPoint: AddCaller_CA_exec failed.");
			return TEE_ERROR_GENERIC;
		}
	}
	//example for AddCaller_CA_exec
	{
		char *packageName = "/system/bin/Template-demoCA";
		uint32_t uid = 0;

		if (TEE_SUCCESS == AddCaller_CA_exec(packageName, uid)) {
			SLogTrace("TA_CreateEntryPoint: AddCaller_CA_exec ok.");
		} else {
			SLogError("TA_CreateEntryPoint: AddCaller_CA_exec failed.");
			return TEE_ERROR_GENERIC;
		}
	}
	//example for AddCaller_CA_apk
	{
		char *packageName = "com.ctd.wasmappstore";
		char *modulus = "c5169effcc46070be2e7389eefe57d3a4bb66e8e7504ab3ae6815cfbf013b7fc83c92623a84a5b8c03f9203091894cc997b7364eae2af38ffea83f13b8d8da3d56d756e74f176810ac742a6cd4bbd257c85e316dfc8fd5bedad60b6358a8b55e2d55d90f742b70e856a170a2ae0cd51aae50f755de0560a5522f06167c4b2d028e9a396241c2c5aec242a1f513a6cc6f95f3f383417de94f9336761c7f5df3452467e314abf53381730b8b91cb5e3890801e588a5e6c0492f4d42f014ddca4604260fd0dfce056364e2cb0fcfaee89f77ceab57cb0453e6fd6680af47062d572f367a62d63907ed8ff5bf3116a6c7b56c1f4107c81195b41bd95b5bd266d1935";
		char *public_exponent = "10001";
		if (TEE_SUCCESS == AddCaller_CA_apk(packageName, modulus, public_exponent)) {
			SLogTrace("TA_CreateEntryPoint: AddCaller_CA_apk ok.");
		} else {
			SLogError("TA_CreateEntryPoint: AddCaller_CA_apk failed.");
			return TEE_ERROR_GENERIC;
		}
	}
	//example for AddCaller_TA
	//NOTICE:  This allows all TA to call your TA, so you NEED to check TA's uuid yourself!
	{
		if (TEE_SUCCESS == AddCaller_TA_all()) {
			SLogTrace("TA_CreateEntryPoint: AddCaller_TA ok.");
		} else {
			SLogError("TA_CreateEntryPoint: AddCaller_TA failed.");
			return TEE_ERROR_GENERIC;
		}
	}
	/* end - add caller info*/

	return TEE_SUCCESS;
}

/**
 *  Function TA_OpenSessionEntryPoint
 *  Description:
 *    The Framework calls the function TA_OpenSessionEntryPoint
 *    when a client requests to open a session with the Trusted Application.
 *    The open session request may result in a new Trusted Application instance
 *    being created.
 */
TEE_Result TA_OpenSessionEntryPoint(uint32_t paramTypes,
	TEE_Param params[4], void** sessionContext)
{
	(void)paramTypes;  /* -Wunused-parameter */
	(void)params;  /* -Wunused-parameter */
	(void)sessionContext;  /* -Wunused-parameter */
	TEE_Result ret=TEE_SUCCESS;
	SLogTrace("---- TA_OpenSessionEntryPoint -------- ");

	return ret;
}

/**
 *  Function TA_InvokeCommandEntryPoint:
 *  Description:
 *    The Framework calls this function when the client invokes a command
 *    within the given session.
 */
TEE_Result TA_InvokeCommandEntryPoint(void* sessionContext, uint32_t cmd_id,
	uint32_t paramTypes, TEE_Param params[4])
{
	TEE_Result ret=TEE_SUCCESS;
	uint32_t buf_len = 0;

	(void)sessionContext;  /* -Wunused-parameter */

	SLogTrace("---- TA_InvokeCommandEntryPoint ----------- ");
	switch(cmd_id) {
	case CMD_GET_TA_VERSION:
		if (!check_param_type(paramTypes,
				TEE_PARAM_TYPE_NONE,
				TEE_PARAM_TYPE_NONE,
				TEE_PARAM_TYPE_NONE,
				TEE_PARAM_TYPE_MEMREF_OUTPUT)) {
			SLogError("Bad expected parameter types\n");
			return TEE_ERROR_BAD_PARAMETERS;
		}
		if (params[3].memref.buffer == NULL ||
			params[3].memref.size < 256) {
			ret = TEE_ERROR_BAD_PARAMETERS;
			SLogError("InvokeCommand bad parameters:0x%x.", ret);
		}
		ret = get_TA_version(params[3].memref.buffer, params[3].memref.size, &buf_len);
		if(ret != TEE_SUCCESS) {
			SLogError("InvokeCommand Failed 0x%x. cmd_id is %d.", ret, cmd_id);
			return ret;
		} else {
			params[3].memref.size = buf_len;
			SLogTrace("InvokeCommand Successed, CmdId = %d.", CMD_GET_TA_VERSION);
		}
		break;

	default:
		SLogError("Unknown CMD ID: %d", cmd_id);
		ret = TEE_FAIL;
	}

	return  ret;
}

/**
 *  Function TA_CloseSessionEntryPoint:
 *  Description:
 *    The Framework calls this function to close a client session.
 *    During the call to this function the implementation can use
 *    any session functions.
 */
void TA_CloseSessionEntryPoint(void* sessionContext)
{
	(void)sessionContext;  /* -Wunused-parameter */
	SLogTrace("---- TA_CloseSessionEntryPoint ----- " );
}

/**
 *  Function TA_DestroyEntryPoint
 *  Description:
 *    The function TA_DestroyEntryPoint is the Trusted Application's destructor,
 *    which the Framework calls when the instance is being destroyed.
 */
void TA_DestroyEntryPoint(void)
{
	SLogTrace("---- TA_DestroyEntryPoint ---- ");
}
