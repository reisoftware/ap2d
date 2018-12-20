// Mgr_Convert.cpp: implementation of the Mgr_Convert class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Ap2D.h"
#include "Mgr_Convert.h"



#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Mgr_Convert::Mgr_Convert()
{

}

Mgr_Convert::~Mgr_Convert()
{

}
CString get_arrow_pos(int pos)
{
	if(pos == dlhml::ARROW_NULL)
		return "no";
	else if(pos == dlhml::ARROW_START)
		return "start_pos";
	else if(pos == dlhml::ARROW_END)
		return "end_pos";
	else if(pos == dlhml::ARROW_DOUBLE)
		return "two_side";
	return "no";
}
int get_arrow_pos(CString str)
{
	if(str == "no")
		return 0;
	return 1;

}
int get_arrow_num(CString str)
{
	if(str == "no")
		return 0;
	else if(str == "start_pos")
		return 1;
	else if(str == "end_pos")
		return 2;
	else if(str == "two_side")
		return 3;
	else
		return 1;

}
dlhml::Dimension_Style::Arrow get_arrow_style_by_int(int pos)
{
	dlhml::Dimension_Style::Arrow arrow;
	if(pos == 0){
		arrow = dlhml::Dimension_Style::LEAD;
	}else if(pos == 1){
		arrow = dlhml::Dimension_Style::CIRCLE;
	}else if(pos == 2){
		arrow = dlhml::Dimension_Style::COMMON;
	}else{
		arrow = dlhml::Dimension_Style::COMMON;
	}
	return arrow;
}
CString get_arrow_style(dlhml::Dimension_Style::Arrow arrow)
{
	CString str;

	if(arrow == dlhml::Dimension_Style::COMMON){
		str = "common";
	}else if(arrow == dlhml::Dimension_Style::CIRCLE){
		str = "circle";
	}else if(arrow == dlhml::Dimension_Style::LEAD){
		str = "lean line";
	}else{
		str = "common";
	}
	return str;

}

dlhml::Dimension_Style::Txt_Frame get_txt_frame(CString name)
{
	dlhml::Dimension_Style::Txt_Frame txt_style;
	if(name == g_dimKindBaseLineFrame){
		txt_style = dlhml::Dimension_Style::Baseline;
	}else if(name == g_dimKindArcFrame){
		txt_style = dlhml::Dimension_Style::ArcEdge;
	}else if(name == g_dimKindArrowFrame){
		txt_style = dlhml::Dimension_Style::ArrowEdge;
	}else if(name == g_dimKindRectFrame){
		txt_style = dlhml::Dimension_Style::RectEdge;
	}else{
		txt_style = dlhml::Dimension_Style::Only;
	}	
	return txt_style;
	
}
CString get_txt_frame(dlhml::Dimension_Style::Txt_Frame txt_style)
{
	CString str;
	if(txt_style == dlhml::Dimension_Style::Baseline){
		str = g_dimKindBaseLineFrame;
	}else if(txt_style == dlhml::Dimension_Style::ArcEdge){
		str = g_dimKindArcFrame;
	}else if(txt_style == dlhml::Dimension_Style::ArrowEdge){
		str = g_dimKindArrowFrame;
	}else if(txt_style == dlhml::Dimension_Style::RectEdge){
		str = g_dimKindRectFrame;
	}else{
		str = g_dimKindNoFrame;
	}	
	return str;
	
}
CString get_txt_pos(dlhml::Dimension_Style::TextPos txt_pos)
{
	CString pos="Up";
	if(txt_pos == dlhml::Dimension_Style::UP){
		pos = "Up";
	}else if(txt_pos == dlhml::Dimension_Style::CENTER){
		pos = "Down";
	}else if(txt_pos == dlhml::Dimension_Style::DOWN){
		pos = "Center";
	}
	return pos;
}
dlhml::Dimension_Style::Arrow get_arrow_style_by_name(CString name)
{
	dlhml::Dimension_Style::Arrow arrow;
	if(name == "common"){
		arrow = dlhml::Dimension_Style::COMMON;
	}else if(name == "circle"){
		arrow = dlhml::Dimension_Style::CIRCLE;
	}else if(name == "lean line"){
		arrow = dlhml::Dimension_Style::LEAD;
	}else if(name == "no"){
		arrow = dlhml::Dimension_Style::NO;
	}else{
		arrow = dlhml::Dimension_Style::COMMON;
	}
	return arrow;
	
}




int colorref_to_index(COLORREF col)
{
  long acirgb, r,g,b;
  long mindst = 2147483647L;
  long dst = 0;
  int minndx = 0;
  long red=GetRValue(col);
  long green=GetGValue(col);
  long blue=GetBValue(col);
  for(int i=1; i<256; ++i){
    acirgb = index_to_colorref(i);
    r =GetRValue(acirgb);
    g =GetGValue(acirgb);
    b =GetBValue(acirgb);
    
    dst = abs ( r-red) + abs ( g -green) + abs (b-blue);
    if ( dst < mindst ) {
      minndx = i;
      mindst = dst;
    }
  }
  return minndx;
}

COLORREF index_to_colorref(int index)
{
  COLORREF col;
  switch(index){
  case 1:col=RGB(255,0,0);break;
  case 2:col=RGB(255,255,0);break;
  case 3:col=RGB(0,255,0);break;
  case 4:col=RGB(0,255,255);break;
  case 5:col=RGB(0,0,255);break;
    
  case 6:col=RGB(255,0,255);break;
  case 7:col=RGB(255,255,255);break;
  case 8:col=RGB(128,128,128);break;
  case 9:col=RGB(242,242,242);break;
  case 10:col=RGB(255,0,0);break;
    
  case 11:col=RGB(255,127,127);break;
  case 12:col=RGB(165,0,0);break;
  case 13:col=RGB(165,82,82);break;
  case 14:col=RGB(127,0,0);break;
  case 15:col=RGB(127,63,63);break;
    
  case 16:col=RGB(76,0,0);break;
  case 17:col=RGB(76,38,38);break;
  case 18:col=RGB(38,0,0);break;
  case 19:col=RGB(38,19,19);break;
  case 20:col=RGB(255,63,0);break;
    
  case 21:col=RGB(255,159,127);break;
  case 22:col=RGB(165,41,0);break;
  case 23:col=RGB(165,103,82);break;
  case 24:col=RGB(127,31,0);break;
  case 25:col=RGB(127,79,63);break;
    
  case 26:col=RGB(76,19,0);break;
  case 27:col=RGB(76,47,38);break;
  case 28:col=RGB(38,9,0);break;
  case 29:col=RGB(38,23,19);break;
  case 30:col=RGB(255,127,0);break;
    
  case 31:col=RGB(255,191,127);break;
  case 32:col=RGB(165,82,0);break;
  case 33:col=RGB(165,124,82);break;
  case 34:col=RGB(127,63,0);break;
  case 35:col=RGB(127,95,63);break;
    
  case 36:col=RGB(76,38,0);break;
  case 37:col=RGB(76,57,38);break;
  case 38:col=RGB(38,19,0);break;
  case 39:col=RGB(38,28,19);break;
  case 40:col=RGB(255,191,0);break;
    
  case 41:col=RGB(255,223,127);break;
  case 42:col=RGB(165,124,0);break;
  case 43:col=RGB(165,145,82);break;
  case 44:col=RGB(127,95,0);break;
  case 45:col=RGB(127,111,63);break;
    
  case 46:col=RGB(76,57,0);break;
  case 47:col=RGB(76,66,38);break;
  case 48:col=RGB(38,28,0);break;
  case 49:col=RGB(38,33,19);break;
  case 50:col=RGB(255,255,0);break;
    
  case 51:col=RGB(255,255,127);break;
  case 52:col=RGB(165,165,0);break;
  case 53:col=RGB(165,165,82);break;
  case 54:col=RGB(127,127,0);break;
  case 55:col=RGB(127,127,63);break;
    
  case 56:col=RGB(76,76,0);break;
  case 57:col=RGB(76,76,38);break;
  case 58:col=RGB(38,38,0);break;
  case 59:col=RGB(38,38,19);break;
  case 60:col=RGB(191,255,0);break;
    
  case 61:col=RGB(223,255,127);break;
  case 62:col=RGB(124,165,0);break;
  case 63:col=RGB(145,165,82);break;
  case 64:col=RGB(95,127,0);break;
  case 65:col=RGB(111,127,63);break;
    
  case 66:col=RGB(57,76,0);break;
  case 67:col=RGB(66,76,38);break;
  case 68:col=RGB(28,38,0);break;
  case 69:col=RGB(33,38,19);break;
  case 70:col=RGB(127,255,0);break;
    
  case 71:col=RGB(191,255,127);break;
  case 72:col=RGB(82,165,0);break;
  case 73:col=RGB(124,165,82);break;
  case 74:col=RGB(63,127,0);break;
  case 75:col=RGB(95,127,63);break;
    
  case 76:col=RGB(38,76,0);break;
  case 77:col=RGB(57,76,38);break;
  case 78:col=RGB(19,38,0);break;
  case 79:col=RGB(28,38,19);break;
  case 80:col=RGB(63,255,0);break;
    
  case 81:col=RGB(159,255,127);break;
  case 82:col=RGB(41,165,0);break;
  case 83:col=RGB(103,165,82);break;
  case 84:col=RGB(31,127,0);break;
  case 85:col=RGB(79,127,63);break;
    
  case 86:col=RGB(19,76,0);break;
  case 87:col=RGB(47,76,38);break;
  case 88:col=RGB(9,38,0);break;
  case 89:col=RGB(23,38,19);break;
  case 90:col=RGB(0,255,0);break;
    
  case 91:col=RGB(127,255,127);break;
  case 92:col=RGB(0,165,0);break;
  case 93:col=RGB(82,165,82);break;
  case 94:col=RGB(0,127,0);break;
  case 95:col=RGB(63,127,63);break;
    
  case 96:col=RGB(0,76,0);break;
  case 97:col=RGB(38,76,38);break;
  case 98:col=RGB(0,38,0);break;
  case 99:col=RGB(19,38,19);break;
  case 100:col=RGB(0,255,63);break;
    
  case 101:col=RGB(127,255,159);break;
  case 102:col=RGB(0,165,41);break;
  case 103:col=RGB(82,165,103);break;
  case 104:col=RGB(0,127,31);break;
  case 105:col=RGB(63,127,79);break;
    
  case 106:col=RGB(0,76,19);break;
  case 107:col=RGB(38,76,47);break;
  case 108:col=RGB(0,38,9);break;
  case 109:col=RGB(19,38,23);break;
  case 110:col=RGB(0,255,127);break;
    
  case 111:col=RGB(127,255,191);break;
  case 112:col=RGB(0,165,82);break;
  case 113:col=RGB(82,165,124);break;
  case 114:col=RGB(0,127,63);break;
  case 115:col=RGB(63,127,95);break;
    
  case 116:col=RGB(0,76,38);break;
  case 117:col=RGB(38,76,57);break;
  case 118:col=RGB(0,38,19);break;
  case 119:col=RGB(19,38,28);break;
  case 120:col=RGB(0,255,191);break;
    
  case 121:col=RGB(127,255,223);break;
  case 122:col=RGB(0,165,124);break;
  case 123:col=RGB(82,165,145);break;
  case 124:col=RGB(0,127,95);break;
  case 125:col=RGB(63,127,111);break;
    
  case 126:col=RGB(0,76,57);break;
  case 127:col=RGB(38,76,66);break;
  case 128:col=RGB(0,38,28);break;
  case 129:col=RGB(19,38,33);break;
  case 130:col=RGB(0,255,255);break;
    
  case 131:col=RGB(127,255,255);break;
  case 132:col=RGB(0,165,165);break;
  case 133:col=RGB(82,165,165);break;
  case 134:col=RGB(0,127,127);break;
  case 135:col=RGB(63,127,127);break;
    
  case 136:col=RGB(0,76,76);break;
  case 137:col=RGB(38,76,76);break;
  case 138:col=RGB(0,38,38);break;
  case 139:col=RGB(19,38,38);break;
  case 140:col=RGB(0,191,255);break;
    
  case 141:col=RGB(127,223,255);break;
  case 142:col=RGB(0,124,165);break;
  case 143:col=RGB(82,145,165);break;
  case 144:col=RGB(0,95,127);break;
  case 145:col=RGB(63,111,127);break;
    
  case 146:col=RGB(0,57,76);break;
  case 147:col=RGB(38,66,76);break;
  case 148:col=RGB(0,28,38);break;
  case 149:col=RGB(19,33,38);break;
  case 150:col=RGB(0,127,255);break;
    
  case 151:col=RGB(127,191,255);break;
  case 152:col=RGB(0,82,165);break;
  case 153:col=RGB(82,124,165);break;
  case 154:col=RGB(0,63,127);break;
  case 155:col=RGB(63,95,127);break;
    
  case 156:col=RGB(0,38,76);break;
  case 157:col=RGB(38,57,76);break;
  case 158:col=RGB(0,19,38);break;
  case 159:col=RGB(19,28,38);break;
  case 160:col=RGB(0,63,255);break;
    
  case 161:col=RGB(127,159,255);break;
  case 162:col=RGB(0,41,165);break;
  case 163:col=RGB(82,103,165);break;
  case 164:col=RGB(0,31,127);break;
  case 165:col=RGB(63,79,127);break;
    
  case 166:col=RGB(0,19,76);break;
  case 167:col=RGB(38,47,76);break;
  case 168:col=RGB(0,9,38);break;
  case 169:col=RGB(19,23,38);break;
  case 170:col=RGB(0,0,255);break;
    
  case 171:col=RGB(127,127,255);break;
  case 172:col=RGB(0,0,165);break;
  case 173:col=RGB(82,82,165);break;
  case 174:col=RGB(0,0,127);break;
  case 175:col=RGB(63,63,127);break;
    
  case 176:col=RGB(0,0,76);break;
  case 177:col=RGB(38,38,76);break;
  case 178:col=RGB(0,0,38);break;
  case 179:col=RGB(19,19,38);break;
  case 180:col=RGB(63,0,255);break;
    
  case 181:col=RGB(159,127,255);break;
  case 182:col=RGB(41,0,165);break;
  case 183:col=RGB(103,82,165);break;
  case 184:col=RGB(31,0,127);break;
  case 185:col=RGB(79,63,127);break;
    
  case 186:col=RGB(19,0,76);break;
  case 187:col=RGB(47,38,76);break;
  case 188:col=RGB(9,0,38);break;
  case 189:col=RGB(23,19,38);break;
  case 190:col=RGB(127,0,255);break;
    
  case 191:col=RGB(191,127,255);break;
  case 192:col=RGB(82,0,165);break;
  case 193:col=RGB(124,82,165);break;
  case 194:col=RGB(63,0,127);break;
  case 195:col=RGB(95,63,127);break;
    
  case 196:col=RGB(38,0,76);break;
  case 197:col=RGB(57,38,76);break;
  case 198:col=RGB(19,0,38);break;
  case 199:col=RGB(28,19,38);break;
  case 200:col=RGB(191,0,255);break;
    
  case 201:col=RGB(223,127,255);break;
  case 202:col=RGB(124,0,165);break;
  case 203:col=RGB(145,82,165);break;
  case 204:col=RGB(95,0,127);break;
  case 205:col=RGB(111,63,127);break;
    
  case 206:col=RGB(57,0,76);break;
  case 207:col=RGB(66,38,76);break;
  case 208:col=RGB(28,0,38);break;
  case 209:col=RGB(33,19,38);break;
  case 210:col=RGB(255,0,255);break;
    
  case 211:col=RGB(255,127,255);break;
  case 212:col=RGB(165,0,165);break;
  case 213:col=RGB(165,82,165);break;
  case 214:col=RGB(127,0,127);break;
  case 215:col=RGB(127,63,127);break;
    
  case 216:col=RGB(76,0,76);break;
  case 217:col=RGB(76,38,76);break;
  case 218:col=RGB(38,0,38);break;
  case 219:col=RGB(38,19,38);break;
  case 220:col=RGB(255,0,191);break;
    
  case 221:col=RGB(255,127,223);break;
  case 222:col=RGB(165,0,124);break;
  case 223:col=RGB(165,82,145);break;
  case 224:col=RGB(127,0,95);break;
  case 225:col=RGB(127,63,111);break;
    
  case 226:col=RGB(76,0,57);break;
  case 227:col=RGB(76,38,66);break;
  case 228:col=RGB(38,0,28);break;
  case 229:col=RGB(38,19,33);break;
  case 230:col=RGB(255,0,127);break;
    
  case 231:col=RGB(255,127,191);break;
  case 232:col=RGB(165,0,82);break;
  case 233:col=RGB(165,82,124);break;
  case 234:col=RGB(127,0,63);break;
  case 235:col=RGB(127,63,95);break;
    
  case 236:col=RGB(76,0,38);break;
  case 237:col=RGB(76,38,57);break;
  case 238:col=RGB(38,0,19);break;
  case 239:col=RGB(38,19,28);break;
  case 240:col=RGB(255,0,63);break;
    
  case 241:col=RGB(255,127,159);break;
  case 242:col=RGB(165,0,41);break;
  case 243:col=RGB(165,82,103);break;
  case 244:col=RGB(127,0,31);break;
  case 245:col=RGB(127,63,79);break;
    
  case 246:col=RGB(76,0,19);break;
  case 247:col=RGB(76,38,47);break;
  case 248:col=RGB(38,0,9);break;
  case 249:col=RGB(38,19,23);break;
  case 250:col=RGB(0,0,0);break;
    
  case 251:col=RGB(51,51,51);break;
  case 252:col=RGB(102,102,102);break;
  case 253:col=RGB(153,153,153);break;
  case 254:col=RGB(244,244,244);break;
  case 255:col=RGB(255,255,255);break;
    
	default:
    col = RGB(255,255,255);
    break;
  }
  return col;
}
time_t get_time(std::string time)
{
	time_t t;
	struct tm tm1;
	char time_str[100];
	CString s = time.c_str();
	s.Replace("-", " ");

	strcpy(time_str,s.GetBuffer(0));
	sscanf(time_str,"%d-%d-%d %d:%d:%d",&tm1.tm_year,&tm1.tm_mon,&tm1.tm_mday,&tm1.tm_hour,&tm1.tm_min,&tm1.tm_sec);   
	tm1.tm_year -= 1900; 
	tm1.tm_mon -= 1; 
	t = mktime(&tm1);



	return t;	
}









