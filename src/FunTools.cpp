#include "FunTools.h"

namespace arise
{
	/*bool IsBlank(const string &sText)
	{
		if (sText.length() > 0)
		{
			int iGap = 0;
			for (int i = 0; i < sText.length(); ++i)
			{
				if (sText.at(i) == '\n' || sText.at(i) == '\t' || sText.at(i) == ' ')
					iGap ++;
			}
			if ( (double)iGap/sText.length() > 0.75 )
				return true;
			else
				return false;
		}
		else
			return true;

	}*/




	/*!
	* \fn void EraseBlank(string &sText);
	* \brief  ������Խ���ʱDOM���ڵ��е�ǰ��˿հף�like trim
	* \param  [in]sText
	* \param  [out]sText
	* \return void
	* \date   2011-06-01 
	* \author nanjunxiao
	*/
	void EraseBlank(string &sText)
	{
		if (sText.length() > 0)
		{
			string::size_type stBeg = 0;
			string::size_type stEnd = sText.length() - 1;
			while (sText.at(stBeg) == '\n' || sText.at(stBeg) == '\t' || sText.at(stBeg) == ' ' )
			{
				++stBeg;
				if (stBeg > stEnd)
					break;
			}
			if (stBeg > 0)
			{
				sText.erase(0, stBeg);
			}//ǰ�˿հ״�����

			if (sText.empty() )
			{
				return ;
			}
			else
			{
				stEnd = sText.length() - 1;
				while(sText.at(stEnd) == '\n' || sText.at(stEnd) == '\t' || sText.at(stEnd) == ' ' )
				{
					if (stEnd > 0)//�߼� ����
					{
						--stEnd;
					}
					else
					{
						break;
					}
				}
				
				if (stEnd < sText.length() - 1)
				{
					sText.erase(stEnd + 1, sText.length() - stEnd - 1);
				}
			}
		}// end if
	}//end fun



	
	/*!
	* \fn void ReplaceSpecialSymbols(string &sText);
	* \brief  �滻���Խ���ʱDOM���ڵ��е������ַ���Ŀǰֻ����&nbsp;
	* \param  [in]sText
	* \param  [out]sText
	* \return void
	* \date   2011-06-01 
	* \author nanjunxiao
	*/
	void ReplaceSpecialSymbols(string &sText)////�� &nbsp;�޸�Replace ע�������ط�Ҫ�䶯
	{
		string::size_type stBeg = 0;
		string::size_type stEnd = 0;
		while( (stBeg = sText.find("&nbsp;", stBeg) ) != string::npos)
		{
			sText.replace(stBeg, 6, " ");
			stBeg ++;
		}
	}

}