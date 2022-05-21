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
	
	//�ַ�������
	int MAX_SIZE = 0;
	//�ַ��������������
	int MAX_LEN = 0;
	//��¼ÿ��UL��Ziֵ
	int* Z;
	//������ĸ��˳���¼��i��λ�ó��ֵ�ȫ����ĸ
	vector<string> UL;
	//��¼ÿ���ַ�����Gֵ
	vector<int> G;
	
	//��������ַ�������
	vector<string> arrs;
	//�������ַ�������
	vector<StringRadixClass> stringRadixArrs;
	//�������ַ�������
	vector<StringRadixClass> sortedStringArrs;
	
	public:
		StringSortAlgorithm(vector<string> arrs) {
			this->arrs = arrs;
			MAX_SIZE = arrs.size();
			
			init();
		}
		
		void init(){
			//��ȡ�ַ�����ĳ���Size
			for(int i=0;i<MAX_SIZE;++i){
				//TODO
				string tmp = arrs.at(i);
				int size = tmp.size();
				if(size > MAX_LEN)
					MAX_LEN = size;
			}
			
			
			int z[MAX_LEN];
			Z = z;
			
			
			//��ʼ��UL��
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
			
			//��ʼ��Z��
			for(int i=0;i<MAX_LEN;++i){
				int count = 1;
				for(int j=i+1;j<MAX_LEN;++j){
					count *= UL.at(j).size();
				}
				Z[i] = count;
			}
			
			//���ÿ���ַ�����Gi(c)
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
		
		int MaxBit(vector<StringRadixClass> input)    //����������������λ��
		{
			int max_num = input.at(0).getGi();      //Ĭ�������Ϊ��һ������
			int size = input.size();
			for (int i = 0; i < size; i++)  //�ҳ������е������
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
				max_num /= 10;   //ÿ�γ���10ȡ��������ȥ�����λ
			}
			return p;
		}
		
		int GetNum(int num, int d)   //ȡ���������ֵĵ�dλ����
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
			vector<StringRadixClass> bucket;   //������ʱ�����������е�����
			vector<int> count(10);   //������λ�����ļ�������������¼�����а���λ��ʮλ...��������λ�õĸ���
			
			for(int i=0;i<length;++i){
				bucket.push_back(stringRadixArrs.at(i));
			}
			
			for (int d = 1; d <= MaxBit(stringRadixArrs); d++) {
				// ��������0
				for (int i = 0; i < 10; i++) {
					count[i] = 0;
				}
		
				// ͳ�Ƹ���Ͱ�еĸ���
				for (int i = 0; i < length; i++) {
					count[GetNum(stringRadixArrs.at(i).getGi(), d)]++;
				}
		
				for (int i = 1; i < 10; i++) {     //�õ�ÿ����Ӧ�÷���bucket�е�λ��
					count[i] += count[i - 1];
				}
		
				for (int i = length - 1; i >= 0; i--) {  //���õ������������Ϊ�˲������Ѿ��źõ�˳��
					int k = GetNum(stringRadixArrs.at(i).getGi(), d);
					bucket[count[k] - 1] = stringRadixArrs.at(i);
					count[k]--;
				}
		
		
				for (int j = 0; j < length; j++)    // ��ʱ���鸴�Ƶ� input ��
				{
					StringRadixClass r = bucket.at(j);
					
					stringRadixArrs.at(j).setGi(r.getGi());
					stringRadixArrs.at(j).setStr(r.getStr());
				}
			}
			
			cout<<"�����Ľ����"<<endl;
			for(int k=0;k<length;++k){
				cout<<stringRadixArrs.at(k).getStr()<<":"<<stringRadixArrs.at(k).getGi()<<endl;
			}
			
			sortedStringArrs = stringRadixArrs;
		}
};




int main(){
	vector<string> arrs;
	
	int n;
	
	cout<<"��������Ҫ������ַ���������"<<endl;
	cin>>n;
	
	string in;
	
	cout<<"������"<<n<<"���ַ�����"<<endl;
	for(int i=0;i<n;++i){
		cin>>in;
		arrs.push_back(in);
	}
	
	StringSortAlgorithm s = StringSortAlgorithm(arrs);
	s.RadixSort();
	
	return 0;
}
