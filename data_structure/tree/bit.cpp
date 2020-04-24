#include <iostream>
#include <vector>
//#define P_MODIFY //point modify,region query
#define R_MODIFY //region modify,point query
using namespace std;
typedef long long LL;

class BIT
{
public:
	BIT(vector<LL>&);
	~BIT();
	void update(LL, LL);
	LL search(LL, LL);
private:
	int len;
	vector<LL> s;
	LL lower_bits(LL);
	LL pre_sum(LL);
};

BIT::BIT(vector<LL>& orgin)
{
	len = orgin.size();
	s.resize(len + 1);
	for (LL i = 0; i < len; i++) update(i, orgin[i]);
}

BIT::~BIT()
{
	s.clear();
}

void BIT::update(LL index, LL val) {
	index++;
	if (index<=0 || index>len) throw "index out of range!";
	for (LL i = index; i <= len; i += lower_bits(i)) s[i] += val;
}

LL BIT::pre_sum(LL index) {
	LL sum = 0;
	for (LL i = index; i; i -= lower_bits(i)) sum += s[i];
	return sum;
}

LL BIT::lower_bits(LL val) {
	return val & -val;
}

LL BIT::search(LL low, LL high) {
	low++; high++;
	if (low<=0 || high>len) throw "index out of range!";
	return pre_sum(high) - pre_sum(low-1);
}

int main()
{
	vector<LL> con;
	vector<LL> diff;
	try
	{	
		#ifdef P_MODIFY
      for (int i = 0; i < 10; i++) con.push_back(i);
      BIT bt(con);
      cout << bt.search(4, 6) << endl;
      bt.update(4, 6);
      cout << bt.search(0, 5) << endl;
		#else
      for (int i = 0; i < 10; i++) con.push_back(i);
      diff.resize(con.size());
      diff[0] = con[0];
      for (int i = 1; i < 10; i++) diff[i] = con[i] - con[i - 1];
      //index i to j added val,query point with index
      BIT bt(diff);
      cout << bt.search(0, 3) << endl;
      bt.update(3, 1);
      bt.update(8, -1);
      cout << bt.search(0, 7) << endl;
		#endif
	}
	catch (const char* msg)
	{
		cerr << msg << endl;
	}
	return 0;
}
