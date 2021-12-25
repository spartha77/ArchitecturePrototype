#pragma once
#ifndef NULLDATADEFINED
#define NULLDATADEFINED
#include "CommandsBase.h"

class /*COMMANDSBASE_API*/ NullData
{
	// Nothing
public:
	NullData() {}
	~NullData() {}
	NullData(const NullData& nul) {}
	NullData(NullData&& nul) {}
	NullData& operator=(const NullData& rhs) { return *this; }
};

namespace AdaptiveHumanTracker {

	class NoData
	{
	public:
		NoData() {}
		virtual ~NoData() {}
		NoData(const NoData& noData) {}
	};
}
#endif
