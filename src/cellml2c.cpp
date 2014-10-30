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

	if(argc<3){
        	cout << "Invalid number of input arguments" << endl << endl;
		cout << "     cellm2c <cellml_file> <output_c_file>" << endl << endl;
		return -1;
	}

        const size_t cSize = strlen(argv[1])+1;
        wchar_t* wc = new wchar_t[cSize];
        mbstowcs (wc, argv[1], cSize);
        wstring wide(wc);	
  
	
	CellMLBootstrap* bootstrap = CreateCellMLBootstrap();
	DOMModelLoader* ml = bootstrap->modelLoader();
	Model* model = ml->loadFromURL(wide);

	CeLEDSExporterBootstrap* celedsexporterb = CreateCeLEDSExporterBootstrap();

	CodeExporter* ce = celedsexporterb->createExporter(L"C.xml");

	wstring code = ce->generateCode(model);

	wofstream wofs(argv[2]);
        wofs << code;

	cout << "File " << argv[2] << " created." <<endl;
	return 0;
}
