#include "stdafx.h"
#include "MASTER.h"
 #define ___884
#include "GLOBAL.h"
#include "TASSERT.h"
#include "ALLOC.h"
#include "ARRLIST.h"
#include "DATASET.h"
#include "SET.h"
#include "FILESTREAM.h"
#include "Q_MSG.h"
#include "DATASET0.h"
using namespace tecplot; void ___2889(void) { ___1177(___4217("Cannot allocate enough memory for this operation.")); }
 #if !defined TECPLOTKERNEL
namespace {
 #endif
___1361 ___1354(___372 ___1102) { ___1361 ___3359 = NULL; try { ___3359 = new ___1362; { ___3359->___816             = NULL; ___3359->___1781 = NULL; ___3359->___3506 = NULL; ___3359->isOrderedData    = ___1305; ___3359->___4335        = ___1369; ___3359->___4327    = ___4329; ___3359->iDim             = 0; ___3359->jDim             = 0; ___3359->kDim             = 0; } } catch (std::bad_alloc const&) { ENSURE(___3359 == NULL); } ENSURE(VALID_REF(___3359) || ___3359 == NULL); return ___3359; }
 #if !defined TECPLOTKERNEL
}
 #endif
namespace { void FieldDataDeallocRawData(___1361 ___1351) { REQUIRE(VALID_REF(___1351)); if (___1720(___1351) != NULL) { char* Tmp = static_cast<char*>(___1720(___1351)); ___1530(Tmp, "FieldData _Data"); ___3487(___1351, NULL); } } } void ___1358(___1361 ___1352) { REQUIRE(VALID_REF(___1352)); { FieldDataDeallocRawData(___1352); } ENSURE(___1720(___1352) == NULL); } void ___1356(___1361 ___1352) { REQUIRE(VALID_REF(___1352)); { ___1358(___1352); } } void ___1357(___1361 *___1352, ___372     ___1103) { REQUIRE(VALID_REF(___1352)); REQUIRE(VALID_REF(*___1352) || *___1352 == NULL); if (*___1352 != NULL) { { ___1356(*___1352); delete *___1352; } *___1352 = NULL; } ENSURE(*___1352 == NULL); } template <typename T> static void copyTypedValueArray(void*       ___1122, ___2227   ___1127, void const* ___3657, ___2227   ___3665, ___2227   ___3659) { REQUIRE(VALID_REF(___1122)); REQUIRE(___1127 >= 0); REQUIRE(VALID_REF(___3657)); REQUIRE(0 <= ___3665 && ___3665 <= ___3659+1); REQUIRE(___1122 != ___3657); size_t const ___2779 = sizeof(T) * (___3659 - ___3665 + 1); if (___2779 != 0) { T const* SrcPtr = ((T const*)___3657) + ___3665; T* DstPtr       = ((T*)___1122) + ___1127; if (DstPtr && SrcPtr) memcpy(DstPtr, SrcPtr, ___2779); } } void ___679( FieldDataType_e ___4335, void*           ___1122, ___2227       ___1127, void const*     ___3657, ___2227       ___3665, ___2227       ___3659) { REQUIRE(VALID_FIELD_DATA_TYPE(___4335) && ___4335 != ___1365); REQUIRE(VALID_REF(___1122)); REQUIRE(___1127 >= 0); REQUIRE(VALID_REF(___3657)); REQUIRE(0 <= ___3665 && ___3665 <= ___3659+1); REQUIRE(___1122 != ___3657); switch (___4335) { case ___1368 : ___478(___1305); case FieldDataType_Double : { ___478(sizeof(uint64_t) == 8 && sizeof(double) == 8); copyTypedValueArray<uint64_t>(___1122, ___1127, ___3657, ___3665, ___3659); } break; case FieldDataType_Float : case FieldDataType_Int32 : { ___478(sizeof(uint32_t) == 4 && sizeof(float) == 4); copyTypedValueArray<uint32_t>(___1122, ___1127, ___3657, ___3665, ___3659); } break; case FieldDataType_Int16 : { ___478(sizeof(uint16_t) == 2); copyTypedValueArray<uint16_t>(___1122, ___1127, ___3657, ___3665, ___3659); } break; case FieldDataType_Byte : { copyTypedValueArray<uint8_t>(___1122, ___1127, ___3657, ___3665, ___3659); } break; default : ___478(___1305); } } void ___3911(FieldDataType_e  ___4335, void            *___3657, ___2227        ___3665, ___2227        ___3659, ___2227        ___3664) { REQUIRE(VALID_FIELD_DATA_TYPE(___4335) && ___4335 != ___1365); REQUIRE(VALID_REF(___3657)); REQUIRE(0 <= ___3665 && ___3665 <= ___3659); REQUIRE(___3664 > 0); switch (___4335) { case ___1368: ___478(___1305); case FieldDataType_Double: { uint64_t *SrcPtr = ((uint64_t *)___3657) + ___3665; uint64_t *SrcPtrEnd = ((uint64_t *)___3657) + ___3659; ___478(sizeof(uint64_t) == 8 && sizeof(double) == 8); while (SrcPtr <= SrcPtrEnd) { ___3370(SrcPtr); SrcPtr += ___3664; } } break; case FieldDataType_Float: case FieldDataType_Int32: { uint32_t *SrcPtr = ((uint32_t *)___3657) + ___3665; uint32_t *SrcPtrEnd = ((uint32_t *)___3657) + ___3659; ___478(sizeof(uint32_t) == 4 && sizeof(float) == 4); while (SrcPtr <= SrcPtrEnd) { ___3367(SrcPtr); SrcPtr += ___3664; } } break; case FieldDataType_Int16: { uint16_t *SrcPtr = ((uint16_t *)___3657) + ___3665; uint16_t *SrcPtrEnd = ((uint16_t *)___3657) + ___3659; ___478(sizeof(uint16_t) == 2); while (SrcPtr <= SrcPtrEnd) { ___3364(SrcPtr); SrcPtr += ___3664; } } break; case FieldDataType_Byte: case ___1365: { } break; default: ___478(___1305); } } void ___3912(FieldDataType_e  ___4335, void            *___3657, ___2227        ___3665, ___2227        ___3659, ___2227        ___3664) { REQUIRE(VALID_FIELD_DATA_TYPE(___4335) && ___4335 != ___1365); REQUIRE(VALID_REF(___3657)); REQUIRE(0 <= ___3665 && ___3665 <= ___3659); REQUIRE(___3664 > 0); switch (___4335) { case ___1368: ___478(___1305); case FieldDataType_Double: { uint8_t *SrcPtr = ((uint8_t *)___3657) + ___3665 * sizeof(uint64_t); uint8_t *SrcPtrEnd = ((uint8_t *)___3657) + ___3659 * sizeof(uint64_t); size_t byte_skip = ___3664 * sizeof(uint64_t); ___478(sizeof(uint64_t) == 8 && sizeof(double) == 8); while (SrcPtr <= SrcPtrEnd) { ___3371(SrcPtr); SrcPtr += byte_skip; } } break; case FieldDataType_Float: case FieldDataType_Int32: { uint8_t *SrcPtr = ((uint8_t *)___3657) + ___3665 * sizeof(uint32_t); uint8_t *SrcPtrEnd = ((uint8_t *)___3657) + ___3659 * sizeof(uint32_t); size_t byte_skip = ___3664 * sizeof(uint32_t); ___478(sizeof(uint32_t) == 4 && sizeof(float) == 4); while (SrcPtr <= SrcPtrEnd)
{ ___3368(SrcPtr); SrcPtr += byte_skip; } } break; case FieldDataType_Int16: { uint8_t *SrcPtr = ((uint8_t *)___3657) + ___3665 * sizeof(uint16_t); uint8_t *SrcPtrEnd = ((uint8_t *)___3657) + ___3659 * sizeof(uint16_t); size_t byte_skip = ___3664 * sizeof(uint16_t); ___478(sizeof(uint16_t) == 2); while (SrcPtr <= SrcPtrEnd) { ___3365(SrcPtr); SrcPtr += byte_skip; } } break; case FieldDataType_Byte: case ___1365: { } break; default: ___478(___1305); } }
 #define DEBUG_FIELDVALUES_BAD_VALUE 0x11
 #if !defined NO_ASSERTS
template <typename T> inline bool IsFieldDataValueInitialized( ___1361 ___1308, ___2227    ___3249) {
 #if defined DEBUG_FIELDVALUES
static unsigned char BadValueStr[] = { DEBUG_FIELDVALUES_BAD_VALUE, DEBUG_FIELDVALUES_BAD_VALUE, DEBUG_FIELDVALUES_BAD_VALUE, DEBUG_FIELDVALUES_BAD_VALUE, DEBUG_FIELDVALUES_BAD_VALUE, DEBUG_FIELDVALUES_BAD_VALUE, DEBUG_FIELDVALUES_BAD_VALUE, DEBUG_FIELDVALUES_BAD_VALUE }; ___478(sizeof(T) <= sizeof(BadValueStr)); ___4278(___3249); return ((sizeof(T) < 4)   || \ memcmp(BadValueStr,((char*)___1720(___1308))+sizeof(T)*(___3249), sizeof(T)) != 0);
 #else
___4278(___1308); ___4278(___3249); return true;
 #endif
}
 #endif
double STDCALL ___1742(const ___1361 ___1308, ___2227          ___3249) { REQUIRE(VALID_REF(___1308)); REQUIRE(0 <= ___3249 && ___3249 < ___1717(___1308)); REQUIRE(IsFieldDataValueInitialized<float>(___1308, ___3249)); double ___3359 = (double)___1690(___1308)[___3249]; return ___3359; } double STDCALL ___1741(const ___1361 ___1308, ___2227          ___3249) { REQUIRE(VALID_REF(___1308)); REQUIRE(0 <= ___3249 && ___3249 < ___1717(___1308)); REQUIRE(IsFieldDataValueInitialized<double>(___1308, ___3249)); double ___3359 = ___1684(___1308)[___3249]; return ___3359; } double STDCALL ___1744(const ___1361 ___1308, ___2227          ___3249) { REQUIRE(VALID_REF(___1308)); REQUIRE(0 <= ___3249 && ___3249 < ___1717(___1308)); REQUIRE(IsFieldDataValueInitialized<int32_t>(___1308, ___3249)); double ___3359 = (double)___1705(___1308)[___3249]; return ___3359; } double STDCALL ___1743(const ___1361 ___1308, ___2227          ___3249) { REQUIRE(VALID_REF(___1308)); REQUIRE(0 <= ___3249 && ___3249 < ___1717(___1308)); REQUIRE(IsFieldDataValueInitialized<int16_t>(___1308, ___3249)); double ___3359 = (double)___1699(___1308)[___3249]; return ___3359; } double STDCALL ___1740(const ___1361 ___1308, ___2227          ___3249) { REQUIRE(VALID_REF(___1308)); REQUIRE(___1726(___1308) == FieldDataType_Byte); REQUIRE(0 <= ___3249 && ___3249 < ___1717(___1308)); REQUIRE(IsFieldDataValueInitialized<uint8_t>(___1308, ___3249)); double ___3359 = (double)___1681(___1308)[___3249]; return ___3359; } double STDCALL ___1739(const ___1361 ___1308, ___2227          ___3249) { REQUIRE(VALID_REF(___1308)); REQUIRE(___1726(___1308) == ___1365); REQUIRE(0 <= ___3249 && ___3249 < ___1717(___1308)); REQUIRE(IsFieldDataValueInitialized<uint8_t>(___1308, ___3249 / 8)); ___2227 ByteOffset = ___3249 / 8; uint8_t    BitMask    = (01 << (___3249 % 8)); uint8_t *byte_array = ___1681(___1308); double ___3359 = (byte_array[ByteOffset] & BitMask) ? 1.0 : 0.0; return ___3359; } ___1383 DetermineFieldDataGetFunction(___1361 ___1351) { REQUIRE(VALID_REF(___1351)); ___1383 ___3359 = NULL; switch (___1726(___1351)) { case FieldDataType_Float:  ___3359 = ___1742;  break; case FieldDataType_Double: ___3359 = ___1741; break; case FieldDataType_Int32:  ___3359 = ___1744;  break; case FieldDataType_Int16:  ___3359 = ___1743;  break; case FieldDataType_Byte:   ___3359 = ___1740;   break; case ___1365:    ___3359 = ___1739;    break; default: ___478(___1305); break; } return ___3359; } static void STDCALL SetFieldValueForFloat(___1361 ___1308, ___2227    ___3249, double       ___4298) { REQUIRE(VALID_REF(___1308)); REQUIRE(0 <= ___3249 && ___3249 < ___1717(___1308)); REQUIRE("val can have any value"); ___1690(___1308)[___3249] = ___650(___4298); ENSURE(IsFieldDataValueInitialized<float>(___1308, ___3249)); } static void STDCALL SetFieldValueForDouble(___1361 ___1308, ___2227    ___3249, double       ___4298) { REQUIRE(VALID_REF(___1308)); REQUIRE(0 <= ___3249 && ___3249 < ___1717(___1308)); REQUIRE("val can have any value"); ___1684(___1308)[___3249] = ___489(___4298); ENSURE(IsFieldDataValueInitialized<double>(___1308, ___3249)); } static void STDCALL SetFieldValueForInt32(___1361 ___1308, ___2227    ___3249, double       ___4298) { REQUIRE(VALID_REF(___1308)); REQUIRE(0 <= ___3249 && ___3249 < ___1717(___1308)); REQUIRE("val can have any value"); ___1705(___1308)[___3249] = ___652(___4298); ENSURE(IsFieldDataValueInitialized<int32_t>(___1308, ___3249)); } static void STDCALL SetFieldValueForInt16(___1361 ___1308, ___2227    ___3249, double       ___4298) { REQUIRE(VALID_REF(___1308)); REQUIRE(0 <= ___3249 && ___3249 < ___1717(___1308)); REQUIRE("val can have any value"); ___1699(___1308)[___3249] = ___651(___4298); ENSURE(IsFieldDataValueInitialized<int16_t>(___1308, ___3249)); } static void STDCALL SetFieldValueForByte(___1361 ___1308, ___2227    ___3249, double       ___4298) { REQUIRE(VALID_REF(___1308)); REQUIRE(___1726(___1308) == FieldDataType_Byte); REQUIRE(0 <= ___3249 && ___3249 < ___1717(___1308)); REQUIRE("val can have any value"); ___1681(___1308)[___3249] = CONVERT_DOUBLE_TO_UINT8(___4298); ENSURE(IsFieldDataValueInitialized<uint8_t>(___1308, ___3249)); } static void STDCALL SetFieldValueForBit(___1361 ___1308, ___2227    ___3249, double       ___4298) { REQUIRE(VALID_REF(___1308)); REQUIRE(___1726(___1308) == ___1365); REQUIRE(0 <= ___3249 && ___3249 < ___1717(___1308)); REQUIRE("val can have any value"); ___2227 ByteOffset = ___3249 / 8; uint8_t   BitMask    = (01 << (___3249 % 8)); if (___4298 < 1.0) ___1681(___1308)[ByteOffset] &= ~BitMask; else ___1681(___1308)[ByteOffset] |= BitMask; ENSURE(IsFieldDataValueInitialized<uint8_t>(___1308, ___3249 / 8)); } ___1384 DetermineFieldDataSetFunction(___1361 ___1351) { REQUIRE(VALID_REF(___1351)); ___1384 ___3359 = NULL; switch (___1726(___1351)) { case FieldDataType_Float:  ___3359 = SetFieldValueForFloat;  break;
case FieldDataType_Double: ___3359 = SetFieldValueForDouble; break; case FieldDataType_Int32:  ___3359 = SetFieldValueForInt32;  break; case FieldDataType_Int16:  ___3359 = SetFieldValueForInt16;  break; case FieldDataType_Byte:   ___3359 = SetFieldValueForByte;   break; case ___1365:    ___3359 = SetFieldValueForBit;    break; default: ___478(___1305); break; } return ___3359; }
 #if !defined TECPLOTKERNEL
namespace {
 #endif
int64_t ___1359(___2227       ___2842, FieldDataType_e ___907) { int64_t ___3359 = 0; REQUIRE(___2842 >= 0); REQUIRE(VALID_FIELD_DATA_TYPE(___907)); switch (___907) { case FieldDataType_Float:  ___3359 = ((int64_t)___2842)*sizeof(float);         break; case FieldDataType_Double: ___3359 = ((int64_t)___2842)*sizeof(double);        break; case FieldDataType_Int32:  ___3359 = ((int64_t)___2842)*sizeof(int32_t);       break; case FieldDataType_Int16:  ___3359 = ((int64_t)___2842)*sizeof(int16_t);       break; case FieldDataType_Byte:   ___3359 = ((int64_t)___2842)*sizeof(uint8_t);       break; case ___1365:    ___3359 = ((int64_t)(___2842+7)/8)*sizeof(uint8_t); break; default: ___478(___1305); break; } ENSURE(___3359 >= 0); return ___3359; }
 #if !defined TECPLOTKERNEL
}
 #endif
 #if defined ___1995 || defined HPUX || defined ___3893
 # define SIZEOF_LARGEST_OBJECT_TO_ALIGN sizeof(int64_t)
 #else
 # define SIZEOF_LARGEST_OBJECT_TO_ALIGN sizeof(int32_t)
 #endif
void FieldDataReinitializeMetaData( ___1361    ___1351, ___372       isOrderedData, ___2227       iDim, ___2227       jDim, ___2227       kDim, FieldDataType_e dataType, ValueLocation_e ___4326, ___372       isReadOnly, ___372       ___2064) { REQUIRE(VALID_REF(___1351)); REQUIRE(VALID_BOOLEAN(isOrderedData)); REQUIRE(IMPLICATION(isOrderedData, iDim >= 0 && jDim >= 0 && kDim >= 0)); REQUIRE(IMPLICATION(!isOrderedData && ___4326 == ___4330, (iDim == 0 && jDim == 0 && kDim == 0) || (iDim >= 0 && jDim == 1 && kDim == 1))); REQUIRE(IMPLICATION(!isOrderedData && ___4326 == ___4328, (iDim == 0 && jDim == 0 && kDim == 0) || (jDim >= 0 && iDim == 1 && kDim == 1))); REQUIRE(VALID_FIELD_DATA_TYPE(dataType)); REQUIRE(VALID_ENUM(___4326, ValueLocation_e)); REQUIRE(VALID_BOOLEAN(isReadOnly)); REQUIRE(VALID_BOOLEAN(___2064)); REQUIRE(IMPLICATION(___2064, isReadOnly)); ___1356(___1351); ___1351->isOrderedData = isOrderedData; ___1351->___4335     = dataType; ___1351->___4327 = ___4326; ___1351->iDim = iDim; ___1351->jDim = jDim; ___1351->kDim = kDim; { ___1351->___1781 = DetermineFieldDataGetFunction(___1351); ___1351->___3506 = DetermineFieldDataSetFunction(___1351); } ENSURE(___1720(___1351) == NULL); }
 #if !defined TECPLOTKERNEL
namespace {
 #endif
___372 ___2315( ___1361 ___1352, ___372    ___3571) { REQUIRE(VALID_REF(___1352)); REQUIRE(___1726(___1352) != ___1369); REQUIRE(___1720(___1352) == NULL); REQUIRE(VALID_BOOLEAN(___3571)); int64_t ActualBytesNeeded = ___1359(___1717(___1352), ___1726(___1352)); size_t  BytesToAllocate   = (size_t)ActualBytesNeeded; ___478(sizeof(size_t) == 4 || sizeof(size_t) == 8); ___372 ___2040 = (___1717(___1352) <= ___2373 && IMPLICATION(sizeof(size_t) == 4, ActualBytesNeeded <= (int64_t)0xffffffff)); if (___2040) { if (___1717(___1352) > 0) { ___3487(___1352, (void*)___23(BytesToAllocate, char, "FieldData's Data"));
 #if defined DEBUG_FIELDVALUES
{ if (___1720(___1352) != NULL) memset(___1720(___1352), DEBUG_FIELDVALUES_BAD_VALUE, BytesToAllocate); }
 #endif
if (___1726(___1352) == ___1365 && ___1720(___1352) != NULL) ((char*)___1720(___1352))[BytesToAllocate-1] = '\0'; } ___2040 = (___1717(___1352) == 0 || ___1720(___1352) != NULL); if (!___2040 && ___3571) ___2889(); } else if (___3571) { ___1177(___4217("Storage limit (%ld) exceeded for a single variable."), (ldfmt_t)___2373); } ENSURE(VALID_REF(___1720(___1352)) || ___1720(___1352) == NULL); ENSURE(VALID_BOOLEAN(___2040)); return ___2040; }
 #if !defined TECPLOTKERNEL
}
 #endif
___372 ___1355( ___1361 ___1352, ___372    ___3571) { REQUIRE(VALID_REF(___1352)); REQUIRE(___1726(___1352) != ___1369); REQUIRE(___1720(___1352) == NULL); REQUIRE(VALID_BOOLEAN(___3571)); ___372 ___2039 = ___2315(___1352, ___3571); ENSURE(VALID_REF(___1720(___1352)) || ___1720(___1352) == NULL); ENSURE(VALID_BOOLEAN(___2039)); return ___2039; }
 #if !defined NO_ASSERTS
 #endif
___1361 ___28(___2227       ___2842, FieldDataType_e ___4236, ___372       ___3571) { REQUIRE(___2842 >= 0); REQUIRE(VALID_FIELD_DATA_TYPE(___4236)); REQUIRE(VALID_BOOLEAN(___3571)); ___1361 ___3359 = ___1354(___1305); if (___3359 != NULL) { ___372 const isReadOnly = ___1305; ___372 const ___2064  = ___1305; FieldDataReinitializeMetaData(___3359, ___4226, ___2842,1,1, ___4236, ___4330, isReadOnly, ___2064); if (!___1355(___3359, ___3571)) ___1357(&___3359, ___1305); } else if (___3571) { ___2889(); } ENSURE(VALID_REF(___3359) || ___3359 == NULL); ENSURE(IMPLICATION(___3359 != NULL, (___1717(___3359) >= 0                     && IMPLICATION(___1717(___3359) != 0, VALID_REF(___1720(___3359))) && VALID_FIELD_DATA_TYPE(___1726(___3359))))); return ___3359; } void ___938(___1361 *FieldDataRef) { ___1357(FieldDataRef, ___1305); }
 #if 0 
 #endif
void ___675(___1361  ___1121, ___2227     ___1124, ___1361  ___3656, ___2227     ___3661) { REQUIRE(VALID_REF(___1121)); REQUIRE(VALID_REF(___3656)); REQUIRE(___1124 >= 0 && ___1124 < ___1717(___1121) && ___3661 >= 0 && ___3661 < ___1717(___3656)); ___372 DoBruteForceCopy = ___4226; if (___2019(___3656) && ___2019(___1121) && ___1726(___3656) == ___1726(___1121)) { switch (___1726(___3656)) { case ___1368 : ___478(___1305); case FieldDataType_Double : { ___478(sizeof(uint64_t) == 8 && sizeof(double) == 8); uint64_t *dst_ptr = ___1678(___1121) + ___1124; uint64_t *src_ptr = ___1678(___3656) + ___3661; *dst_ptr = *src_ptr; DoBruteForceCopy = ___1305; } break; case FieldDataType_Float : case FieldDataType_Int32 : { ___478(sizeof(uint32_t) == 4 && sizeof(float) == 4); uint32_t *dst_ptr = ___1675(___1121) + ___1124; uint32_t *src_ptr = ___1675(___3656) + ___3661; *dst_ptr = *src_ptr; DoBruteForceCopy = ___1305; } break; case FieldDataType_Int16 : { ___478(sizeof(uint16_t) == 2); uint16_t *dst_ptr = ___1672(___1121) + ___1124; uint16_t *src_ptr = ___1672(___3656) + ___3661; *dst_ptr = *src_ptr; } break; case FieldDataType_Byte : { ___1681(___1121)[___1124] = ___1681(___3656)[___3661]; DoBruteForceCopy = ___1305; } break; case ___1365 : break; default : ___478(___1305); } } if (DoBruteForceCopy) { ___3490(___1121, ___1124, ___1735(___3656, ___3661)); } } void SetFieldDataArrayBytesToZero(___1361 ___1308) { REQUIRE(VALID_REF(___1308)); ___2227 NumBytesToMemSet = 0; ___2227 const ___2842 = ___1717(___1308); switch (___1726(___1308)) { case ___1368 : ___478(___1305); case FieldDataType_Double : { ___478(sizeof(uint64_t) == 8 && sizeof(double) == 8); NumBytesToMemSet = ___2842 * static_cast<___2227>(sizeof(int64_t)); } break; case FieldDataType_Int32 : case FieldDataType_Float : { ___478(sizeof(uint32_t) == 4 && sizeof(float) == 4); NumBytesToMemSet = ___2842 * static_cast<___2227>(sizeof(int32_t)); } break; case FieldDataType_Int16 : { ___478(sizeof(uint16_t) == 2); NumBytesToMemSet = ___2842 * static_cast<___2227>(sizeof(int16_t)); } break; case FieldDataType_Byte : { NumBytesToMemSet = ___2842 * static_cast<___2227>(sizeof(uint8_t)); } break; case ___1365 : { NumBytesToMemSet = ((___2842 + 7) / 8) * static_cast<___2227>(sizeof(uint8_t)); } break; default : { ___478(___1305); } break; } memset((char*)___1732(___1308), 0, NumBytesToMemSet); } void ___3486(___1361 ___1308) { REQUIRE(VALID_REF(___1308)); if (___2019(___1308)) { SetFieldDataArrayBytesToZero(___1308); } else { ___2227 const ___2842 = ___1717(___1308); for (___2227 ___1841 = 0; ___1841 < ___2842; ___1841++) ___3490(___1308, ___1841, 0.0); } }
