#pragma once
#include <Python.h>
#include <string>
/**
* Wrapper to handle the C/Python api functionality, in charge of calling the external python scripts
*/
class PythonHandler
{
public:
	PythonHandler(std::string module, std::string function);

	std::string getModuleName();
	void setModuleName(std::string module);

	std::string getFunctionName();
	void setFunctionName(std::string function);

	void callPythonModule();
private:
	std::string moduleName;
	std::string functionName;
};

