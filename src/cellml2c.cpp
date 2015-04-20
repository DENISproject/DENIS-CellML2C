/*===========================================================================
  
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

using namespace iface::cellml_api;
using namespace iface::cellml_services;
using namespace std;


int main(int argc, char **argv)
{

	if(argc<4){
        	cout << "Invalid number of input arguments" << endl << endl;
		cout << "     cellm2c <cellml_file> <output_c_file> <name_space>" << endl << endl;
		return -1;
	}

        string executable = argv[0];
        string formatPath = executable.substr(0, executable.find_last_of("/")+1) + "C.xml";
	wstring wsFormatPath(formatPath.begin(), formatPath.end());

        const size_t cSize = strlen(argv[1])+1;
        wchar_t* wc = new wchar_t[cSize];
        mbstowcs (wc, argv[1], cSize);
        wstring wsURL(wc);	
  
	
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

	wofstream wofs(argv[2]);
        wofs << "namespace " << argv[3] << "{" << endl << code << endl <<"}";

	cout << "File " << argv[2] << " created." <<endl;
	return 0;
}
