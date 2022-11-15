# limeApiCmd
interactive command line tool to drive lime API
(see e.g. https://github.com/myriadrf/LimeSuite/blob/master/docs/lms7_api_quick_start_guide.pdf)

## intention
- cmdline access to Lime API cmds (similar to LimeSuite GUI -> Modules -> API Calls )
- usable in scripts
- small footprint, no need to deploy whole soapy toolkit

## dependencies
Lime API interface:
https://github.com/myriadrf/LimeSuite/blob/master/src/lime/LimeSuite.h
https://github.com/myriadrf/LimeSuite/blob/master/src/lime/LMS7002M_parameters.h


## platforms 
at the moment windows only, tbc
### windows dependencies
LimeSuite.lib
LimeSuite.dll
available as part of Pothos SDR suite https://downloads.myriadrf.org/builds/PothosSDR/

### windows build instruction
tested with VStudio 17
- clone repository
- add LimeSuite.lib and LimeSuite.dll to project (copy them to ../src/LimeApiTx)
- open LimeApiTx.sln
