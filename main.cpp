#include <iostream>  
#include <fstream>
#include <vector>
#include <ctime>  
#include <cstdlib>  
#include <cmath>  
#define INF 9999999  
using namespace std;

class TSP {
private:
	int city;//������Ŀ
	double loc_distance = 0; //��ǰ����
	double min_distance = INF; //Ŀǰ���ҵ�����̾���
	vector<int> temp; //�м�·��
	vector<int> result;//����Ŀǰ����·��
	vector<vector<double>> distance;//���м�������
public:
	//�������������ļ�ʱ
	TSP(int city, int line, string file): temp(city), result(city), distance(city, vector<double>(city, INF)) {
		this->city = city;
		std::ifstream in(file);
		std::cin.rdbuf(in.rdbuf());
		for (int i = 0; i < line; i++)
		{
			int city_a, city_b;
			double k;
			cin >> city_a >> city_b >> k;
			distance[city_a][city_b] = distance[city_b][city_a] = k;//��ʼ���������
		}
		for (int i = 0; i < city; i++) {
			temp[i]=i;//��ʼ��·��
			if (i != city -1) {
				loc_distance += distance[i][i + 1];
			}
		}
		loc_distance += distance[city -1][1];//�����ʼ����
	}
	//���������������ļ�ʱ
	TSP(int city) : temp(city), result(city), distance(city, vector<double>(city, INF)) {
		this->city = city;
		srand((unsigned)time(NULL));
		for (size_t i = 0; i < city -1; i++)
		{
			for (size_t j = i + 1; j < city; j++) {
				float k = (rand() % 10000)/100.0;//�����������
				//cout << i << " " << j << " " << k << endl; 
				distance[i][j] = distance[j][i] = k;//��ʼ���������
			}
		}
		for (size_t i = 0; i < city; i++) {
			temp[i] = i;//��ʼ��·��
			if (i != city - 1) {
				loc_distance += distance[i][i + 1];
			}
		}
		loc_distance += distance[city - 1][1];//�����ʼ����
	}
	double calculate(int loop = 40 , const double t = 1 , const double delta = 0.999,const double epsilon= 1e-30, const int limit=300000) {
		for (int i = loop; i > 0; i--)
		{
			long count = 0;//��������  
			srand((unsigned)time(NULL));//��ʼ����������� 
			double temperature = t;
			while (temperature > epsilon && count <=limit) {
				int t1 = rand() % (city - 1) + 1, t2 = rand() % (city - 1) + 1;//����������λ��   
				if (t1 != t2) {
					swap(temp[t1], temp[t2]);//������λ��   
					double ndist = 0;
					for (int j = 0; j<city - 1; j++)ndist += distance[temp[j]][temp[j + 1]];
					ndist += distance[temp[city - 1]][temp[1]];
					double df = (ndist - loc_distance);
					if (df<0) {//��ǰ�����   
						loc_distance = ndist;
					}
					else if (exp(-df / temperature)>(rand() % 100) / 100.0) {//����   
						loc_distance = ndist;
					}
					else {
						swap(temp[t1], temp[t2]);
					}
					temperature *= delta;//����  
				}
				count++;
			}
			cout << "��ѭ��" << loop-i+1 << "�Σ��˴���̾���" << loc_distance << endl;
			if (loc_distance<min_distance) {
				min_distance = loc_distance;
				result.assign(temp.begin(), temp.end());
			}
		}
		cout << "������ɣ�" << endl;
		return min_distance;
	}
	vector<int> detail() {
		return result;
	}
};
int main() {
	//��һ����ʽ��ָ�������ļ������������������Ŀ���ļ��������ļ�����
	TSP tsp = TSP(35, 595, "input.txt");
	cout<<"��̳���:"<<tsp.calculate()<<endl;
	cout << "·��:";
	auto result = tsp.detail();
	for (auto iter = result.cbegin(); iter != result.cend(); iter++)
	{
		cout << (*iter) << " ";
	}
	cout<<endl;
	
	//�ڶ�����ʽ����ָ�������ļ������������������Ŀ��
	TSP tsp1 = TSP(10);
	cout << "��̳���:" << tsp1.calculate() << endl;
	cout << "·��:";
	result = tsp1.detail();
	for (auto iter = result.cbegin(); iter != result.cend(); iter++)
	{
		cout << (*iter) << " ";
	}
	return 0;
}
