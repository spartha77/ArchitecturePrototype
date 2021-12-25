#pragma once
#include <memory>
#include "CommandManagerLib.h"
#include <ICommand.h>
#include <GenericCommand.h>
#include <CommandReturnsOutputData.h>


namespace AdaptiveHumanTracker {

	class SkillsFactory
	{
	private:
		SkillsFactory() {}

	public:
		template<typename InputDataToSkillExecuteType, typename OutputDataFromSkillExecuteType, typename SkillExecutor>
		static ISkill< InputDataToSkillExecuteType, OutputDataFromSkillExecuteType>*
			CreateSkill(SkillExecutor& executor )
		{
			auto skill = GenericSkillImplWrapper<InputDataToSkillExecuteType, OutputDataFromSkillExecuteType, SkillExecutor>::GenericSkillImplementer::GetInstance(executor);
			return skill;
		}
	};
}