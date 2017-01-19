#include "PythonHandler.h"

PythonHandler::PythonHandler(std::string module, std::string function)
{
	setModuleName(module);
	setFunctionName(function);
}

std::string PythonHandler::getModuleName()
{
	return moduleName;
}

void PythonHandler::setModuleName(std::string modName)
{
	moduleName = modName;
}

std::string PythonHandler::getFunctionName()
{
	return functionName;
}

void PythonHandler::setFunctionName(std::string funcName)
{
	functionName = funcName;
}

void PythonHandler::callPythonModule()
{
	//begin python
	Py_Initialize();

	//call the python module
	PyObject* module = PyImport_ImportModule(moduleName.c_str());
	if (module == 0)
	{
		PyErr_Print();
		printf("Couldn't find python module");
	}

	//create a dictionary of the function's inside the module
	PyObject* comDict = PyModule_GetDict(module);

	//state the specified function name from the dictionary
	PyObject* func = PyDict_GetItemString(comDict, functionName.c_str());

	//state the argument's you want NOTE: currently only work's with functions with 0 arguments
	PyObject* args = PyTuple_New(0);

	//call the object
	PyObject* result = PyObject_CallObject(func, args);
	if (result == NULL)
	{
		printf("Calling function failed");
	}

	//print any errors
	PyErr_Print();

	//clean up the pointer's
	Py_DECREF(module);
	Py_DECREF(comDict);
	Py_DECREF(func);
	Py_DECREF(args);
	Py_DECREF(result);

	//end the python process
	Py_Finalize();
}

