#include "NodeBase.h"
#include "FunTools.h"
#include <iostream>
#include <algorithm>

using namespace std;
namespace arise
{
	/*!
	* \fn void Rpath(const tree<HTML::Node > &tDom);
	* \brief  �ɵ�������Rpath
	* \param  [in]DOM��
	* \param  [out]this->m_lRpath
	* \return void
	* \date   2011-06-01 
	* \author nanjunxiao
	*/
	void NodeBase::Rpath(const tree<HTML::Node> &tDom)
	{
		this->m_lRpath.clear();
		tree <HTML::Node>::iterator tTmpIter = this->m_tIter;
		string sTagName = tTmpIter->tagName();
		transform(sTagName.begin(), sTagName.end(), sTagName.begin(), ::tolower);//ת��ΪСд
		while(sTagName != "body" )
		{
			this->m_lRpath.push_front(tTmpIter->tagName () );//�洢��Ϊԭ���ϵ�
			tTmpIter = tDom.parent(tTmpIter);
			sTagName = tTmpIter->tagName();
			transform(sTagName.begin(), sTagName.end(), sTagName.begin(), ::tolower);
		}

		this->m_lRpath.push_front(tTmpIter->tagName() );//�洢��Ϊԭ���ϵ�
	}



	/*!
	* \fn void Ipath(const tree<HTML::Node > &tDom);
	* \brief  �ɵ�������Ipath
	* \param  [in]DOM��
	* \param  [out]this->m_lIpath
	* \return void
	* \date   2011-06-01 
	* \author nanjunxiao
	*/
	void NodeBase::Ipath(const tree<HTML::Node> &tDom)
	{
		this->m_lIpath.clear();
		tree<HTML::Node>::iterator tSonIter = this->m_tIter;
		string sTagName = tSonIter->tagName();
		transform(sTagName.begin(), sTagName.end(), sTagName.begin(), ::tolower);
		tree<HTML::Node>::iterator tFatherIter = this->m_tIter;
		int iPos = 0;
		while(sTagName != "body")
		{
			tFatherIter = tDom.parent(tSonIter);
			iPos = tDom.index(tSonIter);
			this->m_lIpath.push_front ( make_pair(tSonIter->tagName(), iPos+1) );
			tSonIter = tFatherIter;
			sTagName = tSonIter->tagName();
			transform(sTagName.begin(), sTagName.end(), sTagName.begin(), ::tolower);
		}
		this->m_lIpath.push_front(make_pair(tSonIter->tagName(), 1) );//�洢��Ϊԭ���ϵ�
	}



	/*!
	* \fn const list< pair <string, int> > & ReadIpath() const;
	* \brief  ��ȡ�ڵ��Ipath��ֻ��
	* \param  void
	* \return �ڵ�Ipath������
	* \date   2011-06-01 
	* \author nanjunxiao
	*/
	const list< pair <string, int> > & NodeBase::ReadIpath() const
	{
		return this->m_lIpath;
	}

	

	/*!
	* \fn list <string> & ReadRpath();
	* \brief  ��ȡ�ڵ��Rpath,���޸�
	* \param  void
	* \return �ڵ�Rpath������
	* \date   2011-06-01 
	* \author nanjunxiao
	*/
	list<string> & NodeBase::ReadRpath()//Ҫ�޸�
	{
		return this->m_lRpath;
	}
	
	


	/*!
	* \fn bool RpathIsEqual(const NodeBase &Other) const;
	* \brief  �жϽڵ��Rpath�Ƿ���ͬ
	* \param  [in]��һ��NodeBase
	* \return bool
	* \date   2011-06-01 
	* \author nanjunxiao
	*/
	bool NodeBase::RpathIsEqual(const arise::NodeBase &Other) const
	{
		if (this->m_lRpath == Other.m_lRpath)
		{
			return true;
		}
		else
		{
			return false;
		}
	}



	/*!
	* \fn bool IpathIsEqual(const NodeBase &Other) const;
	* \brief  �жϽڵ��Ipath�Ƿ���ͬ
	* \param  [in]��һ���ڵ�
	* \return bool
	* \date   2011-06-01 
	* \author nanjunxiao
	*/
	bool NodeBase::IpathIsEqual(const arise::NodeBase &Other) const
	{
		if (this->m_lIpath == Other.m_lIpath)
		{
			return true;
		}
		else
		{
			return false;
		}
	}



	/*!
	* \fn void CountNodeChars(const tree<HTML::Node > &tDom) ;
	* \brief  ͳ�ƽڵ��ַ���
	* \param  [in]DOM��
	* \param  [out]this->m_iCountOfChars
	* \return void
	* \date   2011-06-01 
	* \author nanjunxiao
	*/
	void NodeBase::CountNodeChars(const tree<HTML::Node> &tDom) 
	{
		int iCount = 0;
		tree <HTML::Node> tSubDom;
		Pretreat::GenerateSubTree(tDom, this->m_tIter, tSubDom);
		tree<HTML::Node>::iterator tSubIter = tSubDom.begin();
		string sTextTmp;
		for (; tSubIter != tSubDom.end(); ++tSubIter)
		{
			if (!tSubIter->isComment() && !tSubIter->isTag()  )
			{
				sTextTmp = tSubIter->text();
				ReplaceSpecialSymbols(sTextTmp);
				EraseBlank(sTextTmp);
				iCount += sTextTmp.length();
				//iCount += tSubIter->text().length ();
			}
		}
		this->m_iCountOfChars = iCount;
	}



	/*!
	* \fn int ReadNodeChars() const;
	* \brief  ��ȡ�ڵ��ַ�����ֻ��
	* \param  void
	* \return int���ڵ��ַ���
	* \date   2011-06-01 
	* \author nanjunxiao
	*/
	int NodeBase::ReadNodeChars() const
	{
		return this->m_iCountOfChars;
	}



	/*!
	* \fn bool operator== (const NodeBase &Other) const;
	* \brief  ����==
	* \param  [in]��һ���ڵ�
	* \return bool
	* \date   2011-06-01 
	* \author nanjunxiao
	*/
	bool NodeBase::operator ==(const arise::NodeBase &Other) const
	{
		return this->m_tIter == Other.m_tIter && this->m_lRpath == Other.m_lRpath
				&& this->m_lIpath == Other.m_lIpath;
	}



	/*!
	* \fn NodeBase & FindMinStruct(const tree<HTML::Node > &tDom,  NodeBase &Other);
	* \brief  Ѱ�����ڵ����С�����ṹ��
	* \param  [in]DOM��
	* \param  [in]��һ���ڵ�
	* \return �ýڵ������
	* \date   2011-06-01 
	* \author nanjunxiao
	*/
	NodeBase & NodeBase::FindMinStruct(const tree<HTML::Node> &tDom, arise::NodeBase &Other)
	{
		list<pair<string,int> >::iterator lThisIter = this->m_lIpath.begin();
		list<pair<string,int> >::iterator lOtherIter = Other.m_lIpath.begin();

		for (; lThisIter != this->m_lIpath.end() && lOtherIter != Other.m_lIpath.end(); ++lThisIter,++lOtherIter)
		{
			if (lThisIter->first != lOtherIter->first || lThisIter->second != lOtherIter->second)
				break;
		}

		if (lThisIter != this->m_lIpath.end() )
		{
			this->m_lIpath.erase(lThisIter, this->m_lIpath.end() );
		}
		
		this->m_tIter = this->IpathToIterator(tDom);
		this->Rpath(tDom);
		return *this;
	}



	/*!
	* \fn tree<HTML::Node>::iterator IpathToIterator(const tree<HTML::Node > &tDom);
	* \brief  ��Ipathȷ�������������£�
	* \param  [in]DOM��
	* \return ���и�Ipath�Ľڵ��ӦDOM���ĵ�����
	* \date   2011-06-01 
	* \author nanjunxiao
	*/
	tree<HTML::Node>::iterator NodeBase::IpathToIterator(const tree<HTML::Node> &tDom)
	{
		tree<HTML::Node>::iterator tFatherIter = tDom.begin();
		tree<HTML::Node>::iterator tSonIter = tDom.begin();
		string sTagName;
		for (; tFatherIter != tDom.end(); ++tFatherIter)
		{
			if (tFatherIter->isTag() )
			{
				sTagName = tFatherIter->tagName();
				transform(sTagName.begin(), sTagName.end(), sTagName.begin(), ::tolower);
				if (sTagName == "body")
					break;
			}
		}
		//tree<HTML::Node>::iterator tFatherIter = tDom.begin(); //��Ϊbody
		//tree<HTML::Node>::iterator tSonIter = tDom.begin();
		//list< pair<string, int> >::iterator lIter = this->m_lIpath.begin();
		//if (tFatherIter->tagName() != lIter->first)//ǰ����body�����ѿ��ǣ����Դ˴�Ӧ�ò�����ָ����
		//{
		//	cerr << "NodeBase::IpathToIterator ����ʧ�ܣ�����ҳ����body��ǩ" << endl;
		//}
		if (tFatherIter == tDom.end() )
		{
			cerr << "NodeBase::IpathToIterator  input page has no body tag!" << endl;
		}
		list< pair<string, int> >::iterator lIter = this->m_lIpath.begin();
		++ lIter;
		for (; lIter != this->m_lIpath.end(); ++lIter)
		{
			tSonIter = tDom.child(tFatherIter, lIter->second - 1);
			tFatherIter = tSonIter;
		}
		return tFatherIter;

	}


	

	/*!
	* \fn bool IsSon(const NodeBase &Other) const;
	* \brief  �жϸýڵ��Ƿ�Ϊ��һ���ĺ���
	* \param  [in]��һ���ڵ�
	* \return bool
	* \date   2011-06-01 
	* \author nanjunxiao
	*/
	bool NodeBase::IsSon(const NodeBase &Other) const
	{
		if (this->m_lIpath.size() <= Other.m_lIpath.size() ) // Quick Compare
		{
			return false;
		}
		else
		{
			list< pair<string,int> >::const_iterator lThisIter = this->m_lIpath.begin();
			list< pair<string,int> >::const_iterator lOtherIter = Other.m_lIpath.begin();
			for (; lOtherIter != Other.m_lIpath.end(); ++lThisIter, ++lOtherIter)
			{
				if (lThisIter->first != lOtherIter->first || lThisIter->second != lOtherIter->second)
				{
					return false;
				}
			}
			return true;
		}
	}
	



	/*!
	* \fn void RpathToIterator(const tree<HTML::Node> &tDom, vector<tree<HTML::Node>::iterator > &vecIters);//��ȡͬ����ҳʱʹ��
	* \brief  ��Rpathȷ��������
	* \param  [in]DOM��
	* \param  [out]���и�Rpath�ĵ���������
	* \return void
	* \date   2011-06-01 
	* \author nanjunxiao
	*/
	void NodeBase::RpathToIterator(const tree<HTML::Node> &tDom, vector<tree<HTML::Node>::iterator > &vecIters) 
	{
		tree<HTML::Node>::iterator tBodyIter = tDom.begin();
		string sTagName;
		for (; tBodyIter != tDom.end(); ++tBodyIter)
		{
			if (tBodyIter->isTag() )
			{
				sTagName = tBodyIter->tagName();
				transform(sTagName.begin(), sTagName.end(), sTagName.begin(), ::tolower);
				if (sTagName == "body")
					break;
			}
		}
		//string sTagName = tDom.begin()->tagName();
		//transform(sTagName.begin(), sTagName.end(), sTagName.begin(), tolower);
		//if (sTagName != "body")//ǰ����body�����ѿ��ǣ����Դ˴�Ӧ�ò�����ָ����
		//{
		//	cerr << "NodeBase::RathToIterator ����ȡҳ����body�ڵ�" << endl;
		//	return ;
		//}
		if (tBodyIter == tDom.end() )
		{
			cerr << "NodeBase::RathToIterator the page to be extracted has no body tag!" << endl;
			return ;
		}
		vecIters.push_back(tBodyIter);
		vector<tree<HTML::Node>::iterator > vecFatherIters;
		
		list<string>::iterator lIter = this->m_lRpath.begin();
		++lIter;
		if (lIter == this->m_lRpath.end() )
		{
			cerr << "NodeBase::RathToIterator  Rpath length is one" << endl;
			return ;
		}
		tree<HTML::Node>::iterator tSonIter;
		for (; lIter != this->m_lRpath.end(); ++lIter)//rpathѭ��
		{
			vecFatherIters = vecIters;
			vecIters.clear();
			for (vector<tree<HTML::Node>::iterator >::iterator vIter = vecFatherIters.begin();
				vIter != vecFatherIters.end(); ++vIter)//���ڵ�ѭ��
			{
				int iNumOfChildren = tDom.number_of_children(*vIter);
				for (int i = 0; i < iNumOfChildren; i++)//���ڵ��²㺢��ѭ��
				{
					tSonIter = tDom.child(*vIter, i);
					if (tSonIter->tagName() == (*lIter) )
					{
						vecIters.push_back(tSonIter);
					}
				}
			}
		}//����nodeitervec��Ϊiter����
	}



	/*!
	* \fn bool operator < (const NodeBase &Other) const;
	* \brief  ����<
	* \param  [in]��һ���ڵ�
	* \return bool
	* \date   2011-06-01 
	* \author nanjunxiao
	*/
	bool NodeBase::operator < (const NodeBase &Other) const
	{
		return this->m_lIpath < Other.m_lIpath 
				|| (this->m_lIpath == Other.m_lIpath && this->m_lRpath < Other.m_lRpath);
	}


}
