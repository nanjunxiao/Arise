#include "Pretreat.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <errno.h>
#include "htmltidy/tidy.h"
#include "htmltidy/buffio.h"
#include <algorithm>

//using namespace std;

namespace arise
{
	/*!
	* \fn static bool GenerateSubTree(const tree<HTML::Node> &tDom, const string &tagname, tree<HTML::Node> &tSubDom);
	* \brief  生成子树
	* \param  [in]DOM原树
	* \param  [in]子树根节点的标签名
	* \param  [out]DOM子树
	* \return bool
	* \date   2011-06-01 
	* \author nanjunxiao
	*/
	bool Pretreat::GenerateSubTree(const tree<HTML::Node> &tDom, const std::string &tagname, tree<HTML::Node> &tSubDom)//目前只是为body使用
	{
		tree<HTML::Node>::iterator tIter = tDom.begin();
		tree<HTML::Node>::sibling_iterator tFromIter,tToIter;
		string sTagName;
		for (; tIter != tDom.end(); ++tIter)
		{
			/*if (tIter->tagName() == tagname)
				break;*/
			if (tIter->isTag() )
			{
				sTagName = tIter->tagName();
				transform(sTagName.begin(), sTagName.end(), sTagName.begin(), ::tolower);
				if (sTagName == tagname)
					break;
			}
		}
		if (tIter == tDom.end() ) 
		{
			return false;
		}
		
		tFromIter = tIter;
		tToIter = tDom.next_sibling(tFromIter);
		tDom.subtree(tSubDom, tFromIter, tToIter);
		return true;
	}



	/*!
	* \fn static void GenerateSubTree(const tree<HTML::Node> &tDom, const tree<HTML::Node>::iterator &tIter, tree<HTML::Node> &tSubDom);
	* \brief  生成子树
	* \param  [in]DOM原树
	* \param  [in]子树根节点的迭代器
	* \param  [out]DOM子树
	* \return void
	* \date   2011-06-01 
	* \author nanjunxiao
	*/
	void Pretreat::GenerateSubTree(const tree<HTML::Node> &tDom, const tree<HTML::Node>::iterator &tIter, tree<HTML::Node> &tSubDom)
	{
		
		tree<HTML::Node>::sibling_iterator tFromIter,tToIter;
		tFromIter = tIter;
		tToIter = tDom.next_sibling(tFromIter);
		tDom.subtree(tSubDom, tFromIter, tToIter);
	}



	/*!
	* \fn static void CleanUpFormTag(tree<HTML::Node> &m_TagTree);
	* \brief  剪枝，去除scrip等无用节点
	* \param  [in]DOM树
	* \return void
	* \date   2011-06-01 
	* \author nanjunxiao
	*/
	void Pretreat::CleanUpFormTag(tree<HTML::Node> &m_TagTree)
	{
		set<string> m_sCleanFormSet;
		m_sCleanFormSet.insert("input");
		m_sCleanFormSet.insert("noembed");
		m_sCleanFormSet.insert("noscript");
		m_sCleanFormSet.insert("textarea");
		m_sCleanFormSet.insert("marquee");
		m_sCleanFormSet.insert("object");
		m_sCleanFormSet.insert("select");
		m_sCleanFormSet.insert("iframe");
		m_sCleanFormSet.insert("style");
		m_sCleanFormSet.insert("script");

		tree<HTML::Node>::iterator itTagTreeBegin = m_TagTree.begin();
		tree<HTML::Node>::iterator itTagTreeEnd = m_TagTree.end();
		while ( itTagTreeBegin != itTagTreeEnd )
		{
		//遍历标签树，标签节点且节点名称在m_sCleanFormSet中则把标签节点在标签树上删除
			if ( itTagTreeBegin->isTag() )
			{
				string sTagName = itTagTreeBegin->tagName();
				if ( m_sCleanFormSet.find(sTagName) != m_sCleanFormSet.end() )
				{
					tree<HTML::Node>::sibling_iterator sibTmp = itTagTreeBegin;
					sibTmp++;
					m_TagTree.erase( itTagTreeBegin );
					itTagTreeBegin = sibTmp;
				}
				else
				{
					itTagTreeBegin++ ;
				}
			}//end if
			else
			{
				itTagTreeBegin++;
			}
		}//end while
	}



	/*!
	* \fn static int TidyHtml(const char *pcSourcePage, string &sDestPage);
	* \brief  修补丢失、错误标签
	* \param  [in]待修补网页字符串
	* \param  [out]修补后的网页string
	* \return 结果码，==0修补正确，<0修补失败
	* \date   2011-06-01 
	* \author nanjunxiao
	*/
	int Pretreat::TidyHtml(const char *pcSourcePage, std::string &sDestPage)
	{
		int iReturn = 0;
		TidyBuffer errbuf = {0};
		TidyDoc tdoc;
		tmbstr pBuffer = NULL;

		try
		{
			if ( (pcSourcePage == NULL) || (strlen(pcSourcePage) ==0 ) )
			{
				//cerr << "TidyHtml 输入页面为空！" << endl;
				throw (-1);
			}

			int iRet = -1;
			Bool bOk;
			uint uiBufLen;
			int iBufSize;
			tdoc = tidyCreate();// Initialize "document"
			bOk = tidyOptSetBool(tdoc, TidyXhtmlOut, yes);// Convert to XHTML
			if (bOk)
			{
				iRet = tidySetErrorBuffer(tdoc, &errbuf); // Capture diagnostics
			}
			else
			{
				throw (-1);
			}

			if (iRet >= 0)
			{
				iRet = tidySetCharEncoding(tdoc,"utf8"); //Ensure dealing with gb2312 successfully
			}
			else
			{
				throw (-1);
			}

			if (iRet >= 0)
			{
				string htmlsrc = pcSourcePage;
				iRet = tidyParseString (tdoc, htmlsrc.c_str() ); // Parse the input
			}
			else
			{
				throw (-1);
			}

			if (iRet >= 0)
			{
				iRet = tidyCleanAndRepair(tdoc); //Tidy it up!
			}
			else
			{
				throw (-1);
			}
			
			if (iRet >= 0)
			{
				iRet = tidyRunDiagnostics(tdoc); //Kvetch
			}
			else
			{
				throw (-1);
			}

			if(iRet > 1) // If error, force output.
			{
				iRet = ( tidyOptSetBool(tdoc, TidyForceOutput, yes) ? iRet : -1 );
			}
			else if (iRet < 0)
			{
				throw (-1);
			}

			if (iRet >= 0)
			{
				// Pretty Print
				iBufSize = 1024 * 1024 * 5;
				uiBufLen = iBufSize;
				pBuffer = new char [iBufSize];
				memset(pBuffer, '\0', iBufSize);
				iRet = tidySaveString(tdoc, pBuffer, &uiBufLen);
			}
			else
			{
				throw (-1);
			}

			if (iRet >= 0)
			{
				sDestPage = pBuffer;
			}
			else if (iRet == -ENOMEM)
			{
				//pBuffer 长度不够
				//cerr << "TidyHtml pBuffer长度不够！" << endl;
				throw (-1);
			}
			else
			{
				throw (-1);
			}
		}
		catch(exception &err)
		{
			//cerr << "TidyHtml HtmlTidy修补页面失败！ " << err.what() << endl;
			iReturn = -1;
		}
		catch(int iThrow)
		{
			if (iThrow < 0)
			{
				//cerr << "TidyHtml HtmlTidy修补页面失败！" << endl;
			}
			iReturn = iThrow;
		}
		catch(...)
		{
			//cerr << "TidyHtml HtmlTidy修补页面失败！" << endl;
			iReturn = -1;
		}

		tidyBufFree(&errbuf);
		tidyRelease(tdoc);
		if (pBuffer != NULL)
		{
			delete [] pBuffer;
			pBuffer = NULL;
		}
		return iReturn;
	}



	/*!
	* \fn static void ReadOnePage(const string &path,string &html);
	* \brief  读取本地磁盘上的文件
	* \param  [in]文件存储路径
	* \param  [out]文件内容string
	* \return void
	* \date   2011-06-01 
	* \author nanjunxiao
	*/
	void Pretreat::ReadOnePage(const string &path, string &html)
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



	/*!
	* \fn static void EraseBaiduAD(string &sContent);
	* \brief  针对百度，去除百度推广链接（右面）
	* \param  [in]网页string
	* \param  [out]网页string
	* \return void
	* \date   2011-06-01 
	* \author nanjunxiao
	*/
	void Pretreat::EraseBaiduAD(std::string &sContent)
	{
		string::size_type stTableBeg = 0;
		string::size_type stTableEnd = 0;
		string::size_type stTableRight = 0;

		string::size_type stAlignRight = 0;
		string::size_type stClassECmr15 = 0;
		while( (stTableBeg = sContent.find("<table", stTableBeg) ) != string::npos)
		{
			stTableEnd = sContent.find("</table>", stTableBeg + 6);
			if (stTableEnd == string::npos)
				return ;
			stTableRight = sContent.find(">", stTableBeg + 6);
			if (stTableRight > stTableEnd || stTableRight == string::npos)
				return ;
			stAlignRight = sContent.find("align=\"right\"", stTableBeg + 6);
			stClassECmr15 = sContent.find("class=\"EC_mr15\"", stTableBeg + 6);
			if ( (stAlignRight < stTableRight && stAlignRight != string::npos) ||
				 (stClassECmr15 < stTableRight && stClassECmr15 != string::npos) )
			{
				sContent.erase(stTableBeg, stTableEnd + 8 - stTableBeg);
				//cout << "erase once!" << endl;
			}
			else
				stTableBeg = stTableEnd + 8;
		}
	}

	/*void Pretreat::EraseBaiduAD(std::string &sContent)
	{
		string::size_type stTableBeg = 0;
		string::size_type stTableEnd = 0;
		while( (stTableBeg = sContent.find("<table", stTableBeg) ) != string::npos)
		{
			stTableEnd = sContent.find("</table>", stTableBeg + 6);
			if (stTableEnd == string::npos)
				return ;
			if (sContent.find("align=\"right\"", stTableBeg + 6) < stTableEnd)
			{
				sContent.erase(stTableBeg, stTableEnd + 8 - stTableBeg);
			}
			else
				stTableBeg = stTableEnd + 8;
		}
	}*/



	/*!
	* \fn static string SubStringBody(string &sContent);
	* \brief  字符串处理截取body字串,备注	：无法处理大小写问题，效率相比子树也没快多少
	* \param  [in]网页string
	* \return body字串
	* \date   2011-06-01 
	* \author nanjunxiao
	*/
	string Pretreat::SubStringBody(string &sContent)//大小写无法区别，效率没快多少
	{
		string::size_type stBeg = sContent.find("<body", 0);
		if (stBeg == string::npos)
			return string("");
		string::size_type stEnd = sContent.find("</body>", stBeg + 5);
		if (stBeg == string::npos)
			return string("");
		return sContent.substr(stBeg, stEnd + 7 - stBeg); 
	}
	
}
