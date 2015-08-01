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
* \brief  元搜索抽取接口函数
* \param  [in]待抽取网页存储字符串
* \param  [in]是否用htmltidy修复标签
* \param  [out]抽取结果元信息向量
* \return 自定义错误码，定位错误位置：==0抽取正确，<0抽取失败
* \date   2011-06-01 
* \author nanjunxiao
*/
arise_ErrorCode ExtractMetaSearchResult(const char *pcContent, bool bTidyNeeded, vector<_stMetaSearchResult> &vstResult)
{
	if ( (pcContent == NULL) || (strlen(pcContent) == 0) )
	{
		//cerr << "ExtractMetaSearchResult 输入页面为空" << endl;
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
				//throw "ExtractMetaSearchResult TidyHtml失败！";
				return arise_E_TidyHtml_Failed;
			}

			Pretreat::EraseBaiduAD(sContent);//后针对百度添加

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

			Pretreat::EraseBaiduAD(sContent);//后针对百度添加

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