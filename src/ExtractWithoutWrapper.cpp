#include "ExtractWithoutWrapper.h"
#include "NodeBase.h"
#include "AttributeExtract.h"
#include <vector>
#include <iostream>

using namespace std;
namespace arise
{
	/*!
	* \fn arise_ErrorCode ExtractRecords(const tree<HTML::Node> &tBodyDom, vector<_stMetaSearchResult> &vstResult);
	* \brief  withoutwrapper抽取记录属性
	* \param  [in]DOM树
	* \param  [out]全局元信息结构体向量
	* \return 自定义返回码：==arise_E_OK抽取OK，<0抽取失败
	* \date   2011-06-01 
	* \author nanjunxiao
	*/
	arise_ErrorCode ExtractWithoutWrapper::ExtractRecords(const tree<HTML::Node> &tBodyDom, vector<_stMetaSearchResult> &vstResult)
	{	
		arise_ErrorCode ariseReturnCode = arise_E_OK;
		ariseReturnCode = this->Extract(tBodyDom);
		if (ariseReturnCode < 0)
		{
			//cerr << "ExtractWithoutWrapper::ExtractRecords Extract错误" << endl;
			return ariseReturnCode;
		}

		//用信息结构体的第一个元素找父节点
		if (this->ReadInfoStruct().empty() )
		{
			//cerr << "ExtractWithoutWrapper::ExtractRecords 信息结构体为空" << endl;
			return arise_E_InfoStructIsEmpty;
		}
		tree<HTML::Node>::iterator tFatherIter = tBodyDom.parent(this->ReadInfoStruct().begin()->m_tIter );
		int iCountOfSon = tBodyDom.number_of_children(tFatherIter);
		NodeBase nodeSon;
		tree<HTML::Node>::iterator tSonIter;

		long ivstResultBeg = vstResult.size();//vstResult初始结构体个数
		AttributeExtract AttEt;	
		if (this->ReadInfoStruct().size() == iCountOfSon)//貌似没有这种情况，多少都有一些其他兄弟节点
		{
			for (int i = 0; i< iCountOfSon; ++i)
			{
				tSonIter = tBodyDom.child(tFatherIter, i);
				nodeSon.m_tIter = tSonIter;
				AttEt.ParseAttributes(tBodyDom, nodeSon, vstResult);
				
			}
		}
		if (this->ReadInfoStruct().size()  < iCountOfSon)
		{
			//只进行扩展(第一个最后一个节点，以及它们之间的)
			int iBeg = iCountOfSon - tBodyDom.number_of_siblings(this->ReadInfoStruct().begin()->m_tIter ) - 1;
			vector <NodeBase>::const_iterator vInfoIter = this->ReadInfoStruct().end();
			--vInfoIter;
			int iEnd = iCountOfSon - tBodyDom.number_of_siblings(vInfoIter->m_tIter) - 1;
			for (int i = iBeg; i <= iEnd; ++i)
			{
				tSonIter = tBodyDom.child(tFatherIter, i);
				nodeSon.m_tIter = tSonIter;
				AttEt.ParseAttributes(tBodyDom, nodeSon, vstResult);
			}
		}

		long ivstResultEnd = vstResult.size();//一片网页结束后vstResult结构体个数
		if (ivstResultEnd <= ivstResultBeg )
		{
			return arise_E_OnePageAttIsBlank;
		}

		//写成内部成员也可
		//OnePageAttToGlobal(AttEt,vstResult);
		
		//测试用
		/*ofstream ofs("../bin/result/googledizhen.txt");
		if(!ofs.is_open())
		{
			cerr << "../bin/chairesult/googlecmake.txt" << endl;
			exit(1);
		}
		AttEt.WriteFile(ofs);
		ofs.close();*/

		return ariseReturnCode;
	}
}