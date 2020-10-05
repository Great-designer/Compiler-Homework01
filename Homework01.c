#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>

char cc;
char token[2048];
int num;

int symbol;

const int BEGINSY=1;
const int ENDSY=2;
const int FORSY=3;
const int DOSY=4;
const int IFSY=5;
const int THENSY=6;
const int ELSESY=7;

const int IDSY=8;
const int INTSY=9;

const int COLONSY=10;
const int PLUSSY=11;
const int STARSY=12;
const int COMMASY=13;
const int LPARSY=14;
const int RPARSY=15;
const int ASSIGNSY=16;

int reserver()
{
	if(strcmp(token,"BEGIN")==0)
	{
		return 1;
	}
	else if(strcmp(token,"END")==0)
	{
		return 2;
	}
	else if(strcmp(token,"FOR")==0)
	{
		return 3;
	}
	else if(strcmp(token,"DO")==0)
	{
		return 4;
	}
	else if(strcmp(token,"IF")==0)
	{
		return 5;
	}
	else if(strcmp(token,"THEN")==0)
	{
		return 6;
	}
	else if(strcmp(token,"ELSE")==0)
	{
		return 7;
	}
	else
	{
		return 0;
	}
}

FILE*in;


int getsym()//返回类别码 
{
	cc=' ';
	memset(token,0,sizeof(token));
	while(isspace(cc))//读字符，跳空格、换行和Tab 
	{
		cc=fgetc(in);
	}
	if(isalpha(cc))//判断当前字符是否一个字母 
	{
		while(isalpha(cc)||isdigit(cc))//将字符拼接成字符串 
		{
			strncat(token,&cc,1);
			cc=fgetc(in); 
		}
		ungetc(cc,in);//指针后退一个字符
		int resultValue=reserver();//resultValue查找保留字的返回值 
		if(resultValue==0)//token中字符串为标识符 
		{
			symbol=IDSY;
		}
		else//token中字符串为保留字 
		{
			symbol=resultValue;
		}
	}
	else if(isdigit(cc))//判断当前字符是否一个数字 
	{
		while(isdigit(cc))//将字符拼接成整数 
		{
			strncat(token,&cc,1);
			cc=fgetc(in);
		}
		ungetc(cc,in);
		num=atoi(token);//将token中的字符串转换为整数 
		symbol=INTSY;//此时识别的单词是整数 
	}
	else
	{
		switch(cc)
		{
			case':'://判断当前字符是否冒号 
				cc=fgetc(in);
				if(cc=='=')//判断是否赋值符号 
				{
					symbol=ASSIGNSY;
				}
				else
				{
					ungetc(cc,in);
					symbol=COLONSY;
				}
			break;
			case'+'://判断是否加号
				symbol=PLUSSY;
			break;
			case'*'://判断是否星号
				symbol=STARSY;
			break;
			case'('://判断是否左括号
				symbol=LPARSY;
			break;
			case')'://判断是否右括号
				symbol=RPARSY;
			break;
			case','://判断是否逗号 
				symbol=COMMASY;
			break;
			case EOF:
				symbol=-1;
			break;
			default:
				symbol=0;
		}
	}
	return 0;
}

int main(int argc,char *argv[])
{
	in=fopen(argv[1],"r");
	int t=getsym();
	while(t==0)
	{
		switch(symbol)
		{
			case 1:
				printf("Begin\n");
			break;
			case 2:
				printf("End\n");
			break;
			case 3:
				printf("For\n");
			break;
			case 4:
				printf("Do\n");
			break;
			case 5:
				printf("If\n");
			break;
			case 6:
				printf("Then\n");
			break;
			case 7:
				printf("Else\n");
			break;
			case 8:
				printf("Ident(%s)\n",token);
			break; 
			case 9:
				printf("Int(%d)\n",num);
			break;
			case 10:
				printf("Colon\n");
			break;
			case 11:
				printf("Plus\n");
			break;
			case 12:
				printf("Star\n");
			break;
			case 13:
				printf("Comma\n");
			break;
			case 14:
				printf("LParenthesis\n");
			break;
			case 15:
				printf("RParenthesis\n");
			break;
			case 16:
				printf("Assign\n");
			break;
			case -1:
				return 0;
			break;
			default:
				printf("Unknown\n");
			return 0;
		}
		t=getsym();
	}
	fclose(in);
}
