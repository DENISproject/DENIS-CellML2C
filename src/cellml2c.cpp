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
        cout << "Bootstrap created" << endl;
	DOMModelLoader* ml = bootstrap->modelLoader();
        cout << "ModelLoader created" << endl;
	Model* model = ml->loadFromURL(wide);
	cout << "Model loaded from URL" << endl;

	CeLEDSExporterBootstrap* celedsexporterb = CreateCeLEDSExporterBootstrap();
        cout << "CeLEDSExproterBootestrap created" << endl;

	CodeExporter* ce = celedsexporterb->createExporter(L"C.xml");
        cout << "Exporter created" << endl;

	wstring code = ce->generateCode(model);
	cout << "Code generated" << endl;

	wofstream wofs(argv[2]);
        wofs << code;

	cout << "File " << argv[2] << " created." <<endl;
	return 0;
}
