#include "CmdParameter.h"
#include <algorithm>
#include <sstream>

// constructor
// perform initialization, parsing and parameter extraction
CCmdParameter::CCmdParameter(const std::string cmd)
{
    m_sRawCmd   = cmd;
    m_bHelp     = (m_sRawCmd.find('?' ) != std::string::npos);
    m_sParaList = getParaListString(cmd);

    // initialize m_stPara stCfPara    
    //reset the data
    for (int i = 0; i < CF_MAX_PARA; i++) {
        m_stPara[i].ptype = pt_None;
        m_stPara[i].valInt = -1;
        m_stPara[i].valFloat = -9999.9;
        m_stPara[i].valString = "nix";
    }

    m_idx = getIndex();
    if (m_idx >= 0) {
        m_bValid = true;
        m_eCF = (CtrlFunc)m_idx;
        m_sUsage = "usage  : " + cf_usage[m_idx];

        // set expected number of parameters and parameter types for this idx
        m_nPara = 0;
        for (int i = 0; i < CF_MAX_PARA; i++) {
            m_pt[i] = cf_ParaT[m_idx][i];
            m_nPara += (m_pt[i] != pt_None);
        }
    }

    // if valid and num parameters>0 , extract parameter from string
    if (m_bValid) {
        for (int i = 0; i < m_nPara; i++) {
            m_stPara[i].ptype = m_pt[i];

            int res = -1;
            switch (m_pt[i]) {
            case pt_Int:
                res = getIntVal(i, &m_stPara[i].valInt);
                break;
            case pt_Float:
                res = getFloatVal(i, &m_stPara[i].valFloat);
                break;
            case pt_String:
                res = getStringVal(i, &m_stPara[i].valString);
                break;
            }
            m_bValid = (res == 0);

            if (!m_bValid) break;
        }
    }
}


// extract parameter part between ( and )
// transform string tolower and remove whitespace
std::string CCmdParameter::getParaListString(const std::string s)
{
    std::string sp;
    size_t p1 = s.find("(");
    size_t p2 = s.find(")");
    if ((p1 != std::string::npos) && (p2 != std::string::npos)) {
        sp = s.substr(p1+1, p2-(p1+1));
        transform(sp.begin(), sp.end(), sp.begin(), ::tolower);
        sp.erase(std::remove(sp.begin(), sp.end(), ' '), sp.end());         //remove whitespace
    }
    return sp;
}


//
int CCmdParameter::getIndex()
{
    const int n = sizeof(strCtrlFunc) / sizeof(strCtrlFunc[0]);
    for (int i = 0; i < n; ++i)
    {
        //transform szCtrlFunc tolower string
        std::string cs = strCtrlFunc[i];
        transform(cs.begin(), cs.end(), cs.begin(), ::tolower);
        // transform search string tolower
        transform(m_sRawCmd.begin(), m_sRawCmd.end(), m_sRawCmd.begin(), ::tolower);
        if (m_sRawCmd.find(cs) != std::string::npos)
            return i;
    }
    return -1;
}

int CCmdParameter::getIntVal(size_t idx, /*out*/  int *val)
{
    int res = -1;

    std::string token;
    std::istringstream tokenStream(m_sParaList);
    int nCnt = 0;
    while (std::getline(tokenStream, token, ','))
    {
        if (nCnt == idx) {
            res = 0;
            if (token == "tx")      *val = 1;
            else if (token == "rx") *val = 0;
            else {
                try {
                    *val = stoi(token);
                }
                catch (const std::invalid_argument ) {
                    *val = -1;
                    res = -1;
                }
                catch (const std::exception )
                {
                    *val = -1;
                    res = -1;
                }
            }
        }
        nCnt++;
    }
    return res;
}

int CCmdParameter::getFloatVal(size_t idx, /*out*/ float_type *val)
{
    int res = -1;

    std::string token;
    std::istringstream tokenStream(m_sParaList);
    int nCnt = 0;
    while (std::getline(tokenStream, token, ','))
    {
        if (nCnt == idx) {
            res = 0;
            try {
                *val = stof(token);
            }
            catch (const std::invalid_argument) {
                *val = -0.99;
                res = -1;
            }
            catch (const std::exception)
            {
                *val = -0.99;
                res = -1;
            }
        }
        nCnt++;
    }
    return res;
}

int CCmdParameter::getStringVal(size_t idx, /*out*/ std::string* val)
{
    int res = -1;

    std::string token;
    std::istringstream tokenStream(m_sParaList);
    int nCnt = 0;
    while (std::getline(tokenStream, token, ','))
    {
        if (nCnt == idx) {
            *val = token;
            res = 0;
        }
        nCnt++;
    }
    return res;
}
