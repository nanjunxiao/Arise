#include "Interface.h"
#include "htmlcxx/ParserDom.h"
#include "Pretreat.h"
#include "ExtractWithoutWrapper.h"
#include <iostream>

using namespace std;
using namespace htmlcxx;
using namespace arise;


/*!
* \fn arise_ErrorCode ExtractMetaSearchResult(const char *pcContent, bool bTidyNeeded, vector<_stMetaSearchResult> &vstResult);
* \brief  Ԫ������ȡ�ӿں���
* \param  [in]����ȡ��ҳ�洢�ַ���
* \param  [in]�Ƿ���htmltidy�޸���ǩ
* \param  [out]��ȡ���Ԫ��Ϣ����
* \return �Զ�������룬��λ����λ�ã�==0��ȡ��ȷ��<0��ȡʧ��
* \date   2011-06-01 
* \author nanjunxiao
*/
arise_ErrorCode ExtractMetaSearchResult(const char *pcContent, bool bTidyNeeded, vector<_stMetaSearchResult> &vstResult)
{
	if ( (pcContent == NULL) || (strlen(pcContent) == 0) )
	{
		//cerr << "ExtractMetaSearchResult ����ҳ��Ϊ��" << endl;
		return arise_E_ExtractMetaSearchResult_InputIsNull;
	}

	//bool bReturnCode = false;
	bool bGenerateSubTreeCode = false;
	arise_ErrorCode ariseReturnCode = arise_E_OK;
	HTML::ParserDom parser;

	try
	{
		if (bTidyNeeded)
		{
			string sContent;
			int iTidyHtmlCode = -1;

			iTidyHtmlCode = Pretreat::TidyHtml(pcContent, sContent);
			if (iTidyHtmlCode < 0)
			{
				//throw "ExtractMetaSearchResult TidyHtmlʧ�ܣ�";
				return arise_E_TidyHtml_Failed;
			}

			Pretreat::EraseBaiduAD(sContent);//����԰ٶ����

			/*string sBody = Pretreat::SubStringBody(sContent);
			if (sBody.empty() )
				return arise_E_SubStringBody_Failed;

			tree<HTML::Node> tBodyDom = parser.parseTree(sBody);*/

			tree<HTML::Node> tHtmlDom = parser.parseTree(sContent);
			tree<HTML::Node> tBodyDom;
			
			bGenerateSubTreeCode = Pretreat::GenerateSubTree(tHtmlDom, "body", tBodyDom);
			if (bGenerateSubTreeCode == false)
				return arise_E_GenerateSubTree_Failed;

			Pretreat::CleanUpFormTag(tBodyDom);

			ExtractWithoutWrapper oEWW;
			ariseReturnCode = oEWW.ExtractRecords(tBodyDom, vstResult);
		}
		else
		{
			string sContent(pcContent);

			Pretreat::EraseBaiduAD(sContent);//����԰ٶ����

			/*string sBody = Pretreat::SubStringBody(sContent);
			if (sBody.empty() )
				return arise_E_SubStringBody_Failed;

			tree<HTML::Node> tBodyDom = parser.parseTree(sBody);*/
			
			tree<HTML::Node> tHtmlDom = parser.parseTree(sContent);
			tree<HTML::Node> tBodyDom;
			
			bGenerateSubTreeCode = Pretreat::GenerateSubTree(tHtmlDom, "body", tBodyDom);
			if (bGenerateSubTreeCode == false)
				return arise_E_GenerateSubTree_Failed;

			Pretreat::CleanUpFormTag(tBodyDom);
		
			ExtractWithoutWrapper oEWW;
			ariseReturnCode = oEWW.ExtractRecords(tBodyDom, vstResult);
		}
	}
	catch(exception &e)
	{
		//cerr << "ExtractMetaSearchResult: " << e.what() << endl;
		ariseReturnCode = arise_E_ExtractMetaSearchResult_Exception;
	}
	catch(...)
	{
		//cerr << "ExtractMetaSearchResult: Unknown error !" << endl;
		ariseReturnCode = arise_E_ExtractMetaSearchResult_UnknownError;
	}

	return ariseReturnCode;
}