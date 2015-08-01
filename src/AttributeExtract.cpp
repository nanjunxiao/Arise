#include "AttributeExtract.h"
#include "FunTools.h"

using namespace std;
namespace arise
{
	/*!
	* \fn void ParseAttributes(const tree<HTML::Node> &tDom, const NodeBase &nodeInfoStruct ,vector<_stMetaSearchResult> &vstResult);
	* \brief  解析信息结构体三个属性
	* \param  [in]DOM树
	* \param  [in]信息结构体节点
	* \param  [out]Interface中的结构体向量
	* \return void
	* \date   2011-06-01 
	* \author nanjunxiao
	*/
	void AttributeExtract::ParseAttributes(const tree<HTML::Node> &tDom, const arise::NodeBase &nodeInfoStruct ,vector<_stMetaSearchResult> &vstResult)
	{
		tree<HTML::Node> tSubDom;
		Pretreat::GenerateSubTree(tDom, nodeInfoStruct.m_tIter, tSubDom);

		tree<HTML::Node>::iterator tIter = tSubDom.begin();
		while(tIter != tSubDom.end() )
		{
			if (tIter->tagName() == "a" || tIter->tagName() == "A")
			{
				break;
			}
			else
			{
				++tIter;
			}
		}
		if (tIter == tSubDom.end() )
		{
			//cerr << "AttributeExtract::ParseAttributes  记录中没有<a>/<A>标签，算法无法处理" << endl;
			return ;
		}
		_stMetaSearchResult OneResult;
		
		tIter->parseAttributes();
		OneResult.url = tIter->attribute("href").second;//自带转小写

		//标签a的子树，找title
		tree<HTML::Node> tADom;
		Pretreat::GenerateSubTree(tSubDom, tIter, tADom);
		
		//tag a之前也有标题成分
		string sTextTmp;
		for (tree<HTML::Node>::iterator tTmpIter = tSubDom.begin(); tTmpIter != tIter; ++tTmpIter)
		{
			if (!tTmpIter->isComment() && !tTmpIter->isTag()  )
			{
				sTextTmp = tTmpIter->text();
				ReplaceSpecialSymbols(sTextTmp);
				EraseBlank(sTextTmp);
				OneResult.title += sTextTmp;
			}
		}

		for (tree<HTML::Node>::iterator tAIter = tADom.begin(); tAIter != tADom.end(); ++tAIter)
		{
			if (!tAIter->isComment() && !tAIter->isTag()  )
			{
				sTextTmp = tAIter->text();
				ReplaceSpecialSymbols(sTextTmp);
				EraseBlank(sTextTmp);
				OneResult.title += sTextTmp;
			}
		}//title ok

		//减法找abstract
		string sRecord;
		
		for (tIter = tSubDom.begin(); tIter != tSubDom.end(); ++tIter)
		{
			if (!tIter->isComment() && !tIter->isTag()  )
			{
				sTextTmp = tIter->text() ;
				ReplaceSpecialSymbols(sTextTmp);
				EraseBlank(sTextTmp);
				sRecord += sTextTmp;
			}
		}
		OneResult.snippet = sRecord.substr(OneResult.title.length(), sRecord.length() - OneResult.title.length() );//摘要
		//this->m_OnePageAttributes.push_back(OneResult);
		vstResult.push_back(OneResult);
		//return arise_E_OK;
	}



	/*void OnePageAttToGlobal(const AttributeExtract &AttEx, vector<_stMetaSearchResult> &vstResult)
	{
		for (vector<_stMetaSearchResult>::const_iterator vIter = AttEx.m_OnePageAttributes.begin(); 
			vIter != AttEx.m_OnePageAttributes.end(); ++vIter)
		{
			vstResult.push_back(*vIter);
		}
	}*/

	

	/*bool AttributeExtract::IsOnePageAttBlank(void ) const
	{
		return this->m_OnePageAttributes.empty();
	}*/



}