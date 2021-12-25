#pragma once


namespace ManagedCommandsWrapper {

	ref class MngdFaceDetectionCommandExecutorInputData
	{
	private:
		System::String^ m_modelDirectoryPath;
		System::String^ m_dataDirectoryPath;

	public:
		MngdFaceDetectionCommandExecutorInputData()
		{
			m_modelDirectoryPath = gcnew System::String("");
			m_dataDirectoryPath = gcnew System::String("");
		}

		MngdFaceDetectionCommandExecutorInputData(System::String^ modelDirPath, System::String^ dataDirPath)
		{
			m_modelDirectoryPath = modelDirPath;
			m_dataDirectoryPath = dataDirPath;
		}

		property System::String^ ModelDirectoryPath
		{
			System::String^ get()
			{
				return m_modelDirectoryPath;
			}
			void set(System::String^ value)
			{
				m_modelDirectoryPath = value;
			}
		}

		property System::String^ DataDirectoryPath
		{
			System::String^ get()
			{
				return m_dataDirectoryPath;
			}
			void set(System::String^ value)
			{
				m_dataDirectoryPath = value;
			}
		}
	};
}
