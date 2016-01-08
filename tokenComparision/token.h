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
};

class tokenList{
public:
	std::vector<token> list;
	std::string host;

	tokenList(){host = "";}
	tokenList(std::string str){host = str;}
	~tokenList(){}
	void append(std::string str, long num){
		token x(str,num);
		list.push_back(x);
	}

	friend std::istream& operator >> (std::istream& ins, tokenList& target){
		token x;
		ins >> x;
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
		long total = 0, sim = 0;
		while (true){
			int track1 = 0, track2 = 0;
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
			
		}
		std::ostringstream sstr;
		sstr << host << " " << other.host << " " << total << " " << sim << " " << long(sim*100/total);
		return sstr.str();
	}
};
