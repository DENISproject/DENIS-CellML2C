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

using namespace std;
using namespace iface::cellml_api;
using namespace iface::cellml_services;

wstring getFormatPath(char* exeChar){
	string executable = exeChar;
	string formatPath = executable.substr(0, executable.find_last_of("/")+1) + "C.xml";
	wstring wsFormatPath(formatPath.begin(), formatPath.end());
	
	return wsFormatPath;
}

wstring getModelUrL(char* modelChar){
	const size_t cSizeURL = strlen(modelChar)+1;
	wchar_t* wcURL = new wchar_t[cSizeURL];
	mbstowcs (wcURL, modelChar, cSizeURL);
	wstring wsURL(wcURL);	
	
	return wsURL;
}

wstring getModelPrefix(char* prefixChar){
	const size_t cSizePrefix = strlen(prefixChar)+2;
	wchar_t* wcPrefix = new wchar_t[cSizePrefix];
	mbstowcs (wcPrefix, prefixChar, cSizePrefix-1);
	wcPrefix[cSizePrefix-2]='_';
	wcPrefix[cSizePrefix-1]='\0';
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
}

void saveModel(char *file, wstring code){
	wofstream wofs(file);
	wofs << code << endl;
	wcout << "File " << file << " created." <<endl;
}

wstring insertPrefixInCode(wstring code, wstring wsPrefix){
	wstring::size_type posInitConsts = code.find(L"computeRates");
	cout << posInitConsts << endl;
	code.insert(posInitConsts,wsPrefix);
	
	return code;
}
