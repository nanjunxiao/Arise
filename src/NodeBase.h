/*!
 * \class  NodeBase 
 * \brief  �ڵ����
 * \date   2011-06-01 
 * \author nanjunxiao
*/ 


#ifndef NODEBASE_H_
#define NODEBASE_H_

#include <string>
#include <list>
#include <utility>
#include <vector>
#include "htmlcxx/ParserDom.h"
#include "Pretreat.h"

using std::string;
using namespace htmlcxx;

namespace arise
{
	class NodeBase
	{
	public:
		NodeBase():m_iCountOfChars(0){}
		~NodeBase(){}

		
		/*!
		 * \fn void Rpath(const tree<HTML::Node > &tDom);
		 * \brief  �ɵ�������Rpath
		 * \param  [in]DOM��
		 * \param  [out]this->m_lRpath
		 * \return void
		 * \date   2011-06-01 
		 * \author nanjunxiao
		 */
		void Rpath(const tree<HTML::Node > &tDom);


		
		/*!
		 * \fn void Ipath(const tree<HTML::Node > &tDom);
		 * \brief  �ɵ�������Ipath
		 * \param  [in]DOM��
		 * \param  [out]this->m_lIpath
		 * \return void
		 * \date   2011-06-01 
		 * \author nanjunxiao
		 */
		void Ipath(const tree<HTML::Node > &tDom);


		
		/*!
		 * \fn bool RpathIsEqual(const NodeBase &Other) const;
		 * \brief  �жϽڵ��Rpath�Ƿ���ͬ
		 * \param  [in]��һ��NodeBase
		 * \return bool
		 * \date   2011-06-01 
		 * \author nanjunxiao
		 */
		bool RpathIsEqual(const NodeBase &Other) const;


		
		/*!
		 * \fn void CountNodeChars(const tree<HTML::Node > &tDom) ;
		 * \brief  ͳ�ƽڵ��ַ���
		 * \param  [in]DOM��
		 * \param  [out]this->m_iCountOfChars
		 * \return void
		 * \date   2011-06-01 
		 * \author nanjunxiao
		 */
		void CountNodeChars(const tree<HTML::Node > &tDom) ;


		
		/*!
		 * \fn int ReadNodeChars() const;
		 * \brief  ��ȡ�ڵ��ַ�����ֻ��
		 * \param  void
		 * \return int���ڵ��ַ���
		 * \date   2011-06-01 
		 * \author nanjunxiao
		 */
		int ReadNodeChars() const;


		
		/*!
		 * \fn bool IpathIsEqual(const NodeBase &Other) const;
		 * \brief  �жϽڵ��Ipath�Ƿ���ͬ
		 * \param  [in]��һ���ڵ�
		 * \return bool
		 * \date   2011-06-01 
		 * \author nanjunxiao
		 */
		bool IpathIsEqual(const NodeBase &Other) const;

		
		
		/*!
		 * \fn const list< pair <string, int> > & ReadIpath() const;
		 * \brief  ��ȡ�ڵ��Ipath��ֻ��
		 * \param  void
		 * \return �ڵ�Ipath������
		 * \date   2011-06-01 
		 * \author nanjunxiao
		 */
		const list< pair <string, int> > & ReadIpath() const;
		
		
		
		/*!
		 * \fn list <string> & ReadRpath();
		 * \brief  ��ȡ�ڵ��Rpath,���޸�
		 * \param  void
		 * \return �ڵ�Rpath������
		 * \date   2011-06-01 
		 * \author nanjunxiao
		 */
		list <string> & ReadRpath();
		

		
		/*!
		 * \fn bool IsSon(const NodeBase &Other) const;
		 * \brief  �жϸýڵ��Ƿ�Ϊ��һ���ĺ���
		 * \param  [in]��һ���ڵ�
		 * \return bool
		 * \date   2011-06-01 
		 * \author nanjunxiao
		 */
		bool IsSon(const NodeBase &Other) const;


		
		/*!
		 * \fn bool operator== (const NodeBase &Other) const;
		 * \brief  ����==
		 * \param  [in]��һ���ڵ�
		 * \return bool
		 * \date   2011-06-01 
		 * \author nanjunxiao
		 */
		bool operator== (const NodeBase &Other) const;

		
		
		/*!
		 * \fn NodeBase & FindMinStruct(const tree<HTML::Node > &tDom,  NodeBase &Other);
		 * \brief  Ѱ�����ڵ����С�����ṹ��
		 * \param  [in]DOM��
		 * \param  [in]��һ���ڵ�
		 * \return �ýڵ������
		 * \date   2011-06-01 
		 * \author nanjunxiao
		 */
		NodeBase & FindMinStruct(const tree<HTML::Node > &tDom,  NodeBase &Other);
		
		
		
		/*!
		 * \fn void RpathToIterator(const tree<HTML::Node> &tDom, vector<tree<HTML::Node>::iterator > &vecIters);//��ȡͬ����ҳʱʹ��
		 * \brief  ��Rpathȷ��������
		 * \param  [in]DOM��
		 * \param  [out]���и�Rpath�ĵ���������
		 * \return void
		 * \date   2011-06-01 
		 * \author nanjunxiao
		 */
		void RpathToIterator(const tree<HTML::Node> &tDom, vector<tree<HTML::Node>::iterator > &vecIters);//��ȡͬ����ҳʱʹ��


		
		/*!
		 * \fn tree<HTML::Node>::iterator IpathToIterator(const tree<HTML::Node > &tDom);
		 * \brief  ��Ipathȷ�������������£�
		 * \param  [in]DOM��
		 * \return ���и�Ipath�Ľڵ��ӦDOM���ĵ�����
		 * \date   2011-06-01 
		 * \author nanjunxiao
		 */
		tree<HTML::Node>::iterator IpathToIterator(const tree<HTML::Node > &tDom);



		/*!
		 * \fn bool operator < (const NodeBase &Other) const;
		 * \brief  ����<
		 * \param  [in]��һ���ڵ�
		 * \return bool
		 * \date   2011-06-01 
		 * \author nanjunxiao
		 */
		bool operator < (const NodeBase &Other) const;


		tree<HTML::Node>::iterator m_tIter; /**< �ڵ���dom���еĵ�����*/


	protected:
	private:
		//tree<HTML::Node>::iterator m_tIter;
		list<string> m_lRpath; /*< Rpath*/
		list< pair <string, int> > m_lIpath; /**< Ipath*/
		int m_iCountOfChars; /**< �ַ���*/
	
	};
}
#endif
