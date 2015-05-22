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

#include "cellml2c.h"

using namespace iface::cellml_api;
using namespace iface::cellml_services;
using namespace std;


int main(int argc, char **argv)
{

	if(argc<4){
		cout << "Invalid number of input arguments" << endl << endl;
		cout << "	 cellm2c <cellml_file> <output_path> <output_prefix>" << endl << endl;
		return -1;
	}

	wstring wsFormatPath = getFormatPath(argv[0]);
	wstring wsURL = getModelUrL(argv[1]);	
	char *file = getFile(argv[2],argv[3]);
	wstring wsPrefix = getModelPrefix(argv[3]);	
	
	wstring code = getCode(wsURL, wsFormatPath);

	code = insertPrefixInCode(code, wsPrefix);

	saveModel(file,code);
	
	return 0;
}
