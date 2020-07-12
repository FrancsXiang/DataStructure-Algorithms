#include <iostream>
#include <string>
#include <unordered_map>
using namespace std;

struct UniqueState {
	string name;
	string id;
	int age;
	UniqueState(string name_, string id_, int age_) : name(name_), id(id_), age(age_) {}
	friend ostream& operator<< (ostream& os, const UniqueState& state) {
		return os << "[ " << state.name << " " << state.id << " " << state.age << " ]";
	}
};

struct SharedState {
	string tutor;
	string department;
	SharedState(string tutor_, string departmenet_) : tutor(tutor_), department(departmenet_) {}
	friend ostream& operator<< (ostream& os, const SharedState& state) {
		return os << "[ " << state.department << " " << state.tutor << " ]";
	}
};

class FlyWeight {
public:
	FlyWeight() {};
	FlyWeight(const SharedState* state) : shared_state(state) {}
	FlyWeight(const FlyWeight& other) : shared_state(other.get_state()) {}
    const SharedState* get_state() const { return shared_state; }
	void operation (UniqueState* unique_state) const {
		/*cout << "Flying Weight operation with\n" <<
			"SharedState:" << *shared_state << endl <<
			"UniqueState:" << *unique_state << endl;*/
		cout << *shared_state <<  " " << *unique_state << endl;
	}
private:
	const SharedState* shared_state;
};

class FlyWeightFactory {
public:
	FlyWeightFactory(initializer_list<SharedState> list) {
		for (SharedState state : list) {
			fly_weights[getKey(state)] = new FlyWeight(&state);
		}
	}
	FlyWeight* getFlyWeight(const SharedState& state) {
		string key = getKey(state);
		if (fly_weights.find(key) == fly_weights.end()) {
			cout << "can't find a fly_weight, create automatically." << endl;
			fly_weights[key] = new FlyWeight(&state);
		}
		else {
			cout << "find a fly_weight successfully." << endl;
		}
		return fly_weights[key];
	}
	void list_fly_weights() const {
		for (auto& elem : fly_weights) cout << elem.first << endl;
	}
private:
	unordered_map<string, FlyWeight*> fly_weights;
	string getKey(const SharedState& state) const{ return state.tutor + " " + state.department; }
};

void client(FlyWeightFactory& factory, const string name, const string id, const int age, const string tutor, const string department) {
	const FlyWeight* fly_weight = factory.getFlyWeight(*new SharedState(tutor, department));
	//fly_weight->operation(new UniqueState(name, id, age));
}

int main()
{
	FlyWeightFactory* factory = new FlyWeightFactory({ SharedState("lishu","xingongyuan"), SharedState("chenshu","faxueyuan") });
	factory->list_fly_weights();
	client(*factory, "fanxiang", "01", 23, "chenshu", "faxueyuan");
	client(*factory, "tanlinxiang", "02", 22, "lishu2", "xingongyuan");
	factory->list_fly_weights();
	delete factory;
	return 0;
}
