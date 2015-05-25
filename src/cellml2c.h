/*==========================================================================
  
		--- DENIS Project ---
		  -----------------

	 Distributed computing
	 Electrophysiologycal Models
	 Networking colaboration
	 In Silico research
	 Sharing Knowledge
			
 ---------------------------------------------------------------------------

                                                   San Jorge University
				                                  School of Engineering
 
                                                      http://eps.usj.es

 ---------------------------------------------------------------------------

   Copyright 2015 J. Carro; J. Castro

  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at

	   http://www.apache.org/licenses/LICENSE-2.0

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.

 ===========================================================================*/

#include <IfaceCellML_APISPEC.hxx>
#include <IfaceAnnoTools.hxx>
#include <IfaceCeLEDSExporter.hxx>
#include <CeLEDSExporterBootstrap.hpp>
#include <CellMLBootstrap.hpp>
#include <fstream>
#include <string>
#include <cstring>
#include "cellmlFilesList.h"

using namespace std;
using namespace iface::cellml_api;
using namespace iface::cellml_services;

wstring getFormatPath(char* exeChar){
	string executable = exeChar;
	string formatPath = executable.substr(0, executable.find_last_of("/")+1) + "C.xml";
	wstring wsFormatPath(formatPath.begin(), formatPath.end());
	
	return wsFormatPath;
}

wstring getFileWstring(const char* modelChar){
	const size_t cSizeURL = strlen(modelChar)+1;
	wchar_t* wcURL = new wchar_t[cSizeURL];
	mbstowcs (wcURL, modelChar, cSizeURL);
	wstring wsURL(wcURL);	
	
	return wsURL;
}

wstring getModelUrL(char* modelChar){
	const size_t cSizeURL = strlen(modelChar)+1;
	wchar_t* wcURL = new wchar_t[cSizeURL];
	mbstowcs (wcURL, modelChar, cSizeURL);
	wstring wsURL(wcURL);	
	
	return wsURL;
}

wstring getModelPrefix(char* prefixChar){
	const size_t cSizePrefix = strlen(prefixChar)+1;
	wchar_t* wcPrefix = new wchar_t[cSizePrefix];
	mbstowcs (wcPrefix, prefixChar, cSizePrefix);
	wstring wsPrefix(wcPrefix);	
	
	return wsPrefix;
}

wstring getCode(wstring wsURL, wstring wsFormatPath){
	CellMLBootstrap* bootstrap = CreateCellMLBootstrap();
	cout << "Bootstrap created" << endl;
	DOMModelLoader* ml = bootstrap->modelLoader();
	cout << "ModelLoader created" << endl;
	Model* model = ml->loadFromURL(wsURL);
	cout << "Model loaded from URL" << endl;

	CeLEDSExporterBootstrap* celedsexporterb = CreateCeLEDSExporterBootstrap();
	cout << "CeLEDSExproterBootestrap created" << endl;

	CodeExporter* ce = celedsexporterb->createExporter(wsFormatPath);
	cout << "Exporter created" << endl;

	wstring code = ce->generateCode(model);
	cout << "Code generated" << endl;
	
	return code;
}

char *getFile(char* outputPath,char* prefix){
	char * file = new char[strlen(outputPath)+strlen(prefix)+4];
	sprintf(file,"%s/%s.h",outputPath,prefix);
	
	return file;
}

void printCommentHeader(wofstream &wofs, wstring prefix)
{
	wofs << "//==============================================================================" << endl;
	wofs << "//                                                                              " << endl;
	wofs << "//                                  DENIS Project                               " << endl;
	wofs << "//                                                                              " << endl;
	wofs << "//------------------------------------------------------------------------------" << endl;
	wofs << "//                                                                              " << endl;
	wofs << "//   -- C File of the "<< prefix << " model created for the DENIS Project --    " << endl;
	wofs << "//                                                                              " << endl;
	wofs << "// This file has been automatically created using the CellML API.               " << endl;
	wofs << "//                                                                              " << endl;
	wofs << "//------------------------------------------------------------------------------" << endl;
	wofs << "//                                                                              " << endl;
   	wofs << "// DENIS-CellML2C Copyright 2015 J. Carro; J. Castro                            " << endl;
	wofs << "//                                                                              " << endl;
  	wofs << "// Licensed under the Apache License, Version 2.0 (the \"License\");            " << endl;
  	wofs << "// you may not use this file except in compliance with the License.             " << endl;
  	wofs << "// You may obtain a copy of the License at                                      " << endl;
	wofs << "//                                                                              " << endl;
	wofs << "// http://www.apache.org/licenses/LICENSE-2.0                                   " << endl;
	wofs << "//                                                                              " << endl;
  	wofs << "// Unless required by applicable law or agreed to in writing, software          " << endl;
  	wofs << "// distributed under the License is distributed on an \"AS IS\" BASIS,          " << endl;
  	wofs << "// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.     " << endl;
  	wofs << "// See the License for the specific language governing permissions and          " << endl;
  	wofs << "// limitations under the License.                                               " << endl;
	wofs << "//                                                                              " << endl;
	wofs << "//------------------------------------------------------------------------------" << endl;
	wofs << "//                                                                              " << endl;
	wofs << "//                                                        San Jorge University  " << endl;
	wofs << "//                                                       School of Engineering  " << endl;
	wofs << "//                                                                              " << endl;
	wofs << "//                                                           http://eps.usj.es  " << endl;
	wofs << "//                                                                              " << endl;
	wofs << "//==============================================================================" << endl;
	wofs << endl;
}

void saveModel(const char* file, wstring code, wstring prefix){
	cout << file << endl;
	wofstream wofs(file);
	printCommentHeader(wofs, prefix);
	wofs << "namespace " << prefix << "{" << endl;
	wofs << code << endl;
	wofs << "}" << endl;
	
	wofs.close();
	wcout << "File " << file << " created." <<endl;
}

string getCellMLFileName(string s)
{
	string out="";
	
	const char* cellmlExtension = ".cellml";
	if(s.length()<strlen(cellmlExtension))
		return out;

	int extensionLen = strlen(cellmlExtension);
	string extension = s.substr(s.length()-extensionLen,extensionLen);


	if(strcmp(extension.c_str(),cellmlExtension)==0)
		out =  s.substr(0, s.length()-extensionLen);
		
	return out;
	
	
	
}

void printID(ofstream &ofs,cellmlFilesList* list)
{
	cellmlFilesList* iterator=list;
	int i=0;
	while(iterator!=NULL){
		ofs << "#define " << iterator->name << "_ID " << i++ << endl;
		iterator=iterator->next;
	}
	
	ofs << endl;
}

void printIncludes(ofstream &ofs,cellmlFilesList* list)
{
	cellmlFilesList* iterator=list;
	int i=0;
	while(iterator!=NULL){
		ofs << "#include \"" << iterator->name << ".h\"" << endl;
		iterator=iterator->next;
	}
	
	ofs << endl;
}

void printGetModelID(ofstream &ofs,cellmlFilesList* list)
{
	cellmlFilesList* iterator=list;
	int i=0;
	
	ofs << "int getModelId(const char* modelName){" << endl;
	
	while(iterator!=NULL){
		ofs << "\tif(strcmp(modelName, \"" << iterator->name << "\")==0)" <<endl;
		ofs << "\t\treturn " << iterator->name << "_ID;" << endl;
		iterator=iterator->next;
	}
	ofs << "}" << endl;
	ofs << endl;
	
}

void printFunction(ofstream &ofs, string functionType,string functionName, string functionParameters, cellmlFilesList* list)
{
	cellmlFilesList* iterator=list;
	int i=0;
	
	ofs << functionType << " " << functionName << "(int modelId";
	if(functionParameters.length()>0)
		ofs << ", ";
	ofs << functionParameters << "){" <<endl;
	ofs << "\tswitch(modelid){"<<endl;
	while(iterator!=NULL){
		ofs << "\tcase " << iterator->name <<"_ID:" <<endl;
		ofs << "\t\treturn " <<iterator->name << "::" << functionName << "(" << functionParameters << ");" <<endl;
		iterator=iterator->next;
	}
	
	ofs << "\t}" << endl;
	ofs << "}" << endl;
	ofs << endl;
	
}
	
void createModelsHeader(cellmlFilesList* list, string path)
{
	ofstream ofsh((path+"/models.h").c_str());
	
	printIncludes(ofsh, list);
	printID(ofsh, list);
	ofsh << "int getModelId(const char* modelName);" << endl << endl;
	ofsh << "double* getConstantsArray();" << endl;
	ofsh << "double* getRatesArray();" << endl;
	ofsh << "double* getStatesArray();" << endl;
	ofsh << "double* getAlgebraicArray();" << endl << endl;
	ofsh << "void getArrays(int modelId, double **constants, double **rates, double **states, double **algebraic):" << endl;
	ofsh << "void vectorsLength(int modelId, int* algebraicLength, int* statesLength, int* constantsLength);" << endl;
	ofsh << "void names(int modelId, const char* &VoI, const char** constants, const char** rates, const char** states, const char** algebraic);" << endl;
	ofsh << "void initConsts(int modelId, double* constants, double* states);" << endl;
	ofsh << "void computeRates(int modelId, double VoI, double* constants, double* rates, double* states, double* algebraic);" << endl;
	ofsh << "void computeVariables(int modelId, double VoI, double* constants, double* rates, double* states, double* algebraic);" << endl;
	
	ofsh.close();
	
	
	ofstream ofscpp((path+"/models.cpp").c_str());
	
	printGetModelID(ofscpp, list);
	printFunction(ofscpp,"double*", "getConstantsArray", "", list);
	printFunction(ofscpp,"double*", "getRatesArray", "", list);
	printFunction(ofscpp,"double*", "getStatesArray", "", list);
	printFunction(ofscpp,"double*", "getAlgebraicArray", "", list);
	printFunction(ofscpp,"void", "getArrays", "double **constants, double **rates, double **states, double **algebraic", list);
	printFunction(ofscpp,"void", "vectorsLength", "int* algebraicLength, int* statesLength, int* constantsLength", list);
	printFunction(ofscpp,"void", "names", "const char* &VoI, const char** constants, const char** rates, const char** states, const char** algebraic", list);
	printFunction(ofscpp,"void", "initConsts", "double* constants, double* states", list);
	printFunction(ofscpp,"void", "computeRates", "double VoI, double* constants, double* rates, double* states, double* algebraic", list);
	printFunction(ofscpp,"void", "computeVariables", "double VoI, double* constants, double* rates, double* states, double* algebraic", list);

	ofscpp.close();
}
