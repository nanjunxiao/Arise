/*!
 * \class  ExtractBase 
 * \brief  ��ȡ����
 * \date   2011-06-01
 * \author nanjunxiao 
*/ 


#ifndef EXTRACTBASE_H_
#define EXTRACTBASE_H_

#include "htmlcxx/ParserDom.h"
#include "NodeBase.h"
#include <vector>
#include "Interface.h"
using namespace htmlcxx;
namespace arise
{
	class ExtractBase
	{
	public:
		ExtractBase(){}


		virtual ~ExtractBase(){}


		/*!
		 * \fn arise_ErrorCode Extract(const tree<HTML::Node> &tDom);
		 * \brief  ��ȡ������������һֱ��ȡ����Ϣ�ṹ��
		 * \param  [in]DOM��
		 * \return �Զ��巵����
		 * \date   2011-06-01
		 * \author nanjunxiao
		 */
		arise_ErrorCode Extract(const tree<HTML::Node> &tDom);


	
		/*!
		 * \fn void WriteWrapper(const tree<HTML::Node> &tDom, ofstream &ofs);
		 * \brief  ����׼�����顢��Ϣ�ṹ��Rpathд��wrapper
		 * \param  [in]DOM��
		 * \param  [out]����ļ���
		 * \return void
		 * \date   2011-06-01
		 * \author nanjunxiao
		 */
		void WriteWrapper(const tree<HTML::Node> &tDom, ofstream &ofs);
		
	protected:
		
		/*!
		 * \fn const vector<NodeBase> & ReadInfoStruct(void) const;
		 * \brief  ��ȡ��Ϣ�ṹ�壬ֻ��
		 * \param  void
		 * \return ��Ϣ�ṹ������
		 * \date   2011-06-01
		 * \author nanjunxiao
		 */
		const vector<NodeBase> & ReadInfoStruct(void) const;





		/*!
		 * \fn void IdentifyInfoStruct(const tree<HTML::Node> &tDom);
		 * \brief  �ɱ�׼������ȷ����Ϣ�ṹ��
		 * \param  [in]DOM��
		 * \param  [out]this->m_vInfoStruct
		 * \return void
		 * \date   2011-06-01
		 * \author nanjunxiao
		 */
		void IdentifyInfoStruct(const tree<HTML::Node> &tDom);



		/*!
		 * \fn void FindAllLinks(const tree<HTML::Node> &tDom, list<NodeBase> &lAllLinks);
		 * \brief  ��������DOM���е���������
		 * \param  [in]DOM��
		 * \param  [out]this->m_lAllLinks
		 * \return void
		 * \date   2011-06-01
		 * \author nanjunxiao
		 */
		void FindAllLinks(const tree<HTML::Node> &tDom, list<NodeBase> &lAllLinks);



		/*!
		 * \fn arise_ErrorCode Group(list<NodeBase> lAllLinks, vector<vector<NodeBase> > &vvLinkGroups);
		 * \brief  �������ӷ��飬Rpath��ͬ��Ϊһ��
		 * \param  [in]��������
		 * \param  [out]������
		 * \return �Զ��巵����
		 * \date   2011-06-01
		 * \author nanjunxiao
		 */
		arise_ErrorCode Group(list<NodeBase> lAllLinks, vector<vector<NodeBase> > &vvLinkGroups);




		/*!
		 * \fn void IdentifyOrderedLinkGroup(const tree<HTML::Node> &tDom, 
									  const vector<vector<NodeBase> > &vvLinkGroups,
									  const vector<NodeBase> &vMinStructs,
									  vector<NodeBase> &vOrderedLinks);
		 * \brief  ʶ������������
		 * \param  [in]DOM��
		 * \param  [in]������
		 * \param  [in]ÿ��������Ԫ�ص���С���ṹ
		 * \param  [out]����������
		 * \return void
		 * \date   2011-06-01
		 * \author nanjunxiao
		 */
		void IdentifyOrderedLinkGroup(const tree<HTML::Node> &tDom, 
									  const vector<vector<NodeBase> > &vvLinkGroups,
									  const vector<NodeBase> &vMinStructs,
									  vector<NodeBase> &vOrderedLinks);




		
		/*!
		 * \fn arise_ErrorCode RegionStruct(const tree<HTML::Node> &tDom, vector<vector<NodeBase> > &vvLinkGroups, arise::NodeBase &nodeRegionStruct ,vector <NodeBase> &vMinStructs);
		 * \brief  Ѱ������ṹ��
		 * \param  [in]DOM��
		 * \param  [in]������
		 * \param  [out]����ṹ��
		 * \param  [out]ÿ��������Ԫ�ص���С���ṹ
		 * \return �Զ��巵����
		 * \date   2011-06-01
		 * \author nanjunxiao
		 */
		arise_ErrorCode RegionStruct(const tree<HTML::Node> &tDom, vector<vector<NodeBase> > &vvLinkGroups, arise::NodeBase &nodeRegionStruct ,vector <NodeBase> &vMinStructs);



		/*!
		 * \fn int CountPageChars(const tree<HTML::Node> &tDom);
		 * \brief  ͳ����ҳ�ַ���
		 * \param  [in]DOM��
		 * \return int
		 * \date   2011-06-01
		 * \author nanjunxiao
		 */
		int CountPageChars(const tree<HTML::Node> &tDom);

	private:
		/*!
		 * \fn NodeBase MaxFather(const tree<HTML::Node> &tDom, const NodeBase &SeparatedResult, const NodeBase &SeparatedRoot) const;
		 * \brief  �ṹ�����������ڷ�����ڵ����󸸽ڵ�
		 * \param  [in]DOM��
		 * \param  [in]�ṹ������㷨������
		 * \param  [in]������ڵ㣺����ṹ��/���ṹ��
		 * \return ��󸸽ڵ�
		 * \date   2011-06-01
		 * \author nanjunxiao
		 */
		NodeBase MaxFather(const tree<HTML::Node> &tDom, const NodeBase &SeparatedResult, const NodeBase &SeparatedRoot) const;


		list<NodeBase> m_lAllLinks;/**< ��������*/
		vector< vector<NodeBase> > m_vvLinkGroups;/**< �������ӷ����Ľ��*/
		NodeBase m_RegionStruct;/**< ����ӹ��壬��NodeBase�洢*/

		vector<NodeBase> m_vOrderedLinks;/**< ����������*/

		vector<NodeBase> m_vInfoStruct;/**< ��Ϣ�ṹ�弯��*/

	};
}
#endif
