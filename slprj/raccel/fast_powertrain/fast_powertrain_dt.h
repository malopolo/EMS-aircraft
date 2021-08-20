#include "ext_types.h"
static DataTypeInfo rtDataTypeInfoTable [ ] = { { "real_T" , 0 , 8 } , {
"real32_T" , 1 , 4 } , { "int8_T" , 2 , 1 } , { "uint8_T" , 3 , 1 } , {
"int16_T" , 4 , 2 } , { "uint16_T" , 5 , 2 } , { "int32_T" , 6 , 4 } , {
"uint32_T" , 7 , 4 } , { "boolean_T" , 8 , 1 } , { "fcn_call_T" , 9 , 0 } , {
"int_T" , 10 , 4 } , { "pointer_T" , 11 , 8 } , { "action_T" , 12 , 8 } , {
"timer_uint32_pair_T" , 13 , 8 } , { "struct_qjR3VVL6XOE0TG2ANcx3RE" , 14 ,
64 } , { "struct_0sCPl2iL0Y7nsABAISPuqB" , 15 , 40 } , {
"struct_2MXDb7W4JJZIDRf8j3cpxG" , 16 , 168 } , {
"struct_IcLJdXzcioJA7MwAM7PNMG" , 17 , 1168 } } ; static uint_T
rtDataTypeSizes [ ] = { sizeof ( real_T ) , sizeof ( real32_T ) , sizeof (
int8_T ) , sizeof ( uint8_T ) , sizeof ( int16_T ) , sizeof ( uint16_T ) ,
sizeof ( int32_T ) , sizeof ( uint32_T ) , sizeof ( boolean_T ) , sizeof (
fcn_call_T ) , sizeof ( int_T ) , sizeof ( pointer_T ) , sizeof ( action_T )
, 2 * sizeof ( uint32_T ) , sizeof ( struct_qjR3VVL6XOE0TG2ANcx3RE ) , sizeof
( struct_0sCPl2iL0Y7nsABAISPuqB ) , sizeof ( struct_2MXDb7W4JJZIDRf8j3cpxG )
, sizeof ( struct_IcLJdXzcioJA7MwAM7PNMG ) } ; static const char_T *
rtDataTypeNames [ ] = { "real_T" , "real32_T" , "int8_T" , "uint8_T" ,
"int16_T" , "uint16_T" , "int32_T" , "uint32_T" , "boolean_T" , "fcn_call_T"
, "int_T" , "pointer_T" , "action_T" , "timer_uint32_pair_T" ,
"struct_qjR3VVL6XOE0TG2ANcx3RE" , "struct_0sCPl2iL0Y7nsABAISPuqB" ,
"struct_2MXDb7W4JJZIDRf8j3cpxG" , "struct_IcLJdXzcioJA7MwAM7PNMG" } ; static
DataTypeTransition rtBTransitions [ ] = { { ( char_T * ) ( & rtB . nzprtrw2gw
) , 0 , 0 , 152 } , { ( char_T * ) ( & rtB . nvvl1et5cw ) , 8 , 0 , 1 } , { (
char_T * ) ( & rtDW . ae4fdc50fw ) , 0 , 0 , 73 } , { ( char_T * ) ( & rtDW .
jdobxxns3j [ 0 ] ) , 11 , 0 , 67 } , { ( char_T * ) ( & rtDW . jpo5gkezdl [ 0
] ) , 10 , 0 , 12 } , { ( char_T * ) ( & rtDW . jjhzuiuwr5 ) , 2 , 0 , 2 } ,
{ ( char_T * ) ( & rtDW . kt2if2m30y ) , 3 , 0 , 1 } } ; static
DataTypeTransitionTable rtBTransTable = { 7U , rtBTransitions } ; static
DataTypeTransition rtPTransitions [ ] = { { ( char_T * ) ( & rtP . t [ 0 ] )
, 0 , 0 , 363720 } } ; static DataTypeTransitionTable rtPTransTable = { 1U ,
rtPTransitions } ;
