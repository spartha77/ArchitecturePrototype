#pragma once
#include <vector>
#include <memory>
#include "CommandManagerLib.h"

#include <ICommand.h>
#include <CommandReturnsOutputData.h>
#include "CommandFactory.h"


namespace AdaptiveHumanTracker {

	template<typename SkillInputDataType, typename SkillOutputDataType>
	class SkillsManager
	{
	private:
		SkillsManager() { /*m_Skill = nullptr;*/ }
		ISkill<SkillInputDataType, SkillOutputDataType>* m_Skill;

	public:
		~SkillsManager() {}

		static SkillsManager*
			GetInstance()
		{
			static SkillsManager __skillsManager;
			return &__skillsManager;
		}

		template<typename SkillExecutor>
		std::unique_ptr<SkillOutputDataType> Execute(SkillInputDataType& inputData, SkillExecutor& executor)
		{
			std::unique_ptr<SkillOutputDataType> nullOutput;
			m_Skill = SkillsFactory::CreateSkill<SkillInputDataType, SkillOutputDataType, SkillExecutor>(executor);
			if (m_Skill->Execute(inputData))
			{
				auto outputDataFromSkill = m_Skill->GetSkillOutputData();
				return outputDataFromSkill;
			}
			return nullOutput;
		}

		void Terminate()
		{
			if (m_Skill )
				m_Skill->Terminate();
		}
	};
}
