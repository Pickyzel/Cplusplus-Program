//Tiffany McDonnell
//12-9-22
//cs-210

#include <Python.h>
#include <iostream>
#include <fstream>
#include <Windows.h>
#include <cmath>
#include <string>

using namespace std;


void CallProcedure(string pName)
{
	char* procname = new char[pName.length() + 1];
	std::strcpy(procname, pName.c_str());

	Py_Initialize();
	PyObject* my_module = PyImport_ImportModule("python_file");
	PyErr_Print();
	PyObject* my_function = PyObject_GetAttrString(my_module, procname);
	PyObject* my_result = PyObject_CallObject(my_function, NULL);
	Py_Finalize();

	delete[] procname;
}


int callIntFunc(string proc, string param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	char* paramval = new char[param.length() + 1];
	std::strcpy(paramval, param.c_str());


	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"python_file");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(z)", paramval);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;
	delete[] paramval;


	return _PyLong_AsInt(presult);
}


int callIntFunc(string proc, int param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"python_file");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(i)", param);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;

	return _PyLong_AsInt(presult);
}

// Function that reads in a New File that is created by a Python File
void ReadNewFile() {
	ifstream reading;
	string produceName;
	int produceQty;
	reading.open("frequency.dat");

	//prints to the screen if file counldn't open
	if (!reading.is_open()) {
		cout << "Could not open file frequency.dat." << endl;
	}

	while (!reading.eof()) {
		reading >> produceName;
		reading >> produceQty;

		//prints produce name on screen with the text-based histogram representing item quantity
		if (!reading.fail()) {

			cout << produceName << " ";

			for (int i = 0; i < produceQty; ++i) {
				cout << "*";
			}

			cout << endl;
		}
	}

	// Closes file
	reading.close();
}

// function that displays a menu and uses a switch to call correction function based on user input
void Menu() {
	int userOption = 1;
	string userItem;

	//loops through option menu until user quits
	while (userOption != 4) {
		system("CLS");

		try {
			//displays menu
			cout << "What would you like to do?" << endl;
			cout << "Option: 1" << endl;
			cout << "Option: 2" << endl;
			cout << "Option: 3" << endl;
			cout << "4: Exit the program" << endl;

			cin >> userOption;

			//validates user input
			if (cin.fail()) {
				cin.clear();
				cin.ignore();

				throw runtime_error("Invalid option.");
			}

			if (userOption < 1 || userOption > 4) {
				throw runtime_error("Invalid option.");
			}

		}
		catch (runtime_error& inValid) {
			cout << inValid.what() << endl;
			cout << "Please choose an option from the menu." << endl;
			system("pause");
		}

		// switch calls correct function based on user input
		switch (userOption) {
		case 1:
			system("CLS");
			//calls function that calls python function that reads and ouputs product and frequency in a file
			CallProcedure("printProduce");
			system("pause");
			break;

		case 2:
			//loops until user delivers good input
			while (true) {
				system("CLS");

				//validates input
				try {
					cout << "What item would you like to look for?" << endl;
					cin >> userItem;

					if (cin.fail()) {
						cin.clear();
						cin.ignore();
						throw runtime_error("Error.");
					}

					for (unsigned int i = 0; i < userItem.size(); ++i) {
						if (i == 0) {
							if (islower(userItem[i])) {
								userItem[i] = toupper(userItem[i]);
							}
						}
						else if (isupper(userItem[i])) {
							userItem[i] = tolower(userItem[i]);
						}
					}

					//calls python function that reads file and compares user input to file and sees if item is on the file and how many times
					cout << (callIntFunc("readFile", userItem)) << endl;

				}
				catch (runtime_error& error) {
					cout << error.what() << endl;
					cout << "Error." << endl;
				}
				system("pause");
				break;
			}
			break;

		case 3:
			system("CLS");
			//calls python file the writes different types of produce with frequency to file
			callIntFunc("writeNewFile", 0);
			//function reads newly created file and prints produce name and creates a text-based histogram
			ReadNewFile();
			system("pause");
			break;

		case 4:
			break;
		}
	}
}


void main()
{
	Menu();
}