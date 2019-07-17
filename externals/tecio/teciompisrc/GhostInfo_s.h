 #pragma once
#include "ThirdPartyHeadersBegin.h"
#include <algorithm>
#include <iterator>
#include <sstream>
#include <stdexcept>
#include <vector>
#include <boost/unordered_set.hpp>
#include "ThirdPartyHeadersEnd.h"
#include "basicTypes.h"
#include "fileio.h"
struct GhostInfo_s { std::vector<int64_t> m_items; std::vector<int32_t> m_neighbors; std::vector<int64_t> m_neighborItems; GhostInfo_s() {} GhostInfo_s(std::vector<int32_t> const& ___2099) { throwIfDuplicateItems(___2099); std::copy(___2099.begin(), ___2099.end(), std::back_inserter(m_items)); m_neighbors.assign(___2099.size(), 0); m_neighborItems.assign(___2099.size(), 0); } GhostInfo_s(std::vector<int64_t> const& ___2099) : m_items(___2099) { throwIfDuplicateItems(___2099); m_neighbors.assign(___2099.size(), 0); m_neighborItems.assign(___2099.size(), 0); } GhostInfo_s( std::vector<int32_t> const& ___2099, std::vector<int32_t> const& neighbors, std::vector<int32_t> const& neighborItems) : m_neighbors(neighbors) { throwIfDuplicateItems(___2099); std::copy(___2099.begin(), ___2099.end(), std::back_inserter(m_items)); std::copy(neighborItems.begin(), neighborItems.end(), std::back_inserter(m_neighborItems)); } GhostInfo_s( std::vector<int64_t> const& ___2099, std::vector<int32_t> const& neighbors, std::vector<int64_t> const& neighborItems) : m_items(___2099) , m_neighbors(neighbors) , m_neighborItems(neighborItems) { throwIfDuplicateItems(___2099); } template <typename T> void throwIfDuplicateItems(std::vector<T> const& ___2099) { boost::unordered_set<T> ___2100; for(size_t i = 0; i < ___2099.size(); ++i) { if (!___2100.insert(___2099[i]).second) { size_t ___2105 = 0; for(___2105 = 0; ___2105 < i; ++___2105) if (___2099[___2105] == ___2099[i]) break; ___478(___2105 < i); std::ostringstream ___2892; ___2892 << "Duplicate item " << ___2099[i] << " detected at position " << i + 1 << "; duplicates item at position " << ___2105 + 1; throw std::runtime_error(___2892.str().c_str()); } } } bool empty() const { return m_items.empty(); } void writeToFile(tecplot::___3933::FileWriterInterface& outputFile, bool ___4480) const { tecplot::tecioszl::writeVector(outputFile, m_items, ___4480); tecplot::tecioszl::writeVector(outputFile, m_neighbors, ___4480); tecplot::tecioszl::writeVector(outputFile, m_neighborItems, ___4480); } uint64_t sizeInFile(bool ___4480) const { return tecplot::tecioszl::vectorSizeInFile(m_items, ___4480) + tecplot::tecioszl::vectorSizeInFile(m_neighbors, ___4480) + tecplot::tecioszl::vectorSizeInFile(m_neighborItems, ___4480); } GhostInfo_s(tecplot::___3933::___1399& inputFile, bool readASCII) { tecplot::tecioszl::readVector(inputFile, m_items, readASCII); tecplot::tecioszl::readVector(inputFile, m_neighbors, readASCII); tecplot::tecioszl::readVector(inputFile, m_neighborItems, readASCII); } };
