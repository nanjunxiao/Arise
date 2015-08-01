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
	* \brief  withoutwrapper��ȡ��¼����
	* \param  [in]DOM��
	* \param  [out]ȫ��Ԫ��Ϣ�ṹ������
	* \return �Զ��巵���룺==arise_E_OK��ȡOK��<0��ȡʧ��
	* \date   2011-06-01 
	* \author nanjunxiao
	*/
	arise_ErrorCode ExtractWithoutWrapper::ExtractRecords(const tree<HTML::Node> &tBodyDom, vector<_stMetaSearchResult> &vstResult)
	{	
		arise_ErrorCode ariseReturnCode = arise_E_OK;
		ariseReturnCode = this->Extract(tBodyDom);
		if (ariseReturnCode < 0)
		{
			//cerr << "ExtractWithoutWrapper::ExtractRecords Extract����" << endl;
			return ariseReturnCode;
		}

		//����Ϣ�ṹ��ĵ�һ��Ԫ���Ҹ��ڵ�
		if (this->ReadInfoStruct().empty() )
		{
			//cerr << "ExtractWithoutWrapper::ExtractRecords ��Ϣ�ṹ��Ϊ��" << endl;
			return arise_E_InfoStructIsEmpty;
		}
		tree<HTML::Node>::iterator tFatherIter = tBodyDom.parent(this->ReadInfoStruct().begin()->m_tIter );
		int iCountOfSon = tBodyDom.number_of_children(tFatherIter);
		NodeBase nodeSon;
		tree<HTML::Node>::iterator tSonIter;

		long ivstResultBeg = vstResult.size();//vstResult��ʼ�ṹ�����
		AttributeExtract AttEt;	
		if (this->ReadInfoStruct().size() == iCountOfSon)//ò��û��������������ٶ���һЩ�����ֵܽڵ�
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
			//ֻ������չ(��һ�����һ���ڵ㣬�Լ�����֮���)
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

		long ivstResultEnd = vstResult.size();//һƬ��ҳ������vstResult�ṹ�����
		if (ivstResultEnd <= ivstResultBeg )
		{
			return arise_E_OnePageAttIsBlank;
		}

		//д���ڲ���ԱҲ��
		//OnePageAttToGlobal(AttEt,vstResult);
		
		//������
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