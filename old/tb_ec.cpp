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

//DH�����L
int dh_key_exchange(void)
{
	int p = 31, g = 3;
	long long int a_sec, b_sec, a_pub, b_pub, s1, s2;

	size_t n = 64;

	a_sec = 14;	//A����̔閧������(n�r�b�g�̗���)
	b_sec = 18;	//B����̔閧������(n�r�b�g�̗���)

	cout << "p=" << p << "\n" << endl;

	cout << "A����̔閧�l(a):" << a_sec << endl;
	cout << "B����̔閧�l(b):" << b_sec << endl;

	pow_fp(g, a_sec, p, &a_pub);	//A����̋��L�l
	pow_fp(g, b_sec, p, &b_pub);	//B����̋��L�l

	cout << "A����̋��L�l(g^a):" << a_pub << endl;
	cout << "B����̋��L�l(g^b):" << b_pub << endl;

	pow_fp(b_pub, a_sec, p, &s1);	//A����̏���
	pow_fp(a_pub, b_sec, p, &s2);	//B����̏���

	cout << "A�����߂���((g^b)^a):" << s1 << endl;
	cout << "B�����߂���((g^a)^b):" << s2 << endl;

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
