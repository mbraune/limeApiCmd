// ControlFunctions.cpp
//

#include <iostream>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <vector>
#include "LimeSuite.h"
#include "ControlFunctions.h"


using namespace std;

lms_stream_t streamRx;

// print cmd_ok and return value
int ret_cmdok(int i) {
    if (i == 0) cout << "cmd_ok" << endl;
    else        cout << "err_1001" << endl;
    return i;
}

//############################################
// handle_cmd  functions

int handle_About()
{
    cout << "\tversion " << LIMEAPICMD_VERSION << endl;
    cout << "\tdll     " << LMS_GetLibraryVersion() << endl;
    return ret_cmdok(0);
}

int handle_Help()
{
    show_usage();
    return ret_cmdok(0);
}

// execute system command
//  e.g. syscmd(cls)  or syscmd(ls)
int handle_Syscmd(const CCmdParameter& cPara)
{
    int res = -1;
    string s1 = cPara.m_stPara[0].valString;
    string s2 = "\"" + s1 + "\"";
    res = system(s2.c_str());
    return ret_cmdok(res);
}

int handle_Devid()
{
    stringstream ss;
    const lms_dev_info_t* devInfo;
    devInfo = LMS_GetDeviceInfo(device);
    ss << "\t" << hex << uppercase << devInfo->boardSerialNumber << endl;
    cout << ss.str();
    return ret_cmdok(0);
}

int handle_Init()
{
    int res = LMS_Init(device);
    return ret_cmdok(res);
}

int handle_Reset()
{
    int res = LMS_Reset(device);
    return ret_cmdok(res);
}

int handle_GetChipTemperature(const CCmdParameter& cPara)
{
    int res = -1;
    size_t chipindex = 0;  //  error if index !=0
    float_type temp;
    res = LMS_GetChipTemperature(device, chipindex, &temp);
    cout << "\t" << temp << endl;
    return ret_cmdok(res);
}

int handle_EnableChannel(const CCmdParameter& cPara)
{
    int res = -1;
    bool bTx    = (cPara.m_stPara[0].valInt == 1);
    size_t ch   = cPara.m_stPara[1].valInt;
    bool bEn    = (cPara.m_stPara[2].valInt == 1);
    res = LMS_EnableChannel(device, bTx, ch, bEn);
    return ret_cmdok(res);
}

int handle_SetAntenna(const CCmdParameter& cPara)
{
    int res = -1;
    bool bTx   = (cPara.m_stPara[0].valInt == 1);
    size_t ch  = cPara.m_stPara[1].valInt;
    size_t idx = cPara.m_stPara[2].valInt;
    res = LMS_SetAntenna(device, bTx, ch, idx);
    return ret_cmdok(res);
}

int handle_GetAntenna(const CCmdParameter& cPara)
{
    int res = -1;
    bool bTx = (cPara.m_stPara[0].valInt == 1);
    size_t ch = cPara.m_stPara[1].valInt;
    size_t idx = LMS_GetAntenna(device, bTx, ch);
    cout << "\t" << idx << endl;
    if (idx != -1) res = 0;
    return ret_cmdok(res);
}

int handle_SetLOFrequency(const CCmdParameter& cPara)
{
    int res = -1;
    bool bTx     = (cPara.m_stPara[0].valInt == 1);
    size_t ch    = cPara.m_stPara[1].valInt;
    float_type f = cPara.m_stPara[2].valFloat;
    res = LMS_SetLOFrequency(device, bTx, ch, f*1e6);
    return ret_cmdok(res);
}

int handle_GetLOFrequency(const CCmdParameter& cPara)
{
    int res = -1;
    bool bTx = (cPara.m_stPara[0].valInt == 1);
    size_t ch = cPara.m_stPara[1].valInt;
    float_type f;
    res = LMS_GetLOFrequency(device, bTx, ch, &f);

    stringstream ss;
    ss << "\t" << fixed << setprecision(6) << f / 1e6 << " MHz\n";
    cout << ss.str();
    return ret_cmdok(res);
}

int handle_SetNormalizedGain(const CCmdParameter& cPara)
{
    int res = -1;
    bool bTx = (cPara.m_stPara[0].valInt == 1);
    size_t ch = cPara.m_stPara[1].valInt;
    float_type gn = cPara.m_stPara[2].valFloat;
    res = LMS_SetNormalizedGain(device, bTx, ch, gn);
    return ret_cmdok(res);
}

int handle_GetNormalizedGain(const CCmdParameter& cPara)
{
    int res = -1;
    bool bTx = (cPara.m_stPara[0].valInt == 1);
    size_t ch = cPara.m_stPara[1].valInt;
    float_type gn = 0;
    res = LMS_GetNormalizedGain(device, bTx, ch, &gn);
    cout << "\t" << fixed << setprecision(2) << gn << endl;
    return ret_cmdok(res);
}

int handle_SetGaindB(const CCmdParameter& cPara)
{
    int res = -1;
    bool bTx    = (cPara.m_stPara[0].valInt == 1);
    size_t ch   = cPara.m_stPara[1].valInt;
    unsigned gn = cPara.m_stPara[2].valInt;
    res = LMS_SetGaindB(device, bTx, ch, gn);
    return ret_cmdok(res);
}

int handle_GetGaindB(const CCmdParameter& cPara)
{
    int res = -1;
    bool bTx    = (cPara.m_stPara[0].valInt == 1);
    size_t ch   = cPara.m_stPara[1].valInt;
    unsigned gn = 0;
    res = LMS_GetGaindB(device, bTx, ch, &gn);
    cout << "\t" << gn << endl;
    return ret_cmdok(res);
}

int handle_SetSampleRate(const CCmdParameter& cPara)
{
    int res = -1;
    float_type rate = cPara.m_stPara[0].valFloat;
    size_t over     = cPara.m_stPara[1].valInt;
    res = LMS_SetSampleRate(device, rate*1e6, over);
    return ret_cmdok(res);
}

int handle_GetSampleRate(const CCmdParameter& cPara)
{
    int res = -1;
    bool bTx = (cPara.m_stPara[0].valInt == 1);
    size_t ch = cPara.m_stPara[1].valInt;

    float_type f_host;
    float_type f_rf;
    res = LMS_GetSampleRate(device, bTx, ch, &f_host, &f_rf);
    cout << "\t" << f_host/ 1e6 << " MHz" << endl;
    cout << "\t" << f_rf/1e6    << " MHz"  << endl;
    return ret_cmdok(res);
}

int handle_LoadConfig(const CCmdParameter& cPara)
{
    int res = -1;
    const char* file = cPara.m_stPara[0].valString.c_str();
    res = LMS_LoadConfig(device, file);
    return ret_cmdok(res);
}

int handle_SaveConfig(const CCmdParameter& cPara)
{
    int res = -1;
    const char* file = cPara.m_stPara[0].valString.c_str();
    res = LMS_SaveConfig(device, file);
    return ret_cmdok(res);
}

int handle_Synchronize(const CCmdParameter& cPara)
{
    int res = -1;
    bool bTochip = (cPara.m_stPara[0].valInt == 1);
    res = LMS_Synchronize(device, bTochip);
    return ret_cmdok(res);
}

int handle_SetClockFreq(const CCmdParameter& cPara)
{
    int res = -1;
    size_t clkid = cPara.m_stPara[0].valInt;
    float_type f = cPara.m_stPara[1].valFloat;
    LMS_SetClockFreq(device, clkid, f*1e6);
    return ret_cmdok(res);
}

int handle_GetClockFreq(const CCmdParameter& cPara)
{
    int res = -1;
    size_t clkid = cPara.m_stPara[0].valInt;
    float_type f;
    res = LMS_GetClockFreq(device, clkid, &f);
    stringstream ss;
    ss << "\t" << fixed << setprecision(6) << f/1e6 << " MHz\n";
    cout << ss.str();
    return ret_cmdok(res);
}

int handle_VCTCXORead(const CCmdParameter& cPara)
{
    int res = -1;
    uint16_t val = 0;
    res = LMS_VCTCXORead(device, &val);
    cout << "\t" << val << endl;
    return ret_cmdok(res);
}

int handle_VCTCXOWrite(const CCmdParameter& cPara)
{
    int res = -1;
    uint16_t val = cPara.m_stPara[0].valInt;
    res = LMS_VCTCXOWrite(device, val);
    return ret_cmdok(res);
}

int handle_RxStreamSetup(const CCmdParameter& cPara)
{
    streamRx.channel = 0; //channel number
    streamRx.fifoSize = 1024 * 1024; //fifo size in samples
    streamRx.throughputVsLatency = 1.0; //optimize for max throughput
    streamRx.isTx = false; //RX channel
    streamRx.dataFmt = lms_stream_t::LMS_FMT_I12; //12-bit integers
    int res = LMS_SetupStream(device, &streamRx);
    return ret_cmdok(res);
}

int handle_RxStreamStart(const CCmdParameter& cPara)
{
    int res = -1;
    if (streamRx.handle != 0)
        res = LMS_StartStream(&streamRx);
    return ret_cmdok(res);
}

int handle_RxStreamRead(const CCmdParameter& cPara)
{
    int res = -1;
    if (streamRx.handle == 0)
        return ret_cmdok(res);

    int32_t sampleCnt = cPara.m_stPara[0].valInt;
    const char* file  = cPara.m_stPara[1].valString.c_str();

    std::vector<int16_t> sampleBuf(sampleCnt * 2);
    int samplesRead;
    samplesRead = LMS_RecvStream(&streamRx, &sampleBuf[0], sampleCnt, NULL, 1000);

    // write data to gp file
    std::ofstream outFile(file);
    stringstream ss;
    ss << "set size square" << endl << "set xrange[-2050:2050]" << endl << "set yrange[-2050:2050]" << endl;
    ss << "plot '-' with points" << endl;;
    for (int j = 0; j < samplesRead; ++j)
        ss << sampleBuf[2 * j] << " " << sampleBuf[2 * j + 1] << endl;
    ss << 'e';
    outFile << ss.rdbuf();
    outFile.close();

    cout << "\tp_dbm " << fixed << setprecision(2) << p_dbm(&sampleBuf[0], samplesRead) << endl;
    res = !(samplesRead == sampleCnt);
    return ret_cmdok(res);
}

int handle_RxStreamStop(const CCmdParameter& cPara)
{
    int res = -1;
    if (streamRx.handle != 0)
        res = LMS_StopStream(&streamRx);
    return ret_cmdok(res);
}

int handle_RxStreamDestroy(const CCmdParameter& cPara)
{
    int res = LMS_DestroyStream(device, &streamRx);
    return ret_cmdok(res);
}

int handle_Close() {
    int res = LMS_Close(device);
    return ret_cmdok(res);
}


//
// helper
//
double p_dbm(int16_t* buf, int size)
{
    double sum = 0.0;
    int16_t i, q;
    for (int j = 0; j < size; ++j) {
        i = buf[2 * j];
        q = buf[2 * j + 1];
        sum += i * i + q * q;
    }
    sum = sum / size;
    return (10 * log10(sum) - 110);  // -110 offset with normalized gain 0.78
}