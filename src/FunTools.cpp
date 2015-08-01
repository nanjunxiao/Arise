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
	* \brief  清除属性解析时DOM树节点中的前后端空白，like trim
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
			}//前端空白处理完

			if (sText.empty() )
			{
				return ;
			}
			else
			{
				stEnd = sText.length() - 1;
				while(sText.at(stEnd) == '\n' || sText.at(stEnd) == '\t' || sText.at(stEnd) == ' ' )
				{
					if (stEnd > 0)//逻辑 不用
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
	* \brief  替换属性解析时DOM树节点中的特殊字符，目前只处理&nbsp;
	* \param  [in]sText
	* \param  [out]sText
	* \return void
	* \date   2011-06-01 
	* \author nanjunxiao
	*/
	void ReplaceSpecialSymbols(string &sText)////仅 &nbsp;修改Replace 注意其他地方要变动
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