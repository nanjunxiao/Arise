/*!
 * \class  Pretreat 
 * \brief  Ԥ������
 * \date   2011-06-01 
 * \author nanjunxiao
 */ 


#ifndef PRETREAT_H_
#define PRETREAT_H_

#include "htmlcxx/ParserDom.h"
#include <string>

using namespace htmlcxx;
using namespace std;

namespace arise
{
	class Pretreat
	{
	public:
		
		/*!
		 * \fn static bool GenerateSubTree(const tree<HTML::Node> &tDom, const string &tagname, tree<HTML::Node> &tSubDom);
		 * \brief  ��������
		 * \param  [in]DOMԭ��
		 * \param  [in]�������ڵ�ı�ǩ��
		 * \param  [out]DOM����
		 * \return bool
		 * \date   2011-06-01 
		 * \author nanjunxiao
		 */
		static bool GenerateSubTree(const tree<HTML::Node> &tDom, const string &tagname, tree<HTML::Node> &tSubDom);


		
		/*!
		 * \fn static void GenerateSubTree(const tree<HTML::Node> &tDom, const tree<HTML::Node>::iterator &tIter, tree<HTML::Node> &tSubDom);
		 * \brief  ��������
		 * \param  [in]DOMԭ��
		 * \param  [in]�������ڵ�ĵ�����
		 * \param  [out]DOM����
		 * \return void
		 * \date   2011-06-01 
		 * \author nanjunxiao
		 */
		static void GenerateSubTree(const tree<HTML::Node> &tDom, const tree<HTML::Node>::iterator &tIter, tree<HTML::Node> &tSubDom);


		
		/*!
		 * \fn static void CleanUpFormTag(tree<HTML::Node> &m_TagTree);
		 * \brief  ��֦��ȥ��scrip�����ýڵ�
		 * \param  [in]DOM��
		 * \return void
		 * \date   2011-06-01 
		 * \author nanjunxiao
		 */
		static void CleanUpFormTag(tree<HTML::Node> &m_TagTree);



		
		/*!
		 * \fn static int TidyHtml(const char *pcSourcePage, string &sDestPage);
		 * \brief  �޲���ʧ�������ǩ
		 * \param  [in]���޲���ҳ�ַ���
		 * \param  [out]�޲������ҳstring
		 * \return ����룬==0�޲���ȷ��<0�޲�ʧ��
		 * \date   2011-06-01 
		 * \author nanjunxiao
		 */
		static int TidyHtml(const char *pcSourcePage, string &sDestPage);



		
		/*!
		 * \fn static void ReadOnePage(const string &path,string &html);
		 * \brief  ��ȡ���ش����ϵ��ļ�
		 * \param  [in]�ļ��洢·��
		 * \param  [out]�ļ�����string
		 * \return void
		 * \date   2011-06-01 
		 * \author nanjunxiao
		 */
		static void ReadOnePage(const string &path,string &html);
		//static void TagNameToLower(tree<HTML::Node> &tDom);


		
		/*!
		 * \fn static void EraseBaiduAD(string &sContent);
		 * \brief  ��԰ٶȣ�ȥ���ٶ��ƹ����ӣ����棩
		 * \param  [in]��ҳstring
		 * \param  [out]��ҳstring
		 * \return void
		 * \date   2011-06-01 
		 * \author nanjunxiao
		 */
		static void EraseBaiduAD(string &sContent);


		
		/*!
		 * \fn static string SubStringBody(string &sContent);
		 * \brief  �ַ��������ȡbody�ִ�,��ע	���޷������Сд���⣬Ч���������Ҳû�����
		 * \param  [in]��ҳstring
		 * \return body�ִ�
		 * \date   2011-06-01 
		 * \author nanjunxiao
		 */
		static string SubStringBody(string &sContent);
	};
}
#endif