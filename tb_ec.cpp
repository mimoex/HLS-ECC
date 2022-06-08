#include "fp.h"

void ec_add_check()
{
	int a = 1, mod = 97;
	Point p, q, result;

	p.x = 31; p.y = 25;
	q.x = 96; q.y = 17;
	p.inf = false; q.inf = false; result.inf = false;
	result = ec_add(p, q, a, mod);

	cout << "[" << p.x << "," << p.y << "]+[" << q.x << "," << q.y << "]=[" << result.x << "," << result.y << "]" << endl;
}

//DH鍵共有
int dh_key_exchange(void)
{
	int p = 31, g = 3;
	long long int a_sec, b_sec, a_pub, b_pub, s1, s2;

	size_t n = 64;

	a_sec = 14;	//Aさんの秘密鍵生成(nビットの乱数)
	b_sec = 18;	//Bさんの秘密鍵生成(nビットの乱数)

	cout << "p=" << p << "\n" << endl;

	cout << "Aさんの秘密値(a):" << a_sec << endl;
	cout << "Bさんの秘密値(b):" << b_sec << endl;

	pow_fp(g, a_sec, p, &a_pub);	//Aさんの共有値
	pow_fp(g, b_sec, p, &b_pub);	//Bさんの共有値

	cout << "Aさんの共有値(g^a):" << a_pub << endl;
	cout << "Bさんの共有値(g^b):" << b_pub << endl;

	pow_fp(b_pub, a_sec, p, &s1);	//Aさんの処理
	pow_fp(a_pub, b_sec, p, &s2);	//Bさんの処理

	cout << "Aが求めた鍵((g^b)^a):" << s1 << endl;
	cout << "Bが求めた鍵((g^a)^b):" << s2 << endl;

	if (s1 == s2) {
		cout << "OK!" << endl;
		return 0;
	}
	else {
		cout << "NG" << endl;
		return -1;
	}
}

int main()
{
	//dh_key_exchange();
	ec_add_check();
	
	

}
