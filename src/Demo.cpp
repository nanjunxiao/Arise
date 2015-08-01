#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <sstream>
#include "Interface.h"


using namespace std;
//using namespace arise;


void ReadPage(const string &path, string &html)
{
	ifstream ifs(path.c_str());
	if(!ifs.is_open())
	{
		cerr << path << " file open failed!" << endl;
		exit(1);
	}
	stringstream ssm;
	ssm<<ifs.rdbuf();
	html=ssm.str();
	ifs.close();
}

void WriteFile(ofstream &ofs, vector <_stMetaSearchResult> &vstResult) 
{
	for (vector<_stMetaSearchResult>::iterator vIter = vstResult.begin();
		vIter != vstResult.end(); ++vIter)
	{
		/*ofs << "标题： " << vIter->title << endl;
		ofs << "链接： " << vIter->url << endl;
		ofs << "摘要： " << vIter->snippet<< endl;*/
		ofs << "1. " << vIter->title << endl;
		ofs << "2. " << vIter->url << endl;
		ofs << "3. " << vIter->snippet<< endl;
		ofs << endl << endl;
	}
}

int main(int argc, char **argv)
{
	int i;
	string sTidy, sInPage, sRes;

/*	for (i=0; i<argc; i++) 
	{
		cout << "argv[" << i << "]=" << argv[i] <<"\n" ;
	}
*/
	i = 1;
	sTidy = "";
	sInPage = "";
	sRes = "";

	if ((argc==1) || ((argc==2) && (strcmp(argv[i], "--help")==0)))
	{
		//"_Arise"
		//"_Arise --help"

		cout << "\n" << argv[0] << " \n";
		cout << "-------------------------------------------------------------\n"<<endl;
		cout << "Description:\n";
		cout << argv[0] << " is a tool for extracting infomation from retrieval results of search engine. ";
		cout << "For each retrieving record, the information such as title and URL and snippet can be extracted.\n";
		cout << "-------------------------------------------------------------\n"<<endl;
		cout << "Usage:\n\n";
		cout << argv[0];
		cout << " --tidy <tidyoption: 0|1|default> --inpage <pagepath> --outres <resultpath>\n"<<endl;
		cout <<	"Where: tidyoption--whether tidy html or not. 0: not tidy,1: tidy,default: not tidy\n";
		cout <<	"       inpage--path of the same seach engine's page\n";
		cout <<	"       outres--saved path of extracted result\n" << endl;
		cout << "-------------------------------------------------------------\n"<<endl;

		return 0;

	}else if ((argc == 7) && (strcmp(argv[i], "--tidy")==0) && (strcmp(argv[i+2], "--inpage")==0) && (strcmp(argv[i+4], "--outres")==0))
	{
		//_Arise --tidy <0|1|default> --inpage <pagepath> --outres <result path>

		sTidy = argv[i+1];
		sInPage = argv[i+3];
		sRes = argv[i+5];

	}else
	{
		cout << "The arguments are wrong! Using \"--help\" can get the help message. \n";
		return 1;
	}
	
	string sPage;
	ReadPage(sInPage, sPage);
	const char *pcContent = sPage.c_str();

	vector <_stMetaSearchResult> vstResult;
	clock_t tBeg = clock();

	//tidy与否？
	bool bTidyNeeded = false;//默认false
	switch(atoi(sTidy.c_str()) )
	{
	case 0:
		bTidyNeeded = false;break;
	case 1:
		bTidyNeeded = true;break;
	default:
		bTidyNeeded = false;
	}

	arise_ErrorCode ariseReturnCode = ExtractMetaSearchResult(pcContent, bTidyNeeded, vstResult);
	if (ariseReturnCode == 0)
	{
		cout << "ExtracMetaSearchResult extract OK" << endl;

		ofstream ofs(sRes.c_str());
		if(!ofs.is_open())
		{
			cerr << sRes.c_str() << "write failed !" << endl;
			exit(1);
		}
		WriteFile(ofs, vstResult);
		ofs.close();
	}
	else
	{
		cerr << "ExtracMetaSearchResult extract failed!" << endl;
		cerr << "ErrorCode: " << ariseReturnCode << endl;
		return 1;
	}
	cout << "Extracting without wrapper takes: " << (double)(clock() - tBeg) / CLOCKS_PER_SEC << " seconds" << endl;
	return 0;
}
