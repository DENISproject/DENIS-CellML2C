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
#include <dirent.h>

using namespace iface::cellml_api;
using namespace iface::cellml_services;
using namespace std;


int main(int argc, char **argv)
{

	if(argc!=3){
		cout << "Invalid number of input arguments" << endl << endl;
		cout << "	 cellm2c <input_path> <output_path>" << endl << endl;
		return -1;
	}
	
	
	wstring wsFormatPath = getFormatPath(argv[0]);
	wstring wsURL = getModelUrL(argv[1]);
	
	
	DIR *dir;
	struct dirent *ent;
	wstring wsDirCommand = wsURL;
    string sDirCommand(wsDirCommand.begin(), wsDirCommand.end());
	cellmlFilesList * fileList = NULL;
    
	if ((dir = opendir(sDirCommand.c_str())) != NULL) {
		while ((ent = readdir (dir)) != NULL) {
			string cellMLFileName=getCellMLFileName(ent->d_name);
			
			if(strcmp("",cellMLFileName.c_str())!=0){
				
				cellmlFilesList * newFile = new cellmlFilesList();
				newFile->name = cellMLFileName;
				newFile->next = fileList;
				fileList = newFile;
				
				printf ("%s\n", cellMLFileName.c_str());
				wstring fileCellML = getFileWstring(cellMLFileName.c_str());
				wstring code = getCode(wsURL+L"/"+fileCellML+L".cellml", wsFormatPath);
				saveModel((string(argv[2])+"/models/"+cellMLFileName+".h").c_str(),code,fileCellML);
			}
		}
		closedir (dir);
	}
	else {
		/* could not open directory */
		cout << "Error to open dir " << sDirCommand << endl;
		return EXIT_FAILURE;
	}
	
	int i=0;
	cellmlFilesList *iterator=fileList;
	while(iterator!=NULL){
		cout << ++i << ") File " << iterator->name << endl;
		iterator=iterator->next;
	}
	
	createModelsHeader(fileList,string(argv[2]));
	
	return 0;
}
