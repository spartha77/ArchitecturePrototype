#pragma once
#include <string>
#include <functional>

namespace AdaptiveHumanTracker {


	template<typename InputDataToSkillExecuteType, typename OutputDataFromSkillExecuteType>
	using SkillExecuteFunction = typename std::function<std::unique_ptr<OutputDataFromSkillExecuteType>(InputDataToSkillExecuteType&)>;

	//class ISkillExecutor;
	template<typename InputDataToSkillExecuteType, typename OutputDataFromSkillExecuteType>
	class ISkill
	{
	public:
		ISkill() {}
		virtual ~ISkill() {}
		virtual bool Execute(InputDataToSkillExecuteType& data) = 0;
		virtual void SetSkillInputData(InputDataToSkillExecuteType& data) = 0;
		virtual std::unique_ptr<OutputDataFromSkillExecuteType> GetSkillOutputData() = 0;
		virtual void Terminate() = 0;
	};
}