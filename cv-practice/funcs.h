/*在这个文件中引用所需要的函数名
他喵的这C艹毛病真多，还得整个头文件伺候 ヾ(｡｀Д´｡)ﾉ彡 */

#pragma once

//读取、显示图片
void readimg();	

//灰度反转
void greyTrans();

//对数变换
void logTrans();

//背景相减
void subtractTrans();

//移动
void moveTrans();

//旋转
void rotateTrans();

//翻转
void flipTrans();

//转置
void posiTrans();

//缩放
void resizeTrans();

//直方图均衡
void histogramTrans();

//中值滤波
void smoothFilterTrans();