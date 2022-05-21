#include<iostream>
#include<vector>
using namespace std;


class StringRadixClass {
		int Gi;
		string str;
	public:
		StringRadixClass(int G,string s) {
			this->Gi = G;
			this->str = s;
		}
		
		int getGi(){
			return Gi;
		}
		
		void setGi(int gi){
			Gi = gi;
		}
		
		string getStr(){
			return str;
		}
		
		void setStr(string s){
			str = s;
		}
};

class StringSortAlgorithm {
	
	//字符串个数
	int MAX_SIZE = 0;
	//字符串数组中最长长度
	int MAX_LEN = 0;
	//记录每个UL的Zi值
	int* Z;
	//按照字母表顺序记录第i个位置出现的全部字母
	vector<string> UL;
	//记录每个字符串的G值
	vector<int> G;
	
	//待构造的字符串数组
	vector<string> arrs;
	//待排序字符串序列
	vector<StringRadixClass> stringRadixArrs;
	//排序后的字符串序列
	vector<StringRadixClass> sortedStringArrs;
	
	public:
		StringSortAlgorithm(vector<string> arrs) {
			this->arrs = arrs;
			MAX_SIZE = arrs.size();
			
			init();
		}
		
		void init(){
			//获取字符串最长的长度Size
			for(int i=0;i<MAX_SIZE;++i){
				//TODO
				string tmp = arrs.at(i);
				int size = tmp.size();
				if(size > MAX_LEN)
					MAX_LEN = size;
			}
			
			
			int z[MAX_LEN];
			Z = z;
			
			
			//初始化UL表
			for(int i=0;i<MAX_LEN;++i){
				int alph[26] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
				int ULi_size = 0;
				for(int j=0;j<MAX_SIZE;++j){
					string str = arrs.at(j);
					int len = str.size();
					if(len > i){
						alph[str.at(i) - 'a'] = 1;
						ULi_size ++;
					}
				}
				
				char ULi[ULi_size];
				int k = 0;
				for(int j=0;j<26;++j){
					if(alph[j] == 1){
						ULi[k++] = 'a' + j;
					}
				}
				
				ULi[k] = '\0';
				string uli = ULi;
				UL.push_back(uli);
			}
			
			//初始化Z表
			for(int i=0;i<MAX_LEN;++i){
				int count = 1;
				for(int j=i+1;j<MAX_LEN;++j){
					count *= UL.at(j).size();
				}
				Z[i] = count;
			}
			
			//算出每个字符串的Gi(c)
			for(int i=0;i<MAX_SIZE;++i){
				string tmp = arrs.at(i);
				int Gi = 0;
				int Zi = 0;
				int hi = 0;
				int size = tmp.size();
				for(int j=0;j<size;++j){
					int len = UL[j].size();
					for(int k=0;k<len;++k){
						if(tmp.at(j) == UL[j].at(k)){
							hi = k;
							Zi = Z[j];
							Gi += hi * Zi;
							break;
						}
					}
				}
				G.push_back(Gi);
				
				StringRadixClass r = StringRadixClass(Gi,tmp);
				stringRadixArrs.push_back(r);
			}
		}
		
		int MaxBit(vector<StringRadixClass> input)    //求出数组中最大数的位数
		{
			int max_num = input.at(0).getGi();      //默认最大数为第一个数字
			int size = input.size();
			for (int i = 0; i < size; i++)  //找出数组中的最大数
			{
				if (input.at(i).getGi() > max_num)
				{
					max_num = input.at(i).getGi();
				}
			}
			int p = 0;
			while (max_num > 0)
			{
				p++;
				max_num /= 10;   //每次除以10取整，即可去掉最低位
			}
			return p;
		}
		
		int GetNum(int num, int d)   //取出所给数字的第d位数字
		{
			int p = 1;
			while (d - 1 > 0)
			{
				p *= 10;
				d--;
			}
			return num / p % 10;
		}
		
		void RadixSort(){
			int length = stringRadixArrs.size();
			vector<StringRadixClass> bucket;   //创建临时存放排序过程中的数据
			vector<int> count(10);   //创建按位计数的技术容器，即记录排序中按个位、十位...各个数的位置的个数
			
			for(int i=0;i<length;++i){
				bucket.push_back(stringRadixArrs.at(i));
			}
			
			for (int d = 1; d <= MaxBit(stringRadixArrs); d++) {
				// 计数器清0
				for (int i = 0; i < 10; i++) {
					count[i] = 0;
				}
		
				// 统计各个桶中的个数
				for (int i = 0; i < length; i++) {
					count[GetNum(stringRadixArrs.at(i).getGi(), d)]++;
				}
		
				for (int i = 1; i < 10; i++) {     //得到每个数应该放入bucket中的位置
					count[i] += count[i - 1];
				}
		
				for (int i = length - 1; i >= 0; i--) {  //采用倒序进行排序是为了不打乱已经排好的顺序
					int k = GetNum(stringRadixArrs.at(i).getGi(), d);
					bucket[count[k] - 1] = stringRadixArrs.at(i);
					count[k]--;
				}
		
		
				for (int j = 0; j < length; j++)    // 临时数组复制到 input 中
				{
					StringRadixClass r = bucket.at(j);
					
					stringRadixArrs.at(j).setGi(r.getGi());
					stringRadixArrs.at(j).setStr(r.getStr());
				}
			}
			
			cout<<"排序后的结果："<<endl;
			for(int k=0;k<length;++k){
				cout<<stringRadixArrs.at(k).getStr()<<":"<<stringRadixArrs.at(k).getGi()<<endl;
			}
			
			sortedStringArrs = stringRadixArrs;
		}
};




int main(){
	vector<string> arrs;
	
	int n;
	
	cout<<"请输入需要排序的字符串个数："<<endl;
	cin>>n;
	
	string in;
	
	cout<<"请输入"<<n<<"个字符串："<<endl;
	for(int i=0;i<n;++i){
		cin>>in;
		arrs.push_back(in);
	}
	
	StringSortAlgorithm s = StringSortAlgorithm(arrs);
	s.RadixSort();
	
	return 0;
}
