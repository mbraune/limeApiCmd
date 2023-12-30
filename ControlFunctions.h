#pragma once
#include "CmdParameter.h"

//
// prototypes
//
int handle_About();
int handle_Help();
int handle_Syscmd(const CCmdParameter& cPara);
int handle_Devid();
int handle_Init();
int handle_Reset();
int handle_GetChipTemperature(const CCmdParameter& cPara);
int handle_EnableChannel(const CCmdParameter& cPara);
int handle_SetAntenna(const CCmdParameter& cPara);
int handle_GetAntenna(const CCmdParameter& cPara);
int handle_SetLOFrequency(const CCmdParameter& cPara);
int handle_GetLOFrequency(const CCmdParameter& cPara);
int handle_SetNormalizedGain(const CCmdParameter& cPara);
int handle_GetNormalizedGain(const CCmdParameter& cPara);
int handle_SetGaindB(const CCmdParameter& cPara);
int handle_GetGaindB(const CCmdParameter& cPara);
int handle_SetSampleRate(const CCmdParameter& cPara);
int handle_GetSampleRate(const CCmdParameter& cPara);
int handle_LoadConfig(const CCmdParameter& cPara);
int handle_SaveConfig(const CCmdParameter& cPara);
int handle_Synchronize(const CCmdParameter& cPara);
int handle_SetClockFreq(const CCmdParameter& cPara);
int handle_GetClockFreq(const CCmdParameter& cPara);
int handle_VCTCXORead(const CCmdParameter& cPara);
int handle_VCTCXOWrite(const CCmdParameter& cPara);
int handle_RxStreamSetup(const CCmdParameter& cPara);
int handle_RxStreamStart(const CCmdParameter& cPara);
int handle_RxStreamRead(const CCmdParameter& cPara);
int handle_RxStreamStop(const CCmdParameter& cPara);
int handle_RxStreamDestroy(const CCmdParameter& cPara);
int handle_Close();

//
// helper
//
double p_dbm(int16_t* buf, int size);
