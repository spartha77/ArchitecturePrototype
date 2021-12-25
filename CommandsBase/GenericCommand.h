#pragma once
#include <type_traits>
#include <string>
#include <memory>
#include "ICommand.h"
#include "NullData.h"
#include <mutex>

namespace AdaptiveHumanTracker {

	
	template<typename GenericSkillImplWrapper, typename InputDataToSkillExecuteType, typename OutputDataFromSkillExecuteType>
	class /*COMMANDSBASE_API*/ GenericSkill : public ISkill< InputDataToSkillExecuteType, OutputDataFromSkillExecuteType>
	{
	public:
		GenericSkill() {}
		virtual ~GenericSkill() {}
		
		using GenericSkillImplementor = typename GenericSkillImplWrapper::GenericSkillImplementer;
		using skill_input_data_type = typename GenericSkillImplWrapper::skill_input_data_type;
		using skill_output_data_type = typename GenericSkillImplWrapper::skill_output_data_type;

		virtual void SetSkillInputData(InputDataToSkillExecuteType& data) override
		{
			static_cast<GenericSkillImplementor*>(this)->ActuallySetSkillInputData(data);
		}
		virtual std::unique_ptr<OutputDataFromSkillExecuteType> GetSkillOutputData() override
		{
			return static_cast<GenericSkillImplementor*>(this)->ActuallyGetSkillOutputData();
		}
		virtual bool Execute(InputDataToSkillExecuteType& data) override
		{
			return static_cast<GenericSkillImplementor*>(this)->ActuallyExecute(data);
		}
		virtual void Terminate() override
		{
			static_cast<GenericSkillImplementor*>(this)->ActuallyTerminate();
		}

	};

	// GenericObserverImplWrapper holds our typedefs, derived does the rest
	template <typename InputDataToSkillExecuteType, typename OutputDataFromSkillExecuteType, typename ExecutorType>
	class GenericSkillImplWrapper
	{
	public:

		using skill_input_data_type = InputDataToSkillExecuteType;
		using skill_output_data_type = OutputDataFromSkillExecuteType;
		
		using skill_executor_type = ExecutorType;
		
		class GenericSkillImplementer :
			public GenericSkill<GenericSkillImplWrapper, InputDataToSkillExecuteType,
			OutputDataFromSkillExecuteType>
		{ // GenericSkillImplementer is now complete
		private:
			//exec_method_type m_SkilledExecuteFunc;
			skill_input_data_type m_SkillExecuteInputData;
			skill_output_data_type m_SkillExecuteOutputData;
			skill_executor_type *m_SkillExecutor;
			
			GenericSkillImplementer(skill_executor_type& executor) :
				m_SkillExecutor(&executor)
			{

			}
			

			void SetSkillExecutor(skill_executor_type& executor)
			{	
				m_SkillExecutor = &executor;
			}
			
		public:
			static GenericSkillImplementer*
				GetInstance(skill_executor_type& executor)
			{
				static GenericSkillImplementer __genericSkillImplementer(executor);
				{	
					__genericSkillImplementer.SetSkillExecutor(executor);
				}
				return &__genericSkillImplementer;
			}
			virtual ~GenericSkillImplementer() = default;


			bool ActuallyExecute(skill_input_data_type& inputData)
			{	
				auto output = m_SkillExecutor->RunExecute(inputData);
				
				if (output == nullptr)
				{
					return false;
				}
				m_SkillExecuteOutputData = *output;
				return true;
			}

			void ActuallyTerminate()
			{
				m_SkillExecutor->Terminate();
			}

			void ActuallySetSkillInputData(skill_input_data_type& data)
			{
				m_SkillExecuteInputData = data;
			}

			std::unique_ptr<skill_output_data_type> ActuallyGetSkillOutputData()
			{
				std::unique_ptr< skill_output_data_type> out = std::unique_ptr< skill_output_data_type>(new skill_output_data_type(m_SkillExecuteOutputData));
				return out;
			}
		};
	};
}


