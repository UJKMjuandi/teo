#include <iostream>
#include <string>
using namespace std;

class Student{
	private:
		string cui;
		string apellidoPaterno;
		string apellidoMaterno;
		string nombres;
	
	public:
		Student(string _cui, string _paterno, string _materno, string _nombres){
			cui = _cui;
			apellidoPaterno = _paterno;
			apellidoMaterno = _materno;
			nombres = _nombres;
		}
	
	void presentarse() {
		cout << cui << " - " << apellidoPaterno << "/" << apellidoMaterno << ", "<< nombres << endl;
	}
};
