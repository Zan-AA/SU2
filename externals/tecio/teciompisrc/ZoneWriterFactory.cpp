#include "ZoneWriterFactory.h"
#include "ThirdPartyHeadersBegin.h"
#include <stdexcept>
#include <boost/make_shared.hpp>
#include <boost/ref.hpp>
#include "ThirdPartyHeadersEnd.h"
#include "AltTecUtil.h"
#include "ClassicFEZoneWriter.h"
#include "ClassicOrderedZoneWriter.h"
#include "FEZoneInfo.h"
#include "IJKZoneInfo.h"
#include "ItemSetIterator.h"
#include "SZLFEPartitionedZoneWriter.h"
#include "SZLFEZoneWriter.h"
#include "SZLOrderedPartitionedZoneWriter.h"
#include "SZLOrderedZoneWriter.h"
#include "ZoneInfoCache.h"
#include "zoneUtil.h"
namespace tecplot { namespace ___3933 { ___4711::___4711( ZoneInfoCache& zoneInfoCache, ___37& ___36) : ___2680(zoneInfoCache) , ___2337(___36) {} boost::shared_ptr<___4709> ___4711::___4708( ItemSetIterator&              varIter, ___4636                   zone, ___4636                   ___341, std::vector<___372> const& ___4564, ___372                     ___4499) { REQUIRE(0 <= zone && ___2337.___4638(zone + 1)); REQUIRE(0 <= ___341 && ___341 <= zone); REQUIRE(varIter.___2812() == static_cast<___4352>(___4564.size())); REQUIRE(VALID_BOOLEAN(___4499)); boost::shared_ptr<___4709> ___3358; switch(___2337.___4620(zone+1)) { case ___4704: { if (___4646(___2337, zone)) { if (zoneIsPartitioned(___2337, zone)) { ___3358 = boost::make_shared<SZLOrderedPartitionedZoneWriter>( boost::ref(varIter), zone, ___341, boost::ref(___4564), ___4499, boost::ref(___2337), boost::ref(___2680)); } else { boost::shared_ptr<___1881 const> ijkZoneInfo = ___2680.getIJKZoneInfo(zone); ___3358 = boost::make_shared<SZLOrderedZoneWriter>( boost::ref(varIter), zone, ___341, boost::ref(___4564), ___4499, boost::ref(___2337), ijkZoneInfo); } } else { ___3358 = boost::make_shared<ClassicOrderedZoneWriter>( boost::ref(varIter), zone, ___341, boost::ref(___4564), ___4499, boost::ref(___2337)); } } break; case ___4702: case ___4700: case ___4696: { ___3358 = boost::make_shared<ClassicFEZoneWriter>( boost::ref(varIter), zone, ___341, boost::ref(___4564), ___4499, boost::ref(___2337)); } break; case ___4701: case ___4695: { if (zoneIsPartitioned(___2337, zone)) { ___3358 = boost::make_shared<SZLFEPartitionedZoneWriter>( boost::ref(varIter), zone, ___341, boost::ref(___4564), ___4499, boost::ref(___2337), boost::ref(___2680)); } else { boost::shared_ptr<___1350 const> ___1349 = ___2680.getFEZoneInfo(zone); ___3358 = boost::make_shared<SZLFEZoneWriter>( boost::ref(varIter), zone, ___341, boost::ref(___4564), ___4499, boost::ref(___2337), ___1349); } } break; case ___4698: case ___4699: case ___4697: default: std::ostringstream ___2892; ___2892 << "Type of zone " << zone + 1 << " not currently supported"; throw std::runtime_error(___2892.str()); } return ___3358; } }}
