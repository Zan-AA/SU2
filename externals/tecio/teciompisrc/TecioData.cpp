#include "TecioData.h"
#include "ThirdPartyHeadersBegin.h"
#include <sstream>
#include <boost/assign.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/foreach.hpp>
#include <boost/make_shared.hpp>
#include "ThirdPartyHeadersEnd.h"
#include "MASTER.h"
#include "GLOBAL.h"
#include "FieldData_s.h"
using namespace tecplot::___3933; struct ___1293 { }; namespace tecplot { namespace tecioszl { ___3970::___3970() {} ___3970::___3970( std::string const& ___4177, std::string const& ___4350, int32_t            defaultVarType) : ___2649(___4177) , m_defaultVarType(defaultVarType) , m_nextZoneIndex(0) , m_lastZoneFlushedToDisk(-1) , ___2399(new AuxData_s) { if (!VALID_ENUM((FieldDataType_e)defaultVarType, FieldDataType_e)) { std::ostringstream ___2892; ___2892 << "Invalid default variable type: " << defaultVarType; throw std::runtime_error(___2892.str()); } char const* ___3475; if (___4350.find_first_of('\n') != std::string::npos) ___3475 = "\n"; else if (___4350.find_first_of(',') != std::string::npos) ___3475 = ","; else ___3475 = " "; std::string trimmedVariables(___4350); boost::trim_if(trimmedVariables, boost::is_any_of(___3475)); boost::split(___2674, trimmedVariables, boost::is_any_of(___3475), boost::token_compress_on); BOOST_FOREACH(std::string& ___2685, ___2674) { boost::trim(___2685); ___2672.push_back(boost::make_shared<AuxData_s>()); } } ___3970::~___3970() { } void ___3970::___19( char    const* ___4690, int32_t const  ___4692, int64_t const  ___1909, int64_t const  ___2116, int64_t const  ___2161, double  const  ___3640, int32_t const  ___3785, int32_t const  ___2974, int64_t const  ___2802, int32_t const  ___1284, int64_t const  ___4192, int64_t const  ___2786, int64_t const  ___4188, int32_t const* varTypes, int32_t const* ___2982, int32_t const* ___4326, int32_t const* ___3551, int32_t const  ___3549) { REQUIRE(VALID_REF(___4690) && strlen(___4690) > 0); REQUIRE(0 <= ___4692 && ___4692 < 8); REQUIRE(0 < ___1909); REQUIRE(0 < ___2116); REQUIRE(IMPLICATION(___4692 == 0 || ___4692 == 6 || ___4692 == 7, 0 < ___2161)); REQUIRE(0 <= ___3785); REQUIRE(0 <= ___2974); REQUIRE(0 <= ___2802); REQUIRE(IMPLICATION(___4692 < 6, 0 <= ___1284 && ___1284 < 4)); REQUIRE(0 <= ___4192); REQUIRE(0 <= ___2786); REQUIRE(0 <= ___4188); REQUIRE(VALID_REF_OR_NULL(varTypes)); REQUIRE(VALID_REF_OR_NULL(___2982)); REQUIRE(VALID_REF_OR_NULL(___4326)); REQUIRE(VALID_REF_OR_NULL(___3551)); REQUIRE(0 <= ___3549); ZoneType_e tecplotZoneTypes[] = { ___4704, ___4696, ___4702, ___4700, ___4701, ___4695, ___4698, ___4699 }; REQUIRE(0 <= ___4692 && ___4692 < (int)(sizeof(tecplotZoneTypes) / sizeof(tecplotZoneTypes[0]))); ZoneType_e tecplotZoneType = tecplotZoneTypes[___4692]; if (tecplotZoneType == ___4698 || tecplotZoneType == ___4699) throw Error("Polygon and Polyhedral zone types are currently not supported by SZL files."); if (___3549 > 0 && m_zoneMap.find(static_cast<___4636>(___3549 - 1)) == m_zoneMap.end()) { try { std::ostringstream ostream; ostream << "Invalid zone specified for nodemap sharing.\n" "Specified non-existent zone " << ___3549 << "."; throw Error(ostream.str()); } catch (std::bad_alloc const&) { std::cerr << "Out of memory while attempting to report:" << std::endl << "Invalid zone specified for nodemap sharing." << std::endl << "Specified non-existent zone " << ___3549 << "." << std::endl; throw; } } std::vector<FieldDataType_e> fieldDataTypeVector; try { if (varTypes) { std::map<int32_t, FieldDataType_e> varTypeMap = boost::assign::map_list_of (1, FieldDataType_Float) (2, FieldDataType_Double) (3, FieldDataType_Int32) (4, FieldDataType_Int16) (5, FieldDataType_Byte); for (size_t i = 0; i < ___2674.size(); ++i) { if (varTypeMap.find(varTypes[i]) == varTypeMap.end()) { std::ostringstream ___2892; ___2892 << "Invalid variable type for variable " << i + 1 << ": " << varTypes[i]; throw Error(___2892.str()); } fieldDataTypeVector.push_back(varTypeMap[varTypes[i]]); } } else { fieldDataTypeVector.assign(___2674.size(), (FieldDataType_e)m_defaultVarType); } } catch (std::bad_alloc const&) { std::cerr << "Out-of-memory error while processing " << ___2674.size() << " zone variable types." << std::endl; throw; } std::vector<int> passiveVarVector; try { for(size_t ___4291 = 0; ___4291 < ___2674.size(); ++___4291) { if (___2982 && ___2982[___4291] != 0) passiveVarVector.push_back(1); else passiveVarVector.push_back(0); } } catch (std::bad_alloc const&) { std::cerr << "Out-of-memory error while processing " << ___2674.size() << " zone passive variables." << std::endl; throw; } std::vector<ValueLocation_e> valueLocationVector; try { for(size_t ___4291 = 0; ___4291 < ___2674.size(); ++___4291) { if (___4326) valueLocationVector.push_back(static_cast<ValueLocation_e>(___4326[___4291]));
else valueLocationVector.push_back(___4330); } } catch (std::bad_alloc const&) { std::cerr << "Out-of-memory error while processing " << ___2674.size() << " zone variable locations." << std::endl; throw; } std::vector<int> shareVarFromZoneVector; try { for(size_t ___4291 = 0; ___4291 < ___2674.size(); ++___4291) { if (___3551 && ___3551[___4291] != 0) { if (m_zoneMap.find(static_cast<___4636>(___3551[___4291] - 1)) == m_zoneMap.end()) { try { std::ostringstream ostream; ostream << "Invalid zone specified for variable sharing.\n" "Specified non-existent zone " << ___3551[___4291] << " for variable " << ___4291 << "."; throw Error(ostream.str()); } catch (std::bad_alloc const&) { std::cerr << "Out of memory while attempting to report:" << std::endl << "Invalid zone specified for variable sharing." << std::endl << "Specified non-existent zone " << ___3551[___4291] << " for variable " << ___4291 << "." << std::endl; throw; } } else { shareVarFromZoneVector.push_back(___3551[___4291]); } } else { shareVarFromZoneVector.push_back(0); } } } catch (std::bad_alloc const&) { std::cerr << "Out-of-memory error while processing " << ___2674.size() << " zone variable sharing settings." << std::endl; throw; } size_t titleLength = strlen(___4690); if (titleLength > (size_t)___2358) { titleLength = ___2358; std::cerr << "Warning: Zone title too long, truncating to " << titleLength << " chars." << std::endl; } std::string zoneTitleString; try { zoneTitleString.assign(___4690, titleLength); } catch(std::bad_alloc const&) { std::cerr << "Out of memory while processing zone title string." << std::endl; throw; } Zone_s* zone = NULL; try { zone = new Zone_s( *this, zoneTitleString, tecplotZoneType, 1, 1, 1, ___1909, ___2116, ___2161, ___3640, ___3785, static_cast<___1172>(___2974), ___2802, static_cast<FaceNeighborMode_e>(___1284), ___4192, ___2786, ___4188, fieldDataTypeVector, passiveVarVector, valueLocationVector, shareVarFromZoneVector, ___3549); } catch (std::bad_alloc const&) { std::cerr << "Out-of-memory error while creating container to store zone settings." << std::endl; throw; } try { m_zoneMap[m_nextZoneIndex] = boost::shared_ptr<Zone_s>(zone); } catch (std::bad_alloc const&) { std::cerr << "Out-of-memory error while storing zone settings." << std::endl; throw; } ++m_nextZoneIndex; } void ___3970::renumberLastZone(int32_t zoneNumber) { INVARIANT(IMPLICATION(!m_zoneMap.empty(), m_nextZoneIndex > 0)); REQUIRE(!m_zoneMap.empty()); REQUIRE(zoneNumber > m_nextZoneIndex); ___4636 currentZoneIndex = m_nextZoneIndex - 1; ___478(m_zoneMap.rbegin()->first == currentZoneIndex); ___4636 desiredZoneIndex = (___4636)(zoneNumber - 1); m_zoneMap[desiredZoneIndex] = m_zoneMap[currentZoneIndex]; m_zoneMap.erase(currentZoneIndex); m_nextZoneIndex = desiredZoneIndex + 1; } void ___3970::setPartitionOwners(std::vector<int> const& partitionOwners) { if (!m_zoneMap.rbegin()->second->m_partitionOwners.empty()) throw Error("Must be called only once, by only the main process, immediately after TECZNE."); m_zoneMap.rbegin()->second->m_partitionOwners = partitionOwners; } Zone_s* ___3970::getAndCheckZonePtr(int32_t zone) const { Zone_s::ZoneMap::const_iterator iter = m_zoneMap.find(static_cast<___4636>(zone - 1)); if (iter == m_zoneMap.end()) { std::ostringstream ___2892; ___2892 << "Specified non-existent zone " << zone << "."; throw Error(___2892.str()); } Zone_s* zonePtr = iter->second.get(); for (size_t i = 0; i < zonePtr->___2496.size(); ++i) { if (zonePtr->___2496[i]->storedValueCount() != 0) { std::ostringstream ___2892; ___2892 << "Called out-of-order (after caching data to the zone) for zone " << zone << "." << std::endl; ___2892 << "If the zone is partitioned, you must add a partition before calling TECDAT or TECNOD."; throw Error(___2892.str()); } } return zonePtr; } template <typename T> void ___3970::addFEZonePartition( int32_t                     zone, int32_t                     ___2977, int64_t                     ___2821, int64_t                     ___2781, std::vector<T>       const& gnodes, std::vector<int32_t> const& gnpartitions, std::vector<T>       const& gnpnodes, std::vector<T>       const& gcells) { Zone_s* zonePtr = getAndCheckZonePtr(zone); ___4636 numPartitionsMPI = static_cast<___4636>(zonePtr->m_partitionOwners.size()); for(size_t i = 0; i < gnodes.size(); ++i) { if (gnodes[i] < 1 || ___2821 < gnodes[i]) { std::ostringstream ___2892; ___2892 << "Invalid ghost node (" << gnodes[i] << ") at position " << i + 1 << " in the ghost node list for partition " << ___2977 << " of zone " << zone << "." << std::endl; throw Error(___2892.str()); } if (gnpartitions[i] < 1 || (numPartitionsMPI > 0 && numPartitionsMPI < gnpartitions[i])) { std::ostringstream ___2892;
___2892 << "Invalid ghost node partition (" << gnpartitions[i] << ") at position " << i + 1 << " in the ghost node partition list for partition " << ___2977 << " of zone " << zone << "." << std::endl; throw Error(___2892.str()); } if (gnpnodes[i] < 1) { std::ostringstream ___2892; ___2892 << "Invalid ghost node partition node (" << gnpnodes[i] << ") at position " << i + 1 << " in the ghost node partition node list for partition " << ___2977 << " of zone " << zone << "." << std::endl; throw Error(___2892.str()); } } for(size_t i = 0; i < gcells.size(); ++i) if (gcells[i] < 1 || ___2781 < gcells[i]) { std::ostringstream ___2892; ___2892 << "Invalid ghost cell (" << gcells[i] << ") at position " << i + 1 << " in the ghost cell list for partition " << ___2977 << " of zone " << zone << "." << std::endl; throw Error(___2892.str()); } boost::shared_ptr<Zone_s> newPartition = boost::make_shared<Zone_s>(*this, zonePtr, 1, 1, 1, ___2821, ___2781, zonePtr->___2682.___1669()); for (size_t i = 0; i < zonePtr->m_shareVarFromZone.size(); ++i) { ___1172 shareZone = zonePtr->m_shareVarFromZone[i]; if (shareZone) { Zone_s* shareZonePtr = getAndCheckZonePtr(shareZone); if (shareZonePtr->m_partitionMap.empty() || shareZonePtr->m_partitionMap.find(___2977 - 1) == shareZonePtr->m_partitionMap.end()) { std::ostringstream ___2892; ___2892 << "Error in var share list for zone " << zone << " partition " << ___2977 << ": var " << i + 1 << " attempting to share with incompatible zone " << shareZone << "." << std::endl; throw Error(___2892.str()); } newPartition->___2496[i]  = shareZonePtr->m_partitionMap[___2977 - 1]->___2496[i]; newPartition->___2400[i] = shareZonePtr->m_partitionMap[___2977 - 1]->___2400[i]; } } if (zonePtr->m_shareConnectivityFromZone) { Zone_s* shareZonePtr = getAndCheckZonePtr(zonePtr->m_shareConnectivityFromZone); if (shareZonePtr->m_partitionMap.empty() || shareZonePtr->m_partitionMap.find(___2977 - 1) == shareZonePtr->m_partitionMap.end()) { std::ostringstream ___2892; ___2892 << "Error in sharing connectivity for zone " << zone << " partition " << ___2977 << ": attempting to share with incompatible zone " << zonePtr->m_shareConnectivityFromZone << "." << std::endl; throw Error(___2892.str()); } newPartition->___2497 = shareZonePtr->m_partitionMap[___2977 - 1]->___2497; } try { newPartition->m_ghostNodeInfo = GhostInfo_s(gnodes, gnpartitions, gnpnodes); } catch(std::exception const& e) { std::ostringstream ___2892; ___2892 << "Error in ghost node list for zone " << zone << " partition " << ___2977 << ": " << e.what(); throw Error(___2892.str()); } try { newPartition->m_ghostCellInfo = GhostInfo_s(gcells); } catch(std::exception const& e) { std::ostringstream ___2892; ___2892 << "Error in ghost cell list for zone " << zone << " partition " << ___2977 << ": " << e.what(); throw Error(___2892.str()); } zonePtr->m_partitionMap[___2977 - 1] = newPartition; } template void ___3970::addFEZonePartition<int32_t>( int32_t                     zone, int32_t                     ___2977, int64_t                     ___2821, int64_t                     ___2781, std::vector<int32_t> const& gnodes, std::vector<int32_t> const& gnpartitions, std::vector<int32_t> const& gnpnodes, std::vector<int32_t> const& gcells); template void ___3970::addFEZonePartition<int64_t>( int32_t                     zone, int32_t                     ___2977, int64_t                     ___2821, int64_t                     ___2781, std::vector<int64_t> const& gnodes, std::vector<int32_t> const& gnpartitions, std::vector<int64_t> const& gnpnodes, std::vector<int64_t> const& gcells); namespace { void throwIfInvalidIndex(char const* indexName, int64_t ___4314, int64_t maxValue) { if (___4314 > maxValue) { std::ostringstream ___2892; ___2892 << "Invalid value for " << indexName << ": " << ___4314 << ". Max value is " << maxValue << "."; throw ___3970::Error(___2892.str()); } } } void ___3970::addIJKZonePartition(int32_t zone, int32_t ___2977, int64_t iMin, int64_t jMin, int64_t kMin, int64_t iMax, int64_t jMax, int64_t kMax) { REQUIRE(iMax > iMin && iMin > 0); REQUIRE(jMax > jMin && jMin > 0); REQUIRE(kMax > kMin && kMin > 0); Zone_s* zonePtr = getAndCheckZonePtr(zone); throwIfInvalidIndex("IMax", iMax, zonePtr->___2682.i());; throwIfInvalidIndex("JMax", jMax, zonePtr->___2682.___2105());; throwIfInvalidIndex("KMax", kMax, zonePtr->___2682.___2134());; zonePtr->m_partitionMap[___2977 - 1] = boost::make_shared<Zone_s>(*this, zonePtr, iMin, jMin, kMin, iMax, jMax, kMax); } void ___3970::___8(std::string const& ___2685, std::string const& ___4314) { ___2399->m_auxDataItems.push_back(AuxData_s::AuxDataItem(___270, ___4226, ___2685, ___4314)); } void ___3970::___20(int32_t zone, std::string const& ___2685, std::string const& ___4314)
{ REQUIRE(m_zoneMap.find(static_cast<___4636>(zone - 1)) != m_zoneMap.end()); m_zoneMap[zone - 1]->___2345->m_auxDataItems.push_back(AuxData_s::AuxDataItem(___270, ___4226, ___2685, ___4314)); } void ___3970::___18(int32_t ___4336, std::string const& ___2685, std::string const& ___4314) { REQUIRE(0 < ___4336 && ___4336 <= static_cast<___4352>(___2674.size())); ___2672[___4336 - 1]->m_auxDataItems.push_back(AuxData_s::AuxDataItem(___270, ___4226, ___2685, ___4314)); } void ___3970::___6(std::vector<std::string> const& ___2173) { ___2398.push_back(___2173); } void ___3970::___9( double ___4574, double ___4591, double ___4715, CoordSys_e ___3159, ___372 ___2004, ___1172 zone, ___516 color, ___516 ___1411, ___372 ___2022, GeomType_e ___1651, LinePattern_e ___2263, double ___2986, double ___2289, uint16_t ___2793, ArrowheadStyle_e arrowheadStyle, ArrowheadAttachment_e arrowheadAttachment, double arrowheadSize, double arrowheadAngle, Scope_e ___3442, Clipping_e ___495, ___2227 ___2835, ___2227 const* ___2837, float const* ___4572, float const* ___4589, float const* ___4712, char const* ___2327) { REQUIRE(VALID_ENUM(___3159, CoordSys_e)); REQUIRE(VALID_BOOLEAN(___2004)); REQUIRE(___1420 <= color && color <= ___2195); REQUIRE(___1420 <= ___1411 && ___1411 <= ___2195); REQUIRE(VALID_BOOLEAN(___2022)); REQUIRE(VALID_ENUM(___1651, GeomType_e)); REQUIRE(VALID_ENUM(___2263, LinePattern_e)); REQUIRE(VALID_ENUM(arrowheadStyle, ArrowheadStyle_e)); REQUIRE(VALID_ENUM(arrowheadAttachment, ArrowheadAttachment_e)); REQUIRE(VALID_ENUM(___3442, Scope_e)); REQUIRE(VALID_ENUM(___495, Clipping_e)); REQUIRE(VALID_REF(___2837)); REQUIRE(VALID_REF(___4572)); REQUIRE(IMPLICATION(___1651 != GeomType_Circle && ___1651 != GeomType_Square, VALID_REF(___4589))); REQUIRE(IMPLICATION( ___1651 == GeomType_LineSegs3D || (___1651 == GeomType_LineSegs && ___3159 == CoordSys_Grid3D), VALID_REF(___4712))); REQUIRE(VALID_REF_OR_NULL(___2327)); std::vector<std::vector<___4580> > ___1572; if (___1651 == ___1588) { ___1651 = GeomType_LineSegs; ___3159 = CoordSys_Grid3D; } switch(___1651) { case GeomType_LineSegs: { ___1572.resize(static_cast<size_t>(___2835)); int index = 0; for(___2227 i = 0; i < ___2835; ++i) { for(___2227 ___2105 = 0; ___2105 < ___2837[i]; ++___2105) { if (___3159 == CoordSys_Grid3D) ___1572[i].push_back(___4580(___4572[index], ___4589[index], ___4712[index])); else ___1572[i].push_back(___4580(___4572[index], ___4589[index], 0.0)); ++index; } } } break; case GeomType_Rectangle: case GeomType_Ellipse: ___1572.resize(1); ___1572[0].push_back(___4580(___4572[0], ___4589[0], 0.0)); break; case GeomType_Square: case GeomType_Circle: ___1572.resize(1); ___1572[0].push_back(___4580(___4572[0], 0.0, 0.0)); break; default: ___478(___1305); break; } ___2465.push_back(tecioszl::___1556( ___4574, ___4591, ___4715, ___3159, ___2004, zone, color, ___1411, ___2022, ___1651, ___2263, ___2986, ___2289, ___2793, arrowheadStyle, arrowheadAttachment, arrowheadSize, arrowheadAngle, ___3442, ___495, ___1572, ___2327 != NULL ? ___2327 : "")); } void ___3970::___9(tecioszl::___1556 const& ___1555) { ___2465.push_back(___1555); } void ___3970::___16( double ___4574, double ___4591, double ___4713, CoordSys_e ___3159, ___372 ___2004, ___1172 zone, Font_e ___1443, Units_e ___1452, double ___1450, TextBox_e ___410, double ___408, double ___406, ___516 ___402, ___516 ___404, double ___56, TextAnchor_e ___38, double ___2287, ___516 ___4080, Scope_e ___3442, Clipping_e ___495, char const* ___4042, char const* ___2327) { REQUIRE(VALID_ENUM(___3159, CoordSys_e)); REQUIRE(VALID_BOOLEAN(___2004)); REQUIRE(VALID_ENUM(___1443, Font_e) && ___1443 != ___1448); REQUIRE(VALID_ENUM(___1452, Units_e)); REQUIRE(___1450 > 0.0); REQUIRE(VALID_ENUM(___410, TextBox_e)); REQUIRE(0.0 <= ___408 && ___408 <= 100.0); REQUIRE(0.0001 <= ___406 && ___406 <= 100.0); REQUIRE(___1420 <= ___402 && ___402 <= ___2195); REQUIRE(___1420 <= ___404 && ___404 <= ___2195); REQUIRE(VALID_ENUM(___38, TextAnchor_e)); REQUIRE(___2287 > 0.0); REQUIRE(___1420 <= ___4080 && ___4080 <= ___2195); REQUIRE(VALID_ENUM(___3442, Scope_e)); REQUIRE(VALID_ENUM(___495, Clipping_e)); REQUIRE(VALID_REF(___4042)); REQUIRE(VALID_REF_OR_NULL(___2327)); std::map<Font_e, std::string> textTypefaceFamilies = boost::assign::map_list_of (___1454,           "Helvetica") (___1455,       "Helvetica") (Font_HelveticaItalic,     "Helvetica") (Font_HelveticaItalicBold, "Helvetica") (___1449,               "Greek") (___1459,                "Math")
(___1470,         "User Defined") (___1466,               "Times") (___1468,         "Times") (___1467,           "Times") (___1469,     "Times") (___1445,             "Courier") (___1446,         "Courier") (Font_CourierItalic,       "Courier") (Font_CourierItalicBold,   "Courier"); ___372 ___4132 = (___1443 == ___1455         || ___1443 == Font_HelveticaItalicBold   || ___1443 == ___1467             || ___1443 == ___1469       || ___1443 == ___1446           || ___1443 == Font_CourierItalicBold); ___372 ___4134 = (___1443 == ___1468         || ___1443 == ___1469     || ___1443 == Font_HelveticaItalic     || ___1443 == Font_HelveticaItalicBold || ___1443 == Font_CourierItalic       || ___1443 == Font_CourierItalicBold); ___2640.push_back(tecioszl::Text( ___4574, ___4591, ___4713, ___402, ___404, ___406, ___408, ___410, ___38, ___56, ___495, ___4080, ___1450, ___2287, ___2327 != NULL ? ___2327 : "", ___3159, ___3442, ___1452, ___4042, textTypefaceFamilies[___1443], ___4132, ___4134, zone, ___2004)); } void ___3970::___16(tecioszl::Text const& ___4042) { ___2640.push_back(___4042); } void ___3970::___430(___2227 count, void const* data, bool ___2013) { if (m_zoneMap.empty()) throw Error("No zones have been defined."); boost::shared_ptr<Zone_s> zone = m_zoneMap.rbegin()->second; if (!zone->m_partitionMap.empty()) zone = zone->m_partitionMap.rbegin()->second; if (zone->___2397 < zone->___2496.size() && zone->___2496[zone->___2397]->storedValueCount() == 0) { zone->___2496[zone->___2397]-> reserveValues(zone->___2496[zone->___2397]->___2668); } for(___2227 i = 0; i < count; ++i) { if (zone->___2397 >= zone->___2496.size()) throw Error("Too many data values for this zone."); double d; if (___2013) d = ((double const*)data)[i]; else d = static_cast<double>(((float const*)data)[i]); ___1362& ___1351 = *zone->___2496[zone->___2397]; ___1351.appendValue(d); if (zone->___2684 == ___4704 && ___1351.___2669 == ___4328) { if (zone->___2682.i() > 1 && ___1351.storedValueCount() % zone->___2682.i() == static_cast<size_t>(zone->___2682.i() - 1)) ___1351.appendValue(___1362::GHOST_VALUE); if (zone->___2682.___2105() > 1 && ___1351.storedValueCount() % (zone->___2682.i() * zone->___2682.___2105()) == static_cast<size_t>(zone->___2682.i() * (zone->___2682.___2105() - 1))) for(___2227 ___1841 = 0; ___1841 < static_cast<___2227>(zone->___2682.i()); ++___1841) ___1351.appendValue(___1362::GHOST_VALUE); } if (zone->___2496[zone->___2397]->storedValueCount() == zone->___2496[zone->___2397]->___2668) { do { zone->___2397++; } while (zone->___2397 < zone->___2496.size() && zone->___2496[zone->___2397]->storedValueCount() == zone->___2496[zone->___2397]->___2668); if (zone->___2397 < zone->___2496.size()) zone->___2496[zone->___2397]->reserveValues( zone->___2496[zone->___2397]->___2668); } } } void ___3970::___432(___2227 count, int32_t const* ___2723) { boost::shared_ptr<Zone_s> zone = m_zoneMap.rbegin()->second; if (!zone->m_partitionMap.empty()) zone = zone->m_partitionMap.rbegin()->second; if (count + zone->___2497->storedValueCount() > zone->___2497->___2500 * zone->___2497->___2392) throw Error("Too many node map values for this zone."); for (___2227 i = 0; i < count; ++i) { if (((int64_t)___2723[i] > zone->___2682.i()) || (___2723[i] < 1)) { std::ostringstream ___2892; ___2892 << "Err: (TECNODE142) Invalid node map value at position " << i << std::endl << "     node map value = " << ___2723[i] << ", max value = " << zone->___2682.i() << "."; throw ___3970::Error(___2892.str()); } zone->___2497->appendValue(___2723[i] - 1); } } namespace { void throwIf(bool doThrow, char const* ___2432, ___2227 ___4314) { if (doThrow) { std::ostringstream ostream; ostream << ___2432 << ___4314 << "."; throw ___3970::Error(ostream.str()); } } } template <typename T> void ___3970::___431(Zone_s* zonePtr, T const* faceNeighbors) { ___2227 cellCount; ___2227 faceCount = 0; if (zonePtr->___2684 == ___4704) { cellCount = zonePtr->___2682.i() * zonePtr->___2682.___2105() * (zonePtr->___2682.___2134() - 1); int nDimensions = 0; if (zonePtr->___2682.i() > 1) ++nDimensions; if (zonePtr->___2682.___2105() > 1) ++nDimensions; if (zonePtr->___2682.___2134() > 1) ++nDimensions; if (nDimensions == 3) faceCount = 6; else if (nDimensions == 2) faceCount = 4; else faceCount = 0; } else { cellCount = zonePtr->___2682.___2105(); faceCount = zonePtr->___2682.___2134();
} ___2227 currentConnection = 0; ___2227 index = 0; while (currentConnection < zonePtr->___2503) { Zone_s::___458 ___457; ___457.first = (___1172)faceNeighbors[index++]; throwIf(___457.first < 1 || cellCount < ___457.first, "Invalid cell number in face connections: ", ___457.first); ___457.second = faceNeighbors[index++]; throwIf(___457.second < 1 || faceCount < ___457.second, "Invalid face number in face connections: ", ___457.second); Zone_s::___1275& ___1274 = zonePtr->___2457[___457]; ___2227 numNeighbors = 1; if (zonePtr->___2458 == ___1289 || zonePtr->___2458 == ___1286) { ___2227 isObscured = faceNeighbors[index++]; throwIf(isObscured != 0 && isObscured != 1, "Invalid face obscuration flag in face connections: ", isObscured); ___1274.___2488 = (isObscured == 1 ? ___4226 : ___1305); numNeighbors = faceNeighbors[index++]; throwIf(numNeighbors < 0, "Invalid number of neighbors in face connections: ", numNeighbors); } else { ___1274.___2488 = ___4226; } for(___2227 whichNeighbor = 0; whichNeighbor < numNeighbors; ++whichNeighbor) { Zone_s::___4607 zoneCell; if (zonePtr->___2458 == ___1287 || zonePtr->___2458 == ___1286) zoneCell.first = static_cast<___1172>(faceNeighbors[index++]); else zoneCell.first = 0; throwIf(zoneCell.first < 0, "Invalid neighbor zone in face connections: ", (___2227)zoneCell.first); zoneCell.second = faceNeighbors[index++]; throwIf(zoneCell.second < 0, "Invalid neighbor cell in face connections: ", zoneCell.second); ___1274.___2678.push_back(zoneCell); } ++currentConnection; } } template void ___3970::___431<int32_t>(Zone_s* zonePtr, int32_t const* faceNeighbors); template void ___3970::___431<int64_t>(Zone_s* zonePtr, int64_t const* faceNeighbors); void ___3970::copyConnectivity(___3970 const& ___2888) { BOOST_FOREACH(Zone_s::ZoneMap::value_type& zonePair, m_zoneMap) { Zone_s::ZoneMap::const_iterator iter = ___2888.m_zoneMap.find(zonePair.first); throwIf(iter == ___2888.m_zoneMap.end(), "Non-matching zone structure between grid and solution files\nZone not found in grid file: ", zonePair.first); if (!zonePair.second->m_partitionMap.empty()) { BOOST_FOREACH(Zone_s::ZoneMap::value_type& partitionPair, zonePair.second->m_partitionMap) { Zone_s::ZoneMap::const_iterator subIter = iter->second->m_partitionMap.find(partitionPair.first); throwIf(subIter == iter->second->m_partitionMap.end(), "Non-matching zone structure between grid and solution files\npartition not found in grid file: ", partitionPair.first); partitionPair.second->___2497 = subIter->second->___2497; } } else { zonePair.second->___2497 = iter->second->___2497; } } } int32_t ___3970::___2846() const { return static_cast<int32_t>(m_nextZoneIndex); } int32_t ___3970::numZonePartitions(int32_t zone) const { Zone_s::ZoneMap::const_iterator iter = m_zoneMap.find(static_cast<___4636>(zone - 1)); REQUIRE(iter != m_zoneMap.end()); if (iter->second->m_partitionOwners.empty()) return static_cast<int32_t>(iter->second->m_partitionMap.size()); return static_cast<int32_t>(iter->second->m_partitionOwners.size()); } int32_t ___3970::___2843() const { return static_cast<int32_t>(___2674.size()); } void ___3970::___4166(bool checkConnectivity) const { if (!m_zoneMap.empty()) { boost::shared_ptr<Zone_s> zone = m_zoneMap.rbegin()->second; if (!zone->m_partitionMap.empty()) zone = zone->m_partitionMap.rbegin()->second; else if (!zone->m_partitionOwners.empty()) return; if (!zone->m_allVarsAreShared && zone->___2397 != ___2674.size()) { std::ostringstream ostream; ___2227 valuesNeeded = zone->___2496[zone->___2397]->___2668 - (___2227)zone->___2496[zone->___2397]->storedValueCount(); ostream << "Not all variable values for the current zone have been written.\n" << "Currently need " << valuesNeeded << " for variable " << zone->___2397 + 1 << "."; throw Error(ostream.str()); } if (checkConnectivity) { if (zone->___2497 && zone->___2497->___2392 * zone->___2497->___2500 > zone->___2497->storedValueCount()) { ___2227 valuesNeeded = zone->___2497->___2392 * zone->___2497->___2500 - zone->___2497->storedValueCount(); std::ostringstream ostream; ostream << "Not all node map values for the current zone have been written.\n" << "Currently need " << valuesNeeded << " more values."; throw Error(ostream.str()); } } } } void ___3970::clear(int32_t numZonesToRetain, int32_t const* zonesToRetain) { if (!m_zoneMap.empty()) m_lastZoneFlushedToDisk = static_cast<___3933::___4636>(m_zoneMap.rbegin()->first); if (numZonesToRetain == 0) { m_zoneMap.clear(); } else { boost::unordered_set<Zone_s::ZoneMap::key_type>zoneSet; for (int32_t i = 0; i < numZonesToRetain; ++i)
zoneSet.insert(zonesToRetain[i] - 1); for (Zone_s::ZoneMap::iterator it = m_zoneMap.begin(); it != m_zoneMap.end();) if (zoneSet.find(it->first) == zoneSet.end()) { Zone_s::ZoneMap::iterator eraseIt = it; ++it; m_zoneMap.erase(eraseIt); } else { ++it; } } if (___2399) ___2399->m_auxDataItems.clear(); for (size_t ___4336 = 0; ___4336 < ___2672.size(); ++___4336) if (___2672[___4336]) ___2672[___4336]->m_auxDataItems.clear(); ___2465.clear(); ___2640.clear(); ___2398.clear(); ENSURE(empty()); } bool ___3970::empty() { bool ___3358 = true; if (!m_zoneMap.empty() && m_zoneMap.rbegin()->first > m_lastZoneFlushedToDisk) ___3358 = false; if (!___2465.empty() || !___2640.empty() || !___2398.empty()) ___3358 = false; if (___2399 && !___2399->m_auxDataItems.empty()) ___3358 = false; for(size_t i = 0; i < ___2672.size(); ++i) if (___2672[i] && !___2672[i]->m_auxDataItems.empty()) ___3358 = false; return  ___3358; } std::set<___3493> ___3970::zoneSet() const { std::set<___3493> ___3358; for (Zone_s::ZoneMap::const_iterator it = m_zoneMap.begin(); it != m_zoneMap.end(); ++it) ___3358.insert(static_cast<___3493>(it->first + 1)); return ___3358; } std::set<___3493> ___3970::unflushedZoneSet() const { std::set<___3493> ___3358; for (Zone_s::ZoneMap::const_iterator it = m_zoneMap.upper_bound(m_lastZoneFlushedToDisk); it != m_zoneMap.end(); ++it) ___3358.insert(static_cast<___3493>(it->first + 1)); return ___3358; } Zone_s* ___3970::zonePtr(___4636 ___4658) const { REQUIRE(0 < ___4658); Zone_s::ZoneMap::const_iterator zoneIter = m_zoneMap.find(___4658 - 1); if (zoneIter != m_zoneMap.end()) return zoneIter->second.get(); else return NULL; } bool ___3970::validPartitionNum(___3933::___4636 ___4658, ___3933::___4636 partitionNum) const { Zone_s* zPtr = zonePtr(___4658); return zPtr->m_partitionMap.find(partitionNum - 1) != zPtr->m_partitionMap.end(); } void ___3970::flattenSinglePartitionZones() { BOOST_FOREACH(Zone_s::ZoneMap::value_type& valuePair, m_zoneMap) { Zone_s* zonePtr = valuePair.second.get();
 #if defined TECIOMPI
if (zonePtr->m_partitionMap.size() == 1 && zonePtr->m_partitionOwners.size() == 1)
 #else
if (zonePtr->m_partitionMap.size() == 1)
 #endif
{ Zone_s* partitionPtr = zonePtr->m_partitionMap.begin()->second.get(); zonePtr->___2496 = partitionPtr->___2496; zonePtr->___2497 = partitionPtr->___2497; zonePtr->m_partitionMap.clear(); } } } tecplot::___3933::___1393 ___3970::sizeInFile(bool ___4480) const { ___1393 size = 0; size += stringSizeInFile(___2649, ___4480); size += vectorSizeInFile(___2674, ___4480); size += scalarSizeInFile(m_defaultVarType, ___4480); size += scalarSizeInFile(m_nextZoneIndex, ___4480); size += scalarSizeInFile(m_lastZoneFlushedToDisk, ___4480); size += mapOfScalarsToPtrsSizeInFile(m_zoneMap, ___4480); size += ___2399->sizeInFile(___4480); size += vectorOfPtrsSizeInFile(___2672, ___4480); size += vectorOfObjectsSizeInFile(___2465, ___4480); size += vectorOfObjectsSizeInFile(___2640, ___4480); size += scalarSizeInFile((uint64_t)___2398.size(), ___4480); BOOST_FOREACH(std::vector<std::string> const& vec, ___2398) size += vectorSizeInFile(vec, ___4480); return size; } void ___3970::writeToFile(___3933::FileWriterInterface& outputFile, ___3933::___1393 fileLoc, bool ___4480) const { REQUIRE(outputFile.___2041()); outputFile.___3459(fileLoc); ___4544(outputFile, ___2649, ___4480); writeVector(outputFile, ___2674, ___4480); writeScalar(outputFile, m_defaultVarType, ___4480); writeScalar(outputFile, m_nextZoneIndex, ___4480); writeScalar(outputFile, m_lastZoneFlushedToDisk, ___4480); writeMapOfScalarsToPtrs(outputFile, m_zoneMap, ___4480); ___2399->writeToFile(outputFile, ___4480); writeVectorOfPtrs(outputFile, ___2672, ___4480); writeVectorOfObjects(outputFile, ___2465, ___4480); writeVectorOfObjects(outputFile, ___2640, ___4480); writeScalar(outputFile, (uint64_t)___2398.size(), ___4480); BOOST_FOREACH(std::vector<std::string> const& vec, ___2398) writeVector(outputFile, vec, ___4480); ENSURE(outputFile.fileLoc() == fileLoc + sizeInFile(___4480)); } ___3970::___3970(___3933::___1399& inputFile, bool readASCII) { REQUIRE(inputFile.___2041()); readString(inputFile, ___2649, readASCII); readVector(inputFile, ___2674, readASCII); readScalar(inputFile, m_defaultVarType, readASCII); readScalar(inputFile, m_nextZoneIndex, readASCII); readScalar(inputFile, m_lastZoneFlushedToDisk, readASCII); readMapOfScalarsToPtrs(inputFile, m_zoneMap, readASCII); ___2399 = AuxData_s::makePtr(inputFile, readASCII); readVectorOfPtrs(inputFile, ___2672, readASCII); readVectorOfObjects(inputFile, ___2465, readASCII); readVectorOfObjects(inputFile, ___2640, readASCII); uint64_t length; readScalar(inputFile, length, readASCII); ___2398.resize((size_t)length); for(size_t i = 0; i < ___2398.size(); ++i) readVector(inputFile, ___2398[i], readASCII); } }}
