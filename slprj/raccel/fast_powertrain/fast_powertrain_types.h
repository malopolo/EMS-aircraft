#ifndef RTW_HEADER_fast_powertrain_types_h_
#define RTW_HEADER_fast_powertrain_types_h_
#include "rtwtypes.h"
#include "builtin_typeid_types.h"
#include "multiword_types.h"
#ifndef DEFINED_TYPEDEF_FOR_struct_qjR3VVL6XOE0TG2ANcx3RE_
#define DEFINED_TYPEDEF_FOR_struct_qjR3VVL6XOE0TG2ANcx3RE_
typedef struct { uint8_T SimulinkDiagnostic ; uint8_T Model [ 15 ] ; uint8_T
Block [ 38 ] ; uint8_T OutOfRangeInputValue ; uint8_T NoRuleFired ; uint8_T
EmptyOutputFuzzySet ; uint8_T sl_padding0 [ 7 ] ; }
struct_qjR3VVL6XOE0TG2ANcx3RE ;
#endif
#ifndef DEFINED_TYPEDEF_FOR_struct_0sCPl2iL0Y7nsABAISPuqB_
#define DEFINED_TYPEDEF_FOR_struct_0sCPl2iL0Y7nsABAISPuqB_
typedef struct { uint8_T type [ 7 ] ; uint8_T sl_padding0 ; int32_T
origTypeLength ; uint8_T sl_padding1 [ 4 ] ; real_T params [ 2 ] ; int32_T
origParamLength ; uint8_T sl_padding2 [ 4 ] ; } struct_0sCPl2iL0Y7nsABAISPuqB
;
#endif
#ifndef DEFINED_TYPEDEF_FOR_struct_2MXDb7W4JJZIDRf8j3cpxG_
#define DEFINED_TYPEDEF_FOR_struct_2MXDb7W4JJZIDRf8j3cpxG_
typedef struct { struct_0sCPl2iL0Y7nsABAISPuqB mf [ 4 ] ; int32_T origNumMF ;
uint8_T sl_padding0 [ 4 ] ; } struct_2MXDb7W4JJZIDRf8j3cpxG ;
#endif
#ifndef DEFINED_TYPEDEF_FOR_struct_IcLJdXzcioJA7MwAM7PNMG_
#define DEFINED_TYPEDEF_FOR_struct_IcLJdXzcioJA7MwAM7PNMG_
typedef struct { uint8_T type [ 7 ] ; uint8_T andMethod [ 3 ] ; uint8_T
orMethod [ 3 ] ; uint8_T defuzzMethod [ 8 ] ; uint8_T impMethod [ 3 ] ;
uint8_T aggMethod [ 3 ] ; uint8_T sl_padding0 [ 5 ] ; real_T inputRange [ 4 ]
; real_T outputRange [ 2 ] ; struct_2MXDb7W4JJZIDRf8j3cpxG inputMF [ 2 ] ;
struct_2MXDb7W4JJZIDRf8j3cpxG outputMF ; real_T antecedent [ 24 ] ; real_T
consequent [ 12 ] ; real_T connection [ 12 ] ; real_T weight [ 12 ] ; int32_T
numSamples ; int32_T numInputs ; int32_T numOutputs ; int32_T numRules ;
int32_T numInputMFs [ 2 ] ; int32_T numCumInputMFs [ 2 ] ; int32_T
numOutputMFs ; int32_T numCumOutputMFs ; real_T outputSamplePoints [ 2 ] ;
int32_T orrSize [ 2 ] ; int32_T aggSize [ 2 ] ; int32_T irrSize [ 2 ] ;
int32_T rfsSize [ 2 ] ; int32_T sumSize [ 2 ] ; int32_T inputFuzzySetType ;
uint8_T sl_padding1 [ 4 ] ; } struct_IcLJdXzcioJA7MwAM7PNMG ;
#endif
typedef struct P_ P ;
#endif
