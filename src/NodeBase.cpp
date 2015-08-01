#include "NodeBase.h"
#include "FunTools.h"
#include <iostream>
#include <algorithm>

using namespace std;
namespace arise
{
	/*!
	* \fn void Rpath(const tree<HTML::Node > &tDom);
	* \brief  由迭代器求Rpath
	* \param  [in]DOM树
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
		transform(sTagName.begin(), sTagName.end(), sTagName.begin(), ::tolower);//转换为小写
		while(sTagName != "body" )
		{
			this->m_lRpath.push_front(tTmpIter->tagName () );//存储仍为原树上的
			tTmpIter = tDom.parent(tTmpIter);
			sTagName = tTmpIter->tagName();
			transform(sTagName.begin(), sTagName.end(), sTagName.begin(), ::tolower);
		}

		this->m_lRpath.push_front(tTmpIter->tagName() );//存储仍为原树上的
	}



	/*!
	* \fn void Ipath(const tree<HTML::Node > &tDom);
	* \brief  由迭代器求Ipath
	* \param  [in]DOM树
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
		this->m_lIpath.push_front(make_pair(tSonIter->tagName(), 1) );//存储仍为原树上的
	}



	/*!
	* \fn const list< pair <string, int> > & ReadIpath() const;
	* \brief  读取节点的Ipath，只读
	* \param  void
	* \return 节点Ipath的引用
	* \date   2011-06-01 
	* \author nanjunxiao
	*/
	const list< pair <string, int> > & NodeBase::ReadIpath() const
	{
		return this->m_lIpath;
	}

	

	/*!
	* \fn list <string> & ReadRpath();
	* \brief  读取节点的Rpath,可修改
	* \param  void
	* \return 节点Rpath的引用
	* \date   2011-06-01 
	* \author nanjunxiao
	*/
	list<string> & NodeBase::ReadRpath()//要修改
	{
		return this->m_lRpath;
	}
	
	


	/*!
	* \fn bool RpathIsEqual(const NodeBase &Other) const;
	* \brief  判断节点的Rpath是否相同
	* \param  [in]另一个NodeBase
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
	* \brief  判断节点的Ipath是否相同
	* \param  [in]另一个节点
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
	* \brief  统计节点字符数
	* \param  [in]DOM树
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
	* \brief  读取节点字符数，只读
	* \param  void
	* \return int，节点字符数
	* \date   2011-06-01 
	* \author nanjunxiao
	*/
	int NodeBase::ReadNodeChars() const
	{
		return this->m_iCountOfChars;
	}



	/*!
	* \fn bool operator== (const NodeBase &Other) const;
	* \brief  重载==
	* \param  [in]另一个节点
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
	* \brief  寻找两节点的最小公共结构体
	* \param  [in]DOM树
	* \param  [in]另一个节点
	* \return 该节点的引用
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
	* \brief  由Ipath确定迭代器（更新）
	* \param  [in]DOM树
	* \return 具有该Ipath的节点对应DOM树的迭代器
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
		//tree<HTML::Node>::iterator tFatherIter = tDom.begin(); //即为body
		//tree<HTML::Node>::iterator tSonIter = tDom.begin();
		//list< pair<string, int> >::iterator lIter = this->m_lIpath.begin();
		//if (tFatherIter->tagName() != lIter->first)//前建立body子树已考虑，所以此处应该不会出现该情况
		//{
		//	cerr << "NodeBase::IpathToIterator 断言失败，输入页面无body标签" << endl;
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
	* \brief  判断该节点是否为另一个的孩子
	* \param  [in]另一个节点
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
	* \fn void RpathToIterator(const tree<HTML::Node> &tDom, vector<tree<HTML::Node>::iterator > &vecIters);//抽取同类网页时使用
	* \brief  由Rpath确定迭代器
	* \param  [in]DOM树
	* \param  [out]具有该Rpath的迭代器向量
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
		//if (sTagName != "body")//前建立body子树已考虑，所以此处应该不会出现该情况
		//{
		//	cerr << "NodeBase::RathToIterator 待抽取页面无body节点" << endl;
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
		for (; lIter != this->m_lRpath.end(); ++lIter)//rpath循环
		{
			vecFatherIters = vecIters;
			vecIters.clear();
			for (vector<tree<HTML::Node>::iterator >::iterator vIter = vecFatherIters.begin();
				vIter != vecFatherIters.end(); ++vIter)//父节点循环
			{
				int iNumOfChildren = tDom.number_of_children(*vIter);
				for (int i = 0; i < iNumOfChildren; i++)//父节点下层孩子循环
				{
					tSonIter = tDom.child(*vIter, i);
					if (tSonIter->tagName() == (*lIter) )
					{
						vecIters.push_back(tSonIter);
					}
				}
			}
		}//至此nodeitervec即为iter集合
	}



	/*!
	* \fn bool operator < (const NodeBase &Other) const;
	* \brief  重载<
	* \param  [in]另一个节点
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
