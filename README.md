# ArchitecturePrototype


The repository has the basic architecture implemented in cross-platform C++ (11-14) to use this as a framework to productize algorithms into a consummate usable software solution. This will not successfulyl build since it depends on other dependencies which are not added on purpose.

The design is a collection of several architectural features and software design patterns, the best of various software solutions that are available in the major CAD, CAM and Robotic and Avionic simulation software solutions. Keeping up-to the wise saying that “That which is designed is not to be seen and that which is seen is not to be designed” an honest try is made to implement some of the essential design artifacts.
This framework was subsequently used for a continuous face recognition program having the following components.

1.	Layered Architecture
		
  a.	Presentation Layer (Platform): Platform dependent UI, QT and WinForms in Windows and QT on Ubuntu Linux.
  
    Camera live feed that is available for the platform.
    
  b.	Application layer: Intermediate adapter component, C++/CLI for Windows and an adapter component for QT, to make the integration of the core (see below) loosely coupled     with the platform. These adapter components can be called by the presentation layer as APIs as per 
  
  c.	Feature layer: This is the component written as an adapter to the APIs of the OpenVINO library. This layer is a set of components that make use of OpenVINO library artifacts to create essential objects that constitute the algorithm or business logic. This layer is also data layer since the machine learning model, parameters, hyper-parameters are stored as flat files. This layer is implemented as CommandExecutors.  
  •	FaceDetectionCommandExecutor.h/cpp acts as the adapter
  •	Its private implementation FaceDetectionCommandExecutor_impl is the actual component that executes the algorithm. In order for the architecture to execute the command, the actual executor of the command should implement bool RunExecute(). 
  
  d.	Technology layer: This layer is the Intel OpenVINO library itself. This is at best abstracted from the Feature Layer. The reason for the abstraction of technology is to make it possible to shift between various technologies based on the need by having a loose coupling.
  
  e.	Architecture layer This layer is the invisible component that encapsulates the above layers from inside. The basic idea is to provide a parameterized architecture which enables the feature, platform, technology and architecture itself vary independently without any tight coupling.

2.	Use cases (Commands aka Skills)

  a.	Registration of known faces: A set of images of a person’s face are registered against the person’s name. 
  
  b.	Continuous tracking of the registered persons in the live video feed where the video is shown with the UI with the faces boxed with the tag name.
  
3.	Work flows:

  a.	In the case of Registration of known faces, the flow is unidirectional. That means, the user’s invocation of registration executes through the layers and the data for the face is registered in the model. There is no flow of execution that is returnable except the error or exception.
  
  b.	In the case of continuous tracking, the commands (skills) are very unique in the sense that the command’s output is a continuous streamed frames with the person’s face boxed in the frame image. This necessitates the flow mechanism from inner most layer, where the images are edited, which is written in C++ 11-14 to the presentation layer which is in C#, or for that matter any technology.

4.	Requirements on the type of commands:

A typical command consists of the interface base class, concrete command, which routes the execution to the receiver while the received executing the command. The concrete command also implements the Undo(), Redo(), Journalize(), Serialize() etc. The command receivers actually implement the execution. 

Cons of the typical command pattern model: 

a.	Interface and implementation for commands are hard-wired. This is a needless constraint. The various types of commands are but not limited to and not mutually exclusive of

  1.	Undo/Redo-able/ Non-Undo/Redo-able command with various strategies
  2.	Stateless command 
  3.	Multi-stage input command vs Single stage input command
  4.	Asynchronous commands (same machine or cloud based)
  5.	Continuous output streamable command

  How it is addressed in this architecture:
  
    •	Interface is tied to the implementation, which is the Curiously Recurring Template Pattern, through it as a bridge.
    •	The actual implementation is a templated concrete command which itself is an adapter to the any client which executes RunExecute() method.
    •	This any client needs not adhere to the hierarchies of the commands and can vary independently with commands themselves.

b.	Because, the concrete implementations are hard wired, they have to implement the pure virtual functions or contracts.

  How it is addressed in this architecture:

  •	The client which actually implements the command execution can be a standalone class but having one method RunExecute() be registered.
  
c.	These contracts by themselves need not have any meaning is the context of a particular command and so would involve stubbing

d.	The commands might take input data of a type and return an output data type. Most of the software solutions take the data as a void* pointer and do a reinterpret_cast to the type which only the developer is aware of. Such a type cast will crash the command for a wrong type cast.

How it is addressed in this architecture:

  •	The commands are templated interfaces defining the type of Input and Output data types. 
  •	The definition of commands as templates makes it type-safe at the compile time. 

e.	Command interface-implementation does not have provision to introduce various other classes/strategies for a specific association with a predefined conditions among themselves, for the concrete command to run. These are termed as policies. 

  How it is addressed in this architecture:

  •	The concrete implementation of command themselves are templates and are extensible. More command interfaces can be created to involve multiple class types for those objects to associate and generate pre-defined conditions.

f.	Command executors are the last point where the command is executed. A few of the software solutions execute commands in the concrete command class itself, while others do that in the executors. In terms of good practice both are wrong. 

The command should be executed from a component that is called from the command executor. In essence the command executor should be an adapter. 

  How it is addressed in this architecture:

  •	The command executors in this architecture are mere adapter classes, while their private implementations are the placeholders for command execution. The client class which is responsible for executing the command is merely called in the private implementation.

g.	Continuous streaming output commands need more abstract design since they have a upstream communication of data from core to the platform-UI.

  How it is addressed in this architecture:

  •	The event observer notifier system is implemented and multiple events can be added and registered. 
  •	Every command is registered with the event and the callback methods, which take responsible actions, are subscribed to the event manager. The Notify() call in each subscriber calls the call back function or the callable object up-till the platform UI, where the main thread is posted with the UI update call.



This source is not complete and will not compile. This version is only to upload the source files for reference. 

For the detailed explanations on the design and other components, please refer to README_SkillsFrameworkMotivationAndDesign.docx

Good reading!
