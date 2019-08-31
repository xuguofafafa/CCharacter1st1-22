/**
*编写一个程序，把较长的输入行“折”成短一些的两行或多行，折行的位置 在输入行的第 n 列之前的最后一个非空格之后。
*要保证程序能够智能地处理输入行很长以及 
*在指定的列前没有空格或制表符时的情况。
*/
#include <stdio.h>

#define TABLENGTH 8//制表符的标志位相隔的长度
#define SUBLENGTH 10//每次折行的长度n

//用于存储每次输入的需要折的行
char line[SUBLENGTH];

void printl(int pos);//输出当前的行
int findBlank(int pos);//寻找空格符
int newPosition(int pos);//重新定位pos变量的值
int extendTab(int pos);//将制表符转换为等长的空格集

int main(){
	char c;
	int position = 0;
	while((c = getchar()) != EOF){
		line[position] = c;//将输入的字符存到数组
		if(c == '\t'){//如果是制表符则用空格填满到制表符的标志位
			postion = extendTab(position);
		}else if(c == '\n'){//如果是回车符就打印该位置之前的字符，并把位置置为0，作为新的一行
			printl(position);
			postion = 0;
		}else if( ++position >= SUBLENGTH){//其他情况就把位置加1即可，加到位置刚好超出数组的时候，回头寻找空格作判断
			postion = findBlank(postion);
			printl(postion);
			postion = newPosition(postion);
		}
		
	}
	
	return 0;
}

int extendTab(int p){
	line[p] = ' ';//将当前的位置替换为空格
	for(p ++;p < SUBLENGTH && (p % TABLENGTH) != 0;p ++){//将标志位之前的空格填满
		line[p] = ' ';
	}
	if(p < SUBLENGTH){//位置变量p还在数组范围内就返回当前的位置
		return p;
	}else{//如果超出数组的范围表示已经填空格填到最后了，则打印当前的字符数组，并返回0作为最新的字符位置
		printl(p);
		return 0;
	}
	
}

void printl(int p){//遍历打印数组中的元素

	for(int i = 0;i < p ; i ++){
		putchar(line[i]);
	}
	if(p > 0){//如果字符串存在则在打印的字符串后面打印回车键，保证下一个数组从下一行开始打
		putchar('\n');
	}
	
}

int findBlank(int p){//从某个位置回头找空格
	while(p > 0 && line[p] != ' '){//遇到不是空格的，位置就减1
		p--;
	}
	if(p == 0){//没找到就返回行的长度，在数组下标外
		return SUBLENGTH;
	}else{
		return p + 1;//有就返回遇到的空格的位置
	}
}

int newPosition(int p){//折行的时候，通常情况前半段会被打印，后半段会被打印在下一行
	int i,j;
	if(p <= 0 || p >= SUBLENGTH){//如果折行的位置在数组之外，则新的一行的位置就返回为0
		return 0;
	}else{//将后半段的字符串挪到最前面来并且返回诺过字符串后的位置
		i = 0;
		for(j = p ; j < SUBLENGTH ; j ++){
			line[i] = line[j];
			i ++;
		}
		return i;
	}
		
	}
}