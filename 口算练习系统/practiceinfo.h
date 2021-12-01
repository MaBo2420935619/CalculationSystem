#pragma once
#pragma once
#include <string>
using namespace std;
class History
{
private:
	string name;
	int titleNumber;
	int titleScore;
	int freqScore;
	int freq;
	int time;
public:
	History(string sname, int stitleNumber, int stitleScore, int sfreqScore, int sfreq, int stime) {
		name = sname;
		titleNumber = stitleNumber;
		titleScore = stitleScore;
		freqScore = sfreqScore;
		freq = sfreq;
		time = stime;
	}

	/*string getName() {
		return name;
	}
*/
	void setName(string sname) {
		name = sname;
	}

	//int getTitleNumber() {
	//	return titleNumber;
	//}

	void setTitleNumber(int stitleNumber) {
		titleNumber = stitleNumber;
	}

	/*int getTitleScore() {
		return titleScore;
	}*/

	void setTitleScore(int stitleScore) {
		titleScore = stitleScore;
	}

	/*int getFreqScore() {
		return freqScore;
	}*/

	void setFreqScore(int sfreqScore) {
		freqScore = sfreqScore;
	}

	//int getFreq() {
	//	return freq;
	//}

	void setFreq(int sfreq) {
		freq = sfreq;
	}

	//int getTime() {
	//	return time;
	//}

	void setTime(int stime) {
		time = stime;
	}
};

