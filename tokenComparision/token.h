#include <string>
#include <vector>
#include <cmath>
#include <sstream>

class token{
public:
	std::string data;
	long count;
	token(){data = ""; count = 0;};
	token(std::string str, long num){data = str; count = num;}
	~token(){}
	void append(std::string str, long num){
		data = str;
		count = num;
	}

	friend std::istream& operator >> (std::istream& ins, token& target){
		ins >> target.data;
		ins >> target.count;
		return ins;
	}

	bool operator > (const token source) {return data > source.data;}
	bool operator < (const token source) {return data < source.data;}
	bool operator == (const token source) {return data == source.data;}
	void operator = (const token other) {data = other.data; count = other.count;}
};

class tokenList{
public:
	std::vector<token> list;
	std::string host;
	long sumCount;

	tokenList(){host = "";}
	tokenList(std::string str){host = str; sumCount = 0;}
	~tokenList(){sumCount = 0;}
	void append(std::string str, long num){
		token x(str,num);
		list.push_back(x);
	}

	friend std::istream& operator >> (std::istream& ins, tokenList& target){
		token x;
		ins >> x;
		target.sumCount = target.sumCount + x.count;
		target.list.push_back(x);
		return ins;
	}

	friend std::ostream& operator << (std::ostream& outs, tokenList& target){
		for (auto& x : target.list){
			outs << x.data << " " << x.count << std::endl;
		}
		return outs;
	}

	std::string compare(tokenList& other){
		if (sumCount/other.sumCount > 3 || sumCount/other.sumCount > 1/3){
			return "";
		}
		long total = 0, sim = 0;
		int track1 = 0, track2 = 0;
		while (true){
			if (track1 == list.size()){
					while (track2 < other.list.size()){
						total = total + other.list[track2].count;
						track2++;
					}
					break;
			}
			if (track2 == other.list.size()){
					while (track1 < list.size()){
						total = total + list[track1].count;
						track1++;
					}
					break;
			}
			if(list[track1] > other.list[track2]){
				total = total + other.list[track2].count;
				track2++;
				
			} else{
				if(list[track1] < other.list[track2]){
					total = total + list[track1].count;
					track1++;
				}
				else {
					long s = list[track1].count + other.list[track2].count;
					total  = total + s;
					sim = sim + s - std::abs(list[track1].count - other.list[track2].count);
					track1++;
					track2++;
				}
			}
			
			
		}
		std::ostringstream sstr;
		double percent = double(double(sim)*100/double(total));
		if(percent < 30){
			return "";
		}
		else{
			sstr << host << " " << other.host << " " << total << " " << sim << " " << percent;
			return sstr.str();
		}
	}

	void operator = (tokenList const other){
		for(auto& tk : other.list){
			token temp = tk;
			list.push_back(temp);
		}
	}
};
