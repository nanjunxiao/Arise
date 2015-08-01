#include "FunTools.h"
#include "ExtractBase.h"


#include <iostream>
#include <set>
#include <fstream>

using namespace std;
namespace arise
{

	/*!
	* \fn arise_ErrorCode Extract(const tree<HTML::Node> &tDom);
	* \brief  抽取基类主函数，一直抽取到信息结构体
	* \param  [in]DOM树
	* \return 自定义返回码
	* \date   2011-06-01
	* \author nanjunxiao
	*/
	arise_ErrorCode ExtractBase::Extract(const tree<HTML::Node> &tDom)
	{
		FindAllLinks(tDom, this->m_lAllLinks);
		arise_ErrorCode ariseReturnCode = Group(this->m_lAllLinks, this->m_vvLinkGroups);
		if (ariseReturnCode < 0)
		{
			return ariseReturnCode;
		}
		
		vector <NodeBase> vMinStructs;
		ariseReturnCode = RegionStruct(tDom, this->m_vvLinkGroups, this->m_RegionStruct ,vMinStructs);
		if (ariseReturnCode < 0)
		{
			return ariseReturnCode;
		}

		IdentifyOrderedLinkGroup(tDom, this->m_vvLinkGroups, vMinStructs, this->m_vOrderedLinks);

		IdentifyInfoStruct(tDom);

		return ariseReturnCode;
	}



	/*!
	* \fn void IdentifyInfoStruct(const tree<HTML::Node> &tDom);
	* \brief  由标准链接组确定信息结构体
	* \param  [in]DOM树
	* \param  [out]this->m_vInfoStruct
	* \return void
	* \date   2011-06-01
	* \author nanjunxiao
	*/
	void ExtractBase::IdentifyInfoStruct(const tree<HTML::Node> &tDom)
	{
		NodeBase nodeTmp;
		set < NodeBase > setNodeTmp;//去重，简化后没有结构体分离算法，要排重。
		for (vector<NodeBase>::iterator vIter = this->m_vOrderedLinks.begin(); vIter != this->m_vOrderedLinks.end(); ++vIter)
		{
			nodeTmp = MaxFather(tDom, *vIter, this->m_RegionStruct);//出问题没法保证后续不出问题。
			if (setNodeTmp.find(nodeTmp) == setNodeTmp.end() )
			{
				setNodeTmp.insert(nodeTmp);
				this->m_vInfoStruct.push_back(nodeTmp);//信息结构体集合=R>4
			}
		}
	}



	/*!
	* \fn NodeBase MaxFather(const tree<HTML::Node> &tDom, const NodeBase &SeparatedResult, const NodeBase &SeparatedRoot) const;
	* \brief  结构体分离结果相对于分离根节点的最大父节点
	* \param  [in]DOM树
	* \param  [in]结构体分离算法分离结果
	* \param  [in]分离根节点：区域结构体/主结构体
	* \return 最大父节点
	* \date   2011-06-01
	* \author nanjunxiao
	*/
	NodeBase ExtractBase::MaxFather(const tree<HTML::Node> &tDom, const arise::NodeBase &SeparatedResult, const arise::NodeBase &SeparatedRoot) const
	{
		NodeBase nodeTmp;
		tree<HTML::Node>::iterator tSonIter = SeparatedResult.m_tIter;
		tree<HTML::Node>::iterator tIter = SeparatedResult.m_tIter;
		try
		{
			while(tIter != SeparatedRoot.m_tIter)
			{
				tSonIter = tIter;
				tIter = tDom.parent(tSonIter);
			}
			nodeTmp.m_tIter = tSonIter;
			nodeTmp.Ipath(tDom);
			nodeTmp.Rpath(tDom);
			return nodeTmp;
		}
		catch(exception &e)
		{
			cerr << "ExtractBase::MaxFather " << e.what() << endl;
			return NodeBase();
		}
		catch(...)
		{
			cerr << "ExtractBase::MaxFather  Unknown Error!" << endl;
			return NodeBase();
		}
		
	}



	/*!
	* \fn const vector<NodeBase> & ReadInfoStruct(void) const;
	* \brief  读取信息结构体，只读
	* \param  void
	* \return 信息结构体引用
	* \date   2011-06-01
	* \author nanjunxiao
	*/
	const vector<NodeBase> & ExtractBase::ReadInfoStruct() const
	{
		return this->m_vInfoStruct;
	}



	/*!
	* \fn void WriteWrapper(const tree<HTML::Node> &tDom, ofstream &ofs);
	* \brief  将标准链接组、信息结构体Rpath写入wrapper
	* \param  [in]DOM树
	* \param  [out]输出文件流
	* \return void
	* \date   2011-06-01
	* \author nanjunxiao
	*/
	void ExtractBase::WriteWrapper(const tree<HTML::Node> &tDom, std::ofstream &ofs)
	{
		/*for (list<string>::iterator lIter = this->m_RegionStruct.ReadRpath().begin(); 
			 lIter != this->m_RegionStruct.ReadRpath().end(); ++lIter)
		{
			ofs << *lIter << "\t";
		}
		ofs << endl;*/
		//ofs << "*****************************" << endl;

		vector<NodeBase>::iterator vIter = this->m_vOrderedLinks.begin();
		for (list<string>::iterator lIter = vIter->ReadRpath().begin();
			 lIter != vIter->ReadRpath().end(); ++lIter)
		{
			ofs << *lIter << "\t";
		}
		ofs << endl;
		//ofs << "*****************************" << endl;

	    vIter = this->m_vInfoStruct.begin();
		for (list<string>::iterator lIter = vIter->ReadRpath().begin();
			 lIter != vIter->ReadRpath().end(); ++lIter)
		{
			ofs << *lIter << "\t";
		}
		ofs << endl;
	}


	
	/*!
	* \fn void FindAllLinks(const tree<HTML::Node> &tDom, list<NodeBase> &lAllLinks);
	* \brief  遍历查找DOM树中的所有链接
	* \param  [in]DOM树
	* \param  [out]this->m_lAllLinks
	* \return void
	* \date   2011-06-01
	* \author nanjunxiao
	*/
	void ExtractBase::FindAllLinks(const tree<HTML::Node> &tDom, list<NodeBase> &lAllLinks)
	{
		tree<HTML::Node>::iterator tIter = tDom.begin();
		NodeBase nodeTmp;
		for(; tIter != tDom.end(); ++tIter)
		{
			if (tIter->tagName() == "a" || tIter->tagName() == "A")
			{
				nodeTmp.m_tIter = tIter;
				nodeTmp.Rpath(tDom);
				nodeTmp.Ipath(tDom);// 三要素信息准备好，应该比构造再析构快

				lAllLinks.push_back(nodeTmp);
			}
		}

	}



	/*!
	* \fn arise_ErrorCode Group(list<NodeBase> lAllLinks, vector<vector<NodeBase> > &vvLinkGroups);
	* \brief  所有链接分组，Rpath相同分为一组
	* \param  [in]所有链接
	* \param  [out]链接组
	* \return 自定义返回码
	* \date   2011-06-01
	* \author nanjunxiao
	*/
	arise_ErrorCode ExtractBase::Group(list<NodeBase> lAllLinks, vector<vector<NodeBase> > &vvLinkGroups)
	{
		if (lAllLinks.empty() )
		{
			//cerr << "GenerateRegionalStruct::Group 输入lAllLinks为空" << endl;
			return arise_E_GroupInputIsEmpty;
		}
		vector <NodeBase> vNodes;
		list<NodeBase>::iterator lIter;
		NodeBase nodeTmp;
		while(lAllLinks.size() > 0)
		{
			vNodes.clear();
			lIter = lAllLinks.begin();
			nodeTmp = *lIter;
			vNodes.push_back(nodeTmp);
			lAllLinks.erase(lIter);
			lIter = lAllLinks.begin();
			while (lIter != lAllLinks.end())
			{
				if (nodeTmp.RpathIsEqual(*lIter) )
				{
					vNodes.push_back(*lIter);
					lAllLinks.erase(lIter);
					lIter = lAllLinks.begin();
				}
				else
				{
					++lIter;
				}
			}
			if (vNodes.size() > 3)
			{
				vvLinkGroups.push_back(vNodes);
			}
		}
		return arise_E_OK;
	}



	
	/*!
	 * \fn void IdentifyOrderedLinkGroup(const tree<HTML::Node> &tDom, 
									const vector<vector<NodeBase> > &vvLinkGroups,
									const vector<NodeBase> &vMinStructs,
									vector<NodeBase> &vOrderedLinks);
	* \brief  识别有序链接组
	* \param  [in]DOM树
	* \param  [in]链接组
	* \param  [in]每个链接组元素的最小父结构
	* \param  [out]有序链接组
	* \return void
	* \date   2011-06-01
	* \author nanjunxiao
	*/
	void ExtractBase::IdentifyOrderedLinkGroup(const tree<HTML::Node> &tDom, 
											   const vector<vector<NodeBase> > &vvLinkGroups,
											   const vector<NodeBase> &vMinStructs,
											   vector<NodeBase> &vOrderedLinks)
	{
		vector <int> vAveLens;
		vector <int> vPos;
		int iAveLen = 0;
		int iCountOfSon = 0;
		tree<HTML::Node>::iterator tSonIter;
		tree<HTML::Node> tSubDomTmp;
		string sTextTmp;
		for (int i = 0; i < vMinStructs.size(); ++i)
		{
			if (vMinStructs[i].ReadIpath() == this->m_RegionStruct.ReadIpath())
			{
				for (vector<NodeBase>::const_iterator vIter = vvLinkGroups[i].begin(); vIter != vvLinkGroups[i].end(); ++vIter)
				{
					tSubDomTmp.clear();
					Pretreat::GenerateSubTree(tDom, vIter->m_tIter, tSubDomTmp);
					if (tSubDomTmp.empty() )
					{
						continue;
					}
						
					for (tree<HTML::Node>::iterator tSubTmp = tSubDomTmp.begin();
						 tSubTmp != tSubDomTmp.end(); ++tSubTmp)
					{
						if (!tSubTmp->isComment() && !tSubTmp->isTag() )
						{
							sTextTmp = tSubTmp->text();
							ReplaceSpecialSymbols(sTextTmp);//修改Replace 注意此处要变动
							EraseBlank(sTextTmp);
							iAveLen += sTextTmp.length();
							//iAveLen += tSubTmp->text().length();
						}
					}
				}
				
				iAveLen = iAveLen / vvLinkGroups[i].size();
				vAveLens.push_back(iAveLen);
				vPos.push_back(i);
				iAveLen = 0;
			}
		}
		
		int iLen = 0;
		int iPos = 0;
		for (int i = 0; i < vAveLens.size(); ++i)
		{
			if (iLen < vAveLens[i])
			{
				iLen = vAveLens[i];
				iPos = i;
			}
		}
		vOrderedLinks = vvLinkGroups[vPos[iPos] ];
		
	}




	/*!
	* \fn arise_ErrorCode RegionStruct(const tree<HTML::Node> &tDom, vector<vector<NodeBase> > &vvLinkGroups, arise::NodeBase &nodeRegionStruct ,vector <NodeBase> &vMinStructs);
	* \brief  寻找区域结构体
	* \param  [in]DOM树
	* \param  [in]链接组
	* \param  [out]区域结构体
	* \param  [out]每个链接组元素的最小父结构
	* \return 自定义返回码
	* \date   2011-06-01
	* \author nanjunxiao
	*/
	arise_ErrorCode ExtractBase::RegionStruct(const tree<HTML::Node> &tDom, vector<vector<NodeBase> > &vvLinkGroups, arise::NodeBase &nodeRegionStruct ,vector <NodeBase> &vMinStructs)
	{
		if (vvLinkGroups.empty() )
		{
			return arise_E_vvLinkGroupsIsEmpty;
		}
		
		NodeBase nodeMin;

		for (vector<vector<NodeBase> >::iterator vvIter = vvLinkGroups.begin(); vvIter != vvLinkGroups.end(); ++vvIter)
		{
			vector<NodeBase>::iterator vIter = vvIter->begin();
			nodeMin = *vIter;
			++ vIter;//至少4个
			
			for (; vIter != vvIter->end(); ++vIter)
			{
				nodeMin.FindMinStruct(tDom, *vIter);
			}

			nodeMin.CountNodeChars(tDom);
			vMinStructs.push_back(nodeMin);
		}

		vector<NodeBase>::iterator vIter = vMinStructs.begin();
		int iPageChars = CountPageChars(tDom);

		for (; vIter != vMinStructs.end(); ++vIter) 
		{
			if (vIter->ReadNodeChars() > 0.5 * iPageChars )
			{			
				nodeMin = *vIter;
				break;
			}
		}
			
		if (vIter == vMinStructs.end())
		{
			//throw "GenerateRegionalStruct::RegionStruct 没有大于页面字数一半的最小结构体作为区域结构体";
			return arise_E_RegionStructNull;
		}

		++vIter;
		for (; vIter != vMinStructs.end(); ++vIter)
		{
			if (vIter->ReadNodeChars() > 0.5 * iPageChars 
				&& vIter->ReadIpath().size() > nodeMin.ReadIpath().size() )//此处最小结构体只是采用ipath长度比较
			{
				nodeMin = *vIter;
			}
		}

		nodeRegionStruct = nodeMin;
		return arise_E_OK;
	}




	/*!
	* \fn int CountPageChars(const tree<HTML::Node> &tDom);
	* \brief  统计网页字符数
	* \param  [in]DOM树
	* \return int
	* \date   2011-06-01
	* \author nanjunxiao
	*/
	int ExtractBase::CountPageChars(const tree<HTML::Node> &tDom)
	{
		int iPageChars = 0;
		string sTextTmp;
		for (tree<HTML::Node>::iterator tIter = tDom.begin(); tIter != tDom.end(); ++tIter)
		{
			if (!tIter->isComment() && !tIter->isTag()  )
			{
				sTextTmp = tIter->text();
				ReplaceSpecialSymbols(sTextTmp);
				EraseBlank(sTextTmp);
				iPageChars += sTextTmp.length();
				//iPageChars += tIter->text().length();
			}
		}
		return iPageChars;
	}



}
