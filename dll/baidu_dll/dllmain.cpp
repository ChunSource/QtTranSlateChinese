// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "stdafx.h"
#include <ocr.h>
#include <iterator>
#include <iostream>
using namespace std;

#pragma comment(lib,"lib_json.lib")
//#pragma comment(lib,"libssl.lib")
#pragma comment(lib,"libcrypto.lib")

#pragma comment(lib,"curl.lib")

std::string app_id = "15549004";
std::string api_key = "6WXNoajCyanLL6KfHfFTSfsF";
std::string secret_key = "zzCBQnbRgXivqm9CbYSa2GLuNVmYa8Ej";

aip::Ocr client(app_id, api_key, secret_key);
extern "C" _declspec(dllexport)void init()
{
//	aip::Ocr client(app_id, api_key, secret_key);
}

extern "C" _declspec(dllexport)char* tran()
{
	cout << "tran():";
	Json::Value result;

	std::string image;
	aip::get_file_content("d:/tran.jpg", &image);

	// 调用网络图片文字识别, 图片参数为本地图片
//	result = client.web_image(image, aip::null);

	// 如果有可选参数
	std::map<std::string, std::string> options;
	options["language_type"] = "ENG";

	// 带参数调用网络图片文字识别, 图片参数为本地图片
	result = client.web_image(image, options);
	string buf = result.toStyledString();
	cout << "buf:" << buf.data();
	char* ch = new char[1024];
	const char* cpc = (char*)buf.c_str();
	memcpy(ch, cpc, buf.length());
	*(ch + buf.length()) = '\0';
	return ch;
}
BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

