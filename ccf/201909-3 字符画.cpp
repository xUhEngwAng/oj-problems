#include <string>
#include <iostream>
#include <vector>
using namespace std;

struct Color{
	int red = 0, blue = 0, green = 0;
	bool operator!=(const Color &right){
		return !(red == right.red && blue == right.blue && green == right.green);
	}
}curr;

vector<vector<Color>> raw, res;

int to_decimal(string str){
	int ret = 0;
	if(isdigit(str[0])) ret += 16 * (str[0] - '0');
	else ret += 16 * (str[0] - 'a' + 10);
	if(isdigit(str[1])) ret += str[1] - '0';
	else ret += str[1] - 'a' + 10;
	return ret;
}

void getRGB(const string &str, int &red, int &blue, int &green){
	string tmp;
	if(str.size() == 2)
		for(int ix = 0; ix != 6; ++ix)
			tmp.push_back(str[1]);
	else if(str.size() == 4)
		for(int ix = 1; ix <= 3; ++ix){
			tmp.push_back(str[ix]);
			tmp.push_back(str[ix]);
		}
	else tmp = str.substr(1);
	red = to_decimal(tmp.substr(0, 2));
	green = to_decimal(tmp.substr(2, 2));
	blue = to_decimal(tmp.substr(4));
}

string set_color(const Color &c){
	string ret;
	ret.push_back(0x1b);
	ret.push_back('[');
	curr = c;
	if(c.red == 0 && c.blue == 0 && c.green == 0)
		ret.push_back('0');
	else{
		ret += "48;2;";
		ret += to_string(c.red) + ";";
		ret += to_string(c.green) + ";";
		ret += to_string(c.blue);
	}
	ret.push_back('m');
	return ret;
}

int main(){
	freopen("1.in", "r", stdin);
	freopen("1.out", "w", stdout);
	int m, n, p, q, xpos, ypos;
	int red, blue, green;
	string str, output;
	cin >> m >> n >> p >> q;
	raw = vector<vector<Color>>(n, vector<Color>(m));
	res = vector<vector<Color>>(n / q, vector<Color>(m / p));
	for(int ix = 0; ix != n; ++ix)
		for(int jx = 0; jx != m; ++jx){
			cin >> str;
			getRGB(str, red, blue, green);
			raw[ix][jx].red = red;
			raw[ix][jx].blue = blue;
			raw[ix][jx].green = green;
			//cout << red << ' ' << green << ' ' << blue << endl;
		}
	for(int ix = 0; ix != n; ix += q)
		for(int jx = 0; jx != m; jx += p){
			red = blue = green = 0;
			for(int kx = ix; kx != ix + q; ++kx)
				for(int lx = jx; lx != jx + p; ++lx){
					red += raw[kx][lx].red;
					blue += raw[kx][lx].blue;
					green += raw[kx][lx].green;
				}
			xpos = ix / q;
			ypos = jx / p;
			res[xpos][ypos].red = red / (p * q);
			res[xpos][ypos].blue = blue / (p * q);
			res[xpos][ypos].green = green / (p * q);
		}
	str.clear();
	for(int ix = 0; ix != res.size(); ++ix){
		for(int jx = 0; jx != res[0].size(); ++jx){
			//cout << res[ix][jx].red << ' ' << res[ix][jx].green << ' ' << res[ix][jx].blue << endl;
			if(res[ix][jx] != curr)
				str += set_color(res[ix][jx]);
			str.push_back(' ');
		}
		if(!(curr.red == 0 && curr.blue == 0 && curr.green == 0))
			str += set_color(Color());
		str.push_back('\n');
	}
	int digit;
	for(char ch : str){
		output.push_back('\\');
		output.push_back('x');
		digit = ch / 16;
		if(digit < 10) output.push_back(digit + '0');
		else output.push_back(digit - 10 + 'A');
		digit = ch % 16;
		if(digit < 10) output.push_back(digit + '0');
		else output.push_back(digit - 10 + 'A');
	}
	cout << output;
	return 0;
}
