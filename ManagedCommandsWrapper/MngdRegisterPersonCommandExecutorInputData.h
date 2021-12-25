#pragma once


namespace ManagedCommandsWrapper {
	public enum class FaceRegistrationMode
	{
		OFFLINE,
		ONLINE
	};
	ref class MngdRegisterPersonCommandExecutorInputData
	{
	private:
		System::String^ m_modelDirectoryPath;
		System::String^ m_dataDirectoryPath;
		System::String^ m_imageDirectoryPath;
		System::String^ m_registeredName;
		FaceRegistrationMode m_RegistrationMode;

	public:
		MngdRegisterPersonCommandExecutorInputData()
		{
			m_modelDirectoryPath = gcnew System::String("");
			m_dataDirectoryPath = gcnew System::String("");
			m_imageDirectoryPath = gcnew System::String("");
			m_registeredName = gcnew System::String("");
		}
		MngdRegisterPersonCommandExecutorInputData(System::String^ modelDirPath, System::String^ dataDirPath,
			System::String^ imageDirPath, System::String^ regName)
		{
			m_modelDirectoryPath = modelDirPath;
			m_dataDirectoryPath = dataDirPath;
			m_imageDirectoryPath = imageDirPath;
			m_registeredName = regName;
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

		property System::String^ ImageDirectoryPath
		{
			System::String^ get()
			{
				return m_imageDirectoryPath;
			}
			void set(System::String^ value)
			{
				m_imageDirectoryPath = value;
			}
		}

		property System::String^ RegisteredName
		{
			System::String^ get()
			{
				return m_registeredName;
			}
			void set(System::String^ value)
			{
				m_registeredName = value;
			}
		}

		property FaceRegistrationMode RegistrationMode
		{
			FaceRegistrationMode get()
			{
				return m_RegistrationMode;
			}
			void set(FaceRegistrationMode value)
			{
				m_RegistrationMode = value;
			}
		}
	};
}